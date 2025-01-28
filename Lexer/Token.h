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
    // Control flow
    IF,
    ELSE,
    SWITCH,
    CASE,
    DEFAULT,

    // Loops
    WHILE,
    DO,
    FOR,
    BREAK,
    CONTINUE,

    // Functions
    FUNCTION,
    RETURN,
    YIELD,

    // Variable declarations
    VAR,
    LET,
    CONST,

    // Objects and classes
    CLASS,
    THIS,
    SUPER,
    NEW,
    EXTENDS,
    CONSTRUCTOR,

    // Modules
    IMPORT,
    EXPORT,
    FROM,
    AS,

    // Boolean logic
    TRUE,
    FALSE,

    // Try-catch
    TRY,
    CATCH,
    FINALLY,
    THROW,

    // Miscellaneous
    DELETE,
    TYPEOF,
    INSTANCEOF,
    VOID,
    AWAIT,
    WITH,
    DEBUGGER,

    // Strict mode and reserved
    USE_STRICT,
    ENUM,

    UNKNOWN
};

enum class DataType {
    STRING,         // Text data
    NUMBER,         // Numeric values (integer or float)
    BOOLEAN,        // true or false
    BIGINT,         // Large integers
    SYMBOL,         // Unique identifiers
    NULL_TYPE,      // Intentional absence of value (null)
    UNDEFINED,      // Uninitialized or missing value
    OBJECT          // Non-primitive objects, arrays, functions, etc.
};

enum class DelimiterType {
    SEMICOLON,       // ;
    COMMA,           // ,
    PAREN_OPEN,      // (
    PAREN_CLOSE,     // )
    BRACE_OPEN,      // {
    BRACE_CLOSE,     // }
    SQUARE_OPEN,     // [
    SQUARE_CLOSE,    // ]
    DOT,             // .
    COLON,           // :
    QUESTION_MARK,   // ?
    EXCLAMATION_MARK,// !
    TILDE,           // ~
    EQUAL,           // =
    NOT_EQUAL,       // !=
    STRICT_EQUAL,    // ===
    STRICT_NOT_EQUAL,// !==
    PLUS,            // +
    MINUS,           // -
    MULTIPLY,        // *
    DIVIDE,          // /
    MODULUS,         // %
    UNKNOWN          // Any other unexpected delimiter
};

enum class OperatorType {
    ADD,             // +
    SUBTRACT,        // -
    MULTIPLY,        // *
    DIVIDE,          // /
    ASSIGN,          // =
    LESS_THAN,       // <
    GREATER_THAN,    // >
    LESS_THAN_EQUAL, // <=
    GREATER_THAN_EQUAL, // >=
    EQUAL,           // ==
    NOT_EQUAL,       // !=
    STRICT_EQUAL,    // ===
    STRICT_NOT_EQUAL,// !==
    LOGICAL_AND,     // &&
    LOGICAL_OR,      // ||
    BITWISE_AND,     // &
    BITWISE_OR,      // |
    BITWISE_XOR,     // ^
    BITWISE_NOT,     // ~
    LEFT_SHIFT,      // <<
    RIGHT_SHIFT,     // >>
    UNSIGNED_RIGHT_SHIFT, // >>>
    INCREMENT,       // ++
    DECREMENT,       // --
    TERNARY_CONDITION, // ?:
    NULLISH_COALESCING, // ??
    UNKNOWN          // Any other unexpected operator
};



#endif //TOKEN_H
