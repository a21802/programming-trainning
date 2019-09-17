# 重(覆)寫

> 指衍生類別的函數遮蔽了與其同名的基礎類別函數，規則如下:
  
- 如果衍生類別的函數與基礎類別的函數同名，但參數不同。此時，不論有無virtual關鍵字，基礎類別的函數將被隱藏(注意別與重(多)載混淆)
- 如果衍生類別的函數與基礎類別的函數同名，並且參數也相同。但基礎類別沒有virtual關鍵字。此時，基礎類別的函數被隱藏(注意別與覆蓋混淆)
- ps.當子物件強制轉換成父類型時，會呼叫父類別功能，因為只被遮蔽。
- ps2.可參考-hiding inherited name.md-

```
#include <iostream>
using namespace std;

class Base{
	public:
     	void func(){
			cout<< "0" <<endl;
		}
		void func1(){
			cout<< "0" <<endl;
		}
};

class DRBase: public Base{ 
	public:
		void func(){
			cout<< "1" <<endl;
            // Base::func(); //如果增加這行且省略上一行 將可用b2 直接呼叫
            //父類別的func ( b2.func() )
		}
		void func2(){
			cout<< "1" <<endl;
		}
};

int main(){

	Base b1;
    b1.func();      // 0
    
    DRBase b2; 
    b2.func();      // 1
    b2.func1();     // 0
    b2.func2();     // 1
    
    Base b3 = b2;   
    b4.func();      // 0
    
    Base* b4 = new DRBase(); // 父類別指標接子參考，沒有virtual關鍵字不會達成動態多型
    b4->func();     // 0
	
	return 0;
}

```
