#include "logicgraph.h"

/*list of lists*/
Vertex::Vertex(unsigned int v) {
    field = v;
    myadj = nullptr;
    next = nullptr;
    prev = nullptr;

}

AdjVertex::AdjVertex(unsigned int v) {
    field = v;
    next = nullptr;
    prev = nullptr;
}

/*list of lists*/

/*    my features*/
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

int MyGraph::checkSpecialMatrix(int **inputadjlist) {

    unsigned int nv = inputadjlist[0][0];

    for (int i = 1; i < nv + 1; i++) {
        int numadj = inputadjlist[i][0] + 1;

        if (numadj - 1 >= nv || numadj - 1 == 0) { return 1; }

        for (int j = 1; j < numadj; j++) {

            if (inputadjlist[i][j] == i) { return 2; }
            if (inputadjlist[i][j] > nv || inputadjlist[i][j] <= 0) { return 3; }

            for (int k = j + 1; k < numadj; k++) {
                if (inputadjlist[i][j] == inputadjlist[i][k]) { return 4; }
            }

        }
    }

    return 0;
}

bool MyGraph::isSimpleUndirectedGraph(int **inputadjlist) {
    bool **adjacencymatrix;
    bool flag = true;

    int nv = inputadjlist[0][0];
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

    numvertex = inputadjlist[0][0];

    for (int i = 1; i < inputadjlist[0][0] + 1; i++) {
        if (list == nullptr) {
            list = new Vertex(i);
        } else {
            Vertex *newvertex = new Vertex(i);
            list->prev = newvertex;
            newvertex->next = list;
            list = newvertex;

        }
        for (int j = 1; j < inputadjlist[i][0] + 1; j++) {
            AdjVertex *newadjv = new AdjVertex(inputadjlist[i][j]);
            if (list->myadj == nullptr) {
                list->myadj = newadjv;
            } else {
                list->myadj->prev = newadjv;
                newadjv->next = list->myadj;
                list->myadj = newadjv;
            }
        }

    }

    return flag;
}

/*    my features*/

/*--------------GRAPH-------------*/
MyGraph::MyGraph() {
    numvertex = 0;
    list = nullptr;
}

MyGraph::~MyGraph() {
    delete list;
}


void MyGraph::printGraph() {
    if (list == nullptr) {
        cout << "Graph is empty" << endl;
    } else {
        Vertex *nowv = list;
        AdjVertex *nowadj;
        while (nowv != nullptr) {
            cout << "\n" << nowv->field << "<-";
            nowadj = nowv->myadj;
            while (nowadj != nullptr) {
                cout << nowadj->field << ",";
                nowadj = nowadj->next;
            }
            nowv = nowv->next;
        }

    }
}

int MyGraph::addvertex(unsigned int v) {
    if (v == 0) { return 1; } //vertex is zero
    if (list == nullptr) {
        Vertex *newvertex = new Vertex(v);
        list = newvertex;
        numvertex++;
        return 0;
    } else {
        if (vertexexistence(v)) { return 2; }
        Vertex *newvertex = new Vertex(v);
        list->prev = newvertex;
        newvertex->next = list;
        list = newvertex;
        numvertex++;
        return 0;
    }
}

bool MyGraph::vertexexistence(unsigned int v) {
    Vertex *nowv = list;
    bool flag = false;
    while (flag != true && nowv != nullptr) {
        if (nowv->field == v) { flag = !flag; }
        nowv = nowv->next;
    }
    return flag;
}

unsigned int MyGraph::getnumvertex() {
    return numvertex;
}

int MyGraph::addarc(unsigned int b, unsigned int e) {
    if (!vertexexistence(b)) { return 1; }
    if (!vertexexistence(e)) { return 2; }
    if (acrexistence(e, b)) { return 3; }
    if (b == e) { return 4; }
    Vertex *v1 = searchv(b);
    Vertex *v2 = searchv(e);
    addadjv(v1, e);
    addadjv(v2, b);
    return 0;
}

void MyGraph::addadjv(Vertex *v, unsigned int av) {
    AdjVertex *newadjv = new AdjVertex(av);
    if (v->myadj == nullptr) {

        v->myadj = newadjv;
    } else {
        v->myadj->prev = newadjv;
        newadjv->next = v->myadj;
        v->myadj = newadjv;
    }
}

bool MyGraph::acrexistence(unsigned int b, unsigned int e) {
    bool flag = false;
    Vertex *v1 = list;
    Vertex *v2 = list;
    Vertex *nowv = list;
    while (v1->field != b || v2->field != e) {
        if (nowv->field == b) { v1 = nowv; }
        if (nowv->field == e) { v2 = nowv; }
        nowv = nowv->next;
    }

    AdjVertex *nowad = v1->myadj;
    while (flag != true && nowad != nullptr) {
        if (nowad->field == e) {
            flag = true;
        }
        nowad = nowad->next;
    }
    nowad = v2->myadj;
    while (flag != true && nowad != nullptr) {
        if (nowad->field == b) {
            flag = true;
        }
        nowad = nowad->next;
    }

    return flag;
}

std::ostream &operator<<(std::ostream &out, const MyGraph &obj) {
    if (obj.list == nullptr) {
        out << "Graph is empty" << endl;
    } else {
        Vertex *nowv = obj.list;
        AdjVertex *nowadj;
        while (nowv != nullptr) {
            out << "\n" << nowv->field << "<-";
            nowadj = nowv->myadj;
            while (nowadj != nullptr) {
                out << nowadj->field << ",";
                nowadj = nowadj->next;
            }
            nowv = nowv->next;
        }

    }
    return out;
}

int MyGraph::delvertex(unsigned int v) {
    if (list == nullptr) { return 1; }
    if (!vertexexistence(v)) { return 2; }
    Vertex *nowv = searchv(v);
    while (nowv->myadj != nullptr) {
        delarc(v, nowv->myadj->field);
    }

    if (nowv->prev == nullptr) {
        list = nowv->next;
        if (list != nullptr) { list->prev = nullptr; }
    } else {
        nowv->prev->next = nowv->next;
        if (nowv->next != nullptr) { nowv->next->prev = nowv->prev->next; }
    }
    delete nowv;
}

int MyGraph::delarc(unsigned int b, unsigned int e) {
    if (!vertexexistence(b)) { return 1; }
    if (!vertexexistence(e)) { return 2; }
    if (!acrexistence(e, b)) { return 3; }
    if (b == e) { return 4; }
    Vertex *v1 = searchv(b);
    Vertex *v2 = searchv(e);
    deladjv(v1, e);
    deladjv(v2, b);
    return 0;
}

void MyGraph::deladjv(Vertex *v, unsigned int av) {
    AdjVertex *fordel = searchadjv(v, av);
    if (fordel->prev == nullptr) {
        v->myadj = fordel->next;
        if (v->myadj != nullptr) { v->myadj->prev = nullptr; }
    } else {
        fordel->prev->next = fordel->next;
        if (fordel->next != nullptr) { fordel->next->prev = fordel->prev; }
    }
    delete[] fordel;
}

Vertex *MyGraph::searchv(unsigned int v) {
    Vertex *nowv = list;
    while (nowv->field != v && nowv != nullptr) {
        nowv = nowv->next;
    }
    return nowv;
}

AdjVertex *MyGraph::searchadjv(Vertex *v, unsigned int adjv) {
    AdjVertex *nowadjv = v->myadj;
    while (nowadjv->field != adjv && nowadjv != nullptr) {
        nowadjv = nowadjv->next;
    }
    return nowadjv;
}