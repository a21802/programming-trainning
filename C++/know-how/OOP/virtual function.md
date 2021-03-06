# 虛擬函數

當我們談到虛擬函數 (virtual function 或 virtual method) 時, 總是會和 "繼承" 與 "多型" 牽扯在一起. 虛擬函數就是指一個函數的行為可以在其所屬類別之衍生類別中被另一個和該函數具有相同簽名(signature) 之同名函數所重新設計和替換掉. 換句話說, 虛擬函數存在的目的就是讓衍生類別可以自行設計修改原有之函數行為.

## VTABLE / VPOINTER

虛擬函數的運作直接和 VPTR 和 VTABLE 有關。當類別的宣告中含有一個以上的虛擬函數時，編譯器就會為這個類別產生這兩樣東西：VTABLE 裡面存的是這個類別中所有的虛擬函數之位址，VPTR則是一個指向VTABLE的指標。編譯器處理/控制虛擬函數的方法是在每一個類別附加一個隱藏的data member (VPTR) 在此一data member中存放一個指向記載這些虛擬函數記憶體位址的一個特殊矩陣(VTABLE); 一個類別只有一個VTABLE，該 table 基本上就是編譯器在編譯該程式時產生的一個簡單的靜態 (static) 矩陣。基底類別和衍生類別都各自擁有自己的VTABLE.

類別的建構函數會令VPTR 指向VTABLE，當系統執行到程式在呼叫一個虛擬函數時， 系統會讓程式尋找該一物件object中所存放的vpointer並導引到相對應的 VTABLE 去取得該虛擬函數程式碼所在的位址並執行此一程式碼，這就是系統執行遇到虛擬函數時的處理運作過程。

如果衍生類別重新定義了某一虛擬函數, 則會在其VTABLE中更新該新虛擬函數之位址, 否則仍然存放該虛擬函數在基底類別的VTABLE中相同的位址. 如果衍生類別定義了新的虛擬函數, 則會在其VTABLE中加入該新虛擬函數之位址.

程式執行到一個衍生物件並開始建構時, 它的基底物件會先被建構起來並產生其VTABLE. 如果衍生類別有重新定義某個虛擬函數, 則衍生物件的建構函數會在該衍生物件的 VTABLE中更新被重新定義虛擬函數之位址. 這就是你不應該在建構函數中呼叫虛擬函數的原因: 衍生物件中被重定義的虛擬函數之位址可能還沒有被放入/更改到衍生物件之VTABLE中. 你可能執行到舊的虛擬函數.

C++的原則是 VPTR 會指向設定它的建構函數所屬類別的 VTABLE 。所以當衍生類別在呼叫基底類別的建構函數時，基底類別所設定的 VPTR 當然是指向基底類別的 VTABLE ，等到開始執行衍生類別的建構函數，這時衍生類別的 VPTR 就會指向衍生類別的 VTABLE 了。

## 沒有虛擬的建構元

建構元要根據物件的型別來建立 VTABLE 和設定 VPTR ，所以在執行建構元之前是沒有 VTABLE 和 VPTR 的，既然沒有 VTABLE 和VPTR 編譯程式要根據什麼去找到一個虛擬的建構元呢？

為什麼需要虛擬解構元？因為當我們透過指標或參考型別來使用物件時，到最後都必需用 delete 運算子將物件所佔有的記憶體歸還給系統， 如果解構元不是虛擬函數，那編譯程式將只呼叫原來指標被宣告所指向的類別，而不會呼叫指標真正所屬的類別的解構元，如此一來，將很容易產生記憶體遺失的狀況。

## 動態多型

虛擬函數可以實現「執行時期」的多型支援，是一個「晚期連結」（Late binding）、「動態連結」（Dynamic binding），也就是指必須在執行時期才會得知所要調用的物件或其上的公開介面。  

在談虛擬函數之前必須先知道，一個基礎類別的物件指標，可以用來指向其衍生類別物件而不會發生錯誤，例如若基底類別是Base，而衍生類別是Derived，則 下面這個指定是可以接受的：
``` 
Base *bptr; 
Derived d; 
bptr = &d;
```
多型與動態連結的基礎從這開始，它們只有在使用指標或參考時才得以發揮它們的特性，然而由於bptr仍是Base類型的指標，它只能存取Base中有定義的成員，目前來說也只能操作Base中的成員。

注意將衍生類別型態的指標指向基礎類別的物件基本是不可行的（雖然可以使用型態轉換的方式來勉強達成，但並不鼓勵），衍生類別的指標並不能存取基礎類別的成員。 

虛擬函數是一種成員函式，它在基礎類別中使用關鍵字"virtual"宣告（定義），並在衍生類別中重新定義虛擬函數，這將成員函數的操作決議 （Resolution）推遲至執行時期再決定。

虛擬函數可以實現執行時期的「多型」，也就是「一個介面，多種函式」，一個含有虛擬函數的類別被稱為「多型的類別」（Polymorphic class），當一個基礎類別型態的指標指向一個含有虛擬函數的衍生類別，您就可以使用這個指標來存取衍生類別中的虛擬函數。
```
#include <iostream> 
using namespace std; 

class Base { 
public: 
    virtual void show() { 
        cout << "Base's show" << endl; 
    } 
}; 

class Derived : public Base { 
public: 
    virtual void show() {
        cout << "Derived's show" << endl; 
    } 
}; 

void showFooByPtr(Base *foo) {
    foo->show();
}

void showFooByRef(Base &foo) {
    foo.show();
}

int main() { 
    Base f1; 
    Derived f2; 

    // 動態連結
    showFooByPtr(&f1); 
    showFooByPtr(&f2);
    cout << endl;
 
    // 動態連結
    showFooByRef(f1); 
    showFooByRef(f2);
    cout << endl; 

    // 靜態連結
    f1.show(); 
    f2.show(); 

    return 0;
}
```

# 純虛擬函數

在一些情況下，你希望衍生類別和基礎類別有一樣的介面(簽名、宣告)，但不樣的定義(實作)。與impure virtual function不同，pure virtual function要求你**一定**要重新定義該函式。純虛擬函數除了virtual 關鍵字外，還需要 **"= 0"**。
```
virtual void show() = 0;
```

- 宣告一個pure virtual function的目的是為了讓衍生類別只繼承函式介面
- 宣告一個impure virtual function的目的是為了讓衍生類別繼承該函式的介面和預設實作
- pure virtual function也可以有實作定義

```
#include <iostream>

using namespace std;

class Base{
public:
    virtual void show() = 0;
};

void Base::show(){
    cout << "Base" << endl;
}

class Derived : public Base{
public:
    virtual void show(){
        cout << "Derived" << endl;
    }
};


int main()
{
    Derived d;
    d.show();        // Derived
    d.Base::show();  // Base

    return 0;
}
```