// Leetcode刷题记录

// 头文件
#include <bits/stdc++.h> //不建议
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

// 一、基础算法
// 1.二分查找
// 最常用模板 参考https://leetcode-cn.com/leetbook/read/binary-search/xewjg7/
// 二分查找核心四点要素
// 1)初始化：start=0、end=len-1
// 2)循环退出条件：start + 1 < end
// 3)比较中点和目标值：nums[mid] ==、 <、> target
// 4)判断最后两个元素是否符合：nums[start]、nums[end] ? target
// 时间复杂度 O(logn)，使用场景一般是有序数组的查找
int binarySearch_model(vector<int> &nums, int target)
{
    // 1.初始化 start,end
    int start = 0;
    int end = nums.size() - 1;
    // 2.处理循环
    while (start + 1 < end)
    {
        int mid = start + (end - start) / 2;
        // 3.比较
        if (nums[mid] >= target)
            end = mid;
        else
            start = mid;
    }
    // 4.最后剩下的两个元素手动比较
    if (nums[start] == target)
        return start;
    if (nums[end] == target)
        return end;
    return -1;
}

// leetcode 704 二分查找
// 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target,写一个函数搜索 nums 中的 target,如果目标值存在返回下标,否则返回 -1;
int binarySearch(vector<int> &nums, int target)
{
    int start = 0;
    int end = nums.size() - 1;
    while (start + 1 < end)
    {
        int mid = start + (end - start) / 2;
        if (nums[mid] > target)
            end = mid;
        else
            start = mid;
    }
    if (nums[start] == target)
        return start;
    if (nums[end] == target)
        return end;
    return -1;
}

// leetcode 34 在排序数组中查找元素的第一个和最后一个位置
// 给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置,如果数组中不存在目标值，返回 [-1, -1]。
// 思路：核心点就是找第一个 target 的索引，和最后一个 target 的索引，所以用两次二分搜索分别找第一次和最后一次的位置
vector<int> searchRange(vector<int> &nums, int target)
{
    if (nums.empty())
        return {-1, -1};

    int start = 0;
    int end = nums.size() - 1;
    vector<int> ans(2);
    while (start + 1 < end)
    {
        int mid = start + (end - start) / 2;
        if (nums[mid] >= target) //相等 向左搜索
            end = mid;
        else
            start = mid;
    }
    // 搜索左边
    if (nums[start] == target)
        ans[0] = start;
    else if (nums[end] == target)
        ans[0] = end;
    else
    {
        ans[0] = -1;
        ans[1] = -1;
        return ans;
    }

    start = 0, end = nums.size() - 1;
    while (start + 1 < end)
    {
        int mid = start + (end - start) / 2;
        if (nums[mid] <= target) //相等 向右搜索
            start = mid;
        else
            end = mid;
    }
    // 搜索右边
    if (nums[end] == target)
        ans[1] = end;
    else if (nums[start] == target)
        ans[1] = start;
    else
    {
        ans[0] = -1;
        ans[1] = -1;
        return ans;
    }

    return ans;
}

// leetcode 35 搜索插入位置
// 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
int searchInsert(vector<int> &nums, int target)
{
    int start = 0;
    int end = nums.size() - 1;
    while (start + 1 < end)
    {
        int mid = start + (end - start) / 2;
        if (nums[mid] >= target)
            end = mid;
        else
            start = mid;
    }
    if (nums[start] >= target)
        return start;
    else if (nums[end] >= target)
        return end;
    else
        return end + 1;

    return 0;
}

// leetcode 74 搜索二维矩阵
// 编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：
// 每行中的整数从左到右按升序排列。
// 每行的第一个整数大于前一行的最后一个整数。
// 思路：将2纬数组转为1维数组 进行二分搜索
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    if (matrix.empty() || matrix[0].empty())
        return false;

    int row = matrix.size();
    int col = matrix[0].size();

    int start = 0;
    int end = row * col - 1;
    while (start + 1 < end)
    {
        int mid = start + (end - start) / 2;
        if (matrix[mid / col][mid % col] > target)
            end = mid;
        else if (matrix[mid / col][mid % col] < target)
            start = mid;
        else
            return true;
    }
    if (matrix[start / col][start % col] == target || matrix[end / col][end % col] == target)
        return true;
    return false;
}

// leetcode 278 第一个错误的版本
// 你是产品经理，目前正在带领一个团队开发新的产品。不幸的是，你的产品的最新版本没有通过质量检测。由于每个版本都是基于之前的版本开发的，所以错误的版本之后的所有版本都是错的。
// 假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
// 你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version 是否在单元测试中出错。实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。
bool isBadVersion(int version) { return false; }
int firstBadVersion(int n)
{
    int start = 1;
    int end = n;
    while (start + 1 < end)
    {
        int mid = start + (end - start) / 2;
        if (isBadVersion(mid))
            end = mid; //向前搜索
        else
            start = mid;
    }
    if (isBadVersion(start))
        return start;

    return end;
}

// leetcode 153 寻找旋转排序数组中的最小值
// 假设按照升序排序的数组在预先未知的某个点上进行了旋转。( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
// 请找出其中最小的元素。你可以假设数组中不存在重复元素。
int findMin(vector<int> &nums)
{
    if (nums.empty())
        return -1;
    int start = 0;
    int end = nums.size() - 1;
    while (start + 1 < end)
    {
        int mid = start + (end - start) / 2;
        if (nums[mid] >= nums[end]) // 把nums[end]作为target,注意搜索方向
            start = mid;
        else
            end = mid;
    }
    if (nums[start] > nums[end])
        return nums[end];
    return nums[start];
}

// leetcode 154 寻找旋转排序数组中的最小值ii
// 同153，注意数组中存在重复元素
// 思路：跳过重复元素后思路与153相同
int findMin_ii(vector<int> &nums)
{
    if (nums.empty())
        return -1;
    int start = 0;
    int end = nums.size() - 1;
    while (start + 1 < end)
    {
        //去除重复元素
        while (start < end && nums[end] == nums[end - 1])
            end--;
        while (start < end && nums[start] == nums[start + 1])
            start++;

        int mid = start + (end - start) / 2;
        if (nums[mid] >= nums[end])
            start = mid;
        else
            end = mid;
    }
    if (nums[start] > nums[end])
        return nums[end];
    return nums[start];
}

// leetcode 33 搜索旋转排序数组
// 假设按照升序排序的数组在预先未知的某个点上进行了旋转。( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
// 搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。
// 你可以假设数组中不存在重复的元素。你的算法时间复杂度必须是 O(log n) 级别。
// 思路：先找上升区间 再看target是否再上升区间 四种情况
int searchRotationArray(vector<int> &nums, int target)
{
    if (nums.empty())
        return -1;
    int start = 0;
    int end = nums.size() - 1;
    while (start + 1 < end)
    {
        int mid = start + (end - start) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] >= nums[end]) //上升区间在左
        {
            if (nums[mid] > target && nums[start] <= target)
                end = mid;
            else
                start = mid;
        }
        else //上升区间在右
        {
            if (nums[mid] < target && nums[end] >= target)
                start = mid;
            else
                end = mid;
        }
    }
    if (nums[start] == target)
        return start;
    else if (nums[end] == target)
        return end;
    return -1;
}

// leetcode 81 搜索旋转排序数组ii
// 假设按照升序排序的数组在预先未知的某个点上进行了旋转。( 例如，数组 [0,0,1,2,2,5,6] 可能变为 [2,5,6,0,0,1,2] )。
// 编写一个函数来判断给定的目标值是否存在于数组中。若存在返回 true，否则返回 false。
// 思路：去除重复元素后与33相同
bool searchRotationArray_ii(vector<int> &nums, int target)
{
    if (nums.empty())
        return false;
    int start = 0;
    int end = nums.size() - 1;
    while (start + 1 < end)
    {
        //去除重复元素
        while (start < end && nums[end] == nums[end - 1])
            end--;
        while (start < end && nums[start] == nums[start + 1])
            start++;

        int mid = start + (end - start) / 2;
        if (nums[mid] == target)
            return true;
        if (nums[mid] >= nums[end])
        {
            if (nums[mid] > target && nums[start] <= target)
                end = mid;
            else
                start = mid;
        }
        else
        {
            if (nums[mid] < target && nums[end] >= target)
                start = mid;
            else
                end = mid;
        }
    }
    if (nums[start] == target || nums[end] == target)
        return true;
    return false;
}

// *******************************************************************************************************************

// 2.排序算法
// 快速排序
// 1）选取第一个数为基准
// 2）将比基准小的数交换到前面，比基准大的数交换到后面
// 3）对左右区间重复第二步，直到各区间只有一个数
void quickSort(vector<int> &nums, int start, int end)
{
    if (start >= end) //给递归系上安全带
        return;

    int first = start;
    int last = end;
    int key = nums[first]; //选第一个元素作为基准

    while (first < last)
    {
        while (first < last && nums[last] >= key)
            last--;
        if (first < last)
            nums[first++] = nums[last];
        while (first < last && nums[first] <= key)
            first++;
        if (first < last)
            nums[last--] = nums[first];
    }

    nums[first] = key; //找到分界first

    quickSort(nums, start, first - 1);
    quickSort(nums, first + 1, end);
}

