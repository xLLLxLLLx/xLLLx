def isprime(n):
    if n < 2:
        return False
    for x in range(2, int(n**0.5 + 1)):
        if n % x == 0:
            return False
    return True
 
def solve():
    mode = ['aaabb','aabab','aabba','ababa','abbaa',
            'abaab','babaa','baaba','baaab','bbaaa']
    for stri in mode:
        for i in range(10):
            stri1 = stri.replace('b', str(i), 1)
            for j in range(10):
                stri2 = stri1.replace('b', str(j), 1)
                for m in [1,3,7,9]:
                    stri3 = stri2 + str(m)
                    count = 0
                    for k in range(10):
                        stri4 = stri3.replace('a',str(k))
                        if stri4[0] == '0':
                            continue
                        # print(stri4)
                        if isprime(int(stri4)):
                            count += 1
                            if count == 8:
                                print(stri4)
                                print(stri)
                                
 
solve()