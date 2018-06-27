// Aluno	: Ramon Ferreira
// Matrícula: UC14100797

/*
SINTESE
Objetivo: Elaborar um programa para gerenciar um locatório de uma agência de imóveis.
Entrada	: Nome da corretora, cadastramento de id, nome e valor do locatário.
Saída	: ***
*/

/* Bibliotecas */
#include <stdio.h>
#include <string.h>

/* MACRO */
#define MAX_REGISTROS 10
#define TAM_NOMELOCATARIO 60
#define TAM_NOMECORRETORA 60
#define MSG_ERRO "\n\n*** Entrada invalida! ***\n\n"

/*  Structs */
struct Locatario{
	int idLocatario;
	char nomeLocatario[TAM_NOMELOCATARIO];
	float valorAtrasado;
};

/* Protótipos das Funções & Procedimentos */
void excluirLocatario(char *msg, char *nomeCorretora, struct Locatario *locatarios, int *qtdLocatarios);
void pesquisaLocatario(char *msg, char *nomeCorretora, struct Locatario *locatarios, int qtdLocatarios);
void apresentaLocatarios(char *msg, char *nomeCorretora, struct Locatario *locatarios, int qtdLocatarios);
void cadastraLocatorio(char *msg, struct Locatario *locatarios, int *qtdLocatarios);
void ordenaLocatarios(struct Locatario *locatarios, int qtdLocatarios);
void verificaIdRepetido(char *msgErro, struct Locatario *locatarios, int posicaoMax, int *validaRepetido);
void leValidaOpcao(char *msg, char *opcaoUsuario, char *opcoes);
void leValidaString(char *msg, char *msgErro, char *string);
void leValidaFloat(char *msg, char *msgErro, float *numero, float vlrMin, float vlrMax);
void leValidaInt(char *msg, char *msgErro, int *numero, int vlrMin, int vlrMax);

int main(){
// Declarações
	struct Locatario locatarios[MAX_REGISTROS];
	int contQtdLocatarios, validaInteracao;
	char nomeCorretora[TAM_NOMECORRETORA], opcaoUsuario;
// Inicialização
	for(contQtdLocatarios = 0; contQtdLocatarios < MAX_REGISTROS; contQtdLocatarios++){
		locatarios[contQtdLocatarios].idLocatario = 0;
		strcpy(locatarios[contQtdLocatarios].nomeLocatario, "\0");
		locatarios[contQtdLocatarios].valorAtrasado = 0.0;
	}
	contQtdLocatarios = 0;
// Instruções
	leValidaString("Informe o nome da corretora: ", MSG_ERRO, nomeCorretora);
	do{
		validaInteracao = 1;
		opcaoUsuario = '\0';
		system("cls");
		printf("*** GERENCIADOR DE LOCATARIOS ***\n\n");
		printf("---------------------------------\n");
		printf("Empresa: %s\n\n", nomeCorretora);
		printf("[A] - Cadastrar Locatarios\n");
		printf("[B] - Pesquisar Locatario\n");
		printf("[C] - Apresentar Locatarios\n");
		printf("[D] - Excluir Locatario\n");
		printf("[X] - Encerrar programa...\n\n");
		printf("Qtd. Locatarios: %d\n\n", contQtdLocatarios);
		leValidaOpcao("Selecione uma opcao[A/B/C/D/X]: ", &opcaoUsuario, "ABCDX");
		switch(opcaoUsuario){
			case 'A':
				cadastraLocatorio("*** Cadastro de Locatarios ***\n------------------------------\n\n", locatarios, &contQtdLocatarios);
				break;
			case 'B':
				if(contQtdLocatarios > 0){
					pesquisaLocatario("*** Pesquisa de Locatario ***\n-----------------------------\n\n", nomeCorretora, locatarios, contQtdLocatarios);
					getch();
				}else{
					printf("\n\n*** Sem registro de locatarios! ***\n\n");
					getch();
				}
				break;
			case 'C':
				if(contQtdLocatarios > 0){
					apresentaLocatarios("*** Apresenta Locatarios ***\n----------------------------\n\n", nomeCorretora, locatarios, contQtdLocatarios);
					getch();
				}else{
					printf("\n\n*** Sem registro de locatarios! ***\n\n");
					getch();
				}
				break;
			case 'D':
				if(contQtdLocatarios > 0){
					excluirLocatario("*** Excluir Locatarios ***\n--------------------------\n\n", nomeCorretora, locatarios, &contQtdLocatarios);
				}else{
					printf("\n\n*** Sem registro de locatarios! ***\n\n");
					getch();
				}
				break;
			default:
				validaInteracao = 0;
		}
	}while(validaInteracao == 1);

	return 0;
}

/* Funções & Procedimentos */

