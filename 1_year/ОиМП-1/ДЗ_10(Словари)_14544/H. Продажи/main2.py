buyers = {}
with open('input.txt', 'r') as input_file:
    for line in input_file.readlines():
        name, product, cnt = line.split()
        cnt = int(cnt)
        if name not in buyers:
            buyers[name] = {}
            buyers[name][product] = cnt
        elif product not in buyers[name]:
            buyers[name][product] = cnt
        else:
            buyers[name][product] += cnt

for name, stats in sorted(buyers.items()):
    print(f'{name}:')
    for product_name, product_cnt in sorted(stats.items()):
        print(product_name, product_cnt)