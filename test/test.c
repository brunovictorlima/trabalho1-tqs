#include "minunit-master/minunit.h"
#include "../calculadora.h"


// ========================================================================
// Funções de Teste Individuais (Baseadas na Tabela de Casos de Teste)
// Cada MU_TEST representa um ou mais casos de teste relacionados
// ========================================================================

MU_TEST(test_validar_quantidade_valida) {
    // Testa a função validarQuantidade com valores válidos (PE e AVL nos limites)
    mu_check(validarQuantidade(1) == 1);   // Quantidade no limite inferior válido (AVL) - Ref. Caso 4 (Q=1, I=35)
    mu_check(validarQuantidade(3) == 1);   // Quantidade no meio da partição válida (PE) - Ref. Caso 1 (Q=3, I=5)
    mu_check(validarQuantidade(5) == 1);   // Quantidade no limite superior válido (AVL) - Ref. Caso 5 (Q=5, I=35)
}

MU_TEST(test_validar_quantidade_invalida) {
    // Testa a função validarQuantidade com valores inválidos (PE e AVL nos limites)
    mu_check(validarQuantidade(0) == 0);   // Quantidade zero (AVL limite inferior inválido) - Ref. Caso 14
    mu_check(validarQuantidade(-1) == 0);  // Quantidade negativa (PE partição inválida < 0) - Ref. Caso 15
    mu_check(validarQuantidade(6) == 0);   // Quantidade justo acima do limite válido (AVL) - Ref. Caso 16
    mu_check(validarQuantidade(10) == 0);  // Quantidade muito acima do limite (PE partição inválida > 5) - Ref. Caso 17
}

MU_TEST(test_obter_preco_idade_crianca) {
    // Testa a função obterPrecoPorIdade para a faixa Criança (<= 12)
    mu_check(obterPrecoPorIdade(1) == PRECO_CRIANCA);   // Limite inferior válido (AVL) - Ref. Caso 20
    mu_check(obterPrecoPorIdade(5) == PRECO_CRIANCA);   // Meio da partição (PE) - Ref. Caso 1
    mu_check(obterPrecoPorIdade(12) == PRECO_CRIANCA);  // Limite superior (AVL) - Ref. Caso 6, 7
    mu_check(obterPrecoPorIdade(11) == PRECO_CRIANCA);  // Justo abaixo do limite (AVL)
}

MU_TEST(test_obter_preco_idade_adulto) {
    // Testa a função obterPrecoPorIdade para a faixa Adulto (13 a 59)
    mu_check(obterPrecoPorIdade(13) == PRECO_ADULTO);  // Limite inferior (AVL) - Ref. Caso 8, 9
    mu_check(obterPrecoPorIdade(30) == PRECO_ADULTO);  // Meio da partição (PE) - Ref. Caso 2
    mu_check(obterPrecoPorIdade(59) == PRECO_ADULTO);  // Limite superior (AVL) - Ref. Caso 10, 11
    mu_check(obterPrecoPorIdade(14) == PRECO_ADULTO);  // Justo acima do limite (do 12) (AVL)
    mu_check(obterPrecoPorIdade(58) == PRECO_ADULTO);  // Justo abaixo do limite (do 60) (AVL)
}

MU_TEST(test_obter_preco_idade_idoso) {
    // Testa a função obterPrecoPorIdade para a faixa Idoso (>= 60)
    mu_check(obterPrecoPorIdade(60) == PRECO_IDOSO);   // Limite inferior (AVL) - Ref. Caso 12, 13
    mu_check(obterPrecoPorIdade(70) == PRECO_IDOSO);   // Meio da partição (PE) - Ref. Caso 3
    mu_check(obterPrecoPorIdade(61) == PRECO_IDOSO);   // Justo acima do limite (do 59) (AVL)
    mu_check(obterPrecoPorIdade(100) == PRECO_IDOSO);  // Valor alto na partição (PE) - Ref. Caso 21
}

