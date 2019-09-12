## ref: geeksforgeeks
https://www.geeksforgeeks.org/pointer-vs-array-in-c/

### 1. sizeof 運算子
- sizeof(array) 回傳陣列中所有元素使用的記憶體量
- sizeof(pointer) 只回傳指針變量本身使用的記憶體量

### 2. & 運算子
- &array是&array[0]的別稱, 回傳陣列中第一個元素的地址
- &pointer 回傳指標的地址

### 3. 字串文字初始化的字串陣列
- char array[]="abc"設置前4個元素為'a'、'b'、'c'和'\0'在陣列中
- char *pointer="abc"設置指向"abc"字串地址的指標(儲存在唯讀記憶體中且不能修改)

### 4. 指針變量可以賦值，而陣列變量不能
```
int a[10];
int *p; 
p=a; /*legal*/
a=p; /*illegal*/ 
```

### 5. 允許對指針變量進行算術運算
```
p++; /*Legal*/
a++; /*illegal*/ 
```

---
或是下面這篇講得非常清楚  
http://pl-learning-blog.logdown.com/posts/1060530
