party_votes = {}
total_votes = 0
seats = 450
with open('input.txt', 'r') as input_file:
    for line in input_file:
        party = line.rsplit(maxsplit=1)[0]   #возвращает список и нарезает строку начиная справа
        votes_cnt = int(line.rsplit(maxsplit=1)[1])
        total_votes += votes_cnt
        party_votes[party] = party_votes.get(party, 0) + votes_cnt
    input_file.close()

    coef = total_votes / 450
    all_seats = 0
    for party in party_votes:
        seats_party = int(party_votes.get(party) // coef)
        all_seats += seats_party
        #  = дробной части частного от деления числа голосов за данную партию на первое избирательное частное
        coef2 = party_votes.get(party) / coef - seats_party
        party_votes[party] = [(coef2, party_votes.get(party)), seats_party]
        party_votes[party] = [(party_votes.get(party)), seats_party]
        # seats -= seats_party
    #print(seats)

    for party in sorted(party_votes, reverse=True, key=party_votes.get): ## по возврастанию
        #print(party_votes)
        if seats < 450:
            party_votes[party] = party_votes.get(party)[1] + 1
            seats -= 1
        else:
            party_votes[party] = party_votes.get(party)[1]

    for party in party_votes:
        print(party, party_votes[party])