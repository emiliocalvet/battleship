#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void iniciar_tabuleiro           (void);
void preenche_matriz             (void);
void posicionar_navios           (void);
void resultado                   (void);
int  dar_tiro_jogador1	         (void);
int  dar_tiro_jogador2	         (void);
void pause                       (void);
void menu                        (void);
void instrucoes                  (void);
void creditos                    (void);
void multiplayer                 (void);
void solo			 (void);
void jogador 			 (void);
void submarino_horizontal        (void);
void submarino_vertical          (void);
void contratorpedeiro_horizontal (void);
void contratorpedeiro_vertical   (void);
void navio_tanque_horizontal     (void);
void navio_tanque_vertical       (void);
void porta_avioes_horizontal     (void);
void porta_avioes_vertical       (void);
int  escolhe_coluna_jogador1     (void);
int  escolhe_coluna_jogador2     (void);
void escolhe_linha_jogadores     (void);
void navio_abatido_jogador1      (void);
void navio_abatido_jogador2      (void);
void pontuacao_vencedor1         (void);
void pontuacao_vencedor2         (void);

int  matriz_principal [10][10];
int  matriz_secundaria[10][10];

int quantidade_navios = 0;                    //Variavel que controla quantidade de navios na função posicionar navios.
int numero_jogadas1 = 1, numero_jogadas2 = 1; //Variaveis que contam jogadas do jogador 1 e 2.
int pontuacao1 = 0, pontuacao2 = 0;           //Variaveis que contam os pontos do jogador 1 e 2.
int limite_jogadas = 0;                       //Variavel que determina a quantidade de jogadas que os jogadores terão.
int numero_linha = 0, numero_coluna = 0;      //Variaveis que determinam a linha e a coluna que deseja dar o tiro.
int acertos1 = 0, acertos2 = 0;               //Variaveis que contam a quantidade de acertos do jogador 1 e 2.
int tiro_agua1 = 0, tiro_agua2 = 0;           //Variavel que conta a quantidade de tiros na agua do jogador 1 e 2.
int verificador_saida = 0;                    //Variavel usada pra verificar saida para menu no meio do jogo.
int cont_tiro = 0;                            //Contador compartilhado.

//Codigo do programa inicia aqui.

int main(void){

	menu ();

return 0;
}

//Código do programa termina aqui.

void iniciar_tabuleiro(void){//Função para preencher o layout do tabuleiro.

	int  i,j;
	int  linhas [10] = {1,2,3,4,5,6,7,8,9,10};
	char letras [10] = {'A','B','C','D','E','F','G','H', 'I', 'J'};

	printf("\n\n\t\t\t\t\t");

		for(i = 0; i < 10; i++)
			printf("%c\t",letras[i]);

		printf("\n\n");

		for(i = 0; i < 10; i++){
			printf("\t\t\t\t%d\t", linhas[i]);
		
			for(j = 0; j < 10; j++)
				if(matriz_principal[i][j] == 1)
					printf("[?]\t");
				else
					if(matriz_principal[i][j] == 0)//Água
						printf("[X]\t");
					else
						if(matriz_principal[i][j] == -1)//Submarino.
							printf("[S]\t");
						else
							if(matriz_principal[i][j] == -2)//Contratorpedeiro.
								printf("[C]\t");
							else
								if(matriz_principal[i][j] == -3)//Navio_Tanque.
									printf("[T]\t");
								else
									if(matriz_principal[i][j] == -4)//Porta Aviões.
										printf("[P]\t");
			printf("\n\n");
		}
	printf("\t\t\t\t ___________________________________________________________________________________ \n");
	printf("\t\t\t\t|      |               |                      |                  |                  |\n");	
	printf("\t\t\t\t|  [X] | [S] Submarino | [C] Contratorpedeiro | [T] Navio Tanque | [P] Porta Avioes |\n");
	printf("\t\t\t\t| Agua |    Tamanho 2  |       Tamanho 3      |     Tamanho 4    |      Tamanho 5   |\n");        
	printf("\t\t\t\t|______|_______________|______________________|__________________|__________________|\n");
	printf("\t\t\t\t      Digite a letra [M] como coluna para retornar ao [MENU PRINCIPAL] do jogo.      \n");	
}

