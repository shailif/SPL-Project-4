
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "../include/Tree.h"
using namespace std;

class Graph{
public:
    Graph(vector<vector<int>> matrix);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    int  smallestN (int nodeInd);
    int GetState(int nodeInt) const;
    void setCarry(int nodeInt);
    Tree* bfs (int node, Session& session);
    void disconnectV (int vertex);
    vector <int> getA () const;
    vector<vector<int>> getEdges() const;

private:
    vector<vector<int>> edges;
    vector <int> A ; // represent if the node is healthy(-1), carry(0) or infected(1).
};

#endif
