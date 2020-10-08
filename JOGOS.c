/**      @file: 160136784.c
 *     @author: Mariana Mendanha da Cruz
 * @disciplina: Algoritmos e Programação de Computadoresn - APC
 *                                                                                                            
 *   
 *   */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define _GNU_SOURCE 

#define TAM 8
#define TRUE 1
#define FALSE 0 
#define cls() system("clear || cls")


typedef struct{

	char nick[50];
	int pontos;

}PLAYER;


/*FUNÇÃO INTERFACE INICIAL E OPÇÕES DE JOGO:*/
int menu();

const char *readLine(FILE *file);
/*int RANKING(int pontuacao_total);
int verificar_jogador(char jogador[50]);*/

/*FUNÇÕES JOGO:*/
void senha(PLAYER melhores_senha[11]);
void charada(PLAYER melhores_charadas[11]);
void ppt(PLAYER melhores_ppt[11]);
void campo_minado(PLAYER melhores_minas[11]);
void rodaroda(PLAYER melhores_roda[11]);

/*FUNÇÕES AUXILIARES:*/
void limpar_tela();
void limpar_tela2();
void tela_inicial();
void VIDAS(int vidas);
void historia_ppt();
void terreno_escondido(char minas[TAM][TAM]);
void terreno_visivel(char terreno[TAM][TAM]);
void escreve_terreno_escondido(char minas[TAM][TAM]);
void escreve_terreno_visivel(char terreno[TAM][TAM]);
int procura_minas(char minas[TAM][TAM], int linha, int coluna);
void conta_minas(char terreno[TAM][TAM], char minas[TAM][TAM], int linha, int coluna);
int ganhou(char terreno[TAM][TAM], char minas[TAM][TAM]); 
void propaganda(int sec);
void PLAY(int P1, int P2);
int CHUTE_DEUSA(char P);
int CHUTE(char vetor_categoria[10][31], int numeros[3]);
int usleep();
int compara_players();



int menu(){

	int NUM_JOGO;


	printf("\t\t●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●● \n");
	printf("\t\t● O ESPETACULAR GRANDE JOGO DA VIDA ● \n");
	printf("\t\t●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●● \n\n");

	printf("MENU:\n");
	printf("(1)SENHA\n");
	printf("(2)CHARADAS\n");
	printf("(3)PEDRA/PAPEL/TESOURA\n");
	printf("(4)MINAS\n");
	printf("(5)RODA A RODA\n");
	printf("(6)RANKING\n");
	printf("(7)SAIR & SALVAR\n");

	printf("\t            __________________________________\n");
	printf("\t     [0,0] < OLÁ, DIGITE O NÚMERO DA SUA OPÇÃO)\n");
	printf("\t     |)__)\n");
	printf("\t     -”-”-\n");

	scanf("%d", &NUM_JOGO);
	getchar();

	return NUM_JOGO;
}


int main(){

	PLAYER jogador_atual;
	int TERMINO = FALSE;

	PLAYER melhores_senha[11] = {    

		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0}
	};

	PLAYER melhores_charadas[11] = {

		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0}
	};

	PLAYER melhores_ppt[11] = {

		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0}
	};

	PLAYER melhores_minas[11] = {

		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0}
	};

	PLAYER melhores_roda[11] = {
		
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0}
	};

	PLAYER melhores_total[11] = {
		
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0},
		{"",0}
	};

	/*PLAYER *melhores_pontuacoes[] = {melhores_senha, melhores_charadas, melhores_ppt, melhores_minas, melhores_roda}; declarou ponteiro para melhores pontuações com o tipo "nome + pontos" */

	/* declarou jogador atual com o tipo "nome + pontos" */

	PLAYER jogador_comp[66];
	int v;

	char asteriscos[101];
	const char TXT_FILE[] = "RANK_JOGO.txt";

	FILE *arquivo;

	memset(asteriscos,'*',sizeof(asteriscos));/* função verifica a quantidade de caracteres de um string e para cada um escrve um caractere específico num vetor */
	asteriscos[100] = '\0';

	char * line = NULL;
    size_t len = 0;
    ssize_t read;

	cls();

	

	qsort(melhores_senha, 11, sizeof(PLAYER), compara_players);/* função organiza em ordem decrescente os melhores do senha*/
	qsort(melhores_charadas, 11, sizeof(PLAYER), compara_players);
	qsort(melhores_ppt, 11, sizeof(PLAYER), compara_players);
	qsort(melhores_minas, 11, sizeof(PLAYER), compara_players);
	qsort(melhores_roda, 11, sizeof(PLAYER), compara_players);
	qsort(melhores_total, 11, sizeof(PLAYER), compara_players);

	
	arquivo = fopen(TXT_FILE,"rt+");/* abre arquivo em formato de read */
	
	if(!arquivo){ 

		printf("Ranks não puderam ser carregados. O arquivo não foi aberto. Aperte <ENTER> para voltar...");
		while (getchar() != '\n');

	}

	else{

		fread(&melhores_senha,8,sizeof(PLAYER),arquivo);/* lê a pontuação do senha(carrega da anterior) */
		fread(&melhores_charadas,8,sizeof(PLAYER),arquivo);
		fread(&melhores_ppt,8,sizeof(PLAYER),arquivo);
		fread(&melhores_minas,8,sizeof(PLAYER),arquivo);
		fread(&melhores_roda,8,sizeof(PLAYER),arquivo);
		fread(&melhores_total,8,sizeof(PLAYER),arquivo);
		fclose(arquivo);


	
	}

	arquivo = fopen(TXT_FILE,"wt+"); /* tentativa falha de copiar um arquivo*/
	
	if(!arquivo){ 

		printf("Ranks não puderam ser carregados. O arquivo não foi aberto. Aperte <ENTER> para voltar...");
		while (getchar() != '\n');

	}

	else{
		
			fscanf(arquivo, "%s %d", jogador_comp->nick, &jogador_comp->pontos);
		
		
		
		fclose(arquivo);
	
	}




	do{
					
		printf("\nEscreva seu NICK\n\t>> ");
		v = scanf("%[^\n]",jogador_atual.nick);
		/*
		for(i = 0; i < 60; ++i){
			
			printf("%s   ", jogador_comp[i]);
			
			printf("\n");
		}
		getchar();
		while (getchar() != '\n');*/

		strcpy(melhores_senha[10].nick, jogador_atual.nick);
		strcpy(melhores_charadas[10].nick, jogador_atual.nick);
		strcpy(melhores_ppt[10].nick, jogador_atual.nick);
		strcpy(melhores_minas[10].nick, jogador_atual.nick);
		strcpy(melhores_roda[10].nick, jogador_atual.nick);
		strcpy(melhores_total[10].nick, jogador_atual.nick);

		if(v != 1){

			while (getchar() != '\n');
			cls();
			printf("Esse nick não foi aceito\n\n");

		}

		

	    arquivo = fopen(TXT_FILE, "r");
	    if (arquivo == NULL)
	        exit(EXIT_FAILURE);

	    while ((read = getline(&line, &len, arquivo)) != -1) {
	        printf("Retrieved line of length %zu :\n", read);
	        printf("%s", line);
	    }

	    fclose(arquivo);
	    if (line)
	        free(line);
	    exit(EXIT_SUCCESS);
			

	}while(v != 1);

	while(TERMINO == FALSE){



		cls();


		switch(menu()){

			case 1 : 
					 system("clear");
					 printf("(￣^￣)ゞ  Seu comando é uma ordem!\n\n");
					 senha(melhores_senha);
		             break;

		    case 2 : 
		    		 system("clear");
					 printf("(￣^￣)ゞ  Seu comando é uma ordem!\n\n");
		    		 charada(melhores_charadas);
		             break;

		    case 3 : 
					 system("clear");
					 printf("(￣^￣)ゞ  Seu comando é uma ordem!\n\n");
					 ppt(melhores_ppt);
		             break;

			case 4 : 
					 system("clear");
					 printf("(￣^￣)ゞ  Seu comando é uma ordem!\n\n");
					 campo_minado(melhores_minas);
					 break;

			case 5 : 
					 system("clear");
					 printf("(￣^￣)ゞ  Seu comando é uma ordem!\n\n");
					 rodaroda(melhores_roda);
					 break;

			case 6 : 
					 system("clear");
					 printf("\n\t\t\t\t(￣^￣)ゞ  Seu comando é uma ordem!\n\n");
					 sleep(1);
					 cls();
					 
					 printf("+--------------------------------------+ +--------------------------------------+\n");
					 printf("|                SENHA                 | |               CHARADA                |\n");
					 printf("+--------------------------------------+ +--------------------------------------|\n");
					 printf("|       NICK       |      PONTUÇÃO     | |       NICK       |      PONTUÇÃO     |\n");
					 printf("+--------------------------------------+ +--------------------------------------|\n");

					 for(v = 0; v < 10; v++){

						printf("| %-15.15s  |     %10d    | ", melhores_senha[v].nick, melhores_senha[v].pontos);
						printf("| %-15.15s  |     %10d    |\n", melhores_charadas[v].nick, melhores_charadas[v].pontos);
						printf("+--------------------------------------+ +--------------------------------------|\n");
					
					 }
					
					 printf("\n\n\t\t\t   APERTE <ENTER> PARA VER MAIS");
					 while(getchar()!='\n');
					
					 cls();

					 printf("+--------------------------------------+ +--------------------------------------+\n");
					 printf("|                 PPT                  | |                MINAS                 |\n");
					 printf("+--------------------------------------+ +--------------------------------------|\n");
					 printf("|       NICK       |      PONTUÇÃO     | |       NICK       |      PONTUÇÃO     |\n");
					 printf("+--------------------------------------+ +--------------------------------------|\n");

					 for(v = 0; v < 10; v++){
	 
						printf("| %-15.15s  |     %10d    | ", melhores_ppt[v].nick, melhores_ppt[v].pontos); /* %-num.nums */
						printf("| %-15.15s  |     %10d    |\n", melhores_minas[v].nick, melhores_minas[v].pontos);
						printf("+--------------------------------------+ +--------------------------------------|\n");

					 }


					 printf("\n\n\t\t\t   APERTE <ENTER> PARA VER MAIS");
					 while(getchar()!='\n');

					 cls();
					
					
					printf("+--------------------------------------+ +--------------------------------------+\n");
					printf("|              RODA RODA               | |                GERAL                 |\n");
					printf("+--------------------------------------+ +--------------------------------------|\n");
					printf("|       NICK       |      PONTUÇÃO     | |       NICK       |      PONTUÇÃO     |\n");
					printf("+--------------------------------------+ +--------------------------------------|\n");

					for(v = 0; v < 10; v++){

						printf("| %-15.15s  |     %10d    | ", melhores_roda[v].nick, melhores_roda[v].pontos);
						printf("| %-15.15s  |     %10d    |\n", melhores_total[v].nick, melhores_total[v].pontos);
						printf("+--------------------------------------+ +--------------------------------------|\n");

					}


					 printf("\n\n\tAPERTE <ENTER> PARA VOLTAR");

					 while(getchar()!='\n');
					 cls();

					 break;
				
			case 7 : 
					 system("clear");
					 printf("\n\t\t\t(￣^￣)ゞ  Seu comando é uma ordem!\n\n");

					 melhores_total[10].pontos = melhores_senha[10].pontos + melhores_charadas[10].pontos + melhores_ppt[10].pontos + melhores_minas[10].pontos + melhores_roda[10].pontos + melhores_roda[10].pontos;

					 arquivo = fopen(TXT_FILE,"wt+");/* abre arquivo em formato de write */

					 if(!arquivo){

						printf("Ranks não puderam ser salvos. O arquivo não foi aberto.");
					
					 }

					 else{

						qsort(melhores_senha, 11, sizeof(PLAYER), compara_players);/* função organiza em ordem decrescente os melhores do senha*/
						qsort(melhores_charadas, 11, sizeof(PLAYER), compara_players);
						qsort(melhores_ppt, 11, sizeof(PLAYER), compara_players);
						qsort(melhores_minas, 11, sizeof(PLAYER), compara_players);
						qsort(melhores_roda, 11, sizeof(PLAYER), compara_players);
						qsort(melhores_total, 11, sizeof(PLAYER), compara_players);


						fwrite(&melhores_senha, 8, sizeof(PLAYER), arquivo);/* escreve no arquivo a pontuação do easy */
						fwrite(&melhores_charadas, 8, sizeof(PLAYER), arquivo);
						fwrite(&melhores_ppt, 8, sizeof(PLAYER), arquivo);
						fwrite(&melhores_minas, 8, sizeof(PLAYER), arquivo);
						fwrite(&melhores_roda, 8, sizeof(PLAYER), arquivo);
						fwrite(&melhores_total, 8, sizeof(PLAYER), arquivo);
						fclose(arquivo);
						printf("\n\t\t\t  RANKS FORAM SALVOS COM SUCESSO \n");

					 }

					 sleep(1);
					 return 0; 				  		 		  

		    default :
		    		 system("clear");
		             break;
		}
	}


return 0;	
}