void preenche_matriz(void){	//Função para preencher a matriz com 1.

	int i,j;

	for(i = 0; i < 10; i++)
		for(j = 0; j < 10; j++){
			matriz_principal[i][j] = 1;
            matriz_secundaria[i][j] = 0;
		}
}

void posicionar_navios(void){ //Função para colocar os navios no jogo.
	
	int randomico;

	for(quantidade_navios = 0; quantidade_navios < 4; quantidade_navios++){ //Gerando 4 Submarinos.
		randomico = (1 + (rand() % 2));

		switch (randomico){

			case 1: submarino_horizontal();
				break;
			case 2: submarino_vertical();
				break;
		}
	}

	for(quantidade_navios = 0; quantidade_navios < 3; quantidade_navios++){ //Gerando 3 Contratorpedeiros.
		randomico = (1 + (rand() % 2));

		switch (randomico){

			case 1: contratorpedeiro_horizontal();
				break;
			case 2: contratorpedeiro_vertical();
				break;
		}
	}

	for(quantidade_navios = 0; quantidade_navios < 2; quantidade_navios++){ //Gerando 2 Navio Tanque.
		randomico = (1 + (rand() % 2));

		switch (randomico){

			case 1: navio_tanque_horizontal();
				break;
			case 2: navio_tanque_vertical  ();
				break;
		}
	}

	for(quantidade_navios = 0; quantidade_navios < 1; quantidade_navios++){ //Gerando 1 Porta Aviões.
		randomico = (1 + (rand() % 2));

		switch (randomico){

			case 1: porta_avioes_horizontal();
				break;
			case 2: porta_avioes_vertical  ();
				break;
		}
	}
}

int dar_tiro_jogador1(void){//Função que faz escolha da posição e realiza contagem de pontos, jogadas e acertos do jogador 1.
	
	int escolha = 2;

	for(cont_tiro = 0; cont_tiro < 1; cont_tiro++){

		system("clear");
		iniciar_tabuleiro();		
		verificador_saida = escolhe_coluna_jogador1();

		if(verificador_saida == 1)
			break;

		escolhe_linha_jogadores();
			
		if(matriz_principal[numero_linha][numero_coluna] != 1)
			escolha = 1;
				
		switch(escolha){
				
			case 1:printf("\n\n\t\t\t\tPosicao ja foi escolhida anteriormente. Aperte enter e tente novamente!");
				   pause();
				   escolha = 2;
				   cont_tiro--;
			break;
				
			case 2:numero_jogadas1++;
				   limite_jogadas++;
				   matriz_principal[numero_linha][numero_coluna] = matriz_secundaria[numero_linha][numero_coluna];
				   navio_abatido_jogador1();
			break;
		}		
	}
	return verificador_saida;
}

int dar_tiro_jogador2(void){//Função que faz escolha da posição e realiza contagem de pontos, jogadas e acertos do jogador 2.

	int escolha = 2;
	
	for(cont_tiro = 0; cont_tiro < 1; cont_tiro++){

		system("clear");
		iniciar_tabuleiro();
		verificador_saida = escolhe_coluna_jogador2();

		if(verificador_saida == 1)
			break;

		escolhe_linha_jogadores();			

		if(matriz_principal[numero_linha][numero_coluna] != 1)
			escolha = 1;
				
		switch(escolha){
				
			case 1:printf("\n\n\t\t\t\tPosicao ja foi escolhida anteriormente. Aperte enter e tente novamente!");
				   pause();
				   escolha = 2;
				   cont_tiro--;
			break;
				
			case 2:numero_jogadas2++;
				   limite_jogadas++;

				   matriz_principal[numero_linha][numero_coluna] = matriz_secundaria[numero_linha][numero_coluna];
				   navio_abatido_jogador2();
			break;
		}	
	}
	return verificador_saida;
}

void resultado(void){//Função que carrega a matriz secundaria para mostrar todos os navios.

	int i, j;

		for(i = 0; i < 10; i++)
			for(j = 0; j < 10; j++)
				matriz_principal[i][j] = matriz_secundaria[i][j];
}

void pause(void){//Função que pausa o programa.

	setbuf(stdin,NULL);
	getchar();
}

