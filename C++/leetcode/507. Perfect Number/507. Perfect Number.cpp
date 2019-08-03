/******************************************************************************

We define the Perfect Number is a positive integer that is equal to the sum of all its positive divisors except itself.
Now, given an integer n, write a function that returns true when it is a perfect number and false when it is not.

Example:

Input: 28
Output: True
Explanation: 28 = 1 + 2 + 4 + 7 + 14

*******************************************************************************/

#include <iostream>
#include <list>
#include <math.h>

using namespace std;

class Solution {
public:
    bool checkPerfectNumber(int num) {
        list<int> factors = {1};
        
        int root = sqrt(num);
        int sum = 0;
        
        for(int i = 2; i <= root; i++){
            
            if(num % i == 0){
                factors.push_back(i);
                if(i != num / i)
                    factors.push_back(num/i);
            }
        }
        
        for(auto a : factors){
            sum += a;
            cout << a <<endl;
        }
        cout << sum << endl;
        
        if(num == sum) return true;
        else           return false;
    }
};

int main()
{
    Solution s;
    
    cout << s.checkPerfectNumber(28);

    return 0;
}
