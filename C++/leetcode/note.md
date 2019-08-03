# leetcode技巧
## 字串轉小(大)寫
> 小寫的ASCII code比大寫多*32*
```
if(str[i]>='A' && str[i]<='Z'){
    str[i] = (char)(str[i]+32);
}
```
## 判斷一個整數是不是 2 的次方
```
bool is_power_of_2(int x)  
{  
    return (x & -x) == x;  
}  
```
##  交換兩個 int 變數 
```
void swap(int& x, int& y)  
{  
    x = x ^ y; // x' = x ^ y  
    y = x ^ y; // y' = x' ^ y = x ^ y ^ y = x  
    x = x ^ y; // x = x' ^ y' = x ^ y ^ x = y  
} 
```