void menu(void){//Função com as opções do jogo.

	int escolha;

	while(escolha != 4){
	
		system("clear");
		
		printf("\n\n\n\n\n\n\n\n\n\n");

		puts("\t\t\t\t\t __________________________________________________________________ ");
		puts("\t\t\t\t\t| **************************************************************** |");
		puts("\t\t\t\t\t| ************************* BATALHA NAVAL ************************ |");
		puts("\t\t\t\t\t| **************************************************************** |");
		puts("\t\t\t\t\t|                         [1] Jogar                                |");
		puts("\t\t\t\t\t|                         [2] Instrucoes                           |");
		puts("\t\t\t\t\t|                         [3] Creditos                             |");
		puts("\t\t\t\t\t|                         [4] Sair                                 |");
		puts("\t\t\t\t\t|__________________________________________________________________|");

		printf("\n\n\t\t\t\t\tDigite a opcao desejada:");
		scanf("%d", &escolha);		
		
		switch (escolha){
			case 1:
				jogador();
				break;
			case 2:
				instrucoes();
				break;
			case 3:
				creditos();
				break;
			case 4:
				printf("Bye!\n");
				break;
			default:
				printf("\n\n\t\t\t\t\tOpcao invalida. Aperte enter e tente novamente!");
				pause();	
		}	
	}
}

void instrucoes(void){//Função que mostra as instruções do jogo.

	system("clear");

	printf("\n\n\n\n\n\n\n");
	
	puts("\t\t\t\t\t _________________________________________________________________ ");
	puts("\t\t\t\t\t| *************************************************************** |");
	puts("\t\t\t\t\t| ************************* Instrucoes ************************** |");
	puts("\t\t\t\t\t| *************************************************************** |");
	puts("\t\t\t\t\t|                                                                 |");
	puts("\t\t\t\t\t|     Batalha naval consiste em afundar todas as embarcacoes      |");
	puts("\t\t\t\t\t|                     presentes no tabuleiro.                     |");
	puts("\t\t\t\t\t|                                                                 |");
	puts("\t\t\t\t\t|    Sao disponiveis 16 jogadas no modo 1 Jogador e 32 jogadas    |");
	puts("\t\t\t\t\t|                      no modo 2 Jogadores.                       |");
	puts("\t\t\t\t\t|                                                                 |");
	puts("\t\t\t\t\t|    As jogadas nao sao dividas igualmente, tera vantagem quem    |");
	puts("\t\t\t\t\t|     acertar o maior numero de navios, pois a vez do jogador     |");
	puts("\t\t\t\t\t|          so passa quando o mesmo errar as embarcacoes.          |");
	puts("\t\t\t\t\t|                                                                 |");
	puts("\t\t\t\t\t|      Escolha a letra da coluna e precione enter, em seguida     |");
	puts("\t\t\t\t\t|   escolha o numero da linha e precione enter. O tabuleiro ira   |");
	puts("\t\t\t\t\t| atualizar automaticamente, mostrando o desenvolvimento do jogo. |");
	puts("\t\t\t\t\t|_________________________________________________________________|");

	printf("\n\n\t\t\t\t\tPressione enter para voltar ao menu.");
	pause();
}

void creditos(void){//Função que mostra os integrantes da equipe.

	system("clear");

	printf("\n\n\n\n\n\n\n");

	puts("\t\t\t\t\t __________________________________________________________ ");
    puts("\t\t\t\t\t| *********************** Creditos *********************** |");
    puts("\t\t\t\t\t|                                                          |");
    puts("\t\t\t\t\t|                       Emilio Calvet                      |");
    puts("\t\t\t\t\t|__________________________________________________________|");

    printf("\n\n\t\t\t\t\tPressione enter para voltar ao menu.");
	pause();
}

