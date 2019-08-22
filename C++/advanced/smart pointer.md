# smart pointer

> reference  
> https://kheresy.wordpress.com/2012/03/03/c11_smartpointer_p1/

## UNIQUE_PTR

確保一份資源（被配置出來的記憶體空間）只會被一個 unique_ptr 物件管理的 smart pointer；當 unique_ptr 物件消失時，就會自動釋放資源。

```
unique_ptr<int> a( new int(0) );
unique_ptr<int> b = a;  // compile error!
unique_ptr<int> c = move( a );
```

## SHARED_PTR

可以有多個 shared_ptr 共用一份資源的 smart pointer，內部會記錄這份資源被使用的次數（reference counter），只要還有 shared_ptr 物件的存在、資源就不會釋放；只有當所有使用這份資源的 shared_ptr 物件都消失的時候，資源才會被自動釋放。

```
{
    shared_ptr<int> a;  // a is empty
    {
        shared_ptr<int> b( new int( 10 ) );  // allocate resource
        a = b;  // reference counter: 2
        {
            shared_ptr<int> c = a;  // reference counter: 3
            *c = 100;
        }  // c dead, reference counter: 2
    } // b dead, reference counter: 1

    cout << *a << endl;
}  // release resource
```

## WEAK_PTR

搭配 shared_ptr 使用的 smart pointer，和 shared_ptr 的不同點在於 weak_ptr 不會影響資源被使用的次數，也就是說的 weak_ptr 存在與否不代表資源會不會被釋放掉。它基本上也不能用來做資料的存取，主要只能用來監控 shared_ptr 目前的狀況。

```
weak_ptr<int> w1;
{
    shared_ptr<int> a( new int(10) );
    w1 = a;
}
shared_ptr<int> b = w1.lock();

if( b != nullptr )
    cout << *b << endl;
else
    cout << "null" << endl;
```