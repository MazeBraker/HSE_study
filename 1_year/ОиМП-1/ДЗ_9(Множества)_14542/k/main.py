days_in_year, parties = [int(i) for i in input().split()]
zabastovki = set()

for i in range(parties):
    start_day_a, every_b_days = [int(j) for j in input().split()]
    while start_day_a <= days_in_year:
        if start_day_a % 7 != 0:
            if (start_day_a + 1) % 7 != 0:
                zabastovki.add(start_day_a)
        start_day_a += every_b_days

print(len(zabastovki))