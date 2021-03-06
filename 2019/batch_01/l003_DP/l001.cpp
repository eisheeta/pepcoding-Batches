#include <iostream>
#include <vector>

#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>

using namespace std;

void multiplication(vector<vector<int>> &a, vector<vector<int>> &b)
{

    int a0 = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    int a1 = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    int a2 = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    int a3 = a[1][0] * b[0][1] + a[1][1] * b[1][1];

    a[0][0] = a0;
    a[0][1] = a1;
    a[1][0] = a2;
    a[1][1] = a3;
}

void power(vector<vector<int>> &a, vector<vector<int>> &I, int pow)
{
    if (pow == 1)
        return;

    power(a, I, pow / 2);
    multiplication(a, a);

    if (pow % 2 != 0)
        multiplication(a, I);
}

int boardPath_memo(int start, int end, vector<int> &dp)
{
    if (start == end)
    {
        dp[start] = 1;
        return 1;
    }

    // if(dp[start]!=0) return dp[start];

    int count = 0;
    for (int dice = 1; dice <= 6; dice++)
    {
        if (start + dice <= end)
        {
            count += boardPath_memo(start + dice, end, dp);
        }
    }

    dp[start] = count;

    return count;
}

int mazePath(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
    {
        dp[sr][sc] = 1;
        return 1;
    }

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    if (dp.size() == dp[0].size() && dp[sc][sr] != 0)
        return dp[sc][sr];

    int count = 0;
    if (sr + 1 <= er)
    {
        count += mazePath(sr + 1, sc, er, ec, dp);
    }

    if (sc + 1 <= ec)
    {
        count += mazePath(sr, sc + 1, er, ec, dp);
    }

    if (sc + 1 <= ec && sr + 1 <= er)
    {
        count += mazePath(sr + 1, sc + 1, er, ec, dp);
    }

    dp[sr][sc] = count;
    if (dp.size() == dp[0].size())
        dp[sc][sr] = count;
    return count;
}

int mazePathDP(int sr, int sc, int er, int ec)
{

    vector<vector<int>> dp(er + 1, vector<int>(ec + 1));

    for (int sr = er; sr >= 0; sr--)
    {
        for (int sc = ec; sc >= 0; sc--)
        {

            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }
            int count = 0;
            if (sr + 1 <= er)
                count += dp[sr + 1][sc];
            if (sc + 1 <= ec)
                count += dp[sr][sc + 1];
            if (sr + 1 <= er && sc + 1 <= ec)
                count += dp[sr + 1][sc + 1];

            dp[sr][sc] = count;
        }
    }

    return dp[0][0];
}

int mazePathMulti(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
    {
        dp[sr][sc] = 1;
        return 1;
    }

    if (dp[sr][sc] != 0)
        return dp[sr][sc];
    if (dp.size() == dp[0].size() && dp[sc][sr] != 0)
        return dp[sc][sr];

    int count = 0;
    for (int jump = 1; sr + jump <= er; jump++)
    {
        count += mazePathMulti(sr + jump, sc, er, ec, dp);
    }

    for (int jump = 1; sc + jump <= ec; jump++)
    {
        count += mazePathMulti(sr, sc + jump, er, ec, dp);
    }

    for (int jump = 1; sc + jump <= ec && sr + jump <= er; jump++)
    {
        count += mazePathMulti(sr + jump, sc + jump, er, ec, dp);
    }

    dp[sr][sc] = count;
    if (dp.size() == dp[0].size())
        dp[sc][sr] = count;
    return count;
}

int mazePathMultiDP(int sr, int sc, int er, int ec)
{

    vector<vector<int>> dp(er + 1, vector<int>(ec + 1));

    for (int sr = er; sr >= 0; sr--)
    {
        for (int sc = ec; sc >= 0; sc--)
        {

            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }
            int count = 0;

            for (int jump = 1; sr + jump <= er; jump++)
                count += dp[sr + jump][sc];

            for (int jump = 1; sc + jump <= ec; jump++)
                count += dp[sr][sc + jump];

            for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
                count += dp[sr + 1][sc + 1];

            dp[sr][sc] = count;
        }
    }

    return dp[0][0];
}

vector<vector<int>> dirArray = {{0, 1}, {1, 0}, {1, 1}};

int minCost(vector<vector<int>> &costArray, int sr, int sc, vector<vector<int>> &dp)
{

    if (sr == costArray.size() - 1 && sc == costArray[0].size() - 1)
    {
        dp[sr][sc] = costArray[sr][sc];
        return costArray[sr][sc];
    }

    if (dp[sr][sc] != -1)
        return dp[sr][sc];

    int mincost = 1e6;
    for (int d = 0; d < dirArray.size(); d++)
    {
        int r = sr + dirArray[d][0];
        int c = sc + dirArray[d][1];

        if (r < costArray.size() && c < costArray[0].size())
        {
            mincost = min(mincost, minCost(costArray, r, c, dp));
        }
    }

    dp[sr][sc] = costArray[sr][sc] + mincost;

    return costArray[sr][sc] + mincost;
}

