n, m = map(int, raw_input().split())
d = [[0, 0, 0, 0, 0] for i in xrange(m)]
for i in xrange(n):
    s = raw_input()
    for j in xrange(m):
        k = ord(s[j]) - 65
        d[j][k] += 1
a = map(int, raw_input().split())
c = 0
for i in xrange(m):
    c += max(d[i]) * a[i]
print c
