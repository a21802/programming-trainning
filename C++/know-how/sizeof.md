# sizeof()

- sizeof() 回傳值的單位為 byte(=8bits)
- sizeof(str)=12 是因為我們是以**字串**的方式儲存，C 會自動將字串後再接個空白(\n)字元
- sizeof(*p) 所代表的是該指標所指向位置的資料型態，此題 *p 所指向的是char，所以也等於sizeof(char)
- sizeof(p) 所代表的是該指標的位址大小，與編譯器有關(32/64bit)

```
    char str[] = "Hello world";
    char *p = str;
    short a;
    int b;
    long c;
    float d;
    double e;
    
    cout << "sizeof(str): " << sizeof(str) << endl; // 12
    cout << "sizeof(*p): " << sizeof(*p) << endl;   // 1
    cout << "sizeof(p): " << sizeof(p) << endl;     // 8
    cout << "sizeof(a): " << sizeof(a) << endl;     // 2
    cout << "sizeof(b): " << sizeof(b) << endl;     // 4 
    cout << "sizeof(c): " << sizeof(c) << endl;     // 4 or 8，與編譯器有關
    cout << "sizeof(d): " << sizeof(d) << endl;     // 4
    cout << "sizeof(e): " << sizeof(e) << endl;     // 8
```