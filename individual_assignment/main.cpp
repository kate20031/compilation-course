#include <iostream>
#include <string>
#include <vector>
#include <cctype>

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

class Scanner {
private:

    string text;
    size_t pos;
    int line;
    int column;
    vector<Token> tokens;

    char currentChar() const {
        if (pos >=  text.length() ) {
            return '\0';
        }

        return text[pos];
    }

    char peek(size_t offset  = 1) const {
        size_t index = pos +  offset;


        if (index >= text.length()) {
            return '\0';
        }

        return text[index];
    }


    char advance() {
        char ch = currentChar();

        if (ch == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }

        pos++;
        return ch;
    }

    void addToken(TokenType type, const string& value, int tokenLine, int tokenColumn) {
        tokens.push_back({type, value, tokenLine, tokenColumn});
    }

    void scanNumber() {
        size_t startPos = pos;
        int startLine = line;
        int startColumn = column;

        while (isdigit(currentChar())) {
            advance();
        }

        bool isFloat = false;

        if (currentChar() == '.' && isdigit(peek())) {
            isFloat = true;
            advance();

            while (isdigit(currentChar())) {
                advance();

            }
        }

        if (currentChar() == 'e' ||   currentChar() == 'E') {
            isFloat = true;
            advance();

            if (currentChar() == '+' || currentChar()  == '-') {
                advance();
            }

            if (!isdigit(currentChar())) {
                string value = text.substr(startPos, pos - startPos);
                addToken(TokenType::ERROR_FLOAT, value, startLine, startColumn);
                return;
            }

            while (isdigit(currentChar())) {
                advance();
            }
        }

        string value = text.substr(startPos, pos - startPos);


        if (isFloat) {
            addToken(TokenType::FLOAT, value, startLine, startColumn);
        } else {
            addToken(TokenType::INT, value, startLine, startColumn);
        }
    }

    void scanString() {
        size_t startPos = pos;
        int startLine = line;
        int startColumn = column;

        advance(); 

        while (currentChar() != '\0') {
            if (currentChar() == '"') {
                advance(); 

                string value = text.substr(startPos, pos - startPos);
                addToken(TokenType::STRING, value, startLine, startColumn);
                return;
            } else {
                advance();
            }
        }

        string value = text.substr(startPos, pos - startPos);
        addToken(TokenType::ERROR_STRING, value, startLine, startColumn);
    }
 

public:
    Scanner(const string& inputText) {
        text = inputText;
        pos = 0;
        line = 1;
        column = 1;
    }
    

    vector<Token> scan() {
        while (currentChar()  != '\0') {
            char ch = currentChar();

            if (isspace(ch)) {
                advance();
            } else if (ch == '"') {
                scanString();
            } 
            else if (isdigit(ch )) {
                scanNumber();
            } else {
                advance();
            }
        }

        return tokens;
    }
};

int main() {
    cout << "OCaml scanner  started" << endl;

    string input = "let x = 51423";

    Scanner scanner(input);
    vector<Token> tokens = scanner.scan();

        for (const Token& token : tokens) {
    cout << " token type: " << tokenTypeToString(token.type) << endl
            << " token value: " << token.value << endl
            << "  line: " << token.line << endl
            << " column: " << token.column 
            << endl;
    }

    return 0;
}