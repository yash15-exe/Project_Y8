//
// Created by yashr on 17-01-2025.
//

#include "Tokenizer.h"
#include <optional>
#include <unordered_map>
Tokenizer::Tokenizer(std::string source): currentLine(1), currentColumn(1), currentPosition(0), source( move(source)){}


char Tokenizer::advance() {
    char currentChar = charPeek();

    if (currentChar == '\n') {
        currentLine++;
        currentColumn = 0;
    }
    else {
        currentColumn ++;

    }
    currentPosition++;
    return currentChar;
}

bool Tokenizer::isAtEnd() const {
    if (currentPosition == source.length()) {
        return true;
    }
    return false;
}
char Tokenizer::charPeek() const {
    return isAtEnd() ? '\0' : source[currentPosition];
}

void Tokenizer::skipWhitespace() {
    if(!isAtEnd()&&isspace(charPeek())) {
        advance();
    }
}

KeywordType Tokenizer::getKeywordType(const std::string& word) {
    static const std::unordered_map<std::string, KeywordType> keywordMap = {
        {"if", KeywordType::IF},
        {"else", KeywordType::ELSE},
        {"while", KeywordType::WHILE},
        {"return", KeywordType::RETURN},
        {"function", KeywordType::FUNCTION},
        {"let", KeywordType::LET},
        {"const", KeywordType::CONST},
        {"var", KeywordType::VAR},
        {"for", KeywordType::FOR},
        {"switch", KeywordType::SWITCH},
        {"case", KeywordType::CASE},
        {"default", KeywordType::DEFAULT},
        {"break", KeywordType::BREAK},
        {"continue", KeywordType::CONTINUE},
        {"try", KeywordType::TRY},
        {"catch", KeywordType::CATCH},
        {"finally", KeywordType::FINALLY},
        {"throw", KeywordType::THROW},
        {"import", KeywordType::IMPORT},
        {"export", KeywordType::EXPORT},
        {"as", KeywordType::AS}
    };

    auto it = keywordMap.find(word);
    if (it != keywordMap.end()) {
        return it->second;
    }
    return KeywordType::UNKNOWN;
}

DataType Tokenizer::getDataType(const std::string& word) {
    static const std::unordered_map<std::string, DataType> dataTypeMap = {
        {"string", DataType::STRING},
        {"number", DataType::NUMBER},
        {"boolean", DataType::BOOLEAN},
        {"bigint", DataType::BIGINT},
        {"symbol", DataType::SYMBOL},
        {"null", DataType::NULL_TYPE},
        {"undefined", DataType::UNDEFINED},
        {"object", DataType::OBJECT}
    };

    auto it = dataTypeMap.find(word);
    if (it != dataTypeMap.end()) {
        return it->second;
    }
    // If the word doesn't match a recognized data type, return a default
    return DataType::OBJECT;  // Defaulting to OBJECT if not found
}
DelimiterType Tokenizer::getDelimiterType(const char c) {
    static const std::unordered_map<char, DelimiterType> delimiterMap = {
        {';', DelimiterType::SEMICOLON},
        {',', DelimiterType::COMMA},
        {'(', DelimiterType::PAREN_OPEN},
        {')', DelimiterType::PAREN_CLOSE},
        {'{', DelimiterType::BRACE_OPEN},
        {'}', DelimiterType::BRACE_CLOSE},
        {'[', DelimiterType::SQUARE_OPEN},
        {']', DelimiterType::SQUARE_CLOSE},
        {'.', DelimiterType::DOT},
        {':', DelimiterType::COLON},
        {'?', DelimiterType::QUESTION_MARK},
        {'!', DelimiterType::EXCLAMATION_MARK},
        {'~', DelimiterType::TILDE},
        {'=', DelimiterType::EQUAL},
        {'!', DelimiterType::NOT_EQUAL},      // For '!='
        {'+', DelimiterType::PLUS},
        {'-', DelimiterType::MINUS},
        {'*', DelimiterType::MULTIPLY},
        {'/', DelimiterType::DIVIDE},
        {'%', DelimiterType::MODULUS}
    };

    // Handle double character delimiters (e.g., '!=' and '===')
    if (c == '=') {
        // Look ahead for '==' or '==='
        return DelimiterType::STRICT_EQUAL; // Will return correct if '===' is found next
    } else if (c == '!') {
        return DelimiterType::NOT_EQUAL; // Will return correct if '!=' is found next
    }

    auto it = delimiterMap.find(c);
    if (it != delimiterMap.end()) {
        return it->second;
    }

    return DelimiterType::UNKNOWN;
}

