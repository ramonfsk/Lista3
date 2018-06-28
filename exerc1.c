#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOMELOCATARIO 30
#define VLRMIN_ID 0
#define VLRMAX_ID 1000
#define VLRMIN_ATRASADO 0
#define VLRMAX_ATRASADO 10000
#define MSG_ERRO "\n\n*** Entrada invalida! ***\n\n"

typedef struct Locatario{
	int idLocatario;
	char nomeLocatario[TAM_NOMELOCATARIO];
	float valorAtrasado;
}tLocatario;

void apresentaLocatarios(tLocatario *pLocatarios, int *qtdLocatarios);
void pesquisaLocatario(tLocatario *pLocatarios,int *qtdLocatarios);
void cadastraLocatario(tLocatario *pLocatarios, int *qtdLocatarios);
void leValidaNumRepetido(tLocatario *pLocatario, int qtdLocatarios, int *validaRepetido);
void leValidaOpcao(char *msg, char *opcaoUsuario, char *opcoes);
void leValidaString(char *msg, char *msgErro, char *string, int tipoString);
void leValidaFloat(char *msg, char *msgErro, float *numero, float vlrMin, float vlrMax);
void leValidaInt(char *msg, char *msgErro, int *numero, int vlrMin, int vlrMax);

int main(){
//Declarações
	int qtdLocatarios, validaInteracao;
	char escolhaDoUsuario;
	tLocatario *pLocatarios;
//Inicializações
	qtdLocatarios = 0;
	pLocatarios = NULL;
//Instruções
	if((pLocatarios = (tLocatario*) calloc(1, sizeof(tLocatario))) == NULL){
		printf("\n*** ERRO AO ALOCAR MEMORIA! ****\n\n");
		free(pLocatarios);
		getch();
		exit(1);
	}

	do{
		validaInteracao = 1;
		escolhaDoUsuario = '\0';
		system("cls");
		printf("*** GERENCIADOR DE LOCATARIOS ***\n\n");
		printf("---------------------------------\n");
		printf("Qtd. Locatarios: %d\n\n", qtdLocatarios);
		printf("[A] - Cadastrar Locatario\n");
		printf("[B] - Pesquisar Locatario\n");
		printf("[C] - Apresentar Locatarios\n");
		printf("[X] - Encerrar programa...\n\n");
		leValidaOpcao("Selecione uma opcao[A/B/C/X]: ", &escolhaDoUsuario, "ABCX");
		switch(escolhaDoUsuario){
			case 'A':
				cadastraLocatario(pLocatarios, &qtdLocatarios);
				break;
			case 'B':
				if(qtdLocatarios == 0){
					printf("\n*** Nao ha locatarios cadastrados no sistema! ***\n\n");
					getch();					
				}else{
					pesquisaLocatario(pLocatarios, &qtdLocatarios);
					getch();
				}
				break;
			case 'C':
				if(qtdLocatarios == 0){
					printf("\n*** Nao ha locatarios cadastrados no sistema! ***\n\n");
					getch();	
				}else{
					apresentaLocatarios(pLocatarios, &qtdLocatarios);
					getch();
				}
				break;
			default:
				validaInteracao = 0;
				free(pLocatarios);
		}
	}while(validaInteracao == 1);
	
	return 0;
}

void cadastraLocatario(tLocatario *pLocatarios, int *qtdLocatarios){
	int validaNumero;
	char escolhaDoUsuario;
	
	do{
		escolhaDoUsuario = '\0';
		system("cls");
		printf("*** CADASTRO DE LOCATARIOS ***\n");
		printf("------------------------------\n\n");
		do{
			validaNumero = 0;
			leValidaInt("Informe o ID do locatario: ", MSG_ERRO, &pLocatarios[*qtdLocatarios].idLocatario, VLRMIN_ID, VLRMAX_ID);
			leValidaNumRepetido(pLocatarios, *qtdLocatarios, &validaNumero);
			if(validaNumero == 1){
				printf("\n*** O ID %i ja esta cadastrado! ***\n\n", pLocatarios[*qtdLocatarios].idLocatario);
			}
		}while(validaNumero == 1);
		leValidaString("\nAgora, o nome do locatario: ", MSG_ERRO, pLocatarios[*qtdLocatarios].nomeLocatario, 1);
		leValidaFloat("\nE por ultimo, inform o valor em atraso: R$ ", MSG_ERRO, &pLocatarios[*qtdLocatarios].valorAtrasado, VLRMIN_ATRASADO, VLRMAX_ATRASADO);
		leValidaOpcao("\nDeseja cadastrar mais um locatario[S/N]? ", &escolhaDoUsuario, "SN");
		(*qtdLocatarios)++;
		if(escolhaDoUsuario == 'S'){
			pLocatarios = (tLocatario*) realloc(pLocatarios, ((*qtdLocatarios)+1) * sizeof(tLocatario));
			printf("\n\nRealocando os dados.");
			sleep(1);
			printf(".");
			sleep(1);
			printf(".OK!");
			sleep(1);
		}else{
			printf("\n\nGravando os dados.");
			sleep(1);
			printf(".");
			sleep(1);
			printf(".OK!");
			sleep(1);
		}
	}while(escolhaDoUsuario == 'S');
}

