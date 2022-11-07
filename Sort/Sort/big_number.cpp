//
//  big_number.cpp
//  Sort
//
//  Created by wanggy820 on 2022/11/7.
//

#include <stdio.h>
#include "utils.h"
#include <iostream>

void big_number_select_sort(char **arr, int len) {
    int min_index;
    char *tmp;
    for (int i = 0; i < len; i++) {
        min_index = i;
        for (int j = i+1; j < len; j++) {
            if (string2num_compare(arr[min_index], arr[j]) > 0) {
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

void big_number_merge(char **arr, char **reg, int left, int right) {
    int mid = (left + right) >> 1;
    int i = left, j = mid + 1;//两个变量分别指向左边和右边两组数的第一个数
    int sort = left;
    while (i <= mid && j <= right) {
        if (string2num_compare(arr[i], arr[j]) < 0) {//归并的过程
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

void big_number_merge_sort_recursive(char **arr, char **reg, int left, int right){
    if(left < right){
        int mid = (left + right) >> 1;//从中间截开
        big_number_merge_sort_recursive(arr, reg, left, mid);//把左边沿中间截开
        big_number_merge_sort_recursive(arr, reg, mid + 1, right);//把右边沿中间截开
        big_number_merge(arr, reg, left, right);//合并
    }
}

void big_number_merge_sort(char **arr, int len) {
    char **reg = (char **)malloc(sizeof(char *)*len);
    big_number_merge_sort_recursive(arr, reg, 0, len - 1);
}

int big_number_partition(char **arr,int left, int right) {
    char *x = arr[right];
    int i = left - 1;
    char *tmp;
    for (int j = left; j < right; j++) {
        if (string2num_compare(arr[j], x) < 0) {
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

void big_number_quick_sort_recursive(char **arr, int left, int right) {
    if (left < right) {
        int q = big_number_partition(arr, left, right);
        big_number_quick_sort_recursive(arr, left, q-1);
        big_number_quick_sort_recursive(arr, q+1, right);
    }
}

void big_number_quick_sort(char **arr, int len) {
    big_number_quick_sort_recursive(arr, 0, len - 1);
}

void big_number_shell_sort(char **arr, int len) {
    int d,i,j,index;//d为增量
    char *temp;
    //最外层循环，用来确定增量的多少
    for(d = len/2; d > 0; d = d/2) {
        //外层循环，用来确定要执行多少次直接插入排序
        for(i = 0; i < d; i++) {
            //内层循环，分组后的排序，采用直接插入排序
            for(j = i; j < len; j = j + d) {
                temp = arr[j];
                index = j - d;
                while(index >= 0 && string2num_compare(temp, arr[index]) < 0) {
                    arr[index + d] = arr[index];
                    index = index - d;
                }
                arr[index + d]=temp;
            }
        }
    }
}

void big_num_clear(char ***allot, int len) {
    for (int i = 0; i < 10; i++) {
        // 将每个数据的第i位数分配到allot数组中
        for (int j = 0; j < len; j++) {
            allot[i][j] = NULL;
        }
    }
}


/**
    * 基数排序
    * 考虑正负数
    * 为避免出现负数或者0,分开排序
    */
void real_big_number_radix_sort(char **num, int n, int isLessZero) {
    if (n == 0) {
        return;
    }
    //求最小值和最大值
    char *max = num[0];
    char *min = num[0];
    for (int i = 1; i < n; i++) {
        if (string2num_compare(max, num[i]) < 0) {
            max = num[i];
        }
        if (string2num_compare(min, num[i]) > 0) {
            min = num[i];
        }
    }
    
    //求最高位数(统一所有值减去最小值并加1)
    int maxDigit = MAX((int)strlen(max), (int)strlen(min));
    
    int i, j, k, l, digit;
    char ***allot = (char ***)malloc(sizeof(char *)*10);   // 分配数组
    for (int i = 0; i < 10; i++) {
        allot[i] = (char **)malloc(sizeof(char *)*n);
    }
    // 初始化分配数组全为空
    big_num_clear(allot, n);
    // 遍历
    for (i = 1; i <= maxDigit; i++) {
        // 将每个数据的第i位数分配到allot数组中
        for (j = 0; j < n; j++) {
            if (isLessZero && i == maxDigit) {
                continue;
            }
            // 获取当前数据 a[j] 的 第i位数
            digit = get_big_num_digit(num[j], i);
            k = 0;
            // 查找插入的位置
            while (allot[digit][k]) {
                k++;
            }
            // 将a[j]添加到分配数组allot的第digit行的末尾
            allot[digit][k] = num[j];
        }
        // 将分配数组的数据收集到原数组中
        int count = 0;
        l = 0;
        for (j = 0; j < 10; j++) {
            if (isLessZero && i == maxDigit) {
                continue;
            }
            k = 0;
            // 获取数组allot的每一行的数据 到 原数组中
            while (allot[j][k]) {
                num[count++] = allot[j][k++];
            }
        }
        big_num_clear(allot, n);
    }
}

void big_number_radix_sort(char **arr, int len) {
    char **arr1 = (char **)malloc(sizeof(char *) * len);
    char **arr2 = (char **)malloc(sizeof(char *) * len);
    int zeroCount = 0;
    int lessZero = 0;
    int thanZero = 0;
    char *zero = new char[2];
    zero[0] = '0';
    zero[1] = '\0';
    for (int i = 0; i < len; i++) {
        int result = string2num_compare(arr[i], zero);
        if (result < 0) {
            arr1[lessZero++] = arr[i];
        } else if (result > 0) {
            arr2[thanZero++] = arr[i];
        } else {
            zeroCount++;
        }
    }
    int count = 0;
    real_big_number_radix_sort(arr1, lessZero, 1);
    //负数倒排
    for (int i = lessZero -1; i >= 0; i--) {
        arr[count++] = arr1[i];
    }
    for (int i = 0; i < zeroCount; i++) {
        arr[count++] = zero;
    }
    
    real_big_number_radix_sort(arr2, thanZero, 0);
    for (int i = 0; i < thanZero; i++) {
        arr[count++] = arr2[i];
    }
}

int main1(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    int len = NUMS_CNT/100;
    char **arr = input_big_number_list(len);

//    big_number_select_sort(arr, len);
//    big_number_merge_sort(arr, len);
//    big_number_quick_sort(arr, len);
//    big_number_shell_sort(arr, len);
    big_number_radix_sort(arr, len);
    
    
    print_big_number_list(arr, len);
    
    
    return 0;
}
