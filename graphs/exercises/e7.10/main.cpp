#include "graph/graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

constexpr bool VERBOSE = true;

const string OPS_MAP[4]{"SUM", "SUB", "MUL", "DIV"};

struct Vertex {
  int op;
  int val;
};

void dfs(fab::Graph<Vertex> &G, int u, vector<bool> &discovered,
         vector<vector<int>> &operands) {

  discovered[u] = true;

  for (const auto &edge : G.edges[u]) {
    if (!discovered[edge.v]) {
      dfs(G, edge.v, discovered, operands);
      if (G.nodes[u].op != -1) {
        operands[u].push_back(G.nodes[edge.v].val);
      }
    }
  }
  if (G.nodes[u].op != -1) {
    G.nodes[u].val = operands[u][0];
    for (auto i = 1; i < operands[u].size(); i++) {
      if (OPS_MAP[G.nodes[u].op] == "SUM") {
        G.nodes[u].val += operands[u][i];
      } else if (OPS_MAP[G.nodes[u].op] == "SUB") {
        G.nodes[u].val -= operands[u][i];
      } else if (OPS_MAP[G.nodes[u].op] == "MUL") {
        G.nodes[u].val *= operands[u][i];
      } else if (OPS_MAP[G.nodes[u].op] == "DIV") {
        G.nodes[u].val /= operands[u][i];
      }
    }
  }

  return;
}

int main(void) {

  fab::Graph<Vertex> G;
  G.directed = true;

  const string fpath("./graph.txt");
  ifstream ifs(fpath);
  if (!ifs.is_open()) {
    throw runtime_error("Unable to open the file.");
  }

  int nvertices, nedges;
  ifs >> nvertices >> nedges;
  G.nvertices = nvertices;
  G.nodes.clear();
  G.nodes.reserve(nvertices);

  vector<vector<int>> operands(nvertices);

  for (auto i = 0; i < nvertices; i++) {
    int vertex;
    ifs >> vertex >> G.nodes[vertex].op >> G.nodes[vertex].val;
  }

  // Reading the proper graph.
  for (auto e = 0; e < nedges; e++) {
    int u, v;
    ifs >> u >> v;
    fab::add_edge(G, u, v);
  }

  if (VERBOSE) {
    cout << string(80, '-') << endl;
    cout << "Printing the adjacency list." << endl;
    for (auto u = 0; u < G.nvertices; u++) {
      cout << u << ", ";
      if (G.nodes[u].op != -1) {
        cout << OPS_MAP[G.nodes[u].op];
      } else {
        cout << "val=" << G.nodes[u].val;
      }
      cout << " : ";
      for (const auto &edge : G.edges[u]) {
        cout << edge.v << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
  ifs.close();

  // Now we perform DFS.
  vector<bool> discovered(nvertices);
  for (auto it = discovered.begin(); it != discovered.end(); it++)
    *it = false;

  dfs(G, 0, discovered, operands);
  if (VERBOSE) {
    cout << "The result of the tree evaluation is " << G.nodes[0].val << "." << endl;
  }
  return 0;
}
