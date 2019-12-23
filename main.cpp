
#include "logicgraph.h"

int main() {
    MyGraph myGraph;

    for (int i = 0; i < 7; i++) {
        myGraph.addvertex(i);
    }
    myGraph.addarc(1, 3);
    myGraph.addarc(1, 2);
    myGraph.addarc(2, 5);
    myGraph.addarc(3, 4);
    myGraph.addarc(5, 6);
    myGraph.addarc(4, 6);


    int color = myGraph.colors(6);
    cout << "\nNum of colors=" << color << endl;
    myGraph.bfs(1);


    cout << myGraph;
    cout << "\nnum vertex=" << myGraph.getnumvertex();
    return 0;
}