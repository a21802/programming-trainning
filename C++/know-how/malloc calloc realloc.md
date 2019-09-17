動態記憶體配置可以解決在使用陣列宣告時，必須事先知道陣列大小的問題，如下所示:

```
int *arr = malloc(1000 * sizeof(int));
```
這段程式碼動態配置了 1000 個 int 大小的空間，並傳回空間的第一個位址，配置後的空間資料是未知的，可以使用 calloc 來宣告空間配置。例如：

```
int *arr = calloc(1000, sizeof(int));
```

這個程式將宣告 1000 個 int 大小的空間，並將所有的空間值初始為 0  

如果要改變先前配置的記憶體大小，則可以使用 realloc，您必須先使用 malloc、calloc 或 realloc 配置記憶體，而後使用所得到的位址來使用 realloc 重新配置記憶體大小

```
int *arr1 = malloc(size * sizeof(int));
int *arr2 = realloc(arr1, sizeof(int) * size * 2);
```

上例中，arr1 與 arr2 的位址相同並不保證，realloc 會需要複製資料來改變記憶體的大小，若原位址有足夠的空間，則使用原位址調整記憶體的大小，若空間不足，則重新尋找足夠的空間來進行配置，在這個情況下，realloc 前舊位址的空間會被釋放掉。因此，必須使用 realloc 傳回的新位址，而不該使用舊位址，若 realloc 失敗，則傳回空指標（null）。最好是進行檢查：

```
if(!arr2) {
    arr1 = arr2;
}
```

在不使用該資料或程式結束前，應使用 free 釋放記憶體空間

```
free arr1;
```