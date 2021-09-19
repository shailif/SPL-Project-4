#ifndef TREE_H_
#define TREE_H_
#include <vector> 

class Session;

class Tree{
public:
    //constructor
    Tree(int rootLabel);

    void clear();
    //Destructor
    virtual ~Tree ();
    void copy( const Tree &other) ;
    //Copy Constructor
    Tree(const Tree &other);

    //Assignment Operator
    Tree& operator=(const Tree &other);

    void move(const Tree &other);
    //Move Constructor
    Tree (Tree &&other);

    //Move Assignment Operator
    Tree& operator=(Tree &&other);

    void addChild(const Tree& child);
    void addChildPointer(Tree* child);
    static Tree* createTree(const Session& session, int rootLabel);
    int getNode() const  ;
    std::vector<Tree*> getchildren () const ;
    virtual int traceTree()=0;
    virtual Tree* clone () const = 0;


protected:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual ~CycleTree();
    Tree*  clone()const ;
    virtual int traceTree();


private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual ~MaxRankTree();
    Tree*  clone()const ;
    virtual int traceTree();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual ~RootTree();
    Tree*  clone()const ;
    virtual int traceTree();
};

#endif