void senha(PLAYER melhores_senha[11]){

	srand(time(NULL));

	int senha_correta = 10 /*abs(rand() % 100001)*/;
	int tentativa = 0;
	int contador = 0;
	char enter;

	printf("\t\t◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎\n");
	printf("\t\t◎┬┴┬┴┬┴┬┴┬┴┬┴┬┴┤SENHA├┬┴┬┴┬┴┬┴┬┴┬┴┬┴◎\n");
	printf("\t\t◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎\n\n");

	printf("Bem-vindo ao senha,\n");
	printf("O jogo é simples, você só precisa encontrar a senha correta, que é um número entre 0 e 100.000 .\n");
	printf("-PARA VOLTAR AO MENU DIGITE UM NÚMERO NEGATIVO-\n");
	printf("Qual é o seu primeiro palpite?\n\n");

	do{

	    fflush(stdin);

	    if (scanf("%d", &tentativa) == 1){

	 		if(tentativa > 100000){
	 			printf("Querido, a senha é um número entre 0 e 100.000, assim você não vai acertar nunca.\n\n");
	 		}

	 		if(tentativa < 0){
	 			printf("\tＵＴｪＴＵ <A senha era: %d, mas por que você desistiu de mim?)\n\n", senha_correta);
	 			printf("\tVocê desistiu na tentativa %d. Com a penalidade de 100 tentativas.\n\n", contador+100);
	 			printf("\n\t\tPressione <ENTER> para voltar ao MENU.");
	    		fflush(stdin);
	    		fflush(stdout);
	    		scanf("%c", &enter);
	    		while(getchar() != '\n');
	 			system("clear");
	 			return;
	 		}

			if(tentativa >= senha_correta - 99999 && tentativa < senha_correta - 77777){
				printf("LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE, bem longe, péssimo chute, tenta na próxima, é um número bem maior\n\n");
			}

			if(tentativa >= senha_correta - 77777 && tentativa < senha_correta - 50000){	
				printf("MIGO, VOCÊ ESTÁ TÃO LONGE DA SENHA CORRETA, NEM IRIA TE DIZER SE É UM NÚMERO MAIOR OU MENOR QUE %d, VOCÊ NÃO MERECE, MAS EU SOU LEGAL, A SENHA É MAIOR QUE %d.\n\n", tentativa, tentativa);
			}

			if(tentativa >= senha_correta - 50000 && tentativa < senha_correta - 10000){
				printf("LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE, a senha é maior que %d\n\n", tentativa);
			}

			if(tentativa >= senha_correta - 10000 && tentativa < senha_correta - 1000){
				printf("Está começando a chegar perto, se esforce mais, a senha é maior que %d\n\n", tentativa);
			}

			if(tentativa >= senha_correta - 1000 && tentativa < senha_correta - 500){
				printf("Está morno a senha é maior que %d\n\n", tentativa);
			}

			if(tentativa >= senha_correta - 500 && tentativa < senha_correta - 100){
				printf("Está ficando quente... A senha é maior que %d\n\n", tentativa);
			}

			if(tentativa >= senha_correta - 100 && tentativa < senha_correta - 50){
				printf("MININU, ta quase, ta quase, a senha é maior que %d\n\n", tentativa);
			}

			if(tentativa >= senha_correta - 50 && tentativa < senha_correta - 5){
				printf("AAAAAAAAAAAAAh DANADO(A), TÁ PERTO EIN, a senha é maiorzinha que %d\n\n", tentativa);
			}

			if(tentativa >= senha_correta - 5 && tentativa < senha_correta){
				printf("Se você não acertar agora, eu nao sei quem vai, a senha é maior que %d\n\n", tentativa);
			}

			if(tentativa <= senha_correta + 5 && tentativa > senha_correta){
				printf("Se você não acertar agora, eu nao sei quem vai, a senha é menor que %d\n\n", tentativa);
			}

			if(tentativa <= senha_correta + 50 && tentativa > senha_correta + 5){
				printf("AAAAAAAAAAAAAh DANADO(A), TÁ PERTO EIN, a senha é menorzinha que %d\n\n", tentativa);
			}

			if(tentativa <= senha_correta + 100 && tentativa > senha_correta + 50){
				printf("MININU, ta quase, ta quase, a senha é menor que %d\n\n", tentativa);
			}

			if(tentativa <= senha_correta + 500 && tentativa > senha_correta + 100){
				printf("Está ficando quente... A senha é menor que %d\n\n", tentativa);
			}

			if(tentativa <= senha_correta + 1000 && tentativa > senha_correta + 500){
				printf("Está morno a senha é menor que %d\n\n", tentativa);
			}

			if(tentativa <= senha_correta + 10000 && tentativa > senha_correta + 1000){
				printf("Está começando a chegar perto, se esforce mais, a senha é menor que %d\n\n", tentativa);
			}

			if(tentativa <= senha_correta + 50000 && tentativa > senha_correta + 10000){
				printf("LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE, a senha é menor que %d\n\n", tentativa);
			}

			if(tentativa <= senha_correta + 77777 && tentativa > senha_correta + 50000){
				printf("MIGO, VOCÊ ESTÁ TÃO LONGE DA SENHA CORRETA, NEM IRIA TE DIZER SE É UM NÚMERO MAIOR OU MENOR QUE %d, VOCÊ NÃO MERECE, MAS EU SOU LEGAL, A SENHA É MENOR QUE %d.\n\n", tentativa, tentativa);
			}

			if(tentativa <= senha_correta + 99999 && tentativa > senha_correta + 77777){
				printf("LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE LONGE, bem longe, péssimo chute, tenta na próxima, é um número bem menor\n\n");
			}

			++contador;

	    }else{

	    	printf("Você está querendo me mandar alguma mensagem? O que você digitou não vai contar como uma tentativa, Eu não vou ler isso daí não, digite um número.\n\n");
	    	fflush(stdin);
	    	tentativa = getchar();
	    	fflush(stdin);

	    	while(scanf("%d", &tentativa) == 0){
	    		fflush(stdin);
	    		getchar();
	    		fflush(stdin);
	    	}
	    	printf("OBRIGADA POR DIGITAR UM NÚMERO, ISSO MOSTRA QUE VOCÊ NÃO É ESTÚPIDO, AGORA DIGITE SEU PALPITE: ");

	    }

	}while(senha_correta != tentativa);
	
	printf("\t          _______\n");
	printf("\t\\(^ヮ^)/ < YAY!!!)\n\n\n");


	if(contador == 1){ 
		printf(" (╯°□ °）╯︵ ┻━┻  Já pensou em jogar na loteria? Se não, está na hora de começar a jogar. \n\n");
		melhores_senha[10].pontos += 100000000;
	}

    if(contador == 2){ 
    	printf("Tem algo de muito errado com você, como coseguiu acertar em 2 jogadas?\n\n");
    	melhores_senha[10].pontos += 50000000;
    }

	if(contador == 3){  
		printf("Você é muito sortudo, acertou em apenas 3 tentativas.\n\n");
		melhores_senha[10].pontos += 10000000;
    }

	if(contador == 4){  
		printf("Palmas para você, nem acredito que acertou em 4 tentativas.\n\n");
		melhores_senha[10].pontos += 5000000;
    }   

    if(contador == 5){
    	printf("5 tentativas? É sério isso? Parabéns.\n\n");
    	melhores_senha[10].pontos += 1000000;
    }

    if(contador > 5 && contador <= 15){
    	printf("Parabéns, acertou em apenas %d tentativas.\n\n", contador);
    	melhores_senha[10].pontos += 1000;
    }

    if(contador > 15 && contador <= 25){
    	printf("Você acertou em %d tentativas.\n\n", contador);
    	melhores_senha[10].pontos += 100;
    } 

    if(contador > 25 && contador <= 30){
    	printf("Você é meio ruim nesse jogo, alguém ja te disse isso? Acertou a senha em %d tentativas\n\n", contador);
    	melhores_senha[10].pontos += 50;
    }         

    if(contador > 30 && contador <= 40){
    	printf("┻━┻ ︵ヽ(º□ º)ﾉ︵ ┻━┻ Você é muito ruim. %d tentativas? sério?\n\n", contador);
    	melhores_senha[10].pontos += 10;
    }

    if(contador > 40){
    	printf("Acho que você deveria se aposentar desse jogo. Fez %d tentativas.\n\n", contador);
    	melhores_senha[10].pontos += 5;
	}		                                              
    

    printf("\n\t\tPressione <ENTER> para voltar ao MENU");
    fflush(stdin);
    fflush(stdout);
    scanf("%c", &enter);
    while(getchar() != '\n');

    system("clear");


}


