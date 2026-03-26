# ENCS256 – Lab Assignment 2

**Course:** Analysis and Design of Algorithms Lab  
**Program:** BTech | Semester IV | Session 2025-26  
**Faculty:** Dr. Rupendra Hada

---

## Files

| File | Algorithm |
|------|-----------|
| `frac_knapsack.cpp` | Fractional Knapsack |
| `job_sequencing.cpp` | Job Sequencing with Deadline |

---


---

## 1. Fractional Knapsack

### Approach
- Calculate value/weight ratio for each item
- Sort items by ratio in descending order
- Greedily pick items — take the full item if it fits, otherwise take the fraction that fills remaining capacity

### Input
- **Capacity:** 100  
- **Items:**

| Weight | Value | Ratio |
|--------|-------|-------|
| 10     | 100   | 10.00 |
| 50     | 150   | 3.00  |
| 40     | 160   | 4.00  |
| 25     | 175   | 7.00  |
| 20     | 200   | 10.00 |
| 35     | 350   | 10.00 |

### Output
```
   Fractional Knapsack
 CAPACITY : 100
SELECTION:-

 Took Full Item(w=10, v=100, ratio =10.00) | +100 value
 Took Full Item(w=20, v=200, ratio =10.00) | +200 value
 Took Full Item(w=35, v=350, ratio =10.00) | +350 value
 Took Full Item(w=25, v=175, ratio =7.00)  | +175 value
Took 25.00% of Item(w=40, v=160, ratio=4.00) | +40.000000 value
   Maximum value = 865.00
```

### Observation
- Items with ratio 10.00 (w=10, w=20, w=35) are taken fully first.
- Item with ratio 7.00 (w=25) is taken fully next.
- Only 25% of the last item (w=40) is taken to fill the remaining 10 units of capacity.
- Greedy selection by ratio always gives the optimal solution for fractional knapsack.

---

## 2. Job Sequencing with Deadline

### Approach
- Sort jobs by profit in descending order
- For each job, assign it to the latest available time slot on or before its deadline
- Skip the job if no free slot exists before its deadline

### Input

| Job | Deadline | Profit |
|-----|----------|--------|
| A   | 2        | 100    |
| B   | 1        | 19     |
| C   | 2        | 27     |
| D   | 1        | 25     |
| E   | 3        | 15     |

### Output
```
     Job Sequencing with Deadline - Greedy

Jobs (id, deadline, profit):
    Job A -> deadline=2, profit=100
    Job B -> deadline=1, profit=19
    Job C -> deadline=2, profit=27
    Job D -> deadline=1, profit=25
    Job E -> deadline=3, profit=15

 Scheduling process:
 Job A -> slot 2  | profit = 100
 Job C -> slot 1  | profit = 27
 Job E -> slot 3  | profit = 15


 SCHEDULED JOBS :
CAE
 Total Jobs Done : 3
 Total Profit : 142
```

### Observation
- Jobs sorted by profit: A(100) > C(27) > D(25) > B(19) > E(15).
- Job A is assigned slot 2 (latest free slot ≤ deadline 2).
- Job C is assigned slot 1 (latest free slot ≤ deadline 2).
- Jobs B and D are skipped — slot 1 is already taken by C.
- Job E fits into slot 3 with no conflict.
- Maximum achievable profit = **142**.
