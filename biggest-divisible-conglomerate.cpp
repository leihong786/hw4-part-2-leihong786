
#include "bdc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// bottom up tabulation method

// Function to find the largest subset such that for every pair (i, j) in the subset,
// nums[i] % nums[j] == 0 or nums[j] % nums[i] == 0
vector<int> biggest_divisible_conglomerate(vector<int> nums) {
    // Edge case: return empty vector if input is empty
    if (nums.empty()) return {};

    // sort the input to ensure that for any valid subset, as given in the pdf 
    // a smaller number will come before a larger one
    sort(nums.begin(), nums.end());
    int n = nums.size();

    // dp[i] stores the length of the largest divisible subset ending at index i
    vector<int> dp(n, 1);

    // prev[i] stores the index of the previous element in the subset ending at i
    // Used later for backtracking to reconstruct the actual subset
    vector<int> prev(n, -1);

    // This keeps track of the index at which the largest subset ends
    int max_idx = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // If nums[i] is divisible by nums[j], check if we can extend the subset
            if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1; // Update length
                prev[i] = j;       // Track path
            }
        }

        // Update the index of the largest subset found so far
        if (dp[i] > dp[max_idx]) {
            max_idx = i;
        }
    }

    //  reconstruct the largest divisible subset using prev[]
    vector<int> result;
    for (int i = max_idx; i >= 0; i = prev[i]) {
        result.push_back(nums[i]);
        if (prev[i] == -1) break; // Reached the start of the chain
    }

    // reverse the reverse to get the correct order
    reverse(result.begin(), result.end());
    return result;
}

// Helper function to convert a vector of integers to a formatted string
string vec_to_string(vector<int> v) {
    string result = "[";
    for (size_t i = 0; i < v.size(); i++) {
        result += to_string(v[i]);
        if (i != v.size() - 1) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}