void charada(PLAYER melhores_charadas[11]){

	int perguntas = 0;
	int resposta;
	int vidas = 2;

	printf("\t\t◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉ \n");
    printf("\t\t◉✧✧✧✧✧✧✧✧✧✧✧✧✧✧✧CHARADA✧✧✧✧✧✧✧✧✧✧✧✧✧✧✧◉ \n");                                                                                                                    
 	printf("\t\t◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉ \n\n");

 	printf("Bem-vindo ao charada,\n");
	printf("O jogo é simples, você só precisa responder as perguntas corretamente, senão, perde vidas. Você começa com 2 vidas, caso o número de vidas chegue a zero, o jogo termina.\n");
	printf("-PARA VOLTAR AO MENU DIGITE UM NÚMERO NEGATIVO-\n\n");

	do{
 		
		if(perguntas == 0){
			printf("( ￣▽￣)/ <Três gatos comem três ratos em três minutos. Cem gatos comem cem ratos em quanto tempo?)\n\n");
			
			VIDAS(vidas);
					
			printf("(1)1 MINUTO\n");
			printf("(2)100 MINUTOS\n");
			printf("(3)180 SEGUNDOS\n");
			printf("(4)3 SEGUNDOS\n\n");
			printf("RESPOSTA:");

			scanf("%d", &resposta);

			switch(resposta){
				case 1 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (3): 180 SEGUNDOS É IGUAL A 3 MINUTOS\n");
						limpar_tela();						
						break;

				case 2 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (3): 180 SEGUNDOS É IGUAL A 3 MINUTOS\n");
						limpar_tela();
						break;

				case 3 :
						printf("ACERTOU!!!\n");
						printf("180 SEGUNDOS É IGUAL A 3 MINUTOS\n");
						melhores_charadas[10].pontos += 100;
						limpar_tela();
						break;

				case 4 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (3): 180 SEGUNDOS É IGUAL A 3 MINUTOS\n");
						limpar_tela();
						break;

				default :
						perguntas--;
						sleep(1);
						limpar_tela();
						printf("ESSA NÃO É UMA OPÇÃO\n");
						tela_inicial();
						break;
		    }
	    }


	    if(perguntas == 1){
			tela_inicial();
			printf("(〜￣▽￣)〜 <O pai do padre é filho do meu pai. O que eu sou do Padre?)\n\n");

			VIDAS(vidas);
					
			printf("(1)TIO\n");
			printf("(2)AVÔ\n");
			printf("(3)SOBRINHO\n");
			printf("(4)NENHUMA DAS ANTERIORES\n\n");
			printf("RESPOSTA:");

			scanf("%d", &resposta);

			switch(resposta){
				case 1 :
						printf("ACERTOU!!!\n");
						printf("A RESPOSTA CORRETA É A (1): TIO\n");
						melhores_charadas[10].pontos += 100;
						limpar_tela();
						break;

				case 2 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (1): TIO\n");
						limpar_tela();
						break;

				case 3 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (1): TIO\n");
						limpar_tela();
						break;

				case 4 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (1): TIO\n");
						limpar_tela();
						break;
						


				default :
						perguntas--;
						limpar_tela();
						printf("ESSA NÃO É UMA OPÇÃO\n");
						tela_inicial();
						break;
		    }
	    }


	    if(perguntas == 2){
			tela_inicial();
			printf("ヽ( ﾟ〇ﾟ)ﾉ <Um avião lotado de passageiros parte do Rio de Janeiro em direção a Buenos Aires. Por uma fatalidade cai na fronteira Brasil-Argentina. Onde serão enterrados os sobreviventes?)\n\n");
			
			VIDAS(vidas);

			printf("(1)BRASIL\n");
			printf("(2)ARGENTINA\n");
			printf("(3)DEPENDE DA NACIONALIDADE DOS PASSAGEIROS\n");
			printf("(4)NENHUMA DAS ANTERIORES\n\n");
			printf("RESPOSTA:");

			scanf("%d", &resposta);

			switch(resposta){
				case 1 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (4): OS SOBREVIVENTES NÃO SERÃO ENTERRADOS\n");
						limpar_tela();
						break;

				case 2 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (4): OS SOBREVIVENTES NÃO SERÃO ENTERRADOS\n");
						limpar_tela();
						break;

				case 3 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (4): OS SOBREVIVENTES NÃO SERÃO ENTERRADOS\n");
						limpar_tela();
						break;

				case 4 :
						printf("ACERTOU!!!\n");
						printf("A RESPOSTA CORRETA É A (4): OS SOBREVIVENTES NÃO SERÃO ENTERRADOS\n");
						melhores_charadas[10].pontos += 100;
						limpar_tela();
						break;

				default :
						perguntas--;
						limpar_tela();
						printf("ESSA NÃO É UMA OPÇÃO\n");
						tela_inicial();
						break;
		    }
	    }


	    if(perguntas == 3){
			tela_inicial();
			printf("<( ￣ ︶ ￣)> <Em uma sala há 100 pessoas, 99%% são homens. Quantos homens devem sair da sala para que a porcentagem de homens na sala passe a ser 98%%?)\n\n");
			
			VIDAS(vidas);

			printf("(1)2 HOMENS\n");
			printf("(2)ESSA PERGUNTA É IMPOSSÍVEL DE SER RESPONDIDA\n");
			printf("(3)50 HOMENS\n");
			printf("(4)1 HOMEM\n\n");
			printf("RESPOSTA:");

			scanf("%d", &resposta);

			switch(resposta){
				case 1 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (3): Em 100 pessoas, 99 são homens, presume-se que haja 1 mulher, desta forma, para que haja 98%% de homens, seria necessário haver 98 homens e 2 mulheres… Como não podemos alterar o número de mulheres, teriamos que manter a proporção de 98:2 ou simplificando, 49:1. Isto leva a concluir que se temos 99 homens e precisariamos ter 49, teriamos que retirar 50 homens para diminuir 1%% \n");
						limpar_tela();
						break;

				case 2 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (3): Em 100 pessoas, 99 são homens, presume-se que haja 1 mulher, desta forma, para que haja 98%% de homens, seria necessário haver 98 homens e 2 mulheres… Como não podemos alterar o número de mulheres, teriamos que manter a proporção de 98:2 ou simplificando, 49:1. Isto leva a concluir que se temos 99 homens e precisariamos ter 49, teriamos que retirar 50 homens para diminuir 1%% \n");
						limpar_tela();
						break;

				case 3 :
						printf("ACERTOU!!!\n");
						printf("A RESPOSTA CORRETA É A (3): Em 100 pessoas, 99 são homens, presume-se que haja 1 mulher, desta forma, para que haja 98%% de homens, seria necessário haver 98 homens e 2 mulheres… Como não podemos alterar o número de mulheres, teriamos que manter a proporção de 98:2 ou simplificando, 49:1. Isto leva a concluir que se temos 99 homens e precisariamos ter 49, teriamos que retirar 50 homens para diminuir 1%% \n");
						melhores_charadas[10].pontos += 100;
						limpar_tela();
						break;

				case 4 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (3): Em 100 pessoas, 99 são homens, presume-se que haja 1 mulher, desta forma, para que haja 98%% de homens, seria necessário haver 98 homens e 2 mulheres… Como não podemos alterar o número de mulheres, teriamos que manter a proporção de 98:2 ou simplificando, 49:1. Isto leva a concluir que se temos 99 homens e precisariamos ter 49, teriamos que retirar 50 homens para diminuir 1%% \n");	
						limpar_tela();											
						break;

				default :
						perguntas--;
						limpar_tela();
						printf("ESSA NÃO É UMA OPÇÃO\n");
						tela_inicial();
						break;
		    }
	    }


	    if(perguntas == 4){
			tela_inicial();
			printf("\\( ᗒ ᗣ ᗕ )/ <Camiseta, acetona, macaco, abacaxi, mágico. Qual é a próxima palavra da sequência?)\n\n");
			
			VIDAS(vidas);

			printf("(1)CAVALO\n");
			printf("(2)PUBLICAÇÃO\n");
			printf("(3)GRAVATA\n");
			printf("(4)ESCOVA\n\n");
			printf("RESPOSTA:");

			scanf("%d", &resposta);

			switch(resposta){
				case 1 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (2): A regra que determina a seqüência é a posição da letra “C”, publicação é a única palavra na qual “C” é a sexta letra.\n");
						limpar_tela();
						break;

				case 2 :
						printf("ACERTOU!!!\n");	
						printf("A RESPOSTA CORRETA É A (2): A regra que determina a seqüência é a posição da letra “C”, publicação é a única palavra na qual “C” é a sexta letra.\n");
						melhores_charadas[10].pontos += 100;
						limpar_tela();
						break;

				case 3 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (2): A regra que determina a seqüência é a posição da letra “C”, publicação é a única palavra na qual “C” é a sexta letra.\n");
						limpar_tela();
						break;

				case 4 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");	
						printf("A RESPOSTA CORRETA É A (2): A regra que determina a seqüência é a posição da letra “C”, publicação é a única palavra na qual “C” é a sexta letra.\n");
						limpar_tela();											
						break;

				default :
						perguntas--;
						limpar_tela();
						printf("ESSA NÃO É UMA OPÇÃO\n");
						tela_inicial();
						break;
		    }
	    }	


	    if(perguntas == 5){
			tela_inicial();
			printf("┐( ︶▽︶)┌ <6 e 4 = 210, 9 e 2 = 711 ,8 e 5 = 313, 5 e 2 = ?)\n\n");
			
			VIDAS(vidas);

			printf("(1)37\n");
			printf("(2)542\n");
			printf("(3)107\n");
			printf("(4)41\n\n");
			printf("RESPOSTA:");

			scanf("%d", &resposta);

			switch(resposta){
				case 1 :
						printf("ACERTOU!!!\n");
						printf("A RESPOSTA CORRETA É A (1): 5-2=3, 5+2= 7, juntando = 37\n");
						melhores_charadas[10].pontos += 100;
						limpar_tela();
						break;

				case 2 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (1): 5-2=3, 5+2= 7, juntando = 37\n");
						limpar_tela2();
						break;

				case 3 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (1): 5-2=3, 5+2= 7, juntando = 37\n");
						limpar_tela();
						break;

				case 4 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (1): 5-2=3, 5+2= 7, juntando = 37\n");
						limpar_tela();
						break;

				default :
						perguntas--;
						limpar_tela();
						printf("ESSA NÃO É UMA OPÇÃO\n");
						tela_inicial();
						break;
		    }
	    }


	    if(perguntas == 6){
			tela_inicial();
			printf("＼(  º□ º)/ <Se ontem fosse amanhã hoje seria sexta-feira, que dia é hoje?)\n\n");
			
			VIDAS(vidas);

			printf("(1)SEGUNDA\n");
			printf("(2)SÁBADO\n");
			printf("(3)DOMINGO\n");
			printf("(4)TERÇA\n\n");
			printf("RESPOSTA:");

			scanf("%d", &resposta);

			switch(resposta){
				case 1 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (3): DOMINGO\n");
						limpar_tela();
						break;

				case 2 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (3): DOMINGO\n");
						limpar_tela();
						break;

				case 3 :
						printf("ACERTOU!!!\n");
						printf("A RESPOSTA CORRETA É A (3): DOMINGO\n");
						melhores_charadas[10].pontos += 100;
						limpar_tela();
						break;

				case 4 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (3): DOMINGO\n");
						limpar_tela();
						break;

				default :
						perguntas--;
						limpar_tela();
						printf("ESSA NÃO É UMA OPÇÃO\n");
						tela_inicial();
						break;
		    }
	    }


	    if(perguntas == 7){
			tela_inicial();
			printf("⌒ (o＾▽＾o)ノ <Uma pedra cumprimentou uma tora de madeira, que horas são?)\n\n");
			
			VIDAS(vidas);

			printf("(1)12:00\n");
			printf("(2)16:20\n");
			printf("(3)00:00\n");
			printf("(4)20:00\n\n");
			printf("RESPOSTA:");

			scanf("%d", &resposta);

			switch(resposta){
				case 1 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (4): ""OI-TORA"" \n");
						limpar_tela();
						break;

				case 2 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (4): ""OI-TORA"" \n");
						limpar_tela();
						break;

				case 3 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (4): ""OI-TORA"" \n");
						limpar_tela();
						break;

				case 4 :
						printf("ACERTOU!!!\n");
						printf("A RESPOSTA CORRETA É A (4): ""OI-TORA"" \n");
						melhores_charadas[10].pontos += 100;	
						limpar_tela();					
						break;

				default :
						perguntas--;
						limpar_tela();
						printf("ESSA NÃO É UMA OPÇÃO\n");
						tela_inicial();
						break;
		    }
	    }


	    if(perguntas == 8){
			tela_inicial();
			printf("＼( ＾▽＾)／ <Em um avião, dentre os passageiros há 4 romanos e 1 inglês, qual é o nome da aeromoça?)\n\n");
			
			VIDAS(vidas);

			printf("(1)HELENA\n");
			printf("(2)IVONE\n");
			printf("(3)MIKAELA\n");
			printf("(4)ELIZABETH\n\n");
			printf("RESPOSTA:");

			scanf("%d", &resposta);

			switch(resposta){
				case 1 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (2): ""IV"" É 4 EM NÚMEROS ROMANOS E ""ONE"" É 1 EM INGLÊS\n");
						limpar_tela();
						break;

				case 2 :
						printf("ACERTOU!!!\n");
						printf("A RESPOSTA CORRETA É A (2): ""IV"" É 4 EM NÚMEROS ROMANOS E ""ONE"" É 1 EM INGLÊS\n");
						melhores_charadas[10].pontos += 100;	
						limpar_tela();
						break;

				case 3 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (2): ""IV"" É 4 EM NÚMEROS ROMANOS E ""ONE"" É 1 EM INGLÊS\n");
						limpar_tela();
						break;

				case 4 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");	
						printf("A RESPOSTA CORRETA É A (2): ""IV"" É 4 EM NÚMEROS ROMANOS E ""ONE"" É 1 EM INGLÊS\n");
						limpar_tela();											
						break;

				default :
						perguntas--;
						limpar_tela();
						printf("ESSA NÃO É UMA OPÇÃO\n");
						tela_inicial();
						break;
		    }
	    }	


	    if(perguntas == 9){
			tela_inicial();
			printf("(〃＾▽＾〃) <Na rua há quatro cachorros correndo atrás de uma cadela no cio, que horas são?)\n\n");
			
			VIDAS(vidas);

			printf("(1)00:00\n");
			printf("(2)12:56\n");
			printf("(3)17:45\n");
			printf("(4)16:01\n\n");
			printf("RESPOSTA:");

			scanf("%d", &resposta);

			switch(resposta){
				case 1 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (2): ""QUATRO PARA UMA""\n");
						limpar_tela();
						break;

				case 2 :
						printf("ACERTOU!!!\n");	
						printf("A RESPOSTA CORRETA É A (2): ""QUATRO PARA UMA""\n");
						melhores_charadas[10].pontos += 100;
						limpar_tela();
						break;

				case 3 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (2): ""QUATRO PARA UMA""\n");
						limpar_tela();
						break;

				case 4 :
						printf("ERROU!!!\n");
						vidas--;
						printf("-♡\n");
						printf("A RESPOSTA CORRETA É A (2): ""QUATRO PARA UMA""\n");
						limpar_tela();												
						break;

				default :
						perguntas--;
						limpar_tela();
						printf("ESSA NÃO É UMA OPÇÃO\n");
						tela_inicial();
						break;
		    }
	    }	


	    perguntas++;

	    if(resposta < 0){
	    	system("clear");
	    	return;
	    }

		if(vidas <= 0){
			printf("(ｏ・_・)ノ(╥ _ ╥ ) VOCÊ NÃO TEM MAIS VIDAS!! OU SEJA, ESTÁ MORTO.\n");
			printf("\n\n\t\tPressione <ENTER> para voltar ao MENU");
    		fflush(stdin);
    		fflush(stdout);
   			
   		 	while(getchar() != '\n');
			system("clear");
			return;
		}

	}while(perguntas != 10);

	if(vidas == 2){
	    melhores_charadas[10].pontos += 1000;
	}

	printf("\n\t\t\t          _______\n");
	printf("\t\t\t\\(^ヮ^)/ < YAY!!!)\n\n\n");

	printf("\n\t\tPressione <ENTER> para voltar ao MENU.");
    fflush(stdin);
    fflush(stdout);
    
    while(getchar() != '\n');
    system("clear");
    
}


void limpar_tela(){

	char enter;

	printf("\n\t\t\t   Pressione <ENTER>");
    fflush(stdin);
    fflush(stdout);
    scanf("%c", &enter);
   	while(getchar() != '\n');

	system("clear");
}


void limpar_tela2(){

	printf("\n\t\t\t   Pressione <ENTER>");
    fflush(stdin);
    fflush(stdout);
    
   	while(getchar() != '\n');
   	fflush(stdin);

	system("clear");	
}


void tela_inicial(){

	printf("\t\t◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉ \n");
    printf("\t\t◉✧✧✧✧✧✧✧✧✧✧✧✧✧✧✧CHARADA✧✧✧✧✧✧✧✧✧✧✧✧✧✧✧◉ \n");                                                                                                                    
 	printf("\t\t◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉◉Θ◉ \n\n");
}


void VIDAS(int vidas){

	int contador = 1;

	printf("VIDAS:");
	for(; contador <= vidas; contador++)
		printf(" ♡ ");
	printf("\n\n");
}


