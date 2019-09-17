# call by value(傳值)

> swap 內的 a、b 變數地址明顯與main內的 x、y 地址相異
> 理所當然的不能對換 x、y 的值

```
#include <iostream>
using namespace std;

void swap(int a, int b){
    int tmp = a;
    a = b;
    b = tmp;
    cout << "in foo: " << endl;
    cout << "a = " << a << ", b = " << b << endl; 
    cout << "address: " << "a = " << &a << ", b = " << &b << endl;
}

int main()
{
    int x = 0;
    int y = 10;
    
    cout << "in main: " << endl;
    cout << "x = " << x << ", y = " << y << endl;   // x = 0, y = 10
    cout << "address: " << "x = " << &x << ", y = " << &y << endl; 
    
    foo(x, y);                                      // a = 10, b = 0
    
    cout << "in main: " << endl;
    cout << "x = " << x << ", y = " << y << endl;   // x = 0, y = 10
    cout << "address: " << "x = " << &x << ", y = " << &y << endl; 

    return 0;
}
```

# call by reference(傳參考)

> C++ 有，C 沒有
> 只需將上述 swap 參數改成

```
void swap(int &a, int &b)
```


