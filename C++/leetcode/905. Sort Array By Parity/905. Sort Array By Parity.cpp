/******************************************************************************

Given an array A of non-negative integers, return an array consisting of all the even elements of A, followed by all the odd elements of A.

You may return any answer array that satisfies this condition.

 

Example 1:

Input: [3,1,2,4]
Output: [2,4,3,1]
The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.


*******************************************************************************/

#include <iostream>

using namespace std;

class Solution {
public:
    
    int is_odd(int x)  
    {  
        return x & 1;   // x % 2;  
    }  
    
    void swap(int& x, int& y)  
    {  
        x = x ^ y; // x' = x ^ y  
        y = x ^ y; // y' = x' ^ y = x ^ y ^ y = x  
        x = x ^ y; // x = x' ^ y' = x ^ y ^ x = y
    } 
    
    vector<int> sortArrayByParity(vector<int>& A) {
        int len = A.size();
        int front = 0, end = len - 1;
        
        while(front < end){
            
            while(!is_odd(A[front])){
                front++;
                if(front > len - 1) return A;
            }
        
            while(is_odd(A[end])){
                end--;
                if(end < 0) return A;
            }
            
            if(front < end)
                swap(A[front], A[end]);
            
            front++;
            end--;
            
        }
        
        return A;
    }
};
