#Sort

**改排序用C++实现了选择排序，归并排序，快速排序，希尔排序，基数排序，分别可用于小数小量数据、小数大量数据、大数少量数据**

<font color="#660000">common_number.cpp</font><br />  文件封装了
```C++
//选择排序
void select_sort(int *arr, int len);
//归并排序
void merge_sort(int *arr, int len);
//快速排序
void quick_sort(int *arr, int len);
//希尔排序
void shell_sort(int *arr, int len);
//基数排序
void radix_sort(int *arr, int len);
```
其中基数排序考虑到数据可能包含0、负数，先求出最小值和最大值，统一所有值减去最小值并加1，排完序后，再还原数据


<font color="#660000">big_number.cpp</font><br />  文件封装了
```C++
//选择排序
void big_number_select_sort(char **arr, int len);
//归并排序
void big_number_merge_sort(char **arr, int len);
//快速排序
void big_number_quick_sort(char **arr, int len);
//希尔排序
void big_number_shell_sort(char **arr, int len);
//基数排序
void big_number_radix_sort(char **arr, int len);
```
其中基数排序考虑到数据可能包含0、负数，先把正数和负数分开存储在不同数组，分别排序后，负数倒序，并还原0，最后正数正序，才完成排序。

<font color="#660000">distributed_sort.cpp </font><br /> 文件封装了
```C++
// 分布式选择排序
void distributed_sort(int nums[], int len, _Fp&& __f)
```
其中参数 __f 可以传common_number.cpp中实现的排序方法名
把nums分割成10组数据，放到子线程中，分别排序，排序完成后回到主线程，把所有数据归并到原数组中，从而完成排序

