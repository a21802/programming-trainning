# 重(多)載
在C++程式中，可以將語義、功能相似的幾個函數用同一個名字表示，但參數不同(包括類型、順序不同)，即函數重(多)載。  
 
- 相同的範圍(在同一類別中)  
- 函數名稱相同  
- 參數不同  
- virtual關鍵字可有可無
- 返回值型態不能作為函式重載的依據

```
#include <iostream>

using namespace std;

class A{
public:
    void func(int x){
        cout << x << endl;
    }
    void func(int x, int y){
        cout << x << ", " << y << endl;
    }
    
};

int main()
{
    A a;
    a.func(1);     // 1
    a.func(2, 3);  // 2, 3 

    return 0;
}
```
