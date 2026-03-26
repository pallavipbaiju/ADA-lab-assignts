# Assignment 2 - Advanced Algorithm Design Paradigms

**Course:** Analysis and Design of Algorithms Lab (ENCS256)
**Semester:** IV | **Program:** BTech | **Session:** 2025-26
**Department:** SOET – KR Mangalam University
**Faculty:** Dr. Rupendra Hada

---

## Files

| File | Description |
|---|---|
| `divide_and_conquer.cpp` | Task 1 & 2 – Binary Search, Merge Sort, Quick Sort, Max-Min, Strassen |
| `greedy_algorithms.cpp` | Task 3 – Fractional Knapsack, Activity Selection, Huffman Coding |
| `dynamic_programming.cpp` | Task 4 – LCS, 0/1 Knapsack, Matrix Chain Multiplication |

---


## Task 1 & 2 – Divide and Conquer + Sorting Comparison

### Output

```
================================================
  1. BINARY SEARCH
================================================
  Array  : [ 2 5 8 12 16 23 38 45 67 90 ]
  Target : 23
  Found 23 at index 5

================================================
  2. MERGE SORT
================================================
  Before : [ 38 27 43 3 9 82 10 ]
  After  : [ 3 9 10 27 38 43 82 ]

================================================
  3. QUICK SORT
================================================
  Before : [ 64 25 12 22 11 90 42 ]
  After  : [ 11 12 22 25 42 64 90 ]

================================================
  4. FIND MAX & MIN (Divide and Conquer)
================================================
  Array  : [ 70 250 35 18 99 4 150 63 ]
  Max    : 250
  Min    : 4

================================================
  5. STRASSEN'S MATRIX MULTIPLICATION (2x2)
================================================
  Matrix A:
    [ 1  2 ]
    [ 3  4 ]
  Matrix B:
    [ 5  6 ]
    [ 7  8 ]
  Strassen Result:
    [ 19  22 ]
    [ 43  50 ]
  Normal   Result:
    [ 19  22 ]
    [ 43  50 ]
  Both results match: YES
```

### Complexity Summary

| Algorithm | Best | Average | Worst | Space |
|---|---|---|---|---|
| Binary Search | O(1) | O(log n) | O(log n) | O(log n) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) |
| Max & Min D&C | O(n) | O(n) | O(n) | O(log n) |
| Strassen | — | O(n^2.81) | O(n^2.81) | O(n²) |

---

## Task 3 – Greedy Algorithms

### Output

```
================================================
  1. FRACTIONAL KNAPSACK
================================================
  Items:
  ID     Weight   Value
  ------------------------
  A      2        10
  B      3        5
  C      5        15
  D      7        7
  E      1        6
  F      4        18
  Capacity : 15

  Selection process:
  ----------------------------------------------------
  Took FULL  Item E (w=1, v=6,  ratio=6.00) | +6  value
  Took FULL  Item A (w=2, v=10, ratio=5.00) | +10 value
  Took FULL  Item F (w=4, v=18, ratio=4.50) | +18 value
  Took FULL  Item C (w=5, v=15, ratio=3.00) | +15 value
  Took FULL  Item B (w=3, v=5,  ratio=1.67) | +5  value

  Greedy  Max Value : 54.00
  Brute Force Value : 54.00 (whole items only)
  Greedy >= BruteForce : YES

  // OBSERVATION:
  // Greedy gives optimal result for fractional knapsack.
  // Sorting by value/weight ratio ensures maximum value
  // per unit weight is always picked first.
  // Brute-force only considers whole items (0/1),
  // so greedy (with fractions) always >= brute-force.

================================================
  2. ACTIVITY SELECTION PROBLEM
================================================
  Total Activities : 11

  Activities sorted by finish time:
  ID     Start    End
  ------------------------
  A      1        4
  B      3        5
  C      0        6
  D      5        7
  E      3        9
  F      5        10
  G      6        11
  H      8        12
  I      8        13
  J      2        14
  K      12       16

  Selection:
  ----------------------------------------
  Selected Activity A [1, 4)
  Skipped  Activity B [3, 5)  <- overlaps
  Skipped  Activity C [0, 6)  <- overlaps
  Selected Activity D [5, 7)
  Skipped  Activity E [3, 9)  <- overlaps
  Skipped  Activity F [5, 10) <- overlaps
  Skipped  Activity G [6, 11) <- overlaps
  Selected Activity H [8, 12)
  Skipped  Activity I [8, 13) <- overlaps
  Skipped  Activity J [2, 14) <- overlaps
  Selected Activity K [12, 16)

  Total Activities Selected : 4 / 11
  Selected IDs : A D H K

  // OBSERVATION:
  // Greedy picks activity with earliest finish time first.
  // This leaves maximum room for remaining activities.
  // Guaranteed to give maximum number of non-overlapping
  // activities — proven optimal greedy strategy.

================================================
  3. HUFFMAN CODING
================================================
  Input text : BCAADDDCCACACAC
  Length     : 15 characters

  Character Frequencies:
  Char     Freq
  ------------------
  A        5
  B        1
  C        6
  D        3

  Huffman Codes:
  Char     Freq     Code
  ------------------------------
  C        6        0
  B        1        100
  D        3        101
  A        5        11

  Huffman Tree:
  +-[0]-  [15]
  |       +-[0]-  'C' (freq=6)
  |       +-[1]-  [9]
  |               +-[0]-  [4]
  |               |       +-[0]-  'B' (freq=1)
  |               |       +-[1]-  'D' (freq=3)
  |               +-[1]-  'A' (freq=5)

  Original text    : BCAADDDCCACACAC
  Encoded bits     : 1000111110110110100110110110
  Original bits    : 120
  Compressed bits  : 28
  Compression ratio: 4.29x
  Space savings    : 76.7%

  // OBSERVATION:
  // Huffman coding assigns shorter codes to frequent chars.
  // 'C' appears most (6x) -> gets shortest code.
  // 'B' appears least (1x) -> gets longest code.
  // Result is a prefix-free code (no code is prefix
  // of another) — enables unambiguous decoding.
  // Compression ratio > 1 means space is saved.

================================================
  OVERALL OBSERVATIONS
================================================
  1. Greedy is O(n log n) for all three algorithms.
  2. Greedy is OPTIMAL for:
       - Fractional Knapsack (fractions allowed)
       - Activity Selection  (max activities)
       - Huffman Coding      (min weighted path)
  3. Greedy is NOT optimal for 0/1 Knapsack
       -> use Dynamic Programming instead.
================================================
```

