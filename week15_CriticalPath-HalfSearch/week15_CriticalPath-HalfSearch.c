#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXVEX 100

// 边表结点声明
typedef struct EdgeNode {
    int adjvex;
    int weight;
    struct EdgeNode *next;
} EdgeNode;

// 顶点表结点声明
typedef struct VertexNode {
    int in; // 顶点入度
    int data;
    int earlyStart;
    int lateStart;
    EdgeNode *firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct {
    AdjList adjList;
    int numVertexes, numEdges;
} GraphAdjList, *GraphAdjListPtr;

int *etv, *ltv;
int *stack2;
int top2;

// 拓扑排序算法
int TopologicalSort(GraphAdjList GL) {
    EdgeNode *e;
    int i, k, gettop;
    int top = 0;
    int count = 0;
    int *stack;

    stack = (int *)malloc(GL.numVertexes * sizeof(int));

    for (i = 0; i < GL.numVertexes; i++) {
        if (0 == GL.adjList[i].in) {
            stack[++top] = i;
        }
    }

    top2 = 0;
    etv = (int *)malloc(GL.numVertexes * sizeof(int));
    for (i = 0; i < GL.numVertexes; i++) {
        etv[i] = 0;
    }
    stack2 = (int *)malloc(GL.numVertexes * sizeof(int));

    while (0 != top) {
        gettop = stack[top--];
        stack2[++top2] = gettop;
        count++;

        for (e = GL.adjList[gettop].firstedge; e; e = e->next) {
            k = e->adjvex;
            if (!(--GL.adjList[k].in)) {
                stack[++top] = k;
            }

            if ((etv[gettop] + e->weight) > etv[k]) {
                etv[k] = etv[gettop] + e->weight;
            }
        }
    }

    if (count < GL.numVertexes) {
        fprintf(stderr, "图中存在回路，无法进行关键路径计算\n");
        return 0; // 存在回路，返回 0 表示失败
    } else {
        return 1; // 拓扑排序成功
    }
}

// 求关键路径，GL为有向图，输出GL的各项关键活动和拓扑排序结果
void CriticalPath(GraphAdjList GL) {
    EdgeNode *e;
    int i, gettop, k, j;
    int ete, lte;

    // 调用改进后的拓扑排序，求出etv和stack2的值
    if (TopologicalSort(GL) == 0) {
        return; // 拓扑排序失败，存在回路
    }

   printf("Topological Sorting: ");
for (i = 1; i <= top2; i++) {
    printf("v%d -> ", GL.adjList[stack2[i]].data);
}
printf("\n");

    // 初始化ltv都为汇点的时间
    ltv = (int *)malloc(GL.numVertexes * sizeof(int));
    for (i = 0; i < GL.numVertexes; i++) {
        ltv[i] = etv[GL.numVertexes - 1];
    }

    // 从汇点倒过来逐个计算ltv
    while (0 != top2) {
        gettop = stack2[top2--];
        for (e = GL.adjList[gettop].firstedge; e; e = e->next) {
            k = e->adjvex;
            if ((ltv[k] - e->weight) < ltv[gettop]) {
                ltv[gettop] = ltv[k] - e->weight;
            }
        }
    }

    // 通过etv和ltv求ete和lte，并输出关键路径
    printf("Critical Path: ");
    for (j = 0; j < GL.numVertexes; j++) {
        for (e = GL.adjList[j].firstedge; e; e = e->next) {
            k = e->adjvex;
            ete = etv[j];
            lte = ltv[k] - e->weight;

            if (ete == lte) {
                printf("<v%d, v%d> length: %d , ", GL.adjList[j].data, GL.adjList[k].data, e->weight);
            }
        }
    }
    printf("\n");
}

//折半查找
int BinarySearchTopologicalOrder(GraphAdjList GL, int target) {
    int low = 1;
    int high = top2;

    while (low <= high) {
        int mid = (low + high) / 2;
        int midVertexIndex = stack2[mid];

        if (midVertexIndex == target) {
            return mid;
        } else if (midVertexIndex < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // 未找到
}

int main() {
    // 在这里初始化图结构和边
    GraphAdjList graph;
    graph.numVertexes = 9;
    graph.numEdges = 14;

    for (int i = 0; i < graph.numVertexes; i++) {
        graph.adjList[i].data = i + 1;
        graph.adjList[i].in = 0;
        graph.adjList[i].firstedge = NULL;
    }

    int edges[][3] = {
        {0, 1, 6},
        {0, 2, 4},
        {0, 3, 5},
        {1, 4, 1},
        {2, 4, 1},
        {3, 5, 2},
        {4, 6, 9},
        {4, 7, 7},
        {5, 7, 4},
        {6, 8, 2},
        {7, 8, 4},
        {1, 6, 8},
        {2, 7, 7},
        {3, 8, 9}
    };

    for (int i = 0; i < graph.numEdges; i++) {
        int start = edges[i][0];
        int end = edges[i][1];
        int weight = edges[i][2];

        EdgeNode* newEdge = (EdgeNode*)malloc(sizeof(EdgeNode));
        if (newEdge == NULL) {
            fprintf(stderr, "内存分配失败\n");
            exit(EXIT_FAILURE);
        }

        newEdge->adjvex = end;
        newEdge->weight = weight;
        newEdge->next = graph.adjList[start].firstedge;
        graph.adjList[start].firstedge = newEdge;

        // 记录入度
        graph.adjList[end].in++;
    }

    // 调用关键路径算法
    CriticalPath(graph);
    
    int searNumber;
    scanf("%d",&searNumber);
    int searchResult = BinarySearchTopologicalOrder(graph, searNumber);

    if (searchResult != -1) {
        printf("顶点%d在拓扑排序中的位置为 %d \n", searNumber,searchResult);
    } else {
        printf("顶点%d未找到.\n",searNumber);
    }


    return 0;
}
