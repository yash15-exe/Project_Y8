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

    static KeywordType getKeywordType(const std::string& word);
    static DataType Tokenizer::getDataType(const std::string& word) ;
static DelimiterType getDelimiterType(char c) ;
OperatorType getOperatorType(char c) const;

    char peekNextChar() const;

public:
    explicit Tokenizer(std::string source);
    Token nextToken();
    std::vector<Token> tokenizeAll();
};

#endif //TOKENIZER_H
