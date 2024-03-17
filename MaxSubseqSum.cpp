#include"MaxSubseqSum.h"
#include <algorithm>

// 分治法处理
int DivideAndConquer(const std::vector<int>& vector,
                     int left, int right)
{
    // 存放左右子问题的解
    int MaxLeftSum, MaxRightSum;
    // 存放跨分界结果
    int MaxLeftBorderSum{0}, MaxRightBorderSum{0};

    int LeftBorderSum{0},RightBorderSum{0};
    int center, i;

    // 递归终止条件，子列只有1个数字
    if (left==right)
    {
        if (vector[left]>0)
        {
            return vector[left];
        }else
        {
            return 0;
        }   
    }

    center=(left+right)/2;
    MaxLeftSum=DivideAndConquer(vector,left,center);
    MaxRightSum=DivideAndConquer(vector,center+1,right);

    // 跨分界线的最大子列和

    // 中线向左
    for (int i=center;i>=left;i--)
    {
        LeftBorderSum+=vector[i];
        if (LeftBorderSum>MaxLeftBorderSum)
        {
            MaxLeftBorderSum=LeftBorderSum;
        }
    }
    // 中线向右
    for (int i = center+1; i <=right; i++)
    {
        RightBorderSum+=vector[i];
        if (RightBorderSum>MaxRightBorderSum)
        {
            MaxRightBorderSum=RightBorderSum;
        }
    }

    return std::max({MaxLeftSum,MaxRightSum
                    ,MaxLeftBorderSum+MaxRightBorderSum});

}

// 在线处理
int MaxSub(const std::vector<int>& vector)
{
    int thisSum{0}, maxSum{0};
    
    for (size_t i = 0; i < vector.size(); i++)
    {
        thisSum+=vector[i];
        if (thisSum>maxSum)
        {
            maxSum=thisSum;
        }else if (thisSum<0)
        {
            thisSum=0;
        }
    }

    return maxSum;
}