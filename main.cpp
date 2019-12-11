
#include "logicgraph.h"

int main() {
    MyGraph myGraph;

    for (int i = 0; i < 11; i++) {
        myGraph.addvertex(i);
    }
    myGraph.addarc(11, 7);
    myGraph.addarc(1, 77);
    myGraph.addarc(1, 7);
    myGraph.addarc(7, 7);


    myGraph.printGraph();
    cout << "\nnum vertex=" << myGraph.getnumvertex();
    return 0;
}