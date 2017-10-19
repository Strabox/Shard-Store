#include "proj2.h"

/*===========================MAIN====================================*/

int main() {
    char str1;
    char word1[NUMCARACTERES], word2[NUMCARACTERES];
    int numerolinhas;
	char** text;
	
	numerolinhas = getNumberLines();	/*Obtem-se o numero de linhas do texto*/
	STinit();							/*Inicia a Arvore*/
	STHinit(HASHSIZE);					/*Inicia a Hash Tabel*/
	text = getText(numerolinhas);		/*Obtem-se o texto do Standard Input*/
	
	do {
		str1 = getchar();
		switch (str1) {
			case 's' :					/*Imprime o texto dado*/
				ImprimeTexto(text,numerolinhas);
				break;
			case 'f' :					/*Esquecer Palavra*/
				scanf("%s",word1);
				palavraMinusculas(word1);
				f(word1);
				break;
			case 'l' :					/*Imprimir as linhas em que se encontra a palavra*/
				scanf("%s",word2);
				palavraMinusculas(word1);
				if (STHsearch(word2) == NULL)
					l(word2, text);
				break;
			case 'w' :
				scanf("%s %s",word1,word2);
				if ((STHsearch(word1) == NULL) || (STHsearch(word2) == NULL))
				break;
			case 'h' :					/*Percorre-se a ADT arvore em in-order para obter as palavras por ordem alfabetica juntamente com as suas repticoes no texto*/
				traverse();
				break;
      }
	}while(str1 != EOF);
        
    return 0;
}
