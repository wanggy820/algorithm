//
//  big_number.c
//  Sort
//
//  Created by wanggy820 on 2022/11/2.
//

#include <stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <string.h>

#define N 6

void big_number_select_sort(char **a, int n) {
    int minIndex;
    char *tmp;
    for (int i = 0; i < n; i++) {
        minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (string2num_compare(a[minIndex], a[j]) > 0) {
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

void big_number_merge(char **a, int left, int right, int mid) {
    char *s[N];//一个新数组用来存储排序好的数组
    int i = left, j = mid + 1;//两个变量分别指向左边和右边两组数的第一个数
    int sor = left;
    while (i <= mid && j <= right) {
        if (string2num_compare(a[i], a[j]) < 0) {//归并的过程
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


void big_number_merge_sort(char **a,int left,int right){
    if(left < right){
        int mid = (left + right) / 2;//从中间截开
        big_number_merge_sort(a,left, mid);//把左边沿中间截开
        big_number_merge_sort(a, mid + 1, right);//把右边沿中间截开
        big_number_merge(a, left, right, mid);//合并
    }
}

int big_number_partition(char **a,int p,int r) {
    char *x = a[r];
    int i = p - 1;
    char *tmp;
    for (int j = p; j < r; j++) {
        if (string2num_compare(a[j], x) < 0) {
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

void big_number_quick_sort(char **a,int p,int r) {
    if (p < r) {
        int q = big_number_partition(a, p, r);
        big_number_quick_sort(a, p, q-1);
        big_number_quick_sort(a, q+1, r);
    }
}

void big_number_shell_sort(char **a, int n) {
    int d,i,j,index;//d为增量
    char *temp;
    //最外层循环，用来确定增量的多少
    for(d = n/2; d > 0; d = d/2) {
        //外层循环，用来确定要执行多少次直接插入排序
        for(i = 0; i < d; i++) {
            //内层循环，分组后的排序，采用直接插入排序
            for(j = i; j < n; j = j + d) {
                temp = a[j];
                index = j - d;
                while(index >= 0 && string2num_compare(temp, a[index]) < 0) {
                    a[index + d] = a[index];
                    index = index - d;
                }
                a[index + d]=temp;
            }
        }
    }
}

void big_num_clear(char *allot[10][N]) {
    for (int i = 0; i < 10; i++) {
        // 将每个数据的第i位数分配到allot数组中
        for (int j = 0; j < N; j++) {
            allot[i][j] = NULL;
        }
    }
}


/**
    * 基数排序
    * 考虑正负数
    * 为避免出现负数或者0,分开排序
    */
void _big_number_radix_sort(char **num, int n, int isLessZero) {
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
    char *allot[10][N];   // 分配数组
    // 初始化分配数组全为空
    big_num_clear(allot);
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
        big_num_clear(allot);
    }
}

void big_number_radix_sort(char **num, int n) {
    char *num1[N] = {};
    char *num2[N] = {};
    int zeroCount = 0;
    int lessZero = 0;
    int thanZero = 0;
    for (int i = 0; i < n; i++) {
        int result = string2num_compare(num[i], "0");
        if (result < 0) {
            num1[lessZero++] = num[i];
        } else if (result > 0) {
            num2[thanZero++] = num[i];
        } else {
            zeroCount++;
        }
    }
    int count = 0;
    _big_number_radix_sort(num1, lessZero, 1);
    for (int i = lessZero -1; i >= 0; i--) {
        num[count++] = num1[i];
    }
    for (int i = 0; i < zeroCount; i++) {
        num[count++] = "0";
    }
    
    _big_number_radix_sort(num2, thanZero, 0);
    for (int i = 0; i < thanZero; i++) {
        num[count++] = num2[i];
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    int n = N;
    char **a = input_big_number_list(n);

//    big_number_select_sort(a, n);
//    big_number_merge_sort(a, 0, n-1);
//    big_number_quick_sort(a, 0, n-1);
//    big_number_shell_sort(a, n);

    big_number_radix_sort(a, n);
    
    
    print_big_number_list(a, n);
    
    
    return 0;
}
