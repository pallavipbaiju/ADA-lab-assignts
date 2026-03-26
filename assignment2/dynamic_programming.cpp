#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

// HELPER: print separator line
void printLine(int n) {
    for (int i = 0; i < n; i++) printf("-");
    printf("\n");
}

// ================================================
// 1. LONGEST COMMON SUBSEQUENCE (LCS)
// ================================================

int lcsDP(string X, string Y, int dp[][100]) {
    int m = X.length();
    int n = Y.length();

    // Fill DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i-1] == Y[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[m][n];
}

// Backtrack to find actual LCS string
string backtrackLCS(string X, string Y, int dp[][100]) {
    int i = X.length();
    int j = Y.length();
    string lcs = "";

    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            lcs = X[i-1] + lcs;
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    return lcs;
}

void printLCSTable(string X, string Y, int dp[][100]) {
    int m = X.length();
    int n = Y.length();

    printf("\n  LCS DP Table:\n");
    printf("      e  ");
    for (int j = 0; j < n; j++)
        printf(" %c ", Y[j]);
    printf("\n  ");
    printLine(n * 3 + 8);

    for (int i = 0; i <= m; i++) {
        if (i == 0) printf("  e | ");
        else        printf("  %c | ", X[i-1]);

        for (int j = 0; j <= n; j++)
            printf("%2d ", dp[i][j]);
        printf("\n");
    }
}

void runLCS() {
    printf("================================================\n");
    printf("  1. LONGEST COMMON SUBSEQUENCE (LCS)\n");
    printf("================================================\n");

    string X = "ABCBDAB";
    string Y = "BDCABA";

    printf("\n  X = %s\n", X.c_str());
    printf("  Y = %s\n", Y.c_str());

    int dp[100][100] = {0};
    int len = lcsDP(X, Y, dp);

    printLCSTable(X, Y, dp);

    string lcs = backtrackLCS(X, Y, dp);
    printf("\n  LCS Length : %d\n", len);
    printf("  LCS String : %s\n",  lcs.c_str());

    // Observation
    printf("\n  // OBSERVATION:\n");
    printf("  // If X[i]==Y[j]: dp[i][j] = dp[i-1][j-1] + 1\n");
    printf("  // Else         : dp[i][j] = max(dp[i-1][j], dp[i][j-1])\n");
    printf("  // Time : O(m*n)  Space: O(m*n)\n");

    // Timing for increasing sizes
    printf("\n  Execution Time (increasing input size):\n");
    printf("  %-10s %-15s\n", "Length", "Time (ms)");
    printLine(28);

    int sizes[] = {10, 20, 30, 50, 70, 90};
    string chars = "ABCDEFGHIJ";

    for (int s = 0; s < 6; s++) {
        int    n = sizes[s];
        string A = "", B = "";
        for (int i = 0; i < n; i++) A += chars[i % 10];
        for (int i = 0; i < n; i++) B += chars[(i + 3) % 10];

        int table[100][100] = {0};
        clock_t start = clock();
        lcsDP(A, B, table);
        clock_t end = clock();

        double t = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
        printf("  %-10d %-15.4f\n", n, t);
    }
}

// ================================================
// 2. 0/1 KNAPSACK PROBLEM
// ================================================

int knapsack(int weights[], int values[], int n,
             int capacity, int dp[][100]) {

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i-1] <= w)
                dp[i][w] = max(values[i-1] + dp[i-1][w - weights[i-1]],
                               dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][capacity];
}

void printKnapsackTable(int dp[][100], int n, int capacity) {
    printf("\n  0/1 Knapsack DP Table:\n");
    printf("      ");
    for (int w = 0; w <= capacity; w++)
        printf("%3d", w);
    printf("\n  ");
    printLine(capacity * 3 + 8);

    for (int i = 0; i <= n; i++) {
        printf("  i=%d |", i);
        for (int w = 0; w <= capacity; w++)
            printf("%3d", dp[i][w]);
        printf("\n");
    }
}

