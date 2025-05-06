#include "calculadora.h" // Inclui as declarações
#include <stdio.h>

// Definição dos valores das constantes
const int LIMITE_BILHETES = 5;
const int PRECO_CRIANCA = 10;
const int PRECO_IDOSO = 15;
const int PRECO_ADULTO = 30;

// Função para validar a quantidade de bilhetes
// Retorna 1 se a quantidade for válida, 0 caso contrário
int validarQuantidade(int quantidade) {
    // A função apenas valida e retorna, sem imprimir mensagem
    return (quantidade > 0 && quantidade <= LIMITE_BILHETES);
}


// Função para obter o preço unitário com base na idade
// Retorna o preço correspondente à idade, ou -1 para idade inválida
int obterPrecoPorIdade(int idade) {
    if (idade > 0 && idade <= 12) {
        return PRECO_CRIANCA;
    } else if (idade >= 13 && idade <= 59) {
        return PRECO_ADULTO;
    } else if (idade >= 60) {
        return PRECO_IDOSO;
    } else {
        // Idade inválida (por exemplo, 0 ou negativa, embora a lógica já trate 1-12)
        return -1; // Retorna um valor que indica erro
    }
}