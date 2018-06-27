// Alunos	: Ramon Ferreira
// Matrícula: UC14100797

/*
SINTESE
Objetivo: Desenvolver um programa para realizar o cadastro de atletas que participarão das Olimíadas de 2020.
Entrada	: País, número de identificação do atleta e sua idade.
Saída	: Quantidade de atletas, e suas devidas informações em um arquivo de nome atletaOlimp.txt.
*/

/* Bibliotecas */
#include <stdio.h>
#include <string.h>

/* MACRO */
#define MAX_ATLETAS 10 //2000
#define TAM_PAIS 10
#define VLRMIN_ID 9
#define VLRMAX_ID 10000
#define VLRMIN_IDADE 12
#define VLRMAX_IDADE 40
#define MSG_ERRO "\n\n*** Entrada invalida! ***\n\n"

/* Structs */
struct Atleta{
	char pais[TAM_PAIS];
	int idAtleta, idade;
};

/* Prtótipos das Funções & Procedimentos */
void gravarDadosAtletas(struct Atleta *atletas, int qtdAtletas);
void consultaAtletas(char *msg, struct Atleta *atletas, int qtdAtletas);
void ordenaAtletas(struct Atleta *atletas, int qtdAtletas);
void verificaIdRepetido(char *msgErro, struct Atleta *atletas, int posicaoMax, int *validaRepetido);
void leValidaOpcao(char *msg, char *opcaoUsuario, char *opcoes);
void leValidaString(char *msg, char *msgErro, char *string, int tamString);
void leValidaInt(char *msg, char *msgErro, int *numero, int vlrMin, int vlrMax);


int main(){
// Declarações
	struct Atleta atletas[MAX_ATLETAS];
	int contQtdAtletas, validaRepetido, validaInteracao;
	char opcaoUsuario;
// Inicializações
	for(contQtdAtletas = 0; contQtdAtletas < MAX_ATLETAS; contQtdAtletas++){
		strcpy(atletas[contQtdAtletas].pais, "\0");
		atletas[contQtdAtletas].idAtleta = 0;
		atletas[contQtdAtletas].idade = 0;
	}
	contQtdAtletas = 0;
// Instruções
	do{
		opcaoUsuario = '\0';
		system("cls");
		printf("**** OLIMPIADAS 2020 ***\n");
		printf("------------------------\n\n");
		leValidaString("Primeiro, informe o pais do atleta: ", MSG_ERRO, atletas[contQtdAtletas].pais, TAM_PAIS);
		do{
			validaRepetido = 0;
			leValidaInt("Agora, informe o codido de identificacao do atleta: ", MSG_ERRO, &atletas[contQtdAtletas].idAtleta, VLRMIN_ID, VLRMAX_ID);
			verificaIdRepetido("\n\n*** Esse ID ja existe! ***\n\n", atletas, contQtdAtletas, &validaRepetido);
		}while(validaRepetido == 1);
		leValidaInt("E por ultimo, informe a idade: ", MSG_ERRO, &atletas[contQtdAtletas].idade, VLRMIN_IDADE, VLRMAX_IDADE);
		contQtdAtletas++;
		printf("\n\nQtd. atletas: %i\n\n", contQtdAtletas);
		leValidaOpcao("Deseja continuar[S/N]? ", &opcaoUsuario, "SN");
	}while(opcaoUsuario == 'S' && contQtdAtletas < MAX_ATLETAS);
	
	ordenaAtletas(atletas, contQtdAtletas);
	
	do{
		validaInteracao = 1;
		opcaoUsuario = '\0';
		system("cls");
		printf("*** GERENCIADOS DE ATLETAS - OLIMPIADAS 2020 ****\n");
		printf("-------------------------------------------------\n\n");
		printf("[C] - Consultar atletas\n");
		printf("[G] - Gravar dados em arquivo\n");
		printf("[X] - Encerrar programa...\n\n");
		printf("Qtd. atletas: %i\n\n", contQtdAtletas);
		leValidaOpcao("Seleciona uma opcao acima[C/G/X]: ", &opcaoUsuario, "CGX");
		switch(opcaoUsuario){
			case 'C':
				system("cls");
				consultaAtletas("*** Consultar Atletas ***\n-------------------------\n\n", atletas, contQtdAtletas);
				getch();
				break;
			case 'G':
				system("cls");
				gravarDadosAtletas(atletas, contQtdAtletas);
				getch();
				break;
			default:
				validaInteracao = 0;
		}
	}while(validaInteracao == 1);
		
	return 0;
}

/* Funções & Procedimentos */