void findSelectedItems(int dp[][100], int weights[],
                       int values[], int n, int capacity) {
    printf("\n  Selected Items:\n");
    printf("  %-8s %-8s %-8s\n", "Item", "Weight", "Value");
    printLine(26);

    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            printf("  %-8d %-8d %-8d\n", i, weights[i-1], values[i-1]);
            w -= weights[i-1];
        }
    }
}

void runKnapsack() {
    printf("\n================================================\n");
    printf("  2. 0/1 KNAPSACK PROBLEM\n");
    printf("================================================\n");

    int weights[]  = {1, 3, 4, 5};
    int values[]   = {1, 4, 5, 7};
    int n          = 4;
    int capacity   = 7;

    printf("\n  Items:\n");
    printf("  %-8s %-8s %-8s\n", "Item", "Weight", "Value");
    printLine(26);
    for (int i = 0; i < n; i++)
        printf("  %-8d %-8d %-8d\n", i+1, weights[i], values[i]);
    printf("  Capacity : %d\n", capacity);

    int dp[100][100] = {0};
    int maxVal = knapsack(weights, values, n, capacity, dp);

    printKnapsackTable(dp, n, capacity);
    findSelectedItems(dp, weights, values, n, capacity);

    printf("\n  Maximum Value : %d\n", maxVal);

    printf("\n  // OBSERVATION:\n");
    printf("  // If item fits: dp[i][w] = max(include, exclude)\n");
    printf("  // Include     : values[i] + dp[i-1][w-weights[i]]\n");
    printf("  // Exclude     : dp[i-1][w]\n");
    printf("  // Time: O(n*W)  Space: O(n*W)\n");

    // Timing
    printf("\n  Execution Time (increasing input size):\n");
    printf("  %-10s %-15s\n", "n (items)", "Time (ms)");
    printLine(28);

    int testSizes[] = {5, 10, 15, 20, 25, 30};
    for (int s = 0; s < 6; s++) {
        int tn = testSizes[s];
        int tw[tn], tv[tn];
        for (int i = 0; i < tn; i++) {
            tw[i] = (i % 10) + 1;
            tv[i] = (i % 20) + 1;
        }
        int tdp[100][100] = {0};
        clock_t start = clock();
        knapsack(tw, tv, tn, 50, tdp);
        clock_t end = clock();

        double t = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
        printf("  %-10d %-15.4f\n", tn, t);
    }
}

// ================================================
// 3. MATRIX CHAIN MULTIPLICATION
// ================================================

int matrixChain(int dims[], int n, int dp[][10], int split[][10]) {
    // Single matrix = 0 cost
    for (int i = 0; i < n; i++)
        dp[i][i] = 0;

    // chainLen = length of chain
    for (int chainLen = 2; chainLen <= n; chainLen++) {
        for (int i = 0; i <= n - chainLen; i++) {
            int j = i + chainLen - 1;
            dp[i][j] = 99999999;

            // Try every split point k
            for (int k = i; k < j; k++) {
                int cost = dp[i][k]
                         + dp[k+1][j]
                         + dims[i] * dims[k+1] * dims[j+1];

                if (cost < dp[i][j]) {
                    dp[i][j]    = cost;
                    split[i][j] = k;
                }
            }
        }
    }
    return dp[0][n-1];
}

// Print optimal parenthesisation
void printParens(int split[][10], int i, int j) {
    if (i == j) {
        printf("A%d", i+1);
        return;
    }
    printf("(");
    printParens(split, i, split[i][j]);
    printf(" x ");
    printParens(split, split[i][j]+1, j);
    printf(")");
}

