#include "graph/graph.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void initialize_graph(graph &g, bool directed, bool verbose) {
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

void read_graph(graph &g, bool directed, const string &fpath, bool verbose) {
  std::ifstream ifs(fpath);
  if (!ifs.is_open()) {
    throw runtime_error("ERROR: Could not open input file.");
  }

  int m, x, y;

  initialize_graph(g, directed);
  if (!(ifs >> g.nvertices >> m)) {
    throw runtime_error("ERROR: Could not read from file.");
  }
  if (verbose)
    cout << "The graph contains " << g.nvertices << " vertices and " << m
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

void insert_edge(graph &g, int x, int y, bool directed, bool verbose) {
  // Initiliazing.
  edgenode p;
  p.weight = 0;
  p.y = y;

  // Checking if the vertex is already in the graph.
  while (x >= g.edges.size()) {
    list<edgenode> l;
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

void print_graph(const graph &g, bool verbose) {
  for (auto i = 0; i < g.nvertices; i++) {
    cout << i << ": ";
    for (const auto &p : g.edges[i]) {
      cout << " " << p.y;
    }
    cout << endl;
  }
  return;
}
