#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "lexer.hpp"

int main() {
    std::string filepath = "expressions.txt";  // Directly access the file in the same folder

    std::cout << "Reading the file: " << filepath << std::endl; // Displays a message that the files is being read
    std::ifstream sourceFileStream(filepath); // Opens the file in lecture mode

    if (!sourceFileStream) {
        std::cerr << "Error opening file: " << filepath << std::endl; // Verifies that the file was opened successfully
        return 1;
    }

    std::stringstream buffer; // Creates a text buffger to storage the file content
    buffer << sourceFileStream.rdbuf(); // Reads the file from the buffer
    std::string sourceCode = buffer.str(); // Converts the buffer to a string

    Lexer lexer(sourceCode); // Instantiates Lexer and delivers the source code read in the file
    std::vector<Character *> characters = lexer.getCharacters(); // Obtains a list of characters analyzer by lexer

    int counter = 0;

    std::cout << "Analysis ended successfully\n"; // Indicates that the analysis is done

    for (Character *temp : characters) { // Loops the vector of characters obtained by the lexer
        counter++;
        std::cout << counter << ") " << temp->VALUE << " " << typeToStr(temp->TYPE) << std::endl; // Shows the token and its type
        delete temp;  // Free memory
    }

    std::cout << "\nEnd of the program\n"; // Indicates that the program is done
    return 0; // Exits
}