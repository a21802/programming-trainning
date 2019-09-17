/******************************************

You have a set of tiles, where each tile has one letter tiles[i] printed on it.  Return the number of possible non-empty sequences of letters you can make.

 

Example 1:

Input: "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
Example 2:

Input: "AAABBC"
Output: 188

******************************************/

class Solution {
public:

    void rec(vector<int>& v, int& sum)
    {

        for(int& i : v){

            if(i == 0) 
                continue;
            else{
                sum += 1;
                i -= 1;
                rec(v, sum);
                i += 1;
            }
        }
    }
    
    int numTilePossibilities(string tiles) {
        
        vector<int> counts(26);
        int sum = 0;
        
        for (const auto &c :  tiles) {
            counts[c - 'A']++;
        }
        
        rec(counts, sum);
        return sum;
    }
};