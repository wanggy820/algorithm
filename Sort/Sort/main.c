//
//  main.c
//  Sort
//
//  Created by wanggy820 on 2022/11/2.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define N 120

/*
 1.每次从需要排序的元素的找出最小的元素，存储在最左侧，
 2.再从剩余元素中继续寻找，继续存储，直至排序完成
 
 选择排序不稳定，但是效率与冒泡排序相比，有明显提高
 */
void select_sort(int *a, int n) {
    int minIndex, tmp;
    for (int i = 0; i < n; i++) {
        minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (a[minIndex] > a[j]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            tmp = a[minIndex];
            a[minIndex] = a[i];
            a[i] = tmp;
        }
    }
}

void merge(int *a,int left,int right,int mid) {
    int s[N];//一个新数组用来存储排序好的数组
    int i = left, j = mid + 1;//两个变量分别指向左边和右边两组数的第一个数
    int sor = left;
    while (i <= mid && j <= right) {
        if (a[i] < a[j]) {//归并的过程
            s[sor++] = a[i++];
        }
        else {
            s[sor++] = a[j++];
        }
    }
    while (i <= mid) s[sor++] = a[i++];
    while (j <= right)  s[sor++] = a[j++];
    sor = left;
    while (sor <= right) {//把排好序的新数组全部放回原数组里
        a[sor] = s[sor];
        sor++;
    }
}


void merge_sort(int *a,int left,int right){
    if(left<right){
        int mid = (left + right) / 2;//从中间截开
        merge_sort(a,left, mid);//把左边沿中间截开
        merge_sort(a, mid + 1, right);//把右边沿中间截开
        merge(a, left, right, mid);//合并
    }
}

int partition(int *a,int p,int r) {
    int x = a[r];
    int i = p - 1;
    int tmp;
    for (int j = p; j < r; j++) {
        if (a[j] < x) {
            i++;
            tmp = a[j];
            a[j] = a[i];
            a[i] = tmp;
        }
    }
    tmp = a[i+1];
    a[i+1] = a[r];
    a[r] = tmp;
    return i+1;
}

void quick_sort(int *a,int p,int r) {
    if (p < r) {
        int q = partition(a, p, r);
        quick_sort(a, p, q-1);
        quick_sort(a, q+1, r);
    }
}

void shell_sort(int *a, int n) {
    int d,i,j,index;//d为增量
    int temp;
    //最外层循环，用来确定增量的多少
    for(d = n/2; d > 0; d = d/2) {
        //外层循环，用来确定要执行多少次直接插入排序
        for(i = 0; i < d; i++) {
            //内层循环，分组后的排序，采用直接插入排序
            for(j = i; j < n; j = j + d) {
                temp = a[j];
                index = j - d;
                while(temp < a[index] && index>=0) {
                    a[index+d] = a[index];
                    index = index-d;
                }
                a[index+d]=temp;
            }
        }
    }
}


#define  D 5        // 最大位数
// 基数排序
void radix_sort(int *a, int n) {
    int i, j, k, l, digit;
    int allot[10][N];   // 分配数组
    
    // 初始化分配数组全为0
    memset(allot, 0, sizeof(allot));
    
    // 遍历
    for (i = 1; i <= D; i++) {
        // 将每个数据的第i位数分配到allot数组中
        for (j = 0; j < n; j++) {
            // 获取当前数据 num[j] 的 第i位数
            digit = get_digit(a[j], i);
            k = 0;
            // 查找插入的位置
            while (allot[digit][k]) {
                k++;
            }
            // 将num[j]添加到分配数组allot的第digit行的末尾
            allot[digit][k] = a[j];
        }
        // 将分配数组的数据收集到原数组中
        l = 0;
        for (j = 0; j < 10; j++) {
            k = 0;
            // 获取数组allot的每一行的数据 到 原数组中
            while (allot[j][k]) {
                a[l++] = allot[j][k++];
            }
        }
        memset(allot, 0, sizeof(allot));
    }
}


void inputList(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = arc4random()%10001;
    }
}

void printList(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("a[%d] = %d\n", i , a[i]);
    }
}

/*
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    int a[N];
    int n = N;
    inputList(a, n);
//    select_sort(a, n);
//    merge_sort(a, 0, n-1);
//    quicksort(a, 0, n-1);
//    shell_sort(a, n);
    radix_sort(a, n);
    printList(a, n);
    
    return 0;
}
*/
