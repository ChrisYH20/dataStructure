//二叉排序树

#include <stdio.h>
#include <stdlib.h>


struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
};

struct TreeNode* insert(struct TreeNode* root, int value);
struct TreeNode* search(struct TreeNode* root, int key);


struct TreeNode* insert(struct TreeNode* root, int value) {
    if (root == NULL) {
        // 如果树为空，创建新节点
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->data = value;
        newNode->left = newNode->right = NULL;
        newNode->parent=NULL;
        return newNode;
    }


    if (value < root->data) {
        root->left = insert(root->left, value);
        //(root->left)->parent=root->left;
    }
        // 如果值大于当前节点的值，插入右子树
    else if (value > root->data) {
        root->right = insert(root->right, value);
        //(root->right)->parent=root->right;
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

//后序遍历用于插入
struct TreeNode* postOrder(struct TreeNode *node,struct TreeNode *root) {
    if (node == NULL)
        return NULL;

    insert(root,node->data);
    //free(node);
    postOrder(node->left,root);
   // printf("%d  ",root->data);

    postOrder(node->right,root);
//    if(root->parent=NULL){
//        return NULL;
//    }
    

}

void delet(struct TreeNode* root,int key){
    struct TreeNode* temp= search(root,key);
    struct TreeNode* tpright=temp->right;
    struct TreeNode* tpleft=temp->left;

    
    
    free(search(root,key));

    if(tpleft!=NULL){
        postOrder(tpleft,root);

    }
    else if(tpright!=NULL){
        postOrder(tpright,root);
    }
    //free(search(root,key));
}

struct TreeNode* inOrder(struct TreeNode *root) {
    if (root == NULL)
        return NULL;
    // 访问优先级：左子树 -> 根节点 -> 右子树
    inOrder(root->left);
    printf("%d  ",root->data);

    inOrder(root->right);
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

    // 搜索节点
    int key = 30;
   struct TreeNode* result = search(root,key);
   if(result==NULL) {
       printf("%d不在该树中 \n", key);
   } else{
       printf("%d在该树中 \n",key);
   }

    inOrder(root);
    printf("\n");

    delet(root,20);
    printf("删除20后,树为:");
    inOrder(root);
    return 0;
}