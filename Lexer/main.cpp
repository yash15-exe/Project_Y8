#include <iostream>
#include <vector>
#include <variant>
#include "tokenizer.cpp"

std::string tokenTypeToString(TokenType type);
std::string lexemeToString(const LexemeType& lexeme);

int main() {
    const std::string sourceCode = R"(
function greet(name) {
    if (!name) {
        return "Hello, World!";
    }
    let message = `Hello, ${name}!`;
    console.log(message);
    return message;
}

greet("Alice");
)";

    Tokenizer tokenizer(sourceCode);

    std::vector<Token> tokens = tokenizer.tokenizeAll();

    for (const Token& token : tokens) {
        std::cout << "\nToken {\n"<<"Type: " << tokenTypeToString(token.getTokenType())
                  << " Value: " << token.getValue()<<"\n"
                  << " Lexeme: " << lexemeToString(token.getLexeme())<<"\n"
                  << " Line: " << token.getLine()<<"\n"
                  << " Column: " << token.getColumn() <<"\n}"<< "\n";
    }

    return 0;
}


std::string tokenTypeToString(const TokenType type) {
    switch(type) {
        case TokenType::KEYWORD: return "KEYWORD";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::STRING: return "STRING";
        case TokenType::OPERATOR: return "OPERATOR";
        case TokenType::DELIMITER: return "DELIMITER";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::UNKNOWN: return "UNKNOWN";
        case TokenType::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}


std::string lexemeToString(const LexemeType& lexeme) {
    return std::visit([](auto&& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string>) {
            return arg;
        }
        else if constexpr (std::is_same_v<T, char>) {
            return std::string(1, arg);
        }
        else if constexpr (std::is_same_v<T, int>) {
            return std::to_string(arg);
        }
        else if constexpr (std::is_same_v<T, KeywordType>) {

            switch (arg) {
                case KeywordType::IF: return "IF";
                case KeywordType::ELSE: return "ELSE";
                case KeywordType::WHILE: return "WHILE";
                case KeywordType::RETURN: return "RETURN";
                case KeywordType::FUNCTION: return "FUNCTION";
                case KeywordType::LET: return "LET";
                case KeywordType::CONST: return "CONST";
                case KeywordType::VAR: return "VAR";
                case KeywordType::FOR: return "FOR";
                case KeywordType::SWITCH: return "SWITCH";
                case KeywordType::CASE: return "CASE";
                case KeywordType::DEFAULT: return "DEFAULT";
                case KeywordType::BREAK: return "BREAK";
                case KeywordType::CONTINUE: return "CONTINUE";
                case KeywordType::TRY: return "TRY";
                case KeywordType::CATCH: return "CATCH";
                case KeywordType::FINALLY: return "FINALLY";
                case KeywordType::THROW: return "THROW";
                case KeywordType::IMPORT: return "IMPORT";
                case KeywordType::EXPORT: return "EXPORT";
                case KeywordType::AS: return "AS";
                case KeywordType::UNKNOWN: return "UNKNOWN";
                default: return "UNKNOWN KEYWORD";
            }
        }
        else if constexpr (std::is_same_v<T, DataType>) {

            switch (arg) {
                case DataType::STRING: return "STRING";
                case DataType::NUMBER: return "NUMBER";
                case DataType::BOOLEAN: return "BOOLEAN";
                case DataType::BIGINT: return "BIGINT";
                case DataType::SYMBOL: return "SYMBOL";
                case DataType::NULL_TYPE: return "NULL";
                case DataType::UNDEFINED: return "UNDEFINED";
                case DataType::OBJECT: return "OBJECT";
                default: return "UNKNOWN DATA TYPE";
            }
        }
        else if constexpr (std::is_same_v<T, DelimiterType>) {

            switch (arg) {
                case DelimiterType::SEMICOLON: return "SEMICOLON";
                case DelimiterType::COMMA: return "COMMA";
                case DelimiterType::PAREN_OPEN: return "PAREN_OPEN";
                case DelimiterType::PAREN_CLOSE: return "PAREN_CLOSE";
                case DelimiterType::BRACE_OPEN: return "BRACE_OPEN";
                case DelimiterType::BRACE_CLOSE: return "BRACE_CLOSE";
                case DelimiterType::SQUARE_OPEN: return "SQUARE_OPEN";
                case DelimiterType::SQUARE_CLOSE: return "SQUARE_CLOSE";
                case DelimiterType::DOT: return "DOT";
                case DelimiterType::COLON: return "COLON";
                case DelimiterType::QUESTION_MARK: return "QUESTION_MARK";
                case DelimiterType::EXCLAMATION_MARK: return "EXCLAMATION_MARK";
                case DelimiterType::TILDE: return "TILDE";
                case DelimiterType::EQUAL: return "EQUAL";
                case DelimiterType::NOT_EQUAL: return "NOT_EQUAL";
                case DelimiterType::STRICT_EQUAL: return "STRICT_EQUAL";
                case DelimiterType::PLUS: return "PLUS";
                case DelimiterType::MINUS: return "MINUS";
                case DelimiterType::MULTIPLY: return "MULTIPLY";
                case DelimiterType::DIVIDE: return "DIVIDE";
                case DelimiterType::MODULUS: return "MODULUS";
                default: return "UNKNOWN DELIMITER";
            }
        }
        else if constexpr (std::is_same_v<T, OperatorType>) {

            switch (arg) {
                case OperatorType::ADD: return "ADD";
                case OperatorType::SUBTRACT: return "SUBTRACT";
                case OperatorType::MULTIPLY: return "MULTIPLY";
                case OperatorType::DIVIDE: return "DIVIDE";
                case OperatorType::EQUAL: return "EQUAL";
                case OperatorType::ASSIGN: return "ASSIGN";
                case OperatorType::LESS_THAN: return "LESS_THAN";
                case OperatorType::LESS_THAN_EQUAL: return "LESS_THAN_EQUAL";
                case OperatorType::GREATER_THAN: return "GREATER_THAN";
                case OperatorType::GREATER_THAN_EQUAL: return "GREATER_THAN_EQUAL";
                case OperatorType::LOGICAL_AND: return "LOGICAL_AND";
                case OperatorType::BITWISE_AND: return "BITWISE_AND";
                case OperatorType::LOGICAL_OR: return "LOGICAL_OR";
                case OperatorType::BITWISE_OR: return "BITWISE_OR";
                case OperatorType::BITWISE_XOR: return "BITWISE_XOR";
                case OperatorType::BITWISE_NOT: return "BITWISE_NOT";
                case OperatorType::INCREMENT: return "INCREMENT";
                case OperatorType::DECREMENT: return "DECREMENT";
                case OperatorType::NOT_EQUAL: return "NOT_EQUAL";
                case OperatorType::STRICT_NOT_EQUAL: return "STRICT_NOT_EQUAL";
                default: return "UNKNOWN OPERATOR";
            }
        }
        else {
            return "Unknown Lexeme";
        }
    }, lexeme);
}
