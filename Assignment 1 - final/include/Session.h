#ifndef SESSION_H_
#define SESSION_H_

#include <fstream>
#include <string>
#include "json.hpp"
#include "Graph.h"
#include <vector>
#include <queue>

using namespace std;
using json = nlohmann::json;


class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{

private:
    //fields
    Graph g;  //
    TreeType treeType;//
    vector<Agent*> agents;//
    std::queue<int> sickQueue;
    int currentCycle;

public:

    Session();
    //constructor
    Session(const std::string& path);
    //copy constructor
    Session(const Session& other);
    //copy assignment operator
    const Session& operator=(const Session &other);
    // move constructor
    Session(Session &&other);
    //move assignment operator
    const Session& operator=(Session &&other);
    //Destructor
    virtual ~Session();

    void simulate();       //

    void setGraph(const Graph& graph);

    void enqueueInfected(int);//

    int dequeueInfected();//

    void disconnectNode(int nodeToDisconnect );

    bool isInfected(int nodeIndex);

    void becomeInfected(int nodeIndex);

    void addAgent(const Agent& agent);//

    TreeType getTreeType() const;//

    const Graph& getGraph() const;

    int getCurrentCycle() const;

    void becomeSick(int nodeIndex);




};

#endif

