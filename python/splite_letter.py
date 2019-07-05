words = 'Wheresoever you go, go~ with all your heart.'
String = words.lower()
print(String)
temp = ''

for i in String:
    print(i)
    if i.isalpha():
        temp+=i
    elif(len(temp) > 0 and i.isalpha() == False):
        if(temp[0] >= 'h'):
            print(temp.capitalize())
        temp = ''

