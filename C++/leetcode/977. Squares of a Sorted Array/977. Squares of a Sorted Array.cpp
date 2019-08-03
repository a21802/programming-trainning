/******************************************************************************

Given an array of integers A sorted in non-decreasing order, return an array of the squares of each number, also in sorted non-decreasing order.

 

Example 1:

Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]

Example 2:

Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]


*******************************************************************************/

#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
//         for(auto &i : A)
//             i *= i;
        
//         sort(A.begin(), A.end());
        
//         return A;
        
        int i = 0, j = A.size() - 1, idx = j;
        vector<int> res(A.size());
        while (i <= j) {
            if (abs(A[i]) > abs(A[j])) {
                res[idx] = A[i] *A[i];
                i++;
                idx--;
            } else {
                res[idx] = A[j] * A[j];
                j--;
                idx--;
            }
        }
        return res;
    }
};
