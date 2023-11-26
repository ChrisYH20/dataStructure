#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int weight;
    int parent, lchild, rchild;
    char *code;  // 用于存储赫夫曼编码
} HTNode, *HuffmanTree;

// 构建赫夫曼树
void buildHuffmanTree(HuffmanTree ht, int n) {
    for (int i = 0; i < 2 * n - 1; ++i) {
        ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
    }

    for (int i = n; i < 2 * n - 1; ++i) {
        int min1 = -1, min2 = -1;

        // 找到权值最小的两个节点
        for (int j = 0; j < i; ++j) {
            if (ht[j].parent == -1) {
                if (min1 == -1 || ht[j].weight < ht[min1].weight) {
                    min2 = min1;
                    min1 = j;
                } else if (min2 == -1 || ht[j].weight < ht[min2].weight) {
                    min2 = j;
                }
            }
        }

        // 合并两个最小的节点
        ht[i].weight = ht[min1].weight + ht[min2].weight;
        ht[i].lchild = min1;
        ht[i].rchild = min2;
        ht[min1].parent = ht[min2].parent = i;
    }
}

// 生成赫夫曼编码
void generateHuffmanCode(HuffmanTree ht, int n) {
    for (int i = 0; i < n; ++i) {
        int current = i;
        int parent = ht[current].parent;

        // 从叶子结点向上回溯，生成编码
        while (parent != -1) {
            if (ht[parent].lchild == current) {
                ht[i].code = strcat(strdup("0"), ht[i].code);
            } else {
                ht[i].code = strcat(strdup("1"), ht[i].code);
            }
            current = parent;
            parent = ht[current].parent;
        }
    }
}

// 打印赫夫曼树的信息和编码
void printHuffmanTree(HuffmanTree ht, int n) {
    printf("Weight\tParent\tLChild\tRChild\tCode\n");
    for (int i = 0; i < 2 * n - 1; ++i) {
        printf("%d\t%d\t%d\t%d\t%s\n", ht[i].weight, ht[i].parent, ht[i].lchild, ht[i].rchild, ht[i].code);
    }
}

int main() {
    int weights[] = {5, 29, 7, 8, 14};
    int n = sizeof(weights) / sizeof(weights[0]);

    HuffmanTree ht = (HuffmanTree)malloc(sizeof(HTNode) * (2 * n - 1));

    // 初始化节点权值
    for (int i = 0; i < n; ++i) {
        ht[i].weight = weights[i];
        ht[i].code = "";
    }

    buildHuffmanTree(ht, n);
    generateHuffmanCode(ht, n);
    printHuffmanTree(ht, n);

    free(ht);

    return 0;
}
