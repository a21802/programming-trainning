/******************************************************************************

Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in arr2 are also in arr1.

Sort the elements of arr1 such that the relative ordering of items in arr1 are the same as in arr2.  Elements that don't appear in arr2 should be placed at the end of arr1 in ascending order.

 

Example 1:

Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
Output: [2,2,2,1,4,3,3,9,6,7,19]


*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Solution {    
public:
    void swap(int &x, int &y){
        x = x ^ y;
        y = x ^ y;
        x = x ^ y;
    }
    
    void shift(vector<int> &arr, int i, int j){
        int k;
        for(k = j; k > i; k--)
            swap(arr[k], arr[k - 1]);
    }
    
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        int j = 0, k, size = arr1.size(), index = 0;
        int size2 = arr2.size();
        bool flag;
            
        while(index < size2){
            flag = false;
                 
            if(arr1[j] == arr2[index]){
                j++;
                if(j >= size - 1) break;
                continue;
            }
            else{
                k = j + 1;
                    
                while(k < size){
                    if(arr1[k] == arr2[index]){
                        flag = true;
                        break;
                    } 
                    k++;
                }
                if(flag){
                    shift(arr1, j, k);
                    j++;
                }
                else
                    index++;
            }
        }
        
        sort(arr1.begin() + j, arr1.end());
        
        return arr1;
    }
};

int main()
{
    Solution s;

    // vector<int> arr1 = {943,790,427,722,860,550,225,846,715,320};
    // vector<int> arr2 = {943,715,427,790,860,722,225,320,846,550};
    
    vector<int> arr1 = {28,6,22,8,44,17};
    vector<int> arr2 = {22,28,8,6};
    
    
    for(auto i : s.relativeSortArray(arr1, arr2))
        cout << i << " ";

    return 0;
}
