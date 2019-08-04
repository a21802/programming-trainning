/******************************************************************************

Given an array A of non-negative integers, half of the integers in A are odd, and half of the integers are even.

Sort the array so that whenever A[i] is odd, i is odd; and whenever A[i] is even, i is even.

You may return any answer array that satisfies this condition.

 

Example 1:

Input: [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.


*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

	bool IsEven (int i) { 
        return (i%2) == 0; 
    }
    
    bool same(int i, int j){
        if( (i % 2) == (j % 2) )
            return true;
        else
            return false;
    }
    
    void swap(int &x, int &y){
        x = x ^ y;
        y = x ^ y;
        x = x ^ y;
    }
    
    vector<int> sortArrayByParityII(vector<int>& A) {
        /* int i, j; 
        int size = A.size();
        bool flag;
        
        for(i = 0; i < size - 1; i++){
            
            if(same(A[i], i)) 
                continue;
            else{
                flag = false;
                j = i + 1;
                while(j <= size - 1){
                    
                    if(!same(A[j], j) && !same(i, j)){
                        flag = true;
                        break;
                    }  
                    
                    j++;
                }
                if(flag)
                    swap(A[i], A[j]);
                    
            }
        }
        
        return A; */
		
		auto bound = std::partition (A.begin(), A.end(), 
                                     [](int x) { return x % 2 == 0;});
        
        auto it = A.begin();
        
        int i = 0, size = A.size();
        vector<int> temp;
        
        while(i < size){
            
            if(IsEven(i)){
                temp.push_back(*it);
                it++;
            }
            else{
                temp.push_back(*bound);
                bound++;
            }
            i++;
    
        }
       
        
        return temp;
    }
};

int main()
{
    Solution s;

    //vector<int> arr = {4,2,5,7};
    //vector<int> arr = {648,831,560,986,192,424,997,829,897,843};
    vector<int> arr = {2,3,1,1,4,0,0,4,3,3};
    for(auto k : arr)
        cout << k << " ";
    cout << endl;
    
     for(auto i : s.sortArrayByParityII(arr))
         cout << i << " ";

    return 0;
}
