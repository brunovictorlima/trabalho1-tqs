#include <stdio.h>
#include "calculadora.h"

int main() {
    int idade;
    int quantidade;
    int preco_unitario;
    int total;

    printf("=== Sistema de Venda de Bilhetes ===\n");

    // Leitura da idade com verificação básica do scanf
    printf("Informe a idade do visitante: ");
    if (scanf("%d", &idade) != 1) {
        printf("Erro ao ler a idade. Por favor, insira um número inteiro.\n");
        return 1; // Indica erro na execução
    }

    // Leitura da quantidade com verificação básica do scanf
    printf("Informe a quantidade de bilhetes (maximo %d): ", LIMITE_BILHETES);
    if (scanf("%d", &quantidade) != 1) {
        printf("Erro ao ler a quantidade. Por favor, insira um número inteiro.\n");
        return 1; // Indica erro na execução
    }

    // Valida a quantidade primeiro
    if (!validarQuantidade(quantidade)) {
        printf("\n=== Quantidade inválida de bilhetes! Limite: %d por pessoa. ===\n", LIMITE_BILHETES);
        // Não calcula nem imprime o total, pois a quantidade é inválida
    } else {
        // Se a quantidade for válida, obtém o preço unitário pela idade
        preco_unitario = obterPrecoPorIdade(idade);

        // Verifica se a idade resultou em um preço válido
        if (preco_unitario == -1) {
             printf("\n=== Idade informada invalida. ===\n");
        } else {
            // Calcula o total (quantidade válida e idade com preço válido)
            total = quantidade * preco_unitario;

            // Imprime o resultado
            printf("\n--- Resumo da Compra ---\n");
            printf("Idade informada: %d\n", idade);
            printf("Quantidade de bilhetes: %d\n", quantidade);
            printf("Preco unitario: R$ %d,00\n", preco_unitario);
            printf("O valor total é R$ %d,00\n", total);
            printf("-----------------------\n");
        }
    }

    return 0; // Indica que o programa terminou com sucesso
}