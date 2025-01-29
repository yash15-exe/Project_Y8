//
// Created by yashr on 17-01-2025.
//
#pragma once
#include <string>
#include <variant>

#ifndef TOKEN_H
#define TOKEN_H

// Define all necessary enums **before** using them in `LexemeType`
enum class KeywordType {
    IF, ELSE, SWITCH, CASE, DEFAULT,
    WHILE, DO, FOR, BREAK, CONTINUE,
    FUNCTION, RETURN, YIELD,
    VAR, LET, CONST,
    CLASS, THIS, SUPER, NEW, EXTENDS, CONSTRUCTOR,
    IMPORT, EXPORT, FROM, AS,
    TRUE, FALSE,
    TRY, CATCH, FINALLY, THROW,
    DELETE, TYPEOF, INSTANCEOF, VOID, AWAIT, WITH, DEBUGGER,
    USE_STRICT, ENUM, UNKNOWN
};

enum class DataType {
    STRING, NUMBER, BOOLEAN, BIGINT, SYMBOL,
    NULL_TYPE, UNDEFINED, OBJECT
};

enum class DelimiterType {
    SEMICOLON, COMMA, PAREN_OPEN, PAREN_CLOSE, BRACE_OPEN, BRACE_CLOSE,
    SQUARE_OPEN, SQUARE_CLOSE, DOT, COLON, QUESTION_MARK, EXCLAMATION_MARK,
    TILDE, EQUAL, NOT_EQUAL, STRICT_EQUAL, STRICT_NOT_EQUAL,
    PLUS, MINUS, MULTIPLY, DIVIDE, MODULUS, UNKNOWN
};
enum class IdentifierType {
    NUMBER, STRING
};
enum class OperatorType {
    ADD, SUBTRACT, MULTIPLY, DIVIDE, ASSIGN,
    LESS_THAN, GREATER_THAN, LESS_THAN_EQUAL, GREATER_THAN_EQUAL,
    EQUAL, NOT_EQUAL, STRICT_EQUAL, STRICT_NOT_EQUAL,
    LOGICAL_AND, LOGICAL_OR, BITWISE_AND, BITWISE_OR, BITWISE_XOR, BITWISE_NOT,
    LEFT_SHIFT, RIGHT_SHIFT, UNSIGNED_RIGHT_SHIFT,
    INCREMENT, DECREMENT, TERNARY_CONDITION, NULLISH_COALESCING, UNKNOWN
};

// Define the possible types of `lexeme`
using LexemeType = std::variant<std::string, char, int, KeywordType, DataType, DelimiterType, OperatorType, IdentifierType>;

enum class TokenType {
    KEYWORD, IDENTIFIER, NUMBER, STRING, OPERATOR, DELIMITER, COMMENT, UNKNOWN, ERROR
};

class Token {
private:
    TokenType tokenType;
    std::string value;
    LexemeType lexeme;  // ✅ Correctly using `LexemeType`
    int line;
    int column;

public:
    // ✅ No `auto`, replaced with `LexemeType`
    Token(TokenType tokenType, std::string value, LexemeType lexeme, int line, int column)
        : tokenType(tokenType), value(std::move(value)), lexeme(std::move(lexeme)), line(line), column(column) {}

    [[nodiscard]] TokenType getTokenType() const { return tokenType; }
    [[nodiscard]] int getLine() const { return line; }
    [[nodiscard]] int getColumn() const { return column; }
    [[nodiscard]] const std::string& getValue() const { return value; }
    [[nodiscard]] const LexemeType& getLexeme() const { return lexeme; }
};

#endif //TOKEN_H
