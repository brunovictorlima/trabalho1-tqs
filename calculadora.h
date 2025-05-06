#ifndef CALCULADORA_H
#define CALCULADORA_H

// Declaração de constantes do projeto
extern const int LIMITE_BILHETES;
extern const int PRECO_CRIANCA;
extern const int PRECO_IDOSO;
extern const int PRECO_ADULTO;

// Declarações das funções de lógica
int validarQuantidade(int quantidade);
int obterPrecoPorIdade(int idade);

#endif // CALCULADORA_H