int minCostDP(vector<vector<int>> &costArray, vector<vector<int>> &dp)
{
    for (int sr = costArray.size() - 1; sr >= 0; sr--)
    {
        for (int sc = costArray[0].size() - 1; sc >= 0; sc--)
        {
            if (sr == costArray.size() - 1 && sc == costArray[0].size() - 1)
            {
                dp[sr][sc] = costArray[sr][sc];
                continue;
            }

            int mincost = 1e6;
            for (int d = 0; d < dirArray.size(); d++)
            {
                int r = sr + dirArray[d][0];
                int c = sc + dirArray[d][1];

                if (r < costArray.size() && c < costArray[0].size())
                {
                    mincost = min(mincost, dp[r][c]);
                }
            }

            dp[sr][sc] = costArray[sr][sc] + mincost;
        }
    }

    return dp[0][0];
}

void pathType()
{
    // int n = 10;
    // vector<int> dp(n + 1, 0);
    // cout << boardPath_memo(0, n, dp) << endl;

    // for (int ele : dp)
    // {
    //     cout << ele << " ";
    // }

    // int n = 3;
    // int m = 3;
    // vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // cout << mazePath(0, 0, n, m, dp) << endl;
    // cout << mazePathDP(0, 0, n, m) << endl;

    // cout << mazePathMulti(0, 0, 2, 2, dp) << endl;

    vector<vector<int>> costArray = {{2, 3, 0, 4},
                                     {0, 6, 5, 2},
                                     {8, 0, 3, 7},
                                     {2, 0, 4, 2}};
    vector<vector<int>> dp(costArray.size(), vector<int>(costArray[0].size(), -1));
    // cout << minCost(costArray, 0, 0, dp) << endl;
    cout << minCostDP(costArray, dp) << endl;

    for (vector<int> &ar : dp)
    {
        for (int &ele : ar)
        {
            cout << ele << " ";
        }
        cout << endl;
    }
}

//===================================

int minJumps(vector<int> &arr)
{
    vector<int> dp(arr.size(), 1e6);
    dp[arr.size() - 1] = 0;

    for (int i = arr.size() - 2; i >= 0; i--)
    {
        int min_ = (int)1e6;
        for (int j = 1; j <= arr[i] && i + j < arr.size(); j++)
        {
            min_ = min(min_, dp[i + j]);
        }
        dp[i] = min_ + 1;
    }
    return dp[0];
}

int PairAndSingle(int n)
{
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++)
    {
        dp[i] += dp[i - 1];           // single
        dp[i] += dp[i - 2] * (i - 1); //pairUp ways.
    }

    return dp[n];
}

int PairAndSingle2(int n)
{

    int a = 1;
    int b = 2;
    int c = 0;
    for (int i = 3; i <= n; i++)
    {
        c = b + a * (i - 1); // f(n)=f(n-1) + f(n-2) * (n-1).
        a = b;
        b = c;
    }

    return c;
}

int divideInKGroups(int n, int k)
{
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= k; i++)
    {
        for (int j = i; j <= n; j++)
        {
            dp[i][j] += dp[i - 1][j - 1] + dp[i][j - 1] * i;
        }
    }
    return dp[k][n];
}

vector<vector<bool>> isPali(string str)
{
    vector<vector<bool>> isPlaidrome(str.length(), vector<bool>(str.length(), false));

    for (int gap = 0; gap < str.length(); gap++)
    {
        for (int i = 0, j = gap; j < str.length(); j++, i++)
        {
            if (gap == 0)
            {
                isPlaidrome[i][j] = true;
            }
            else if (str[i] == str[j])
            {
                if (gap == 1)
                    isPlaidrome[i][j] = true;
                else if (isPlaidrome[i + 1][j - 1])
                    isPlaidrome[i][j] = true;
            }
        }
    }

    return isPlaidrome;
}

int lpSubstring(string str)
{
    vector<vector<int>> dp(str.length(), vector<int>(str.length(), 0));
    vvb isPalindrome = isPali(str);

    for (int gap = 0; gap < str.length(); gap++)
    {
        for (int i = 0, j = gap; j < str.length(); j++, i++)
        {
            if (gap == 0)
            {
                dp[i][j] = 1;
            }
            else if (gap == 1 && str[i] == str[j])
            {
                dp[i][j] = 2;
            }
            else if (str[i] == str[j] && isPalindrome[i + 1, j - 1])
            {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            }
            else
            {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][str.length() - 1];
}

int lpSubsequence(string str)
{
    vector<vector<int>> dp(str.length(), vector<int>(str.length(), 0));

    for (int gap = 0; gap < str.length(); gap++)
    {
        for (int i = 0, j = gap; j < str.length(); j++, i++)
        {
            if (gap == 0)
                dp[i][j] = 1;
            else if (str[i] == str[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }.
    return dp[0][str.length() - 1];
}

void minType()
{
    vector<int> jumps = {0, 3, 0, 4, 0, 0, 2, 1, 1, 0};
    // cout<<minJumps(jumps)<<endl;
    // cout<<PairAndSingle(5)<<endl;
    // cout << PairAndSingle2(5) << endl;
    cout << divideInKGroups(6, 4) << endl;
}

void solve()
{
    // vector<vector<int>> a = {{1, 1}, {1, 0}};
    // vector<vector<int>> I = {{1, 1}, {1, 0}};
    // int n = 13;
    // power(a, I, n + 1);
    // cout << a[1][1] << endl;

    // pathType();
    minType();
}

int main()
{
    solve();
    return 0;
}