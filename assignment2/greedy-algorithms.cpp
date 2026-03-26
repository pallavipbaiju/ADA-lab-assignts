#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <cmath>
using namespace std;


// 1. FRACTIONAL KNAPSACK

struct Item {
    char id;
    int  weight, value;
    double ratio;
};

bool compareItems(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Greedy solution
double fractionalKnapsack(Item items[], int n, int capacity) {
    for (int i = 0; i < n; i++)
        items[i].ratio = (double)items[i].value / items[i].weight;

    sort(items, items + n, compareItems);

    double totalValue = 0;
    int    remaining  = capacity;

    printf("\n  Selection process:\n");
    printf("  %s\n", string(52, '-').c_str());

    for (int i = 0; i < n; i++) {
        if (remaining == 0) break;

        if (items[i].weight <= remaining) {
            totalValue += items[i].value;
            remaining  -= items[i].weight;
            printf("  Took FULL  Item %c (w=%d, v=%d, ratio=%.2f) | +%d value\n",
                   items[i].id, items[i].weight,
                   items[i].value, items[i].ratio, items[i].value);
        } else {
            double frac   = (double)remaining / items[i].weight;
            double gained = frac * items[i].value;
            totalValue   += gained;
            printf("  Took %.2f%% of Item %c (w=%d, v=%d, ratio=%.2f) | +%.2f value\n",
                   frac * 100, items[i].id,
                   items[i].weight, items[i].value,
                   items[i].ratio, gained);
            remaining = 0;
        }
    }
    return totalValue;
}

// Brute-force: try all 2^n subsets (only whole items)
double Fractional01(Item items[], int n, int capacity) {
    double best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int    totalW = 0;
        double totalV = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                totalW += items[i].weight;
                totalV += items[i].value;
            }
        }
        if (totalW <= capacity && totalV > best)
            best = totalV;
    }
    return best;
}

// 2. ACTIVITY SELECTION PROBLEM

struct Activity {
    char id;
    int  start, end;
};

bool compareActivity(Activity a, Activity b) {
    return a.end < b.end;   // sort by finish time
}

void activitySelection(Activity acts[], int n) {
    sort(acts, acts + n, compareActivity);

    printf("\n  Activities sorted by finish time:\n");
    printf("  %-6s %-8s %-8s\n", "ID", "Start", "End");
    printf("  %s\n", string(24, '-').c_str());
    for (int i = 0; i < n; i++)
        printf("  %-6c %-8d %-8d\n", acts[i].id, acts[i].start, acts[i].end);

    printf("\n  Selection:\n");
    printf("  %s\n", string(40, '-').c_str());

    int    count    = 1;
    int    lastEnd  = acts[0].end;
    bool   selected[n];
    for (int i = 0; i < n; i++) selected[i] = false;
    selected[0] = true;

    printf("  Selected Activity %c [%d, %d)\n",
           acts[0].id, acts[0].start, acts[0].end);

    for (int i = 1; i < n; i++) {
        if (acts[i].start >= lastEnd) {
            selected[i] = true;
            lastEnd      = acts[i].end;
            count++;
            printf("  Selected Activity %c [%d, %d)\n",
                   acts[i].id, acts[i].start, acts[i].end);
        } else {
            printf("  Skipped  Activity %c [%d, %d)  <- overlaps\n",
                   acts[i].id, acts[i].start, acts[i].end);
        }
    }

    printf("\n  Total Activities Selected : %d / %d\n", count, n);
    printf("  Selected IDs : ");
    for (int i = 0; i < n; i++)
        if (selected[i]) printf("%c ", acts[i].id);
    printf("\n");
}

// 3. HUFFMAN CODING

struct HuffNode {
    char   ch;
    int    freq;
    HuffNode* left;
    HuffNode* right;

    HuffNode(char c, int f) {
        ch    = c;
        freq  = f;
        left  = right = NULL;
    }
};