void jogador(void){//Função que permite selecionar a quantidade de jogadores.

	int escolha;

	for(int i = 0; i < 1; i++){

		system("clear");

		printf("\n\n\n\n\n\n\n\n\n\n");

		puts("\t\t\t\t\t ________________________________________________________________ ");
		puts("\t\t\t\t\t| ************************** Modalidade ************************ |");
		puts("\t\t\t\t\t|                                                                |");
		puts("\t\t\t\t\t|                       [1] Solo (1 Jogador)                     |");
		puts("\t\t\t\t\t|                                                                |");
		puts("\t\t\t\t\t|                   [2] Multiplayer (2 Jogadores)                |");
		puts("\t\t\t\t\t|________________________________________________________________|");

		printf("\n\n\t\t\t\t\tDigite a opcao desejada:");
		scanf("%d", &escolha);

		switch (escolha){

		case 1: solo();
			break;
		case 2: multiplayer();
			break;
		default:
			printf("\n\n\t\t\t\t\tOpcao invalida. Aperte enter e tente novamente!");
			pause();
			i--;	
		}
	}
}

void solo(void){//Função onde o jogo roda no modo 1 jogador.
		
	limite_jogadas = 0;
	numero_jogadas1 = 1;
	tiro_agua1 = 0;
	acertos1 = 0;
	pontuacao1 = 0;
	verificador_saida = 0;

	preenche_matriz();
	posicionar_navios();

	while(limite_jogadas < 16){
		
		system("clear");

		iniciar_tabuleiro();
		verificador_saida = dar_tiro_jogador1();
		if(verificador_saida == 1)
			break;	
	}

	if(verificador_saida == 0){
		system("clear");	
		pontuacao_vencedor1();
	}
}

void multiplayer(void){//Função onde o jogo roda no modo 2 jogadores.
	
	limite_jogadas = 0;
	numero_jogadas1 = 1;	
	numero_jogadas2 = 1;
	tiro_agua1 = 0;
	tiro_agua2 = 0;
	acertos1 = 0;
	acertos2 = 0;
	pontuacao1 = 0;
	pontuacao2 = 0;
	verificador_saida = 0;

	preenche_matriz  ();
	posicionar_navios();

	while(limite_jogadas < 32){
			
		system("clear");

		iniciar_tabuleiro();
		verificador_saida  = dar_tiro_jogador1();

		if(verificador_saida == 1)
			break;
		

		verificador_saida = dar_tiro_jogador2();

		if(verificador_saida == 1)
			break;
	}

	if(verificador_saida == 0){
		system("clear");	
		pontuacao_vencedor2();
	}
}

void submarino_horizontal(void){//Função para gerar submarino na horizontal.

	int linha, coluna;

		linha = rand() % 10;      
		coluna = rand() % 8;
			
		if(matriz_secundaria[linha][coluna] == 0 && matriz_secundaria[linha][coluna+1] == 0){

			for(int i = 0; i < 2; i++){
				matriz_secundaria[linha][coluna] =- 1;
				coluna++;
			}
		}
			else
				quantidade_navios--;
}

void submarino_vertical(void){//Função para gerar submarino na vertical.

	int linha, coluna;

		linha = rand() % 8;      
	  	coluna = rand() % 10;

		if(matriz_secundaria[linha][coluna] == 0 && matriz_secundaria[linha+1][coluna] == 0){

			for(int i = 0; i < 2; i++){
				matriz_secundaria[linha][coluna] =- 1;
				linha++;
			}
		}
			else
				quantidade_navios--;
}

void contratorpedeiro_horizontal(void){//Função para gerar contratorpedeiro na horizontal.

	int linha, coluna;

		linha = rand() % 10;      
		coluna = rand() % 7;
				
		if(matriz_secundaria[linha][coluna] == 0 && matriz_secundaria[linha][coluna+1] == 0 && matriz_secundaria[linha][coluna+2] == 0){

			for(int i = 0; i < 3; i++){
				matriz_secundaria[linha][coluna] =- 2;
				coluna++;
			}
		}
			else
				quantidade_navios--;
}

void contratorpedeiro_vertical(void){//Função para gerar contratorpedeiro na vertical.

	int linha, coluna;

		linha = rand() % 7;      
		coluna = rand() % 10;

		if(matriz_secundaria[linha][coluna] == 0 && matriz_secundaria[linha+1][coluna] == 0 && matriz_secundaria[linha+2][coluna] == 0){

			for(int i = 0; i < 3; i++){
				matriz_secundaria[linha][coluna] =- 2;
				linha++;
			}
		}
			else
				quantidade_navios--;
}