// 归并排序
// 把数据分为两段，从两段中逐个选最小的元素移入新数据段的末尾
void mergeSortRecursive(vector<int> &nums, vector<int> &reg, int start, int end)
{
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;

    // 先分
    mergeSortRecursive(nums, reg, start1, end1);
    mergeSortRecursive(nums, reg, start2, end2);

    // 后合
    int i = start;
    while (start1 <= end1 && start2 <= end2)
        reg[i++] = nums[start1] < nums[start2] ? nums[start1++] : nums[start2++]; //谁小合并谁

    //合并剩余部分
    while (start1 <= end1)
        reg[i++] = nums[start1++];

    while (start2 <= end2)
        reg[i++] = nums[start2++];

    for (i = start; i <= end; ++i)
        nums[i] = reg[i];
}

void mergeSort(vector<int> &nums)
{
    vector<int> reg(nums.size());
    mergeSortRecursive(nums, reg, 0, nums.size() - 1);
}

// 堆排序
// 二叉堆其实就是一种特殊的二叉树（完全二叉树），存储在数组里，数组索引作为指针：
// 1）建立大顶堆--将n个元素组成的无序序列构建一个大根堆，
// 2）交换堆元素--交换堆尾元素和堆首元素，使堆尾元素为最大元素；
// 3）重建大顶堆--将前n-1个元素组成的无序序列调整为大根堆
// sink（)下沉函数，调整堆为大顶堆
void sink(vector<int> &nums, int root, int len)
{
    while (1)
    {
        int lSon = 2 * root + 1; // 左子节点索引
        int rSon = 2 * root + 2; // 右子节点索引
        int maxIndex = root;     // 保存跟、左右子节点较大值

        if (lSon < len && nums[lSon] > nums[maxIndex])
            maxIndex = lSon;
        if (rSon < len && nums[rSon] > nums[maxIndex])
            maxIndex = rSon;

        if (root == maxIndex) // 如果根节点较大，则不下沉
            return;

        // 如果根节点较小，交换并下沉
        swap(nums[root], nums[maxIndex]);
        root = maxIndex;
    }
}

void heapSort(vector<int> &nums)
{
    int len = nums.size();
    // 构建大根堆 从最后一个非叶子节点开始
    for (int i = len / 2 - 1; i >= 0; --i)
        sink(nums, i, len);

    // 交换首尾元素，长度减一，循环下沉
    for (int j = len - 1; j > 0; --j) // j最小为1
    {
        swap(nums[0], nums[j]);
        sink(nums, 0, j); // 从根节点开始
    }
}

// *******************************************************************************************************************

// 3.动态规划

// i.矩阵类型
// leetcode 64 最小路径和
// 给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
// 说明：每次只能向下或者向右移动一步。
// 思路：动态规划
// 1)state: f[x][y]从起点走到 x,y 的最短路径
// 2)function: f[x][y] = min(f[x-1][y], f[x][y-1]) + A[x][y]
// 3)intialize: f[0][0] = A[0][0]、f[i][0] = sum(0,0 -> i,0)、 f[0][i] = sum(0,0 -> 0,i)
// 4)answer: f[n-1][m-1]
int minPathSum(vector<vector<int>> &grid)
{
    int m = grid.size();
    int n = grid[0].size();

    // 初始化：f[i][0]、f[0][j]
    for (int i = 1; i < m; ++i)
        grid[i][0] += grid[i - 1][0];

    for (int j = 1; j < n; ++j)
        grid[0][j] += grid[0][j - 1];

    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j];
        }
    }

    return grid[m - 1][n - 1];
}

// leetcode 62 不同路径
// 一个机器人位于一个 m x n 网格的左上角,机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角。问总共有多少条不同的路径？
// 1 <= m, n <= 100
int uniquePaths(int m, int n)
{
    int f[101][101];
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == 0 || j == 0) // 初始化
                f[i][j] = 1;
            else
                f[i][j] = f[i - 1][j] + f[i][j - 1];
        }
    }

    return f[m - 1][n - 1];
}

// leetcode 63 不同路径ii
// 一个机器人位于一个 m x n 网格的左上角 。机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角。现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
// 网格中的障碍物和空位置分别用 1 和 0 来表示
int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    if (obstacleGrid[0][0] == 1)
        return 0;
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    int f[110][110];             // 默认初始化为0，注意大小 leetcode 上有问题
    for (int i = 1; i <= m; ++i) //增加一行一列，不需要初始化初值
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i == 1 && j == 1)
                f[i][j] = 1;
            else
            {
                if (obstacleGrid[i - 1][j - 1] == 1)
                    f[i][j] = 0;
                else
                    f[i][j] = f[i - 1][j] + f[i][j - 1];
            }
        }
    }
    return f[m][n];

    // if (obstacleGrid[0][0] == 1)
    //     return 0;
    // int m = obstacleGrid.size();
    // int n = obstacleGrid[0].size();

    // int f[101][101];
    // // 初始化
    // for (int i = 0; i < m; ++i)
    // {
    //     for (int j = 0; j < n; ++j)
    //         f[i][j] = 1;
    // }
    // // 初始化边缘初值
    // for (int i = 1; i < m; ++i)
    // {
    //     if (obstacleGrid[i][0] == 1 || f[i - 1][0] == 0)
    //         f[i][0] = 0;
    // }
    // for (int j = 1; j < n; ++j)
    // {
    //     if (obstacleGrid[0][j] == 1 || f[0][j - 1] == 0)
    //         f[0][j] = 0;
    // }

    // for (int i = 1; i < m; ++i)
    // {
    //     for (int j = 1; j < n; ++j)
    //     {
    //         if (obstacleGrid[i][j] == 1)
    //             f[i][j] = 0;
    //         else
    //             f[i][j] = f[i - 1][j] + f[i][j - 1];
    //     }
    // }
    // return f[m - 1][n - 1];
}

// ii.序列类型
// 常见处理方式是给 0 位置占位，这样处理问题时一视同仁，初始化则在原来基础上 length+1，返回结果 f[n]
// 状态可以为前 i 个
// 初始化 length+1
// 取值 index=i-1
// 返回值：f[n]或者 f[m][n]

// leetcode 132 分割回文子串ii
// 给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。返回符合要求的最少分割次数。
int minCut(string s)
{
    int l = s.size();
    if (l == 0 || l == 1)
        return 0;
    // state: f[i] "前i"个字符组成的子字符串需要最少几次cut(个数-1为索引)
    int *f = new int[l + 1];
    for (int i = 0; i < l + 1; ++i)
        f[i] = i - 1;

    // 然后从i = range(l)循环一次，每次以s[i]为中心寻找回文子串，当找到从start到end为回文串时，
    // 设置f[end+1]=min(f[start]+1,f[end+1])
    for (int i = 0; i < l; ++i)
    {
        f[i + 1] = min(f[i] + 1, f[i + 1]);
        // if(i==l-1)
        //     break;
        int start = i, end = i + 1;
        while (s[start] == s[end])
        {
            f[end + 1] = min(f[start] + 1, f[end + 1]);
            if (end == l - 1 || start == 0)
                break;
            end++;
            start--;
        }
        start = i - 1, end = i + 1;
        if (start < 0)
            continue;
        while (s[start] == s[end])
        {
            f[end + 1] = min(f[start] + 1, f[end + 1]);
            if (end == l - 1 || start == 0)
                break;
            end++;
            start--;
        }
        if (f[l] == 0)
        {
            return 0;
        }
    }
    return f[l];
}

// leetcode 300 最长上升子序列
int lengthOfLIS(vector<int> &nums)
{
    int l = nums.size();
    if (l == 0 || l == 1)
        return l;
    vector<int> f(l, 1);
    // f[i] 表示从0开始到i结尾的最长序列长度
    for (int i = 1; i < l; ++i)
    {
        for (int j = 0; j < i; ++j)
            if (nums[j] < nums[i])
                f[i] = max(f[j] + 1, f[i]);
    }
    // int maxInd=0;
    // for(int i=0;i<l;++i)
    // {
    //     if(f[i]>f[maxInd])
    //         maxInd=i;
    // }
    // return f[maxInd];
    return *max_element(f.begin(), f.end());
}

// leetcode 139 单词拆分
bool wordBreak(string s, vector<string> &wordDict)
{
    int l = s.size();
    vector<bool> dp(l + 1, false); // dp[i]表示前i个字符是否可被切分
    dp[0] = true;
    for (int i = 0; i <= l; ++i)
    {
        if (dp[i] == false)
            continue;
        for (string &word : wordDict)
        {
            if (s.substr(i).find(word) == 0)
                dp[i + word.size()] = true;
        }
    }
    return dp[l];
}

