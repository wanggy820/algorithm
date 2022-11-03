//
//  utils.h
//  Sort
//
//  Created by wanggy820 on 2022/11/2.
//

#ifndef utils_h
#define utils_h

#include <stdio.h>

struct BigNumber {
    char *value;
    char *virtualV;
};

int get_digit(int M, int i);
int string2num_compare(char *a, char *b);

void input_list(int *a, int n);
void print_list(int *a, int n);

char** input_big_number_list(int n);
void print_big_number_list(char **a, int n);

int get_big_num_digit(char *M, int i);
char* calculate(char *s1, char *s2);
int MAX(int a, int b);
#endif /* utils_h */
