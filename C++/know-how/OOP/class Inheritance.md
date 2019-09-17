# 繼承

C++有3種繼承的機制: public, protected, private，每種繼承方式會使衍生類別繼承自基礎類別的成員存取權限將有所不同。

- 不論衍生類別以何種繼承方式，基礎類別內private等級的成員皆會隱藏, 無法透過衍生類別的成員存取
- 衍生類別以private等級繼承基礎類別時，基礎類別內protected ,public等級成員則變成private等級被繼承
- 衍生類別以protected等級繼承基礎類別時，基礎類別內public等級成員則變成protected等級被繼承
- 衍生類別以public等級繼承基礎類別時，基礎類別內存取權限不改變
- 在類別外必須透過衍生類別成員函數才可存取繼承自基礎類別的資料成員

```
#include <iostream>

using namespace std;

class Base{
public:
    Base(): pub(1), pro(2), pri(3){}
    int pub;
    void pub_show(){
        cout << "base public ";
        cout << pub << endl;
    }
    void get_pri(){
        cout << pri << endl;
    }
    
protected:
    int pro;
    void pro_show(){
        cout << "base protect ";
        cout << pro << endl;
    }
    
private:
    int pri;
    void pri_show(){
        cout << "base private ";
        cout << pri << endl;
    }
    
};

class Derived1 : public Base{
public:
    void show(){
        cout << "Base public: " << pub << endl;
        cout << "Base protected: " << pro << endl;
        //cout << "Base private: " << pri << endl;  //can't see
    } 
};

class Derived2 : protected Base{
public:
    void show(){
        cout << "Base public: " << pub << endl;
        cout << "Base protected: " << pro << endl;
        //cout << "Base private: " << pri << endl;  //can't see
    } 
};

class Derived3 : private Base{
public:
    void show(){
        cout << "Base public: " << pub << endl;
        cout << "Base protected: " << pro << endl;
        //cout << "Base private: " << pri << endl;  //can't see
    } 
};

int main()
{
    Derived1 d1;
    Derived2 d2;
    Derived3 d3;
    
    d1.show();
    d1.pub_show();
    //d1.pro_show();          //can't see
    cout << d1.pub << endl;
    //cout << d1.pro << endl; //can't see
    d1.get_pri();
    
    cout << "=====" << endl;
    
    d2.show();
    //d2.pub_show();          //can't see
    //cout << d2.pub << endl; //can't see
    
    cout << "=====" << endl;
    
    d3.show();

    return 0;
}
```