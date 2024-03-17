#include "graph/graph.h"
#include <iostream>
#include <string>

using namespace std;

void read_graph_example(const string &fpath) {
  Graph G;
  initialize_graph(G, false);
  read_graph(G, false, fpath);
  print_graph(G);
}

void bfs_example(const string &fpath) {
  Graph G;
  initialize_graph(G, false);
  read_graph(G, false, fpath);
  cout << "Here's the graph:" << endl;
  print_graph(G);
  cout << endl;

  BFSInfo info;
  bfs(G, 1, info);

  cout << "Here's the parent relation of this graph starting from node " << 1
       << ":" << endl;

  auto i = 0;
  for (const auto&p: info.parent) {
    if (G.edges[i].size() > 0) {
      cout << "The parent of " << i << " is " << p << "." << endl;
    }
    i++;
  }

  return;
}

int main(void) {
  bfs_example("./bfs_input.txt");

  return 0;
}