MU_TEST(test_obter_preco_idade_invalida) {
     // Testa a função obterPrecoPorIdade para idades inválidas (<= 0)
    mu_check(obterPrecoPorIdade(0) == -1);   // Limite inferior inválido (AVL) - Ref. Caso 18
    mu_check(obterPrecoPorIdade(-5) == -1);  // Valor negativo (PE) - Ref. Caso 19
}

// --- Testes para o Cálculo Total (Combinando Idade e Quantidade Válidas) ---
// Estes testes verificam se a combinação de uma quantidade válida e uma idade válida
// resulta no preço total esperado.

MU_TEST(test_calculo_total_crianca) {
    int idade = 5; // Criança (PE)
    int quantidade = 3; // Válida (PE)
    mu_check(validarQuantidade(quantidade) == 1); // Opcional, mas bom para verificar a premissa
    mu_check(obterPrecoPorIdade(idade) != -1);
    mu_check(quantidade * obterPrecoPorIdade(idade) == 3 * PRECO_CRIANCA); // Ref. Caso 1

    idade = 12; // Criança limite (AVL)
    quantidade = 5; // Quantidade limite (AVL)
    mu_check(validarQuantidade(quantidade) == 1);
    mu_check(obterPrecoPorIdade(idade) != -1);
    mu_check(quantidade * obterPrecoPorIdade(idade) == 5 * PRECO_CRIANCA); // Combinação AVL-AVL

    idade = 1; // Criança limite (AVL)
    quantidade = 1; // Quantidade limite (AVL)
    mu_check(validarQuantidade(quantidade) == 1);
    mu_check(obterPrecoPorIdade(idade) != -1);
    mu_check(quantidade * obterPrecoPorIdade(idade) == 1 * PRECO_CRIANCA); // Ref. Caso 20
}

MU_TEST(test_calculo_total_adulto) {
    int idade = 30; // Adulto (PE)
    int quantidade = 2; // Válida (PE)
    mu_check(validarQuantidade(quantidade) == 1);
    mu_check(obterPrecoPorIdade(idade) != -1);
    mu_check(quantidade * obterPrecoPorIdade(idade) == 2 * PRECO_ADULTO); // Ref. Caso 2

    idade = 13; // Adulto limite (AVL)
    quantidade = 4; // Válida (AVL)
    mu_check(validarQuantidade(quantidade) == 1);
    mu_check(obterPrecoPorIdade(idade) != -1);
    mu_check(quantidade * obterPrecoPorIdade(idade) == 4 * PRECO_ADULTO); // Combinação AVL-AVL

    idade = 59; // Adulto limite (AVL)
    quantidade = 5; // Quantidade limite (AVL)
    mu_check(validarQuantidade(quantidade) == 1);
    mu_check(obterPrecoPorIdade(idade) != -1);
    mu_check(quantidade * obterPrecoPorIdade(idade) == 5 * PRECO_ADULTO); // Ref. Caso 5 (Idade 35 no original, mas a lógica é a mesma para 59)

    idade = 35; // Adulto (PE)
    quantidade = 1; // Quantidade limite (AVL)
     mu_check(validarQuantidade(quantidade) == 1);
    mu_check(obterPrecoPorIdade(idade) != -1);
    mu_check(quantidade * obterPrecoPorIdade(idade) == 1 * PRECO_ADULTO); // Ref. Caso 4
}

