//
// Created by yashr on 17-01-2025.
//
#pragma once
#include <string>
#include <utility>
#ifndef TOKEN_H
#define TOKEN_H


enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    STRING,
    OPERATOR,
    DELIMITER,
    COMMENT,
    UNKNOWN
};
class Token {
private:
    TokenType tokenType;
    std::string value{};
    int line;
    int column;
public:
    Token(const TokenType tokenType, std::string value, const int line, const int column) : tokenType(tokenType), value(std::move(value)), line(line), column(column) {}
    TokenType getTokenType() const { return tokenType; }
    int getLine() const { return line; }
    int getColumn() const { return column; }
    const std::string& getValue() const { return value; }
};

enum class KeywordType {
    IF,
    ELSE,
    WHILE,
    RETURN,
    INT,
    FLOAT,
    UNKNOWN
};
enum class DelimiterType {
    SEMICOLON,
    COMMA,
    PAREN_OPEN,
    PAREN_CLOSE,
    BRACE_OPEN,
    BRACE_CLOSE,
    UNKNOWN
};

enum class OperatorType {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    ASSIGN,
    LESS_THAN,
    GREATER_THAN,
    UNKNOWN
};


#endif //TOKEN_H
