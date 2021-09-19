
#include "../include/Agent.h"


using namespace std;

Agent::Agent()=default;
Agent::~Agent(){};

ContactTracer::ContactTracer(): Agent(){};
ContactTracer:: ~ContactTracer(){};
Agent* ContactTracer:: clone()const{
    return new ContactTracer(*this);
}

void ContactTracer:: act(Session& session){
    int vertex= session.dequeueInfected();
    if(vertex!=-1){
        Tree *tempTree=session.getG().bfs(vertex,session);
        int isolated=tempTree->traceTree();
        session.getGPointer()->disconnectV(isolated);
        delete tempTree;
    }
}

Virus:: Virus(int nodeInd):Agent(), nodeInd(nodeInd) {};
Virus:: ~Virus(){};
Agent* Virus::  clone() const{
    return new Virus(*this);
}

void Virus :: act(Session& session){
    if (!session.getG().isInfected(nodeInd)) {
        session.getGPointer()->infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    int node= session.getG().smallestN(nodeInd);
    if (node!=-1){
        const Agent &a= Virus (node); 
        session.addAgent(a);
        session.getGPointer()->setCarry(node);
    }

}
int Virus::getnodeInd() const {
    return nodeInd;
}


