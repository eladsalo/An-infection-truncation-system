#include "Agent.h"
#include <vector>
#include "Session.h"
#include <queue>

Session::Session():g(),treeType(Root),agents(vector<Agent*>()),sickQueue(queue<int>()),currentCycle(0){
}

//constructor
Session::Session(const std::string& path):g(vector<vector<int>>()),treeType(Root),agents(vector<Agent*>()),sickQueue(queue<int>()),currentCycle(0){

    ifstream i(path);
    json j;
    i >> j;

    g=Graph(j["graph"]);

    for (auto& agent: j["agents"]){
        if(agent[0] == "C"){
            Agent* cT= new ContactTracer();  // create a new contact tracer
            agents.push_back(cT);
        }
        else{
            Agent* v = new Virus(agent[1]);  // create a new virus
            agents.push_back(v);
            g.infectNode(agent[1]);
        }
    }

    if (j["tree"] == "C"){
        treeType = Cycle;
    }
    else if (j["tree"] == "M"){
        treeType = MaxRank;
    }
    else if (j["tree"] == "R"){
        treeType = Root;
    }


}


//copy constructor
Session::Session(const Session& other):
        g(other.g),treeType(other.treeType),agents(vector<Agent*>()),sickQueue(other.sickQueue),currentCycle(other.currentCycle){
    for (auto agent : other.agents){
        agents.push_back((*agent).clone());
    }
}

//move constructor
Session::Session(Session &&other):
        g(other.g),treeType(other.treeType),agents(),sickQueue(other.sickQueue),currentCycle(other.currentCycle){
    for (auto &agent:other.agents) {
        agents.push_back(agent);
        agent = nullptr;
    }
}

//copy assignment operator
const Session& Session:: operator=(const Session &other){
    if(this != &other){
        treeType = other.treeType;
        currentCycle = other.currentCycle;
        sickQueue = other.sickQueue;
        g = other.g;

        for(auto & agent : agents){
            if (agent){
                delete agent;
                agent = nullptr;
            }
        }
        for (const auto agent: other.agents) {
            agents.push_back((*agent).clone());
        }
    }

    return *this;
}

//move assignment operator
const Session& Session:: operator=(Session &&other){
    if (this != &other){
        treeType = other.treeType;
        g = other.g;
        sickQueue = other.sickQueue;
        currentCycle = other.currentCycle;

        for(auto & agent : agents){
            if (agent){
                delete agent;
                agent = nullptr;
            }
        }
        agents = other.agents;
        for(auto & agent : other.agents){
            agent = nullptr;
        }
    }
    return *this;
}

// Destructor
Session::~Session() {
    for (auto &agent : agents) {
        if (agent) {
            delete agent;
            agent = nullptr;
        }
    }
}

void Session::simulate(){
    int AgentsSize;
    int newAgentsSize;
    bool finished = false;
    while(finished==false){
        AgentsSize = agents.size();
        for(int i = 0; i < AgentsSize; ++i){   // will go over every agent in the current iteration
            (*agents[i]).act(*this);
        }
        newAgentsSize = agents.size();
        currentCycle=currentCycle+1;
        if(AgentsSize == newAgentsSize)    // if there is no new virus in the agents list, so its mean the virus finished to spread and we finished
            finished=true;
    }
    json j;
    vector<int> v = g.getInfectedVector();
    j["infected"] = v;
    j["graph"] = g.getEdges();
    ofstream o("output.json");
    o << j;
}

void Session:: setGraph(const Graph& otherGraph){
    g = otherGraph;
}

void Session:: enqueueInfected(int nodeIndex){
    sickQueue.push(nodeIndex);
}

int Session::dequeueInfected() {
    if (sickQueue.empty()){
        return -1;
    }
    int result = sickQueue.front();
    sickQueue.pop();
    return result;
}

void Session::disconnectNode(int nodeToDisconnect) {
    g.disconnect(nodeToDisconnect);
}

bool Session::isInfected(int nodeIndex){
    return g.isInfected(nodeIndex);

}

void Session::becomeInfected(int nodeIndex) {
    g.infectNode(nodeIndex);
    Virus v(nodeIndex);
    addAgent(v);
}

void Session:: addAgent(const Agent& agent){
    agents.push_back(agent.clone());
}

TreeType Session::getTreeType() const {
    return treeType;
}

const Graph& Session::getGraph() const {
    return g;
}

int Session::getCurrentCycle() const {
    return currentCycle;
}

void Session::becomeSick(int nodeIndex){
    g.changeToSick(nodeIndex);
}

