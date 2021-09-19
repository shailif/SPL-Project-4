#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    //constructor
    Session(const std::string& path);

    void clear();
    //Destructor
    virtual~ Session ();

    void copy (const Session &other);
    //Copy Constructor
    Session(const Session &other);

    //Assignment Operator
    Session& operator=(const Session &other);

    void move (const Session& other);
    //Move Constructor
    Session (Session &&other);

    //Move Assignment Operator
    Session& operator=(Session &&other);

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);

    void enqueueInfected(int);
    int dequeueInfected();
    Graph getG() const;
    Graph * getGPointer() ;
    TreeType getTreeType() const;
    std::vector<Agent*> getAgents()const;
    int  getCycle () const;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> queueInfected;
    int cycle ;
};

#endif