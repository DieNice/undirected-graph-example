
#include "logicgraph.h"

int main() {
    MyGraph myGraph;

    int N = 7;

    for (int i = 1; i < N; i++) {
        myGraph.addvertex(N - i);
    }

    //6 тест
/*    myGraph.addarc(1, 3);
    myGraph.addarc(1, 2);
    myGraph.addarc(2, 3);
    myGraph.addarc(3, 5);
    myGraph.addarc(5, 4);
    myGraph.addarc(4, 2);
    myGraph.addarc(4, 6);
    myGraph.addarc(5, 6);
    myGraph.addarc(2, 6);
    myGraph.addarc(3, 6);
    myGraph.addarc(6, 7);
    myGraph.addarc(7, 8);
    myGraph.addarc(7, 9);
    myGraph.addarc(8, 9);*/
    //5 тест
/*      myGraph.addarc(1,3);
      myGraph.addarc(3,5);
      myGraph.addarc(5,4);
      myGraph.addarc(4,2);
      myGraph.addarc(2,1);

      myGraph.addarc(7,9);
      myGraph.addarc(9,6);
      myGraph.addarc(6,8);
      myGraph.addarc(8,10);
      myGraph.addarc(10,7);

      myGraph.addarc(1,7);
      myGraph.addarc(3,8);
      myGraph.addarc(5,9);
      myGraph.addarc(4,10);
      myGraph.addarc(2,6);*/



//4 тест
/*
       myGraph.addarc(1, 8);
       myGraph.addarc(8, 2);
       myGraph.addarc(2, 3);
       myGraph.addarc(3, 7);
       myGraph.addarc(7, 6);
       myGraph.addarc(6, 5);
       myGraph.addarc(5, 4);
       myGraph.addarc(4, 1);

       myGraph.addarc(1, 3);
       myGraph.addarc(1, 6);
       myGraph.addarc(3, 6);
       myGraph.addarc(5, 2);
       myGraph.addarc(5, 7);
       myGraph.addarc(2, 7);
*/



// 3 тест
    myGraph.addarc(1, 5);
    myGraph.addarc(5, 2);
    myGraph.addarc(2, 6);
    myGraph.addarc(6, 3);
    myGraph.addarc(3, 4);
    myGraph.addarc(4, 1);
    myGraph.addarc(4, 5);
    myGraph.addarc(4, 6);
    myGraph.addarc(5, 6);

    //2тест+
/*    myGraph.addarc(1, 4);
    myGraph.addarc(4, 2);
    myGraph.addarc(2, 3);
    myGraph.addarc(3, 5);
    myGraph.addarc(5, 6);
    myGraph.addarc(6, 1);
    myGraph.addarc(6, 4);
    myGraph.addarc(5, 2);
    myGraph.addarc(6, 3);*/


    //* 1 граф+
/*    myGraph.addarc(1, 3);
    myGraph.addarc(3, 4);
    myGraph.addarc(4, 2);
    myGraph.addarc(2, 7);
    myGraph.addarc(7, 6);
    myGraph.addarc(6, 5);
    myGraph.addarc(5, 8);
    myGraph.addarc(8, 1);*/


    myGraph.printGraph();

    myGraph.colors();


    return 0;
}