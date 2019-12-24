
#include "logicgraph.h"

int main() {
    MyGraph myGraph;
/*    for (int i = 1; i <= 8; i++) {
        myGraph.addvertex(i);
    }


    for(int i=1; i<=6; i++){
        for(int j=1; j<=6; j++){
            myGraph.addarc(i,j);
        }
    }*/


    for (int i = 1; i <= 7; i++) {
        myGraph.addvertex(i);
    }
/*    myGraph.addarc(2, 5);
    myGraph.addarc(6, 5);
    myGraph.addarc(6, 1);
    myGraph.addarc(1, 3);
    myGraph.addarc(3, 4);
    myGraph.addarc(2, 4);*/

myGraph.addarc(1,2);
myGraph.addarc(1,3);
myGraph.addarc(2,4);
myGraph.addarc(2,3);
myGraph.addarc(4,3);
myGraph.addarc(4,5);
myGraph.addarc(6,5);
myGraph.addarc(7,5);
myGraph.addarc(7,6);
myGraph.addarc(2,5);
myGraph.addarc(3,5);

    myGraph.printGraph();

    myGraph.colors();

    return 0;
}