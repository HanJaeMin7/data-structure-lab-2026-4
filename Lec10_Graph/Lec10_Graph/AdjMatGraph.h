#pragma once
#include <stdio.h>
#define MAX_ELEMENT 200
#define MAX_VTXS 20

class AdjMatGraph {
protected:
    int size;
    char vertices[MAX_VTXS];
    int adj[MAX_VTXS][MAX_VTXS];

public:
    AdjMatGraph() { reset(); }

    char getVertex(int i) { return vertices[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }

    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= MAX_VTXS; }

    void reset() {
        size = 0;

        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                setEdge(i, j, 0);
    }

    void insertVertex(char name) {
        if (!isFull())
            vertices[size++] = name;
        else
            printf("Error: 그래프 정점 개수 초과\n");
    }

    void insertEdge(int u, int v) {
        setEdge(u, v, 1);
        setEdge(v, u, 1);
    }

    void display(FILE* fp = stdout) {
        fprintf(fp, "%d\n", size);

        for (int i = 0; i < size; i++) {
            fprintf(fp, "%c ", getVertex(i));

            for (int j = 0; j < size; j++)
                fprintf(fp, "%3d", getEdge(i, j));

            fprintf(fp, "\n");
        }
    }
};

class SrchAMGraph : public AdjMatGraph {
    bool visited[MAX_VTXS];

public:
    void resetVisited() {
        for (int i = 0; i < size; i++)
            visited[i] = false;
    }

    bool isLinked(int u, int v) {
        return getEdge(u, v) != 0;
    }

    void DFS(int v) {
        visited[v] = true;

        printf("%c ", getVertex(v));

        for (int w = 0; w < size; w++) {
            if (isLinked(v, w) && visited[w] == false)
                DFS(w);
        }
    }
};

#define INF 9999

class WGraph : public AdjMatGraph {
public:
    void insertEdge(int u, int v, int weight) {
        if (weight > INF) weight = INF;
        setEdge(u, v, weight);
    }
    bool hasEdge(int i, int j) { return(getEdge(i, j) < INF); }
    void load(const char* filename) {
        FILE* fp;
        fopen_s(&fp, filename, "r");
        if (fp != NULL) {
            int n, val;
            fscanf_s(fp, "%d", &n);
            for (int i = 0; i < n; i++) {
                char str[80];
                int val;
                fscanf_s(fp, "%s", str, sizeof(str));
                insertVertex(str[0]);
                for (int j = 0; j < n;j++) {
                    fscanf_s(fp, "%d", &val);
                    insertEdge(i, j, val);
                }
                
            }
        }
        fclose(fp);
    }
};

class VertexSets {
    int parent[MAX_VTXS];
    int nSets;
public:
    VertexSets(int n) : nSets(n) {
        for (int i = 0; i < nSets; i++)
            parent[i] = -1;
    }
    bool isRoot(int i) { return parent[i] < 0; }
    int findSet(int v) {
        while (!isRoot(v)) v = parent[v];
        return v;
    }
    void unionSets(int s1, int s2) {
        parent[s1] = s2;
        nSets--;
    }

};

class MinHeap {
    HeapNode node[MAX_ELEMENT];
    int size;

public:
    MinHeap() : size(0) { }

    bool isFull() {
        return size == MAX_ELEMENT - 1;
    }

    bool isEmpty() {
        return size == 0;
    }

    HeapNode& getParent(int i) {
        return node[i / 2];
    }

    void insert(int key, int u, int v) {
        if (isFull()) return;

        int i = ++size;

        while (i != 1 && key < node[i / 2].getKey()) {
            node[i] = node[i / 2];
            i /= 2;
        }

        node[i].setKey(key, u, v);
    }
    HeapNode& remove() {
        HeapNode item = node[1];
        HeapNode last = node[size--];
        int parent = 1, child = 2;
        while (child <= size) {
            if (child < size && node[child].getKey()>node[child + 1].getKey())
                child++;
            if (last.getKey() <= node[child].getKey()) break;
            node[parent] = node[child];
            parent = child;
            child *= 2;

        }
        node[parent] = last;
        return item;
    }
};



class HeapNode {
    int key;
    int v1;
    int v2;
public:
    HeapNode() : key(0), v1(0), v2(0) {}
    HeapNode(int k, int u, int v) : key(k), v1(u), v2(v){}
    void setKey(int k, int u, int v) { key = k; v1 = u; v2 = v; }
    int getKey() { return key; }
    int getV1() { return v1; }
    int getV2() { return v2; }
};
class WGraphMST : public WGraph {
public:
    void Kruskal() {   // kruskal의 최소 비용 신장 트리 프로그램
        MinHeap heap;
        for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j < size; j++)
                if (hasEdge(i, j))
                    heap.insert(getEdge(i, j), i, j); // 모든 간선 삽입
        VertexSets set(size);    // size개의 집합을 만듦
        int edgeAccepted = 0;      // 선택된 간선의 수
        while (edgeAccepted < size - 1) { // 간선의 수 < (size-1)
            HeapNode& e = heap.remove();
            int uset = set.findSet(e.getV1());
            int vset = set.findSet(e.getV2());
            if (uset != vset) {
                printf("간선 추가 : %c - %c (비용:%d)\n",
                    getVertex(e.getV1()), getVertex(e.getV2()), e.getKey());
                set.unionSets(uset, vset);      // 두개의 집합을 합함.
                edgeAccepted++;
            }
        }
    }
};
