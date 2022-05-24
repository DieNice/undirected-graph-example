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
/*    if (v == 0) { return 1; } //vertex is zero*/
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

unsigned int MyGraph::getindex(unsigned int v) {
    Vertex *nowv = list;
    int i = 0;
    while (nowv->field != v) {
        i++;
        nowv = nowv->next;
    }
    return i;
}

int MyGraph::bfs(unsigned int u) {
    if (!vertexexistence(u)) { return 1; }
    bool *used = new bool[numvertex];
    cout << "\nBFS=";
    used[getindex(u)] = true;
    cout << u << " ";

    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        unsigned int u = q.front();
        q.pop();
        AdjVertex *nowvadj = searchv(u)->myadj;
        while (nowvadj != nullptr) {
            unsigned int v = nowvadj->field;
            unsigned int index = getindex(v);
            if (!used[index]) {
                used[index] = true;
                q.push(v);
                cout << v << " ";
            }
            nowvadj = nowvadj->next;
        }
    }
    delete[] used;
    return 0;
}

bool MyGraph::clrisfree(unsigned int i, int *clrs, int clr) {
    bool flag = true;
    Vertex *v = list;
    for (int j = 0; j < i; j++) { v = v->next; }

    AdjVertex *nowadj = v->myadj;
    while (nowadj != nullptr) {
        int index = getindex(nowadj->field);
        if (clrs[index] == clr) { return false; }
        nowadj = nowadj->next;
    }
    return flag;
}

int MyGraph::getmaxcolor(int *clrs) {
    int max = clrs[0];
    for (int i = 1; i < numvertex; i++) {
        if (clrs[i] > max) { max = clrs[i]; }
    }
    return max;
}

bool MyGraph::isbadColors(int *clrs) {
    bool result = false;
    for (int i = 0; i < numvertex; i++) {
        if (clrs[i] < 0) {
            result = true;
            break;
        }
    }
    return result;
}

void MyGraph::colors() {
    int *clrs = new int[numvertex];
    for (int i = 0; i < numvertex; i++) { clrs[i] = -1; } //обнуляем раскраски
    for (int i = 0; i < numvertex; i++) {
        int minclr = 0;
        while (!clrisfree(i, clrs, minclr)) { minclr++; }
        clrs[i] = minclr;
    }
    int q = getmaxcolor(clrs); //находим макс цвет
    int *subclrs = new int[numvertex]; //доп. массив если расскраски не удались
    for (int i = 0; i < numvertex; i++) { subclrs[i] = clrs[i]; }
    bool flag = false;
    while (!flag) {
        unsigned int Xq = 0;
        while (subclrs[Xq] != q) { Xq++; } //находим Xk*
        returncolor(Xq, subclrs, q);
        int nowclr = getmaxcolor(subclrs);
        if (nowclr < q && !isbadColors(subclrs)) {
            for (int j = 0; j < numvertex; j++) { clrs[j] = subclrs[j]; }
            q = nowclr;
        } else { flag = true; }

    }

    cout << "\nColors" << endl;
    Vertex *nowv = list;
    for (int i = 0; i < numvertex; i++) {
        cout << nowv->field << " ";
        nowv = nowv->next;
    }
    cout << endl;
    for (int i = 0; i < numvertex; i++) { cout << clrs[i] + 1 << " "; }
    delete[] clrs;
}

void MyGraph::returncolor(unsigned int i, int *clrs, unsigned int maxclr) {
    //находим смежную вершину с максимальным номером, меньше номера вершины (i) Xk
    Vertex *v = list;
    for (int j = 0; j < i; j++) { v = v->next; }
    AdjVertex *nowadj = v->myadj;
    int maxadj = -1;
    while (nowadj != nullptr) {
        int index = getindex(nowadj->field);
        if (index > maxadj && index < i) { maxadj = index; }
        nowadj = nowadj->next;
    }
    if (maxadj < 0) { return; }
    //пытаемся перекрасить в цвет больший собственного, но меньше чем макс-й
    //обнуляем расскраски вершин больше Xk
    for (int j = maxadj + 1; j < numvertex; j++) { clrs[j] = -1; }
    int Jk = clrs[maxadj] + 1;
    while (!clrisfree(maxadj, clrs, Jk)) { Jk++; }
    if (Jk < maxclr) {
        clrs[maxadj] = Jk;
        //перекрашиваем смежные вершины номером больше v
        //раскрашиваем
        int k;
        for (k = maxadj + 1; k < numvertex; k++) {
            int minclr = 0;
            while (!clrisfree(k, clrs, minclr)) { minclr++; }
            if (minclr == maxclr) {
                returncolor(k, clrs, maxclr);
                break;
            } else { clrs[k] = minclr; }
        }
    } else { returncolor(maxadj, clrs, maxclr); }
}