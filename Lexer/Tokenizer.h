//
// Created by yashr on 17-01-2025.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>
#include "Token.h"


class Tokenizer {
private:
    int currentLine;
    int currentColumn;
    size_t currentPosition;
    std::string source;

    char charPeek() const;
    char advance();
    bool isAtEnd() const;
    void skipWhitespace();

KeywordType getKeywordType(const std::string& word) const;
DelimiterType getDelimiterType(char c) const;
OperatorType getOperatorType(char c) const;

public:
    explicit Tokenizer(std::string source);
    Token nextToken();
    std::vector<Token> tokenizeAll();
};

#endif //TOKENIZER_H