void navio_tanque_horizontal(void){//Função para gerar navio tanque na horizontal.

	int linha, coluna;

		linha = rand()%10;      
		coluna = rand()%6;
				
		if(matriz_secundaria[linha][coluna] == 0 && matriz_secundaria[linha][coluna+1] == 0 && matriz_secundaria[linha][coluna+2] == 0
		&& matriz_secundaria[linha][coluna+3] == 0){

			for(int i = 0; i < 4; i++){
				matriz_secundaria[linha][coluna] =- 3;
				coluna++;
			}
		}
			else
				quantidade_navios--;
}

void navio_tanque_vertical(void){//Função para gerar navio tanque na vertical.

	int linha, coluna;

		linha = rand() % 6;      
		coluna = rand() % 10;

		if(matriz_secundaria[linha][coluna] == 0 && matriz_secundaria[linha+1][coluna] == 0 && matriz_secundaria[linha+2][coluna] == 0
		&& matriz_secundaria[linha+3][coluna] == 0){

			for(int i = 0; i < 4; i++){
				matriz_secundaria[linha][coluna] =- 3;
				linha++;
			}
		}
			else
				quantidade_navios--;
}

void porta_avioes_horizontal(void){//Função para gerar porta aviões na horizontal.

	int linha, coluna;
	
		linha = rand() % 10;      
		coluna = rand() % 5;
				
		if(matriz_secundaria[linha][coluna] == 0 && matriz_secundaria[linha][coluna+1] == 0 && matriz_secundaria[linha][coluna+2] == 0
		&& matriz_secundaria[linha][coluna+3] == 0 && matriz_secundaria[linha][coluna+4] == 0){

			for(int i = 0; i < 5; i++){
				matriz_secundaria[linha][coluna] =- 4;
				coluna++;
			}
		}
			else
				quantidade_navios--;
}

void porta_avioes_vertical(void){//Função para gerar porta aviões na horizontal.

	int linha, coluna;

		linha = rand() % 5;      
		coluna = rand() % 10;

		if(matriz_secundaria[linha][coluna] == 0 && matriz_secundaria[linha+1][coluna] == 0 && matriz_secundaria[linha+2][coluna] == 0
		&& matriz_secundaria[linha+3][coluna] == 0 && matriz_secundaria[linha+4][coluna] == 0){

			for(int i = 0; i < 5; i++){
				matriz_secundaria[linha][coluna] =- 4;
				linha++;
			}
		}
			else
				quantidade_navios--;
}

int escolhe_coluna_jogador1(void){//Função que obtem a coluna do tiro do jogador 1.
	
	char letra;

	for(int i = 0; i < 1; i++){
		printf("\n\n\t\t\t\t(Jogador 1 | %2da jogada) Digite a letra da coluna: ", numero_jogadas1);
		scanf(" %c", &letra);
		setbuf(stdin,NULL);

		switch(letra){

			case 'A':
				numero_coluna = 0;
				return 0;
			case 'a':
				numero_coluna = 0;
				return 0;
			case 'B':
				numero_coluna = 1;
				return 0;
			case 'b':
				numero_coluna = 1;
				return 0;
			case 'C':
				numero_coluna = 2;
				return 0;
			case 'c':
				numero_coluna = 2;
				return 0;
			case 'D':
				numero_coluna = 3;
				return 0;
			case 'd':
				numero_coluna = 3;
				return 0;
			case 'E':
				numero_coluna = 4;
				return 0;
			case 'e':
				numero_coluna = 4;
				return 0;
			case 'F':
				numero_coluna = 5;
				return 0;
			case 'f':
				numero_coluna = 5;
				return 0;
			case 'G':
				numero_coluna = 6;
				return 0;
			case 'g':
				numero_coluna = 6;
				return 0;
			case 'H':
				numero_coluna = 7;
				return 0;
			case 'h':
				numero_coluna = 7;
				return 0;
			case 'I':
				numero_coluna = 8;
				return 0;
			case 'i':
				numero_coluna = 8;
				return 0;
			case 'J':
				numero_coluna = 9;
				return 0;
			case 'j':
				numero_coluna = 9;
				return 0;
			case 'M':
				return 1;
			case 'm':
				return 1;
			default:
				printf("\n\n\t\t\t\tLetra digitada incorreta, Pressione enter e tente novamente!");
				i--;
				pause();
				system("clear");
				iniciar_tabuleiro();
				return 0;
		}
	}
}

