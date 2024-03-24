#include "graph/graph.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void read_graph_example(const string &fpath) {
  Graph<int> G;
  initialize_graph<int>(G, false);
  read_graph<int>(G, false, fpath);
  print_graph<int>(G);
}

void bfs_example(const string &fpath, int startNode = 1) {
  Graph<int> G;
  initialize_graph<int>(G, false);
  read_graph<int>(G, false, fpath);
  cout << "Here's the graph:" << endl;
  print_graph<int>(G);
  cout << endl;

  BFSInfo<int> info;
  bfs<int>(G, startNode, info);

  cout << "Here's the parents relation of this graph starting from node " << 1
       << ":" << endl;

  auto i = 0;
  for (const auto &p : info.parents) {
    if (G.edges[i].size() > 0) {
      cout << "The parent of " << i << " is " << p << "." << endl;
    }
    i++;
  }

  return;
}

void find_path_example(const string &fpath) {
  Graph<int> G;
  initialize_graph<int>(G, false);
  read_graph<int>(G, G.directed, fpath);
  BFSInfo<int> info;
  bfs<int>(G, 1, info);
  // Finding the shortest path between two nodes.
  int start = 1, end = 6;
  auto shortestPath = find_path<int>(start, end, info.parents);
  cout << "Here's the shortest path between " << start << " and " << end << ":"
       << endl;
  for (auto i = 0; i < shortestPath.size(); i++) {
    if (i == shortestPath.size() - 1) {
      cout << " -- " << shortestPath[i] << "." << endl;
    } else if (i == 0) {
      cout << shortestPath[i];
    } else {
      cout << " -- " << shortestPath[i];
    }
  }
  return;
}

int main(void) {
  // bfs_example("./bfs_input.txt");
  find_path_example("./bfs_input.txt");

  return 0;
}
