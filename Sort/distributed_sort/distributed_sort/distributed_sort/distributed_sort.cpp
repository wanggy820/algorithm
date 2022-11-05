#include <iostream>
#include <vector>
#include <thread>

#define NUMS_CNT 10000
#define THRE_CNT 10

using namespace std;

void select_sort(int nums[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < len; j++)
        {
            if (nums[j] < nums[min_idx])
            {
                min_idx = j;
            }
        }
        int temp = nums[i];
        nums[i] = nums[min_idx];
        nums[min_idx] = temp;
    }
}

// 分布式选择排序
void distributed_select_sort(int nums[], int len)
{
    // 划分成多个数组
    vector<int> temp_nums[THRE_CNT];
    int per = len / THRE_CNT;
    int* begin = nums;
    for (int i = 0; i < THRE_CNT - 1; i++)
    {
        temp_nums[i].assign(begin, begin + per);
        begin += per;
    }
    temp_nums[THRE_CNT - 1].assign(begin, nums + len);
    // 分布式选择排序
    thread* thres[THRE_CNT];
    for (int i = 0; i < THRE_CNT; i++)
    {
        thres[i] = new thread(select_sort, &temp_nums[i][0], temp_nums[i].size());
    }
    for (int i = 0; i < THRE_CNT; i++)
    {
        if (thres[i]->joinable())
        {
            thres[i]->join();
        }
    }
    // 归并
    int cur_idx[THRE_CNT] = {0};
    for (int i = 0; i < len; i++)
    {
        int min_thre = 0;
        for (int k = 0; k < THRE_CNT; k++)
        {
            if (cur_idx[k] < temp_nums[k].size())
            {
                min_thre = k;
                break;
            }
        }
        for (int j = 1; j < THRE_CNT; j++)
        {
            if (cur_idx[j] < temp_nums[j].size() && temp_nums[j][cur_idx[j]] < temp_nums[min_thre][cur_idx[min_thre]])
            {
                min_thre = j;
            }
        }
        nums[i] = temp_nums[min_thre][cur_idx[min_thre]];
        cur_idx[min_thre]++;
    }
}

void merge_sort_recursive(int arr[], int reg[], int start, int end) {
    if (start >= end)
        return;
    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge_sort_recursive(arr, reg, start1, end1);
    merge_sort_recursive(arr, reg, start2, end2);
    int k = start;
    while (start1 <= end1 && start2 <= end2)
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    while (start1 <= end1)
        reg[k++] = arr[start1++];
    while (start2 <= end2)
        reg[k++] = arr[start2++];
    for (k = start; k <= end; k++)
        arr[k] = reg[k];
}
void merge_sort(int arr[], int len) {
    auto reg = new int[len];
    merge_sort_recursive(arr, reg, 0, len - 1);
}

// 分布式归并排序
void distributed_merge_sort(int nums[], int len)
{
    // 划分成多个数组
    vector<int> temp_nums[THRE_CNT];
    int per = len / THRE_CNT;
    int* begin = nums;
    for (int i = 0; i < THRE_CNT - 1; i++)
    {
        temp_nums[i].assign(begin, begin + per);
        begin += per;
    }
    temp_nums[THRE_CNT - 1].assign(begin, nums + len);
    // 分布式归并排序
    thread* thres[THRE_CNT];
    for (int i = 0; i < THRE_CNT; i++)
    {
        thres[i] = new thread(merge_sort, &temp_nums[i][0], temp_nums[i].size());
    }
    for (int i = 0; i < THRE_CNT; i++)
    {
        if (thres[i]->joinable())
        {
            thres[i]->join();
        }
    }
    // 归并
    int cur_idx[THRE_CNT] = { 0 };
    for (int i = 0; i < len; i++)
    {
        int min_thre = 0;
        for (int k = 0; k < THRE_CNT; k++)
        {
            if (cur_idx[k] < temp_nums[k].size())
            {
                min_thre = k;
                break;
            }
        }
        for (int j = 1; j < THRE_CNT; j++)
        {
            if (cur_idx[j] < temp_nums[j].size() && temp_nums[j][cur_idx[j]] < temp_nums[min_thre][cur_idx[min_thre]])
            {
                min_thre = j;
            }
        }
        nums[i] = temp_nums[min_thre][cur_idx[min_thre]];
        cur_idx[min_thre]++;
    }
}

int main()
{
    // 生成数据集
    vector<int> nums;
    for (int i = 0; i < NUMS_CNT; i++)
    {
        nums.push_back(rand());
    }
    // 分布式选择排序
    //distributed_select_sort(&nums[0], nums.size());

    // 分布式归并排序
    distributed_merge_sort(&nums[0], nums.size());

    // 验证
    for (int i = 0; i + 1 < nums.size(); i++)
    {
        if (nums[i + 1] < nums[i])
        {
            cout << "faile" << endl;
            return 0;
        }
    }
    std::cout << "sucess" << endl;
    return 0;
}