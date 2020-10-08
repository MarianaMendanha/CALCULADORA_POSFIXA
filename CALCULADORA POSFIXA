#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct elemento{
    char dado[15];				/* Meu elemento passa a ser uma string, de forma a se permitir números maiores que 9 nas expressões */
    struct elemento * proximo;
}t_elemento;


typedef struct lista{
    t_elemento * primeiro;
    t_elemento * ultimo;
}t_lista;


typedef struct pilha{
    t_lista * l;
}t_pilha;

int estaVazia(t_lista *);

t_lista *criaLista(){
   t_lista * l = (t_lista *)malloc(sizeof(t_lista));
   l->primeiro = NULL;
   l->ultimo = NULL;
   return l;
}


void insereInicio(char *valor, t_lista * l){
    t_elemento * novoprimeiro = (t_elemento *)malloc(sizeof(t_elemento));
    strcpy(novoprimeiro->dado,valor);
    novoprimeiro->proximo = l->primeiro;
    l->primeiro = novoprimeiro;
    if(l->ultimo == NULL){
        l->ultimo = novoprimeiro;
    }
}

void imprimeLista(t_lista *l) {
	t_elemento *no; /* Iterador para percorrer a lista SEM ALTERÁ-LA */

	for (no = l->primeiro; no != NULL; no = no->proximo) { /* Iterando um nó - a lista não é modificada */
		printf ("%s ",no->dado); /*Imprime cada elemento da lista separado por espaços */
	}
	printf("\n");
}


void insereFinal(char *valor, t_lista * l){
   t_elemento * novoultimo = (t_elemento *)malloc(sizeof(t_elemento));
   strcpy(novoultimo->dado,valor);
   novoultimo->proximo = NULL; 
   if(l->primeiro == NULL){
      l->primeiro = novoultimo;
   }else{
     l->ultimo->proximo = novoultimo;
   }
   l->ultimo = novoultimo;
}

char *removeInicio(t_lista * l){
    if(estaVazia(l)){
        return NULL;
    }
    char *tmp = (char *) malloc(15*sizeof(char)); /* Aloca um espaço para a string tmp, de forma que eu possa retorná-la */
	strcpy(tmp,l->primeiro->dado);
    t_elemento * removido = l->primeiro;
    l->primeiro = l->primeiro->proximo;
    free(removido);
    if(l->primeiro == NULL){
       l->ultimo = NULL;
    }
    return tmp;
}



int estaVazia(t_lista * l){
    if(l->primeiro == NULL){
       return 1;
    }
    return 0;
}

t_pilha * criaPilha(){
   t_pilha * p =  (t_pilha *)malloc(sizeof(t_pilha));
   p->l = criaLista();
   return p;
}

void empilhar(char *valor,t_pilha * p){
  insereInicio(valor, p->l);
}


char *desempilhar(t_pilha * p){
  return removeInicio(p->l);
}


int estaVaziaPilha(t_pilha * p){
    return estaVazia(p->l);
}

char *topoPilha(t_pilha *p){
  char *topo_pilha = desempilhar(p);
  empilhar(topo_pilha, p);
  return topo_pilha;
}

int prioridadeOperador(char *op) {
	if (strcmp(op,"+") == 0 || strcmp(op,"-") == 0) {
		return 0;
	}
	else if (strcmp(op,"*") == 0 || strcmp(op,"/") == 0) {
		return 1;
	}
	return -1;
}

t_lista *infixaPosfixa(char expressao[],int tam) {
	char *aux = (char *) malloc(15*sizeof(char));
	int i = 0;
	int j;
	t_pilha *pilha = criaPilha();
	t_lista *posfixa = criaLista();

	while (i < tam) {
		aux[0] = expressao[i];  		/* Monta uma string auxiliar para o caso de aparecer um operador, cuja condicional será adiante */
		aux[1] = '\0';

		if (isdigit(expressao[i]) || expressao[i] == '.') { /* Se meu caractere é um dígito */
			strcpy(aux,"\0"); /* Zero minha string auxiliar, pois vou precisar dela */
			j = 0;
			while (i< tam && (isdigit(expressao[i]) || expressao[i] == '.')) { /* Este loop concatena os dígitos e ponto (para números reais) encontrados na string aux */
				aux[j] = expressao[i];
				i++;
				j++;
			}
			aux[j] = '\0'; /* aux agora contém um token numérico, que pode ser um número maior que 9 */
			insereFinal(aux,posfixa);
		}
		else if (isspace(expressao[i])) {
			i++; /* Ignora espaços */
		}
		else if (expressao[i] == '(') { /* Se é um abre parêntese */
			aux[0] = '('; /* aux agora é uma string que representa o abre parêntese: "(" */
			aux[1] = '\0';
			empilhar(aux,pilha); /* Empilha o abre parêntese */
			i++;
		}
		else if (expressao[i] == ')') {
			while (strcmp(topoPilha(pilha),"(") != 0 && !estaVaziaPilha(pilha)) { /* Evita a invasão de memória não-alocada */
				insereFinal(desempilhar(pilha),posfixa); /* Desempilho tudo e insiro na expressão posfixa enquanto não achar o abre parêntese */
			}
			desempilhar(pilha); /* Descarta o abre parentesis */
			i++;
		}
		else if (prioridadeOperador(aux) != -1) { /* Encontrei um operador: '+','-','*','/' */
			while (!estaVaziaPilha(pilha) && prioridadeOperador(topoPilha(pilha)) >= prioridadeOperador(aux)) {
				insereFinal(desempilhar(pilha),posfixa); /* Enquanto a pilha não está vazia e a prioridade do operador do topo da pilha for maior que a prioridade do operador encontrado, desempilhe e insira na expressao posfixa */
			}
			empilhar(aux,pilha); /* Por fim, empilhe o operador encontrado na pilha de operadores */
			i++;
		}
	}
	
	while (!estaVaziaPilha(pilha)) {
		insereFinal(desempilhar(pilha),posfixa); /* Ao final, desempilhe tudo o que tiver na pilha e insira na expressao */
	}

	return posfixa;
}