void ppt(PLAYER melhores_ppt[11]){

	int PLAYER1, PLAYER2, PLAYER3, v1, v2, v3, acabou = 0;
	char enter;

	historia_ppt();	

	do{

		printf("\t\t口口口口口口口口口口口口口口口口口口口口口口口口口口\n");
 		printf("\t\t口☆ ━━━━━━━━━☆   PEDRA/PAPEL\\TESOURA  ☆ ━━━━━━━━☆ 口\n");
 		printf("\t\t口口口口口口口口口口口口口口口口口口口口口口口口口口\n\n");


		printf("Bem-vindo ao PEDRA/PAPEL/TESOURA,\n");
		printf("O jogo é simples e é definido por estas 3 regras:\n");
		printf("• A tesoura corta o papel;\n");
		printf("• O papel embrulha a pedra;\n");
		printf("• A pedra quebra a tesoura.\n");
		printf("ESCOLHA UM NÚMERO ENTRE 1 E 3\n");
		printf("-O JOGO TERMINA QUANDO UM JOGADOR GANHA-\n\n");

		printf("(1)Q(ºo ºQ) (GUERREIRO DE JO - PEDRA)\n\n");
		printf("(2)(ﾒ￣▽￣)ﾉಠ  (GUERREIRO KEN - PAPEL)\n\n");
		printf("(3)( ＾▽＾)っ✂  (GUERREIRO DE PO - TESOURA)\n\n\n");
		printf("PLAYER1: ");

		v1 = scanf("%d", &PLAYER1);
		system("clear");


	
		printf("\t\t口口口口口口口口口口口口口口口口口口口口口口口口口口\n");
 		printf("\t\t口☆ ━━━━━━━━━☆   PEDRA/PAPEL\\TESOURA  ☆ ━━━━━━━━☆ 口\n");
 		printf("\t\t口口口口口口口口口口口口口口口口口口口口口口口口口口\n\n");


		printf("(1)Q(ºo ºQ) (GUERREIRO DE JO - PEDRA)\n\n");
		printf("(2)(ﾒ￣▽￣)ﾉಠ  (GUERREIRO KEN - PAPEL)\n\n");
		printf("(3)( ＾▽＾)っ✂  (GUERREIRO DE PO - TESOURA)\n\n\n");
		printf("PLAYER2: ");

		v2 = scanf("%d", &PLAYER2);
		system("clear");



		printf("\t\t口口口口口口口口口口口口口口口口口口口口口口口口口口\n");
 		printf("\t\t口☆ ━━━━━━━━━☆   PEDRA/PAPEL\\TESOURA  ☆ ━━━━━━━━☆ 口\n");
 		printf("\t\t口口口口口口口口口口口口口口口口口口口口口口口口口口\n\n");


		printf("(1)Q(ºo ºQ) (GUERREIRO DE JO - PEDRA)\n\n");
		printf("(2)(ﾒ￣▽￣)ﾉಠ  (GUERREIRO KEN - PAPEL)\n\n");
		printf("(3)( ＾▽＾)っ✂  (GUERREIRO DE PO - TESOURA)\n\n\n");
		printf("PLAYER3: ");

		v3 = scanf("%d", &PLAYER3);
		system("clear");



		printf("			       				                 |ZZzzz                         \n");
		printf("				           	                         |                          \n");
		printf("		            					         |                              \n");
		printf("    						    	    |ZZzzz      /^\\            |ZZzzz      \n");
		printf("	    					    	    |          |~~~|           |            \n");
		printf("							    |        |^^^^^^^|        / \\                  \n");
		printf("							   /^\\       |[]+    |       |~~~|                 \n");
		printf("							|^^^^^^^|    |    +[]|       |   |                  \n");
		printf("     |						        |    +[]|/\\/\\/\\/\\^/\\/\\/\\/\\/|^^^^^^^|\n");
		printf("   ! +_						        |+[]+   |~~~~~~~~~~~~~~~~~~|    +[]|        \n");
		printf("  _G//\\|					        |       |  []   /^\\   []   |+[]+   |       \n");
		printf(" { }` (__       				   	|   +[]+|  []  || ||  []   |   +[]+|        \n");
		printf(" ~(_,-'> `       				  	|[]+    |      || ||       |[]+    |        \n");
		printf("  / >             					|_______|------------------|_______|        \n");
		printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
		printf("\t\t\tVERIFICANDO O RESULTADO...\n");
		sleep(1);
		system("clear");

        printf("	      				                         	 |ZZzzz                                   \n");
		printf("		           	                            	         |                                \n");
		printf("		            			            	         |                                    \n");
		printf("    				    	            	    |ZZzzz      /^\\            |ZZzzz            \n");
		printf("	    			    	        	    |          |~~~|           |                      \n");
		printf("					               	    |        |^^^^^^^|        / \\                        \n");
		printf("						           /^\\       |[]+    |       |~~~|                           \n");
		printf("					        	|^^^^^^^|    |    +[]|       |   |                            \n");
		printf("            |					        |    +[]|/\\/\\/\\/\\^/\\/\\/\\/\\/|^^^^^^^|          \n");
		printf("   	  ! +_			       			|+[]+   |~~~~~~~~~~~~~~~~~~|    +[]|                      \n");
		printf("         _G//\\|			       	    		|       |  []   /^\\   []   |+[]+   |         \n");
		printf("        { }` (__        		   		|   +[]+|  []  || ||  []   |   +[]+|                  \n");
		printf("        ~(_,-'> `       			  	|[]+    |      || ||       |[]+    |                  \n");
		printf("         / >             				|_______|------------------|_______|                  \n");
		printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
		printf("\t\t\tVERIFICANDO O RESULTADO...\n");
		sleep(1);
		system("clear");

	    printf("	      				                         	 |ZZzzz                                   \n");
		printf("		           	                            	         |                                \n");
		printf("		            			            	         |                                    \n");
		printf("    				    	              	    |ZZzzz      /^\\            |ZZzzz            \n");
		printf("	    			    	        	    |          |~~~|           |                      \n");
		printf("					               	    |        |^^^^^^^|        / \\                        \n");
		printf("						           /^\\       |[]+    |       |~~~|                           \n");
		printf("					        	|^^^^^^^|    |    +[]|       |   |                            \n");
		printf("                     |				        |    +[]|/\\/\\/\\/\\^/\\/\\/\\/\\/|^^^^^^^|      \n");
		printf("       	           ! +_			           	|+[]+   |~~~~~~~~~~~~~~~~~~|    +[]|              \n");
		printf("                  _G//\\|			       	|       |  []   /^\\   []   |+[]+   |             \n");
		printf("                 { }` (__        		        |   +[]+|  []  || ||  []   |   +[]+|          \n");
		printf("                 ~(_,-'> `     			        |[]+    |      || ||       |[]+    |          \n");
		printf("                  / >                            	|_______|------------------|_______|      \n");
		printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
		printf("\t\t\tVERIFICANDO O RESULTADO...\n");
		sleep(1);
		system("clear");

		printf("                                                                                  |  \n");
		printf("                                                                                  |  \n"); 
		printf("		                                                                  |          \n");        
		printf("                                                                     |ZZzzz      /   \n");          
		printf("					        		     |          |~                               \n");           
		printf("			             				     |        |^^^                           \n");           
		printf("			   		    	_______             /^\\       |[]+                      \n");       
		printf("			     		       |  /.-- }         |^^^^^^^|    |                      \n");          
		printf("	                    |   	 __/)  | //_,-'          |    +[]|/\\/\\/\\/\\       \n");            
		printf("                          ! +_		(_ º \\}|//'              |+[]+   |~~~~~~~~      \n");  
		printf("	                 _G//\\|	          `\\  ^^^^^^^'.          |       |  []   /  \n");             
		printf("                        { }` (__            \\  , (   /\\\\         |   +[]+|  []  ||\n");            
		printf("                        ~(_,-'> `	     >/ -->/`  \\'.__ .   |[]+    |      ||      \n");              
		printf("	                 / >	 	    ^^   ^^     '^^^'    |_______|--------           \n");
		printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww  \n");
		printf("\t\t\tVERIFICANDO O RESULTADO...\n");
		sleep(1);
		system("clear");

		printf("                                                                                  |  \n");
		printf("                                                                                  |  \n"); 
		printf("		                                                                  |          \n");        
		printf("                                                                     |ZZzzz      /   \n");          
		printf("					        		     |          |~                               \n");           
		printf("			             				     |        |^^^                           \n");           
		printf("			   		    	_______             /^\\       |[]+                      \n");       
		printf("			     		       |  /.-- }         |^^^^^^^|    |                      \n");          
		printf("	                    |   	 __/)  | //_,-'          |    +[]|/\\/\\/\\/\\       \n");            
		printf("                          ! +_       ~^~(_ º \\}|//'              |+[]+   |~~~~~~~~  \n");  
		printf("	                 _G//\\|	          `\\  ^^^^^^^'.          |       |  []   /  \n");             
		printf("                        { }` (__            \\  , (   /\\\\         |   +[]+|  []  ||\n");            
		printf("                        ~(_,-'> `	     >/ -->/`  \\'.__ .   |[]+    |      ||      \n");              
		printf("	                 / >	 	    ^^   ^^     '^^^'    |_______|--------           \n");
		printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww  \n");
		printf("\t\t\tVERIFICANDO O RESULTADO...\n");
		sleep(2);
		system("clear"); 

		if((v1 == 1) && (v2 == 1) && (v3 == 1)){

			if(((PLAYER1 > 3) || (PLAYER1 < 1)) || ((PLAYER2 > 3) || (PLAYER2 < 1)) || ((PLAYER3 > 3) || (PLAYER3 < 1))){

					printf("\n\t\tISSO NÃO É UMA ESCOLHA\n");
					sleep(2);
					limpar_tela2();

			}else{
					
				if((PLAYER1 == PLAYER2) && (PLAYER2 == PLAYER3)){
				printf("\n\t\t    GUERREIROS DO MESMO REINO NÃO LUTAM ENTRE SI\n\n");
				}


				else if(((PLAYER1 == 1) && (PLAYER2 == 3) && (PLAYER3 == 3)) || ((PLAYER1 == 2) && (PLAYER2 == 1) && (PLAYER3 == 1)) || ((PLAYER1 == 3) && (PLAYER2 == 2) && (PLAYER3 == 2))){
				printf("\n\t\t\tPLAYER1 É VITORIOSO\n\n");
				acabou = 1;
				melhores_ppt[10].pontos += 100;
				}
				
				
				else if(((PLAYER2 == 1) && (PLAYER1 == 3) && (PLAYER3 == 3)) || ((PLAYER2 == 2) && (PLAYER1 == 1) && (PLAYER3 == 1)) || ((PLAYER2 == 3) && (PLAYER1 == 2) && (PLAYER3 == 2))){
				printf("\n\t\t\tPLAYER2 É VITORIOSO\n\n");
				acabou = 1;
				melhores_ppt[10].pontos += 100;
				}


				else if(((PLAYER3 == 1) && (PLAYER1 == 3) && (PLAYER2 == 3)) || ((PLAYER3 == 2) && (PLAYER1 == 1) && (PLAYER2 == 1)) || ((PLAYER3 == 3) && (PLAYER1 == 2) && (PLAYER2 == 2))){
				printf("\n\t\t\tPLAYER3 É VITORIOSO\n\n");
				acabou = 1;
				melhores_ppt[10].pontos += 100;
				}

				
		        else{
				    printf("\n\t\t\t   ~HOUVE EMPATE~\n\n");	
					sleep(2);
					limpar_tela2();
				}	
			}

		}else{

				printf("\n\t\t\tISSO NÃO É UMA ESCOLHA\n");
				while(getchar()!='\n');
				sleep(2);
				limpar_tela2();
		}

			

	}while(acabou == 0);



	printf("\n\t\tPressione <ENTER> para voltar ao MENU");
    fflush(stdin);
    fflush(stdout);
    scanf("%c", &enter);
    while(getchar() != '\n');

    system("clear");

}

