//
//  utils.hpp
//  Sort
//
//  Created by wanggy820 on 2022/11/7.
//

#ifndef utils_hpp
#define utils_hpp

#define NUMS_CNT 10000
#include <stdio.h>

//获取数字num的第i位数
int get_digit(int num, int i);
int string2num_compare(char *a, char *b);

void input_list(int *arr, int len);
void print_list(int *arr, int len);

char** input_big_number_list(int len);
void print_big_number_list(char **arr, int len);
//获取字符串m的第i位数
int get_big_num_digit(char *num, int i);
int MAX(int a, int b);

#endif /* utils_hpp */