int escolhe_coluna_jogador2(void){//Função que obtem a coluna do tiro do jogador 2.

	char letra;

	for(int i = 0; i < 1; i++){
		printf("\n\n\t\t\t\t(Jogador 2 | %2da jogada) Digite a letra da coluna: ", numero_jogadas2);
		scanf(" %c", &letra);
		setbuf(stdin,NULL);

		switch(letra){

			case 'A':
				numero_coluna = 0;
				return 0;
			case 'a':
				numero_coluna = 0;
				return 0;
			case 'B':
				numero_coluna = 1;
				return 0;
			case 'b':
				numero_coluna = 1;
				return 0;
			case 'C':
				numero_coluna = 2;
				return 0;
			case 'c':
				numero_coluna = 2;
				return 0;
			case 'D':
				numero_coluna = 3;
				return 0;
			case 'd':
				numero_coluna = 3;
				return 0;
			case 'E':
				numero_coluna = 4;
				return 0;
			case 'e':
				numero_coluna = 4;
				return 0;
			case 'F':
				numero_coluna = 5;
				return 0;
			case 'f':
				numero_coluna = 5;
				return 0;
			case 'G':
				numero_coluna = 6;
				return 0;
			case 'g':
				numero_coluna = 6;
				return 0;
			case 'H':
				numero_coluna = 7;
				return 0;
			case 'h':
				numero_coluna = 7;
				return 0;
			case 'I':
				numero_coluna = 8;
				return 0;
			case 'i':
				numero_coluna = 8;
				return 0;
			case 'J':
				numero_coluna = 9;
				return 0;
			case 'j':
				numero_coluna = 9;
				return 0;
			case 'M':
				return 1;
			case 'm':
				return 1;
			default:
				printf("\n\n\t\t\t\tLetra digitada incorreta, Aperte enter e tente novamente!");
				i--;
				pause();
				system("clear");
				iniciar_tabuleiro();
				return 0;
		}
	}							
}

void escolhe_linha_jogadores(void){//Função que obtem a linha do tiro de ambos os jogadores.
	
	for(int i = 0; i < 1; i++){
		printf("\n\n\t\t\t\tDigite o numero da linha:");
		scanf("%d", &numero_linha);
		if(numero_linha < 1 || numero_linha > 10){
			printf("\n\n\t\t\t\tNumero digitado incorreto, Aperte enter e tente novamente!");
			i--;
			pause();
			system("clear");
			iniciar_tabuleiro();
		}
	}numero_linha--;//Linhas da matriz começão do 0, não do 1.	
}

void navio_abatido_jogador1(void){//Função para mosrar qual navio abatido e calcular pontuação do jogador 1.

	if(matriz_secundaria[numero_linha][numero_coluna] != 0){
		acertos1++;

		if(matriz_secundaria[numero_linha][numero_coluna] == -1){
			system("clear");
			iniciar_tabuleiro();
			printf("\n\n\t\t\t\tVoce acertou um Submarino. Aperte enter para continuar!");
			cont_tiro--;
			pontuacao1 += 8;
			pause();
		}
		else
			if(matriz_secundaria[numero_linha][numero_coluna] == -2){
				system("clear");
				iniciar_tabuleiro();
				printf("\n\n\t\t\t\tVoce acertou um Contratorpedeiro. Aperte enter para continuar!");
				cont_tiro--;
				pontuacao1 += 12; 
				pause();
			}
			else
				if(matriz_secundaria[numero_linha][numero_coluna] == -3){
					system("clear");
					iniciar_tabuleiro();
					printf("\n\n\t\t\t\tVoce acertou um Navio Tanque. Aperte enter para continuar!");
					cont_tiro--;
					pontuacao1 += 16;
					pause();
				}
				else
					if(matriz_secundaria[numero_linha][numero_coluna] == -4){
						system("clear");
						iniciar_tabuleiro();
						printf("\n\n\t\t\t\tVoce acertou um Porta Avioes. Aperte enter para continuar!");
						cont_tiro--;
						pontuacao1 += 20;
						pause();
					}	
	}
	else{
		system("clear");
		iniciar_tabuleiro();
		printf("\n\n\t\t\t\tTiro na agua. Aperte enter para continuar!");
		tiro_agua1++;	
		pause();
	}
}

