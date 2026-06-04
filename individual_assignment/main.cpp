#include <iostream>

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

int main() {
    cout << "OCaml scanner started" << endl;
    return 0;
}