//Objetivo	: Gravar todos os dados de atletas em arquivo de nome atletasOlimp.txt
//Parâmetros: Referência a um ponteiro de struct do tipo Atleta e a quantidade de atletas. 
//Retorno	: ***
void gravarDadosAtletas(struct Atleta *atletas, int qtdAtletas){
	FILE *pArquivoAtletas;
	char opcaoUsuario, nomeArquivoAtletas[] = "atletasOlimp.txt";
	int contQtdAtletas, somaIdades;;

	opcaoUsuario = '\0';
	if((pArquivoAtletas = fopen(nomeArquivoAtletas, "r")) == NULL){
		if((pArquivoAtletas = fopen(nomeArquivoAtletas, "w")) == NULL){
			printf("\n*** Falha ao abrir o arquivo %s! ***\n", nomeArquivoAtletas);
			fclose(pArquivoAtletas);
			return;
		}else{
			printf("\n*** Arquivo %s criado com sucesso! ***\n", nomeArquivoAtletas);
		}
	}else{
		leValidaOpcao("*** O arquivo ja existe no diretorio, deseja sobrescrevelo[S/N]? ", &opcaoUsuario, "SN");
		if(opcaoUsuario == 'S'){
			if((pArquivoAtletas = fopen(nomeArquivoAtletas, "w")) == NULL){
				printf("\n*** Falha ao abrir o arquivo %s! ***\n", nomeArquivoAtletas);
				fclose(pArquivoAtletas);
				return;
			}else{
				printf("\n*** Arquivo %s criado com sucesso! ***\n", nomeArquivoAtletas);
			}
		}else{
			fclose(pArquivoAtletas);
			return;
		}
	}
	
	fprintf(pArquivoAtletas, "+--------+----------+-------+\n");
	fprintf(pArquivoAtletas, "|  Pais  | idAtleta | Idade |\n");
	fprintf(pArquivoAtletas, "+--------+----------+-------+\n");
	for(contQtdAtletas = 0; contQtdAtletas < qtdAtletas; contQtdAtletas++){
		fprintf(pArquivoAtletas, "|%-8s|%-10.i|%-7.i|\n", atletas[contQtdAtletas].pais, atletas[contQtdAtletas].idAtleta, atletas[contQtdAtletas].idade);
		fprintf(pArquivoAtletas, "+--------+----------+-------+\n");
		somaIdades = somaIdades + atletas[contQtdAtletas].idade;
	}
	fprintf(pArquivoAtletas, "\n\nMedia de todas as idades: %i ", (somaIdades/qtdAtletas));
	printf("\n\n*** Dados gravados com sucesso no arquivo %s! ***\n\n", nomeArquivoAtletas);
	
	fclose(pArquivoAtletas);
}

//Objetivo	: Consultar todos os atletas cadastrados.
//Parâmetros: Referência a um vetor de caraceteres, um ponteiro de struct do tipo Atleta e a quantidade de atletas.
//Retorno	: ***
void consultaAtletas(char *msg, struct Atleta *atletas, int qtdAtletas){
	int contQtdAtletas, somaIdades = 0, contQtdAtletasPais = 0;
	char pesquisaPais[TAM_PAIS];
	
	printf(msg);
	leValidaString("Informe o codigo do pais que deseja buscar: ", MSG_ERRO, pesquisaPais, TAM_PAIS);
	printf("+--------+----------+-------+\n");
	printf("|  Pais  | idAtleta | Idade |\n");
	printf("+--------+----------+-------+\n");
	for(contQtdAtletas = 0; contQtdAtletas < qtdAtletas; contQtdAtletas++){
		if(stricmp(pesquisaPais , atletas[contQtdAtletas].pais) == 0){
			printf("|%-8s|%-10.i|%-7.i|\n", atletas[contQtdAtletas].pais, atletas[contQtdAtletas].idAtleta, atletas[contQtdAtletas].idade);
			printf("+--------+----------+-------+\n");
			somaIdades = somaIdades + atletas[contQtdAtletas].idade;
			contQtdAtletasPais++;
		}
	}
	printf("\n\nMedia das idade do pais %s: %i", pesquisaPais, (somaIdades/contQtdAtletasPais));
}

//Objetivo	: Ordenar um vetor de struct do tipo Atleta.
//Parâmetros: Referência a um ponteiro de struct do tipo Atleta e a quantidade de atletas cadastrados.
//Retorno	: ***
void ordenaAtletas(struct Atleta *atletas, int qtdAtletas){
	int contQtdAtletas, contQtdAux;
	struct Atleta swapAtleta;
	
	for(contQtdAux = 0; contQtdAux < qtdAtletas; contQtdAux++){
		for(contQtdAtletas = (contQtdAux+1); contQtdAtletas < qtdAtletas; contQtdAtletas++){
			if(atletas[contQtdAux].idade > atletas[contQtdAtletas].idade){
				swapAtleta = atletas[contQtdAux];
				atletas[contQtdAux] = atletas[contQtdAtletas];
				atletas[contQtdAtletas] = swapAtleta;
			}
		}
	}
}

//Objetivo	: Verificar se há um número identificador repetido.
//Parâmetros: Referência a um vetor de caracteres, struct Atleta, a posição máxima a ser verificada e a flag para validar o número repetido.
//Retorno	: ***
void verificaIdRepetido(char *msgErro, struct Atleta *atletas, int posicaoMax, int *validaRepetido){
	int contQtdAtletas;
	
	for(contQtdAtletas = 0; contQtdAtletas < posicaoMax; contQtdAtletas++){
		if(atletas[posicaoMax].idAtleta == atletas[contQtdAtletas].idAtleta){
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
//Parâmetros: Referência a dois vetores de caracteres, a string a ser validada e o seu tamanho.
//Retorno	: ***
void leValidaString(char *msg, char *msgErro, char *string, int tamString){
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
		if(strlen(string) > tamString){
			printf(msgErro);
		}else{
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
		}
	}while(validaString == 1);
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
