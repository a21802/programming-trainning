# const 修飾

```
char greeting[] = "Hello";
char* p = greeting;        // non-const pointer, non-const data
const char* p = greeting;  // non-const pointer, const data
char const * p = greeting; // 同上
char* const p = greeting;  // const pointer, non-const data
const char* const p = greeting; // const pointer, const data
```

如果關鍵字 const 出現在星號左邊, 表示被指物是常數; 如果出現在星號右邊, 表示指標本身是常數