#include <iostream>
#include <vector>
#include <thread>
#include "common_number.h"


#define THRE_CNT 10

using namespace std;

template <class _Fp>
// 分布式选择排序
void distributed_sort(int nums[], int len, _Fp&& __f)
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
        thres[i] = new thread(__f, &temp_nums[i][0], temp_nums[i].size());
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

int main()
{
    // 生成数据集
    vector<int> nums;
    for (int i = 0; i < NUMS_CNT; i++)
    {
        nums.push_back(rand());
    }

    distributed_sort(&nums[0], nums.size(), select_sort);
//    distributed_sort(&nums[0], nums.size(), merge_sort);
//    distributed_sort(&nums[0], nums.size(), quick_sort);
//    distributed_sort(&nums[0], nums.size(), shell_sort);
//    distributed_sort(&nums[0], nums.size(), radix_sort);
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
