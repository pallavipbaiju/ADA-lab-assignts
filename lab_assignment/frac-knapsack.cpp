#include <iostream>
#include <algorithm>
using namespace std;

struct Item{
	int weight, value;
	double ratio;
};

bool compare(Item a, Item b){
	return a.ratio > b.ratio;
}

double fractionalKnapsack(Item items[], int n, int capacity){
	for(int i=0; i<n; i++){
		items[i].ratio =(double)items[i].value / items[i].weight;
	}
	sort(items, items + n, compare);
	
	double totalValue =0;
	int remaining =  capacity;
	
	printf("SELECTION:-\n\n");
	
	for (int i=0;i<n;i++){ // if item can be taken fully
		if(remaining ==0) break;
		
		if(items[i].weight <= remaining){
			totalValue += items[i].value;
			remaining -= items[i].weight;
			
			printf (" Took Full Item(w=%d, v=%d, ratio =%.2f) | +%d value\n",
			items[i].weight, items[i].value, items[i].ratio, items[i].value);
		}else{ // if inly a fraction of item can be taken
			double fraction =(double)remaining/ items[i].weight;
			double gained = fraction * items[i].value;
			totalValue += gained;
			
			printf("Took %.2f%% of Item(w=%d, v=%d, ratio=%.2f) | +%2f value\n",
			fraction *100, items[i].weight, items[i].value, items[i].ratio,gained);
			
			remaining =0;
		}
	}
	return totalValue;
}

int main(){
	Item items[] ={{10,100},{50,150},{40,160},{25,175},{20,200},{35,350}};
	int n =6;
	int capacity =100;
	
	printf("   Fractional Knapsack    \n");
	printf(" CAPACITY : %d\n", capacity);
	
	double result = fractionalKnapsack(items,n,capacity);
	
	printf("   Maximum value = %.2f ",result);
	return 0;
}
