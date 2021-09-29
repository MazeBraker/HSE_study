n = int(input())
accents = {}
for i in range(n):
    word = input()
    base_form = word.lower()
    if base_form not in accents:
        # добавляем все варианты слова с ударениями {'cannot': {'cAnnot', 'cannOt'}
        accents[base_form] = set()
    accents[base_form].add(word)
# print(accents)
errors = 0
Petias_sent = input().split()
for word in Petias_sent:  # check spelling
    base_form = word.lower()
    if (base_form not in accents or word in accents[base_form]):
        # если одно ударение и его нету в accents
        if len([ch for ch in word if l.isupper()]) == 1:  #  выражение для подсета кол-во заглавных букв
            continue
    errors += 1
print(errors)

# 2 решение (взято)
# def check_errors(
#         dictionary, sentence):
#     errors = 0
#     for word in sentence:
#         lower_form = word.lower()
#         if lower_form in dictionary and \
#             word not in dictionary[lower_form] \
#                 or len([letter for letter in word if letter.isupper()]) != 1:
#             errors += 1
#     return str(errors)
#
#
# with open('input.txt') as file:
#     lines = file.readlines()
# dictionary = {}
# dictionany_length = int(lines[0])
# if dictionany_length:
#     for word in lines[1:-1]:
#         word = word.strip()
#         lower_form = word.lower()
#         if lower_form not in dictionary:
#             dictionary[lower_form] = set()
#         dictionary[lower_form].add(word)
# sentence = lines[-1].split()
#
#
# with open('output.txt', 'w') as file:
#     file.write(check_errors(
#         dictionary, sentence))