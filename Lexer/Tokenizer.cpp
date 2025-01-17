//
// Created by yashr on 17-01-2025.
//

#include "Tokenizer.h"
#include <optional>
Tokenizer::Tokenizer(std::string source): source( move(source)), currentColumn(1), currentLine(1), currentPosition(0){}


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

KeywordType Tokenizer::getKeywordType(const std::string& word) const {
    if (word == "if") return KeywordType::IF;
    if (word == "else") return KeywordType::ELSE;
    if (word == "while") return KeywordType::WHILE;
    if (word == "return") return KeywordType::RETURN;
    if (word == "int") return KeywordType::INT;
    if (word == "float") return KeywordType::FLOAT;
    return KeywordType::UNKNOWN;
}


DelimiterType Tokenizer::getDelimiterType(const char c) const {
    switch (c) {
        case ';': return DelimiterType::SEMICOLON;
        case ',': return DelimiterType::COMMA;
        case '(': return DelimiterType::PAREN_OPEN;
        case ')': return DelimiterType::PAREN_CLOSE;
        case '{': return DelimiterType::BRACE_OPEN;
        case '}': return DelimiterType::BRACE_CLOSE;
        default: return DelimiterType::UNKNOWN;
    }
}

OperatorType Tokenizer::getOperatorType(char c) const {
    switch (c) {
        case '+': return OperatorType::ADD;
        case '-': return OperatorType::SUBTRACT;
        case '*': return OperatorType::MULTIPLY;
        case '/': return OperatorType::DIVIDE;
        case '=': return OperatorType::ASSIGN;
        case '<': return OperatorType::LESS_THAN;
        case '>': return OperatorType::GREATER_THAN;
        default: return OperatorType::UNKNOWN;
    }
}

Token Tokenizer::nextToken() {
    skipWhitespace();

    if (isAtEnd()) {
        return Token(TokenType::UNKNOWN, "", currentLine, currentColumn);
    }

    char current = charPeek();


    if ( getDelimiterType(current) != DelimiterType::UNKNOWN) {
        advance();
        return Token(TokenType::DELIMITER, std::string(1, current), currentLine, currentColumn);
    }


    if ( getOperatorType(current) != OperatorType::UNKNOWN) {
        advance();
        return Token(TokenType::OPERATOR, std::string(1, current), currentLine, currentColumn);
    }

    if (std::isalpha(current) || current == '_') {
        std::string identifier;
        while (std::isalnum(charPeek()) || charPeek() == '_') {
            identifier += advance();
        }
        if ( getKeywordType(identifier) != KeywordType::UNKNOWN) {
            return Token(TokenType::KEYWORD, identifier, currentLine, currentColumn);
        }
        return Token(TokenType::IDENTIFIER, identifier, currentLine, currentColumn);
    }

    // Check for numbers
    if (std::isdigit(current)) {
        std::string number;
        while (std::isdigit(charPeek())) {
            number += advance();
        }
        return Token(TokenType::NUMBER, number, currentLine, currentColumn);
    }

    // Handle unknown tokens
    advance();
    return Token(TokenType::UNKNOWN, std::string(1, current), currentLine, currentColumn);
}

std::vector<Token> Tokenizer::tokenizeAll() {
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        tokens.push_back(nextToken());
    }
    return tokens;
}

