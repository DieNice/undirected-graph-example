#ifndef UNDIRECRED_RAPH_LOGICGRAPH_H
#define UNDIRECRED_RAPH_LOGICGRAPH_H

#include <iostream>

using namespace std;

int **readSpecialMatrix(); //return specisal matrix adjacent
void printSpecialMatrix(int **adjlist);//print to screen matrix adjacent

struct AdjVertex {
    int field;
    AdjVertex *next;
    AdjVertex *prev;

    AdjVertex(int v);

};

struct Vertex {
    AdjVertex *myadj;
    int field;
    Vertex *next;
    Vertex *prev;

    Vertex(int v);

};

class MyGraph {
private:
    int numvertex;
    Vertex *list;

    /*    my features*/
    int checkSpecialMatrix(int **inputadjlist);

    bool isSimpleUndirectedGraph(int **inputadjlist);

    /*    my features*/

public:
    MyGraph(int nv);

    ~MyGraph();

    bool readSpecialMatrix(int **inputadjlist);

    int addvertex(int v);

    int addarc(int b, int e);

    void printGraph();

};


#endif //UNDIRECRED_RAPH_LOGICGRAPH_H
