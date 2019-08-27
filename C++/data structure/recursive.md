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
- 可以容易改寫成迭代型式

## Q-Matrix

let 
${
Q = \left[ \begin{array}{cc}
1 & 1\\
1 & 0\\
\end{array}
\right] 
= \left[ \begin{array}{cc}
F_2 & F_1\\
F_1 & F_0\\
\end{array}
\right] 
}$  

hence
${
Q^n = \left[ \begin{array}{cc}
1 & 1\\
1 & 0\\
\end{array}
\right]^n 
= \left[ \begin{array}{cc}
F_{n+1} & F_n\\
F_n & F_{n-1}\\
\end{array}
\right] 
}$  

$
\begin{aligned}
\text{since}
\left[ \begin{array}{cc}
F_{2n+1} & F_{2n}\\
F_{2n} & F_{2n-1}\\
\end{array}\right]
&= \left[ \begin{array}{cc}
1 & 1\\
1 & 0\\
\end{array}\right]^{2n}
= \left[ \begin{array}{cc}
1 & 1\\
1 & 0\\
\end{array}\right]^{n+1} 
\cdot
\left[ \begin{array}{cc}
1 & 1\\
1 & 0\\
\end{array}\right]^{n-1}\\
&= \left[ \begin{array}{cc}
F_{n+2} & F_{n+1}\\
F_{n+1} & F_{n}\\
\end{array}\right]
\cdot
\left[ \begin{array}{cc}
F_{n} & F_{n-1}\\
F_{n-1} & F_{n-2}\\
\end{array}\right]
\end{aligned}
$

$
\text{we get}
\left\{ \begin{array}{cc}
\begin{aligned}
F_{2n} &= F_n (2F_{n+1} − F_n) \\
F_{2n+1} &= (F_{n+1})^2 + (F_{n})^2 \\
\end{aligned}
\end{array}
\right.
$

## use tail recursive & Q-Matrix & Fast Doubling
```
int fib(int n, int a, int b, int bit) {
    if (bit == 0) return a;
    // F(2k) = F(k) * [2 * F(k + 1) - F(k)]
    int c = a * ((b << 1) - (a));
    // F(2k + 1) = F(k)^2 + F(k + 1)^2
    int d = (a * a) + (b * b);
    
    if ((n & bit) != 0) {
        int e = c + d; // F(2k + 2)
        a = d; // k = 2k + 1
        b = e;
    } else {
        a = c; // k = 2k
        b = d;
    }
    
    bit = bit >> 1;
    //cout << n << ", " << a << ", " << b << ", " << bit << endl;
    
    return fib(n, a, b, bit);
}
```