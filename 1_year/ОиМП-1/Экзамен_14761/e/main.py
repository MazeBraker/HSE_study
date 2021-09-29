def main():
    import sys
    from string import punctuation
    from collections import OrderedDict
    punctuation = punctuation.replace("_", "")
    empty_line = len(punctuation) * " "
    translation_dic = str.maketrans(punctuation, empty_line)
    n, case_sensitive, begins_with_number = input().split()
    n = int(n)
    case_sensitive = True if case_sensitive == "yes" else False
    begins_with_number = True if begins_with_number == "yes" else False
    key_words = []
    stat_dict = OrderedDict()
    for _ in range(n):
        if not case_sensitive:
            key_words.append(input().lower())
        else:
            key_words.append(input())
    for line in sys.stdin:
        line = line.strip().translate(translation_dic).split()
        for word in line:
            if not case_sensitive:
                word = word.lower()
            if word not in key_words:
                if not begins_with_number:
                    if word[0].isnumeric():
                        continue
                if any([not x.isnumeric() for x in word]):
                    if word in stat_dict:
                        stat_dict[word] += 1
                    else:
                        stat_dict[word] = 1
    max_number = max(stat_dict.values())
    for key, value in stat_dict.items():
        if value == max_number:
            print(key)
            break


if __name__ == "__main__":
    main()