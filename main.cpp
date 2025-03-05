#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "lexer.hpp"

int main() {
    std::string filepath = "expressions.txt";  // Directly access the file in the same folder

    std::cout << "Reading the file: " << filepath << std::endl;
    std::ifstream sourceFileStream(filepath);

    if (!sourceFileStream) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << sourceFileStream.rdbuf();
    std::string sourceCode = buffer.str();

    Lexer lexer(sourceCode);
    std::vector<Character *> characters = lexer.getCharacters();

    int counter = 0;

    std::cout << "Analysis ended successfully\n";

    for (Character *temp : characters) {
        counter++;
        std::cout << counter << ") " << temp->VALUE << " " << typeToStr(temp->TYPE) << std::endl;
        delete temp;  // Free memory
    }

    std::cout << "\nEnd of the program\n";
    return 0;
}