// iii.双序列类型
// leetcode 1143 最长公共子序列
// 给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。
// 一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
// 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。
// 若这两个字符串没有公共子序列，则返回 0。
// dp[i][j] a前i个和b前j个字符最长公共子序列
// dp[m+1][n+1]
//   ' a d c e
// ' 0 0 0 0 0
// a 0 1 1 1 1
// c 0 1 1 2 1
int longestCommonSubsequence(string text1, string text2)
{
    int m = text1.size();
    int n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            // 相等取左上元素+1，否则取左或上的较大值
            if (text1[i - 1] == text2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

// leetcode 72 编辑距离
// 给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。
// 你可以对一个单词进行如下三种操作：插入一个字符，删除一个字符，替换一个字符。
int minDistance(string word1, string word2)
{
    int m = word1.size();
    int n = word2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= m; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= n; ++j)
        dp[0][j] = j;

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (word1[i - 1] == word2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
        }
    }
    return dp[m][n];
}

// vi.零钱背包类型
// leetcode 322 零钱兑换
// 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。
// 思路：和其他 DP 不太一样，i 表示钱或者容量
// 状态 dp[i]表示金额为i时，组成的最小硬币个数
// 推导 dp[i]  = min(dp[i-1], dp[i-2], dp[i-5])+1, 前提 i-coins[j] > 0
// 初始化为最大值 dp[i]=amount+1
// 返回值 dp[n] or dp[n]>amount =>-1
int coinChange(vector<int> &coins, int amount)
{
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i)
    {
        for (int coin : coins)
        {
            if (i - coin >= 0)
                dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }
    if (dp[amount] > amount)
        return -1;

    return dp[amount];
}

// 背包问题注意点：
// 1）空间优化
// 2）初始化，如果是背包恰好装满，则dp[0]初始化为0，其余为负无穷；如果是最大装多少，则全初始化为0
// 3）循环顺序是顺序还是逆序，循环的起始终止条件
// lintcode 92 背包问题
// 在n个物品中挑选若干物品装入背包，最多能装多满？假设背包的大小为m，每个物品的大小为A[i]
int backPack(int m, vector<int> &A)
{
    vector<vector<bool>> f(A.size() + 1, vector<bool>(m + 1, false));
    f[0][0] = true;
    for (int i = 1; i <= A.size(); ++i)
    {
        for (int j = 0; j <= m; ++j)
        {
            f[i][j] = f[i - 1][j];
            if (j - A[i - 1] >= 0 && f[i - 1][j - A[i - 1]])
                f[i][j] = true;
        }
    }
    for (int i = m; i >= 0; --i)
    {
        if (f[A.size()][i])
            return i;
    }
    return 0;
}

// 0-1背包
// lintcode 125 背包问题ii
// 有 n 个物品和一个大小为 m 的背包. 给定数组 w 表示每个物品的大小和数组 v 表示每个物品的价值.
// 问最多能装入背包的总价值是多大?
// 思路：不放第n个物品，此时总价值为f(n−1,C),放置第n个物品，此时总价值为f(n−1,C−w[n)]+v[n]
int backPack_ii(int m, vector<int> &w, vector<int> &v)
{
    vector<vector<int>> dp(w.size() + 1, vector<int>(m + 1, 0));
    for (int i = 1; i < w.size(); ++i)
    {
        for (int j = 0; j <= m; ++j)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i - 1]) // j<w,背包装不下该物品，最大价值不变
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
        }
    }
    return dp[w.size()][m];
}

// 优化空间 将二维数组降成一维数组
int backPack_ii2(int m, vector<int> &w, vector<int> &v)
{
    vector<int> dp(m + 1, 0);
    for (int i = 1; i < w.size(); ++i)
    {
        for (int j = m; j >= w[i - 1]; --j) // 注意j为逆序 且不需要到0;
            dp[j] = max(dp[j], dp[j - w[i - 1]] + v[i - 1]);
    }
    return dp[m];
}

// 完全背包
// lintcode 440 背包问题iii
// 有 n 个物品和一个大小为 m 的背包. 给定数组 w 表示每个物品的大小和数组 v 表示每个物品的价值.每种物品无限个.
// 问最多能装入背包的总价值是多大?
int backPack_iii(int m, vector<int> &w, vector<int> &v)
{
    vector<vector<int>> dp(w.size() + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= w.size(); ++i)
    {
        for (int j = 0; j <= m; ++j)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i - 1])
                dp[i][j] = max(dp[i][j], dp[i][j - w[i - 1]] + v[i - 1]); // 注意这里转移方程的区别
        }
    }
    return dp[w.size()][m];
}

// 优化空间
int backPack_iii2(int m, vector<int> &w, vector<int> &v)
{
    vector<int> dp(m + 1, 0);
    for (int i = 1; i <= w.size(); ++i)
    {
        for (int j = w[i - 1]; j <= m; ++j) // 注意循环的起始终止
            dp[j] = max(dp[j], dp[j - w[i - 1]] + v[i - 1]);
    }
    return dp[m];
}

// 多重背包
// 有 n 个物品和一个大小为 m 的背包. 给定数组 w 表示每个物品的大小和数组 v 表示每个物品的价值.每种物品n个.
// 问最多能装入背包的总价值是多大?
// 思路：将第i种物品分成若干件物品，可以有(wi,vi),（wi*2,vi*2),(wi*4,vi*4)
// 每件物品有一个系数，分别为1，2，4，2^(k-1),k为满足n-2^k+1>0的最大整数
int backPack_iv(int m, vector<int> &w, vector<int> &v, vector<int> &n)
{
    vector<int> dp(m + 1, 0);
    for (int i = 1; i <= w.size(); i++)
    {
        int num = min(n[i - 1], m / w[i - 1]);
        for (int k = 1; num > 0; k <<= 1)
        {
            if (k > num)
                k = num;
            num -= k;
            for (int j = m; j >= w[i - 1] * k; j--)
                dp[j] = max(dp[j], dp[j - w[i - 1] * k] + v[i - 1] * k);
        }
    }
}

// *******************************************************************************************************************
// *******************************************************************************************************************
// *******************************************************************************************************************

// 二、算法思维
// 1.递归
// leetcode 24 两两交换链表中的节点
// 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
// 思路：将链表翻转转化为一个子问题，然后通过递归方式依次解决
// 先翻转两个，然后将后面的节点继续这样翻转，然后将这些翻转后的节点连接起来
ListNode *swapPairs(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode *nextHead = head->next->next;
    ListNode *pNext = head->next;
    pNext->next = head;
    head->next = swapPairs(nextHead);
    return pNext;
}

// leetcode 95 不同的二叉搜索树ii
// 给定一个整数 n，生成所有由 1 ... n 为节点所组成的 二叉搜索树 。
vector<TreeNode *> generateTrees(int start, int end)
{
    if (start > end)
        return {nullptr};

    vector<TreeNode *> ans;
    for (int i = start; i <= end; ++i)
    {
        vector<TreeNode *> leftTrees = generateTrees(start, i - 1);
        vector<TreeNode *> rightTrees = generateTrees(i + 1, end);

        for (auto &left : leftTrees)
        {
            for (auto &right : rightTrees)
            {
                TreeNode *root = new TreeNode(i);
                root->left = left;
                root->right = right;
                ans.push_back(root);
            }
        }
    }
    return ans;
}

vector<TreeNode *> generateTrees(int n)
{
    if (n == 0)
        return {};

    return generateTrees(1, n);
}

// *******************************************************************************************************************

// 2.滑动窗口
// 和双指针题目类似，更像双指针的升级版，滑动窗口核心点是维护一个窗口集，根据窗口集来进行处理
// 核心步骤
// 1)右指针右移之后窗口数据更新
// 2)判断窗口是否要收缩
// 3)左指针右移之后窗口数据更新
// 4)根据题意计算结果

// leetcode 76 最小覆盖字串
// 给你一个字符串 S、一个字符串 T 。请你设计一种算法，可以在 O(n) 的时间复杂度内，从字符串 S 里面找出：包含 T 所有字符的最小子串。
string minWindow(string s, string t)
{
    unordered_map<char, int> sFreq;
    unordered_map<char, int> tFreq;

    for (auto &c : t) // 初始化
        tFreq[c]++;

    int l = 0, r = 0, distance = 0; // distance用作计数
    int minLen = s.size() + 1;
    int start = 0;

    while (r < s.size())
    {
        if (tFreq[s[r]] == 0) // 不匹配
        {
            r++;
            continue;
        }
        if (sFreq[s[r]] < tFreq[s[r]])
            distance++;
        sFreq[s[r]]++;
        r++;

        while (distance == t.size()) // 当窗口包含所有需要的字符
        {
            if (r - l < minLen)
            {
                minLen = r - l;
                start = l; // 记录开始点
            }

            if (tFreq[s[l]] == 0)
            {
                l++;
                continue;
            }
            if (sFreq[s[l]] == tFreq[s[l]])
                distance--;
            sFreq[s[l]]--;
            l++;
        }
    }
    if (minLen == s.size() + 1)
        return "";
    return s.substr(start, minLen);
}