void navio_abatido_jogador2(void){//Função para mostrar qual navio abatido e calcular pontuação do jogador 2.

	if(matriz_secundaria[numero_linha][numero_coluna] != 0){
		acertos2++;

		if(matriz_secundaria[numero_linha][numero_coluna] == -1){
			system("clear");
			iniciar_tabuleiro();
			printf("\n\n\t\t\t\tVoce acertou um Submarino. Aperte enter para continuar!");
			cont_tiro--;
			pontuacao2 += 8;
			pause();
		} 
		else
			if(matriz_secundaria[numero_linha][numero_coluna] == -2){
				system("clear");
				iniciar_tabuleiro();
				printf("\n\n\t\t\t\tVoce acertou um Contratorpedeiro. Aperte enter para continuar!");
				cont_tiro--;
				pontuacao2 += 12;
				pause();
			}
			else
				if(matriz_secundaria[numero_linha][numero_coluna] == -3){
					system("clear");
					iniciar_tabuleiro();
					printf("\n\n\t\t\t\tVoce acertou um Navio Tanque. Aperte enter para continuar!");
					cont_tiro--;
					pontuacao2 += 16;
					pause();
				}
				else
					if(matriz_secundaria[numero_linha][numero_coluna] == -4){
						system("clear");
						iniciar_tabuleiro();
						printf("\n\n\t\t\t\tVoce acertou um Porta Avioes. Aperte enter para continuar!");
						cont_tiro--;
						pontuacao2 += 20;
						pause();
					}
	}
	else{
		system("clear");
		iniciar_tabuleiro();
		printf("\n\n\t\t\t\tTiro na agua. Aperte enter para continuar!");
		tiro_agua2++;
		pause();
	}
}

void pontuacao_vencedor1(void){//Função que mostra a pontuação no final do jogo solo.
	
	int escolha;
	
	system("clear");

	printf("\n\n\n\n\n\n\n");
	
	  puts("\t\t\t\t\t _________________________________________________________ ");
	  puts("\t\t\t\t\t|*********************************************************|");
	  puts("\t\t\t\t\t|********************** FIM DE JOGO **********************|");
	  puts("\t\t\t\t\t|*********************************************************|");
	  puts("\t\t\t\t\t|                                                         |");
	printf("\t\t\t\t\t|                   Pontuacao-----> %4d                  |\n",pontuacao1);
	printf("\t\t\t\t\t|                   Acertos-------> %4d                  |\n",acertos1);
	printf("\t\t\t\t\t|                   Tiros na Agua-> %4d                  |\n",tiro_agua1); 
	  puts("\t\t\t\t\t|_________________________________________________________|");
	  
	printf("\n\n\t\t\t\t\tPressione enter para voltar ao menu.");
	pause();
}

void pontuacao_vencedor2(void){//Função que mostra a pontuação no final do jogo multiplayer.
	
	system("clear");

	printf("\n\n\n\n\n\n\n");
	
	puts("\t\t\t\t _________________________________________________________________________________ ");
	puts("\t\t\t\t|*********************************************************************************|");
	puts("\t\t\t\t|********************************* FIM DE JOGO ***********************************|");
	puts("\t\t\t\t|*********************************************************************************|");
	puts("\t\t\t\t|                                       |                                         |");
	puts("\t\t\t\t|              [JOGADOR 1]              |              [JOGADOR 2]                |");
	puts("\t\t\t\t|                                       |                                         |");
	printf("\t\t\t\t|          Pontuação-----> %4d         |          Pontuacao-----> %4d           |\n",pontuacao1, pontuacao2);
	printf("\t\t\t\t|          Acertos-------> %4d         |          Acertos-------> %4d           |\n",acertos1, acertos2);
	printf("\t\t\t\t|          Tiros na Agua-> %4d         |          Tiros na Agua-> %4d           |\n",tiro_agua1, tiro_agua2);
	puts("\t\t\t\t|_______________________________________|_________________________________________|");

	printf("\n\n\t\t\t\tPressione enter para voltar ao menu.");
	pause();	  
}
