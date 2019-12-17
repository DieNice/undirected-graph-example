#ifndef UNDIRECRED_RAPH_LOGICGRAPH_H
#define UNDIRECRED_RAPH_LOGICGRAPH_H

#include <iostream>

using namespace std;

int **readSpecialMatrix(); //return specisal matrix adjacent
void printSpecialMatrix(int **adjlist);//print to screen matrix adjacent

struct AdjVertex {
    unsigned int field;
    AdjVertex *next;
    AdjVertex *prev;

    AdjVertex(unsigned int v);

};

struct Vertex {
    AdjVertex *myadj;
    unsigned int field;
    Vertex *next;
    Vertex *prev;

    Vertex(unsigned int v);

};

class MyGraph {
private:
    unsigned int numvertex;
    Vertex *list;

    /*    my features*/
    int checkSpecialMatrix(int **inputadjlist);

    bool isSimpleUndirectedGraph(int **inputadjlist);

    /*    my features*/

    bool vertexexistence(unsigned int v);

    bool acrexistence(unsigned int b, unsigned int e);

    void addadjv(Vertex *v, unsigned int av);

    void deladjv(Vertex *v, unsigned int av);


public:
    MyGraph();

    ~MyGraph();

    unsigned int getnumvertex();

    bool readSpecialMatrix(int **inputadjlist);

    int addvertex(unsigned int v);

    int addarc(unsigned int b, unsigned int e);

    int delvertex(unsigned int v);

    int delarc(unsigned int b, unsigned int e);

    void printGraph();

    friend std::ostream &operator<<(std::ostream &out, const MyGraph &obj);

};


#endif //UNDIRECRED_RAPH_LOGICGRAPH_H
