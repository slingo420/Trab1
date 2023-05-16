#include <iostream>
#include <fstream>
#include <stack>
#include <string>

//-----------Valores de Tags Necessarios-----------//
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
//-----------Variaveis para valores de Tags necessarios-----------//


//-----------Funcao para atribuir valores para as variaveis-----------//
void getVars(const std::string& xmlfilename) {
    std::ifstream file(xmlfilename);  //cria o arquivo

    std::string line; 
    while (std::getline(file, line)) {  //loop para percorrer cada linha do arquivo 
        size_t startPos = line.find("<");  //busca por tags 
        while (startPos != std::string::npos) {
            size_t endPos = line.find(">", startPos);
            if (endPos != std::string::npos) {
                std::string tag = line.substr(startPos + 1, endPos - startPos - 1);
                if (tag[0] != '/') {  //É uma tag de abertura
                    size_t closingTagPos = line.find("</" + tag + ">", endPos);
                    if (closingTagPos != std::string::npos) {
                        size_t valueStartPos = endPos + 1;
                        std::string value = line.substr(valueStartPos, closingTagPos - valueStartPos);  //adquire o valor da tag 
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
                        if (tag == "matriz") {

                        }
                        //armazenar a matriz em uma variavel
                        //criar uma funcao que recebe como argumento nome_cenario, dimensaomatriz.altura, dimensaomatriz.largura,
                        //robo_.x, robo_.y e a matriz e calcula o tamanho da area que deve ser limpa pelo robo
                        //depois, a funcao deve imprimir nome_cenario e o tamanho da area que deve ser limpa pelo robo
                        //chamar a funcao que calcula a area da matriz e passar todos os argumentos
                    }
                }
            }
            startPos = line.find("<", endPos);
        }
    }
}
//-----------Funcao para atribuir valores para as variaveis-----------//

int main() {
    //-----------Problema1: Empilhar Tags-----------//
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
                std::string tag = line.substr(startPos + 1, endPos - startPos - 1);  //armazena o nome da tag na string tag
                if (tag[0] != '/') {  //É uma tag de abertura
                    tagStack.push(tag);  //empilha a tag
                } else {  //É uma tag de fechamento
                    std::string closingTag = tag.substr(1);
                    if (!tagStack.empty() && tagStack.top() == closingTag) {
                        tagStack.pop();  //desempilha a tag
                    } else {
                        std::cout << "Erro" << std::endl;
                        return 1;
                    }
                }
            }
            startPos = line.find("<", endPos);
        }
    }

    // Verifica se a pilha nao esta vazia, terminando em um erro caso nao esteja
    if (!tagStack.empty()) {
        std::cout << "Erro" << std::endl;
    }
    return 0;
    //-----------Problema1: Empilhar Tags-----------//
}