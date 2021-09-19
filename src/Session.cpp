#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <iostream>
#include "../include/Graph.h"
#include "../include/Session.h"
#include "../include/Agent.h"
#include "../include/json.hpp"

using namespace std;
using json= nlohmann::json;

Session::Session(const std::string& path):  g(vector<vector<int>>()), treeType(), agents(),queueInfected(), cycle(0) {
    std::ifstream temp(path);
    json j = json::parse(temp);
    g=Graph (j["graph"]);
    if (j["tree"]=="C")
        treeType=Cycle;
    else if (j["tree"]=="M")
        treeType= MaxRank;
    else
        treeType=Root;
    for(auto& item :j["agents"]) {
        if (item[0] == "V") {
            Virus *newVirus = new Virus(item[1]);
            agents.push_back(newVirus);
        } else {
            ContactTracer* newCt =new ContactTracer();
            agents.push_back(newCt);
        }
    }
}

void Session:: clear() {
    for (unsigned int i = 0; i < agents.size(); i++) {
        delete agents.at(i);
    }
    agents.clear();

    while (!queueInfected.empty())
        queueInfected.pop();
}



//Destructor
Session :: ~Session (){clear(); }

void Session :: copy (const Session &other){
    for(unsigned int i=0; other.agents.size() ; i++) {
        agents.push_back(other.agents.at(i)->clone());
        g=other.g;
    }
    queueInfected=other.queueInfected;
}

//Copy Constructor
Session:: Session (const Session &other): g(vector<vector<int>>()), treeType(other.treeType), agents() , queueInfected(), cycle(other.cycle){
    this->copy(other);
}

//Assignment Operator
Session& Session:: operator=(const Session &other){
    if (this != &other){
        clear();
        copy(other);
    }
    return *this;
}


void Session :: move (const Session& other){
    getG().getEdges().resize((other.getG().getEdges().size()));
    for (unsigned int i=0; i<other.getG().getEdges().size(); i++)
        (getG().getEdges().at(i))=(other.getG().getEdges().at(i));

    for( Agent* agent:other.agents){
        agents.push_back(agent);
    }
}

//Move Constructor
Session ::Session (Session &&other) :g(vector<vector<int>>()), treeType(other.treeType), agents() , queueInfected(other.queueInfected), cycle(other.cycle){
    this->move(other);
    other.clear();
}

//Move Assignment Operator
Session& Session :: operator=(Session &&other) {
    if (this != &other) {
        this->clear();
        this->move(other);
        other.clear();
    }
    return *this;
}
void Session :: simulate(){
    unsigned int currsize = (unsigned int) agents.size();
    bool finish=false;
    while (!finish) {
        for (unsigned int i = 0; i <currsize; i++) {
            agents[i]->act(*this);
        }
        cycle++;
        if((unsigned int)agents.size()==currsize)
            finish=true;
        else
            currsize=(unsigned int)agents.size();
    }
    vector <int> list;
    for (unsigned int i=0; i<g.getA().size(); i++){
        if (g.getA()[i]==1)
            list.push_back(i);
    }

    json output;
    output["graph"]=g.getEdges();
    output["infected"]=list;
    ofstream i("./output.json");
    i <<output;

}

void Session :: addAgent(const Agent& agent) {
    Agent* newAgent= agent.clone();
    agents.push_back(newAgent);
}
void Session ::setGraph(const Graph& graph) {
    g = graph;
}


void Session :: enqueueInfected(int vertex) {
    queueInfected.push(vertex);
}

int Session :: dequeueInfected() {
    if (!queueInfected.empty()) {
        int out = queueInfected.front();
        queueInfected.pop();
        return out;
    }
    return -1;
};

//getters
Graph Session ::getG() const {return g;};
Graph* Session::getGPointer(){ return &g; };
TreeType Session ::getTreeType() const{return treeType;};
std::vector<Agent*> Session ::getAgents()const{return agents;};
int Session :: getCycle () const{return cycle;};