void historia_ppt(){

	printf("\n");                                                                                                    
    printf("                         ,-.^._                 _                                           \n");                    
    printf("                       .'      `-.            ,' ;                                          \n");                     
    printf("            /`-.  ,----'         `-.   _  ,-.,'  `                                          \n");                       
    printf("         _.'   `--'                 `-' '-'      ;                                          \n");               
    printf("        :                                       ;                                           \n");                  
    printf("        ,'          o                           ;                                           \n");      
    printf("       :      Reino de JO                      ;                                            \n");         
    printf("       :                                      ;                                             \n");                   
    printf("       :                                      :         A MUITO MUITO TEMPO ATRÁS,          \n");           
    printf("       ;                                      :    EXISTIAM APENAS TRÊS REINOS VIZINHOS...  \n");                  
    printf("      (                            o          ;                                             \n");          
    printf("       `-.                    Reino de KEN  ,'                                              \n");         
    printf("         ;                                 :                                                \n");        
    printf("       .'                             .-._,'                                                \n");       
    printf("     .'           o                   `.                                                    \n");             
    printf("  _.'        Reino de PO             .__;                                                   \n");         
    printf("  `._                               ;                                                       \n");        
    printf("     `.                            :                                                        \n");                 
    printf("       `.               ,..__,---._;                                                        \n");             
    printf("         `-.__         :                                                                    \n");                  
    printf("              `.--.____;                                                                    \n"); 
 	limpar_tela2();

 	printf("                                                               .---.            \n");             
    printf("                                                              /  .  \\          \n");  
    printf("                                                             |\\_/|   |         \n");     
    printf("                                                             |   |  /|          \n");        
 	printf(" .----------------------------------------------------------------'  |          \n");    
	printf(" /  .-.    OS TRÊS REIS SE ODIAVAM DE TAL FORMA QUE CONSTANTEMENTE   |          \n");     
	printf("|  /   \\   MANDAVAM UM SÚDITO ESCOLHIDO A DEDO PARA BATALHAR ATÉ     |         \n");        
	printf("| |\\_.  |            A MORTE PELA HONRA DE SEU REINO...              |         \n");       
	printf("|\\|  | /|                                                            |         \n");           
	printf("| `---' |  Q(ºo ºQ) (GUERREIRO DE JO)    (ﾒ￣▽￣)ﾉಠ  (GUERREIRO KEN) |          \n");         
	printf("|       |                                                            |          \n");                                 
	printf("|       |              ( ＾▽＾)っ✂  (GUERREIRO DE PO)                /           \n");         
	printf("|       |----------------------------------------------------------'            \n");   
	printf("\\       |                                                                      \n");     
	printf(" \\     /                                                                       \n");         
	printf("  `---'                                                                         \n");                                                                     
	limpar_tela2();
 	
 	printf("AS BATALHAS JÁ ERAM TRAVADAS A TANTO TEMPO QUE NÍNGUEM MAIS LEMBRAVA O MOTIVO DO DESENTENDIMENTO ENTRE OS TRÊS...\n");
 	printf("MESMO ASSIM, OS POVOS NUNCA QUESTIONAVAM SEU RESPECTIVO REI, POIS TODOS OS TRÊS ERAM MUITO RESPEITADOS E AMADOS...\n");
	limpar_tela2();

	printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
 	printf(" O RESULTADO DAS BATALHAS ERA SEMPRE O MESMO:\n");
 	printf(" -QUANDO JO MANDAVA SEUS SÚDITOS PARA O REINO DE KEN, TODOS ERAM MORTOS, QUANDO MANDAVA PARA O REINO DE PO, TODOS VOLTAVAM VIVOS E VITORIOSOS. \n");
 	printf(" -QUANDO KEN MANDAVA SEUS SÚDITOS PARA O REINO DE PO, TODOS ERAM MORTOS, QUANDO MANDAVA PARA O REINO DE JO, TODOS VOLTAVAM VIVOS E VITORIOSOS. \n");
 	printf(" -QUANDO PO MANDAVA SEUS SÚDITOS PARA O REINO DE JO, TODOS ERAM MORTOS, QUANDO MANDAVA PARA O REINO DE KEN, TODOS VOLTAVAM VIVOS E VITORIOSOS. \n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
 	printf("\t\t\tDESTA FORMA SE MANTEU POR MUITAS GERAÇÕES E NUNCA HOUVE UMA TRÉGUA SEQUER...\n");
	limpar_tela2();

 	printf("ESTÁ NA HORA DE DECIDIR DE QUE LADO VOCÊ IRÁ FICAR, VAMOS COMEÇAR.\n");
	limpar_tela2();
} 
  

void campo_minado(PLAYER melhores_minas[11]){
 
    char minas[TAM][TAM];
    char terreno[TAM][TAM];
    int linha, coluna; 
    char enter;
 	
    
	printf("\t\t                            _                                \n");          
	printf("\t\t          ,--.!,           (_)                       ,--.!,  \n");   
	printf("\t\t       __/   -*-  _ __ ___  _ _ __   __ _ ___     __/   -*-  \n"); 
	printf("\t\t     ,d08b.  '|` | '_ ` _ \\| | '_ \\ / _` / __|  ,d08b.  '|`\n");
	printf("\t\t     0088MM      | | | | | | | | | | (_| \\__ \\  0088MM     \n"); 
	printf("\t\t     `9MMP'      |_| |_| |_|_|_| |_|\\__,_|___/  `9MMP'      \n\n");



	printf(" _____________________________________________________________________________________________ \n");
	printf("|                                                                                             |\n");
	printf("|    VOCÊ FOI CAPTURADO PELOS INIMIGOS JUNTO COM SEU CÃO(MAX).                                |\n"); 
	printf("|    IMAGINANDO QUE VOCÊS NÃO FOSSEM CAPAZES,                                                 |\n");
	printf("|    OS INIMIGOS TE DÃO UMA CHANCE DE ESCAPAR VIVOS,                                          |\n"); 
	printf("|    SE SEU CÃO, SEGUIDO PELOS SEUS COMANDOS,                                                 |\n");
	printf("|    DESCOBRIR ONDE ESTÃO ENTERRADAS AS MINAS QUE SE LOCALIZAM NO TERRITÓRIO INIMIGO.         |\n");
	printf("|    O QUE ELES NÃO CONTAVAM, É QUE VOCÊ E MAX SÃO ESPECIALISTAS EM BOMBAS E MAX CONSEGUE,    |\n"); 
	printf("|    POR MEIO DE SINAIS, AVISÁ-LO QUANTAS BOMBAS PRÓXIMAS HÁ DE ONDE ELE CAVA.                |\n");
	printf("|    OS INIMIGOS TE DÃO APENAS UM PEDAÇO DE PAPEL E UM LÁPIS                                  |\n");
	printf("|    PARA VOCÊ ANOTAR AS COORDENADAS DOS LOCAIS LIVRES DE BOMBAS.                             |\n");
	printf("|    BOA SORTE,                                                                               |\n");
	printf("|    TENHA CUIDADO PARA NÃO PASSAR OS COMANDOS ERRADOS PARA SEU COMPANHEIRO,                  |\n");
	printf("|    SENÃO ELE IRÁ MORRER POR SUA CULPA E VOCÊ SERÁ FUZILADO PELOS INIMIGOS.                  |\n");
	printf("|_____________________________________________________________________________________________|\n\n");



	printf("\tBem-vindo ao minas,\n");
	printf("\tO jogo é simples, você só precisa cavar todas as coordenadas sem bombas do terreno.\n");
	printf("\t\t-ESCOLHER UMA COORDENADA AVISA O NÚMERO DE BOMBAS ADJACENTES Á ELA-\n");
	printf("\t\t-PARA REINICIAR O JOGO, PRESSIONE UM NÚMERO MAIOR QUE 6 OU UMA LETRA-\n");
	printf("\t\t-EXISTEM 10 BOMBAS ARMADAS NO CAMPO-\n");
	limpar_tela2();

    terreno_escondido(minas);
    terreno_visivel(terreno);
    escreve_terreno_visivel(terreno);
    
 
    for(;;){

        do{


        printf("\nESCOLHA AS SUAS COORDENADAS: \n\n");
        printf("|LINHA| ");
        
        if(scanf("%d", &linha) == 0){
            campo_minado(melhores_minas);
        }
        printf("\n|COLUNA| ");
        if(scanf("%d", &coluna) == 0){
            campo_minado(melhores_minas);
        }
        if((linha > 6) || (linha < 1) || (coluna < 1) || (coluna > 6)){
            campo_minado(melhores_minas);
        }
         
        }while((linha < 0) || (linha > TAM - 1) || (coluna < 0) || (linha > TAM - 1));
 
 
        if(minas[linha][coluna] == '*'){

            system("clear");

            system("clear");

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t       \\   .-;:-,.    /          \n");
            printf("\t\t\t\t    \\  ...::';'.:....' /         \n");
            printf("\t\t\t\t       (^^.^~~:.'')  ).           \n");
            printf("\t\t\t\t       -\\  \\     /  /-          \n");
            printf("\t\t\t\t      ___\\  \\   /  /___         \n");

            usleep(90000);
            system("clear");

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                 \n");
			printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t       \\         .  ./           \n");
            printf("\t\t\t\t    \\     .:';'.:..'   /         \n");
            printf("\t\t\t\t        ( ^^.^~~:.'').            \n");
            printf("\t\t\t\t  -   (/  .    . . \\ \\)  -      \n");
            printf("\t\t\t\t     ((| :. ~ ^  :. .|))          \n");
            printf("\t\t\t\t  -   (\\- |  \\ /  |  /)  -      \n");
            printf("\t\t\t\t       -\\  \\     /  /-          \n");
            printf("\t\t\t\t      ___\\  \\   /  /___         \n");

            usleep(90000);
            system("clear");

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t       \\  .:';'.:..   ./         \n");
            printf("\t\t\t\t    \\   /   /       )            \n");
            printf("\t\t\t\t       ( ^^.^~~:.  '').           \n");
            printf("\t\t\t\t  -   (/  .    . . \\ \\)  -      \n");
            printf("\t\t\t\t     ((| :. ~ ^  :.  .|))         \n");
            printf("\t\t\t\t  -   (\\- |  \\ /  |  /)  -      \n");
            printf("\t\t\t\t       -\\  \\     /  /-          \n");
            printf("\t\t\t\t      ___\\  \\   /  /___         \n");

            usleep(90000);
            system("clear");

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t       \\  .:';'.:..   ./         \n");
            printf("\t\t\t\t    \\   /   /       )            \n");
            printf("\t\t\t\t       ( ^^.^~~:.  '').          \n");
            printf("\t\t\t\t  -   (/  .    . . \\ \\)  -      \n");
            printf("\t\t\t\t     ((| :. ~ ^  :.  .|))         \n");
            printf("\t\t\t\t  -   (\\- |  \\ /  |  /)  -      \n");
            printf("\t\t\t\t        -\\  \\     / /-          \n");
            printf("\t\t\t\t      _____|| || ||_____         \n");

            usleep(90000);
            system("clear");

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t       \\  .:';'.:..   ./         \n");
            printf("\t\t\t\t    \\   /   /       )            \n");
            printf("\t\t\t\t       ( ^^.^~~:.  '').          \n");
            printf("\t\t\t\t  -   (/  .    . . \\ \\)  -      \n");
            printf("\t\t\t\t     ((| :. ~ ^  :.  .|))         \n");
            printf("\t\t\t\t  -   (\\- |  \\ /  |  /)  -      \n");
            printf("\t\t\t\t         || |    | ||               \n");
            printf("\t\t\t\t      _____|| || ||_____            \n");

            usleep(90000);
            system("clear");

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t       \\  .:';'.:..   ./         \n");
            printf("\t\t\t\t    \\   /   /       )            \n");
            printf("\t\t\t\t       ( ^^.^~~:.  '').          \n");
            printf("\t\t\t\t  -   (/  .    . . \\ \\)  -      \n");
            printf("\t\t\t\t     ((| :. ~ ^  :.  .|))         \n");
            printf("\t\t\t\t       -  || |  | ||     -         \n");
            printf("\t\t\t\t           || |  ||               \n");
            printf("\t\t\t\t      ______|| |||______            \n");

            usleep(90000);
            system("clear");

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t       \\  .:';'.:..   ./         \n");
            printf("\t\t\t\t    \\   /   /       )            \n");
            printf("\t\t\t\t       ( ^^.^~~:.  '').          \n");
            printf("\t\t\t\t  -   (/  .    . . \\ \\)  -      \n");
            printf("\t\t\t\t         ||  |  |  ||                \n");
            printf("\t\t\t\t       -   || |  ||     -         \n");
            printf("\t\t\t\t            ||  ||               \n");
            printf("\t\t\t\t      _______||||_______            \n");

            usleep(90000);
            system("clear");

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t           .:';'.:..   .         \n");
            printf("\t\t\t\t         /    /     )            \n");
            printf("\t\t\t\t      - (^^.^~~:.  '').          \n");
            printf("\t\t\t\t       (:            :)  -      \n");
            printf("\t\t\t\t          ':._   _.:'                 \n");
            printf("\t\t\t\t       -    ||  ||     -         \n");
            printf("\t\t\t\t             |  |               \n");
            printf("\t\t\t\t     _____((/   \\))_____            \n");

            usleep(90000);
            system("clear");
			
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
			printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t          .:';'.:..            \n");
            printf("\t\t\t\t         /   /     )            \n");
            printf("\t\t\t\t        (^^.^~~:. '').          \n");
            printf("\t\t\t\t       (:           :)         \n");
            printf("\t\t\t\t         ':._   _.:'                 \n");
            printf("\t\t\t\t           (=====)                     \n"); 
            printf("\t\t\t\t             | |                       \n");
            printf("\t\t\t\t             | |               \n");
            printf("\t\t\t\t             | |               \n");
            printf("\t\t\t\t       ___((/   \\))___            \n");

            usleep(90000);
            system("clear");

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t         ..-^~~~^-..                   \n"); 
            printf("\t\t\t\t       .~           ~.                 \n");      
            printf("\t\t\t\t      (;:           :;)                \n");          
            printf("\t\t\t\t       (:           :)                 \n");           
            printf("\t\t\t\t         ':._   _.:'                   \n");             
            printf("\t\t\t\t             | |                       \n");         
            printf("\t\t\t\t           (=====)                     \n");           
            printf("\t\t\t\t             | |                       \n");                 
            printf("\t\t\t\t             | |                       \n");            
            printf("\t\t\t\t             | |                       \n");                   
            printf("\t\t\t\t       ___((/   \\))___                \n");  

			usleep(90000);
            system("clear");

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t      ____,-~~/~`---.               \n");
			printf("\t\t\t\t    _/_,---(    ,    )              \n");     
			printf("\t\t\t\t   /      <    /   )  \\            \n");       
			printf("\t\t\t\t  ==----------------===;;;=        \n");          
			printf("\t\t\t\t   \\/~'~'~'~'~'~\\~'~)~'/          \n");               
			printf("\t\t\t\t   (_ (   \\ (    >    \\)          \n");               
			printf("\t\t\t\t   \\_( _ <       >_>'              \n");          
			printf("\t\t\t\t      ~ `-i'::>|--''                 \n");       
			printf("\t\t\t\t           |;|.|                    \n");              
			printf("\t\t\t\t         .'|i|i|'.                  \n");      
			printf("\t\t\t\t  ______(` ^`-' ' )______           \n\n"); 

            usleep(100000);
            system("clear"); 

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t     ____,-~~/~  `---.               \n");
			printf("\t\t\t\t   _/_,---(      ,    )              \n");     
			printf("\t\t\t\t  /        <    /   )  \\            \n");       
			printf("\t\t\t\t===------------------===;;;==        \n");          
			printf("\t\t\t\t  \\/  ~'~'~'~'~'~\\~'~)~'/          \n");               
			printf("\t\t\t\t  (_ (   \\  (     >    \\)          \n");               
			printf("\t\t\t\t  \\_( _ <         >_>'              \n");          
			printf("\t\t\t\t     ~ `-i' ::>|--''                 \n");       
			printf("\t\t\t\t          I;|.|.|                    \n");              
			printf("\t\t\t\t        .'|i::|i|'.                  \n");      
			printf("\t\t\t\t  _____(` ^''`-' ' )_____           \n\n"); 

			usleep(100000);
            system("clear");
            
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t     _.-^^---....,,--.                \n");
            printf("\t\t\t\t _--   ---(           '--_             \n");     
            printf("\t\t\t\t<------------------------>)           \n");
            printf("\t\t\t\t|       (         >       |           \n");
            printf("\t\t\t\t \\._      .''.,        _./           \n");
            printf("\t\t\t\t    ```--. . , ; .--'''               \n");
            printf("\t\t\t\t          | |   |                     \n");
            printf("\t\t\t\t       .-=||  | |=-.                  \n");
            printf("\t\t\t\t       `-=#$%%&%%$#=-'                \n");
            printf("\t\t\t\t          | ;  :|                     \n");
            printf("\t\t\t\t _____.,-#%%&$@%%#&#~,._____          \n\n");

			usleep(100000);
            system("clear"); 

            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");                         
			printf("\t\t\t\t     _.-^^---....,,--                 \n");
            printf("\t\t\t\t _--                  --_             \n");     
            printf("\t\t\t\t<                        >)           \n");
            printf("\t\t\t\t|                         |           \n");
            printf("\t\t\t\t \\._                   _./           \n");
            printf("\t\t\t\t    ```--. . , ; .--'''               \n");
            printf("\t\t\t\t          | |   |                     \n");
            printf("\t\t\t\t       .-=||  | |=-.                  \n");
            printf("\t\t\t\t       `-=#$%%&%%$#=-'                \n");
            printf("\t\t\t\t          | ;  :|                     \n");
            printf("\t\t\t\t _____.,-#%%&$@%%#&#~,._____          \n\n");

			usleep(100000);
            system("clear");          
 
            printf("\t\t\t\t                                  \n");
            printf("\t\t\t\t                                  \n");
			printf("     _.-^^---....,,--                                                                    \n");
            printf(" _--                  --_                                                                \n");     
            printf("<                        >)                                                 -|-          \n");
            printf("|                         |                                                  |           \n");
            printf(" \\._                   _./                                               .-'~~~`-.       \n");
            printf("    ```--. . , ; .--'''                                                .' _     _ `.     \n");
            printf("          | |   |                                                      | |_| | |_) |     \n");
            printf("       .-=||  | |=-. VOCÊ DEU UM COMANDO ERRADO E MAX CAVOU UMA MINA.  | | \\ | |   |    \n");
            printf("       `-=#$%%&%%$#=-'                                                   |    max    |     \n");
            printf("          | ;  :|                                                    \\\\|           |//   \n");
            printf(" _____.,-#%%&$@%%#&#~,._____                                          ^^^^^^^^^^^^^^^^^^^  \n");
            printf("\n");      


            escreve_terreno_escondido(minas);

            printf("\n\t\t\t\t\tPressione <ENTER>");
		    fflush(stdin);
		    fflush(stdout);
		    scanf("%c", &enter);
		   	while(getchar() != '\n');

			system("clear");
    		return;

            

        }
        else{
            conta_minas(terreno, minas, linha, coluna);
        }
                             
        escreve_terreno_visivel(terreno);
 
        if(ganhou(terreno, minas) == TRUE){

        	melhores_minas[10].pontos += 100000;

        	printf("\t\t                                               __,------._           \n");                             
            printf("\t\t                                            .-'           ``-.         \n");                       
            printf("\t\t                                          .'  ESTAMOS SALVOS  `.       \n");               
            printf("\t\t                                         .'    COMPANHEIRO!    :       \n");                             
            printf("\t\t                                        ,'        YAY!!!       |       \n");                   
            printf("\t\t                            __       __,',-'`.      ♡        ,'        \n");                         
            printf("\t\t     ,                    ,' e`--o   `--'     `-..______,--''          \n");                 
            printf("\t\t    ((                   (  | __,'                                     \n");                        
            printf("\t\t     \\\\~----------------' \\_;/                                      \n");         
            printf("\t\t     (                      /                                          \n");                
            printf("\t\t     /) ._______________.  )                                           \n");        
            printf("\t\t    (( (               (( (                                            \n");  
            printf("\t\t     ``-'               ``-'                                           \n");     

        	printf("\n\t\t\t\t\tPressione <ENTER>");
		    fflush(stdin);
		    fflush(stdout);
		    scanf("%c", &enter);
		   	while(getchar() != '\n');

			system("clear");
    		return;
        }
 
 
    } 
}
 

void terreno_escondido(char minas[TAM][TAM]){
     
    int linhas_bomba[10];
    int colunas_bomba[10];
    int i, j;
    int aux=0;

    srand(time(NULL));
 
    /*escolhe coordenadas de bombas*/
    for(i = 0; i < 10; i++){

        linhas_bomba[i] = abs(rand() % 6);
        colunas_bomba[i] = abs(rand() % 6);

    }


    /*preenchendo bombas na matriz*/
    for(i = 0; i < 6; i++){
        for (j = 0; j < 6; ++j){

            if((linhas_bomba[aux] == i) || (colunas_bomba [aux] == j)){
                minas[i+1][j+1] = '*';
                aux++;
            }else{
                minas[i+1][j+1] = '.';

            }
        }
    }
}




void terreno_visivel( char terreno[TAM][TAM]){

    int i, j;
 
    
    for(i = 0; i < TAM; i++)
        for(j = 0; j < TAM; j++)
            terreno[i][j] = '.';
 
 
    for(i = 0; i < TAM; i++)
        for(j = 0; j < TAM; j++)
            if(i == 0 || i == TAM - 1)
                terreno[i][j] = ' ';
 
    for(j = 0; j < TAM; j++)
        for(i = 0; i < TAM; i++)
            if(j == 0 || j == TAM - 1)
                terreno[i][j] = ' ';
}




void escreve_terreno_visivel(char terreno[TAM][TAM]){

    int i, j;
 
    system("clear");

    printf("\t\t                            _                                \n");          
	printf("\t\t          ,--.!,           (_)                       ,--.!,  \n");   
	printf("\t\t       __/   -*-  _ __ ___  _ _ __   __ _ ___     __/   -*-  \n"); 
	printf("\t\t     ,d08b.  '|` | '_ ` _ \\| | '_ \\ / _` / __|  ,d08b.  '|`\n");
	printf("\t\t     0088MM      | | | | | | | | | | (_| \\__ \\  0088MM     \n"); 
	printf("\t\t     `9MMP'      |_| |_| |_|_|_| |_|\\__,_|___/  `9MMP'      \n\n\n");

    
    printf("\t\t\t     ");
    for(i = 1; i < TAM - 1; i++)
        printf("%d    ", i);
    printf("\n\n");
 
    
    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){
            if(i == 0 || i == TAM - 1){
                terreno[i][j] = ' ';
            }
        }
    }
 
    for(j = 0; j < TAM; j++){
        for(i = 0; i < TAM; i++){
            if(j == 0 || j == TAM - 1){
                terreno[i][j] = ' ';
            }
        }
    }
 
    
    for(i = 0; i < TAM; i++){
        printf("\t\t\t");
        for(j = 0; j < TAM; j++){
            printf("%c ", terreno[i][j]);
            printf("   ");
        }

        if(i > 0 &&  i < TAM - 1)
            printf("%d", i);
        if(i < 7){
            printf("\n\n\n");
        }else{
            printf("\n");
        }    
    }
}




