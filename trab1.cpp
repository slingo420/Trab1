#include <iostream>
#include <fstream>
#include <stack>
#include <string>

std::string nome_cenario;

struct dimensoes {
  int altura;
  int largura;
};

struct robo {
  int x;
  int y;
};

dimensoes dimensaomatriz;
robo robo_;

void getVars(const std::string& xmlfilename) {
    std::ifstream file(xmlfilename);

    std::string line;
    while (std::getline(file, line)) {
        size_t startPos = line.find("<");
        while (startPos != std::string::npos) {
            size_t endPos = line.find(">", startPos);
            if (endPos != std::string::npos) {
                std::string tag = line.substr(startPos + 1, endPos - startPos - 1);
                if (tag[0] != '/') {  // É uma tag de abertura
                    size_t closingTagPos = line.find("</" + tag + ">", endPos);
                    if (closingTagPos != std::string::npos) {
                        size_t valueStartPos = endPos + 1;
                        std::string value = line.substr(valueStartPos, closingTagPos - valueStartPos);
                        std::cout << "Tag: " << tag << ", Valor: " << value << std::endl;
                        if (tag == "nome") {
                            nome_cenario = value;
                        }
                        if (tag == "altura") {
                            dimensaomatriz.altura = std::stoi(value);
                        }
                        if (tag == "largura") {
                            dimensaomatriz.largura = std::stoi(value);
                        }
                        if (tag == "x") {
                            robo_.x = std::stoi(value);
                        }
                        if (tag == "y") {
                            robo_.y = std::stoi(value);
                        }
                        // encontrar uma forma de armazenar a matriz
                        // chamar uma funcao que limpa a area da matriz
                    }
                }
            }
            startPos = line.find("<", endPos);
        }
    }
}

int main() {
    // Primeiro problema - begin
    
    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada

    std::ifstream file(xmlfilename);

    getVars(xmlfilename);
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
                        std::cout << "Erro" << std::endl;
                        return 1;
                    }
                }
            }
            startPos = line.find("<", endPos);
        }
    }

    // Verifica se a pilha está vazia, indicando que todas as tags foram corretamente fechadas
    if (!tagStack.empty()) {
        std::cout << "Erro" << std::endl;
    }
    return 0;

    // Primeiro problema - end
}