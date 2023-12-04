#include <stdio.h>
#include <stdlib.h>

// 结点结构
struct Node {
    int data;
    struct Node* next;
};

// 图结构
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

// 创建结点
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 创建图
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    // 创建邻接表数组
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    // 初始化每个邻接表为空
    for (int i = 0; i < vertices; ++i) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0; // 设置所有顶点为未访问
    }

    return graph;
}

// 添加边
void addEdge(struct Graph* graph, int src, int dest) {
    // 添加边 src->dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // 由于是无向图，还要添加 dest->src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// 深度优先搜索
void DFS(struct Graph* graph, int vertex) {
    struct Node* adjList = graph->adjLists[vertex];
    struct Node* temp = adjList;

    printf("访问顶点 %d\n", vertex);
    graph->visited[vertex] = 1; // 将当前顶点标记为已访问

    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// 广度优先搜索
void BFS(struct Graph* graph, int startVertex) {
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0;
    int rear = 0;

    // 将起始顶点入队列
    queue[rear++] = startVertex;
    graph->visited[startVertex] = 1; // 将起始顶点标记为已访问

    printf("访问顶点 %d\n", startVertex);

    while (front < rear) {
        int currentVertex = queue[front++];
        struct Node* temp = graph->adjLists[currentVertex];

        while (temp != NULL) {
            int adjVertex = temp->data;
            if (graph->visited[adjVertex] == 0) {
                printf("访问顶点 %d\n", adjVertex);
                graph->visited[adjVertex] = 1; // 标记为已访问
                queue[rear++] = adjVertex; // 入队列
            }
            temp = temp->next;
        }
    }

    free(queue);
}

// 主函数
int main() {
    int vertices = 5;
    struct Graph* graph = createGraph(vertices);

    // 添加边
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // 进行深度优先搜索
    printf("深度优先搜索结果:\n");
    DFS(graph, 0);

    // 重置访问标记
    for (int i = 0; i < vertices; ++i) {
        graph->visited[i] = 0;
    }

    // 进行广度优先搜索
    printf("\n广度优先搜索结果:\n");
    BFS(graph, 0);

    // 释放内存
    free(graph->visited);
    free(graph->adjLists);
    free(graph);

    return 0;
}
