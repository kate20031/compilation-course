#include <iostream>
#include <string>

using namespace std;

enum class TokenType {
    INT,
    FLOAT,
    STRING,
    COMMENT,
    IDENTIFIER,
    KEYWORD,
     SYMBOL,
    UNKNOWN,
    ERROR_STRING,
    ERROR_COMMENT,
    ERROR_FLOAT,
    END_OF_FILE
};

struct Token {
    TokenType type;
    string value;
    int line;
    int column;
};

string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INT: return "INT";
        case TokenType::FLOAT: return  "FLOAT";
        case TokenType::STRING: return  "STRING";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::IDENTIFIER:  return "IDENTIFIER";
        case TokenType::KEYWORD: return "KEYWORD";
        case TokenType::SYMBOL: return "SYMBOL";
        case  TokenType::UNKNOWN: return "UNKNOWN";
        case TokenType::ERROR_STRING: return "ERROR_STRING";
        case TokenType::ERROR_COMMENT: return "ERROR_COMMENT";
        case TokenType::ERROR_FLOAT: return "ERROR_FLOAT";
        case TokenType::END_OF_FILE:  return "END_OF_FILE";
        default: return "UNDEFINED";
    }
}

int main() {
    cout << "OCaml scanner started" << endl;
    return 0;
}