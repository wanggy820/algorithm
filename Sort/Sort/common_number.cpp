//
//  common_number.cpp
//  Sort
//
//  Created by wanggy820 on 2022/11/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


/*
 1.每次从需要排序的元素的找出最小的元素，存储在最左侧，
 2.再从剩余元素中继续寻找，继续存储，直至排序完成
 
 选择排序不稳定，但是效率与冒泡排序相比，有明显提高
 */
void select_sort(int *arr, int len) {
    int min_index, tmp;
    for (int i = 0; i < len; i++) {
        min_index = i;
        for (int j = i+1; j < len; j++) {
            if (arr[min_index] > arr[j]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            tmp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = tmp;
        }
    }
}

void merge(int *arr, int *reg, int left, int right) {
    int mid = (left + right) >> 1;
    int i = left, j = mid + 1;//两个变量分别指向左边和右边两组数的第一个数
    int sort = left;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {//归并的过程
            reg[sort++] = arr[i++];
        }
        else {
            reg[sort++] = arr[j++];
        }
    }
    while (i <= mid) reg[sort++] = arr[i++];
    while (j <= right)  reg[sort++] = arr[j++];
    sort = left;
    while (sort <= right) {//把排好序的新数组全部放回原数组里
        arr[sort] = reg[sort];
        sort++;
    }
}

void merge_sort_recursive(int *arr, int *reg, int left, int right) {
    if(left < right){
        int mid = (left + right) >> 1;//从中间截开
        merge_sort_recursive(arr, reg, left, mid);//把左边沿中间截开
        merge_sort_recursive(arr, reg, mid + 1, right);//把右边沿中间截开
        merge(arr, reg, left, right);//合并
    }
}

void merge_sort(int *arr, int len) {
    int *reg = new int[len];
    merge_sort_recursive(arr, reg, 0, len - 1);
}

int partition(int *arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    int tmp;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            tmp = arr[j];
            arr[j] = arr[i];
            arr[i] = tmp;
        }
    }
    tmp = arr[i+1];
    arr[i+1] = arr[right];
    arr[right] = tmp;
    return i+1;
}

void quick_sort_recursive(int *arr, int left, int right) {
    if (left < right) {
        int q = partition(arr, left, right);
        quick_sort_recursive(arr, left, q-1);
        quick_sort_recursive(arr, q+1, right);
    }
}

void quick_sort(int *arr, int len) {
    quick_sort_recursive(arr, 0, len-1);
}

void shell_sort(int *arr, int len) {
    int d,i,j,index;//d为增量
    int temp;
    //最外层循环，用来确定增量的多少
    for(d = len/2; d > 0; d = d/2) {
        //外层循环，用来确定要执行多少次直接插入排序
        for(i = 0; i < d; i++) {
            //内层循环，分组后的排序，采用直接插入排序
            for(j = i; j < len; j = j + d) {
                temp = arr[j];
                index = j - d;
                while(index >= 0 && temp < arr[index]) {
                    arr[index + d] = arr[index];
                    index = index - d;
                }
                arr[index + d]=temp;
            }
        }
    }
}


/**
    * 基数排序
    * 考虑正负数
    * 为避免出现负数或者0, 统一所有值减去最小值并加1
    */
void radix_sort(int *arr, int len) {
    //求最小值和最大值
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < len; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
        if (min > arr[i]) {
            min = arr[i];
        }
    }
    //求最高位数(统一所有值减去最小值并加1)
    int maxDigit = 0;
    int value = max - min + 1;
    while (value > 0) {
        value /= 10;
        maxDigit++;
    }
    
    int i, j, k, l, digit;
    int allot[10][len];   // 分配数组
    // 初始化分配数组全为0
    memset(allot, 0, sizeof(allot));

    // 遍历
    for (i = 1; i <= maxDigit; i++) {
        // 将每个数据的第i位数分配到allot数组中
        for (j = 0; j < len; j++) {
            // 获取当前数据 a[j] 的 第i位数
            digit = get_digit(arr[j] - min + 1, i);
            k = 0;
            // 查找插入的位置
            while (allot[digit][k] > 0) {
                k++;
            }
            // 将a[j]添加到分配数组allot的第digit行的末尾
            allot[digit][k] = arr[j] - min + 1;
        }
        // 将分配数组的数据收集到原数组中
        int count = 0;
       
        l = 0;
        for (j = 0; j < 10; j++) {
            k = 0;
            // 获取数组allot的每一行的数据 到 原数组中
            while (allot[j][k] > 0) {
                arr[count++] = allot[j][k++] + min - 1;
            }
        }
        memset(allot, 0, sizeof(allot));
    }
}

int main2(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    int len = NUMS_CNT/100;
    int arr[len];
    
    input_list(arr, len);
//    select_sort(arr, len);
//    merge_sort(arr, len);
//    quick_sort(arr, len);
//    shell_sort(arr, len);
    radix_sort(arr, len);
    print_list(arr, len);
    
    return 0;
}
