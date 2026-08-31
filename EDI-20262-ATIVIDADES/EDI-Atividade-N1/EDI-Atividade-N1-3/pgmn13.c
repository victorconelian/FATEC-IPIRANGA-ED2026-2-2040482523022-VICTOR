/* -------------------------------------------------------------------   
 * Disciplina: 			Estrutura de Dados				
 * Professor:			Prof. Veríssimo
 * Objetivo do Programa: 	Sistema de Atendimento - Lava-Rápido Brilho Total
 * Data:			31/08/2026
 * Autor: 			Victor Conelian
 * ------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VALOR_PREMIUM 100.0

typedef struct {
	char placa[8];
	float valor;
} Veiculo;

void exibirCabecalho(void){
	printf("=================================\n");	
	printf("LAVA - RAPIDO BRILHO TOTAL - FILA DE ATENDIMENTO\n");	
	printf("=================================\n");	
}

void preencherFrota(Veiculo *frota, int quantidade){
		for (int i = 0; i < quantidade; i++){
			printf("Placa do veiculo %d: ", i + 1);
			scanf("%7s", (frota + i)->placa);
			printf("Valor do servico (R$): ");
			scanf("%f", &(frota + i)->valor);
		}
}

void exibirFrotaRecursivo(Veiculo *frota, int indice, int quantidade){
	if (indice == quantidade){
		return;
	} else {
		printf("%d) Placa: %s | Valor: R$ %.2f\n", indice + 1, (frota + indice)->placa, (frota + indice)->valor);	
		exibirFrotaRecursivo(frota, indice + 1, quantidade);
	}
}

float calcularValorTotalRecursivo(Veiculo *frota, int indice, int quantidade){
	if (indice == quantidade){
		// caso base ou de parada
		return 0;
	} else {
		// caso recursivo
		return (frota + indice)->valor + calcularValorTotalRecursivo(frota,indice + 1,quantidade);
	}
}

int buscarVeiculoRecursivo(Veiculo *frota, int indice, int quantidade, char placa[8]){
	if (indice == quantidade){
		// caso base ou de parada
		// se o indice se equiparar com a quantidade, significa que não foi encontrado a placa
		return -1;
	} else {
		if (strcmp(frota[indice].placa, placa) == 0){
			// caso base 2 caso encontrarmos a placa na nossa frota
			return indice;
		} else {
			// passo recursivo passando para o próximo veículo
			return buscarVeiculoRecursivo(frota,indice + 1,quantidade,placa);
		}
	}
		
}

int contarPremiumRecursivo(Veiculo *frota, int indice, int quantidade){
	if (indice == quantidade){
		return 0;
	} else {
		if (frota[indice].valor >= VALOR_PREMIUM) {
			return contarPremiumRecursivo(frota,indice + 1,quantidade) + 1;
		} else {
			return contarPremiumRecursivo(frota, indice + 1, quantidade);
		}
	}
}

int main(){
	// declarando o indice
	int indice = 0;
	
	exibirCabecalho();
	
	// lendo a qtd de veiculos
	int quantidade;
	printf("Quantos veiculos serao atendidos hoje? ");
	scanf("%d", &quantidade);
	
	// vetor que armazena os enderecos de veiculos alocados dinamicamente
	Veiculo *frota = (Veiculo *) malloc(quantidade * sizeof(Veiculo));

	// validar se a alocação de memória foi bem sucedida
	if (frota == NULL){
		printf("Erro na alocação.\n");
		return 1;
	}
	
	// preencher frota
	preencherFrota(frota,quantidade);

	// exibir frota
	printf("\n--- Veiculos atendidos hoje ---\n");
	exibirFrotaRecursivo(frota,indice,quantidade);	

	// buscar pela placa
	char placaBusca[8];
	int indicePlacaBusca;

	printf("\n--- Busca recursiva por placa ---\n");
	printf("Placa a ser pesquisada: ");
	scanf("%7s", placaBusca);
	
	indicePlacaBusca = buscarVeiculoRecursivo(frota,indice,quantidade,placaBusca);

	if (indicePlacaBusca == -1){
		printf("Veiculo nao encontrado na frota.\n");
	} else {
	       	printf("Veiculo encontrado na posicao %d! Placa: %s | Valor: R$ %.2f\n", indicePlacaBusca + 1, (frota + indicePlacaBusca)->placa, (frota + indicePlacaBusca)->valor);
	}

	// resumo do dia
	printf("\n--- Resumo do dia ---\n");
	printf("Total de veiculos atendidos: %d\n", quantidade);
	printf("Servicos premium (>= %.2f): %d\n", VALOR_PREMIUM, contarPremiumRecursivo(frota,indice,quantidade));
	printf("Valor total arrecadado: R$ %.2f\n", calcularValorTotalRecursivo(frota,indice,quantidade));

	// liberacao de memoria da frota
	free(frota);
	frota = NULL;
	printf("\nMemoria da frota liberada com sucesso. Sistema encerrado.\n");

	return 0;
}
