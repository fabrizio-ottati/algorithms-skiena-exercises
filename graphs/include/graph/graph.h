#ifndef GRAPH_H_
#define GRAPH_H_

#include <functional>
#include <list>
#include <string>
#include <vector>

typedef int vertex_t;

constexpr vertex_t ROOT_VERTEX = -1;

// Data structure describing an edge in the Graph.
typedef struct edgenode {
  vertex_t y;
  int weight;
} edgenode_t;

// Data structure describing a Graph.
// Based on adjacency list.
struct Graph {
  std::vector<std::list<edgenode_t>> edges;
  std::vector<int> degree;
  int nvertices;
  int nedges;
  bool directed;
};

struct BFSInfo {
  std::vector<bool> processed;
  std::vector<bool> discovered;
  std::vector<vertex_t> parents;
};

void initialize_graph(Graph &g, bool directed, bool verbose = false);

void read_graph(Graph &g, bool directed, const std::string &fpath,
                bool verbose = false);

void insert_edge(Graph &g, vertex_t x, vertex_t y, bool directed,
                 bool verbose = false);

void print_graph(const Graph &g, bool verbose = false);

void init_BFSInfo(BFSInfo &info);

void bfs(Graph &g, vertex_t start, BFSInfo &info,
         std::function<void(vertex_t)> process_vertex_early = nullptr,
         std::function<void(vertex_t, vertex_t)> process_edge = nullptr,
         std::function<void(vertex_t)> process_vertex_late = nullptr);

std::vector<vertex_t> find_path(vertex_t start, vertex_t end,
                                const std::vector<vertex_t> &parents);
#endif // GRAPH_H_
