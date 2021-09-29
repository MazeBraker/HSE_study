for q in range(10, 100):
    if q == ((q % 10) * (q // 10)) * 2:
        print(q)