// leetcode 567 字符串的排列
// 给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。换句话说，第一个字符串的排列之一是第二个字符串的子串。
bool checkInclusion(string s1, string s2)
{
    unordered_map<char, int> s1Frep;
    unordered_map<char, int> s2Frep;

    for (auto &c : s1)
        s1Frep[c]++;

    int l = 0, r = 0, distance = 0;

    while (r < s2.size())
    {
        if (s1Frep[s2[r]] == 0)
        {
            r++;
            continue;
        }
        if (s2Frep[s2[r]] < s1Frep[s2[r]])
            distance++;
        s2Frep[s2[r]]++;
        r++;
        while (distance == s1.size())
        {
            if (r - l == s1.size())
                return true;
            if (s1Frep[s2[l]] == 0)
            {
                l++;
                continue;
            }
            if (s2Frep[s2[l]] == s1Frep[s2[l]])
                distance--;
            s2Frep[s2[l]]--;
            l++;
        }
    }
    return false;
}

// leetcode 438 找到字符串中所有字母异位词
vector<int> findAnagrams(string s, string p)
{
    unordered_map<char, int> sFreq;
    unordered_map<char, int> pFrep;
    vector<int> ans;

    for (auto &c : p)
        pFrep[c]++;

    int l = 0, r = 0, distance = 0;

    while (r < s.size())
    {
        if (pFrep[s[r]] == 0)
        {
            r++;
            continue;
        }
        if (sFreq[s[r]] < pFrep[s[r]])
            distance++;
        sFreq[s[r]]++;
        r++;

        while (distance == p.size())
        {
            if (r - l == p.size())
                ans.push_back(l);

            if (pFrep[s[l]] == 0)
            {
                l++;
                continue;
            }
            if (sFreq[s[l]] == pFrep[s[l]])
                distance--;
            sFreq[s[l]]--;
            l++;
        }
    }
    return ans;
}

// leetcode 无重复字符的最长子串
// 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
int lengthOfLongestSubstring(string s)
{
    unordered_map<char, int> sFreq;

    int l = 0, r = 0;
    int maxLen = 0;
    while (r < s.size())
    {
        char c = s[r];
        r++;
        sFreq[c]++;
        while (sFreq[c] > 1)
        {
            sFreq[s[l]]--;
            l++;
        }
        maxLen = max(maxLen, r - l);
    }
    return maxLen;
}

// *******************************************************************************************************************

// 3.回溯
// 非常好 https://leetcode-cn.com/problems/subsets/solution/c-zong-jie-liao-hui-su-wen-ti-lei-xing-dai-ni-gao-/
// DFS是一个劲的往某一个方向搜索，而回溯算法建立在DFS基础之上的，但不同的是在搜索过程中，达到结束条件后，恢复状态，回溯上一层，再次搜索。因此回溯算法与DFS的区别就是有无状态重置。
// 即满足结束条件或者发现不是正确路径的时候(走不通)，要撤销选择，回退到上一个状态，继续尝试，直到找出所有解为止.
// 核心步骤:
// 1）画出递归树，找到状态变量(回溯函数的参数)，这一步非常重要※
// 2）根据题意，确立结束条件
// 3）找准选择列表(与函数参数相关),与第一步紧密关联※
// 4）判断是否需要剪枝
// 5)作出选择，递归调用，进入下一层
// 6)撤销选择
// 类型：子集、组合，全排列，搜索

// 子集问题
// 子集、组合类问题，关键是用一个start参数来控制选择列表
// leetcode 78 子集
// 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。解集不能包含重复的子集。
void backTrack_78(vector<int> &nums, vector<int> &track, int start, vector<vector<int>> &ans);
vector<vector<int>> subsets(vector<int> &nums)
{
    vector<vector<int>> ans;
    vector<int> track;
    backTrack_78(nums, track, 0, ans);
    return ans;
}
void backTrack_78(vector<int> &nums, vector<int> &track, int start, vector<vector<int>> &ans)
{
    ans.push_back(track);
    for (int i = start; i < nums.size(); ++i) // 选择列表
    {
        track.push_back(nums[i]);              // 做出选择
        backTrack_78(nums, track, i + 1, ans); // //递归进入下一层，注意i+1，标识下一个选择列表的开始位置，最重要的一步
        track.pop_back();                      // 撤销选择
    }
}

// leetcode 90 子集 II
// 给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。解集不能包含重复的子集。
void backTrack_90(vector<int> &nums, vector<int> &track, int start, vector<vector<int>> &ans);
vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    vector<int> track;
    backTrack_90(nums, track, 0, ans);
    return ans;
}
void backTrack_90(vector<int> &nums, vector<int> &track, int start, vector<vector<int>> &ans)
{
    ans.push_back(track);
    for (int i = start; i < nums.size(); ++i)
    {
        if (i > start && nums[i] == nums[i - 1]) // 剪枝去重（必须先排序）
            continue;
        track.push_back(nums[i]);
        backTrack_90(nums, track, i + 1, ans);
        track.pop_back();
    }
}

// 组合问题
// leetcode 77 组合
// 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
void backTrack_77(vector<int> &track, int n, int k, int start, vector<vector<int>> &ans);
vector<vector<int>> combine(int n, int k)
{
    vector<vector<int>> ans;
    vector<int> track;
    backTrack_77(track, n, k, 1, ans);
    return ans;
}
void backTrack_77(vector<int> &track, int n, int k, int start, vector<vector<int>> &ans)
{
    if (track.size() == k)
    {
        ans.push_back(track);
        return;
    }
    for (int i = start; i <= n; ++i)
    {
        track.push_back(i);
        backTrack_77(track, n, k, i + 1, ans);
        track.pop_back();
    }
}

// leetcode 39 组合总和
// 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
// candidates 中的数字可以无限制重复被选取。
void backTrack_39(vector<int> &candidates, vector<int> &track, int target, int sum, int start, vector<vector<int>> &ans);
vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    vector<vector<int>> ans;
    vector<int> track;
    backTrack_39(candidates, track, target, 0, 0, ans);
    return ans;
}
void backTrack_39(vector<int> &candidates, vector<int> &track, int target, int sum, int start, vector<vector<int>> &ans)
{
    if (sum == target)
    {
        ans.push_back(track);
        return;
    }
    for (int i = start; i < candidates.size(); ++i)
    {
        if (sum > target)
            return;
        track.push_back(candidates[i]);
        backTrack_39(candidates, track, target, sum + candidates[i], i, ans);
        track.pop_back();
    }
}

// leetcode 40 组合总和 II
// 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
// candidates 中的每个数字在每个组合中只能使用一次。
void backTrack_40(vector<int> &candidates, vector<int> &track, int target, int sum, int start, vector<vector<int>> &ans);
vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
    vector<vector<int>> ans;
    sort(candidates.begin(), candidates.end());
    vector<int> track;
    backTrack_40(candidates, track, target, 0, 0, ans);
    return ans;
}
void backTrack_40(vector<int> &candidates, vector<int> &track, int target, int sum, int start, vector<vector<int>> &ans)
{
    if (sum == target)
    {
        ans.push_back(track);
        return;
    }
    for (int i = start; i < candidates.size(); ++i)
    {
        if (sum > target)
            return;
        if (i > start && candidates[i] == candidates[i - 1])
            continue;
        track.push_back(candidates[i]);
        backTrack_40(candidates, track, target, sum + candidates[i], i + 1, ans);
        track.pop_back();
    }
}

// leetcode 17 电话号码的字母组合
// 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
// 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
void backTrack_17(string &digits, map<int, string> &mp, string &track, int index, vector<string> &ans);
vector<string> letterCombinations(string digits)
{
    if (digits.empty())
        return {};
    map<int, string> mp = {{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
    string track;
    vector<string> ans;
    backTrack_17(digits, mp, track, 0, ans);
    return ans;
}
void backTrack_17(string &digits, map<int, string> &mp, string &track, int index, vector<string> &ans)
{
    if (index == digits.size())
    {
        ans.push_back(track);
        return;
    }
    for (int i = 0; i < mp[digits[index]].size(); ++i)
    {
        track.push_back(mp[digits[index]][i]);
        backTrack_17(digits, mp, track, index + 1, ans);
        track.pop_back();
    }
}

// 排列问题
// “排列”类型问题和“子集、组合”问题不同在于：“排列”问题使用used数组来标识选择列表，而“子集、组合”问题则使用start参数。另外还需注意两种问题的判重剪枝！！
// leetcode 46 全排列
// 给定一个 没有重复 数字的序列，返回其所有可能的全排列。
void backTrack_46(vector<int> &nums, vector<int> &track, vector<bool> &visited, vector<vector<int>> &ans);
vector<vector<int>> permute(vector<int> &nums)
{
    vector<vector<int>> ans;
    vector<int> track;
    vector<bool> visited(nums.size(), false);
    backTrack_46(nums, track, visited, ans);
    return ans;
}
void backTrack_46(vector<int> &nums, vector<int> &track, vector<bool> &visited, vector<vector<int>> &ans)
{
    if (track.size() == nums.size())
    {
        ans.push_back(track);
        return;
    }
    for (int i = 0; i < nums.size(); ++i)
    {
        if (!visited[i])
        {
            track.push_back(nums[i]);
            visited[i] = true;
            backTrack_46(nums, track, visited, ans);
            track.pop_back();
            visited[i] = false;
        }
    }
}

// leetcode 47 全排列 II
// 给定一个可包含重复数字的序列，返回所有不重复的全排列。
void backTrack_47(vector<int> &nums, vector<int> &track, vector<bool> &visited, vector<vector<int>> &ans);
vector<vector<int>> permuteUnique(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    vector<int> track;
    vector<bool> visited(nums.size(), false);
    backTrack_47(nums, track, visited, ans);
    return ans;
}
void backTrack_47(vector<int> &nums, vector<int> &track, vector<bool> &visited, vector<vector<int>> &ans)
{
    if (track.size() == nums.size())
    {
        ans.push_back(track);
        return;
    }
    for (int i = 0; i < nums.size(); ++i)
    {
        if (!visited[i])
        {
            if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]) // 排序过后，三个判断条件去重
                continue;
            track.push_back(nums[i]);
            visited[i] = true;
            backTrack_47(nums, track, visited, ans);
            track.pop_back();
            visited[i] = false;
        }
    }
}

