clients_dict = {}
with open('input.txt', 'r') as input_file:
    for line in input_file.readlines():
        operation, *param = line.split()

        if operation == "DEPOSIT":
            name_cl = param[0]  # param = [Ivanov, 100]
            money = int(param[1])
            if name_cl in clients_dict:
                clients_dict[name_cl] += (money)
                # clients_dict[name_cl] = clients_dict.get(name_cl, 0) + money
            else:  # создание счета
                clients_dict[name_cl] = 0  # ?
                clients_dict[name_cl] += money

        elif operation == "WITHDRAW":
            name_cl = param[0]  # param = [Ivanov, 100]
            money = int(param[1])
            if name_cl in clients_dict:
                clients_dict[name_cl] -= money
                # clients_dict[name_cl] = clients_dict.get(name_cl, 0) + money
            else:
                clients_dict[name_cl] = 0  # ?
                clients_dict[name_cl] -= money

        elif operation == "TRANSFER":
            name1_cl = param[0]
            name2_cl = param[1]
            sum = int(param[2])
            if name1_cl not in clients_dict:
                clients_dict[name1_cl] = 0
            if name2_cl not in clients_dict:
                clients_dict[name2_cl] = 0
            clients_dict[name1_cl] -= sum
            clients_dict[name2_cl] += sum

        elif operation == "INCOME":
            p = int(param[0])
            for i in clients_dict:
                if int(clients_dict[i]) < 0:
                    continue
                else:
                    # tuple неизменяемый обьект, тут доработал
                    bonus = int(clients_dict[i] / 100 * p)
                    clients_dict[i] += bonus

        elif operation == "BALANCE":
            # print(clients_dict)
            name_cl = param[0]
            if name_cl in clients_dict:
                print(clients_dict[name_cl])
            else:
                print("ERROR")