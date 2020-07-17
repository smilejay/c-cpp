#include <stdio.h>
#define ARRAY_LEN 10

/*
leetcode: 53.maximum-sum-subarray 最大子序列之和

运用动态规划的思想：将其拆解为规模更小的同样问题，并且找出递推关系。

我们不妨假设问题 Q(list, i) 表示 list 中以索引 i 结尾的情况下最大子序列和，
那么原问题就转化为 Q(list, i), 其中 i = 0,1,2…n-1 中的最大值。

我们继续来看下递归关系，即 Q(list, i)和 Q(list, i - 1)的关系，
即如何根据 Q(list, i - 1) 推导出 Q(list, i)。

如果已知 Q(list, i - 1)， 我们可以将问题分为两种情况，即以索引为 i 的元素终止，
或者只有一个索引为 i 的元素。
    如果以索引为 i 的元素终止， 那么就是 Q(list, i - 1) + list[i]
    如果只有一个索引为 i 的元素，那么就是 list[i]
*/

/*
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。
注意：你不能在买入股票前卖出股票。

方法：先将每日的股票价格变成每日的变化量，然后求出最大子序列之和。
*/


int max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

int max_sum_subarray(int* nums, int numsSize)
{
    int max_sum = nums[0];
    int max_sum_ending_curr_index = nums[0];
    for (int i = 1; i < numsSize; i++)
    {
        max_sum_ending_curr_index = max(max_sum_ending_curr_index + nums[i], nums[i]);
        max_sum = max(max_sum_ending_curr_index, max_sum);
    }
    return max_sum;
}


int main(int argc, char const *argv[])
{
    int test_array[ARRAY_LEN] = {1, -2, 3, 1, 4, -3, 4, 5, 8, -1};
    int max_sum = max_sum_subarray(test_array, ARRAY_LEN);
    printf("max_sum is: %d\n", max_sum);
    return 0;
}