void escreve_terreno_escondido(char minas[TAM][TAM]){

    int i, j;
 
    printf("\t\t\t\t\t -CAMPO MINADO-\n");
    printf("\n\t\t\t\t\t ");
    for(i = 1; i < TAM - 1; i++){
        printf("%d ", i);
    }
    printf("\n");
 
    
    for(i = 1; i < 7; i++){
    	printf("\t\t\t\t\t ");
        for(j = 1; j < 7; j++){
            printf("%c ", minas[i][j]);
        }
        if((i > 0) &&  (i < TAM - 1)){
            printf("%d", i);
        }
        printf("\n");
    } 
    printf("\n");
}
 



int procura_minas(char minas[TAM][TAM], int linha, int coluna){

    int minas_proximas = 0;
 
    /*+*/
    if(minas[linha - 1][coluna] == '*')
        minas_proximas++;
    if(minas[linha + 1][coluna] == '*')
        minas_proximas++;
    if(minas[linha][coluna - 1] == '*')
        minas_proximas++;
    if(minas[linha][coluna + 1] == '*')
        minas_proximas++;
 
    /*diagonais*/
    if(minas[linha - 1][coluna + 1] == '*')
        minas_proximas++;
    if(minas[linha - 1][coluna - 1] == '*')
        minas_proximas++;
    if(minas[linha + 1][coluna + 1] == '*')
        minas_proximas++;
    if(minas[linha + 1][coluna - 1] == '*')
        minas_proximas++;
return minas_proximas;
}
 
 

void conta_minas(char terreno[TAM][TAM], char minas[TAM][TAM], int linha, int coluna){

    int minas_proximas = 0;
    int i = 0;
 
        minas_proximas = procura_minas(minas, linha, coluna);
        terreno[linha][coluna] = (char)(((int)'0') + minas_proximas);
 
        
        while((minas_proximas < 1) && (i < linha)){

            minas_proximas = procura_minas(minas, linha - i, coluna);
            terreno[linha - i][coluna] = (char)(((int)'0') + minas_proximas);
            i++;

        }

        i = 0;
        minas_proximas = 0;
      
        while((minas_proximas < 1) && (linha + i < TAM - 2)){

            minas_proximas = procura_minas(minas, linha + i, coluna);
            terreno[linha + i][coluna] = (char)(((int)'0') + minas_proximas);
            i++;
        }

        i = 0;
        minas_proximas = 0;
        
        while((minas_proximas < 1) && (i < coluna)){

            minas_proximas = procura_minas(minas, linha, coluna - i);
            terreno[linha][coluna - i] = (char)(((int)'0') + minas_proximas);
            i++;
        }

        i = 0;
        minas_proximas = 0;
       
        while((minas_proximas < 1) && (coluna + i < TAM - 2)){

            minas_proximas = procura_minas(minas, linha, coluna + i);
            terreno[linha][coluna + i] = (char)(((int)'0') + minas_proximas);
            i++;
        }

        i = 0;
        minas_proximas = 0;
        
        while((minas_proximas < 1) && (coluna + i < TAM - 2) && (i < linha)){

            minas_proximas = procura_minas(minas, linha - i, coluna + i);
            terreno[linha + i][coluna + i] = (char)(((int)'0') + minas_proximas);
            i++;
        }

        i = 0;
        minas_proximas = 0;
        
        while((minas_proximas < 1) && (i < linha) && (i < linha) && (i < coluna)){

            minas_proximas = procura_minas(minas, linha - i, coluna - i);
            terreno[linha - i][coluna - i] = (char)(((int)'0') + minas_proximas);
            i++;
        }

        i = 0;
        minas_proximas = 0;
       
        while((minas_proximas < 1) && (linha + i < TAM - 2) && (coluna + i < TAM - 2)){

            minas_proximas = procura_minas(minas, linha + i, coluna + i);
            terreno[linha + i][coluna + i] = (char)(((int)'0') + minas_proximas);
            i++;
        }

        i = 0;
        minas_proximas = 0;
       
        while((minas_proximas < 1) && (linha + i < TAM - 2) && (i < coluna)){

            minas_proximas = procura_minas(minas, linha + i, coluna - i);
            terreno[linha + i][coluna - i] = (char)(((int)'0') + minas_proximas);
            i++;
        }
}
 

int ganhou(char terreno[TAM][TAM], char minas[TAM][TAM]){

    int i, j;
 
    for(i = 1; i < TAM - 1; i++){
        for(j = 1; j < TAM - 1; j++){
            if((terreno[i][j] == '.') && (minas[i][j] != '*')){
                return FALSE;
            }
        }
    }
return TRUE;
}





void propaganda(int sec){

    if(sec == 4){

        usleep(9000);
        system("clear");
        
        printf("        _,-''',-''''`--.                                                                   \n");
        printf("      ,'    __,--''''   '' .                                                               \n");
        printf("    ,'       _   ___  '-._,-'                                                              \n"); 
        printf("  ,'                ''--..__ '.                                                            \n");   
        printf(" (                          `..'                                                           \n");   
        printf("  `._,      _   _             ;                                             ___            \n");
        printf("   ,'    ,,' `-'Hb-.___..._,-'                                        .-.  (   )      .-.  \n");
        printf("   \\      'Hb.-'HH`-.dHF'   /     .-.    .--.     .--.     ___  ___  ( __)  | |_     ( __) \n");
        printf("    `---...'Hb  HH  dF'..-''     ( __)  /    \\   /    \\   (   )(   ) (''') (   __)   (''') \n");
        printf("            'Hb HH dF            (''') |  .-. ; |  .-. '   | |  | |   | |   | |       | |  \n");
        printf("             'HbHHdF              | |  |  | | | | |  | |   | |  | |   | |   | | ___   | |  \n");
        printf("              |HHHF               | |  |  |/  | | |  | |   | |  | |   | |   | |(   )  | |  \n");
        printf("              |HHH|               | |  |  ' _.' | |  | |   | |  | |   | |   | | | |   | |  \n");
        printf("              |HHH|               | |  |  .'.-. | '  | |   | |  ; '   | |   | ' | |   | |  \n");
        printf("              |HHH|           ___ | |  '  `-' / ' `-'  |   ' `-'  /   | |   ' `-' ;   | |  \n");
        printf("              |HHH|          (   )' |   `.__.'   `._ / |    '.__.'   (___)   `.__.   (___) \n");
        printf("              dHHHb           ; `-' '                | |                                   \n");
        printf("            .dFd|bHb.          '.__.'                (___)                                 \n");

        usleep(250000);
        system("clear");
        
    }
  
}

void PLAY(int P1, int P2){

    if((P1 < 10) && (P2 < 10)){
        printf("\t                 .---.                                _______          \n");
        printf("\t               /` ___|`\\                             ( _____ )        \n"); 
        printf("\t               |_/    \\|                             ((     ))        \n");
        printf("\t               (  o/o  )                             (  -|-  )         \n");
        printf("\t                \\_ - _/                               \\_ = _/        \n");      
        printf("\t               .-'|_|'-.                             .-'|_|'-.         \n");
        printf("\t              /    _    \\                           /    _    \\      \n");
        printf("\t             /    (_)    \\                         /    (_)    \\     \n");   
        printf("\t            / _____|_____ \\                       / _____|_____ \\    \n");
        printf("\t           /.-------------.\\                     /.-------------.\\   \n");
        printf("\t           \\|             |/                     \\|             |/   \n");
        printf("\t            |    _____    |                       |    _____    |      \n");
        printf("\t            |   |     |   |                       |   |     |   |      \n");
        printf("\t            |   |P1:%d |   |                       |   |P2:%d |   |    \n", P1, P2);
        printf("\t            |   |_____|   |                       |   |_____|   |      \n");  
        printf("\t            |             |                       |             |      \n");
        printf("\t            |             |                       |             |      \n\n");
    }

    if((P1 < 10) && (P2 >= 10)){
        printf("\t                 .---.                                _______          \n");
        printf("\t               /` ___|`\\                             ( _____ )        \n"); 
        printf("\t               |_/    \\|                             ((     ))        \n");
        printf("\t               (  o/o  )                             (  -|-  )         \n");
        printf("\t                \\_ - _/                               \\_ = _/        \n");      
        printf("\t               .-'|_|'-.                             .-'|_|'-.         \n");
        printf("\t              /    _    \\                           /    _    \\      \n");
        printf("\t             /    (_)    \\                         /    (_)    \\     \n");   
        printf("\t            / _____|_____ \\                       / _____|_____ \\    \n");
        printf("\t           /.-------------.\\                     /.-------------.\\   \n");
        printf("\t           \\|             |/                     \\|             |/   \n");
        printf("\t            |    _____    |                       |    _____    |      \n");
        printf("\t            |   |     |   |                       |   |     |   |      \n");
        printf("\t            |   |P1:%d |   |                       |   |P2:%d|   |     \n", P1, P2);
        printf("\t            |   |_____|   |                       |   |_____|   |      \n");  
        printf("\t            |             |                       |             |      \n");
        printf("\t            |             |                       |             |      \n\n");
    }

    if((P1 >= 10) && (P2 < 10)){
        printf("\t                 .---.                                _______          \n");
        printf("\t               /` ___|`\\                             ( _____ )        \n"); 
        printf("\t               |_/    \\|                             ((     ))        \n");
        printf("\t               (  o/o  )                             (  -|-  )         \n");
        printf("\t                \\_ - _/                               \\_ = _/        \n");      
        printf("\t               .-'|_|'-.                             .-'|_|'-.         \n");
        printf("\t              /    _    \\                           /    _    \\      \n");
        printf("\t             /    (_)    \\                         /    (_)    \\     \n");   
        printf("\t            / _____|_____ \\                       / _____|_____ \\    \n");
        printf("\t           /.-------------.\\                     /.-------------.\\   \n");
        printf("\t           \\|             |/                     \\|             |/   \n");
        printf("\t            |    _____    |                       |    _____    |      \n");
        printf("\t            |   |     |   |                       |   |     |   |      \n");
        printf("\t            |   |P1:%d|   |                       |   |P2:%d |   |      \n", P1, P2);
        printf("\t            |   |_____|   |                       |   |_____|   |      \n");  
        printf("\t            |             |                       |             |      \n");
        printf("\t            |             |                       |             |      \n\n");
    }

    if((P1 >= 10) && (P2 >= 10)){
        printf("\t                 .---.                                _______          \n");
        printf("\t               /` ___|`\\                             ( _____ )        \n"); 
        printf("\t               |_/    \\|                             ((     ))        \n");
        printf("\t               (  o/o  )                             (  -|-  )         \n");
        printf("\t                \\_ - _/                               \\_ = _/        \n");      
        printf("\t               .-'|_|'-.                             .-'|_|'-.         \n");
        printf("\t              /    _    \\                           /    _    \\      \n");
        printf("\t             /    (_)    \\                         /    (_)    \\     \n");   
        printf("\t            / _____|_____ \\                       / _____|_____ \\    \n");
        printf("\t           /.-------------.\\                     /.-------------.\\   \n");
        printf("\t           \\|             |/                     \\|             |/   \n");
        printf("\t            |    _____    |                       |    _____    |      \n");
        printf("\t            |   |     |   |                       |   |     |   |      \n");
        printf("\t            |   |P1:%d|   |                       |   |P2:%d|   |      \n", P1, P2);
        printf("\t            |   |_____|   |                       |   |_____|   |      \n");  
        printf("\t            |             |                       |             |      \n");
        printf("\t            |             |                       |             |      \n\n");
        
    }
}


