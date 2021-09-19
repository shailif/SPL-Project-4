
#ifndef AGENT_H_
#define AGENT_H_


#include "../include/Session.h"
#include "../include/Tree.h"

class Agent{
public:
    Agent();
    virtual ~Agent();
    virtual Agent* clone() const=0;
    virtual void act(Session& session)=0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual ~ContactTracer();
    virtual Agent* clone() const;
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual ~Virus();
    virtual Agent* clone() const;
    virtual void act(Session& session);
    int getnodeInd()const;
private:
    const int nodeInd;
};

#endif


