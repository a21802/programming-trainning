// https://onlinegdb.com/H1hXY0-XH
/******************************************************************************

Given a valid (IPv4) IP address, return a defanged version of that IP address.

A defanged IP address replaces every period "." with "[.]".

 

Example 1:

Input: address = "1.1.1.1"
Output: "1[.]1[.]1[.]1"

Example 2:

Input: address = "255.100.50.0"
Output: "255[.]100[.]50[.]0"


*******************************************************************************/

#include <iostream>

using namespace std;

class Solution {
public:
    string defangIPaddr(string address) {
        string address_extend;
        for(auto i: address){
            if(isdigit(i))
                address_extend += i;
            else
                address_extend += "[.]";
        }
        
        return address_extend;
    }
};

int main()
{
    Solution s;
    
    cout << s.defangIPaddr("1.1.1.1");

    return 0;
}
