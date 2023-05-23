#ifndef AGENT_H_
#define AGENT_H_

#include "Session.h"
#include <vector>

class Agent{
public:
    Agent();   //

    virtual ~Agent();

    virtual void act(Session& session)=0;           //

    virtual Agent* clone() const = 0;

};

class Virus: public Agent{

private:
    const int nodeInd;          //

public:
    Virus(int nodeInd);     //

    Virus(const Virus& other);

    virtual void act(Session& session);     //

    virtual Agent* clone() const;


};

class ContactTracer: public Agent{
public:
    ContactTracer();        //

    virtual Agent* clone() const;

    virtual void act(Session& session);         //
};

#endif
