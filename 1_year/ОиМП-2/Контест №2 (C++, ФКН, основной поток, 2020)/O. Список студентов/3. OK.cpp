std::string join(const std::vector<std::string> &tokens, char delimiter) {
    std::string str1;
    for (const auto& i : tokens)
        str1 += i + delimiter;
    str1.erase(str1.end() - 1, str1.end());
    return str1;
}