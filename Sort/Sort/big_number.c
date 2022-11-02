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
            if (compare(a[minIndex], a[j]) > 0) {
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

char ** input_big_number_list(char **a, int n) {
    a = malloc(sizeof(char *)*n);
    for (int i = 0; i < n; i++) {
        int rand = arc4random();
        char s[100] = {};
        itoa(rand, s, 10);
        strcat(s, "12321")
        a[i] = s;
    }
    a[0] = "123434567";
    a[1] = "123456324237";
    a[2] = "123314567";
    a[3] = "1233124567";
    a[4] = "123431567";
    a[5] = "1234234567";
    return a;
}

void print_big_number_list(char **a, int n) {
    for (int i = 0; i < n; i++) {
        printf("a[%d] = %s\n", i , a[i]);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    int n = N;
    char **a = malloc(sizeof(char *)*n);
    a[0] = "123434567";
    a[1] = "123456324237";
    a[2] = "123314567";
    a[3] = "1233124567";
    a[4] = "123431567";
    a[5] = "1234234567";
    big_number_select_sort(a, n);
//    merge_sort(a, 0, n-1);
//    quicksort(a, 0, n-1);
//    shell_sort(a, n);
//    radix_sort(a, n);
    
    
    print_big_number_list(a, n);
    
    return 0;
}