//Objetivo	: Excluir um locatario da listagem.
//Parâmetros: Referência a uma vetor de caracteres, nome da corretora, struct Locatario e quantidade de locatarios.
//Retorno	: ***
void excluirLocatario(char *msg, char *nomeCorretora, struct Locatario *locatarios, int *qtdLocatarios){
	int contQtdLocatarios, escolhaId, validaId;
	char opcaoUsuario;
	
	
	do{
		do{
			validaId = 1;
			system("cls");
			printf(msg);
			apresentaLocatarios("", nomeCorretora, locatarios, *qtdLocatarios);
			leValidaInt("\nConforme listagem acima, qual locatario deseja excluir[ID]? ", MSG_ERRO, &escolhaId, 0, 100);
			for(contQtdLocatarios = 0; contQtdLocatarios < *qtdLocatarios; contQtdLocatarios++){
				if(escolhaId == locatarios[contQtdLocatarios].idLocatario){
					validaId = 0;
					break;
				}
			}
			if(validaId == 1){
				printf("\n\n*** Id invalido! ***\n\n");
				getch();
			}
		}while(validaId == 1);
		locatarios[contQtdLocatarios].idLocatario = 0;
		strcpy(locatarios[contQtdLocatarios].nomeLocatario, "\0");
		locatarios[contQtdLocatarios].valorAtrasado = 0.0;
		*qtdLocatarios = (*qtdLocatarios - 1);
		printf("\n\n*** Locatario excluido com sucesso! ***\n\n");
		for(contQtdLocatarios = 0; contQtdLocatarios < *qtdLocatarios; contQtdLocatarios++){
			if(locatarios[contQtdLocatarios].idLocatario == 0){
				locatarios[contQtdLocatarios] = locatarios[contQtdLocatarios+1];
			}
		}
		ordenaLocatarios(locatarios, *qtdLocatarios);
		
		if(*qtdLocatarios > 0){
			leValidaOpcao("\n\nDeseja excluir mais algum locatario[S/N]? ", &opcaoUsuario, "SN");
		}else{
			printf("\n\n*** Nao hoa registros! ***\n\n");
			opcaoUsuario = 'N';
			getch();
		}
	}while(opcaoUsuario == 'S');	

}

//Objetivo	: Pesquisa de locatarios.
//Parâmetros: Referência a uma vetor de caracteres, nome da corretora, struct Locatario e quantidade de locatarios.
//Retorno	: ***
void pesquisaLocatario(char *msg, char *nomeCorretora, struct Locatario *locatarios, int qtdLocatarios){
	int contQtdLocatarios, pesquisaId, validaPesquisa;
	
	system("cls");
	printf(msg);
	printf("Nome da Corretora: %s\n\n", nomeCorretora);
	leValidaInt("Informe o ID que deseja pesquisar: ", MSG_ERRO, &pesquisaId, 0, 100);
	for(contQtdLocatarios = 0; contQtdLocatarios < qtdLocatarios; contQtdLocatarios++){
		if(pesquisaId == locatarios[contQtdLocatarios].idLocatario){
			printf("\n+----+--------------------+--------------+\n");
			printf("| ID |        Nome        | Valor R$     |\n");
			printf("+----+--------------------+--------------+\n");
			printf("|%-4.i|%-20s| R$ %-10.2f|\n", 
			locatarios[contQtdLocatarios].idLocatario, locatarios[contQtdLocatarios].nomeLocatario, locatarios[contQtdLocatarios].valorAtrasado);
			printf("+----+--------------------+--------------+\n");
			validaPesquisa = 0;
			break;
		}else{
			validaPesquisa = 1;
		}
	}
	if(validaPesquisa == 1){
		printf("\n\n*** Nao ha registro com o ID %i informado! ***\n\n", pesquisaId);
	}
}

//Objetivo	: Apresentar todos os locatarios.
//Parâmetros: Referência a um vetor de caracteres, nome da corretora, struct Locatario e quantidade de locatarios.
//Retorno	: ***
void apresentaLocatarios(char *msg, char *nomeCorretora, struct Locatario *locatarios, int qtdLocatarios){
	int contQtdLocatarios;
	
	system("cls");
	printf(msg);
	printf("Nome da Corretora: %s\n\n", nomeCorretora);
	printf("+----+--------------------+--------------+\n");
	printf("| ID |        Nome        | Valor R$     |\n");
	printf("+----+--------------------+--------------+\n");
	for(contQtdLocatarios = 0; contQtdLocatarios < qtdLocatarios; contQtdLocatarios++){
		printf("|%-4.i|%-20s| R$ %-10.2f|\n", 
		locatarios[contQtdLocatarios].idLocatario, locatarios[contQtdLocatarios].nomeLocatario, locatarios[contQtdLocatarios].valorAtrasado);
		printf("+----+--------------------+--------------+\n");
	}
}

