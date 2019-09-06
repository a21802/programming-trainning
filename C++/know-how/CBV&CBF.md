# call by value(傳值)

> swap內的a、b變數地址明顯與main內的x、y地址相異
> 理所當然的不能對換x、y的值

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

> C++有，C沒有
> 只需將上述swap界面改成

```
void swap(int &a, int &b)
```