// Min-heap comparator
struct Compare {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;
    }
};

// Generate codes by traversing tree
void generateCodes(HuffNode* root, string code,
                   string codes[], char chars[], int& idx) {
    if (!root) return;

    if (!root->left && !root->right) {   // leaf node
        chars[idx]   = root->ch;
        codes[idx++] = code;
        return;
    }
    generateCodes(root->left,  code + "0", codes, chars, idx);
    generateCodes(root->right, code + "1", codes, chars, idx);
}

// Print Huffman tree visually
void printTree(HuffNode* root, string prefix = "", bool isLeft = true) {
    if (!root) return;
    string connector = isLeft ? "+-[0]- " : "+-[1]- ";
    if (root->ch != '\0')
        printf("  %s%s '%c' (freq=%d)\n",
               prefix.c_str(), connector.c_str(), root->ch, root->freq);
    else
        printf("  %s%s [%d]\n",
               prefix.c_str(), connector.c_str(), root->freq);

    string newPrefix = prefix + (isLeft ? "|       " : "        ");
    printTree(root->left,  newPrefix, true);
    printTree(root->right, newPrefix, false);
}

void huffmanCoding(string text) {
    // Step 1: Count frequencies
    int freq[256] = {0};
    for (int i = 0; i < text.length(); i++) {
    	freq[(int)text[i]]++;
	}

    printf("\n  Character Frequencies:\n");
    printf("  %-8s %-8s\n", "Char", "Freq");
    printf("  %s\n", string(18, '-').c_str());
    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
            printf("  %-8c %-8d\n", (char)i, freq[i]);

    // Step 2: Build min-heap priority queue
    priority_queue<HuffNode*, vector<HuffNode*>, Compare> pq;
    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
            pq.push(new HuffNode((char)i, freq[i]));

    // Step 3: Build Huffman tree
    while (pq.size() > 1) {
        HuffNode* left  = pq.top(); pq.pop();
        HuffNode* right = pq.top(); pq.pop();

        HuffNode* merged = new HuffNode('\0', left->freq + right->freq);
        merged->left     = left;
        merged->right    = right;
        pq.push(merged);
    }

    HuffNode* root = pq.top();

    // Step 4: Generate codes
    string codes[256];
    char   chars[256];
    int    idx = 0;
    generateCodes(root, "", codes, chars, idx);

    printf("\n  Huffman Codes:\n");
    printf("  %-8s %-8s %-12s\n", "Char", "Freq", "Code");
    printf("  %s\n", string(30, '-').c_str());
    for (int i = 0; i < idx; i++)
        printf("  %-8c %-8d %-12s\n",
               chars[i], freq[(int)chars[i]], codes[i].c_str());

    // Step 5: Encode the text
    string encoded = "";
	for (int i = 0; i < text.length(); i++) {
		for (int j = 0; j < idx; j++){
        	if (chars[j] == text[i]) { encoded += codes[j]; break; }
        }
	}
    // Step 6: Compression ratio
    int originalBits   = text.length() * 8;
    int compressedBits = encoded.length();
    double ratio       = (double)originalBits / compressedBits;
    double savings     = (1.0 - (double)compressedBits / originalBits) * 100;

    printf("\n  Huffman Tree:\n");
    printTree(root);

    printf("\n  Original text    : %s\n",   text.c_str());
    printf("  Encoded bits     : %s\n",   encoded.c_str());
    printf("\n  Original bits    : %d\n",  originalBits);
    printf("  Compressed bits  : %d\n",   compressedBits);
    printf("  Compression ratio: %.2fx\n", ratio);
    printf("  Space savings    : %.1f%%\n", savings);
}

