#include <iostream>
#include <fstream>
#include <stack>
#include <string>

int main() {
    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada

    std::ifstream file(xmlfilename);
    if (!file.is_open()) {
        std::cout << "Falha ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::stack<std::string> tagStack;  // Pilha para armazenar as tags

    std::string line;
    while (std::getline(file, line)) {
        size_t startPos = line.find("<");
        while (startPos != std::string::npos) {
            size_t endPos = line.find(">", startPos);
            if (endPos != std::string::npos) {
                std::string tag = line.substr(startPos + 1, endPos - startPos - 1);
                if (tag[0] != '/') {  // É uma tag de abertura
                    tagStack.push(tag);
                } else {  // É uma tag de fechamento
                    std::string closingTag = tag.substr(1);
                    if (!tagStack.empty() && tagStack.top() == closingTag) {
                        tagStack.pop();
                    } else {
                        std::cout << "Tag de fechamento inesperada: </" << closingTag << ">" << std::endl;
                        return 1;
                    }
                }
            }
            startPos = line.find("<", endPos);
        }
    }

    // Verifica se a pilha está vazia, indicando que todas as tags foram corretamente fechadas
    if (tagStack.empty()) {
        std::cout << "Todas as tags foram fechadas corretamente." << std::endl;
    } else {
        std::cout << "Existem tags de abertura sem o fechamento correspondente." << std::endl;
    }

    return 0;
}