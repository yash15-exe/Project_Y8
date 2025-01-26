#include <iostream>
#include <vector>
#include "Tokenizer.h"
#include "tokenizer.cpp"
std::string tokenTypeToString(TokenType type);
int main() {
    std::string sourceCode = "int myFunction() {return 0;}";
    Tokenizer tokenizer(sourceCode);

    std::vector<Token> tokens = tokenizer.tokenizeAll();

    for (const Token& token : tokens) {
        std::cout << "Type: " << tokenTypeToString(token.getTokenType())
                  << ", Value: " <<token.getValue()
                  << ", Line: " << token.getLine()
                  << ", Column: " << token.getColumn() << "\n";
    }

    return 0;
}
std::string tokenTypeToString(TokenType type) {
    switch(type) {
        case TokenType::KEYWORD: return "KEYWORD";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::STRING: return "STRING";
        case TokenType::OPERATOR: return "OPERATOR";
        case TokenType::DELIMITER: return "DELIMITER";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::UNKNOWN: return "UNKNOWN";
        
    }
}
