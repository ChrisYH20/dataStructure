#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

typedef struct
{
    int *elem;    // 储存线性表大小的元素的数组
    int size;     // 线性表大小
    int capacity; // 线性表容量
} sqlist;

void InitList(sqlist *L, int capacity)
{
    L->elem = (int *)malloc(capacity * sizeof(int));
    if (L->elem == NULL)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    L->size = 0;
    L->capacity = capacity;
    printf("内存分配成功\n");
}

enum Boolean
{
    FALSE,
    TRUE
};

enum Boolean ListEmpty(sqlist *L)
{

    if (L->size > 0)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void CreateList(sqlist *L, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("请输入第%d个数:", i + 1);
        scanf("%d", &L->elem[i]);
    }
    L->size = n;
}

int ListLength(sqlist *L)
{
    return L->size;
}

void GetElem(sqlist *L)
{
    printf("请输入要查找第几个数:");
    int a = 0;
    scanf("%d", &a);
    if (a > L->size || a < 0)
    {
        printf("错误");
        exit(1);
    }
    else
    {
        for (int i = 0; i <= L->size; i++)
        {
            if (i == a - 1)
                printf("L1中第%d的数是 %d\n", a, L->elem[i]);
        }
    }
}

int locateElem(sqlist *list, int target, int (*compare)(int, int))
{
    for (int i = 0; i < list->size; i++)
    {
        if (compare(list->elem[i], target) == 0)
        {
            return i + 1;
        }
    }
    return -1;
}

int priorElem(sqlist *list, int cur_e, int *pre_e)
{
    for (int i = 1; i < list->size; i++)
    {
        if (list->elem[i] == cur_e)
        {
            *pre_e = list->elem[i - 1];
            return 1;
        }
    }
    return 0;
}

int nextElem(sqlist *list, int cur_e, int *next_e)
{
    for (int i = 0; i < list->size - 1; i++)
    {
        if (list->elem[i] == cur_e)
        {
            *next_e = list->elem[i + 1];
            return 1;
        }
    }
    return 0;
}

int compare(int a, int b)
{
    return a - b;
}

int insert(sqlist *list, int element, int position)
{
    if (position < 0)
    {
        return 0;
    }

    if (list->size == list->capacity)
    {
        int newCapacity = list->capacity * 2;
        int *newData = (int *)realloc(list->elem, sizeof(int) * newCapacity);
        if (newData == NULL)
        {
            printf("内存分配失败\n");
            exit(1);
        }
        list->elem = newData;
        list->capacity = newCapacity;
    }

    for (int i = list->size; i > position; i--)
    {
        list->elem[i] = list->elem[i - 1];
    }

    list->elem[position] = element;
    list->size++;
    return 1;
}

int listInsert(sqlist *list, int i, int *e)
{
    if (i < 1 || i > list->size)
    {
        return 0;
    }

    *e = list->elem[i - 1];

    for (int j = i; j < list->size; j++)
    {
        list->elem[j - 1] = list->elem[j];
    }

    list->size--;
    return 1;
}

void merge(sqlist *LA, sqlist *LB, sqlist *LC)
{
    int i = 0, j = 0;

    while (i < LA->size && j < LB->size)
    {
        if (LA->elem[i] <= LB->elem[j])
        {
            insert(LC, LA->elem[i], LC->size);
            i++;
        }
        else
        {
            insert(LC, LB->elem[j], LC->size);
            j++;
        }
    }

    while (i < LA->size)
    {
        insert(LC, LA->elem[i], LC->size);
        i++;
    }

    while (j < LB->size)
    {
        insert(LC, LB->elem[j], LC->size);
        j++;
    }
}

void printList(sqlist *L)
{
    printf("线性表中的元素: ");
    for (int i = 0; i < L->size; i++)
    {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

void clear(sqlist *L)
{
    L->size = 0;
}

void DestroyList(sqlist *list)
{
    free(list->elem);
    list->size = 0;
    list->capacity = 0;
    list->elem = NULL;
}

int main()
{
    sqlist L1;
    InitList(&L1, 10);
    enum Boolean result_1 = ListEmpty(&L1);
    printf("L1是空表吗：%d \n", result_1);
    CreateList(&L1, 6);

    printList(&L1);

    int a = insert(&L1, 222, 2);
    printf("插入是否成功%d\n", a);

    printList(&L1);

    int result_2 = ListLength(&L1);
    printf("L1中数据元素的个数为：%d \n", result_2);
    GetElem(&L1);

    int target = 10;
    int position = locateElem(&L1, target, compare);
    if (position != -1)
    {
        printf("%d 第一次出现在位序 %d\n", target, position);
    }
    else
    {
        printf("%d 未找到\n", target);
    }

    int cur_e_1 = 10;
    int pre_e;
    if (priorElem(&L1, cur_e_1, &pre_e))
    {
        printf("%d 的前驱是 %d\n", cur_e_1, pre_e);
    }
    else
    {
        printf("%d 无前驱\n", cur_e_1);
    }

    int cur_e_2 = 10;
    int next_e;
    if (nextElem(&L1, cur_e_1, &next_e))
    {
        printf("%d 的后继是 %d\n", cur_e_2, next_e);
    }
    else
    {
        printf("%d 无后继\n", cur_e_2);
    }

    int i = 2;
    int e;
    if (listInsert(&L1, i, &e))
    {
        printf("删除的元素值为: %d\n", e);
    }
    else
    {
        printf("删除失败\n");
    }

    sqlist LA, LB, LC;
    InitList(&LA, 4);
    InitList(&LB, 7);

    insert(&LA, 3, 0);
    insert(&LA, 5, 1);
    insert(&LA, 8, 2);
    insert(&LA, 11, 3);

    insert(&LB, 2, 0);
    insert(&LB, 6, 1);
    insert(&LB, 8, 2);
    insert(&LB, 9, 3);
    insert(&LB, 11, 4);
    insert(&LB, 15, 5);
    insert(&LB, 20, 6);

    printf("线性表 LA: ");
    printList(&LA);

    printf("线性表 LB: ");
    printList(&LB);

    InitList(&LC, LA.size + LB.size);
    merge(&LA, &LB, &LC);

    printf("合并后的线性表 LC: ");
    printList(&LC);

    DestroyList(&L1);
    DestroyList(&LA);
    DestroyList(&LB);
    DestroyList(&LC);

    return 0;
}