### Complexity Summary

| Algorithm | Time | Space | Optimal? |
|---|---|---|---|
| Fractional Knapsack | O(n log n) | O(1) | ✅ Yes |
| Activity Selection | O(n log n) | O(n) | ✅ Yes |
| Huffman Coding | O(n log n) | O(n) | ✅ Yes |

---

## Task 4 – Dynamic Programming

### Output

```
================================================
  1. LONGEST COMMON SUBSEQUENCE (LCS)
================================================
  X = ABCBDAB
  Y = BDCABA

  LCS DP Table:
      e   B  D  C  A  B  A
  --------------------------
  e |  0  0  0  0  0  0  0
  A |  0  0  0  0  1  1  1
  B |  0  1  1  1  1  2  2
  C |  0  1  1  2  2  2  2
  B |  0  1  1  2  2  3  3
  D |  0  1  2  2  2  3  3
  A |  0  1  2  2  3  3  4
  B |  0  1  2  2  3  4  4

  LCS Length : 4
  LCS String : BDAB

  // OBSERVATION:
  // If X[i]==Y[j]: dp[i][j] = dp[i-1][j-1] + 1
  // Else         : dp[i][j] = max(dp[i-1][j], dp[i][j-1])
  // Time : O(m*n)  Space: O(m*n)

  Execution Time (increasing input size):
  Length     Time (ms)
  ----------------------------
  10         0.0000
  20         0.0000
  30         0.0000
  50         0.0000
  70         0.0000
  90         0.0000

================================================
  2. 0/1 KNAPSACK PROBLEM
================================================
  Items:
  Item     Weight   Value
  --------------------------
  1        1        1
  2        3        4
  3        4        5
  4        5        7
  Capacity : 7

  0/1 Knapsack DP Table:
        0  1  2  3  4  5  6  7
  -----------------------------
  i=0 |  0  0  0  0  0  0  0  0
  i=1 |  0  1  1  1  1  1  1  1
  i=2 |  0  1  1  4  5  5  5  5
  i=3 |  0  1  1  4  5  6  6  9
  i=4 |  0  1  1  4  5  7  8  9

  Selected Items:
  Item     Weight   Value
  --------------------------
  3        4        5
  2        3        4

  Maximum Value : 9

  // OBSERVATION:
  // If item fits: dp[i][w] = max(include, exclude)
  // Include     : values[i] + dp[i-1][w-weights[i]]
  // Exclude     : dp[i-1][w]
  // Time: O(n*W)  Space: O(n*W)

================================================
  3. MATRIX CHAIN MULTIPLICATION
================================================
  Matrix Dimensions:
  Matrix     Dimensions
  --------------------------------
  A1         30 x 35
  A2         35 x 15
  A3         15 x 5
  A4         5  x 10
  A5         10 x 20
  A6         20 x 25

  MCM DP Cost Table:
        A1      A2      A3      A4      A5      A6
  ------------------------------------------------------
  A1 |       0   15750    7875    9375   11875   15125
  A2 |  ------       0    2625    4375    7125   10500
  A3 |  ------  ------       0     750    2500    5375
  A4 |  ------  ------  ------       0    1000    3500
  A5 |  ------  ------  ------  ------       0    5000
  A6 |  ------  ------  ------  ------  ------       0

  Minimum Multiplications : 15125
  Optimal Parenthesisation: ((A1 x (A2 x A3)) x ((A4 x A5) x A6))

  // OBSERVATION:
  // dp[i][j] = min cost to multiply matrices i to j
  // Try all split points k between i and j
  // Cost = dp[i][k] + dp[k+1][j] + dims[i]*dims[k+1]*dims[j+1]
  // Time: O(n^3)   Space: O(n^2)

================================================
  OVERALL OBSERVATIONS
================================================
  1. LCS       : O(m*n)  - grows quadratically
  2. 0/1 Knap  : O(n*W)  - pseudo-polynomial
  3. MCM       : O(n^3)  - cubic growth

  DP vs Greedy:
  - DP guarantees OPTIMAL solution always
  - Greedy is faster but not always optimal
  - 0/1 Knapsack NEEDS DP (greedy fails here)
  - DP uses extra memory for the table
================================================
```

### Complexity Summary

| Algorithm | Time | Space |
|---|---|---|
| LCS | O(m·n) | O(m·n) |
| 0/1 Knapsack | O(n·W) | O(n·W) |
| Matrix Chain | O(n³) | O(n²) |

---


## Overall Algorithm Comparison

| Paradigm | Strategy | Optimal? | Time |
|---|---|---|---|
| Divide & Conquer | Split → Solve → Merge | ✅ Yes | O(n log n) |
| Greedy | Best local choice | Depends | O(n log n) |
| Dynamic Programming | Store subproblem results | ✅ Yes | Varies |

---