void pesquisaLocatario(tLocatario *pLocatarios,int *qtdLocatarios){
	int contQtdLocatarios, pesquisaId, validaPesquisa;
	
	system("cls");
	printf("*** PESQUISA LOCATARIO ***\n");
	printf("--------------------------\n\n");
	leValidaInt("Informe o ID que deseja pesquisar: ", MSG_ERRO, &pesquisaId, VLRMIN_ID, VLRMAX_ID);
	for(contQtdLocatarios = 0; contQtdLocatarios < *qtdLocatarios; contQtdLocatarios++){
		if(pesquisaId == pLocatarios[contQtdLocatarios].idLocatario){
			printf("\n+----+--------------------+--------------+\n");
			printf("| ID |        Nome        | Valor R$     |\n");
			printf("+----+--------------------+--------------+\n");
			printf("|%-4.i|%-20s| R$ %-10.2f|\n", 
			pLocatarios[contQtdLocatarios].idLocatario, pLocatarios[contQtdLocatarios].nomeLocatario, pLocatarios[contQtdLocatarios].valorAtrasado);
			printf("+----+--------------------+--------------+\n");
			validaPesquisa = 0;
			break;
		}else{
			validaPesquisa = 1;
			break;
		}
	}
	if(validaPesquisa == 1){
		printf("\n\n*** Nao ha registro com o ID %i informado! ***\n\n", pesquisaId);
	}
}

//Objetivo	: Apresentar todos os locatarios.
//Parâmetros: Referência a um vetor de caracteres, nome da corretora, struct Locatario e quantidade de locatarios.
//Retorno	: ***
void apresentaLocatarios(tLocatario *pLocatarios, int *qtdLocatarios){
	int contQtdLocatarios;
	
	system("cls");
	system("cls");
	printf("*** APRESENTA LOCATARIOS ***\n");
	printf("----------------------------\n\n");
	printf("+----+--------------------+--------------+\n");
	printf("| ID |        Nome        | Valor R$     |\n");
	printf("+----+--------------------+--------------+\n");
	for(contQtdLocatarios = 0; contQtdLocatarios < *qtdLocatarios; contQtdLocatarios++){
		printf("|%-4.i|%-20s| R$ %-10.2f|\n", 
		pLocatarios[contQtdLocatarios].idLocatario, pLocatarios[contQtdLocatarios].nomeLocatario, pLocatarios[contQtdLocatarios].valorAtrasado);
		printf("+----+--------------------+--------------+\n");
	}
}

void leValidaNumRepetido(tLocatario *pLocatarios, int qtdLocatarios, int *validaRepetido){
	int contQtd;
	
	for(contQtd = 0; contQtd < qtdLocatarios; contQtd++){
		if(pLocatarios[qtdLocatarios].idLocatario == pLocatarios[contQtd].idLocatario){
			*validaRepetido = 1;
			break;
		}
	}
}

//Objetivo	: Ler e validar opção do usuário.
//Parâmetros: Referência a três vetores de caracteres, sendo eles a opção desejada a as disponíveis.
//Retorno	: ***
void leValidaOpcao(char *msg, char *opcaoUsuario, char *opcoes){
	unsigned int contQtdChars, validaOpcoes, validaScanf;
	
	do{
		do{
			validaOpcoes = 1;
			validaScanf = 1;
			fflush(stdin);
			printf(msg);
			validaScanf = scanf(" %c", opcaoUsuario);
			if(validaScanf != 1){
				printf("\n\n*** Leitura invalida! ***\n");
			}
		}while(validaScanf != 1);
		*opcaoUsuario = toupper(*opcaoUsuario);
		for(contQtdChars = 0; contQtdChars < strlen(opcoes); contQtdChars++){
			if(*opcaoUsuario == opcoes[contQtdChars]){
				validaOpcoes = 0;
				break;
			}
		}
	}while(validaOpcoes == 1);
}

//Objetivo	: Ler e validar uma string.
//Parâmetros: Referência a dois vetores de caracteres, a string a ser validada, o seu tamanho e o tipo de string(0 - Qualquer, 1 - Nome).
//Retorno	: ***
void leValidaString(char *msg, char *msgErro, char *string, int tipoString){
	unsigned int contQtdChars, contQtdEspacos, validaString, validaScanf;
	
	do{
		validaString = 1;
		contQtdEspacos = 0;
		do{
			fflush(stdin);
			printf(msg);
			if(tipoString == 0){
				validaScanf = scanf("%[^\n]s", string);
			}else{
				validaScanf = scanf("%[a-zA-Z ][^\n]s", string);
			}
		}while(validaScanf != 1);

		for(contQtdChars = 0; contQtdChars < (strlen(string)-1); contQtdChars++){
			if(string[contQtdChars] == ' '){
				contQtdEspacos++;
			}
		}
		if(contQtdEspacos == (strlen(string))){
			printf("\n\n*** String em branco! ***\n");
		}else{
			validaString = 0;
		}
	}while(validaString == 1);
}

//Objetivo	: Ler a validar um número real.
//Parâmetros: Referência a dois vetores de caracteres, o número e seus limites.
//Retorno	: ***
void leValidaFloat(char *msg, char *msgErro, float *numero, float vlrMin, float vlrMax){
	unsigned int validaScanf;
	
	do{
		do{
			fflush(stdin);
			printf(msg);
			validaScanf = scanf("%f", numero);
		}while(validaScanf != 1);
		if(*numero < vlrMin || *numero > vlrMax){
			printf(msgErro);
		}
	}while(*numero < vlrMin || *numero > vlrMax);
}

//Objetivo	: Ler a validar um número inteiro.
//Parâmetros: Referência a dois vetores de caracteres, o número e seus limites.
//Retorno	: ***
void leValidaInt(char *msg, char *msgErro, int *numero, int vlrMin, int vlrMax){
	unsigned int validaScanf;
	
	do{
		do{
			fflush(stdin);
			printf(msg);
			validaScanf = scanf("%i", numero);
		}while(validaScanf != 1);
		if(*numero < vlrMin || *numero > vlrMax){
			printf(msgErro);
		}
	}while(*numero < vlrMin || *numero > vlrMax);
}
