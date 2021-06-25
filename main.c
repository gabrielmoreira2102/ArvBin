#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int valor;
	int conteudo;
	int chave;
	struct no *direita;
	struct no *esquerda;
}NoArv;

NoArv* inserir(NoArv *raiz, int num){
	if (raiz == NULL){
		NoArv *aux = malloc(sizeof(NoArv));
		aux->valor = num;
		aux->esquerda = NULL;
		aux->direita = NULL;
		return aux;		
	}
	else{
		if(num < raiz->valor)
			raiz->esquerda = inserir(raiz->esquerda, num);
		else
			raiz->direita = inserir(raiz->direita, num);
		return raiz;
	}
}

NoArv* remover(NoArv *raiz, int chave){
	if(raiz == NULL){
		printf("Valor nao encontrado!\n");
		return NULL;
	}
	else{
		if(raiz->conteudo == chave){
			//remove nós folhas (nós sem filhos)
			if(raiz->esquerda == NULL && raiz->direita == NULL){
				free(raiz);
				return NULL;
			}
			else{
				//remove nós que possuem apenas 1 filho
				if(raiz->esquerda == NULL || raiz->direita == NULL){
					NoArv *aux;
					if(raiz->esquerda != NULL)
						aux = raiz->esquerda;
					else
						aux = raiz->direita;
					free(raiz);
					return aux;
				}
				else{
					//remove nós que possuem 2 filhos
					NoArv *aux = raiz->esquerda;
					while(aux->direita != NULL)
						aux = aux->direita;
					raiz->conteudo = aux->conteudo;
					aux->conteudo = chave;
					raiz->esquerda = remover(raiz->esquerda, chave);
					return raiz;
				}
			}
		
		}
		else{
			if(chave < raiz->conteudo)
				raiz->esquerda = remover(raiz->esquerda, chave);
			else
				raiz->direita = remover(raiz->direita, chave);
			return raiz;
		}
	}
}

void imprimir(NoArv *raiz){
	if(raiz){
		printf("\n\t\t%d", raiz->valor);
		imprimir(raiz->esquerda);
		imprimir(raiz->direita);
	}
}
	
int main(){
	
	NoArv * raiz = NULL;
	int opcao, valor;
	
	do{
		printf("\n\t***** MENU *****");
		printf("\n\t1 - Inserir valores");
		printf("\n\t2 - Remover valores");
		printf("\n\t3 - Imprimir valores");
		printf("\n\t0 - Sair");
		printf("\nDigite uma opcao: ");
		scanf("%d", &opcao);
		
		switch(opcao){
		case 1:
			printf("\n\tDigite um valor: ");
			scanf("%d", &valor);
			raiz = inserir(raiz, valor);
			break;
		case 2:
			printf("\n\tDigite um valor a ser removido: ");
			scanf("%d", &valor);
			raiz = remover(raiz, valor);
			break;
		case 3:
			printf("\n\tImprimir: \n");
			imprimir(raiz);
			printf("\n");			
			break;
		case 0:
			printf("\n\tSistema encerrado!");
			break;		
		default:
			if(opcao != 0)
				printf("\n\tOpcao invalida!!\n");
		}
	}
	while(opcao != 0);
	
	return 0;
		
}