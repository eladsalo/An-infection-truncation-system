#include "Graph.h"
using namespace std;

Graph::Graph():edges(vector<vector<int>>()){}

Graph::Graph(vector<vector<int>> matrix):edges(matrix){}

void Graph::infectNode(int nodeInd){
    edges[nodeInd][nodeInd] = 1;
}

bool Graph::isInfected(int nodeInd){
    return ((edges[nodeInd][nodeInd] == 1) | (edges[nodeInd][nodeInd] ==2));
}

const vector<vector<int>>& Graph::getEdges() const {
    return edges;
}

void Graph::disconnect(int nodeToDisconnect) {
     for(unsigned int i = 0; i < edges.size(); ++i){
         int counterForIntComparison=i;
         if(counterForIntComparison != nodeToDisconnect)
         {
             edges[nodeToDisconnect][i] =0;
             edges[i][nodeToDisconnect] = 0;
         }
     }
}


bool Graph::isSickNode(int nodeIndex) const{
     if(edges[nodeIndex][nodeIndex] == 2)
        return true;
        else
            return false;
}


vector<int> Graph::getInfectedVector() {
    vector<int> result = vector<int>();
    for (unsigned int j = 0; j < edges.size(); j = j + 1) {
        if (edges[j][j] != 0) {
            result.push_back(j);
            edges[j][j] = 0;
        }
    }
    return result;
}

void Graph::changeToSick(int nodeIndex) {
    edges[nodeIndex][nodeIndex] = 2;
}






