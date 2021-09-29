std::vector <std::string> split(const std::string& str, char delimiter) {
    std::vector <std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delimiter, prev);
        if (pos == std::string::npos)
            pos = str.length();
        if (!str.substr(prev, pos - prev).empty())
            tokens.push_back(str.substr(prev, pos - prev));
        prev = pos + delimiter.length();
    } while (pos < str.length());
    return tokens;
}