int CHUTE_DEUSA(char P){

    char chute[31];

    printf("DIGITE A PRIMEIRA PALAVRA: ");
    scanf("%s", chute);
    if((strcmp(chute, "MARIANA") == 0) || (strcmp(chute, "mariana") == 0)){
        printf("DIGITE A SEGUNDA PALAVRA: ");
        scanf("%s", chute);

        if((strcmp(chute, "MENDANHA") == 0) || (strcmp(chute, "mendanha") == 0)){
        printf("DIGITE A TERCEIRA PALAVRA: ");
        scanf("%s", chute);

            if((strcmp(chute, "CRUZ") == 0) || (strcmp(chute, "cruz") == 0)){
                return 7;
                     
            }
        }
    }
    
return 1;
}


int CHUTE(char vetor_categoria[10][31], int numeros[3]){

    char chute[31];

    printf("DIGITE A PRIMEIRA PALAVRA: ");
    scanf("%s", chute);
    if((strcmp(chute, vetor_categoria[numeros[0]]) == 0) || (strcmp(chute, vetor_categoria[numeros[0]]) == 0)){
        printf("DIGITE A SEGUNDA PALAVRA: ");
        scanf("%s", chute);

        if((strcmp(chute, vetor_categoria[numeros[1]]) == 0) || (strcmp(chute, vetor_categoria[numeros[1]]) == 0)){
        printf("DIGITE A TERCEIRA PALAVRA: ");
        scanf("%s", chute);

            if((strcmp(chute, vetor_categoria[numeros[2]]) == 0) || (strcmp(chute, vetor_categoria[numeros[2]]) == 0)){
                return 7;
                     
            }
        }
    }
printf("\t\t\t\t\t  VOCÊ ERROU!!!\n\n");    
return 3;
}