int ehNumero(char *token) {
	int i;
	for (i = 0; i < strlen(token); i++) {
		if (!(isdigit(token[i]) || token[i] == '.')) {
			return 0;				/* Retorno 0 por que token é uma string que não pode representar um número */
		}
	}
	return 1;					/* Retorno 1 se a string é um número */
}

double avaliaPosfixa(t_lista *expressao) {
	t_elemento *no; /* Iterador para percorrer a lista SEM ALTERÁ-LA */
	t_pilha *pilha_solucao = criaPilha(); /* Pilha que guarda a solução da expressão */
	double hold, resultado; /* Hold serve para segurar resultados temporários; result é o resultado */
	char *numeros = (char *) malloc (50*sizeof(char)); /* Aloca uma string auxiliar para guardar resultados */
	char *operando1 = (char *) malloc(15*sizeof(char)); /* Aloca string para operando */
	char *operando2 = (char *) malloc(15*sizeof(char)); /* Aloca string para operando */
	for (no = expressao->primeiro; no != NULL; no = no->proximo) { /* Varre a lista da expressao */
		if (ehNumero(no->dado)) {
			empilhar(no->dado,pilha_solucao); /* Se é um número, empilha na pilha de soluções */
		}
		else {
			operando2 = desempilhar(pilha_solucao);
			operando1 = desempilhar(pilha_solucao);
			switch (no->dado[0]) {		/* Switch com os operadores */
				case '+':
					hold = atof(operando1) + atof(operando2); /* Calcula uma soma */
					break;
				case '-':
					hold = atof(operando1) - atof(operando2); /* Calcula uma subtração */
					break;
				case '*':
					hold = atof(operando1) * atof(operando2); /* Calcula uma multiplicação */
					break;
				case '/':
					hold = atof(operando1) / atof(operando2); /* Calcula uma divisão */
					break;
				default:
					break;
			}
			sprintf(numeros,"%lf",hold); /* Transforma hold numa string e guarda em numeros */
			empilhar(numeros,pilha_solucao);
		}
	}
	free(operando1);
	free(operando2);
	free(numeros);
	resultado = atof(topoPilha(pilha_solucao)); /* Pega o resultado como o topo da pilha de soluções */
	while (!estaVaziaPilha(pilha_solucao)) {
		desempilhar(pilha_solucao);			/* Esvazia a pilha */
	}

	return resultado;
}

int valida(t_pilha * p,char expressao[]){

	int i,z=0;
	char *aux = (char *) malloc (2*sizeof(char)); /* Aloca uma string para ser auxiliar */
	
	for (i=0; expressao[i] != '\0'; i++){
	     if(!isdigit(expressao[i]) && expressao[i] != ')' && expressao[i] != '(' && expressao[i] != '-' && expressao[i] != '+' && expressao[i] != '/' && expressao[i] != '*' && expressao[i] != '.'){

	        return 0;
	     }
	     if(isdigit(expressao[i])){  
		z++;
	     }
	     if (expressao[i] == '(') {
		aux[0] = '(';						/* Monta uma string com o abre parêntese para ser empilhada */
		aux[1] = '\0';		
		empilhar(aux,p);					/* Empilha um "(" */
	     }
	     else if (expressao[i] == ')'){
		      if (estaVaziaPilha(p)) {
			  free(aux);
			  return 0;
			}
			else {
				desempilhar(p);
			}
	     }
	}
	free(aux);
	if(!estaVaziaPilha(p) || z==0){
	    return 0;
	}else return 1;
}


int main(void) {
	char expressao[200];
	t_lista *ptr;
	t_pilha *p = criaPilha();
	printf("Expressão: ");
	scanf("%[^\n]",expressao);
	if(valida(p,expressao)){		
		printf("a expressão é valida..\n");		
		ptr = infixaPosfixa(expressao,strlen(expressao));
		printf("expressão posfixa: ");
		imprimeLista(ptr);
		printf ("Resultado = %.1lf\nDONE\n",avaliaPosfixa(ptr));
	}else{
			printf("a expressão nao é valida.\nDONE\n");
	}
	return 0;
}
