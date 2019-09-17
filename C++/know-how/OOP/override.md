# 覆蓋

> 指衍生類別覆蓋基礎類別，特徵是:

- 不同的範圍(分別位於衍生類別與基礎類別)
- 函數名稱相同
- 參數相同
- 基礎類別必須有virtual關鍵字
- ps. 當子物件強制轉換成父類型時，會呼叫子類別功能，因為已經被覆蓋

```
#include <iostream>
using namespace std;

class Base{
	public:
     	virtual void func(){
			cout<< "0" <<endl;
		}
};

class DRBase: public Base{ 
	public:
		void func(){
			cout<< "1" <<endl;
		}
};

int main(){

	Base b1;
    b1.func();      // 0
    
    DRBase b2; 
    b2.func();      // 1
    
    Base* b3 = new DRBase();
    b3->func();     // 1
	
	return 0;
}
```