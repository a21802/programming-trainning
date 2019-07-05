def factors(x):
    if x <= 0:
        return []
    if x == 1:
        return [1]
    
    fac_li = []
    for i in range(1, int(x**(1/2)) + 1):
        if (x%i == 0):
            fac_li.append(i)
            if (x/i != i):
                fac_li.append(int(x/i))
    return sorted(fac_li)

if __name__ == '__main__':
    for x in range(1, 15):
        print(x, ' => ', factors(x))
    