// leetcode 剑指 Offer 38. 字符串的排列
// 输入一个字符串，打印出该字符串中字符的所有排列。你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
void backTrack_38(string &s, string &track, vector<bool> &visited, vector<string> &ans);
vector<string> permutation(string s)
{
    sort(s.begin(), s.end());
    vector<string> ans;
    string track;
    vector<bool> visited(s.size(), false);
    backTrack_38(s, track, visited, ans);
    return ans;
}
void backTrack_38(string &s, string &track, vector<bool> &visited, vector<string> &ans)
{
    if (track.size() == s.size())
    {
        ans.push_back(track);
        return;
    }
    for (int i = 0; i < s.size(); ++i)
    {
        if (!visited[i])
        {
            if (i > 0 && s[i] == s[i - 1] && !visited[i - 1])
                continue;
            track.push_back(s[i]);
            visited[i] = true;
            backTrack_38(s, track, visited, ans);
            track.pop_back();
            visited[i] = false;
        }
    }
}

// leetcode 784 字母大小写全排列
// 给定一个字符串S，通过将字符串S中的每个字母转变大小写，我们可以获得一个新的字符串。返回所有可能得到的字符串集合。
// 本体代码较为繁琐，主要为了体现回溯思想
void backTrack_784(string &s, string &track, int index, vector<string> &ans);
vector<string> letterCasePermutation(string S)
{
    vector<string> ans;
    string track;
    backTrack_784(S, track, 0, ans);
    return ans;
}
void backTrack_784(string &s, string &track, int index, vector<string> &ans)
{
    if (track.size() == s.size())
    {
        ans.push_back(track);
        return;
    }
    if (isupper(s[index]))
    {
        track.push_back(s[index]);
        backTrack_784(s, track, index + 1, ans);
        track.pop_back();

        track.push_back(tolower(s[index]));
        backTrack_784(s, track, index + 1, ans);
        track.pop_back();
    }
    else if (islower(s[index]))
    {
        track.push_back(s[index]);
        backTrack_784(s, track, index + 1, ans);
        track.pop_back();

        track.push_back(toupper(s[index]));
        backTrack_784(s, track, index + 1, ans);
        track.pop_back();
    }
    else
    {
        track.push_back(s[index]);
        backTrack_784(s, track, index + 1, ans);
        track.pop_back();
    }
}

// 搜索问题
// leetcode 131 分割回文串
// 给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。返回 s 所有可能的分割方案。
bool isPalindrome(string &s, int start, int end);
void backTrack_131(string &s, vector<string> &track, int start, vector<vector<string>> &ans);
vector<vector<string>> partition(string s)
{
    vector<vector<string>> ans;
    vector<string> track;
    backTrack_131(s, track, 0, ans);
    return ans;
}

void backTrack_131(string &s, vector<string> &track, int start, vector<vector<string>> &ans)
{
    if (start == s.size()) // start表示分割的位置
    {
        ans.push_back(track);
        return;
    }
    for (int i = start; i < s.size(); ++i)
    {
        if (!isPalindrome(s, start, i))
            continue;
        track.push_back(s.substr(start, i - start + 1));
        backTrack_131(s, track, i + 1, ans);
        track.pop_back();
    }
}

bool isPalindrome(string &s, int start, int end)
{
    while (start < end)
    {
        if (s[start] != s[end])
            return false;
        start++;
        end--;
    }
    return true;
}

// leetcode 79 单词搜索
// 给定一个二维网格和一个单词，找出该单词是否存在于网格中。
// 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
bool backTrack_79(vector<vector<char>> &board, string &word, vector<vector<bool>> &visited, int rows, int cols, int row, int col, int pathLen);
bool exist(vector<vector<char>> &board, string word)
{
    int rows = board.size();
    int cols = board[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            if (backTrack_79(board, word, visited, rows, cols, row, col, 0))
                return true;
        }
    }
    return false;
}
bool backTrack_79(vector<vector<char>> &board, string &word, vector<vector<bool>> &visited, int rows, int cols, int row, int col, int pathLen)
{
    if (pathLen == word.size())
    {
        return true;
    }
    bool haspath = false;
    if (row >= 0 && row < rows && col >= 0 && col < cols && board[row][col] == word[pathLen] && !visited[row][col])
    {
        pathLen++;
        visited[row][col] = true;
        haspath = backTrack_79(board, word, visited, rows, cols, row + 1, col, pathLen) || backTrack_79(board, word, visited, rows, cols, row - 1, col, pathLen) || backTrack_79(board, word, visited, rows, cols, row, col + 1, pathLen) || backTrack_79(board, word, visited, rows, cols, row, col - 1, pathLen);

        if (!haspath)
        {
            pathLen--;
            visited[row][col] = false;
        }
    }
    return haspath;
}

// leetcode 401 二进制手表
// 二进制手表顶部有 4 个 LED 代表 小时（0-11），底部的 6 个 LED 代表 分钟（0-59）。
// 每个 LED 代表一个 0 或 1，最低位在右侧。
int countOne(int num);
vector<string> readBinaryWatch(int num)
{
    vector<string> ans;
    vector<int> cnt(60);
    for (int i = 0; i < 60; ++i)
        cnt[i] = countOne(i);

    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 60; ++j)
        {
            if (cnt[i] + cnt[j] == num)
                ans.push_back(to_string(i) + ":" + (j < 10 ? "0" + to_string(j) : to_string(j)));
        }
    }
    return ans;
}
int countOne(int num)
{
    int cnt = 0;
    while (num)
    {
        cnt += num & 1;
        num = num >> 1;
    }
    return cnt;
}

// leetcode 93 复原IP地址
// 给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
// 有效的 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。
// 例如："0.1.2.201" 和 "192.168.1.1" 是 有效的 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效的 IP 地址。
bool isValidIP(string &s, int left, int right);
void backTrack_93(string &s, string &track, int pointNum, int lastPos, vector<string> &ans);
vector<string> restoreIpAddresses(string s)
{
    if (s.empty())
        return {};
    string track(s);
    vector<string> ans;
    backTrack_93(s, track, 0, -1, ans);
    return ans;
}

void backTrack_93(string &s, string &track, int pointNum, int lastPos, vector<string> &ans)
{
    if (pointNum == 3)
    {
        if (isValidIP(s, lastPos + 1, s.size() - 1))
            ans.push_back(track);
        return;
    }
    for (int i = lastPos + 1; i < s.size() - 1; ++i)
    {
        if (!isValidIP(s, lastPos + 1, i))
            return;
        track.insert(track.begin() + pointNum + i + 1, '.');
        backTrack_93(s, track, pointNum + 1, i, ans);
        track.erase(pointNum + i + 1, 1);
    }
}

bool isValidIP(string &s, int left, int right)
{
    string split = s.substr(left, right - left + 1);
    if (split.size() > 3)
        return false;
    int n = stoi(split);
    if (n <= 255 && !(left != right && split[0] == '0'))
        return true;
    return false;
}

// 三、数据结构
// 1.链表
// 核心点
// null/nil 异常处理
// dummy node 哑巴节点(注意new后要delete)
// 快慢指针
// 插入一个节点到排序链表
// 从一个链表中移除一个节点
// 翻转链表
// 合并两个链表
// 找到链表的中间节点(两种优劣)

// leetcode 83 删除排序链表中的重复元素
// 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。
ListNode *deleteDuplicates(ListNode *head)
{
    ListNode *pNode = head;
    while (pNode != nullptr)
    {
        while (pNode->next != nullptr && pNode->val == pNode->next->val)
            pNode->next = pNode->next->next;
        pNode = pNode->next;
    }
    return head;
}

// leetcode 82 删除排序链表中的重复元素 II
// 给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。
// 思路：链表头结点可能被删除，所以用 dummy node 辅助删除
// 注意点 • A->B->C 删除 B，A.next = C • 删除用一个 Dummy Node 节点辅助（允许头节点可变） • 访问 X.next 、X.value 一定要保证 X != nil
ListNode *deleteDuplicates_ii(ListNode *head)
{
    ListNode *dummyNode = new ListNode(-1);
    dummyNode->next = head;
    ListNode *pNode = dummyNode;
    while (pNode->next != nullptr && pNode->next->next != nullptr)
    {
        if (pNode->next->val == pNode->next->next->val)
        {
            int value = pNode->next->val;
            while (pNode->next != nullptr && pNode->next->val == value)
                pNode->next = pNode->next->next;
        }
        else
            pNode = pNode->next;
    }
    pNode = dummyNode->next;
    delete dummyNode;
    dummyNode == nullptr;
    return pNode;
}

