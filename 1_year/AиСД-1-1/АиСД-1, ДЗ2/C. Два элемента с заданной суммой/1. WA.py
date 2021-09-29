def merge1(seq1, seq2):
    lst1 = []
    while seq1 and seq2:
        if seq1[0] < seq2[0]:
            lst1.append(seq1.pop(0))
        else:
            lst1.append(seq2.pop(0))
    if seq1:
        lst1.extend(seq1)
    if seq2:
        lst1.extend(seq2)
    return lst1


N, M, K = list(map(int, input().split()))
seq1 = [int(i) for i in input().split()]
seq2 = [int(i) for i in input().split()]
seq3 = [int(i) for i in input().split()]
seq12 = merge1(seq1, seq2)
print(*merge1(seq12, seq3))
