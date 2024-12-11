#include "../include/utils.hh"
#include <cstring>

void tokenize(const std::string &s, const std::string &delimiters,
        std::vector<std::string> &tokens) {

    if(delimiters.size() == 0) { 
        return;
    }
    size_t pos {};
    size_t prev{};
    for (const auto& delim : delimiters) {
        for (const auto& c : s) { 
            if (c == delim) {
                std::string token(s, prev, pos);
                prev = pos + 1;
                tokens.push_back(token);
                token.clear();
            }
            pos++;
        }
    }

    dbg::print(tokens);
}