// leetcode 206 反转链表
// 反转一个单链表。
ListNode *reverseList(ListNode *head)
{
    ListNode *pPrev = nullptr;
    ListNode *pNode = head;
    while (pNode != nullptr)
    {
        ListNode *pNext = pNode->next;
        pNode->next = pPrev;
        pPrev = pNode;
        pNode = pNext;
    }
    return pPrev;
}

// leetcode 92 反转链表 II
// 反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。
// 思路：先遍历到 m 处，翻转，再拼接后续，注意指针处理
ListNode *reverseBetween(ListNode *head, int m, int n)
{
    if (head == nullptr)
        return head;

    ListNode *dummyNode = new ListNode(0);
    dummyNode->next = head;
    ListNode *pNode = dummyNode;
    ListNode *pPrev = nullptr;
    for (int i = 0; i < m; ++i)
    {
        pPrev = pNode;
        pNode = pNode->next;
    }
    ListNode *mid = pNode;
    ListNode *pNext = nullptr;
    for (int i = m; i <= n; ++i)
    {
        ListNode *tmp = pNode->next;
        pNode->next = pNext;
        pNext = pNode;
        pNode = tmp;
    }
    pPrev->next = pNext;
    mid->next = pNode;
    pNode = dummyNode->next;
    delete dummyNode;
    dummyNode = nullptr;
    return pNode;
}

// leetcode 21 合并两个有序链表
// 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    ListNode *dummyNode = new ListNode(0);
    ListNode *pNode = dummyNode;
    while (l1 != nullptr && l2 != nullptr)
    {
        if (l1->val < l2->val)
        {
            pNode->next = l1;
            l1 = l1->next;
            pNode = pNode->next;
        }
        else
        {
            pNode->next = l2;
            l2 = l2->next;
            pNode = pNode->next;
        }
    }
    pNode->next = l1 != nullptr ? l1 : l2;
    pNode = dummyNode->next;
    delete dummyNode;
    dummyNode = nullptr;
    return pNode;
}

// leetcode 86 分隔链表
// 给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。
// 思路：将大于 x 的节点，放到另外一个链表，最后连接这两个链表
ListNode *partition(ListNode *head, int x)
{
    if (head == nullptr)
        return nullptr;
    ListNode *dummyNode = new ListNode(0);
    ListNode *tailNode = new ListNode(0);
    dummyNode->next = head;
    ListNode *pNode = dummyNode;
    ListNode *tail = tailNode;
    while (pNode->next != nullptr)
    {
        if (pNode->next->val >= x)
        {
            tail->next = pNode->next;
            tail = tail->next;
            pNode->next = pNode->next->next;
        }
        else
            pNode = pNode->next;
    }
    tail->next = nullptr;
    pNode->next = tailNode->next;
    pNode = dummyNode->next;

    delete dummyNode;
    dummyNode = nullptr;
    delete tailNode;
    tailNode = nullptr;

    return pNode;
}

// leetcode 148 排序链表
// 在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。
// 思路：归并排序，找中点和合并操作
// 快慢指针 判断 fast 及 fast.Next 是否为 nil 值
// 递归 mergeSort 需要断开中间节点
// 递归返回条件为 head 为 nil 或者 head.Next 为 nil
ListNode *mergeSortList(ListNode *head);
ListNode *findMidNode(ListNode *head);
ListNode *mergeTwoOrderedLists(ListNode *l1, ListNode *l2);
ListNode *sortList(ListNode *head)
{
    return mergeSortList(head);
}

ListNode *mergeSortList(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode *mid = findMidNode(head);
    ListNode *tail = mid->next;
    mid->next = nullptr;
    ListNode *left = mergeSortList(head);
    ListNode *right = mergeSortList(tail);

    return mergeTwoOrderedLists(left, right);
}

ListNode *findMidNode(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode *mergeTwoOrderedLists(ListNode *l1, ListNode *l2)
{
    ListNode *dummyNode = new ListNode(0);
    ListNode *pNode = dummyNode;
    while (l1 != nullptr && l2 != nullptr)
    {
        if (l1->val < l2->val)
        {
            pNode->next = l1;
            l1 = l1->next;
            pNode = pNode->next;
        }
        else
        {
            pNode->next = l2;
            l2 = l2->next;
            pNode = pNode->next;
        }
    }
    pNode->next = l1 == nullptr ? l2 : l1;
    pNode = dummyNode->next;
    delete dummyNode;
    dummyNode = nullptr;
    return pNode;
}

// leetcode 143 重排链表
// 给定一个单链表 L：L0→L1→…→Ln-1→Ln ，将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…
// 思路：找到中点断开，翻转后面部分，然后合并前后两个链表
// 找中间节点的另外一种方式是 fast=head,slow=head
// 这两种方式不同点在于，一般用 fast=head.Next 较多，因为这样可以知道中点的上一个节点，可以用来删除等操作。
// fast 如果初始化为 head.Next 则中点在 slow.Next
// fast 初始化为 head,则中点在 slow

void reorderList(ListNode *head)
{
    if (head == nullptr)
        return;
    ListNode *mid = findMidNode(head);
    ListNode *tail = reverseList(mid->next);
    mid->next = nullptr;
    head = mergeLists(head, tail);
}

ListNode *findMidNode(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode *reverseList(ListNode *head)
{
    ListNode *pPrev = nullptr;
    ListNode *pNode = head;
    while (pNode != nullptr)
    {
        ListNode *pNext = pNode->next;
        pNode->next = pPrev;
        pPrev = pNode;
        pNode = pNext;
    }
    return pPrev;
}

ListNode *mergeLists(ListNode *l1, ListNode *l2)
{
    ListNode *dummyNode = new ListNode(0);
    ListNode *pNode = dummyNode;
    bool flag = true;
    while (l1 != nullptr && l2 != nullptr)
    {
        if (flag)
        {
            pNode->next = l1;
            pNode = pNode->next;
            l1 = l1->next;
        }
        else
        {
            pNode->next = l2;
            pNode = pNode->next;
            l2 = l2->next;
        }
        flag = !flag;
    }
    pNode->next = l1 != nullptr ? l1 : l2;
    pNode = dummyNode->next;
    delete dummyNode;
    dummyNode = nullptr;
    return pNode;
}

// leetcode 141 环形链表
// 给定一个链表，判断链表中是否有环。
// 为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
// 思路：快慢指针，快慢指针相同则有环，证明：如果有环每走一步快慢指针距离会减 1
bool hasCycle(ListNode *head)
{
    if (head == nullptr)
        return false;

    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        if (slow == fast)
            return true;
        slow = slow->next;
        fast = fast->next->next;
    }
    return false;
}

// leetcode 142 环形链表 II
// 给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
// 为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
// 说明：不允许修改给定的链表。
// 思路：快慢指针，快慢相遇之后，慢指针回到头，快慢指针步调一致一起移动，相遇点即为入环点
// 注意点
// 指针比较时直接比较对象，不要用值比较，链表中有可能存在重复值情况
// 第一次相交后，快指针需要从下一个节点开始和头指针一起匀速移动
ListNode *detectCycle(ListNode *head)
{
    if (head == nullptr)
        return nullptr;

    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        if (slow == fast)
        {
            slow = head;
            fast = fast->next;
            while (fast != slow)
            {
                fast = fast->next;
                slow = slow->next;
            }
            return slow;
        }
        fast = fast->next->next;
        slow = slow->next;
    }
    return nullptr;
}

// leetcode 234 回文链表
// 请判断一个链表是否为回文链表。
bool isPalindrome(ListNode *head)
{
    if (head == nullptr)
        return true;

    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *tail = reverseList(slow->next);
    slow->next = nullptr;
    while (head != nullptr && tail != nullptr)
    {
        if (head->val != tail->val)
            return false;
        head = head->next;
        tail = tail->next;
    }
    return true;
}

ListNode *reverseList(ListNode *head)
{
    ListNode *pPrev = nullptr;
    ListNode *pNode = head;
    while (pNode != nullptr)
    {
        ListNode *pNext = pNode->next;
        pNode->next = pPrev;
        pPrev = pNode;
        pNode = pNext;
    }
    return pPrev;
}

// leetcode 138 复制带随机指针的链表
// 给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。要求返回这个链表的 深拷贝。 
// 我们用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：
// val：一个表示 Node.val 的整数。
// random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
Node *copyRandomList(Node *head)
{
    if (head == nullptr)
        return head;

    Node *pNode = head;
    while (pNode != nullptr)
    {
        Node *pClonedNode = new Node(pNode->val);
        pClonedNode->next = pNode->next;

        pNode->next = pClonedNode;
        pNode = pClonedNode->next;
    }

    pNode = head;
    while (pNode != nullptr)
    {
        if (pNode->random != nullptr)
            pNode->next->random = pNode->random->next; // 很关键
        pNode = pNode->next->next;
    }

    pNode = head;
    Node *pClonedHead = head->next;
    while (pNode != nullptr && pNode->next != nullptr)
    {
        Node *tmp = pNode->next;
        pNode->next = pNode->next->next;
        pNode = tmp;
    }
    return pClonedHead;
}

