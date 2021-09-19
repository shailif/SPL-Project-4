#include <vector>
#include <queue>
#include "../include/Tree.h"
#include "../include/Graph.h"

using namespace std;

   Graph:: Graph(std::vector<std::vector<int>> matrix) : edges(std:: move(matrix)), A(){
        for (unsigned int i = 0; i < edges.size(); i++)
            A.push_back(-1) ;
    }

    void Graph::infectNode(int nodeInd) {
        A[nodeInd] = 1;
    }

    bool Graph:: isInfected(int nodeInd){
        return A[nodeInd]==1;
    }

    int Graph:: smallestN (int nodeInd) {
        for (unsigned int i = 0; i < edges.size(); i++) {
            if (edges[nodeInd][i] == 1 && A[i]==-1)
                return i;
        }
        return -1;
    }

    int Graph:: GetState(int nodeInt) const {
        return A[nodeInt];
    }

vector<vector<int>> Graph ::getEdges() const{
        return edges;
   }
    void Graph:: setCarry(int nodeInt) {
        A[nodeInt]=0;
    }


Tree* Graph :: bfs (int node, Session& session){
    // Mark all the vertices as not visited
    vector <bool> visited;
    for(unsigned int i = 0; i < edges.size(); i++)
        visited.push_back(false);

    Tree* root = Tree:: createTree(session, node);
    queue<Tree*> queue;
    visited[root->getNode()] = true;
    queue.push(root);
    while(!queue.empty())
    {
        Tree* node = queue.front();
        queue.pop();
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            if (edges[node->getNode()][i] == 1 && !visited[i])
            {
                visited[i] = true;
                Tree *toAdd= Tree::createTree(session, i);
                node->addChildPointer(toAdd);
                queue.push(toAdd);
            }
        }
    }
return root;
}

void Graph :: disconnectV (int vertex){
    for (unsigned int i = 0; i < edges.size(); i++) {
        if (edges[vertex][i] == 1)
            edges[vertex][i]=0;
        if (edges[i][vertex] == 1)
            edges[i][vertex]=0;

    }
}

vector <int> Graph ::getA () const{
    return A;
};

