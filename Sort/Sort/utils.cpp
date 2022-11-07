//
//  utils.cpp
//  Sort
//
//  Created by wanggy820 on 2022/11/7.
//

#include "utils.h"
#include <math.h>
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;
//取整数M的第i位数
int get_digit(int m, int i) {
    m = abs(m);
    while(i > 1) {
        m /= 10;
        i--;
    }
    return m % 10;
}


char* itoa(long num,char* str,int radix)
{
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";//索引表
    unsigned unum;//存放要转换的整数的绝对值,转换的整数可能是负数
    int i=0,j,k;//i用来指示设置字符串相应位，转换之后i其实就是字符串的长度；转换后顺序是逆序的，有正负的情况，k用来指示调整顺序的开始位置;j用来指示调整顺序时的交换。
 
    //获取要转换的整数的绝对值
    if(radix==10&&num<0)//要转换成十进制数并且是负数
    {
        unum=(unsigned)-num;//将num的绝对值赋给unum
        str[i++]='-';//在字符串最前面设置为'-'号，并且索引加1
    }
    else unum=(unsigned)num;//若是num为正，直接赋值给unum
 
    //转换部分，注意转换后是逆序的
    do
    {
        str[i++]=index[unum%(unsigned)radix];//取unum的最后一位，并设置为str对应位，指示索引加1
        unum/=radix;//unum去掉最后一位
 
    }while(unum);//直至unum为0退出循环
 
    str[i]='\0';//在字符串最后添加'\0'字符，c语言字符串以'\0'结束。
 
    //将顺序调整过来
    if(str[0]=='-') k=1;//如果是负数，符号不用调整，从符号后面开始调整
    else k=0;//不是负数，全部都要调整
 
    char temp;//临时变量，交换两个值时用到
    for(j=k;j<=(i-1)/2;j++)//头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1
    {
        temp=str[j];//头部赋值给临时变量
        str[j]=str[i-1+k-j];//尾部赋值给头部
        str[i-1+k-j]=temp;//将临时变量的值(其实就是之前的头部值)赋给尾部
    }
    str[i+1] = '\0';
    return str;//返回转换后的字符串
}

//为方便比较假设a,b非空并能转为整数，
int string2num_compare(char *a, char *b) {
    char firstA = a[0];
    char firstB = b[0];
    int signA = firstA == '-' ? -1 : 1;
    int signB = firstB == '-' ? -1 : 1;
    if (signA > 0 && signB < 0) {
        return 1;
    }
    if (signA < 0 && signB > 0) {
        return -1;
    }
    
    size_t aL = strlen(a);
    size_t bL = strlen(b);
    if (aL > bL) {
        return signA;
    }
    if (aL < bL) {
        return -signA;
    }
    int i = 0;
    while (i < aL) {
        i++;
        if (a[i-1] > b[i-1]) {
            return signA;
        }
        if (a[i-1] < b[i-1]) {
            i++;
            return -signA;
        }
    }
    return 0;
}

void input_list(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        int rand = arc4random();
        arr[i] = rand/101;//需要保证数据不溢出
    }
}

void print_list(int *arr, int len) {
    for (int i = 0; i < len; i++) {
//        printf("arr[%3d] = %10d\n", i , arr[i]);
        cout << "arr[" << setw(3) << i << "] == " << setw(10) << arr[i] << endl;
    }
}

#define size 1000
char ** input_big_number_list(int len) {
    char **arr = (char **)malloc(sizeof(char *)*len);
    for (int i = 0; i < len; i++) {
        *(arr+i) = (char *)malloc(sizeof (char)*size);
        int rand1 = arc4random();
        int rand2 = arc4random();
        if (rand2 < 0) {
            rand2 = -rand2;
        }
        char s1[size] = {};
        itoa(rand1, s1, 10);
        char s2[size] = {};
        itoa(rand2, s2, 10);
        strcat(s1, s2);
        strcpy(arr[i], s1);
    }
    return arr;
}

void print_big_number_list(char **arr, int len) {
    for (int i = 0; i < len; i++) {
//        printf("arr[%3d] = %40s\n", i , arr[i]);
        cout << "arr[" << setw(3) << i << "] == " << setw(30) << arr[i] << endl;
    }
}

int MAX(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int get_big_num_digit(char *num, int i) {
    int len = (int)strlen(num);
    if (i > len) {
        return 0;
    }
    if (len == i && num[0] == '-') {
        return 0;
    }
    return num[len - i] - '0';
}
