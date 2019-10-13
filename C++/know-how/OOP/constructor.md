# 建構子 & 解構子

利用建構子可以幫助物件進行初始化，並且利用解構子進行記憶體的釋放。若是在類別中沒有定義建構子或是解構子，編譯器會自動生成一個無參數、沒有實作內容的建(解)構函式。

### 建構子:
- 與類別名稱相同
- 為公開的成員函式
- 沒有回傳值
- 可以多載

### 解構子:
- 與類別名稱相同
- 為公開的成員函式
- 在函式前加上 " ~ " 符號
- 沒有回傳值
- 只能有一個(不予許多載)

```
#include <iostream>
using namespace std;

class Test{
    
public:
    Test(){
        cout << "無參數建構子" << endl;
    }
    
    Test(int i){
        cout << "有參數建構子 " << i << endl;
    }
    
    Test(const Test& t){
        m_data = t.m_data;
        cout << "複製建構子 " << m_data << endl;
    }
    
    ~Test(){
        cout << "解構子" << endl;
    }
    
private:
    int m_data; 
};

void callTest(){
    
    // 調用方法
    // 1. 傳入參數
    Test T1;     // 無參數建構子，ps1.
    Test T2(10); // 有參數建構子
    Test T3(T2); // 複製建構子
    cout << "====================" << endl;
    
    // 2. 顯示法
    Test T4 = Test(20); // 有參數建構子
    Test T5 = Test(T4); // 複製建構子

    Test(30); // 匿名物件，ps2.
    cout << "匿名物件在這之前就會解構"
    
    //Test(T2); // ps3.
    cout << "====================" << endl;
    
    // 3. 隱式轉換
    Test T6 = 40; // 相當於 Test T6 = Test(40); 有參數建構子
    Test T7 = T6; // 複製建構子
}

int main()
{
    callTest();

    return 0;
}

```
 ### ps
1. 調用無參數建構子時, 不能加 "( )"，編譯器會認為是函式宣告
2. 匿名物件在執行完的當下就會被回收
3. 不要利用複製建構子初始化匿名物件，編譯器會認為是重複定義
```
Test(T2) === Test T2
```