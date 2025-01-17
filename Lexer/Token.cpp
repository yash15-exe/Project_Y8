//
// Created by yashr on 17-01-2025.
//

#include "Token.h"
#include <iostream>


int main() {
    // Create a Token object
    Token token(TokenType::KEYWORD, "if", 1, 5);

    // Print token details
    std::cout << "Token Type: " << static_cast<int>(token.getTokenType()) << "\n";
    std::cout << "Value: " << token.getValue() << "\n";
    std::cout << "Line: " << token.getLine() << "\n";
    std::cout << "Column: " << token.getColumn() << "\n";

    return 0;
}
