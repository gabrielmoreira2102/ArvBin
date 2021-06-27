#include <stdio.h>
#include <stdlib.h>

typedef int TIPOCHAVE;

typedef struct aux{
	TIPOCHAVE chave;
	struct aux *esq;
	struct aux *dir;
}NO;

typedef NO* PONT;

PONT inicializa(){
	return (NULL);
}

PONT insere(PONT raiz, int ch){
	if(raiz == NULL){
		PONT novoNo = (PONT)malloc(sizeof(NO));
		novoNo->esq = NULL;
		novoNo->dir = NULL;
		novoNo->chave = ch;
		return(novoNo);
	}
	else{
		if(ch < raiz->chave)
			raiz->esq = insere(raiz->esq, ch);
		else
			raiz->dir = insere(raiz->dir, ch);
		return(raiz);
	}
}

PONT busca(TIPOCHAVE ch, PONT raiz){
	if(raiz == NULL)
		return(NULL);
	if(raiz->chave == ch)
		return(raiz);
	else
		if(raiz->chave > ch)
			return(busca(ch, raiz->esq));
		else 
			return(busca(ch, raiz->dir));
	}

PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
	PONT atual = raiz;
	*pai = NULL;
	while(atual){
		if(atual->chave == ch)
			return(atual);
		*pai = atual;
		if(ch < atual->chave) 
			atual = atual->esq;
		else
			atual = atual->dir;
	}
	return(NULL);
}

PONT removeNo(PONT raiz, TIPOCHAVE ch){
	PONT pai, no, p, q;
	no = buscaNo(raiz, ch, &pai);
	if(no == NULL){
		return(raiz);
	if(!no->esq || !no->dir){
		if(!no->esq)
			q = no->dir;
		else
			q = no->esq;
		}
	}
	else{
		p = no;
		q = no->esq;
		while(q->dir){
			p = q;
			q = q->dir;
		}
		if(p != no){
			p->dir = q->esq;
			q->esq = no->esq;
		}
		q->dir = no->dir;
	}
	if(!pai){
		free(no);
		return(q);
	}
	if(ch < pai->chave)
		pai->esq = q;
	else
		pai->dir = q;
	free(no);
	return(raiz);
}

void imprime(PONT raiz){
	if(raiz != NULL){
		printf("%d", raiz->chave);
		printf("(");
	 	imprime(raiz->esq);
		imprime(raiz->dir);
		printf(")");
	}
}

int main(){
	
	PONT raiz = NULL;
	int opcao, valor;
	
	do{
		printf("\n\t***** MENU *****");
		printf("\n\t1 - Inserir valores");
		printf("\n\t2 - Remover valores");
		printf("\n\t3 - Busca valores");
		printf("\n\t4 - Imprimir valores");
		printf("\n\t0 - Sair");
		printf("\nDigite uma opcao: ");
		scanf("%d", &opcao);
		
		switch(opcao){
		case 1:
			printf("\n\tDigite um valor a ser inserido: ");
			scanf("%d", &valor);
			raiz = insere(raiz, valor);
			break;
		case 2:
			printf("\n\tDigite um valor a ser removido: ");
			scanf("%d", &valor);
			raiz = removeNo(raiz, valor);
			break;
		case 3:
			printf("\n\tQual valor você deseja buscar? ");
			scanf("%d", &valor);
			printf("\n\tValor encontrado: %d\n", valor);
			break;
		case 4:
			printf("\n\tImpressao da arvore binaria: \n");
			imprime(raiz);
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