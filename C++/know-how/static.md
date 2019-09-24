# static

#### reference:  
> http://kamory0931.pixnet.net/blog/post/119201381-c%2B%2B%E7%9A%84static  
> https://yodalee.blogspot.com/2012/11/c-static.html  
> https://medium.com/@alan81920/c-c-%E4%B8%AD%E7%9A%84-static-extern-%E7%9A%84%E8%AE%8A%E6%95%B8-9b42d000688f

首先先將 static 修飾詞出現的位置分成幾部分:

### 全域函式/變數前

代表著是這個函式/變數的scope只限於當下定義的檔案中。  
也就是說雖然是全域函式/變數在編譯的過程中，別的檔案裡的code即使用extern的方式宣告想要使用它也是不行的。

### 函式內的成員變數前

函式內的靜態變數較區域變數有永久存在的特性，一般而言區域變數存在於stack中隨著函式呼叫而起，隨著return而終。
但是靜態變數則是存於data segment的BSS中 ([Data Segment@wiki](https://en.wikipedia.org/wiki/Data_segment))擁有完整的程式執行生命周期。

### (C++) class 內的成員變數/函式前

在 class 裡把成員變數宣告成 static，代表他是「與 class 相關連」，而不是「與物件相關連」。他獨立配置記憶體，獨立於 class 的任何物件而存在，這個 class 產生的所有物件共用使同一個 static 成員變數，甚至不需要有物件也能夠被使用。

因為 static 成員變數不屬於任何物件，所以必須定義在外面。與一般成員變數不同，static 成員變數並不是經由建構子初始化，而是在定義時被初始化。

```
class A
{
public:
	static int m_nNum;	//宣告static member variable
};

//必須定義在外面，不寫不行
//int A::m_nNum 也行
int A::m_nNum = 0;	

int main()
{
	cout<<A::m_nNum<<endl;	//如果m_nNum是private的，那就不能用這種方式取值了
}

```

如果 static 成員變數是 private 的，那就寫一個 Get 的 member function:

```
class A
{
private:
	static int m_nNum;
public:
	int GetNum(){return m_nNum;}
};
```

但要產生物件才能使用 GetNum() 來存取一個不用產生物件的 m_nNum 這樣寫很奇怪，因此 GetNum() 也改成 static:

```
class A
{
private:
	static int m_nNum;
public:
	static int GetNum(){return m_nNum;}
};
```