// 3.栈和队列
// 栈的特点是后入先出,根据这个特点可以临时保存一些数据，之后用到依次再弹出来，常用于 DFS 深度搜索
// 队列一般常用于 BFS 广度搜索，类似一层一层的搜索

// stack 栈
class MinStack
{
public:
    /** initialize your data structure here. */
    MinStack()
    {
    }

    void push(int x)
    {
        m_data.push(x);
        if (m_min.empty() || x < m_min.top())
            m_min.push(x);
        else
            m_min.push(m_min.top());
    }

    void pop()
    {
        m_data.pop();
        m_min.pop();
    }

    int top()
    {
        return m_data.top();
    }

    int getMin()
    {
        return m_min.top();
    }

private:
    stack<int> m_data;
    stack<int> m_min;
};

// leetcode 150 逆波兰表达式求值
// 根据 逆波兰表示法，求表达式的值。有效的运算符包括 +, -, *, / 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。
int evalRPN(vector<string> &tokens)
{
    stack<int> sk;
    int a, b;
    for (auto &s : tokens)
    {
        if (s == "+")
        {
            a = sk.top();
            sk.pop();
            b = sk.top();
            sk.pop();
            sk.push(b + a);
        }
        else if (s == "-")
        {
            a = sk.top();
            sk.pop();
            b = sk.top();
            sk.pop();
            sk.push(b - a);
        }
        else if (s == "*")
        {
            a = sk.top();
            sk.pop();
            b = sk.top();
            sk.pop();
            sk.push(b * a);
        }
        else if (s == "/")
        {
            a = sk.top();
            sk.pop();
            b = sk.top();
            sk.pop();
            sk.push(b / a);
        }
        else
            sk.push(atoi(s.c_str()));
    }
    return sk.top();
}

// leetcode 394 字符串解码
// 给定一个经过编码的字符串，返回它解码后的字符串。
// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。
string decodeString(string s)
{
    stack<int> numSk;
    stack<string> ansSk;
    int num = 0;
    string ans;
    for (int i = 0; i < s.size(); ++i)
    {
        if (isalpha(s[i]))
            ans.push_back(s[i]);
        else if (isdigit(s[i]))
            num = 10 * num + s[i] - '0'; // 注意这里的10* 可能是多位数
        else if (s[i] == '[')
        {
            ansSk.push(ans);
            ans = "";
            numSk.push(num);
            num = 0;
        }
        else
        {
            for (int j = 0; j < numSk.top(); ++j)
                ansSk.top() += ans;
            numSk.pop();
            ans = ansSk.top();
            ansSk.pop();
        }
    }
    return ans;
}

// leetcode 94 二叉树的中序遍历
// 给定一个二叉树，返回它的中序 遍历。
vector<int> inorderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return {};
    stack<TreeNode *> sk;
    vector<int> ans;
    while (root != nullptr || !sk.empty())
    {
        while (root != nullptr)
        {
            sk.push(root);
            root = root->left;
        }

        TreeNode *pNode = sk.top();
        sk.pop();
        ans.push_back(pNode->val);
        root = pNode->right;
    }
    return ans;
}

// leetcode 200 岛屿数量
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
// 岛屿总是被水包围，并且每座岛屿只能由水平方向或竖直方向上相邻的陆地连接形成。
// 此外，你可以假设该网格的四条边均被水包围。
int dfs_200(vector<vector<char>> &grid, int row, int col);
int numIslands(vector<vector<char>> &grid)
{
    int ans = 0;
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            if (grid[i][j] == '1' && dfs_200(grid, i, j) > 0)
                ans++;
        }
    }
    return ans;
}
int dfs_200(vector<vector<char>> &grid, int row, int col)
{
    if (row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size())
    {
        if (grid[row][col] == '1')
        {
            grid[row][col] = '0';
            return dfs_200(grid, row + 1, col) + dfs_200(grid, row - 1, col) + dfs_200(grid, row, col + 1) + dfs_200(grid, row, col - 1) + 1; // +1很关键
        }
    }
    return 0;
}

// leetcode 84 柱状图中最大的矩形
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
// 求在该柱状图中，能够勾勒出来的矩形的最大面积。
// 思路：求以当前柱子为高度的面积，即转化为寻找小于当前值的左右两边值，用栈保存小于当前值的左的元素。
int largestRectangleArea(vector<int> &heights)
{
    if (heights.empty())
        return 0;

    stack<int> sk;
    int ans = 0;
    int cur = 0;
    for (int i = 0; i < heights.size(); ++i)
    {
        if (i == heights.size())
            cur = 0;
        else
            cur = heights[i];

        while (!sk.empty() && cur <= heights[sk.top()])
        {
            int h = heights[sk.top()];
            sk.pop();
            int w = i;
            if (!sk.empty())
            {
                int peek = sk.top();
                w = i - peek - 1;
            }
            ans = max(ans, h * w);
        }
        sk.push(i);
    }
    return ans;
}

// 队列 queue
// leetcode 232 用栈实现队列
class MyQueue
{
public:
    /** Initialize your data structure here. */
    MyQueue()
    {
    }

    /** Push element x to the back of queue. */
    void push(int x)
    {
        sk1.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop()
    {
        if (sk2.empty())
        {
            while (!sk1.empty())
            {
                int tmp = sk1.top();
                sk1.pop();
                sk2.push(tmp);
            }
        }
        int tmp = sk2.top();
        sk2.pop();
        return tmp;
    }

    /** Get the front element. */
    int peek()
    {
        if (sk2.empty())
        {
            while (!sk1.empty())
            {
                sk2.push(sk1.top());
                sk1.pop();
            }
        }
        return sk2.top();
    }

    /** Returns whether the queue is empty. */
    bool empty()
    {
        return sk1.empty() && sk2.empty();
    }

private:
    stack<int> sk1;
    stack<int> sk2;
};

// leetcode 542 01矩阵
// 给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。
// 两个相邻元素间的距离为 1 。
vector<vector<int>> updateMatrix(vector<vector<int>> &matrix)
{
    queue<pair<int, int>> q;
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            if (matrix[i][j] == 0)
                q.push({i, j});
            else
                matrix[i][j] = -1;
        }
    }
    int dir[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (!q.empty())
    {
        auto [m, n] = q.front();
        q.pop();
        for (int k = 0; k < 4; ++k)
        {
            int x = m + dir[k][0];
            int y = n + dir[k][1];
            if (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size() && matrix[x][y] == -1)
            {
                matrix[x][y] = matrix[m][n] + 1;
                q.push({x, y});
            }
        }
    }
    return matrix;
}

// 3.二进制
// 常见二进制操作
// 基本操作
// a=0^a=a^0
// 0=a^a
// 由上面两个推导出：a=a^b^b
// 交换两个数
// a=a^b
// b=a^b
// a=a^b
// 移除最后一个 1
// a=n&(n-1)
// 获取最后一个 1
// diff=(n&(n-1))^n

// leetcode 136 只出现一次的数字
// 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
int singleNumber_136(vector<int> &nums)
{
    int ans = 0;
    // 相同两数异或为0
    for (auto num : nums)
        ans = ans ^ num;
    return ans;
}

// leetcode 137 只出现一次的数字 II
// 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。
int singleNumber_137(vector<int> &nums)
{
    int ans = 0, sum;
    // 统计每位1的个数
    for (int i = 0; i < 32; ++i)
    {
        sum = 0;
        for (auto num : nums)
            sum += (num >> i) & 1;
        // 还原位00^10=10 或者用| 也可以
        ans ^= (sum % 3) << i;
    }
    return ans;
}

// leetcode 260 只出现一次的数字 III
// 给定一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。
vector<int> singleNumber_260(vector<int> &nums)
{
    vector<int> ans(2);
    int diff = 0;
    // diff=a^b
    for (auto num : nums)
        diff ^= num;
    // 取diff中最后一个1所在的位置
    diff = (diff & (diff - 1)) ^ diff;
    for (auto num : nums)
    {
        // 将数据分为两组
        if ((diff & num) == 0)
            ans[0] ^= num;
        else
            ans[1] ^= num;
    }
    return ans;
}

// leetcode 191 位1的个数
// 编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’ 的个数（也被称为汉明重量）。
int hammingWeight(uint32_t n)
{
    int ans = 0;
    while (n)
    {
        if (n & 1)
            ans++;
        n = n >> 1;
    }
    return ans;
}

// leetcode 338 比特位计数
// 给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。
vector<int> countBits(int num)
{
    vector<int> ans;
    for (int i = 0; i <= num; ++i)
    {
        int tmp = i;
        int tmpAns = 0;
        while (tmp)
        {
            if (tmp & 1)
                tmpAns++;
            tmp = tmp >> 1;
        }
        ans.push_back(tmpAns);
    }
    return ans;
}

