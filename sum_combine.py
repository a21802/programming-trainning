def sum_combine(x, n, s = 1):
#===========================
#   x = k1 + k2 + ... + kn
#   k1 < k2 < ... < kn
#   s : start
#===========================
    if (x <= 0 or n <= 0): return []   
    if (n == 1): return [x]

    result = []
    for i in range(s, x):
        if i < (x - i): #限制i範圍 不然會有重複結果
            y = sum_combine(x - i, n - 1, i + 1)
            
            for j in y:
                print(j)
                if len(y) == 1 and isinstance(j, int): #如果y只有一個元素 且此元素j是整數
                    result.append([i] + y)
                else:
                    temp = [i] + j
                    result.append(temp)
    return result                    


if __name__ == '__main__':
    print('6 => ', sum_combine(6, 2))
    print('6 => ', sum_combine(6, 3))
    print('12 => ', sum_combine(12, 3))
    print('12 => ', sum_combine(12, 4)) 
    print('15 => ', sum_combine(15, 4))