#ifndef GRAPH_H_
#define GRAPH_H_

#include <functional>
#include <list>
#include <vector>
#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

constexpr int NO_PARENT = -1;

// Data structure describing an edge in the graph.
template <typename V>
struct Edge {
  V y;
  int weight;
};

// Data structure describing a Graph<V>.
// Based on adjacency list.
template<typename V>
struct Graph {
  std::vector<std::list<Edge<V>>> edges;
  std::vector<int> degree;
  int nvertices;
  int nedges;
  bool directed;
};

template <typename V>
struct BFSInfo {
  std::vector<bool> processed;
  std::vector<bool> discovered;
  std::vector<V> parents;
};

template <typename V>
void initialize_graph(Graph<V> &g, bool directed, bool verbose = false) {
  g.nvertices = 0;
  g.nedges = 0;
  g.directed = directed;

  for (auto i = 0; i < g.edges.size(); i++) {
    g.edges[i].clear();
  }
  g.edges.clear();
  g.degree.clear();
  return;
}

template <typename V>
void read_graph(Graph<V> &g, bool directed, const std::string &fpath,
                bool verbose = false){
  std::ifstream ifs(fpath);
  if (!ifs.is_open()) {
    throw std::runtime_error("ERROR: Could not open input file.");
  }

  int m;
  V x, y;

  initialize_graph<V>(g, directed);
  if (!(ifs >> g.nvertices >> m)) {
    throw std::runtime_error("ERROR: Could not read from file.");
  }
  if (verbose)
    std::cout << "The graph contains " << g.nvertices << " vertices and " << m
         << " edges." << std::endl;

  for (auto i = 0; i < m; i++) {
    if (!(ifs >> x >> y)) {
      throw std::runtime_error("ERROR: Could not read from file.");
    }
    if (verbose)
      std::cout << "Read the following edge: (" << x << ", " << y << ")." << std::endl;
    insert_edge<V>(g, x, y, directed);
  }

  ifs.close();

  return;
}

template <typename V>
void insert_edge(Graph<V> &g, V x, V y, bool directed,
                 bool verbose = false) {
  // Initiliazing.
  Edge<V> e;
  e.weight = 0;
  e.y = y;

  // Checking if the vertex is already in the Graph.
  while (x >= g.edges.size()) {
    std::list<Edge<V>> l;
    g.edges.push_back(l);
    g.degree.push_back(0);
  }

  // Inserting the new edge to the head of the list.
  g.edges[x].push_front(e);
  g.degree[x]++;

  if (!directed) {
    insert_edge<V>(g, y, x, true);
  } else {
    g.nedges++;
  }

  return;
}

template <typename V>
void print_graph(const Graph<V> &g, bool verbose = false) {
  for (auto i = 0; i < g.nvertices; i++) {
    if (g.edges[i].size() > 0) {
      std::cout << i << ": ";
      for (const auto &e : g.edges[i]) {
        std::cout << " " << e.y;
      }
      std::cout << std::endl;
    }
  }
  return;
}

template <typename V>
void init_BFSInfo(BFSInfo<V> &info) {
  info.processed.clear();
  info.discovered.clear();
  info.parents.clear();
  return;
}

template <typename V>
void bfs(Graph<V> &g, V start, BFSInfo<V> &info,
         std::function<void(V)> process_vertex_early = nullptr,
         std::function<void(V, V)> process_edge = nullptr,
         std::function<void(V)> process_vertex_late = nullptr) {
  // Initializing the information of the graph.
  for (auto i = 0; i < g.nvertices; i++) {
    info.processed.push_back(false);
    info.discovered.push_back(false);
    info.parents.push_back(NO_PARENT);
  }

  // FIFO to store the nodes being discovered during the graph traversal.
  std::queue<V> q;

  q.push(start);
  info.discovered[start] = true;

  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    if (process_vertex_early != nullptr)
      process_vertex_early(u);
    // Setting to processed because we will visit all its edges before going to
    // the next node.
    info.processed[u] = true;

    for (const auto &e : g.edges[u]) {
      auto v = e.y;
      if (!info.processed[v] || g.directed) {
        if (process_edge != nullptr)
          process_edge(u, v);
      }
      if (!info.discovered[v]) {
        q.push(v);
        info.discovered[v] = true;
        info.parents[v] = u;
      }
    }
    if (process_vertex_late != nullptr)
      process_vertex_late(u);
  }
  return;
}

// Recursive inner function to find the path between vertices.
template <typename V>
static void find_path_r(std::vector<V> &path, V start, V end,
                        const std::vector<V> &parents) {
  if (start == end || end == NO_PARENT) {
    path.push_back(start);
    return;
  }

  find_path_r(path, start, parents[end], parents);
  path.push_back(end);
  return;
}

template <typename V>
std::vector<V> find_path(V start, V end,
                                const std::vector<V> &parents) {
  if (parents[start] != NO_PARENT) {
    std::cerr << "WARNING: The start vertex " << start << " is not a root one.\n"
         << std::endl;
  }

  std::vector<V> path;
  path.clear();
  find_path_r(path, start, end, parents);
  return path;
}

template <typename V>
std::vector<V> connected_components(Graph<V> &G) {
  BFSInfo<V> info;
  init_BFSInfo<V>(info);

  std::vector<V> roots;
  for (auto v = 0; v < G.nvertices; v++) {
    if (!info.discovered[v]) {
      roots.push_back(v);
      bfs<V>(G, v, info);
    }
  }

  return roots;
}

#endif // GRAPH_H_
