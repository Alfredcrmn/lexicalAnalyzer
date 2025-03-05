#ifndef __LEXER_H
#define __LEXER_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

enum Type {
    CHARACTER_VARIABLE,
    CHARACTER_INT,
    CHARACTER_ASSIGNMENT,
    CHARACTER_SUM,
    CHARACTER_SUB,
    CHARACTER_PROD,
    CHARACTER_DIV,
    CHARACTER_LEFT_PARENTHESIS,
    CHARACTER_RIGHT_PARENTHESIS
};

struct Character { 
    Type TYPE; //Indicates the type of character
    std::string VALUE; //stores the value as a string 
};

std::string typeToStr(Type TYPE) {
    switch (TYPE) { //Uses switch 
        case CHARACTER_VARIABLE: return "CHARACTER_VARIABLE"; // " a - z "
        case CHARACTER_INT: return "CHARACTER_INT"; // " 0 - 9 "
        case CHARACTER_ASSIGNMENT: return "CHARACTER_ASSIGNMENT"; // " = "
        case CHARACTER_SUM: return "CHARACTER_SUM"; // " + "
        case CHARACTER_SUB: return "CHARACTER_SUB"; // " - "
        case CHARACTER_PROD: return "CHARACTER_PROD"; // " * " 
        case CHARACTER_DIV: return "CHARACTER_DIV"; // " / "
        case CHARACTER_LEFT_PARENTHESIS: return "CHARACTER_LEFT_PARENTHESIS"; // " ( "
        case CHARACTER_RIGHT_PARENTHESIS: return "CHARACTER_RIGHT_PARENTHESIS"; // " ) "
        default: return "UNKNOWN";
    }
}

class Lexer { 
public:
    Lexer(std::string sourceCode) {
        source = sourceCode;
        cursor = 0;
        size = sourceCode.length();
        current = (size > 0) ? source.at(0) : '\0';
    }

    char advance() {
        if (cursor < size) {
            char temp = current;
            cursor++;
            current = (cursor < size) ? source[cursor] : '\0';
            return temp;
        } else {
            return '\0';
        }
    }

    void checkAndSkip() {
        while (current == ' ' || current == '\n' || current == '\t' || current == '\r') {
            advance();
        }
    }

    Character* characterID() {
        std::stringstream buffer;
        buffer << advance();

        while (islower(current)) {  // Only allow lowercase letters (a-z)
            buffer << advance();
        }

        Character* newCharacter = new Character();
        newCharacter->TYPE = CHARACTER_VARIABLE;
        newCharacter->VALUE = buffer.str();

        return newCharacter;
    }

    Character* characterSPECIAL(Type TYPE) {
        Character* newCharacter = new Character();
        newCharacter->TYPE = TYPE;
        newCharacter->VALUE = std::string(1, advance());
        return newCharacter;
    }

    Character* characterInt() {
        std::stringstream buffer;
        while (isdigit(current)) {
            buffer << advance();
        }

        Character* newCharacter = new Character();
        newCharacter->TYPE = CHARACTER_INT;
        newCharacter->VALUE = buffer.str();

        return newCharacter;
    }

    std::vector<Character*> getCharacters() {
        std::vector<Character*> characters;

        while (cursor < size) {
            checkAndSkip();

            if (islower(current)) {  // Only allow lowercase letters for variable names
                characters.push_back(characterID());
                continue;
            }

            if (isdigit(current)) {
                characters.push_back(characterInt());
                continue;
            }

            switch (current) {
                case '=': characters.push_back(characterSPECIAL(CHARACTER_ASSIGNMENT)); break;
                case '+': characters.push_back(characterSPECIAL(CHARACTER_SUM)); break;
                case '-': characters.push_back(characterSPECIAL(CHARACTER_SUB)); break;
                case '*': characters.push_back(characterSPECIAL(CHARACTER_PROD)); break;
                case '/': characters.push_back(characterSPECIAL(CHARACTER_DIV)); break;
                case '(': characters.push_back(characterSPECIAL(CHARACTER_LEFT_PARENTHESIS)); break;
                case ')': characters.push_back(characterSPECIAL(CHARACTER_RIGHT_PARENTHESIS)); break;
                default:
                    std::cout << "Unknown character: " << current << std::endl;
            }
        }
        return characters;
    }

private:
    std::string source;
    int cursor;
    int size;
    char current;
};

#endif  // __LEXER_H