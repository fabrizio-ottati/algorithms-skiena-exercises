#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <string>
#include <vector>

// Data structure describing an edge in the graph.
typedef struct edgenode {
  int y;
  int weight;
} edgenode;

// Data structure describing a graph.
// Based on adjacency list.
typedef struct {
  std::vector<std::list<edgenode>> edges;
  std::vector<int> degree;
  int nvertices;
  int nedges;
  bool directed;
} graph;

void initialize_graph(graph &g, bool directed, bool verbose = false);

void read_graph(graph &g, bool directed, const std::string &fpath,
                bool verbose = false);

void insert_edge(graph &g, int x, int y, bool directed, bool verbose = false);

void print_graph(const graph &g, bool verbose = false);

#endif // GRAPH_H_
