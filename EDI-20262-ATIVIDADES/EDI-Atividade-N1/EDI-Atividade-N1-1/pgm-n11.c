#include <stdio.h>
#define TAMANHO_TURMA 5

void exibirCabecalho(void){
	printf("=================================\n");
	printf(" SISTEMA DE NOTAS - TURMA ADS\n");
	printf("=================================\n"); 
} 

// o vetor é passado por referência pois queremos que a função acesse seus valores originais
float calcularMedia(float vetor[], int tamanho){
	float media;
	media = 0.00;

	for (int i = 0; i < tamanho; i++){
		media = media + vetor[i];
	}

	media = (float) media / (float) TAMANHO_TURMA; 
	return media;
}

void simularAjuste(float notaOriginal, float bonus){

	printf("Simulacao para o aluno 1: %.2f + %.2f = %.2f (nao aplicado ainda)", notaOriginal, bonus, notaOriginal +  bonus);
}

void aplicarBonus(float *nota, float bonus){
	*nota = *nota + bonus;	
}

int main(){
	float notas[TAMANHO_TURMA];
	float bonus, media;

	// Exibir cabecalho
	exibirCabecalho();
	
	for (int i = 0; i < TAMANHO_TURMA; i++){
		printf("Nota do aluno %d: ", i+1);
		scanf("%f", &notas[i]);
	}
	
	printf("Informe o valor do bonus a aplicar: ");
	scanf("%f", &bonus);


	// Exibir media
	printf("\n--- Media da turma antes do ajuste ---\n");

	media = calcularMedia(notas, TAMANHO_TURMA);
	printf("Media inicial: %.2f\n\n", media);
	
	// Exibir simulacao
	printf("--- Simulacao do ajuste (passagem por valor) ---\n");

	simularAjuste(notas[0], bonus);
	printf("\nNota do aluno 1 apos a simulacao (inalterada): %.2f\n", notas[0]);
	
	// Aplicar o bonus nos valores originais
	printf("\n--- Aplicacao real do bonus (passagem por referencia) ---");
	
	for (int i = 0; i < TAMANHO_TURMA; i++){
		aplicarBonus(&notas[i], bonus);
	}

	printf("\nBonus de %.2f aplicado a todas as notas da turma.", bonus);

	// Exibir notas com bonus
	printf("\n\n--- Notas finais da turma ---\n");

	for (int i = 0; i < TAMANHO_TURMA; i++){
		printf("Aluno %d: %.2f\n", i+1, notas[i]);
	}

	// Exibir media da turma apos ajuste
	printf("\n--- Media da turma apos o ajuste ---");
	printf("\nMedia final: %.2f\n", calcularMedia(notas, TAMANHO_TURMA));

	return 0;
}