void printMCMTable(int dp[][10], int n) {
    printf("\n  MCM DP Cost Table:\n");
    printf("      ");
    for (int j = 0; j < n; j++)
        printf("  A%-5d", j+1);
    printf("\n  ");
    printLine(n * 8 + 6);

    for (int i = 0; i < n; i++) {
        printf("  A%d |", i+1);
        for (int j = 0; j < n; j++) {
            if (j < i)       printf("  ------");
            else if (i == j) printf("  %6d", 0);
            else             printf("  %6d", dp[i][j]);
        }
        printf("\n");
    }
}

void runMCM() {
    printf("\n================================================\n");
    printf("  3. MATRIX CHAIN MULTIPLICATION\n");
    printf("================================================\n");

    // Matrices: A1=30x35, A2=35x15, A3=15x5, A4=5x10, A5=10x20, A6=20x25
    int dims[] = {30, 35, 15, 5, 10, 20, 25};
    int n      = 6;   // number of matrices

    printf("\n  Matrix Dimensions:\n");
    printf("  %-10s %-20s\n", "Matrix", "Dimensions");
    printLine(32);
    for (int i = 0; i < n; i++)
        printf("  A%-9d %d x %d\n", i+1, dims[i], dims[i+1]);

    int dp[10][10]    = {0};
    int split[10][10] = {0};

    int minCost = matrixChain(dims, n, dp, split);

    printMCMTable(dp, n);

    printf("\n  Split Table:\n");
    printf("      ");
    for (int j = 0; j < n; j++)
        printf("  A%-5d", j+1);
    printf("\n  ");
    printLine(n * 8 + 6);
    for (int i = 0; i < n; i++) {
        printf("  A%d |", i+1);
        for (int j = 0; j < n; j++) {
            if (j <= i) printf("  ------");
            else        printf("  %6d", split[i][j]+1);
        }
        printf("\n");
    }

    printf("\n  Minimum Multiplications : %d\n", minCost);
    printf("  Optimal Parenthesisation: ");
    printParens(split, 0, n-1);
    printf("\n");

    printf("\n  // OBSERVATION:\n");
    printf("  // dp[i][j] = min cost to multiply matrices i to j\n");
    printf("  // Try all split points k between i and j\n");
    printf("  // Cost = dp[i][k] + dp[k+1][j] + dims[i]*dims[k+1]*dims[j+1]\n");
    printf("  // Time: O(n^3)   Space: O(n^2)\n");

    // Timing
    printf("\n  Execution Time (increasing chain length):\n");
    printf("  %-12s %-15s\n", "Matrices(n)", "Time (ms)");
    printLine(30);

    int testDims[][10] = {
        {10, 20, 30},
        {10, 20, 30, 40, 50},
        {10, 20, 30, 40, 50, 60, 70},
        {5, 10, 15, 20, 25, 30, 35, 40},
        {5, 10, 15, 20, 25, 30, 35, 40, 45}
    };
    int chainLens[] = {2, 4, 6, 7, 8};

    for (int t = 0; t < 5; t++) {
        int tdp[10][10]    = {0};
        int tsplit[10][10] = {0};

        clock_t start = clock();
        matrixChain(testDims[t], chainLens[t], tdp, tsplit);
        clock_t end = clock();

        double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
        printf("  %-12d %-15.4f\n", chainLens[t], time);
    }
}


int main() {
    runLCS();
    runKnapsack();
    runMCM();

    printf("\n================================================\n");
    printf("  OVERALL OBSERVATIONS\n");
    printf("================================================\n");
    printf("  1. LCS       : O(m*n)  - grows quadratically\n");
    printf("  2. 0/1 Knap  : O(n*W)  - pseudo-polynomial\n");
    printf("  3. MCM       : O(n^3)  - cubic growth\n");
    printf("\n");
    printf("  DP vs Greedy:\n");
    printf("  - DP guarantees OPTIMAL solution always\n");
    printf("  - Greedy is faster but not always optimal\n");
    printf("  - 0/1 Knapsack NEEDS DP (greedy fails here)\n");
    printf("  - DP uses extra memory for the table\n");
    printf("================================================\n");

    return 0;
}

