# 名稱遮蔽規則
```
#include <iostream>

using namespace std;

int x = 10;

void f(){
    int x = 5;
    cout << x << endl; // 5
}

int main()
{
    f();
    cout << x << endl; // 10

    return 0;
}
```
> 上述f()內指涉的是local變數x，而不是global變數x，因為內層作用域的名稱會遮掩(遮蔽)外圍作用域的名稱。  
> 以下的程式碼，讓base class內所有名為f1和f3的函式都被derived class內的f1和f3函式遮掩掉了。從名稱搜尋觀點來看，Base::f1和Base::f3不再被Derived繼承。
```
#include <iostream>

using namespace std;

class Base{
private:
    int x;
public:
    virtual void f1(){
        cout << "base f1" << endl;
    }
    virtual void f1(int){
        cout << "base f1 int" << endl;
    }
    virtual void f2(){
        cout << "base f2" << endl;
    }
    void f3(){
        cout << "base f3" << endl;
    }
    void f3(double){
        cout << "base f3 double" << endl;
    }
    
};

class Derived: public Base{
public:
    virtual void f1(){
        cout << "derived f1" << endl;
    }
    void f3(){
        cout << "derived f3" << endl;
    }
    void f4(){
        cout << "derived f4" << endl;
    }
};


int main()
{
    Derived d;
    int x;
    
    d.f1();         // OK, derived f1
    // d.f1(x);     // wrong
    d.f2();         // OK, base f2
    d.f3();         // OK, derived f3
    //d.f3(x);      // wrong
    d.f4();         // OK, derived f4

    return 0;
}
```
> 如果你繼承base calss並加上重載函式，而你又希望而你又希望重新定義或覆寫其中一部分，那麼你必須為那些被遮掩的每個名稱引入一個using宣告式，否則某些你希望繼承的名稱會被遮掩。
```
class Derived: public Base{
public:
    using Base::f1;
    using Base::f3;

    virtual void f1();
    void f3();
    void f4();
};

...

Derived d;
int x;
    
d.f1();         // still OK
d.f1(x);        // OK now, call Base::f1
d.f2();         // still OK
d.f3();         // still OK
d.f3(x);        // OK now, call Base::f3
d.f4();         // still OK
```