OperatorType Tokenizer::getOperatorType(char c) const {
    // Single-character operators
    switch (c) {
        case '+':
            if (peekNextChar() == '+') return OperatorType::INCREMENT; // '++'
        return OperatorType::ADD;
        case '-':
            if (peekNextChar() == '-') return OperatorType::DECREMENT; // '--'
        return OperatorType::SUBTRACT;
        case '*': return OperatorType::MULTIPLY;
        case '/': return OperatorType::DIVIDE;
        case '=':
            if (peekNextChar() == '=') return OperatorType::EQUAL; // '=='
        return OperatorType::ASSIGN;
        case '<':
            if (peekNextChar() == '=') return OperatorType::LESS_THAN_EQUAL; // '<='
        return OperatorType::LESS_THAN;
        case '>':
            if (peekNextChar() == '=') return OperatorType::GREATER_THAN_EQUAL; // '>='
        return OperatorType::GREATER_THAN;
        case '&':
            if (peekNextChar() == '&') return OperatorType::LOGICAL_AND; // '&&'
        return OperatorType::BITWISE_AND;
        case '|':
            if (peekNextChar() == '|') return OperatorType::LOGICAL_OR; // '||'
        return OperatorType::BITWISE_OR;
        case '^': return OperatorType::BITWISE_XOR;
        case '~': return OperatorType::BITWISE_NOT;
        case '!':
            if (peekNextChar() == '=') return OperatorType::NOT_EQUAL; // '!='
        if (peekNextChar() == '=') return OperatorType::STRICT_NOT_EQUAL; // '!=='
        return OperatorType::UNKNOWN;
        default:
            return OperatorType::UNKNOWN;  // If none matched, return unknown
    }
}


char Tokenizer::peekNextChar() const {
    return currentPosition + 1 < source.length() ? source[currentPosition + 1] : '\0';
}

Token Tokenizer::nextToken() {
    skipWhitespace();

    if (isAtEnd()) {
        return {TokenType::UNKNOWN, "", currentLine, currentColumn};  // Use braced initializer list
    }

    char current = charPeek();

    if (getDelimiterType(current) != DelimiterType::UNKNOWN) {
        advance();
        return {TokenType::DELIMITER, std::string(1, current), currentLine, currentColumn};  // Use braced initializer list
    }

    if (getOperatorType(current) != OperatorType::UNKNOWN) {
        advance();
        return {TokenType::OPERATOR, std::string(1, current), currentLine, currentColumn};  // Use braced initializer list
    }

    if (std::isalpha(current) || current == '_') {
        std::string identifier;
        while (std::isalnum(charPeek()) || charPeek() == '_') {
            identifier += advance();
        }
        if (getKeywordType(identifier) != KeywordType::UNKNOWN) {
            return {TokenType::KEYWORD, identifier, currentLine, currentColumn};  // Use braced initializer list
        }
        return {TokenType::IDENTIFIER, identifier, currentLine, currentColumn};  // Use braced initializer list
    }

    if (std::isdigit(current)) {
        std::string number;
        while (std::isdigit(charPeek())) {
            number += advance();
        }
        return {TokenType::NUMBER, number, currentLine, currentColumn};  // Use braced initializer list
    }

    advance();
    return {TokenType::UNKNOWN, std::string(1, current), currentLine, currentColumn};  // Use braced initializer list
}

std::vector<Token> Tokenizer::tokenizeAll() {
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        tokens.push_back(nextToken());
    }
    return tokens;
}

