#include <vector>
#include <queue>
#include "../include/Tree.h"
#include "../include/Session.h"
class Session;

using namespace std;

Tree::Tree(int rootLabel): node (rootLabel), children(vector<Tree*>()){};

void Tree:: clear(){
       for (unsigned int i=0; i<(children.size()); i++){
           delete children.at(i);
       }
children.clear();
}

//Destructor
Tree:: ~Tree (){ clear();}

void Tree:: copy (const Tree &other){ //vector<Tree*> other_children, const int &other_node){
    node=other.node;
    for (unsigned int i=0; i<other.children.size(); i++)
        children.push_back(other.children.at(i)->clone());
    }

//Copy Constructor
Tree::Tree (const Tree &other): node(),children(vector<Tree*>()){
      this->copy(other);
}

//Assignment Operator
Tree& Tree:: operator=(const Tree &other){
    if (this != &other){
        clear();
        copy(other);
    }
    return *this;
}

void Tree :: move (const Tree& other){
    node=other.node;
    children.resize(((unsigned int) other.children.size()));
    for( Tree* tree:other.children){
        children.push_back(tree);
    }
}

//Move Constructor
Tree:: Tree(Tree &&other): node(),children(vector<Tree*>()){
    this->move(other);
    other.clear();
}

//Move Assignment Operator
Tree& Tree:: operator=(Tree &&other){
    if(this != &other){
        this->clear();
        this->move(other);
        other.clear();

    }
    return *this;
}

void Tree:: addChild(const Tree& child){
       Tree* copy = child.clone();
        children.push_back(copy);
}

void Tree:: addChildPointer(Tree* child){
    children.push_back(child);
}

Tree* Tree :: createTree(const Session& session, int rootLabel) {
    if (session.getTreeType()==Cycle)
        return new CycleTree(rootLabel,session.getCycle());
    if (session.getTreeType()==MaxRank)
        return new MaxRankTree(rootLabel);
    else
        return new RootTree(rootLabel);
}

//getters
int Tree ::getNode()  const {return node;}
vector<Tree*> Tree :: getchildren () const {return children;}



CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){};
CycleTree::~CycleTree(){};

Tree* CycleTree::clone()const{
    Tree* tree= new CycleTree(this->node,this->currCycle);
    for (unsigned int i=0; i<this->getchildren().size(); i++){
        tree->addChild(*this->children[i]);
    }
    return tree;
}



 int CycleTree :: traceTree() {
     int cycle= currCycle;
     Tree* tree =clone();
     Tree* pointer=tree;
     while( (cycle>0) & ((unsigned int)tree->getchildren().size()!=0)) {
        cycle--;
        tree=tree->getchildren()[0];
     }
     int output=tree->getNode();
     delete pointer;
     return output;
}

MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel){};
MaxRankTree::~MaxRankTree(){};

Tree* MaxRankTree::clone()const {
        Tree *tree = new MaxRankTree(this->node);
        for (unsigned int i = 0; i < this->getchildren().size(); i++) {
            tree->addChild(*this->children[i]);
        }
        return tree;
}

int MaxRankTree:: traceTree() {
    queue<Tree *> queue;
    Tree *tree = clone();
    Tree* pointer=tree;
    int maxRank = (int)children.size();
    queue.push(tree);
    while (!queue.empty()) {
        Tree *currentTree = queue.front();
        queue.pop();
        for (unsigned int i = 0; i < currentTree->getchildren().size(); i++)
            queue.push(currentTree->getchildren()[i]);
        if ((int)currentTree->getchildren().size() > maxRank) {
            tree = currentTree;
            maxRank = currentTree->getchildren().size();
        }
    }
    int output= tree->getNode();
    //delete tree;
    delete pointer;
    return output;

}

RootTree::RootTree(int rootLabel):Tree(rootLabel){};
RootTree::~RootTree() {};

Tree* RootTree::clone()const{
        Tree* tree= new RootTree(this->node);
        for (unsigned int i=0; i<this->getchildren().size(); i++){
            tree->addChild(*this->children[i]);
        }
        return tree;
}

     int RootTree:: traceTree(){
        return getNode();
    }
