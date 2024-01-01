
#include <stdio.h>

// 冒泡排序
void bubbleSort(int array[], int number) {
    // 外循环，控制需要比较的轮数
    for (int i = number; i > 0; --i) {
        // 内循环，每轮比较相邻的元素并交换它们的位置
        for (int j = 0; j < i - 1; ++j) {
            // 如果前面的元素比后面的元素大，进行交换
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}


//插入排序
void insertion_sort(int array[],int number){
    for (int i = 1; i < number; ++i) {
        int base= array[i];
        int j = i-1;
        for ( j; j > 0 && array[j]>base; --j) {
            array[j+1]=array[j];
        }
        
        array[j+1]=base;
    }
}

/* 插入排序 */
void insertionSort(int nums[], int size) {
    // 外循环：已排序元素数量为 1, 2, ..., n
    for (int i = 1; i < size; i++) {
        int base = nums[i], j = i - 1;
        // 内循环：将 base 插入到已排序部分的正确位置
        while (j >= 0 && nums[j] > base) {
            // 将 nums[j] 向右移动一位
            nums[j + 1] = nums[j];
            j--;
        }
        // 将 base 赋值到正确位置
        nums[j + 1] = base;
    }
}

/* 堆的长度为 n ，从节点 i 开始，从顶至底堆化 */
void siftDown(int nums[], int n, int i) {
    while (1) {
        // 判断节点 i, l, r 中值最大的节点，记为 ma
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int ma = i;
        if (l < n && nums[l] > nums[ma])
            ma = l;
        if (r < n && nums[r] > nums[ma])
            ma = r;
        // 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出
        if (ma == i) {
            break;
        }
        // 交换两节点
        int temp = nums[i];
        nums[i] = nums[ma];
        nums[ma] = temp;
        // 循环向下堆化
        i = ma;
    }
}

/* 堆排序 */
void heapSort(int nums[], int n) {
    // 建堆操作：堆化除叶节点以外的其他所有节点
    for (int i = n / 2 - 1; i >= 0; --i) {
        siftDown(nums, n, i);
    }
    // 从堆中提取最大元素，循环 n-1 轮
    for (int i = n - 1; i > 0; --i) {
        // 交换根节点与最右叶节点（交换首元素与尾元素）
        int tmp = nums[0];
        nums[0] = nums[i];
        nums[i] = tmp;
        // 以根节点为起点，从顶至底进行堆化
        siftDown(nums, i, 0);
    }
}


int main() {
   int array[]={1,4,9, 5,6,7,8,2,3};
    printf("排序前的数组为：");
   for (int i = 0; i < 9; ++i) {
        printf("%d  ",array[i]);
    }



    printf("\n");
    bubbleSort(array,9);
    printf("冒泡排序后的数组为：");
    for (int i = 0; i < 9; ++i) {
        printf("%d  ",array[i]);
    }


    printf("\n");
    int array1[]={1,4,9, 5,6,7,8,2,3};
    insertion_sort(array1,9);
    // insertionSort(array1,9);
    printf("插入排序后的数组为：");
    for (int i = 0; i < 9; ++i) {
        printf("%d  ",array1[i]);
    }

    printf("\n");
    int array2[]={1,4,9, 5,6,7,8,2,3};
    heapSort(array2,9);
    printf("插入排序后的数组为：");
    for (int i = 0; i < 9; ++i) {
        printf("%d  ",array2[i]);
    }
    printf("\n");


    return 0;
}