#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
using namespace std;

class Graph{
private:

    vector<vector<int>> edges; //

public:

    Graph();

    Graph(vector<std::vector<int>> matrix); //

    void infectNode(int nodeInd); //

    bool isInfected(int nodeInd); //

    const vector<vector<int>>& getEdges() const;

    void disconnect(int nodeToDisconnect );

    bool isSickNode(int nodeIndex) const;

    vector<int> getInfectedVector();

    void changeToSick(int nodeIndex);


};

#endif
