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
        default: return "UNKNOWN"; //Not defined characters
    }
}

class Lexer { 
public:
    Lexer(std::string sourceCode) { //Gets the source code as a string
        source = sourceCode;
        cursor = 0; // Initializes cursor on 0
        size = sourceCode.length(); // Size is the length of the source code
        current = (size > 0) ? source.at(0) : '\0'; //Current stores the first character of the source code
    }

    char advance() { // Continues in the lecture of the source code
        if (cursor < size) {
            char temp = current; // Stores the actual character in temp
            cursor++; // Increments the cursor 
            current = (cursor < size) ? source[cursor] : '\0'; //Returns the read character and '\0' if it gets to the end of code  
            return temp;
        } else {
            return '\0';
        }
    }

    void checkAndSkip() { // Skips blank spaces and empty lines
        while (current == ' ' || current == '\n' || current == '\t' || current == '\r') {
            advance(); // Skips empty characters (' ', '\n', '\t', '\r') to avoid their processing
        }
    }

    Character* characterID() { // Analyzes identifiers (or variables)
        std::stringstream buffer;
        buffer << advance(); // Will continue while the character is a lower case letter

        while (islower(current)) {  // Only allow lowercase letters (a-z)
            buffer << advance();
        }

        Character* newCharacter = new Character();
        newCharacter->TYPE = CHARACTER_VARIABLE; // Creates a character CHARACTER_VARIABLE type and their value
        newCharacter->VALUE = buffer.str();

        return newCharacter;
    }

    Character* characterSPECIAL(Type TYPE) { // Receives corresponding type
        Character* newCharacter = new Character(); 
        newCharacter->TYPE = TYPE;
        newCharacter->VALUE = std::string(1, advance()); // Creates a character with the given type and their value
        return newCharacter;
    }

    Character* characterInt() {
        std::stringstream buffer;
        while (isdigit(current)) {
            buffer << advance(); 
        } // accumulates digits in a stringstream

        Character* newCharacter = new Character();
        newCharacter->TYPE = CHARACTER_INT;
        newCharacter->VALUE = buffer.str();

        return newCharacter; //Returns a character with CHARACTER_INT
    }

    std::vector<Character*> getCharacters() {
        std::vector<Character*> characters;

        while (cursor < size) {
            checkAndSkip(); // Skips blank spaces

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
    std::string source; // Source code
    int cursor; // Actual position on the lecture
    int size; // Length of the source code
    char current; // Character being analyzed
};

#endif  // __LEXER_H