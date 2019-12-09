#include "logicgraph.h"

int **readSpecialMatrix() {
    cout << "Please, input num of vertex:";
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

        if (nownumadj > 0) {
            cout << "please,adjacent vertices separated by spaces" << endl;
            for (int j = 0; j < nownumadj; j++) {
                cin >> adjlist[i][j + 1];
            }
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
    numvertex = nv;
    list = new Node *[nv];
}

MyGraph::~MyGraph() {
    delete[] list;

}

int MyGraph::checkSpecialMatrix(int **inputadjlist) {
    if (inputadjlist[0][0] != numvertex) { return 1; }

    for (int i = 1; i < numvertex + 1; i++) {
        int numadj = inputadjlist[i][0] + 1;

        if (numadj - 1 >= numvertex || numadj - 1 == 0) { return 2; }

        for (int j = 1; j < numadj; j++) {

            if (inputadjlist[i][j] == i) { return 3; }
            if (inputadjlist[i][j] > numvertex || inputadjlist[i][j] <= 0) { return 4; }

            for (int k = j + 1; k < numadj; k++) {
                if (inputadjlist[i][j] == inputadjlist[i][k]) { return 5; }
            }

        }
    }

    return 0;
}

bool MyGraph::isSimpleUndirectedGraph(int **inputadjlist) {
    bool **adjacencymatrix;
    bool flag = true;

    int nv = numvertex;
    adjacencymatrix = new bool *[nv];
    for (int i = 0; i < nv; i++) {
        adjacencymatrix[i] = new bool[nv];
    }

    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            adjacencymatrix[i][j] = false;
        }
    }

    for (int i = 1; i < inputadjlist[0][0] + 1; i++) {
        for (int j = 1; j < inputadjlist[i][0] + 1; j++) {
            int k = inputadjlist[i][j] - 1;
            adjacencymatrix[i - 1][k] = true;
        }
    }


/*    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            cout << adjacencymatrix[i][j] << " ";
        }
        cout << endl;
    }*/

    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            if (adjacencymatrix[i][j] != adjacencymatrix[j][i]) { return !flag; }
        }
    }

    for (int i = 0; i < nv; i++) {
        delete[] adjacencymatrix[i];
    }

    return flag;

}

bool MyGraph::readSpecialMatrix(int **inputadjlist) {
    bool flag = false;
    if (checkSpecialMatrix(inputadjlist) > 0) { return !flag; }
    if (!isSimpleUndirectedGraph(inputadjlist)) { return !flag; }

    return flag;
}

