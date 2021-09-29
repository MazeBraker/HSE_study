def merge1(seq1, seq2):
    Res = []
    i = 0
    j = 0
    while i < len(seq1) and j < len(seq2):
        if seq1[i] <= seq2[j]:
            Res.append(seq1[i])
            i += 1
        else:
            Res.append(seq2[j])
            j += 1
    Res += seq1[i:] + seq2[j:]
    return Res


N, M, K = list(map(int, input().split()))
seq1 = [int(i) for i in input().split()]
seq2 = [int(i) for i in input().split()]
seq3 = [int(i) for i in input().split()]
seq12 = merge1(seq1, seq2)
print(*merge1(seq12, seq3))
