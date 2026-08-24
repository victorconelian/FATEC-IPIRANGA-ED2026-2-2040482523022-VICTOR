#include <stdio.h>
#define TAMANHO_ESTOQUE 5
#define ESTOQUE_MINIMO 10

// vetor global
int estoque[TAMANHO_ESTOQUE];

void exibirCabecalho(void){
	printf("=================================\n");
	printf("SISTEMA DE ESTOQUE - LOJA CONSTRUMAIS\n");
	printf("=================================\n"); 
}

void preencherEstoque(void){
	int *p = estoque;
	for (int i = 0; i < TAMANHO_ESTOQUE; i++){
		printf("Quantidade do produto %d: ", i+1);
		scanf("%d", p + i);
	}
}

void exibirEstoque(int momento){
	int *p = estoque;

	switch (momento){
		case 0:
			printf("\n–- Estoque atual (antes da reposicao) –-\n");
			break;
		case 1:
			printf("\n–- Estoque final (apos reposicao) –-\n");
			break;
	}
	
	for (int i = 0; i < TAMANHO_ESTOQUE; i++){
		printf("Produto %d: %d unidades\n", i + 1, *(p + i));
	}
}

float calcularMediaEstoque(void){
	// p + i - endereço de memória somado à unidade 'i' que desloca esse endereço para o próximo
	// *(p + i) - pega o valor armazenado no resultado do endereço de memória = (p + i)
	
	int *p = estoque, soma;
	float media;

	soma = 0;

	for (int i = 0; i < TAMANHO_ESTOQUE; i++){
		soma = soma + *(p + i);
	}
	
	media = soma / (float)TAMANHO_ESTOQUE;

	return media;
}

void simularReposicao(int quantidadeAtual, int reposicao){
	printf("\n–- Simulacao de reposicao (passagem por valor) –-\n");
	printf("Simulacao para o produto 1: %d + %d = %d (nao aplicado ainda)\n", quantidadeAtual, reposicao, quantidadeAtual + reposicao);
}

void aplicarReposicaoGeral(int reposicao){
	int *p = estoque;
	for (int i = 0; i < TAMANHO_ESTOQUE; i++){
		*(p + i) = *(p + i) + reposicao; 
	}
}

void identificarEstoqueCritico(int minimo){
	int *p = estoque;
	int validador = 0;
	
	printf("\n–- Analise de estoque critico (minimo = %d unidades) –-\n", minimo);
	for (int i = 0; i < TAMANHO_ESTOQUE; i++){
		if ( *(p + i) < minimo){
			printf("Produto %d esta em nivel critico: %d unidades (abaixo do minimo)\n", i + 1, *(p + i));
			validador = 1;
		}
	}

	if (validador == 0) printf("Estoque esta regularizado\n");
}

int main(){
	int reposicao;

	exibirCabecalho();	
	
	preencherEstoque();
	printf("Quantidade de reposicao a aplicar: ");
	scanf("%d", &reposicao);
	
	exibirEstoque(0);
	
	simularReposicao(estoque[0],reposicao);
	printf("Quantidade do produto 1 apos a simulacao (inalterada): %d\n", estoque[0]);
	
	printf("\n–- Aplicacao real da reposicao (ponteiro interno ao vetor global) –-\n");
	aplicarReposicaoGeral(reposicao);
	printf("Reposicao de %d unidades aplicada a todos os produtos do estoque.\n", reposicao);

	exibirEstoque(1);
	
	float media = calcularMediaEstoque();
	printf("\n–- Media geral do estoque –-\n");
	printf("Media final: %.2f unidades\n", media);

	identificarEstoqueCritico(10);
	
	return 0;
}
