l1, w1, h1 = int(input()), int(input()), int(input())
l2, w2, h2 = int(input()), int(input()), int(input())
lc, wc, hc = int(input()), int(input()), int(input())
if l1 < w1:
    l1, w1 = w1, l1
if l2 < w2:
    l2, w2 = w2, l2
if lc < wc:
    lc, wc = wc, lc
if h1 > hc or h2 > hc or l1 > lc or l2 > lc or w1 > wc or w2 > wc:
    print('NO')
elif l1 + l2 <= lc or w1 + w2 <= wc or h1 + h2 <= hc:
    print('YES')
elif l1 + w2 <= lc and l2 <= wc:
    print('YES')
elif w1 + w2 <= lc and l1 <= wc and l2 <= wc:
    print('YES')
elif w1 + l2 <= lc and l1 <= wc:
    print('YES')
else:
    print('NO')