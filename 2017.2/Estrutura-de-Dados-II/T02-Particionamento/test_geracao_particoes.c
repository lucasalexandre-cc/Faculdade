#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <io.h>
#define F_OK 0
#define ACCESS _access
#else
#include <unistd.h>
#define ACCESS access
#endif

#define AFTER_TEST after();
#define NOME_ARQUIVO_ENTRADA "entrada.dat"

#include <limits.h>
#include <stdlib.h>

#include "ufftest.h"
#include "cliente.h"
#include "lista_clientes.h"
#include "nomes.h"
#include "geracao_particoes.h"

Nomes *nomes = NULL;

void after()
{
	Nomes *atual = nomes;
	while (atual) {
		remove(atual->nome);
		atual = atual->prox;
	}
	libera_nomes(nomes);
	nomes = NULL;
}

int file_exist(char *filename)
{
	return (ACCESS(filename, F_OK) != -1);
}

BEGIN_TESTS();



/*********************************************************************
 * *******************************************************************
 * TESTES RELACIONADOS A GERAÇÃO DE PARTIÇÃO POR SELECAO NATURAL
 * *******************************************************************
 *********************************************************************/

TEST("Teste Selecao Natural. Arquivo vazio deve criar p1.dat vazio");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;

	entrada = cria_clientes(1, cliente(INT_MAX, ""));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(1, cliente(INT_MAX, ""));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 2 Selecao Natural. Arquivo com 2 registros ja ordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(3,
		cliente(1, "Joao"),
		cliente(5, "Maria"),
		cliente(INT_MAX, ""));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(3,
		cliente(1, "Joao"),
		cliente(5, "Maria"),
		cliente(INT_MAX, ""));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 3 Selecao Natural. Arquivo com 2 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(3,
		cliente(5, "Maria"),
		cliente(1, "Joao"),
		cliente(INT_MAX, ""));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(3,
		cliente(1, "Joao"),
		cliente(5, "Maria"),
		cliente(INT_MAX, ""));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 4 Selecao Natural. Arquivo com 6 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(7,
		cliente(5, "Maria"),
		cliente(1, "Joao"),
		cliente(10, "Mirtes"),
		cliente(8, "Vanessa"),
		cliente(7, "Bruna"),
		cliente(2, "Marcos"),
		cliente(INT_MAX, ""));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), cria_nomes(cria_str("p2.dat"), NULL));

	selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(7,
		cliente(1, "Joao"),
		cliente(2, "Marcos"),
		cliente(5, "Maria"),
		cliente(7, "Bruna"),
		cliente(8, "Vanessa"),
		cliente(10, "Mirtes"),
		cliente(INT_MAX, ""));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(0);
	ASSERT_FALSE(file_exist(p->nome))
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 5 Selecao Natural. Exemplo visto em aula");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(55,
		cliente(29, "Maria"),
		cliente(14, "Joao"),
		cliente(76, "Mirtes"),
		cliente(75, "Mariana"),
		cliente(59, "Matheus"),
		cliente(6, "Jonas"),
		cliente(7, "Vanessa"),
		cliente(74, "Karla"),
		cliente(48, "Tatiana"),
		cliente(46, "Larissa"),
		cliente(10, "Marcela"),
		cliente(18, "Bruna"),
		cliente(56, "Catarina"),
		cliente(20, "Leonel"),
		cliente(26, "Leo"),
		cliente(4, "Yasmin"),
		cliente(21, "Ana"),
		cliente(65, "Yoko"),
		cliente(22, "Mauricio"),
		cliente(49, "Jose"),
		cliente(11, "Alice"),
		cliente(16, "JC"),
		cliente(8, "TJ"),
		cliente(15, "Maira"),
		cliente(5, "Viviane"),
		cliente(19, "Fernanda"),
		cliente(50, "Daniel"),
		cliente(55, "Diego"),
		cliente(25, "Harry Potter"),
		cliente(66, "James Bond"),
		cliente(57, "Clark Kent"),
		cliente(77, "Lois Lane"),
		cliente(12, "Iris"),
		cliente(30, "Rosa"),
		cliente(17, "Helo"),
		cliente(9, "Joel"),
		cliente(54, "Carlos"),
		cliente(78, "Alex"),
		cliente(43, "Adriel"),
		cliente(38, "Ana Paula"),
		cliente(51, "Bia"),
		cliente(32, "Milton"),
		cliente(58, "Xande"),
		cliente(13, "Fausto"),
		cliente(73, "Sidney"),
		cliente(79, "Igor"),
		cliente(27, "Alexandre"),
		cliente(1, "Aline"),
		cliente(3, "Andrea"),
		cliente(60, "Murilo"),
		cliente(36, "Rafael"),
		cliente(47, "Ricardo"),
		cliente(31, "Regiane"),
		cliente(80, "Fabio"),
		cliente(INT_MAX, ""));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"),
		cria_nomes(cria_str("p2.dat"),
		cria_nomes(cria_str("p3.dat"),
		cria_nomes(cria_str("p4.dat"),
		cria_nomes(cria_str("p5.dat"), NULL)))));

	selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(12,
		cliente(6, "Jonas"),
		cliente(7, "Vanessa"),
		cliente(14, "Joao"),
		cliente(29, "Maria"),
		cliente(46, "Larissa"),
		cliente(48, "Tatiana"),
		cliente(56, "Catarina"),
		cliente(59, "Matheus"),
		cliente(74, "Karla"),
		cliente(75, "Mariana"),
		cliente(76, "Mirtes"),
		cliente(INT_MAX, ""));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(10,
		cliente(4, "Yasmin"),
		cliente(10, "Marcela"),
		cliente(18, "Bruna"),
		cliente(20, "Leonel"),
		cliente(21, "Ana"),
		cliente(22, "Mauricio"),
		cliente(26, "Leo"),
		cliente(49, "Jose"),
		cliente(65, "Yoko"),
		cliente(INT_MAX, ""));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(16,
		cliente(5, "Viviane"),
		cliente(8, "TJ"),
		cliente(11, "Alice"),
		cliente(15, "Maira"),
		cliente(16, "JC"),
		cliente(19, "Fernanda"),
		cliente(25, "Harry Potter"),
		cliente(30, "Rosa"),
		cliente(50, "Daniel"),
		cliente(54, "Carlos"),
		cliente(55, "Diego"),
		cliente(57, "Clark Kent"),
		cliente(66, "James Bond"),
		cliente(77, "Lois Lane"),
		cliente(78, "Alex"),
		cliente(INT_MAX, ""));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(13,
		cliente(9, "Joel"),
		cliente(12, "Iris"),
		cliente(17, "Helo"),
		cliente(32, "Milton"),
		cliente(38, "Ana Paula"),
		cliente(43, "Adriel"),
		cliente(47, "Ricardo"),
		cliente(51, "Bia"),
		cliente(58, "Xande"),
		cliente(60, "Murilo"),
		cliente(73, "Sidney"),
		cliente(79, "Igor"),
		cliente(INT_MAX, ""));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(8,
		cliente(1, "Aline"),
		cliente(3, "Andrea"),
		cliente(13, "Fausto"),
		cliente(27, "Alexandre"),
		cliente(31, "Regiane"),
		cliente(36, "Rafael"),
		cliente(80, "Fabio"),
		cliente(INT_MAX, ""));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

END_TESTS();