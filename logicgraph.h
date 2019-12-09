#ifndef UNDIRECRED_RAPH_LOGICGRAPH_H
#define UNDIRECRED_RAPH_LOGICGRAPH_H

#include <iostream>

using namespace std;

int **readSpecialMatrix(); //return specisal matrix adjacent
void printSpecialMatrix(int **adjlist);//print to screen matrix adjacent

struct Node {
    int field;
    struct list *next;
    struct list *prev;
};

class MyGraph {
private:
    int numvertex;
    Node **list;

    int checkSpecialMatrix(int **inputadjlist);

    bool isSimpleUndirectedGraph(int **inputadjlist);

public:
    MyGraph(int nv);

    ~MyGraph();

    bool readSpecialMatrix(int **inputadjlist);

    bool addAdjvertex(int invertex, int addvertext);

    void printGraph();

};


#endif //UNDIRECRED_RAPH_LOGICGRAPH_H
