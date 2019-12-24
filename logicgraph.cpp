#include <queue>
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
        if (nowv->next != nullptr) { nowv->next->prev = nowv->prev; }
    }
    numvertex--;
    delete nowv;
    return 0;
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

unsigned int getindex(unsigned int *m, unsigned int v) {
    int i = 0;
    while (m[i] != v) {
        i++;
    }
    return i;
}

int MyGraph::bfs(unsigned int u) {
    if (!vertexexistence(u)) { return 1; }
    bool *used = new bool[numvertex];
    unsigned int *vertexes = new unsigned int[numvertex];
    Vertex *nowv = list;
    for (int i = 0; i < numvertex; i++) {
        vertexes[i] = nowv->field;
        nowv = nowv->next;
    }
    cout << "\nBFS=";
    used[getindex(vertexes, u)] = true;
    cout << u << " ";

    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        unsigned int u = q.front();
        q.pop();
        AdjVertex *nowvadj = searchv(u)->myadj;
        while (nowvadj != nullptr) {
            unsigned int v = nowvadj->field;
            unsigned int index = getindex(vertexes, v);
            if (!used[index]) {
                used[index] = true;
                q.push(v);
                cout << v << " ";
            }
            nowvadj = nowvadj->next;
        }
    }
    delete[] vertexes;
    delete[] used;
    return 0;
}


int MyGraph::bfscolors(unsigned int u) {
    if (!vertexexistence(u)) { return -1; }
    bool *used = new bool[numvertex];
    unsigned int *clrs = new unsigned int[numvertex];
    unsigned int *vertexes = new unsigned int[numvertex];
    Vertex *nowv = list;
    for (int i = 0; i < numvertex; i++) {
        vertexes[i] = nowv->field;
        clrs[i] = 0;
        nowv = nowv->next;
    }
    clrs[getindex(vertexes, u)] = 1;
    used[getindex(vertexes, u)] = true;
    cout << "\nColors=" << u << "-1;";
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        unsigned int u = q.front();
        q.pop();
        AdjVertex *nowvadj = searchv(u)->myadj;
        while (nowvadj != nullptr) {
            unsigned int v = nowvadj->field;
            unsigned int index = getindex(vertexes, v);
            if (!used[index]) {
                used[index] = true;
                q.push(v);
                unsigned int minclr = 1;
                while (!clrisfree(v, vertexes, clrs, minclr)) {
                    minclr++;
                }
                clrs[index] = minclr;
                cout << v << "-" << minclr << ";";
            }
            nowvadj = nowvadj->next;
        }
    }

    unsigned int maxclr = clrs[0];
    for (int i = 1; i < numvertex; i++) {
        if (maxclr < clrs[i]) {
            maxclr = clrs[i];
        }
    }

    delete[] vertexes;
    delete[] clrs;
    delete[] used;
    return maxclr;
}

bool MyGraph::clrisfree(unsigned int v, unsigned int *vertexes, unsigned int *clrs, int clr) {
    AdjVertex *nowadjv = searchv(v)->myadj;
    bool flag = true;
    while (nowadjv != nullptr) {
        int index = getindex(vertexes, nowadjv->field);
        if (clrs[index] == clr) { return !flag; }
        nowadjv = nowadjv->next;
    }
    return flag;
}

int MyGraph::colors(unsigned u) {
    if (!vertexexistence(u)) { return -1; }
    bool *used = new bool[numvertex];
    unsigned int *clrs = new unsigned int[numvertex];
    unsigned int *vertexes = new unsigned int[numvertex];
    Vertex *nowv = list;
    for (int i = 0; i < numvertex; i++) {
        vertexes[i] = nowv->field;
        clrs[i] = 0;
        nowv = nowv->next;
    }
    clrs[getindex(vertexes, u)] = 1;
    used[getindex(vertexes, u)] = true;
    nowv = searchv(u);
    bool forward = true;
    bool stop = false;
    unsigned int maxclr = 1;
    while (!stop) {
        unsigned int v = nowv->field;
        unsigned int index = getindex(vertexes, v);
        if (!used[index]) {
            used[index] = true;
            unsigned int minclr = 1;
            while (!clrisfree(v, vertexes, clrs, minclr)) {
                minclr++;
            }
            clrs[index] = minclr;
            if (minclr > maxclr) { maxclr = minclr; }
        }

        if (forward == true && nowv->next != nullptr) { nowv = nowv->next; }
        else { forward = false; }

        if (forward == false && nowv->prev == nullptr) { stop = true; }
        if (forward == false && nowv->prev != nullptr) { nowv = nowv->prev; }
    }
    ///part2

    nowv = list;
    while (clrs[getindex(vertexes, nowv->field)] != maxclr) { nowv = nowv->next; }

    returncolor(nowv, vertexes, clrs, maxclr);

    nowv = list;
    cout << "\nColors=";
    int i = 0;
    while (nowv != nullptr) {
        cout << nowv->field << "-";
        cout << clrs[i] << ";";
        i++;
        nowv = nowv->next;
    }

    delete[] vertexes;
    delete[] clrs;
    delete[] used;
    return maxclr;
}

void MyGraph::returncolor(Vertex *v, unsigned int *vertexes, unsigned int *clrs, unsigned int maxclr) {
    unsigned int maxadj = 0;
    AdjVertex *nowadj = v->myadj;
    while (nowadj != nullptr) {
        if (nowadj->field > maxadj && nowadj->field < v->field) {
            maxadj = nowadj->field;
        }
        nowadj = nowadj->next;
    }
    if (maxadj == 0) { return; }
    int index = getindex(vertexes, maxadj);

    if (clrs[index] + 1 < maxclr) {
        clrs[index] = clrs[index] + 1;

        Vertex *nowv = list;
        while (nowv != nullptr) {
            if (nowv->field > maxadj) {
                unsigned int index = getindex(vertexes, nowv->field);
                unsigned int minclr = 1;
                while (!clrisfree(nowv->field, vertexes, clrs, minclr)) {
                    minclr++;
                }
                if (minclr >= maxclr) {
                    returncolor(searchv(nowv->field), vertexes, clrs, maxclr);
                }
                clrs[index] = minclr;
                if (searchv(nowv->field) == list) {
                    return;
                }
            }
            nowv = nowv->next;
        }


    } else {
        returncolor(searchv(maxadj), vertexes, clrs, maxclr);
    }
}