vector<int> countBits_dp(int num)
{
    vector<int> ans(num + 1);
    for (int i = 0; i <= num; ++i)
        ans[i] = ans[i & (i - 1)] + 1;
}

// leetcode 190 颠倒二进制位
// 颠倒给定的 32 位无符号整数的二进制位。
uint32_t reverseBits(uint32_t n)
{
    uint32_t ans = 0;
    int pow = 31;
    while (n)
    {
        ans += (n & 1) << pow;
        pow--;
        n = n >> 1;
    }
    return ans;
}

// leetcode 201 数字范围按位与
// 给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。
int rangeBitwiseAnd(int m, int n)
{
    // 找所有数的公共前缀
    int cnt = 0;
    while (m != n)
    {
        m >>= 1;
        n >>= 1;
        cnt++;
    }
    m <<= cnt;
    return m;
    // while(m<n)
    //     n=n&(n-1);
    // return n;
}

// 4.二叉树
// leetcode 104 二叉树的最大深度
int maxDepthCore(TreeNode *root);
int maxDepth(TreeNode *root)
{
    return maxDepthCore(root);
}
int maxDepthCore(TreeNode *root)
{
    if (root == nullptr)
        return 0;

    int left = maxDepthCore(root->left);
    int right = maxDepthCore(root->right);
    return max(left, right) + 1;
}

// leetcode 110 平衡二叉树
// 给定一个二叉树，判断它是否是高度平衡的二叉树。
// 本题中，一棵高度平衡二叉树定义为：一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。
int maxDepthCore_110(TreeNode *root);
bool isBalanced(TreeNode *root)
{
    if (maxDepthCore_110(root) == -1)
        return false;
    return true;
}

// 返回-1 表示不平衡 其他返回表示树的深度
int maxDepthCore_110(TreeNode *root)
{
    if (root == nullptr)
        return 0;

    int left = maxDepthCore_110(root->left);
    int right = maxDepthCore_110(root->right);
    if (left == -1 || right == -1 || left - right > 1 || left - right < -1)
        return -1;

    return max(left, right) + 1;
}

// leetcode 124 二叉树中的最大路径和
// 给定一个非空二叉树，返回其最大路径和。
// 本题中，路径被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。
int maxGainCore(TreeNode *root, int &ans);
int maxPathSum(TreeNode *root)
{
    int ans = INT_MIN;
    maxGainCore(root, ans);
    return ans;
}

int maxGainCore(TreeNode *root, int &ans)
{
    if (root == nullptr)
        return 0;

    int left = max(maxGainCore(root->left, ans), 0);
    int right = max(maxGainCore(root->right, ans), 0);

    int pathSum = root->val + left + right;
    ans = max(ans, pathSum);
    return root->val + max(left, right);
}

// leetcode 236 二叉树的最近公共祖先
// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
bool dfs_236(TreeNode *root, TreeNode *p, TreeNode *q, TreeNode *&ans);
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    TreeNode *ans;
    dfs_236(root, p, q, ans);
    return ans;
}

bool dfs_236(TreeNode *root, TreeNode *p, TreeNode *q, TreeNode *&ans)
{
    if (root == nullptr)
        return false;

    bool lSon = dfs_236(root->left, p, q, ans);
    bool rSon = dfs_236(root->right, p, q, ans);

    if ((lSon && rSon) || ((lSon || rSon) && (root == q || root == p)))
        ans = root;
    return lSon || rSon || root == p || root == q;
}

// leetcode 102 二叉树的层序遍历
// 给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> ans;
    if (root == nullptr)
        return ans;

    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();
        ans.push_back(vector<int>());
        for (int i = 0; i < n; ++i)
        {
            TreeNode *pNode = q.front();
            q.pop();
            ans.back().push_back(pNode->val);
            if (pNode->left)
                q.push(pNode->left);
            if (pNode->right)
                q.push(pNode->right);
        }
    }
    return ans;
}

// leetcode 107 二叉树的层次遍历 II
// 给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）
vector<vector<int>> levelOrderBottom(TreeNode *root)
{
    vector<vector<int>> ans;
    if (root == nullptr)
        return ans;

    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        int count = q.size();
        ans.push_back(vector<int>());
        for (int i = 0; i < count; i++)
        {
            TreeNode *node = q.front();
            q.pop();
            ans.back().push_back(node->val);
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// leetcode 103 二叉树的锯齿形层次遍历
// 给定一个二叉树，返回其节点值的锯齿形层次遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
vector<vector<int>> zigzagLevelOrder(TreeNode *root)
{
    vector<vector<int>> ans;
    if (root == nullptr)
        return ans;

    queue<TreeNode *> q;
    int level = 0;
    q.push(root);
    while (!q.empty())
    {
        vector<int> tmp;
        int cnt = q.size();
        for (int i = 0; i < cnt; ++i)
        {
            TreeNode *pNode = q.front();
            q.pop();
            if (level % 2 == 0)
                tmp.push_back(pNode->val);
            else
                tmp.insert(tmp.begin(), pNode->val);

            if (pNode->left)
                q.push(pNode->left);
            if (pNode->right)
                q.push(pNode->right);
        }
        level++;
        ans.push_back(tmp);
    }
    return ans;
}

// leetcode 验证二叉搜索树
// 给定一个二叉树，判断其是否是一个有效的二叉搜索树。
bool isValidBST(TreeNode *root)
{
    stack<TreeNode *> sk;
    long long inorder = (long long)INT_MIN - 1;
    while (!sk.empty() || root != nullptr)
    {
        while (root != nullptr)
        {
            sk.push(root);
            root = root->left;
        }
        TreeNode *node = sk.top();
        sk.pop();
        if (node->val <= inorder)
            return false;
        inorder = node->val;
        root = node->right;
    }
    return true;
}

// leetcode 701 二叉搜索树中的插入操作
// 给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 输入数据保证，新值和原始二叉搜索树中的任意节点值都不同。
TreeNode *insertIntoBST(TreeNode *root, int val)
{
    if (root == nullptr)
    {
        root = new TreeNode(val);
        return root;
    }

    if (root->val > val)
        root->left = insertIntoBST(root->left, val);
    else
        root->right = insertIntoBST(root->right, val);

    return root;
}

// leetcode 820 单词的压缩编码
// 给定一个单词列表，我们将这个列表编码成一个索引字符串 S 与一个索引列表 A。例如，如果这个列表是 ["time", "me", "bell"]，我们就可以将其表示为 S = "time#bell#" 和 indexes = [0, 2, 5]。
// 对于每一个索引，我们可以通过从字符串 S 中索引的位置开始读取字符串，直到 "#" 结束，来恢复我们之前的单词列表。那么成功对给定单词列表进行编码的最小字符串长度是多少呢？
// 扩展：求出 s 和 索引
int minimumLengthEncoding(vector<string> &words)
{
    unordered_set<string> wordsSet(words.begin(), words.end());
    for (auto &word : words)
    {
        for (int i = 1; i < word.size(); ++i)
            wordsSet.erase(word.substr(i));
    }

    int ans = 0;
    for (auto &word : wordsSet)
    {
        ans += word.size() + 1;
    }

    // 求字符串
    string s;
    for (auto &word : words)
    {
        if (wordsSet.find(word) != wordsSet.end())
        {
            s.append(word);
            s.append("#");
        }
    }

    // 求索引
    vector<int> indexs;
    for (auto &word : words)
    {
        int index = s.find(word);
        indexs.push_back(index);
    }

    return ans;
}

// 四、输入输出
// 1.scanf()函数 from <cstdio>

// 2.cin from <iostream>

// kmp
// void getNext(char *p, int *next)
// {
//     next[0] = -1;
//     int i = 0, j = -1;

//     while (i < strlen(p))
//     {
//         if (j == -1 || p[i] == p[j])
//         {
//             ++i;
//             ++j;
//             next[i] = j;
//         }
//         else
//             j = next[j];
//     }
// }

// int kmp(char *p, char *t, int *next)
// {
//     int i = 0, j = 0;
//     while (i < strlen(t) && j < strlen(p))
//     {
//         if (j == -1 || t[i] == p[j])
//         {
//             i++;
//             j++;
//         }
//         else
//             j = next[j];
//     }
//     if (j == strlen(p))
//         return i - j;

//     return -1;
// }

int main()
{
    // std::vector<int> v = {3, 8, 4, 2, 1, 9, 5};
    // for (int i = 0; i < v.size(); ++i)
    // {
    //     printf("%d ", v[i]);
    // }
    // printf("\n");

    // // bubbleSort(v);
    // // selectSort(v);
    // // insertSort(v);
    // // quickSort(v,0,v.size());
    // // mergeSort(v);
    // // heapSort(v);

    // for (int i = 0; i < v.size(); ++i)
    // {
    //     printf("%d ", v[i]);
    // }

    // // int m=11;
    // // vector<int> w={2,4,3,5,1};
    // // vector<int> v={3,3,2,6,1};
    // // cout<<backPack_ii(m,w,v);

    // return 0;
    return 0;
}