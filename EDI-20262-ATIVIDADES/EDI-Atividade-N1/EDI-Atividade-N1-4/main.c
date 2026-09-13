#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 	Apelidamos de No a estrutura que irá receber:
 * 		- id do Paciente
 * 		- nome do Paciente
 * 		- ponteiro que recebe o endereço do próximo No
 */
typedef struct no {
	int id;
	char nome[50];
	struct no *prox;
} No; 

/*
 * 	Apelidamos de NoPtr um ponteiro do tipo No que armazena um endereço de memória da estrutura No 
 */
typedef No* NoPtr;

/* 
 *	Declarando uma estrutura que chamará Cabecalho e terá dois ponteiros:
 *		- NoPtr ini é uma variável do tipo NoPtr, ou seja, um ponteiro do tipo No que irá armazenar o endereço do primeiro No
 *		- NoPtr fim é uma variável do tipo NoPtr, ou seja, um ponteiro do tipo No que irá armazenar o endereço do último No
 */
typedef struct {
	NoPtr ini;
	NoPtr fim;
} Cabecalho; 

/*
 *	Declarando um ponteiro que chamaremos de Fila que aponta para o endereço do Cabecalho. 
 *	O Cabecalho é a estrutura que armazena o No inicial e final da Fila 
 */
typedef Cabecalho* Fila;

/*
 * 	Função que cria e retorna o ponteiro da Fila
 */
Fila Criar() {
	// Alocação de memória para a variável Fila f do tamanho da estrutura Cabecalho
	Fila f = (Fila) malloc(sizeof(Cabecalho));
	if (f != NULL){
		f->ini = NULL;
		f->fim = NULL;
	}
	return f;
}

/*
 *	Função auxiliar que valida se a fila está vazia
 */
int filaVazia(Fila f){
	if (f == NULL || f->ini == NULL){
		printf("\n[AVISO] A fila esta vazia.\n");
		return 1;
	} else {
		return 0;
	}	
}

/*
 *	Função para inserir um novo Paciente à Fila
 */
int inserir(Fila f, int id, const char *nome){
	// Declaramos uma nova variável do tipo NoPtr que será o ponteiro do nosso novo Paciente de estrutura No
	NoPtr novo = (NoPtr) malloc(sizeof(No));
	if (novo == NULL) return 0;

	// Atribuindo os valores id e nome ao novo No
	novo->id = id;
	strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
	novo->nome[sizeof(novo->nome) - 1] = '\0';
	novo->prox = NULL;

	if (f->ini == NULL){
		// Significa que se a lista estiver vazia, ou seja, o f->ini (primeiro nó) apontar para NULO, devemos atribuir o novo nó como primeiro da fila
		f->ini = novo;
	} else {
		// Se não estiver vazia, atribuimos o novo nó ao final da fila
		// O nó que é considerado o último da fila deixa de apontar para NULO e passa a apontar para o próximo da fila (novo). 
		f->fim->prox = novo;
	}

	// Agora que novo foi inserido na fila, devemos atualizar ele como sendo o último desta fila
	f->fim = novo;
	return 1;
}

/*
 *	Função para remover um Paciente da fila
 */
int remover(Fila f){
	// Validar se a fila não está vazia
	if (filaVazia(f)) return 0;	

	// Se não estiver vazia, "atual" recebe o primeiro Paciente da fila
	NoPtr atual = f->ini;
	f->ini = atual->prox;
	
	// Exibindo dados do paciente em atendimento
	printf(">> Paciente em atendimento:\n");
	printf(">> ID: %d - Nome: %s\n", atual->id, atual->nome);
	
	// Liberando a memória alocada do primeiro paciente da fila
	free(atual);
	return 1;
}

/*
 *	Função para consultar o primeiro da paciente da fila
 */	
void consultar(Fila f){
	if (filaVazia(f)){
		printf(">> Não foi possível consultar o próximo da fila.\n");
		return;
	}
	
	printf(">> Próximo paciente da fila:\n");
	printf(">> ID: %d - Nome: %s\n", f->ini->id, f->ini->nome);
}

/*
 *	Função para contar os Pacientes da fila
 */
int contar(Fila f){
	if (filaVazia(f)){
		return 0;
	} else {
		int i = 0;	
		NoPtr atual = f->ini;
		
		while(atual != NULL){
			i++;
			atual = atual->prox;	
		}
		return i;
	}
}

/*
 *	Função para listar a os Pacientes da fila
 */
void listarFila(Fila f){
	// Valida se a fila não está vazia chamando a função auxiliar int filaVazia(Fila f);
	if (filaVazia(f)) return;

	// Cria uma variável de ponteiro provisória que percorrer pela fila
	NoPtr atual = f->ini;
	printf("\n=== FILA DE PACIENTES ===\n");

	// Enquanto esse ponteiro não chegar ao fim da fila, igual a nulo, ele irá imprimir o paciente e seu id atuais e passar para o próximo.
	while (atual != NULL){
		printf("ID: %d - Nome: %s\n", atual->id, atual->nome);
		atual = atual->prox;
	}
	printf("=========================\n");

}

/*
 * Função para esvaziar a fila liberando a memória de cada um dos nós
 */
void esvaziarFila(Fila f){
	NoPtr atual = f->ini;
	NoPtr proximo;

	while (atual != NULL){
		proximo = atual->prox;
		free(atual);
		atual = proximo;
	}
	
	f->ini = NULL;
	f->fim = NULL;

	printf(">> Realizado a liberação de memória da fila.\n");
}

/*
 *	Função para liberar a memória da fila que foi criada 
 */
void destruirFila(Fila f){
	free (f);
}

int main(){
	Fila filaAtendimento = Criar();
	int opcao, id;
	char nome[50];

	do {
		printf("\n--- SISTEMA HOSPITALAR (FATEC IPIRANGA) ---\n");
		printf("1. Chegada de Paciente (Inserir na Fila)\n");
		printf("2. Listar Fila de Pacientes\n");
		printf("3. Atender Paciente (Retirar da Fila)\n");
		printf("4. Consultar Próximo da Fila\n");
		printf("5. Verificar a Quantidade de Pacientes na Fila\n");
		printf("0. Sair\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);

		switch(opcao){
			case 1:
				printf("Informe o ID do paciente: ");
				scanf("%d", &id);
				getchar(); // Limpar o buffer do teclado
				printf("Informe o Nome do paciente: ");
				fgets(nome, sizeof(nome), stdin);
				nome[strcspn(nome, "\n")] = 0; // Remover quebra de linha
				
				if (inserir(filaAtendimento, id, nome)){
					printf(">> Paciente inserido com sucesso!\n");	
				} else {
					printf(">> Erro ao inserir paciente.\n");
				}
				break;
			case 2:
				listarFila(filaAtendimento);
				break;
			case 3:
				if (!remover(filaAtendimento)) {
					printf(">> Erro ao atender paciente.\n");		
				} else {
					printf(">> Primeiro paciente da fila atendido com sucesso.\n");
				}
				break;
			case 4:
				consultar(filaAtendimento);
				break;
			case 5:
				int qtd = contar(filaAtendimento);
				printf(">> Quantidade de pacientes na fila: %d.\n", qtd);
				break;
			case 0:
				esvaziarFila(filaAtendimento);
				destruirFila(filaAtendimento);
				printf(">> Encerrando o sistema...\n");
				break;
			default:
				printf("Opcao invalida!\n");
		}
	} while (opcao != 0);

	return 0;
}
