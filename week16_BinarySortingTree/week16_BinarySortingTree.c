#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct TreeNode* insert(struct TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

//这个函数会从给定的节点开始，沿着左子树一直向下走，直到找到最左边的节点。这个最左边的节点就是当前节点的最小值节点。
struct TreeNode* findMin(struct TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL) {
        return root;
    }

    // 找到要删除的节点
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // 节点包含要删除的值

        // 节点只有一个子节点或没有子节点
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp; //返回右子节点作为新的父节点
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp; //返回左子节点作为新的父节点
        }

        // 节点有两个子节点，找到中序后继节点
        struct TreeNode* temp = findMin(root->right);

        // 将中序后继节点的值复制到当前节点
        root->data = temp->data;

        // 删除中序后继节点
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}
//搜索节点
struct TreeNode* search(struct TreeNode* root, int key) {

    if (root == NULL || root->data == key) {
        return root;
    }

    // 如果要查找的键小于当前节点的键，在左子树中查找
    if (key < root->data) {
        return search(root->left, key);
    }

    else {
        return search(root->right, key);
    }
}
//中序遍历
void inOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

int main() {
    struct TreeNode* root = NULL;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("原始二叉排序树：");
    inOrderTraversal(root);
    printf("\n");

    int keyToDelete = 50;
    root = deleteNode(root, keyToDelete);

    printf("删除节点 %d 后的二叉排序树：", keyToDelete);
    inOrderTraversal(root);
    printf("\n");

     // 搜索节点
    int key;
    printf("请输入你要查找的数：");
    scanf("%d",&key);
   struct TreeNode* result = search(root,key);
   if(result==NULL) {
       printf("%d不在该树中 \n", key);
   } else{
       printf("%d在该树中 \n",key);
   }

    return 0;
}
