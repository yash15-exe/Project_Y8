//
// Created by yashr on 17-01-2025.
//

#include "Tokenizer.h"
#include <optional>
#include <unordered_map>
Tokenizer::Tokenizer(std::string source): currentLine(0), currentColumn(0), currentPosition(0), source( move(source)){}


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
    while (!isAtEnd() && isspace(charPeek())) {
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

    return DataType::OBJECT;
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
        {'!', DelimiterType::NOT_EQUAL},
        {'+', DelimiterType::PLUS},
        {'-', DelimiterType::MINUS},
        {'*', DelimiterType::MULTIPLY},
        {'/', DelimiterType::DIVIDE},
        {'%', DelimiterType::MODULUS}
    };


    if (c == '=') {

        return DelimiterType::STRICT_EQUAL;
    } else if (c == '!') {
        return DelimiterType::NOT_EQUAL;
    }

    auto it = delimiterMap.find(c);
    if (it != delimiterMap.end()) {
        return it->second;
    }

    return DelimiterType::UNKNOWN;
}

OperatorType Tokenizer::getOperatorType(char c) const {

    switch (c) {
        case '+':
            if (peekNextChar() == '+') return OperatorType::INCREMENT;
        return OperatorType::ADD;
        case '-':
            if (peekNextChar() == '-') return OperatorType::DECREMENT;
        return OperatorType::SUBTRACT;
        case '*': return OperatorType::MULTIPLY;
        case '/': return OperatorType::DIVIDE;
        case '=':
            if (peekNextChar() == '=') return OperatorType::EQUAL;
        return OperatorType::ASSIGN;
        case '<':
            if (peekNextChar() == '=') return OperatorType::LESS_THAN_EQUAL;
        return OperatorType::LESS_THAN;
        case '>':
            if (peekNextChar() == '=') return OperatorType::GREATER_THAN_EQUAL;
        return OperatorType::GREATER_THAN;
        case '&':
            if (peekNextChar() == '&') return OperatorType::LOGICAL_AND;
        return OperatorType::BITWISE_AND;
        case '|':
            if (peekNextChar() == '|') return OperatorType::LOGICAL_OR;
        return OperatorType::BITWISE_OR;
        case '^': return OperatorType::BITWISE_XOR;
        case '~': return OperatorType::BITWISE_NOT;
        case '!':
            if (peekNextChar() == '=') return OperatorType::NOT_EQUAL;
        if (peekNextChar() == '=') return OperatorType::STRICT_NOT_EQUAL;
        return OperatorType::UNKNOWN;
        default:
            return OperatorType::UNKNOWN;
    }
}


char Tokenizer::peekNextChar() const {
    return currentPosition + 1 < source.length() ? source[currentPosition + 1] : '\0';
}

Token Tokenizer::nextToken() {
    skipWhitespace();

    if (isAtEnd()) {
        return {TokenType::UNKNOWN, "","Unknown", currentLine, currentColumn};
    }

    char current = charPeek();
    if (current == '"' || current == '\'') {
        char stringDelimiter = current;
        std::string value;
        advance();

        while (!isAtEnd() && charPeek() != stringDelimiter) {
            if (charPeek() == '\\' && (peekNextChar() == stringDelimiter)) {

                value += advance();
                value += advance();
            } else {
                value += advance();
            }
        }

        if (isAtEnd()) {
            return {TokenType::ERROR, "Unterminated string","Error", currentLine, currentColumn};
        }

        advance();
        return {TokenType::STRING, value,"String", currentLine, currentColumn};
    }
    if (getDelimiterType(current) != DelimiterType::UNKNOWN) {
        advance();
        DelimiterType delimiterType = getDelimiterType(current);
        return {TokenType::DELIMITER, std::string(1, current),delimiterType, currentLine, currentColumn};
    }

    if (getOperatorType(current) != OperatorType::UNKNOWN) {
        advance();
        return {TokenType::OPERATOR, std::string(1, current),DelimiterType::UNKNOWN, currentLine, currentColumn};
    }

    if (std::isalpha(current) || current == '_') {
        std::string identifier;
        while (std::isalnum(charPeek()) || charPeek() == '_') {
            identifier += advance();
        }
        KeywordType keyword = getKeywordType(identifier);
        if (keyword != KeywordType::UNKNOWN) {
            return {TokenType::KEYWORD, identifier,keyword, currentLine, currentColumn};
        }
        return {TokenType::IDENTIFIER, identifier,KeywordType::UNKNOWN, currentLine, currentColumn};
    }

    if (std::isdigit(current)) {
        std::string number;
        while (std::isdigit(charPeek())) {
            number += advance();
        }
        return {TokenType::NUMBER, number,IdentifierType::NUMBER, currentLine, currentColumn};
    }

    advance();
    return {TokenType::UNKNOWN, std::string(1, current),KeywordType::UNKNOWN, currentLine, currentColumn};
}

std::vector<Token> Tokenizer::tokenizeAll() {
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        tokens.push_back(nextToken());
    }
    return tokens;
}