MU_TEST(test_calculo_total_idoso) {
    int idade = 70; // Idoso (PE)
    int quantidade = 4; // Válida (PE)
    mu_check(validarQuantidade(quantidade) == 1);
    mu_check(obterPrecoPorIdade(idade) != -1);
    mu_check(quantidade * obterPrecoPorIdade(idade) == 4 * PRECO_IDOSO); // Ref. Caso 3

    idade = 60; // Idoso limite (AVL)
    quantidade = 2; // Válida (PE)
    mu_check(validarQuantidade(quantidade) == 1);
    mu_check(obterPrecoPorIdade(idade) != -1);
    mu_check(quantidade * obterPrecoPorIdade(idade) == 2 * PRECO_IDOSO); // Ref. Caso 12, 13

    idade = 100; // Idoso alto (PE)
    quantidade = 5; // Quantidade limite (AVL)
     mu_check(validarQuantidade(quantidade) == 1);
    mu_check(obterPrecoPorIdade(idade) != -1);
    mu_check(quantidade * obterPrecoPorIdade(idade) == 5 * PRECO_IDOSO); // Ref. Caso 21
}

MU_TEST(test_calculo_total_limites_quantidade) {
    // Testa o cálculo total para quantidades nos limites válidos e próximos,
    // usando uma idade representativa válida (Adulto, preco 30)

    int idade_representativa = 35; // Idade válida (Adulto, preço R$ 30)
    int preco_unitario_representativo = obterPrecoPorIdade(idade_representativa);
    mu_check(preco_unitario_representativo != -1); // Garante que a idade representativa é válida

    // --- Quantidade no limite inferior válido (1) ---
    int quantidade = 1;
    mu_check(validarQuantidade(quantidade) == 1); // Verifica se a quantidade é marcada como válida
    mu_check(quantidade * preco_unitario_representativo == 1 * PRECO_ADULTO); // Verifica o cálculo total (Ref. Caso 4)

    // --- Quantidade justo acima do limite inferior (2) ---
    quantidade = 2;
    mu_check(validarQuantidade(quantidade) == 1);
    mu_check(quantidade * preco_unitario_representativo == 2 * PRECO_ADULTO); // Baseado em AVL

    // --- Quantidade justo abaixo do limite superior (4) ---
    quantidade = 4;
    mu_check(validarQuantidade(quantidade) == 1);
    mu_check(quantidade * preco_unitario_representativo == 4 * PRECO_ADULTO); // Baseado em AVL

    // --- Quantidade no limite superior válido (5) ---
    quantidade = 5;
    mu_check(validarQuantidade(quantidade) == 1); // Verifica se a quantidade é marcada como válida
    mu_check(quantidade * preco_unitario_representativo == 5 * PRECO_ADULTO); // Verifica o cálculo total (Ref. Caso 5)

    // Observação: Testes para quantidades inválidas (0, <0, >5) são cobertos em test_validar_quantidade_invalida
}


// ========================================================================
// Suite de Testes
// Lista todos os testes a serem executados
// ========================================================================

MU_TEST_SUITE(test_suite) {
    // Execute os testes de validação de quantidade
    MU_RUN_TEST(test_validar_quantidade_valida);
    MU_RUN_TEST(test_validar_quantidade_invalida);

    // Execute os testes de preço por idade
    MU_RUN_TEST(test_obter_preco_idade_crianca);
    MU_RUN_TEST(test_obter_preco_idade_adulto);
    MU_RUN_TEST(test_obter_preco_idade_idoso);
    MU_RUN_TEST(test_obter_preco_idade_invalida);

    // Execute os testes de cálculo total para diferentes faixas de idade
    MU_RUN_TEST(test_calculo_total_crianca);
    MU_RUN_TEST(test_calculo_total_adulto);
    MU_RUN_TEST(test_calculo_total_idoso);
    MU_RUN_TEST(test_calculo_total_limites_quantidade);

    // Adicione outras suites de testes aqui se o projeto crescer e precisar organizar melhor
}

// ========================================================================
// Função Principal do Test Runner (Fornecida pelo template do MinUnit)
// ========================================================================

int main(int argc, char *argv[]) {
    // Executa a suite de testes principal
    MU_RUN_SUITE(test_suite);

    // Reporta os resultados (número de testes, falhas)
    MU_REPORT();

    // Retorna o código de saída apropriado (0 para sucesso, 1 para falha)
    return MU_EXIT_CODE;
}