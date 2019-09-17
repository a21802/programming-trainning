/*****************************************************************

In a 2 dimensional array grid, each value grid[i][j] represents the height of a building located there. We are allowed to increase the height of any number of buildings, by any amount (the amounts can be different for different buildings). Height 0 is considered to be a building as well. 

At the end, the "skyline" when viewed from all four directions of the grid, i.e. top, bottom, left, and right, must be the same as the skyline of the original grid. A city's skyline is the outer contour of the rectangles formed by all the buildings when viewed from a distance. See the following example.

What is the maximum total sum that the height of the buildings can be increased?

Example:
Input: grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
Output: 35
Explanation: 
The grid is:
[ [3, 0, 8, 4], 
  [2, 4, 5, 7],
  [9, 2, 6, 3],
  [0, 3, 1, 0] ]

The skyline viewed from top or bottom is: [9, 4, 8, 7]
The skyline viewed from left or right is: [8, 7, 9, 3]

The grid after increasing the height of buildings without affecting skylines is:

gridNew = [ [8, 4, 8, 7],
            [7, 4, 7, 7],
            [9, 4, 8, 7],
            [3, 3, 3, 3] ]

******************************************************************/
class Solution {
    
public:
    
/*     int rv_max(auto v){
        
        int max = -1;

        
        for(auto i : v){
            if(i > max) max = i;
        }
        
        return max;
        
    } */
    
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        
        int row = grid.size();
        int col = grid.front().size();
        int sum = 0;
        /*int c_max = 0, r_max = 0;
        int minmax = 0;
        
        for(int i = 0; i < col; i++){
            for(int j = 0; j < row; j++){
                
                c_max = -1;
                    
                for(int k = 0; k < row; k++)
                    c_max = (grid[k][i] > c_max ? grid[k][i] : c_max);
                r_max = rv_max(grid[j]);
                
                minmax = (c_max < r_max ? c_max : r_max);
                sum += minmax - grid[j][i];
            }
        } */
		
		vector<int> rmax(row);
		vector<int> cmax(col);
		int value = 0;
		
        for(int j = 0; j < row; j++){
			for(int i = 0; i < col; i++){
			
				value = grid[j][i];
				
				rmax[i] = max(rmax[i], value);
				cmax[j] = max(cmax[j], value);
			}
		}
		
		for(int i = 0; i < col; i++){
			for(int i = 0; i < col; i++){
			
				value = grid[j][i];
				sum += (max(rmax[i], cmax[j]) - value);
			
			}
		}
        
        return sum;
    }
};