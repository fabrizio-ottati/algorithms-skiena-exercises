#ifndef GRAPH_H_
#define GRAPH_H_

#include <functional>
#include <list>
#include <string>
#include <vector>

// Data structure describing an edge in the Graph.
typedef struct edgenode {
  int y;
  int weight;
} edgenode;

// Data structure describing a Graph.
// Based on adjacency list.
struct Graph {
  std::vector<std::list<edgenode>> edges;
  std::vector<int> degree;
  int nvertices;
  int nedges;
  bool directed;
};

struct BFSInfo {
  std::vector<bool> processed;
  std::vector<bool> discovered;
  std::vector<int> parent;
};

void initialize_graph(Graph &g, bool directed, bool verbose = false);

void read_graph(Graph &g, bool directed, const std::string &fpath,
                bool verbose = false);

void insert_edge(Graph &g, int x, int y, bool directed, bool verbose = false);

void print_graph(const Graph &g, bool verbose = false);

void init_BFSInfo(BFSInfo &info);

void bfs(Graph &g, int start, BFSInfo &info,
         std::function<void(int)> process_vertex_early = nullptr,
         std::function<void(int, int)> process_edge = nullptr,
         std::function<void(int)> process_vertex_late = nullptr);

#endif // GRAPH_H_
