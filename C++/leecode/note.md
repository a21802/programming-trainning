# leecode技巧
## 字串轉小(大)寫
> 小寫的ASCII code比大寫多*32*
```
 if(str[i]>='A' && str[i]<='Z'){
    str[i] = (char)(str[i]+32);
}
```
---
