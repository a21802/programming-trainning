# recursive

> 以Fibonacci series做為範例

## 使用遞迴
```
int fib(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fib(n - 1) + fib(n - 2);
}
```
### 缺點

- 耗費stack空間
- 此種二元遞迴產生多餘的計算
- 通常效率較差

### 優點

- 某些數學結構下，較容易寫出該函式

## 使用迭代

```

int fib(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else {
        // a: F(n-2)
        // b: F(n-1)
        int a = 0, b = 1, result = 0;
	   
        for (int i = 2; i <= n; i++) {
            result = a + b;
            a = b;
            b = result;
        }
	   
        return result;
    }
}
```

### 缺點

- 有時無法直觀看出流程

### 優點

- 通常效率較佳

## tail recursive(尾端遞迴)

```
int fib(int n, int a, int b) {
    if (n == 0) return a;
    //cout << "(" << n - 1 << ", " << b << ", " << a + b << ")" << endl; 
    return fib(n - 1, b, a + b);
}
```

### 優點

- 改善了一般遞迴的stack使用，轉而放到參數內傳遞
- 改善了一般遞迴的流程，不用回到上一層呼叫的函式，而在終止條件達成時直接結束

