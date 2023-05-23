#include "Agent.h"
#include "Tree.h"
#include <vector>


//Agent
Agent:: Agent(){}

Agent:: ~Agent(){};


// Virus

Virus:: Virus(int nodeInd):Agent(),nodeInd(nodeInd){}

Virus:: Virus(const Virus& other):Agent(),nodeInd(other.nodeInd){}

Agent* Virus:: clone() const{
    return new Virus(*this);
}

void Virus:: act(Session& session){
    const Graph& g = session.getGraph();
    if((g.isSickNode(nodeInd))==false){  // check if the node is already sick or just got infected
        session.enqueueInfected(nodeInd);
        session.becomeSick(nodeInd);
    }
    bool virusFree = false;
    unsigned int i=0;  //counter for unsigned int comparison
    while( (virusFree==false) & (i<g.getEdges().size()) )       // will check all the neighbours of the infected node
        {
        if((g.getEdges()[nodeInd][i] == 1) & ((session.isInfected(i))==false))  // if the nodes connected and there is another virusFree node
        {
            session.becomeInfected(i);
            virusFree = true;
        }
        i=i+1;
    }
}


//ContactTracer
ContactTracer:: ContactTracer():Agent(){}

Agent* ContactTracer:: clone() const{
    return new ContactTracer(*this);
}

void ContactTracer:: act(Session& session){
    int rootNode = session.dequeueInfected();       // will take the first sick node from the queue
    if (rootNode != -1){
        Tree* tree = Tree::createTree(session,rootNode);
        (*tree).bfsTree(session);       // will create a tree from the rootNode
        int nodeToDisconnect = (*tree).traceTree();
        session.disconnectNode(nodeToDisconnect);
        delete tree;
    }
}