// ================================================
// MAIN
// ================================================
int main() {

    // -- 1. FRACTIONAL KNAPSACK ----------------
   
    printf("  \n1. FRACTIONAL KNAPSACK\n");
    

    Item items[] = {
        {'A', 2, 10}, {'B', 3,  5},
        {'C', 5, 15}, {'D', 7,  7},
        {'E', 1,  6}, {'F', 4, 18}
    };
    int n        = 6;
    int capacity = 15;

    printf("\n  Items:\n");
    printf("  %-6s %-8s %-8s\n", "ID", "Weight", "Value");
    printf("  %s\n", string(24, '-').c_str());
    for (int i = 0; i < n; i++)
        printf("  %-6c %-8d %-8d\n",
               items[i].id, items[i].weight, items[i].value);
    printf("  Capacity : %d\n", capacity);

    double greedy = fractionalKnapsack(items, n, capacity);
    printf("\n  Greedy  Max Value : %.2f\n", greedy);

    // Reset items for brute force (sort changes order)
    Item items2[] = {
        {'A', 2, 10}, {'B', 3,  5},
        {'C', 5, 15}, {'D', 7,  7},
        {'E', 1,  6}, {'F', 4, 18}
    };
    double brute = Fractional01(items2, n, capacity);
    printf("  Brute Force Value : %.2f (whole items only)\n", brute);
    printf("  Greedy >= BruteForce : %s\n", greedy >= brute ? "YES" : "NO");

    // Observation
    printf("\n  // OBSERVATION:\n");
    printf("  // Greedy gives optimal result for fractional knapsack.\n");
    printf("  // Sorting by value/weight ratio ensures maximum value\n");
    printf("  // per unit weight is always picked first.\n");
    printf("  // Brute-force only considers whole items (0/1),\n");
    printf("  // so greedy (with fractions) always >= brute-force.\n");

    // -- 2. ACTIVITY SELECTION -----------------
    printf(" \n 2. ACTIVITY SELECTION PROBLEM\n");

    Activity acts[] = {
        {'A', 1,  4}, {'B', 3,  5}, {'C', 0,  6},
        {'D', 5,  7}, {'E', 3,  9}, {'F', 5, 10},
        {'G', 6, 11}, {'H', 8, 12}, {'I', 8, 13},
        {'J', 2, 14}, {'K',12, 16}
    };
    int actCount = 11;

    printf("\n  Total Activities : %d\n", actCount);
    activitySelection(acts, actCount);

    printf("\n  // OBSERVATION:\n");
    printf("  // Greedy picks activity with earliest finish time first.\n");
    printf("  // This leaves maximum room for remaining activities.\n");
    printf("  // Guaranteed to give maximum number of non-overlapping\n");
    printf("  // activities — proven optimal greedy strategy.\n");

    // -- 3. HUFFMAN CODING ---------------------
    printf(" \n 3. HUFFMAN CODING\n");
   

    string text = "BCAADDDCCACACAC";
    printf("\n  Input text : %s\n", text.c_str());
    printf("  Length     : %d characters\n", (int)text.length());

    huffmanCoding(text);

    printf("\n  // OBSERVATION:\n");
    printf("  // Huffman coding assigns shorter codes to frequent chars.\n");
    printf("  // 'C' appears most (6x) -> gets shortest code.\n");
    printf("  // 'B' appears least (1x) -> gets longest code.\n");
    printf("  // Result is a prefix-free code (no code is prefix\n");
    printf("  // of another) — enables unambiguous decoding.\n");
    printf("  // Compression ratio > 1 means space is saved.\n");

    printf("\n================================================\n");
    printf("  OVERALL OBSERVATIONS\n");
    printf("================================================\n");
    printf("  1. Greedy is O(n log n) for all three algorithms.\n");
    printf("  2. Greedy is OPTIMAL for:\n");
    printf("       - Fractional Knapsack (fractions allowed)\n");
    printf("       - Activity Selection  (max activities)\n");
    printf("       - Huffman Coding      (min weighted path)\n");
    printf("  3. Greedy is NOT optimal for 0/1 Knapsack\n");
    printf("       -> use Dynamic Programming instead.\n");
    printf("================================================\n");

    return 0;
}

