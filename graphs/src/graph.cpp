#include "graph/graph.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

void initialize_graph(Graph &g, bool directed, bool verbose) {
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

void read_graph(Graph &g, bool directed, const string &fpath, bool verbose) {
  std::ifstream ifs(fpath);
  if (!ifs.is_open()) {
    throw runtime_error("ERROR: Could not open input file.");
  }

  int m;
  vertex_t x, y;

  initialize_graph(g, directed);
  if (!(ifs >> g.nvertices >> m)) {
    throw runtime_error("ERROR: Could not read from file.");
  }
  if (verbose)
    cout << "The Graph contains " << g.nvertices << " vertices and " << m
         << " edges." << endl;

  for (auto i = 0; i < m; i++) {
    if (!(ifs >> x >> y)) {
      throw runtime_error("ERROR: Could not read from file.");
    }
    if (verbose)
      cout << "Read the following edge: (" << x << ", " << y << ")." << endl;
    insert_edge(g, x, y, directed);
  }

  ifs.close();

  return;
}

void insert_edge(Graph &g, vertex_t x, vertex_t y, bool directed,
                 bool verbose) {
  // Initiliazing.
  edgenode_t p;
  p.weight = 0;
  p.y = y;

  // Checking if the vertex is already in the Graph.
  while (x >= g.edges.size()) {
    list<edgenode_t> l;
    g.edges.push_back(l);
    g.degree.push_back(0);
  }

  // Inserting the new edge to the head of the list.
  g.edges[x].push_front(p);
  g.degree[x]++;

  if (!directed) {
    insert_edge(g, y, x, true);
  } else {
    g.nedges++;
  }

  return;
}

void print_graph(const Graph &g, bool verbose) {
  for (auto i = 0; i < g.nvertices; i++) {
    if (g.edges[i].size() > 0) {
      cout << i << ": ";
      for (const auto &p : g.edges[i]) {
        cout << " " << p.y;
      }
      cout << endl;
    }
  }
  return;
}

void init_BFSInfo(BFSInfo &info) {
  info.processed.clear();
  info.discovered.clear();
  info.parents.clear();
  return;
}

void bfs(Graph &g, vertex_t start, BFSInfo &info,
         std::function<void(vertex_t)> process_vertex_early,
         std::function<void(vertex_t, vertex_t)> process_edge,
         std::function<void(vertex_t)> process_vertex_late) {
  // Initializing the information of the graph.
  for (auto i = 0; i < g.nvertices; i++) {
    info.processed.push_back(false);
    info.discovered.push_back(false);
    info.parents.push_back(ROOT_VERTEX);
  }

  // FIFO to store the nodes being discovered during the graph traversal.
  queue<vertex_t> q;

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

    for (const auto &p : g.edges[u]) {
      auto v = p.y;
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
static void find_path_r(vector<vertex_t> &path, vertex_t start, vertex_t end,
                        const vector<vertex_t> &parents) {
  if (start == end || end == ROOT_VERTEX) {
    path.push_back(start);
    return;
  }

  find_path_r(path, start, parents[end], parents);
  path.push_back(end);
  return;
}

vector<vertex_t> find_path(vertex_t start, vertex_t end,
                           const vector<vertex_t> &parents) {
  if (parents[start] != ROOT_VERTEX) {
    cerr << "WARNING: The start vertex " << start << " is not a root one.\n"
         << endl;
  }

  vector<vertex_t> path;
  path.clear();
  find_path_r(path, start, end, parents);
  return path;
}