void rodaroda(PLAYER melhores_roda[11]){

    char DEUSA[3][31] = {"M A R I A N A", "M E N D A N H A", "C R U Z"},
         deusa[3][31] = {"_ _ _ _ _ _ _", "_ _ _ _ _ _ _ _", "_ _ _ _"},

         ANIMAL[10][31] = {"Q U A T I", "J A G U A T I R I C A", "T A R T A R U G A", "F E R R E T", "T A M A N D U A", "C A L O P S I T A", "B A B U I N O", "O R A N G O T A N G O", "C O A L A", "V E S P A"},
         animal[10][31] = {"_ _ _ _ _", "_ _ _ _ _ _ _ _ _ _ _", "_ _ _ _ _ _ _ _ _", "_ _ _ _ _ _", "_ _ _ _ _ _ _ _", "_ _ _ _ _ _ _ _ _", "_ _ _ _ _ _ _", "_ _ _ _ _ _ _ _ _ _ _", "_ _ _ _ _", "_ _ _ _ _"},
         A_CHUTE[10][31] = {"QUATI", "JAGUATIRICA", "TARTARUGA", "FERRET", "TAMANDUA", "CALOPSITA", "BABUINO", "ORANGOTANGO", "COALA", "VESPA"}, 
         
         COR[10][31] = {"O C R E", "M A R A V I L H A", "M A G E N T A", "C I A N O", "L A R A N J A", "V E R M E L H O", "D O U R A D O", "A R D O S I A", "C I T R I N O", "N Y A N Z A"},
         cor[10][31] = {"_ _ _ _", "_ _ _ _ _ _ _ _ _", "_ _ _ _ _ _ _", "_ _ _ _ _", "_ _ _ _ _ _ _", "_ _ _ _ _ _ _ _", "_ _ _ _ _ _ _", "_ _ _ _ _ _ _", "_ _ _ _ _ _ _", "_ _ _ _ _ _"},
         C_CHUTE[10][31] = {"OCRE", "MARAVILHA", "MAGENTA", "CIANO", "LARANJA", "VERMELHO", "DOURADO", "ARDOSIA", "CITRINO", "NYANZA"},
         
         PAIS[10][31] = {"D J I B O U T I", "A F E G A N I S T A O", "A R G E N T I N A", "S R I L A N K A", "A C R E", "M O N G O L I A", "C A T A R", "B U T A O", "G U A T E M A L A", "L I S T E S N T A I N E"},
         pais[10][31] = {"_ _ _ _ _ _ _ _", "_ _ _ _ _ _ _ _ _ _ _", "_ _ _ _ _ _ _ _ _", "_ _ _ _ _ _ _ _", "_ _ _ _", "_ _ _ _ _ _ _ _", "_ _ _ _ _", "_ _ _ _ _", "_ _ _ _ _ _ _ _ _", "_ _ _ _ _ _ _ _ _ _ _ _"},
         P_CHUTE[10][31] = {"DJIBOUTI", "AFEGANISTAO", "ARGENTINA", "SRILANKA", "ACRE", "MONGOLIA", "CATAR", "BUTAO", "GUATEMALA", "LISTENSTAINE"};

    
    char P1, P2;

    int i, j;
    int categoria;
    int numeros[3];
    int ganhou=0, aux=0, sec=0;
    int P1_points=0, P2_points=0;

    srand(time(NULL));
    

    for (i = 0; i < 3; ++i){

        numeros[i] = abs(rand() % 10);

        if(i > 0){
            while(numeros[1] == numeros[0]){
                    numeros[i] = abs(rand() % 10);
            }
            if(i > 1){
                
                while(numeros[0] == numeros[2]){
                        numeros[i] = abs(rand() % 10);
                }
                while(numeros[1] == numeros[2]){
                        numeros[i] = abs(rand() % 10);
                }
            }
        }
        
    }

    printf("      _..._                                                                          _..._          \n");                            
    printf("    .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
    printf("   :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
    printf("   :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
    printf("   `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
    printf("     `':..-'                                                                        `-..:''         \n\n\n");

    printf(" ______________________________________________________________________________________________ \n");
    printf("|                                                                                              |\n");
    printf("|    VOCÊ FOI CHAMADO PARA PARTICIPAR DE UM PROGRAMA DE AUDITÓRIO                              |\n"); 
    printf("|    E TEM A CHANCE DE GANHAR MUITO DINHEIRO.                                                  |\n");
    printf("|    TUDO QUE VOCÊ TEM QUE FAZER É ACERTAR 3 PALAVRAS QUE ESÃO DENTRO DE UMA MESMA CATEGORIA,  |\n"); 
    printf("|    O ÚNICO PROBLEMA É QUE VOCÊ NÃO É O ÚNICO QUE POSSUI A CHANCE DE GANHAR,                  |\n");
    printf("|    SEU MELHOR AMIGO TAMBÉM FOI CHAMADO PARA PARTICIPAR.                                      |\n");
    printf("|    AMBOS PRECISAM DO DINHEIRO,                                                               |\n"); 
    printf("|    JOGUE COM ESTRATÉGIA, QUEM ACERTAR MAIS LETRAS GANHA MAIS PONTOS,                         |\n");
    printf("|    SE VOCÊ ERRAR UMA LETRA, PERDE METADE DE SEUS PONTOS,                                     |\n");
    printf("|    SE VOCÊ ACHAR QUE SABE AS 3 PALAVRAS, VOCÊ PODE TENTAR A SORTE,                           |\n");
    printf("|    SE ACERTA-LAS, RECEBERÁ 30 PONTOS E FINALIZARÁ O JOGO COMO CAMPEÃO E MILIONÁRIO,          |\n");
    printf("|    MAS SE ERRAR, PERDE TODOS OS SEUS PONTOS E DÁ A VEZ PARA O OUTRO PARTICIPANTE.            |\n");
    printf("|    VOCÊ PODE ESCOLHER A CATEGORIA QUE ACHAR MELHOR, BOA SORTE.                               |\n");
    printf("|______________________________________________________________________________________________|\n\n");

    printf("\tBem-vindo ao roda a roda,\n");
    printf("\tO jogo é simples, você só precisa acertar 3 palavras.\n");
    printf("\t  -CADA LETRA CERTA VALE 1 PONTO-\n");
    printf("\t  -UMA LETRA NÃO PERTENCENTE AS PALAVRAS FAZ O JOGADOR PERDER METADE DE SEUS PONTOS-\n");
    printf("\t  -É POSSIVEL CHUTAR AS 3 PALAVRAS SEGUIDAS CASO O JOGADOR DIGITE [;](PONTO E VÍRGULA)-\n");
    printf("\t  -O CHUTE DEVE SER FEITO APENAS COM LETRAS MAIÚSCULAS-\n");
    printf("\t  -SE O CHUTE FOR ERRADO, O JOGADOR PERDE TODOS OS SEUS PONTOS-\n");
    printf("\t  -SE O CHUTE FOR CORRETO, O JOGADOR GANHA 30 PONTOS E FINALIZA O JOGO-\n");
    printf("\t  -O VENCEDOR É AQUELE COM MAIS PONTOS AO FINAL DO JOGO-\n");
    printf("\t  -O NÍVEL DE DIFICULDADE AUMENTA COM O CRESCIMENTO DAS CATEGORIAS-\n\n");

    printf("ESCOLHA UMA DAS SEGUINTES CATEGORIAS:\n");
    printf("① DEUSA \n");
    printf("② ANIMAL\n");
    printf("③ COR   \n");
    printf("④ PAÍS  \n\n");
    scanf("%d", &categoria);








    if(categoria == 1){
        
        sleep(1);
        system("clear");

        printf("     _..._                                                                          _..._          \n");                            
        printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
        printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
        printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
        printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
        printf("    `':..-'                                                                        `-..:''         \n\n\n");

        printf("CATEGORIA - [DEUSA]\n");
        PLAY(P1_points, P2_points);
         
        for(i = 0; i < 3; ++i){
            printf("\t\t\t\t\t");
            for(j = 0; j < 30; ++j){
                printf("%c", deusa[i][j]);             
            }
            printf("\n");
        }


        do{    

            getchar();
            printf("\nP1:");
            scanf("%c", &P1);
            
            if(P1 == ';'){

                if(CHUTE_DEUSA(P1) == 7){
                    P1_points += 30;
                    melhores_roda[10].pontos += 200;
                    break;
                }
                else if(CHUTE_DEUSA(P1) == 1){
                    P1_points = 0;
                }
                
            }

            sec++;
            propaganda(sec);

            if(sec != 4){
                sleep(1);
                system("clear");
            }else{
                sec = 0;
            }
                

            aux=0;
            for(i = 0; i < 3; ++i){   
                for(j = 0; j < 30; ++j){

                    if(toupper(P1) == DEUSA[i][j]){
                        aux++;
                        if(deusa[i][j] == '_'){
                            P1_points++;
                        }
                        deusa[i][j] = P1;
                    }          
                }              
            }
            
            if(aux == 0){
                P1_points /= 2;
            }                

            printf("     _..._                                                                          _..._          \n");                            
            printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
            printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
            printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
            printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
            printf("    `':..-'                                                                        `-..:''         \n\n\n");

            printf("CATEGORIA - [DEUSA]\n");
            PLAY(P1_points, P2_points);

            for(i = 0; i < 3; ++i){
                printf("\t\t\t\t\t");
                for(j = 0; j < 30; ++j){

                 printf("%c", deusa[i][j]);   
                        
                }
                printf("\n");
            }

            ganhou=0;
            for(i = 0; i < 3; ++i){
                for(j = 0; j < 30; ++j){

                    if(deusa[i][j] == '_'){
                        ganhou++;

                    }

                }

            }

            if(ganhou == 0){
            	melhores_roda[10].pontos += 100;
                break;
            }


            getchar();
            printf("\nP2:");
            scanf("%c", &P2);

            if(P2 == ';'){

                if(CHUTE_DEUSA(P2) == 7){
                    P2_points += 30;
                    melhores_roda[10].pontos += 200;
                    break;
                }
                else if(CHUTE_DEUSA(P2) == 1){
                    P2_points = 0;
                }
                
            }

            sleep(1);
            system("clear");    

            aux=0;
            for(i = 0; i < 3; ++i){   
                for(j = 0; j < 30; ++j){
                
                    if(toupper(P2) == DEUSA[i][j]){
                        aux++;
                        if(deusa[i][j] == '_'){
                            P2_points++;
                        }
                        deusa[i][j] = P2;
                    }                                           
                }                     
            }
            
            if(aux == 0){
                P2_points /= 2;
            }    

            printf("     _..._                                                                          _..._          \n");                            
            printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
            printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
            printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
            printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
            printf("    `':..-'                                                                        `-..:''         \n\n\n");

            printf("CATEGORIA - [DEUSA]\n");
            PLAY(P1_points, P2_points);


            for(i = 0; i < 3; ++i){
                printf("\t\t\t\t\t");
                for(j = 0; j < 30; ++j){

                 printf("%c", deusa[i][j]);   
                        
                }
                printf("\n");
            }

            ganhou=0;
            for(i = 0; i < 3; ++i){
                for(j = 0; j < 30; ++j){

                    if(deusa[i][j] == '_'){
                        ganhou++;

                    }

                }

            }

        }while(ganhou != 0);    

        if(P1_points == P2_points){
            printf("\nHOUVE EMPATE ENTRE OS PLAYERS\n");
        }
        else if(P1_points > P2_points){
            printf("\nPLAYER1 GANHOU COM UMA PONTUAÇÃO DE %d\n", P1_points);
        }
        else{
            printf("\nPLAYER2 GANHOU COM UMA PONTUAÇÃO DE %d\n", P2_points);
        }
        sleep(3);
        system("clear");
        return;
    }









    
    if(categoria == 2){

        sleep(1);
        system("clear");

        printf("     _..._                                                                          _..._          \n");                            
        printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
        printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
        printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
        printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
        printf("    `':..-'                                                                        `-..:''         \n\n\n");

        printf("CATEGORIA - [ANIMAL]\n");
        PLAY(P1_points, P2_points);

        for(i = 0; i < 3; ++i){
            printf("\t\t\t\t\t");
            for(j = 0; j < 30; ++j){
             printf("%c", animal[numeros[i]][j]);              
            }
            printf("\n");
        }



        do{    

            getchar();
            printf("\nP1:");
            scanf("%c", &P1);

            if(P1 == ';'){

                if(CHUTE(A_CHUTE, numeros) == 7){
                	melhores_roda[10].pontos += 1000;
                    P1_points += 30;
                    break;
                }

                P1_points = 0;
            }

            sec++;
            propaganda(sec);

            if(sec != 4){
                sleep(1);
                system("clear");
            }else{
                sec = 0;
            }

            aux=0;
            for(i = 0; i < 3; ++i){   
                for(j = 0; j < 30; ++j){
                
                    if(toupper(P1) == ANIMAL[numeros[i]][j]){
                        aux++;
                        if(animal[numeros[i]][j] == '_'){
                            P1_points++;
                        }
                        animal[numeros[i]][j] = P1;
                    }                         
                }              
            }

            if(aux == 0){
                P1_points /= 2;
            }   

            printf("     _..._                                                                          _..._          \n");                            
            printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
            printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
            printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
            printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
            printf("    `':..-'                                                                        `-..:''         \n\n\n");

            printf("CATEGORIA - [ANIMAL]\n");
            PLAY(P1_points, P2_points);


            for(i = 0; i < 3; ++i){
                printf("\t\t\t\t\t");
                for(j = 0; j < 30; ++j){

                 printf("%c", animal[numeros[i]][j]);   
                        
                }
                printf("\n");
            }

            ganhou=0;
            for(i = 0; i < 3; ++i){
                for(j = 0; j < 30; ++j){
                    if(animal[numeros[i]][j] == '_'){
                        ganhou++;
                    }
                }
            }

            if(ganhou == 0){
            	melhores_roda[10].pontos += 500;
                break;
            }

            getchar();
            printf("\nP2:");
            scanf("%c", &P2);

            if(P2 == ';'){

                if(CHUTE(A_CHUTE, numeros) == 7){
                	melhores_roda[10].pontos += 1000;
                    P2_points += 30;
                    break;
                }
               
                P2_points = 0;   
            }

            sleep(1);
            system("clear"); 

            aux=0;
            for(i = 0; i < 3; ++i){   
                for(j = 0; j < 30; ++j){
                
                    if(toupper(P2) == ANIMAL[numeros[i]][j]){
                        aux++;
                        if(animal[numeros[i]][j] == '_'){
                            P2_points++;
                        }
                        animal[numeros[i]][j] = P2;
                    }                        
                }              
            }

            if(aux == 0){
                P2_points /= 2;
            }   

            printf("     _..._                                                                          _..._          \n");                            
            printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
            printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
            printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
            printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
            printf("    `':..-'                                                                        `-..:''         \n\n\n");

            printf("CATEGORIA - [ANIMAL]\n");
            PLAY(P1_points, P2_points);

            for(i = 0; i < 3; ++i){
                printf("\t\t\t\t\t");
                for(j = 0; j < 30; ++j){

                 printf("%c", animal[numeros[i]][j]);         
                }
                printf("\n");
            }

            ganhou=0;
            for(i = 0; i < 3; ++i){
                for(j = 0; j < 30; ++j){

                    if(animal[numeros[i]][j] == '_'){
                        ganhou++;
                    }
                }
            }

        }while(ganhou != 0);    

        if(P1_points == P2_points){
            printf("\nHOUVE EMPATE ENTRE OS PLAYERS\n");
        }
        else if(P1_points > P2_points){
            printf("\nPLAYER1 GANHOU COM UMA PONTUAÇÃO DE %d\n", P1_points);
        }else{
            printf("\nPLAYER2 GANHOU COM UMA PONTUAÇÃO DE %d\n", P2_points);
        }
        sleep(3);
        system("clear");
        return;
    }







    if(categoria == 3){

        sleep(1);
        system("clear");

        printf("     _..._                                                                          _..._          \n");                            
        printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
        printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
        printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
        printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
        printf("    `':..-'                                                                        `-..:''         \n\n\n");

        printf("CATEGORIA - [COR]\n");
        PLAY(P1_points, P2_points);

        for(i = 0; i < 3; ++i){
            printf("\t\t\t\t\t");
            for(j = 0; j < 30; ++j){
             printf("%c", cor[numeros[i]][j]);              
            }
            printf("\n");
        }



        do{    

            getchar();
            printf("\nP1:");
            scanf("%c", &P1);

            if(P1 == ';'){

                if(CHUTE(C_CHUTE, numeros) == 7){
                	melhores_roda[10].pontos += 2000;
                    P1_points += 30;
                    break;
                }

                P1_points = 0;
            }

            sec++;
            propaganda(sec);

            if(sec != 4){
                sleep(1);
                system("clear");
            }else{
                sec = 0;
            }

            aux=0;
            for(i = 0; i < 3; ++i){   
                for(j = 0; j < 30; ++j){
                
                    if(toupper(P1) == COR[numeros[i]][j]){
                        aux++;
                        if(cor[numeros[i]][j] == '_'){
                            P1_points++;
                        }
                        cor[numeros[i]][j] = P1;
                    }                         
                }              
            }

            if(aux == 0){
                P1_points /= 2;
            }   

            printf("     _..._                                                                          _..._          \n");                            
            printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
            printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
            printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
            printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
            printf("    `':..-'                                                                        `-..:''         \n\n\n");

            printf("CATEGORIA - [COR]\n");
            PLAY(P1_points, P2_points);


            for(i = 0; i < 3; ++i){
                printf("\t\t\t\t\t");
                for(j = 0; j < 30; ++j){

                 printf("%c", cor[numeros[i]][j]);   
                        
                }
                printf("\n");
            }

            ganhou=0;
            for(i = 0; i < 3; ++i){
                for(j = 0; j < 30; ++j){
                    if(cor[numeros[i]][j] == '_'){
                        ganhou++;
                    }
                }
            }

            if(ganhou == 0){
            	melhores_roda[10].pontos += 1000;
                break;
            }

            getchar();
            printf("\nP2:");
            scanf("%c", &P2);

            if(P2 == ';'){

                if(CHUTE(C_CHUTE, numeros) == 7){
                	melhores_roda[10].pontos += 2000;
                    P2_points += 30;
                    break;
                }

                P2_points = 0;
            }

            sleep(1);
            system("clear"); 

            aux=0;
            for(i = 0; i < 3; ++i){   
                for(j = 0; j < 30; ++j){
                
                    if(toupper(P2) == COR[numeros[i]][j]){
                        aux++;
                        if(cor[numeros[i]][j] == '_'){
                            P2_points++;
                        }
                        cor[numeros[i]][j] = P2;
                    }                        
                }              
            }

            if(aux == 0){
                P2_points /= 2;
            }   

            printf("     _..._                                                                          _..._          \n");                            
            printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
            printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
            printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
            printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
            printf("    `':..-'                                                                        `-..:''         \n\n\n");

            printf("CATEGORIA - [COR]\n");
            PLAY(P1_points, P2_points);

            for(i = 0; i < 3; ++i){
                printf("\t\t\t\t\t");
                for(j = 0; j < 30; ++j){

                 printf("%c", cor[numeros[i]][j]);         
                }
                printf("\n");
            }

            ganhou=0;
            for(i = 0; i < 3; ++i){
                for(j = 0; j < 30; ++j){

                    if(cor[numeros[i]][j] == '_'){
                        ganhou++;
                    }
                }
            }

        }while(ganhou != 0);    

        if(P1_points == P2_points){
            printf("\nHOUVE EMPATE ENTRE OS PLAYERS\n");
        }
        else if(P1_points > P2_points){
            printf("\nPLAYER1 GANHOU COM UMA PONTUAÇÃO DE %d\n", P1_points);
        }else{
            printf("\nPLAYER2 GANHOU COM UMA PONTUAÇÃO DE %d\n", P2_points);
        }
        sleep(3);
        system("clear");
        return;

    }







    if(categoria == 4){

        sleep(1);
        system("clear");

        printf("     _..._                                                                          _..._          \n");                            
        printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
        printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
        printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
        printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
        printf("    `':..-'                                                                        `-..:''         \n\n\n");

        printf("CATEGORIA - [PAÍS]\n");
        PLAY(P1_points, P2_points);

        for(i = 0; i < 3; ++i){
            printf("\t\t\t\t\t");
            for(j = 0; j < 30; ++j){
             printf("%c", pais[numeros[i]][j]);              
            }
            printf("\n");
        }



        do{    

            getchar();
            printf("\nP1:");
            scanf("%c", &P1);

            if(P1 == ';'){

                if(CHUTE(P_CHUTE, numeros) == 7){
                	melhores_roda[10].pontos += 25000;
                    P1_points += 30;
                    break;
                }

                P1_points = 0;
            }

            sec++;
            propaganda(sec);

            if(sec != 4){
                sleep(1);
                system("clear");
            }else{
                sec = 0;
            }

            aux=0;
            for(i = 0; i < 3; ++i){   
                for(j = 0; j < 30; ++j){
                
                    if(toupper(P1) == PAIS[numeros[i]][j]){
                        aux++;
                        if(pais[numeros[i]][j] == '_'){
                            P1_points++;
                        }
                        pais[numeros[i]][j] = P1;
                    }                         
                }              
            }

            if(aux == 0){
                P1_points /= 2;
            }   

            printf("     _..._                                                                          _..._          \n");                            
            printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
            printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
            printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
            printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
            printf("    `':..-'                                                                        `-..:''         \n\n\n");

            printf("CATEGORIA - [PAÍS]\n");
            PLAY(P1_points, P2_points);


            for(i = 0; i < 3; ++i){
                printf("\t\t\t\t\t");
                for(j = 0; j < 30; ++j){

                 printf("%c", pais[numeros[i]][j]);   
                        
                }
                printf("\n");
            }

            ganhou=0;
            for(i = 0; i < 3; ++i){
                for(j = 0; j < 30; ++j){
                    if(pais[numeros[i]][j] == '_'){
                        ganhou++;
                    }
                }
            }

            if(ganhou == 0){
            	melhores_roda[10].pontos += 10000;
                break;
            }

            getchar();
            printf("\nP2:");
            scanf("%c", &P2);

            if(P2 == ';'){

                if(CHUTE(P_CHUTE, numeros) == 7){
                	melhores_roda[10].pontos += 25000;
                    P2_points += 30;
                    break;
                }

                P2_points = 0;
            }

            sleep(1);
            system("clear"); 

            aux=0;
            for(i = 0; i < 3; ++i){   
                for(j = 0; j < 30; ++j){
                
                    if(toupper(P2) == PAIS[numeros[i]][j]){
                        aux++;
                        if(pais[numeros[i]][j] == '_'){
                            P2_points++;
                        }
                        pais[numeros[i]][j] = P2;
                    }                        
                }              
            }

            if(aux == 0){
                P2_points /= 2;
            }   

            printf("     _..._                                                                          _..._          \n");                            
            printf("   .::'   `.   ____  _____  ____    __        __      ____  _____  ____    __     .'   `::.        \n");                              
            printf("  :::       : (  _ \\(  _  )(  _ \\  /__\\      /__\\    (  _ \\(  _  )(  _ \\  /__\\   :       :::\n");                                     
            printf("  :::       :  )   / )(_)(  )(_) )/(__)\\    /(__)\\    )   / )(_)(  )(_) )/(__)\\  :       :::    \n");                           
            printf("  `::.     .' (_)\\_)(_____)(____/(__)(__)  (__)(__)  (_)\\_)(_____)(____/(__)(__) `.     .::'     \n");                      
            printf("    `':..-'                                                                        `-..:''         \n\n\n");

            printf("CATEGORIA - [PAÍS]\n");
            PLAY(P1_points, P2_points);

            for(i = 0; i < 3; ++i){
                printf("\t\t\t\t\t");
                for(j = 0; j < 30; ++j){

                 printf("%c", pais[numeros[i]][j]);         
                }
                printf("\n");
            }

            ganhou=0;
            for(i = 0; i < 3; ++i){
                for(j = 0; j < 30; ++j){

                    if(pais[numeros[i]][j] == '_'){
                        ganhou++;
                    }
                }
            }

        }while(ganhou != 0);    

        if(P1_points == P2_points){
            printf("\nHOUVE EMPATE ENTRE OS PLAYERS\n");
        }
        else if(P1_points > P2_points){
            printf("\nPLAYER1 GANHOU COM UMA PONTUAÇÃO DE %d\n", P1_points);
        }else{
            printf("\nPLAYER2 GANHOU COM UMA PONTUAÇÃO DE %d\n", P2_points);
        }
        sleep(3);
        system("clear");
        return;
    }
        
    else{
        if(scanf("%d",&categoria) == 0){
            usleep(90000);
            system("clear");
            getchar();  
            rodaroda(melhores_roda);  
        }
        usleep(90000);
        system("clear");
        rodaroda(melhores_roda);
    }
        
}         


int compara_players(const void *a, const void *b){

	PLAYER *A = (PLAYER *) a;
	PLAYER *B = (PLAYER *) b;

	if(A->pontos == B->pontos){

		return strcmp(A->nick, B->nick);
	
	}

	else{

		return(B->pontos - A->pontos);

	}

}









const char *readLine(FILE *file) {

    if (file == NULL) {
        printf("Error: file pointer is null.");
        exit(1);
    }

    int maximumLineLength = 128;
    char *lineBuffer = (char *)malloc(sizeof(char) * maximumLineLength);

    if (lineBuffer == NULL) {
        printf("Error allocating memory for line buffer.");
        exit(1);
    }

    char ch = getc(file);
    int count = 0;

    while ((ch != '\n') && (ch != EOF)) {
        if (count == maximumLineLength) {
            maximumLineLength += 128;
            lineBuffer = realloc(lineBuffer, maximumLineLength);
            if (lineBuffer == NULL) {
                printf("Error reallocating space for line buffer.");
                exit(1);
            }
        }
        lineBuffer[count] = ch;
        count++;

        ch = getc(file);
    }

    lineBuffer[count] = '\0';
    char line[count + 1];
    strncpy(line, lineBuffer, (count + 1));
    free(lineBuffer);
    const char *constLine = line;
    return constLine;
}