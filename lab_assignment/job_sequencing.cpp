#include <iostream>
#include <algorithm>
using namespace std;

struct Job{
	char id;
	int deadline;
	int profit;
};

bool compare(Job a, Job b){
	return a.profit > b.profit;
}

void jobSequencing(Job jobs[], int n){
	sort(jobs, jobs + n, compare);
	
	int maxDeadline =0;
	for(int i=0;i<n; i++){
		if(jobs[i].deadline > maxDeadline)
			maxDeadline =jobs[i].deadline;
	}
	char slot[maxDeadline +1];
	bool filled[maxDeadline +1];
	
	for(int i=0; i<=maxDeadline; i++){
		slot[i] ='-';
		filled[i] =false;
	}
	int totalProfit =0;
	int jobCount =0;
	
	printf("\n Scheduling process: \n");
	
	for(int i =0; i<n; i++){
		for(int j =jobs[i].deadline; j>=1;j--){
			if(!filled[j]){
				slot[j] =jobs[i].id;
				filled[j] =true;
				totalProfit += jobs[i].profit;
				jobCount++;
				printf(" Job %c -> slot %d  | profit = %d \n",
				jobs[i].id, j, jobs[i].profit);
				break;
			}
		}
	}
	
	printf("\n\n SCHEDULED JOBS :  \n");
	for(int i=1; i<=maxDeadline; i++){
		if(filled[i]){
			printf("%c",slot[i]);
		}
	}
	printf("\n Total Jobs Done : %d", jobCount);
	printf("\n Total Profit : %d", totalProfit);
}

int main(){
	Job jobs[] ={{'A', 2, 100},
        {'B', 1,  19},
        {'C', 2,  27},
        {'D', 1,  25},
        {'E', 3,  15}
    };
    
    int n =5;
    
    printf("     Job Sequencing with Deadline - Greedy\n");
    printf("  \nJobs (id, deadline, profit):\n");
    for (int i = 0; i < n; i++)
        printf("    Job %c -> deadline=%d, profit=%d\n",
                jobs[i].id, jobs[i].deadline, jobs[i].profit);

    jobSequencing(jobs, n);

    return 0;
}