//Objetivo	: Cadastrar um locatório.
//Parâmetros: Referência a uma struct do tipo Locatario e a quantidade de locatarios.
//Retorno	: ***
void cadastraLocatorio(char *msg, struct Locatario *locatarios, int *qtdLocatarios){
	int contQtdLocatarios, validaRepetido;
	char opcaoUsuario;
	
	do{
		contQtdLocatarios = 0;
		system("cls");
		printf(msg);
		do{
			validaRepetido = 0;
			leValidaInt("Informe o id: ", MSG_ERRO, &locatarios[*qtdLocatarios].idLocatario, 0, 100);
			verificaIdRepetido("\n\n*** Esse ID ja existe! ***\n\n", locatarios, *qtdLocatarios, &validaRepetido);
		}while(validaRepetido == 1);
		leValidaString("Agora, o nome: ", MSG_ERRO, locatarios[*qtdLocatarios].nomeLocatario);
		leValidaFloat("Por ultimo, informe o valor: R$ ", MSG_ERRO, &locatarios[*qtdLocatarios].valorAtrasado, 0.00, 1000000.00);
		leValidaOpcao("\n\nDeseja continuar cadastrando[S/N]? ", &opcaoUsuario, "SN");
		contQtdLocatarios++;
		*qtdLocatarios = contQtdLocatarios + *qtdLocatarios;
	}while(opcaoUsuario == 'S');
	ordenaLocatarios(locatarios, *qtdLocatarios);
}

//Objetivo	: Ordenar um vetor de struct do tipo Locatario;
//Parâmetros: Referência a um ponteiro de struct do tipo Locatario e a quantidade de Locatarios.
//Retorno	: ***
void ordenaLocatarios(struct Locatario *locatarios, int qtdLocatarios){
	int contQtdLocatarios, contQtdAux;
	struct Locatario swapLocatario;
	
	for(contQtdAux = 0; contQtdAux < qtdLocatarios; contQtdAux++){
		for(contQtdLocatarios = (contQtdAux+1); contQtdLocatarios < qtdLocatarios; contQtdLocatarios++){
			if(locatarios[contQtdAux].idLocatario > locatarios[contQtdLocatarios].idLocatario){
				swapLocatario = locatarios[contQtdAux];
				locatarios[contQtdAux] = locatarios[contQtdLocatarios];
				locatarios[contQtdLocatarios] = swapLocatario;
			}
		}
	}
}

//Objetivo	: Verificar se há um número identificador repetido.
//Parâmetros: Referência a um vetor de caracteres, struct Locatario, a posição máxima a ser verificada e a flag para validar o número repetido.
//Retorno	: ***
void verificaIdRepetido(char *msgErro, struct Locatario *locatarios, int posicaoMax, int *validaRepetido){
	int contQtdLocatarios;
	
	for(contQtdLocatarios = 0; contQtdLocatarios < posicaoMax; contQtdLocatarios++){
		if(locatarios[posicaoMax].idLocatario == locatarios[contQtdLocatarios].idLocatario){
			printf(msgErro);
			*validaRepetido = 1;
			break;
		}
	}
}

//Objetivo	: Ler e validar opção do usuário.
//Parâmetros: Referência a três vetores de caracteres, sendo eles a opção desejada a as disponíveis.
//Retorno	: ***
void leValidaOpcao(char *msg, char *opcaoUsuario, char *opcoes){
	int contQtdChars, validaOpcoes, validaScanf;
	
	do{
		do{
			validaOpcoes = 1;
			validaScanf = 1;
			fflush(stdin);
			printf(msg);
			validaScanf = scanf(" %c", opcaoUsuario);
			if(!validaScanf){
				printf("\n\n*** Leitura invalida! ***\n");
			}
		}while(!validaScanf);
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
//Parâmetros: Referência a dois vetores de caracteres e a string a ser validada.
//Retorno	: ***
void leValidaString(char *msg, char *msgErro, char *string){
	int contQtdChars, contQtdEspacos, validaString, validaScanf;
	
	do{
		do{
			validaScanf = 1;
			validaString = 1;
			fflush(stdin);
			printf(msg);
			validaScanf = scanf("%[a-zA-Z ][^\n]s", string);
			if(!validaScanf){
				printf(msgErro);
			}
		}while(!validaScanf);
		for(contQtdChars = 0; contQtdChars < strlen(string); contQtdChars++){
			if(string[contQtdChars] == ' '){
				contQtdEspacos++;
			}
		}
		if(contQtdEspacos == strlen(string)){
			printf("\n\n*** Nome em branco! ***\n");
		}else{
			validaString = 0;
		}
	}while(validaString == 1);
}

//Objetivo	: Ler a validar um número real.
//Parâmetros: Referência a dois vetores de caracteres, o número e seus limites.
//Retorno	: ***
void leValidaFloat(char *msg, char *msgErro, float *numero, float vlrMin, float vlrMax){
	int validaScanf;
	
	do{
		do{
			validaScanf = 1;
			fflush(stdin);
			printf(msg);
			validaScanf = scanf("%f", numero);
			if(!validaScanf){
				printf(msgErro);
			}
		}while(!validaScanf);
	}while(*numero < vlrMin || *numero > vlrMax);
}

//Objetivo	: Ler a validar um número inteiro.
//Parâmetros: Referência a dois vetores de caracteres, o número e seus limites.
//Retorno	: ***
void leValidaInt(char *msg, char *msgErro, int *numero, int vlrMin, int vlrMax){
	int validaScanf;
	
	do{
		do{
			validaScanf = 1;
			fflush(stdin);
			printf(msg);
			validaScanf = scanf("%i", numero);
			if(!validaScanf){
				printf(msgErro);
			}
		}while(!validaScanf);
	}while(*numero < vlrMin || *numero > vlrMax);
}
