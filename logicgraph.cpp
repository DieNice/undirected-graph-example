#include "logicgraph.h"

int **readSpecialMatrix() {
    cout << "Please, input num of vertext:";
    int numvertex;
    cin >> numvertex;
    int **adjlist;
    adjlist = new int *[numvertex + 1];

    adjlist[0] = new int;
    adjlist[0][0] = numvertex;

    int nownumadj;
    for (int i = 1; i < numvertex + 1; i++) {
        cout << "please,input num adjacent vertex of vertex number " << i << ":";
        cin >> nownumadj;
        adjlist[i] = new int[nownumadj + 1];
        adjlist[i][0] = nownumadj;
        cout << "please,adjacent vertices separated by spaces" << endl;
        for (int j = 0; j < nownumadj; j++) {
            cin >> adjlist[i][j + 1];
        }
    }
    return adjlist;

}

void printSpecialMatrix(int **adjlist) {
    cout << "num of vertex=" << adjlist[0][0];
    for (int i = 1; i < adjlist[0][0] + 1; i++) {
        cout << "\nVertex numver:" << i << ":";
        for (int j = 0; j < adjlist[i][0]; j++) {
            cout << adjlist[i][j + 1] << " ";
        }
    }
}


/*--------------GRAPH-------------*/
MyGraph::MyGraph(int nv) {
    list = new Node *[nv];
}

MyGraph::~MyGraph() {
    for (int i = 0; i < numvertex; i++) {
        delete[] list[0];
    }
    delete[] list;
}

int MyGraph::checkSpecialMatrix(int **inputadjlist) {
    int answer = 0;


    return answer;
}