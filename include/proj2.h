#include <stdio.h>
#include <stdlib.h>
#include "st.h"

#define NUMCARACTERES 1026        	/*Numero Caracteres Maximo de uma frase +1 para o \0*/
#define NUMSEP 9    		  		/*Numero de Separadores de palavras*/
#define HASHSIZE 997				/*Tamanho da Hash Tabel*/

void processa(char* palavraT, int nlinha){    						/*Funcao que insere uma palavra do texto na Arvore nao sabendo se ela la esta ou se e a 1º vez que esta a ser inserida*/
    Item no;
	
	no = (Item) malloc(sizeof(struct palavralida));
	no->palavra = (char*) malloc(sizeof(char)*(strlen(palavraT)+1));
	strcpy(no->palavra,palavraT);
	no->repeticoes = 1;
	no->numerodelinhas =1;
	no->nLinhas = malloc(sizeof(int)*(NLINHASBASE));
	no->nLinhas[0]= nlinha;
	
	STinsert(no);
	
	return;
}

char tolowers(char caracter){					/*Funcao que converte uma letra para minuscula*/
	if ((caracter>='A') && (caracter<='Z'))
		caracter = caracter + 'a'-'A';
	return caracter;
}
const char separators[] = { ' ','\t',',',';','.','?','!','"','\n' };

void split(char *line,int nlinha)				/*Funcao que vai dividindo a frase obtida em palavras e vai processando as palavras*/
{
	int i, j, k;
	char buffer[NUMCARACTERES];
	
	for(i = 0, k = 0; line[i] != '\0'; i++, k++) {
		buffer[k] = tolowers(line[i]);
		for(j = 0; j < NUMSEP; j++) {
			if(line[i] == separators[j]) {
				if(k != 0) {
					buffer[k] = '\0';					 
					processa(buffer,nlinha);
				}
				k = -1;
			}
		}
	}
}


int getNumberLines(){									/*Funcao que obtem e devolve o numero de linhas do texto que e introduzido inicialmente*/

    int letra = 0;
	int numerolinhas = 0;
	
	letra = getchar();
	while (letra != '\n'){
		numerolinhas = (numerolinhas*10) + (letra -'0');
		letra = getchar();
	}
	return numerolinhas;
}

char* getLine(){										/*Funcao que vai obtendo uma linha de cada vez e guarda num vector so do tamnanho necessario*/
	int indice;
	int caracter=0;
	char* aux;
	char Receptor[NUMCARACTERES];
	
	for(indice = 0;(caracter = getchar()) != '\n';indice++){
		Receptor[indice] = caracter;
	}
	
	Receptor[indice] = '\n';
	Receptor[++indice] = '\0'; 			
	
	aux = (char*) malloc(sizeof(char)*strlen(Receptor)+1);	/*Aloca-se unicamente o espaco necessario para frase para nao se desperdiçar memoria*/
	strcpy(aux,Receptor);

	return aux;
}

char** getText(int NumeroLinhas){							/*Funcao que obtem o Texto do Standard Input*/
	int i;
	char** textoT;  										/*Array de strings, em que cada string e uma linha completa do texto dado*/
	
	
	textoT = (char**) malloc(sizeof(char*)* NumeroLinhas);
	
	
	for(i = 0 ;i < NumeroLinhas; i++){
		
		*(textoT+i) = getLine();
		
		split(*(textoT+i),i+1);    
	}
	
	return textoT;
}


void palavraMinusculas(char palavra[]){					/*Transforma todas as letras de uma palavra para Minusculas*/	
	int i;
	
	for(i=0; palavra[i] != '\0';i++){
		palavra[i] = tolowers(palavra[i]);
	}
	
}

void l(char* palavracmp, char** text){    			/*Funcao que executa o comando L(Imprimir as Linhas em que se encontra uma palavra)*/
    int i;
	Item aux;
	
	aux = STsearch(palavracmp);

	if (aux != NULLitem){
		for( i=0; i < aux->numerodelinhas; i++){	/* Imprime-se as linhas que contem pelo menos uma vez a palavra pedida*/
			printf("%d %s", aux->nLinhas[i], *(text +aux->nLinhas[i]-1));
		}
	}
}

void f(char* palavra){										/*Funcao para o comando F (Esquecer uma palavra)*/
	char* aux;
	
	aux = (char*) malloc(sizeof(char)*(strlen(palavra)+1));
	
	strcpy(aux,palavra);
	
	STHinsert(aux);											/*Guarda na Hash Tabel a palavra esquecida*/
}

void ImprimeTexto(char** text, int NumeroLinhas){    		/*Funcao para o comando S (Mostrar o Texto Original Completo)*/
	int i;
	
	for(i = 0; i < NumeroLinhas; i++){
		printf("%s",*(text+i));
	}
}
