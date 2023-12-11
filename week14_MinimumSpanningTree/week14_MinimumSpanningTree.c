#include <stdio.h>
#include <stdlib.h>

// 定义图的最大顶点数
#define MAX_VERTICES 100

// 定义图的最大边数
#define MAX_EDGES 100

// 定义无穷大值，表示两顶点之间没有直接边相连
#define INF 999999

// 定义图的边结构体
typedef struct {
    int start;  // 边的起始顶点
    int end;    // 边的结束顶点
    int weight; // 边的权重
} Edge;

// 定义图的结构体
typedef struct {
    int numVertices; // 顶点数
    int numEdges;    // 边数
    Edge edges[MAX_EDGES]; // 边数组
} Graph;

// 初始化图
void initGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;
    graph->numEdges = 0;
}

// 添加边到图
void addEdge(Graph* graph, int start, int end, int weight) {
    if (graph->numEdges < MAX_EDGES) {
        graph->edges[graph->numEdges].start = start;
        graph->edges[graph->numEdges].end = end;
        graph->edges[graph->numEdges].weight = weight;
        graph->numEdges++;
    }
}

// Prim算法实现
void prim(Graph* graph) {
    int selected[MAX_VERTICES]; // 记录顶点是否被选中
    int parent[MAX_VERTICES];   // 记录每个顶点的父节点
    int key[MAX_VERTICES];      // 记录每个顶点的关键值

    // 初始化数组
    for (int i = 0; i < graph->numVertices; i++) {
        selected[i] = 0;
        key[i] = INF;
        parent[i] = -1;
    }

    // 从第一个顶点开始
    key[0] = 0;

    // 找到包含V-1个顶点的最小生成树
    for (int i = 0; i < graph->numVertices - 1; i++) {
        // 找到关键值最小的未选中顶点
        int minKey = INF;
        int minIndex = -1;
        for (int j = 0; j < graph->numVertices; j++) {
            if (!selected[j] && key[j] < minKey) {
                minKey = key[j];
                minIndex = j;
            }
        }

        // 将该顶点标记为已选中
        selected[minIndex] = 1;

        // 更新与该顶点相邻的未选中顶点的关键值和父节点
        for (int j = 0; j < graph->numEdges; j++) {
            if (graph->edges[j].start == minIndex && !selected[graph->edges[j].end] && graph->edges[j].weight < key[graph->edges[j].end]) {
                key[graph->edges[j].end] = graph->edges[j].weight;
                parent[graph->edges[j].end] = minIndex;
            }
            if (graph->edges[j].end == minIndex && !selected[graph->edges[j].start] && graph->edges[j].weight < key[graph->edges[j].start]) {
                key[graph->edges[j].start] = graph->edges[j].weight;
                parent[graph->edges[j].start] = minIndex;
            }
        }
    }

    // 输出最小生成树的边
    printf("Prim's Minimum Spanning Tree:\n");
    for (int i = 1; i < graph->numVertices; i++) {
        printf("(%d, %d) - %d\n", parent[i], i, key[i]);
    }
}

// Kruskal算法实现
void kruskal(Graph* graph) {
    int parent[MAX_VERTICES]; // 记录每个顶点的父节点

    // 初始化数组
    for (int i = 0; i < graph->numVertices; i++) {
        parent[i] = i;
    }

    // 排序所有边
    for (int i = 0; i < graph->numEdges - 1; i++) {
        for (int j = 0; j < graph->numEdges - i - 1; j++) {
            if (graph->edges[j].weight > graph->edges[j + 1].weight) {
                // 交换两条边
                Edge temp = graph->edges[j];
                graph->edges[j] = graph->edges[j + 1];
                graph->edges[j + 1] = temp;
            }
        }
    }

    // 输出排序后的边
    printf("Sorted Edges:\n");
    for (int i = 0; i < graph->numEdges; i++) {
        printf("(%d, %d) - %d\n", graph->edges[i].start, graph->edges[i].end, graph->edges[i].weight);
    }

    // 输出最小生成树的边
    printf("Kruskal's Minimum Spanning Tree:\n");
    for (int i = 0; i < graph->numEdges; i++) {
        int root1 = parent[graph->edges[i].start];
        int root2 = parent[graph->edges[i].end];

        // 如果边的两个顶点不在同一连通分量中，则选择该边
        if (root1 != root2) {
            printf("(%d, %d) - %d\n", graph->edges[i].start, graph->edges[i].end, graph->edges[i].weight);

            // 合并两个连通分量
            for (int j = 0; j < graph->numVertices; j++) {
                if (parent[j] == root2) {
                    parent[j] = root1;
                }
            }
        }
    }
}

int main() {
    Graph graph;
    int numVertices, numEdges;

    printf("输入顶点数: ");
    scanf("%d", &numVertices);

    initGraph(&graph, numVertices);

    printf("输入边数: ");
    scanf("%d", &numEdges);

    printf("请输入边（输入每条边的起始顶点、结束顶点和权重）:\n");
    for (int i = 0; i < numEdges; i++) {
        int start, end, weight;
        scanf("%d %d %d", &start, &end, &weight);
        addEdge(&graph, start, end, weight);
    }

    prim(&graph);
    kruskal(&graph);

    return 0;
}
