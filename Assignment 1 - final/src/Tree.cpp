#include "Tree.h"
#include <queue>
using namespace std;


//Tree

Tree::Tree():node(),children(vector<Tree*>()){}

//constructor
Tree::Tree(int rootLabel):node(rootLabel),children(vector<Tree*>()){}

//Copy constructor
Tree::Tree(const Tree &other):node(other.node),children(vector<Tree*>()){
    for(auto j : other.children){
        children.push_back((*j).clone());
    }
}

//Copy assignment operator
const Tree& Tree:: operator=(const Tree &other){
    if(this != &other){
        node = other.node;
        for(auto & child : children){
            if (child){
                delete child;
                child = nullptr;
            }
        }
        children = vector<Tree*>(other.children.size());
        for(unsigned int i=0; i < other.children.size();i=i+1){
            *children[i]= *other.children[i];
        }
    }
    return *this;
}

//Move constructor
Tree::Tree(Tree &&other):node(other.node) ,children(other.children) {
    for(auto &child : other.children){
        child = nullptr;
    }
}


//Move assignment operator
const Tree& Tree:: operator=(Tree &&other){
    if (this != &other){
        node = other.node;
        for(auto & child : children){
            if (child){
                delete child;
                child = nullptr;
            }
        }
        children = other.children;
        for(auto & children : other.children){
            children = nullptr;
        }
    }
    return *this;
}

//Destructor:
Tree:: ~Tree(){
    for(auto & child : children){
        if (child){
            delete child;
            child = nullptr;
        }
    }
}

int Tree::getNode() const{
    return node;
}


void Tree:: addChild(const Tree& child){
    Tree* tree = child.clone();
    children.push_back(tree);
}

void Tree:: addChild(Tree* child){
    children.push_back(child);
}

Tree* Tree::createTree(const Session& session, int rootLabel){
    if(session.getTreeType() == Root)
    {
        return new RootTree(rootLabel);
    }
    else if(session.getTreeType() == MaxRank){
        return new MaxRankTree(rootLabel);
    }
    else {
        return new CycleTree(rootLabel, session.getCurrentCycle());
    }
}

const vector<Tree*> &Tree::getChildren() const {
    return children;
}

void Tree::bfsTree(const Session& session) {
    const vector<vector<int>> *graphEdges = &(session.getGraph().getEdges());
    queue<Tree*> bfsQueue;
    vector<char> visited = vector<char>((*graphEdges).size());
    for(unsigned int j=0; j< visited.size();j=j+1)   // will initial all the nodes with x
    {
        visited[j]= 'x';    // we didnt visit here yet
    }
    unsigned int i = 0;
    int counterForIntComparison=0;
    while(i < (*graphEdges).size())
    {
        if((counterForIntComparison != node) & ((*graphEdges)[node][i] == 1) ){
            visited[i] = 'v';  // we now visit this node
            Tree *tree = createTree(session, i);
            bfsQueue.push(tree);
            addChild(tree);
        }
        i=i+1;
        counterForIntComparison=counterForIntComparison+1;
    }

    visited[node] = 'f';  // we finished with this node
    while(bfsQueue.empty()==false){     // will continue until the queue is empty
        Tree *child = bfsQueue.front();
        bfsQueue.pop();
        if(visited[(child)->node] != 'f'){          // if haven't finished yet
            visited[child->node] = 'f';
            int counterForIntComparison2=0;
            for(unsigned int k = 0; k < (*graphEdges).size(); k=k+1 ){
                if((counterForIntComparison2 != child->node) & (visited[k] == 'x') & ((*graphEdges)[child->node][k] == 1)){
                    // will check if the node is my neighbour and we didnt  visit him yet
                    Tree* tree = createTree(session,k);
                    visited[k] = 'v';
                    bfsQueue.push(tree);
                    (*child).addChild(tree);
                }
                counterForIntComparison2++;
            }
        }
    }
}







// RootTree

RootTree:: RootTree(int rootLabel):Tree(rootLabel){}

Tree* RootTree::clone() const{
    return new RootTree(*this);
}

int RootTree::traceTree() {
    return node;
}

//CycleTree

CycleTree::CycleTree():Tree(),currCycle(0){}

//constructor:
CycleTree:: CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle) {}

//Copy constructor:
CycleTree:: CycleTree(const CycleTree &other): Tree(other), currCycle(other.currCycle) {}

//Copy assignment operator:
const CycleTree& CycleTree:: operator=(const CycleTree &other) {
    if(this != &other){
        Tree::operator=(other);
        currCycle = other.currCycle;
    }
    return *this;
}

//Move constructor:
CycleTree:: CycleTree(CycleTree &&other): Tree(other), currCycle(other.currCycle) {}

//Move assignment operator:
const CycleTree& CycleTree:: operator=(CycleTree &&other){
    if(this != &other){
        Tree::operator=(other);
        currCycle = other.currCycle;
    }
    return *this;
}

Tree* CycleTree::clone() const{
    return new CycleTree(*this);
}

int CycleTree::traceTree() {
    if((currCycle==0)| (children.empty()==true))
    {
        return node;
    }
    else{
        Tree* nextChild = children[0];
        int cycleCounter=1;
        while(cycleCounter<currCycle)  // will keep going until cycleCounter will get to the current number of iteration
        {
            if(((*nextChild).getChildren().empty())==true){  // if there is no more children
                return (*nextChild).getNode();
            }
            else{
                nextChild = (*nextChild).getChildren()[0];
            }
            cycleCounter=cycleCounter+1;
        }
        return (*nextChild).getNode();
    }
}


// MaxRankTre

MaxRankTree:: MaxRankTree(int rootLabel):Tree(rootLabel){}

Tree* MaxRankTree::clone() const{
    return new MaxRankTree(*this);
}



int MaxRankTree::traceTree() {
    queue<Tree *> queue;
    queue.push(this);

    int maxChildrenNode = -1;
    int resultNode=-1;

    while (queue.empty()==false) {
        Tree *curr = queue.front();
        queue.pop();
        if ((*curr).getChildrenSize() > maxChildrenNode) {
            maxChildrenNode = (*curr).getChildrenSize();
            resultNode = (*curr).getNode();
        }
        vector<Tree *> childVector = (*curr).getChildren();

        for (Tree *child : childVector) {
            queue.push(child);
        }
    }
    return resultNode;
}

