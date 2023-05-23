#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"
#include "Graph.h"
#include <queue>

class Session;  ///

class Tree{     //

protected:
    //Fields:
    int node;           //
    vector<Tree*> children;     //

public:
    Tree();
    //constructor
    Tree(int rootLabel);        //
    //copy constructor
    Tree(const Tree &other);
    //copy assignment operator
    const Tree& operator=(const Tree &other);
    // move constructor
    Tree(Tree &&other);
    //move assignment operator
    const Tree& operator=(Tree &&other);
    //Destructor
    virtual ~Tree();

    int getChildrenSize() {
        return children.size();
    }

    void addChild(const Tree& child);       //

    void addChild(Tree* child);

    void bfsTree(const Session& session);

    const vector<Tree*>& getChildren() const;

    int getNode() const;

    static Tree* createTree(const Session& session, int rootLabel);     //

    virtual int traceTree()=0;          //

    virtual Tree* clone() const = 0;

};

class CycleTree: public Tree{

private:
    int currCycle;       //

public:

    CycleTree();
    //constructor
    CycleTree(int rootLabel, int currCycle);         ///
    //copy constructor
    CycleTree(const CycleTree &other);
    //copy assignment operator
    const CycleTree& operator=(const CycleTree &other);
    //move constructor
    CycleTree(CycleTree &&other);
    //move assignment operator
    const CycleTree& operator=(CycleTree &&other);

    virtual int traceTree();        //

    virtual Tree* clone() const;

};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);         //

    virtual int traceTree();        //

    virtual Tree* clone() const;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);        //

    virtual int traceTree();        //

    virtual Tree* clone() const;
};



#endif
