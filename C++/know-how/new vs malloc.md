# new vs malloc

> refence: https://www.cnblogs.com/jiayouwyhit/p/3242124.html

- new 是個「運算子」(operator). malloc() 是個函式.
- new 知道類型, 所配置的大小是以類型為單位, 你只需寫需要多少個元素:
```
const size_t ARRAY_SIZE = 30; 
int *pi = new int[ARRAY_SIZE];
```
- malloc() 只會配置 bytes, 所以你還得乘上類型的大小:
```
int *pi = (int*)malloc(ARRAY_SIZE * sizeof *pi);
```
-  malloc() 在 C 裡使用不需 typecast. C++ 是個 strong-typed language, 在 C++ 裡使用 malloc() 需要 typecast. 
- 因為 new 知道類型, 所以在配置後, new 會呼叫 constructor 來初始化所配置的記憶體. malloc() 只管配置. 
- new 可以 overload. 每一個 class 可以有自己特殊用途的 new. Global 的 new 也可以 overload. 


new | malloc
-|-
calls constructor | doesnot calls constructors
It is an operator | It is a function
Returns exact data type | Returns void *
on failure, Throws | on failure, returns NULL
memory allocated from free store | memory allocated from heap
can be overridden | cannot be overridden
size is calculated by compiler | size is calculated manually
