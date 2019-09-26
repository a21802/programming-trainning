#Pointer

#### reference:
> https://bluelove1968.pixnet.net/blog/post/222285085-c-%E8%AA%9E%E8%A8%80%E6%8C%87%E6%A8%99%E7%9A%84%E7%94%A8%E6%B3%95
> https://h0are.wordpress.com/2016/04/02/掌握了指標的人就能掌握c/
> https://en.cppreference.com/w/c/language/operator_precedence
> https://openhome.cc/Gossip/CppGossip/FunctionPointer.html
> https://codertw.com/%E7%A8%8B%E5%BC%8F%E8%AA%9E%E8%A8%80/482502/

指標判讀大原則為**從右讀到左**

```
int a; // 一個整數型
int *a; // 一個指向整數的指標
int **a; // 一個指向指標的指標，它指向的指標是指向一個整數型
int a[10]; // 一個有10個整數型的陣列
int *a[10]; // 一個有10個指標的陣列，該指標是指向一個整數型的
int (*a)[10]; // 一個指向有10個整數型陣列的指標
int (*a)(int); // 一個指向函數的指標，該函數有一個整數型參數並返回一個整數
int (*a[10])(int); // 一個有10個指標的陣列，該指標指向一個函數，該函數有一個整數型參數並返回一個整數
```

指標與前後置遞增配合:  
\* 與 ++ 優先度相同，因此靠右的先做

```
*ptr++   // 
*(ptr++) // 同上
(*ptr)++ //
*++ptr   // 
*(++ptr) // 同上
++*ptr   // 
++(*ptr) // 同上
```

```
#include <iostream>

using namespace std;

int main()
{
    char s[] = "0918276";
    char *p = s;

    printf("%c", *p++);    // 0
    printf("%c", *(p++));  // 9
    printf("%c", (*p)++);  // 1
    printf("%c", *++p);    // 8
    printf("%c", *(++p));  // 2
    printf("%c", ++*p);    // 3
    printf("%c", ++(*p));  // 4

    printf("\n");
    printf(s);             // 0928476
    

    return 0;
}
```

函數指標陣列應用: **不用if判斷式**來選擇函數

```
#include <iostream>

using namespace std;

void func1(){ cout << "in fun1" << endl; }
void func2(){ cout << "in fun2" << endl; }
void func3(){ cout << "in fun3" << endl; }
void func4(){ cout << "in fun4" << endl; }
void func5(){ cout << "in fun5" << endl; }

void (*show[5])() = {func5, func1, func2, func3, func4};

int main()
{
    show[1%5]();  // in fun1
    show[2%5]();  // in fun2
    show[3%5]();  // in fun3
    show[4%5]();  // in fun4
    show[5%5]();  // in fun5

    return 0;
}
```