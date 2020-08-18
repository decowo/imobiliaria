//Ari Tedeschi Junior        RA:190075
//Joel Ribeiro Bonfim Junior RA:190304
//Wallace Galli              RA:171850
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct endereco{
	char logradouro[80];
	char bairro[20];
	char CEP[10];
	char cidade[20];
	char estado[20];
	char fone[15];
	char cel[15];
	char email[30];
}endereco;

typedef struct info_casa{
	int  num_casa;
	char status_casa;
}info_casa;

typedef struct prop{
	int              reg_prop; 
	char             nome[80];
	char             CPF[15];
	struct endereco  end_prop;
	int              qtde_casa;
	struct info_casa casa[5]; 
}prop;

typedef struct adress{
	char logradouro[80];
	char bairro[20];
	char CEP[10];
	char cidade[20];
}adress;

typedef struct info_loc{
	char sigla;
	int  reg_loc;
}inf_loc;

union dados{
	char   sigla;
	struct info_loc loc;
};

typedef struct imovel{
	int           reg_imov;
	struct adress end_imov;
	float         area;
	int           quartos;
	float         valor;
	union dados   status;
}imovel;

typedef struct locatario{
	int    reg_loc;
	char   nome[80];
	char   CPF[15];
	struct endereco end_loc;
	int    reg_imov; 
	int    dia_venc;
	char   inicio[9];
	char   termino[9];
}locatario;

void alocOwner(prop **pr,int len);    //Aloca Propriet?o
void alocImovel(imovel **pi,int len); //Aloca Imovel
void alocLoc(locatario **li,int len); //Aloca locataria
int  checkFile(char *flName);         //Fun? que conta quantidade de registros a partir do arquivo informado
char convertUpperCase(char c);        //Fun? que converte caractere para caixa alta retornando-o
int  compareStrings(char *queryA, char *queryB); //Fun? para comparar 2 strings em caixa alta
int  inputFilter(char *strValue, int parameter); //Fun? gen?ca para aplicar filtros complexos em entradas
void ownersWriter(prop *owner, char *operation, int deslocate); //Fun? para atualizar e gravar o arquivo do propriet?o
void locWriter(locatario *loc, char *operation, int deslocate); //Funcao para atualizar e gravar o arquivo do locatario
void immobilesWriter(imovel *immobiles, char *operation, int deslocate); //Fun? para atualizar e gravar o arquivo do imovel
int  ownersSelectBy(prop *owner, int parameter, char *strQuery, int intQuery); //Fun? gen?ca para realizar buscas no arquivo do propriet?o
void ownersShowOff(prop *owner, char cpf); //Fun? para mostrar na tela dados do propriet?o
void LocShowOff(locatario *loc); //Fun? para mostrar na tela dados de todos locatarios
void ownersRegister(prop *owner); //Fun? de cadastro do propriet?o
void locRegister(locatario *loc, imovel *immobiles, prop *owner); //Fun? de cadastro do locatario
void immobilesRegister(imovel *immobiles, prop *owner); //Fun? de cadastro do im??
void ownersSelectAll(prop *owner); //Fun? para mostrar todos propriet?os
void LocSelectAll(locatario *loc); // funcao para monstrar todos locatarios
void OwnersSearchCPF(prop *owner); //Fun? para mostrar propriet?o pelo CPF
void immobilesSearchBed(imovel *immobiles); //Fun? gen?ca para consultar im?? (inclui busca parcial e total)
void immobilesSearchAll(imovel *immobiles, locatario *loc, prop *owner);//Fun? consulta total imoveis
void immobileShowOff(imovel *immobile, char type); //Fun? para mostrar na tela dados do im??
int  immobileSearch(imovel *immobile, int parameter, int queryInt, char* queryStr, char status); //Fun? gen?ca para realizar buscas no arquivo do im??
void rentImmobiles(imovel *immobiles, locatario *loc, prop *owner); // Fun? para alugar im??
int  locSearch(locatario *loc, int parameter, int queryInt, char* strQuery);// Fun? gen?ca para realizar busca por locat?os
void reportSearch(locatario *loc,int parameter, prop *owner, imovel *immobiles);//report dos locatarios
void reportShowOff(locatario *loc,prop *owners,imovel *immobiles);// Fun? para exibir dados do relat??
void shutDownContract(locatario *loc,prop *owners,imovel *immobiles);// Fun? para encerrar contrato
void ownerUpdate(prop *owner);// Fun? para realizar altera?s em propriet?o
void immobileUpdate(imovel *immobile);// Fun? para realizar altera?s em im??
void locUpdate(locatario *loc);// Fun? para realizar altera?s em locatario
void updateData(locatario *loc,prop *owners,imovel *immobiles);// Fun? para realizar altera?s

main(){
	int    op;
	//Ponteiro para propriet?o
	prop   *owners = NULL;
	
	//Ponteiro para im??s
	imovel *immobiles = NULL;
	
	//Ponteiro para locatario
	locatario *loc = NULL;
	
	do{
		printf("\n Menu\n\n [01] - Cadastrar Proprietario\n [02] - Ver todos proprietarios\n [03] - Consultar proprietario pelo CPF\n\n [04] - Cadastrar imovel\n [05] - Buscar imoveis por filtros \n [06] - Visualizar todos imoveis\n [07] - Alugar imovel\n\n [08] - Mostrar todos locatarios\n [09] - Relatorio locatarios\n [10] - Encerrar contrato\n [11] - Alterar dados\n [12] - Sair\n\n Opcao: ");
		scanf("%d",&op);
		fflush(stdin);
		switch(op){
			case 1:
				//Utilizando ponteiros com um espa?- manipula? de arquivo parcial
				alocOwner(&owners,1);
				system("cls");
				ownersRegister(owners); //Cadastro de propriet?o
				free(owners);
				owners=NULL;
			break;
			case 2:
				//Utilizando ponteiros com um espa?- manipula? de arquivo parcial
				alocOwner(&owners,1);
				system("cls");
				ownersSelectAll(owners);//Consulta total de propriet?o
				free(owners);
				owners=NULL;
			break;
			case 3:
				//Utilizando ponteiros com um espa?- manipula? de arquivo parcial
				alocOwner(&owners,1);
				system("cls");
				OwnersSearchCPF(owners);//Consulta parcial de propriet?o
				free(owners);
				owners=NULL;
			break;
			case 4:
				//Utilizando ponteiros com um espa?- manipula? de arquivo parcial
				alocOwner(&owners,1);
				alocImovel(&immobiles,1);
				system("cls");
				immobilesRegister(immobiles,owners);//Cadastro de im??s
				free(owners);
				free(immobiles);
				owners=NULL;
				immobiles=NULL;
			break;
			case 5: 
				//Utilizando ponteiros com um espa?- manipula? de arquivo parcial
				alocImovel(&immobiles,1);
				system("cls");
				immobilesSearchBed(immobiles);//Consulta parcial de im??s
				system("pause");
				system("cls");
				free(immobiles);
				immobiles=NULL;
			break;
			case 6: 
				//Utilizando ponteiros com um espa?- manipula? de arquivo parcial
				alocOwner(&owners,1);
				alocImovel(&immobiles,1);
				alocLoc(&loc,1);
				system("cls");
				immobilesSearchAll(immobiles,loc,owners);// Consulta total de im??s
				free(owners);
				free(immobiles);
				free(loc);
				owners=NULL;
				immobiles=NULL;
				loc=NULL;
			break;
			case 7: 
				//Utilizando ponteiros com um espa?- manipula? de arquivo parcial
				alocOwner(&owners,1);
				alocImovel(&immobiles,1);
				alocLoc(&loc,1);
				system("cls");
				rentImmobiles(immobiles,loc,owners);// Alugar um im??
				free(owners);
				free(immobiles);
				free(loc);
				owners=NULL;
				immobiles=NULL;
				loc=NULL;
			break;
			case 8: 
				alocLoc(&loc,1);
				system("cls");
				LocSelectAll(loc);// Consulta total de locat?os
				free(loc);
				loc=NULL;
			break;
			case 9:
				//Utilizando ponteiros com um espa?- manipula? de arquivo parcial
				alocOwner(&owners,1);
				alocImovel(&immobiles,1);
				alocLoc(&loc,1);
				system("cls");
				reportSearch(loc,1,owners,immobiles);// Gera relat?? de aluguel por dia de vencimento informado
				free(owners);
				free(immobiles);
				free(loc);
				owners=NULL;
				immobiles=NULL;
				loc=NULL;
			break;
			case 10:
				//Utilizando ponteiros com um espa?- manipula? de arquivo parcial
				alocOwner(&owners,1);
				alocImovel(&immobiles,1);
				alocLoc(&loc,1);
				system("cls");
				shutDownContract(loc,owners,immobiles);// Termina contrato
				free(owners);
				free(immobiles);
				free(loc);
				owners=NULL;
				immobiles=NULL;
				loc=NULL;
			break;
			case 11:
				//Utilizando ponteiros com um espa?- manipula? de arquivo parcial
				alocOwner(&owners,1);
				alocImovel(&immobiles,1);
				alocLoc(&loc,1);
				system("cls");
				updateData(loc,owners,immobiles);// Altera dados
				free(owners);
				free(immobiles);
				free(loc);
				owners=NULL;
				immobiles=NULL;
				loc=NULL;
			break;
			default:
				system("cls");
		}
	}while(op!=12);
	
}

//Fun? Aloca propriet?o-------------------
void alocOwner(prop **pr,int len){
	if((*pr = (prop*) realloc(*pr,len*sizeof(prop)))==NULL)
	exit(1);
}
//Fun? Aloca propriet?o-------------------

//Fun? Aloca Im??-------------------------
void alocImovel(imovel **pi,int len){
	if((*pi = (imovel*) realloc(*pi,len*sizeof(imovel)))==NULL)
	exit(1);
}
//Fun? Aloca Im??-------------------------

//Funcao Aloca locatario----------
void alocLoc(locatario **li,int len){
		if((*li = (locatario*) realloc(*li,len*sizeof(locatario)))==NULL)
	exit(1);
}
//Funcao aloca locatario---------------

//Fun? para contar quantidades de registos-------------------------
int  checkFile(char *flName){
	long int ownQtd=0;
	FILE     *fpReader=NULL;
	
	//Abre o arquivo informado
	if((fpReader=fopen(flName,"rb"))==NULL)
	{
		return ownQtd;
	}
	else
	{
		fseek(fpReader,0,2);
		//Conta quantidade de registros do arquivo informado
		ownQtd = ftell(fpReader);
		//Divide a quantidade de acordo com arquivo informado
		ownQtd /= (strcmp("proprietario.bin",flName)==0) ? (sizeof(prop)) : ((strcmp("locatario.bin",flName)==0) ? (sizeof(locatario)) : (sizeof(imovel)));
		
		fclose(fpReader);
		return ownQtd;
	}
}
//Fun? para contar quantidades de registos-------------------------

//Converte caractere maiusculo-----------------------------
char convertUpperCase(char c){
	if(c>='a' && c<='z')
		return c-32;
	return c;
}
//Converte caractere maiusculo-----------------------------

//Fun? que compara 2 strings independente do uso de caixa alta
int compareStrings(char *queryA, char *queryB){
	int reponse=1, dx=0;
	
	if(strlen(queryA)==strlen(queryB)){
		while(dx<strlen(queryA)){
			if(convertUpperCase(*(queryA+dx)) != convertUpperCase(*(queryB+dx)))
				return reponse;
			dx++;
		}
	}
	reponse = (dx==0) ? 1 : 0;
	return reponse;
}
//Fun? que compara 2 strings independente do uso de caixa alta

//Fun? gen?ca para filtrar entradas----------------------------
int inputFilter(char *strValue, int parameter){
	int  dx=0,dy,very;
	int  dateYear,dateMonth, dateDay;
	char alg[]="0123456789";   //Caracteres num?cos permitidos
	
	prop      *p_prop=NULL; //Ponteiro para propriet?o auxiliar para filtro de e-mail
	locatario *p_loc=NULL;  //Ponteiro para locat?o auxiliar para filtro de CPF
	
	switch(parameter){
		//Filtro de cpf, for?do uma formata?
		case 1 : 
			if(strlen(strValue) != 14) //V?da quantidade de caracteres necess?os
				return -1;
				
			for(dx=0;dx<strlen(strValue);dx++){
				if(dx<12){
					if(dx!=3 && dx!=7 && dx!=11) //Verifica os algarismos
					{
						very=0;
						for(dy=0;dy<strlen(alg);dy++)
								if(*(strValue+dx) == *(alg+dy))
									very = 1;
						if(very==0)
							return -1;
					}
							
					//Verifica se o CPF possui pontos e o hn
					if((dx==3 && *(strValue+dx)!='.') || (dx==7 && *(strValue+dx)!='.') || (dx==11 && *(strValue+dx)!='-'))
						return -1;
				}
			}
			return 0;
		break;
		//Segundo filtro de CPF, validar os cadastrados em proprietarios
		case 2:
			//Aloca espa?para um 1 propriet?o, para utilizar a fun? gen?ca de busca
			//Realiza-se isso para que o ponteiro presente no cadastro n?perca as informa?s j?adastradas
			alocOwner(&p_prop,1);
		
			if(ownersSelectBy(p_prop,1,strValue,0)!=-1){   //procura se o CPF j?oi cadastrado, caso esteja retorna -1
				free(p_prop);
				return -1;
			}
			free(p_prop);
			return 0;
		break;
		//Filtro de CEP
		case 3:
			if(strlen(strValue) != 9)
				return -1;
			for(dx=0;dx<strlen(strValue);dx++){
				
				if(dx!=5)//Verifica os algarismos
				{
					very=0;
					for(dy=0;dy<strlen(alg);dy++)
						if(*(strValue+dx) == *(alg+dy))
							very = 1;
					if(very==0)
						return -1;
				}
				else{
					if(*(strValue+dx)!='-')//Verifica se o CEP possui hn
						return -1;
				}
			}
			return 0;
		break;
		//Filtro de e-mail, validar os cadastrados
		case 4:
			//Aloca espa?para um 1 propriet?o, para utilizar a fun? gen?ca de busca
			//Realiza-se isso para que o ponteiro presente no cadastro n?perca as informa?s j?adastradas
			alocOwner(&p_prop,1);
			
			if(ownersSelectBy(p_prop,3,strValue,0)!=-1){ //procura se o e-mail j?oi cadastrado, caso esteja retorna -1
				free(p_prop);
				return -1;
			}
			free(p_prop);
			return 0;
		break;
		//Filtro para a datas
		case 5:
			if(strlen(strValue) != 8){
				printf("\n Informe uma data seguindo este formato: dd/mm/aa !\n ");
			}
			else{
				if(*(strValue+2)!='/' || *(strValue+5)!='/'){
					printf("\n Informe uma data utilizando barras seguindo este formato: dd/mm/aa !\n ");
				}
				else{
					//Utilizando os nmeros da tabela ASCII para validar os dias
					// 52 = '4' | 50 = '2'
					
					for(dx=0;dx<8;dx++){
						if(dx==0||dx==1||dx==3||dx==4||dx==6||dx==7){
							if(*(strValue+dx)<48 || *(strValue+dx)>57){
								printf("\n Informe uma data seguindo este formato: dd/mm/aa !\n ");
								return -1;
							}
						}
					}
					
					dateYear  = 10 * (*(strValue+6)-48) + 1 * (*(strValue+7)-48);
					dateMonth = 10 * (*(strValue+3)-48) + 1 * (*(strValue+4)-48);
					dateDay   = 10 * (*(strValue+0)-48) + 1 * (*(strValue+1)-48);
					
					//Filtro para dias > 00 e < 32
					if(dateDay > 0 ){
						if(dateMonth > 0 && dateMonth < 13){
							//Ano bissexto
							if(dateMonth == 2 && ( (dateYear % 4 == 0 && dateDay <= 29) || (dateYear % 4 !=0 && dateDay <=28))){
								return 0;
							}
							//Meses com at?1 dias
							else if(dateDay <=31 && (dateMonth==1 || dateMonth==3 || dateMonth == 5 || dateMonth == 7 || dateMonth == 8 || dateMonth == 10 || dateMonth == 12)){
								return 0;
							}
							//Meses com at?0 dias
							else if(dateDay <=30 && (dateMonth==4 || dateMonth==6 || dateMonth == 9 || dateMonth == 11)){
								return 0;
							}
							else{
								printf("\n Informe uma data utilizando um dia valido, cuidado com os dias 30, 31 e ano bissexto. Siga este formato: dd/mm/aa !\n ");
							}
						}
						else{
							printf("\n Informe uma data utilizando um mes valido. Siga este formato: dd/mm/aa !\n ");
						}
					}
					else{
						printf("\n Informe uma data utilizando um dia valido, cuidado com os dias 30, 31 e ano bissexto. Siga este formato: dd/mm/aa !\n ");
					}
				}	
			}
			return -1;
		break;
		//Filtro de CPF, validar os cadastrados em locatarios
		case 6:
			//Aloca espa?para um 1 locatario, para utilizar a fun? gen?ca de busca
			//Realiza-se isso para que o ponteiro presente no cadastro n?perca as informa?s j?adastradas
			alocLoc(&p_loc,1);
		
			if(locSearch(p_loc,4,dx,strValue)!=-1){   //procura se o CPF j?oi cadastrado, caso esteja retorna -1
				free(p_loc);
				return -1;
			}
			free(p_loc);
			return 0;
		break;
		default:
			return -1;
	}
}
//Fun? gen?ca para filtrar entradas----------------------------

//Fun? para manipular o arquivo do propriet?o--------------------
void ownersWriter(prop *owner, char *operation, int deslocate){
	FILE *fpWriter = NULL;
	
	//Abre arquivo para realizar opera? informada
	if((fpWriter=fopen("proprietario.bin",operation))==NULL)
	{
		printf("\nErro ao manipular arquivo");
	}
	else
	{
		//Desloca ponteiro do arquivo at?m indice informado para altera?
		if(strcmp(operation,"rb+")==0)
		   fseek(fpWriter, deslocate*sizeof(prop), 0);
		    
		fwrite(owner,sizeof(prop),1,fpWriter);
	}
	fclose(fpWriter);
}
//Fun? para manipular o arquivo do propriet?o-----------------

//Fun? para manipular o arquivo do locatario--------------------
void locWriter(locatario *loc, char *operation, int deslocate){
	FILE *flWriter = NULL;
	
	//Abre arquivo para realizar opera? informada
	if((flWriter=fopen("locatario.bin",operation))==NULL)
	{
		printf("\nErro ao manipular arquivo");
	}
	else
	{
		//Desloca ponteiro do arquivo at?m indice informado para altera?
		if(strcmp(operation,"rb+")==0)
		   fseek(flWriter, deslocate*sizeof(locatario), 0);
		    
		fwrite(loc,sizeof(locatario),1,flWriter);
	}
	fclose(flWriter);
}
//Fun? para manipular o arquivo do locatario-----------------

//Fun? para manipular o arquivo do im??--------------------
void immobilesWriter(imovel *immobiles, char *operation, int deslocate){
	FILE *fpWriter = NULL;
	
	//Abre arquivo para realizar opera? informada
	if((fpWriter=fopen("imovel.bin",operation))==NULL)
	{
		printf("\nErro ao manipular arquivo");
	}
	else
	{
		//Desloca ponteiro do arquivo at?m indice informado para altera?
		if(strcmp(operation,"rb+")==0)
		   fseek(fpWriter, deslocate*sizeof(imovel), 0);
		    
		fwrite(immobiles,sizeof(imovel),1,fpWriter);
	}
	fclose(fpWriter);	
}
//Fun? para manipular o arquivo do im??--------------------

//Fun? gen?ca para pesquisar propriet?o em arquivo---------------------
int ownersSelectBy(prop *owner, int parameter, char *strQuery, int intQuery){
	int   ownerQtd, dx=0, dy=0, response=-1;
	FILE  *fpReader=NULL;
	//Nome do arquivo a ser manipulado
	char  flName[]="proprietario.bin";
	
	/*
		strQuery: par?tro contendo dado string a ser procurado
		intQuery: par?tro contendo dado int a ser procurado
		parameter: tipo de campo 1- CPF; 2- reg_num; 3- e-mail; 4- registro do imovel cadastrado
	*/
	
	//Recebe quantidade de registros presentes no arquivo de propriet?os
	ownerQtd = checkFile(flName);
	
	if((fpReader=fopen("proprietario.bin","rb"))==NULL)
	{
		if(ownerQtd>0)
			printf("\nErro ao ler arquivo");
	}
	else
	{
		while(dx<ownerQtd){
			//Desloca ponteiro do arquivo para realizar a leitura
			fseek(fpReader,dx*sizeof(prop),0);
			
			//o ponteiro l?m propriet?o por vez
			fread(owner,sizeof(prop),1,fpReader);
			
			//Aplica filtro de busca
			switch(parameter){
				//Filtro para CPF
				case 1:
					if(compareStrings(strQuery,(owner->CPF))==0){
					   response = dx;
					   dx = ownerQtd;
					}
				break;
				//Filtro para Registro do propriet?o
				case 2:
					if(intQuery==owner->reg_prop){
					   response = dx;
					   dx = ownerQtd;
					}
				break;
				//Filtro para E-mail
				case 3:
					if(compareStrings(strQuery,(owner->end_prop.email))==0){
					   response = dx;
					   dx = ownerQtd;
					}
				break;
				//Filtro para procurar proprietado pelo registro do imovel
				case 4:
					dy=0;
					while(dy<owner->qtde_casa){ //Realiza varredura buscando nas casas de cada prop.
						if((owner->casa+dy)->num_casa == intQuery){
						   response = dx;
						   dx = ownerQtd;
						   dy = owner->qtde_casa;
						}
						dy++;
					}
				break;
				default:
					printf("\nErro - tente novamente, por favor!");
			}
			dx++;
		}
		fclose(fpReader);
	}
	return response;
}
//Fun? gen?ca para pesquisar propriet?o em arquivo---------------------

//Fun? para mostrar todos os dados do propriet?o na tela-----------------
void ownersShowOff(prop *owner, char cpf){
	int dy=0;
	
	printf("\n\n Registro do proprietario: %d\n",owner->reg_prop);
	printf(" Nome                    : %s\n",owner->nome);
	if(cpf != 's')
		printf(" CPF                     : %s\n",owner->CPF);
	printf("\n\n - Endereco -\n");
	printf(" Logradouro              : %s\n",owner->end_prop.logradouro);
	printf(" Bairro                  : %s\n",owner->end_prop.bairro);
	printf(" CEP                     : %s\n",owner->end_prop.CEP);
	printf(" Cidade                  : %s\n",owner->end_prop.cidade);
	printf(" Estado                  : %s\n",owner->end_prop.estado);
	printf(" Telefone                : %s\n",owner->end_prop.fone);
	printf(" Celular                 : %s\n",owner->end_prop.cel);
	printf(" E-mail                  : %s\n",owner->end_prop.email);
	
	printf("\n\n Quantidade de imoveis: %d\n",owner->qtde_casa);
	
	while(dy<(owner->qtde_casa)){
		printf("\n Imovel %d - ",dy+1);
		printf(" N%c : %d - ",167,(owner->casa+dy)->num_casa);
		printf(" Status: %c",(owner->casa+dy)->status_casa);
		dy++;
	}
	printf("\n========================================================================\n");
}
//Fun? para mostrar todos os dados do propriet?o na tela-----------------

//Fun? que realiza cadastro de propriet?o----------------------
void ownersRegister(prop *owner){
	int  ownerQtd;
	
	//Nome do arquivo a ser manipulado e opera? utilizada
	char  flName[]="proprietario.bin", operation[]="ab";
	
	ownerQtd = checkFile(flName); //Avalia a quantidade de registros, a partir dela gera-se o registro do propriet?o
	
	printf("\nRegistro: %d",ownerQtd+1);
	owner->reg_prop = (ownerQtd+1); //Atribui nmero de registro ao propriet?o
	
	do{
		printf("\nInforme o CPF do proprietario: ");
		gets(owner->CPF);
		fflush(stdin);
		if(inputFilter(owner->CPF,1)==-1)
			printf("\nInforme um CPF valido com pontos e hifen!\n");
		
	}while(inputFilter(owner->CPF,1)==-1);
	
	if(inputFilter(owner->CPF,2)==-1 && ownerQtd > 0)
		printf("\nCPF ja foi cadastrado por um proprietario, tente seu cadastro novamente ou entre em contato conosco!\n");
	else{
		
		do{
			printf("\nInforme o e-mail do proprietario: ");
			gets(owner->end_prop.email);
			fflush(stdin);
		}while(strlen(owner->end_prop.email)==0);
		
		if(inputFilter(owner->end_prop.email,4)==-1 && ownerQtd > 0)
			printf("\nE-mail ja cadastrado, tente seu cadastro novamente ou entre em contato conosco!\n");
		else{
			
			do{
				printf("\nInforme o nome do proprietario: ");
				gets(owner->nome);
				fflush(stdin);
			}while(strlen(owner->nome)==0);
			
			// Informa?s do endere?do propriet?o ----------------------------
			do{
				printf("\nInforme o logradouro do proprietario: ");
				gets(owner->end_prop.logradouro);
				fflush(stdin);
			}while(strlen(owner->end_prop.logradouro)==0);
			
			do{
				printf("\nInforme o bairro do proprietario: ");
				gets(owner->end_prop.bairro);
				fflush(stdin);
			}while(strlen(owner->end_prop.bairro)==0);
			
			do{
				printf("\nInforme o CEP do proprietario: ");
				gets(owner->end_prop.CEP);
				fflush(stdin);
				if(inputFilter(owner->end_prop.CEP,3)==-1)
					printf("\nInforme um CEP valido com hifen e numeros\n");
			}while(inputFilter(owner->end_prop.CEP,3)==-1);
			
			do{
				printf("\nInforme a cidade do proprietario: ");
				gets(owner->end_prop.cidade);
				fflush(stdin);
			}while(strlen(owner->end_prop.cidade)==0);
			
			do{
				printf("\nInforme o estado do proprietario: ");
				gets(owner->end_prop.estado);
				fflush(stdin);
			}while(strlen(owner->end_prop.estado)==0);
			
			do{
				printf("\nInforme o fone do proprietario: ");
				gets(owner->end_prop.fone);
				fflush(stdin);
			}while(strlen(owner->end_prop.fone)==0);
			
			do{
				printf("\nInforme o celular do proprietario: ");
				gets(owner->end_prop.cel);
				fflush(stdin);
			}while(strlen(owner->end_prop.cel)==0);
			
			
			//----------------------------------------------------------
			
			owner->qtde_casa = 0;
			
			//Salva cadastro em arquivo
			ownersWriter(owner,operation,1);
			printf("\n Proprietario cadastrado com sucesso!\n");
		}
	}
	system("pause");
	system("cls");
}
//Fun? que realiza cadastro de propriet?o----------------------

//Fun? que realiza cadastro de Im??----------------------
void immobilesRegister(imovel *immobiles, prop *owner){
	int   immQtd=0, menuSlt, regProp, response;
	
	//Vari?l auxiliar para realizar na procura do dono do im?? a ser cadastrado
	char  strAux[30], confirm;
	
	//Nome do arquivo a ser manipulado e opera?s para serem realizadas
	char  flName[]="imovel.bin", update[]="rb+", save[]="ab";
	
	
	//Filtro para menu, caso n?encontre o pr??tario permite-se procurar de novo ou cancelar cadastro
	do{
		
		//Filtro de entrada do menu
		do{
			printf("\n\n Para cadastrar um imovel informe um dos dados abaixo:\n\n [1] - CPF do proprietario\n [2] - Numero de registro do proprietario\n [3] - E-mail do proprietario\n [4] - Cancelar cadastro de imovel\n Opcao:");
			scanf("%d",&menuSlt);
			fflush(stdin);
			if(menuSlt != 1 && menuSlt != 2 && menuSlt != 3)
				system("cls");
		}while(menuSlt != 1 && menuSlt != 2 && menuSlt != 3 && menuSlt != 4);
		//Filtro de entrada do menu
		
		//Caso usuario deseje informar o CPF ou E-mail
		if(menuSlt==1 || menuSlt== 3){
			if(menuSlt==1)
				printf("\n Informe o CPF: ");
			else
				printf("\n Informe o E-mail: ");
				
			gets(strAux);
			fflush(stdin);
			
			//Al?de retornar a posi? no arquivo, desloca ponteiro prop.
			response = ownersSelectBy(owner, menuSlt, strAux, 0);
		}
		
		//Caso usuario deseje informar o registro do proprietario
		else if(menuSlt==2){
			printf("\n Informe o numero de registro do proprietario: ");
			scanf("%d",&regProp);
			fflush(stdin);
			
			//Al?de retornar a posi? no arquivo, desloca ponteiro prop.
			response = ownersSelectBy(owner, menuSlt, strAux, regProp);
		}
		
		//Caso usuario cancele o cadastro
		else{
			response=-1;
		}
		
		if(response==-1){
			system("cls");
			switch(menuSlt){
				case 1:
					printf("\n Nenhum proprietario foi encontrado com o CPF informado, tente novamente por favor.\n");
				break;
				case 2:
					printf("\n Nenhum proprietario foi encontrado com o registro informado, tente novamente por favor.\n");
				break;
				case 3:
					printf("\n Nenhum proprietario foi encontrado com o e-mail informado, tente novamente por favor.\n");
				break;
				case 4:
				break;
				default:
					printf("\n Nenhum proprietario foi encontrado, tente novamente por favor.\n");
			}
		}
			
	}while(response==-1 && menuSlt != 4);
	
	//Caso encontre o propriet?o e n?dejesa-se cancelar
	if(menuSlt!=4){
		
		//Caso o propriet?o n?tenha mais de 5 im??s registrados, permite-se o cadastro de um novo
		if(owner->qtde_casa < 5){
			system("cls");
			
			//Como o ponteiro do prop. est?eslocado exibe-se para confer?ia
			printf("Proprietario encontrado:\n Nome: %s\n CPF: %s\n Quantidade de imoveis cadastrados: %d\n\n",owner->nome,owner->CPF,owner->qtde_casa);
			
			do{
				printf("\n Deseja realizar cadastro no proprietario encontrado? (S/N)\n ");
				scanf("%c",&confirm);
				fflush(stdin);
			}while(convertUpperCase(confirm)!='S' && convertUpperCase(confirm)!='N');
			
			if(convertUpperCase(confirm)=='N'){
				printf("\nAperte qualquer tecla para voltar ao menu inicial!\n");
				system("pause");
			}
			else
			{
				//Recebe quantidade de registros presentes no arquivo dos im??s
				immQtd = checkFile(flName);
				
				printf("\nRegistro do imovel: %d",immQtd+1);
				immobiles->reg_imov = (immQtd+1);
				fflush(stdin);
				
				do{
					printf("\nInforme o logradouro do imovel: ");
					gets(immobiles->end_imov.logradouro);
					fflush(stdin);
				}while(strlen(immobiles->end_imov.logradouro)==0);
				
				do{
					printf("\nInforme o bairro do imovel: ");
					gets(immobiles->end_imov.bairro);
					fflush(stdin);
				}while(strlen(immobiles->end_imov.bairro)==0);
				
				do{
					printf("\nInforme o CEP do imovel: ");
					gets(immobiles->end_imov.CEP);
					fflush(stdin);
					if(inputFilter(immobiles->end_imov.CEP,3)==-1)
						printf("\nInforme um CEP valido com hifen e numeros\n");
				}while(inputFilter(immobiles->end_imov.CEP,3)==-1);
				
				do{
					printf("\nInforme a cidade do imovel: ");
					gets(immobiles->end_imov.cidade);
					fflush(stdin);
				}while(strlen(immobiles->end_imov.cidade)==0);
				
				do{
					printf("\nInforme a area util do imovel em m%c: ",253);
					scanf("%f",&(immobiles->area));
					fflush(stdin);
					if(immobiles->area<=0)
						printf("\nInforme uma area util valida!\n");
				}while(immobiles->area<=0);
				
				do{
					printf("\nInforme a quantidade de quartos do imovel: ");
					scanf("%i",&(immobiles->quartos));
					fflush(stdin);
					if(immobiles->quartos<=0)
						printf("\nInforme uma quantidade de quartos valida!\n");
				}while(immobiles->quartos<=0);
				
				do{
					printf("\nInforme o valor do imovel: ");
					scanf("%f",&(immobiles->valor));
					fflush(stdin);
					if(immobiles->valor<=0)
						printf("\nInforme um valor valido!\n");
				}while(immobiles->valor<=0);
				
				immobiles->status.sigla = 'L';
				
				//Grava novo im??
				immobilesWriter(immobiles,save,1);
				
				//Associar im?? ao propriet?o
				(owner->casa+(owner->qtde_casa))->status_casa = 'L';
				(owner->casa+(owner->qtde_casa))->num_casa    = immobiles->reg_imov;
				owner->qtde_casa++;
				
				//Atualiza os im??s do propriet?o
				ownersWriter(owner,update,response);
				printf("\n Imovel cadastrado com sucesso!\n\n");
				system("PAUSE");
			}
		}
		else{
			//Tratamento caso propriet?o informado possua 5 casas
			system("cls");
			printf("\n O proprietario \"%s\" - CPF: \"%s\" ja cadastrou 5 casas, o maximo permitido sao 5 casas por proprietario.\n Por favor, entre em contato conosco!\n\n",owner->nome,owner->CPF);
			system("pause");
		}
	}
	system("cls");
}
//Fun? que realiza cadastro de Im??----------------------

//Fun? de cadastro do locatario----------------------------
void locRegister(locatario *loc, imovel *immobiles, prop *owner){
	int   dy=0, indexHolder, response, locQtd;
	
	//Variaveis para filtrar as datas de inicio e t?ino
	int   startYear,startMonth,startDay,endYear,endMonth,endDay, dataCheck=0;
	
	//Nome do arquivo a ser manipulado e opera? utilizada
	char  flName[]="locatario.bin", update[]="rb+", operation[]="ab", strEmpty[]="", imEmpty='L', locNull[]="@";
	
	//Valida se existe um espa?no arquivo de locat?os ocioso (registro deletado)
	response = locSearch(loc,6,dy,locNull);
	
	locQtd = checkFile(flName); //Avalia a quantidade de registros, a partir dela gera-se o registro do locatario
	
	//Caso n?tenha
	if(response==-1){
		loc->reg_loc = (locQtd+1); //Atribui nmero de registro ao locatario
	}
	
	printf("\nRegistro do locatario: %d",loc->reg_loc);
			
	do{
		printf("\nInforme o CPF do locatario: ");
		gets(loc->CPF);
		fflush(stdin);
		if(inputFilter(loc->CPF,1)==-1)
			printf("\nInforme um CPF valido com pontos e hifen!\n");
	}while(inputFilter(loc->CPF,1)==-1);
	
	if(inputFilter(loc->CPF,6)==-1 && locQtd > 0){
		system("cls");
		printf("\n CPF ja foi cadastrado por um locatario, tente seu cadastro novamente ou entre em contato conosco!\n\n");
	}
	else{
		do{
			printf("\nInforme o nome do locatario: ");
			gets(loc->nome);
			fflush(stdin);
		}while(strlen(loc->nome)==0);
		
		// Informa?s do endere?do locatario ----------------------------
		do{
			printf("\nInforme o logradouro do locatario: ");
			gets(loc->end_loc.logradouro);
			fflush(stdin);
		}while(strlen(loc->end_loc.logradouro)==0);
		
		do{
			printf("\nInforme o bairro do locatario: ");
			gets(loc->end_loc.bairro);
			fflush(stdin);
		}while(strlen(loc->end_loc.bairro)==0);
		
		do{
			printf("\nInforme o CEP do locatario: ");
			gets(loc->end_loc.CEP);
			fflush(stdin);
			if(inputFilter(loc->end_loc.CEP,3)==-1)
				printf("\nInforme um CEP valido com hifen e numeros\n");
		}while(inputFilter(loc->end_loc.CEP,3)==-1);
		
		do{
			printf("\nInforme a cidade do locatario: ");
			gets(loc->end_loc.cidade);
			fflush(stdin);
		}while(strlen(loc->end_loc.cidade)==0);
		
		do{
			printf("\nInforme o estado do locatario: ");
			gets(loc->end_loc.estado);
			fflush(stdin);
		}while(strlen(loc->end_loc.estado)==0);
		
		do{
			printf("\nInforme o fone do locatario: ");
			gets(loc->end_loc.fone);
			fflush(stdin);
		}while(strlen(loc->end_loc.fone)==0);
		
		do{
			printf("\nInforme o celular do locatario: ");
			gets(loc->end_loc.cel);
			fflush(stdin);
		}while(strlen(loc->end_loc.cel)==0);
		
		do{
			printf("\nInforme o e-mail do locatario: ");
			gets(loc->end_loc.email);
			fflush(stdin);
		}while(strlen(loc->end_loc.email)==0);
		
		loc->reg_imov = immobiles->reg_imov;
		
		do{
			printf("\nInforme o dia de vencimento do aluguel: ");
			scanf("%i",&(loc->dia_venc));
			fflush(stdin);
		}while(loc->dia_venc<=0 || loc->dia_venc>31);			
		
		do{
			printf("\nInforme a data de inicio do contrato: ");
			gets(loc->inicio);
			fflush(stdin);
		}while(inputFilter(loc->inicio,5)==-1);
		
		do{
			//filtro de data
			dataCheck=0;
			
			do{
			printf("\nInforme a data de termino do contrato: ");
				gets(loc->termino);
				fflush(stdin);
			}while(inputFilter(loc->termino,5)==-1);
			
			//Data de inicio
			startYear  = 10 * (*(loc->inicio+6)-48) + 1 * (*(loc->inicio+7)-48);
			startMonth = 10 * (*(loc->inicio+3)-48) + 1 * (*(loc->inicio+4)-48);
			startDay   = 10 * (*(loc->inicio+0)-48) + 1 * (*(loc->inicio+1)-48);
			
			//Data de termino
			endYear  = 10 * (*(loc->termino+6)-48) + 1 * (*(loc->termino+7)-48);
			endMonth = 10 * (*(loc->termino+3)-48) + 1 * (*(loc->termino+4)-48);
			endDay   = 10 * (*(loc->termino+0)-48) + 1 * (*(loc->termino+1)-48);
			
			//Valida se a data de t?ino ?osterior a de inicio
			if(endYear >= startYear){
				if(endYear == startYear ){
					if(endMonth >= startMonth){
						if(endMonth == startMonth){
							if(endDay > startDay){
								dataCheck = 1;
							}
							else{
								printf("\n Informe uma data de termino posterior a data de inicio!\n");
								dataCheck = 0;
							}
						}else{
							dataCheck = 1;
						}
					}
					else{
						printf("\n Informe uma data de termino posterior a data de inicio!\n");
						dataCheck = 0;
					}
				}
				else{
					dataCheck = 1;
				}
			}
			else{
				printf("\n Informe uma data de termino posterior a data de inicio!\n");
				dataCheck = 0;
			}
		}while(dataCheck!=1);
	
		
		//----------------------------------------------------------
		
		//Salva locat?o
		if(response!=-1){
			locWriter(loc,update,response);
		}
		else{
			locWriter(loc,operation,1);
		}
		
		//Usa uma auxiliar para salvar o registro do propriet?o
		//Por utilizarmos um ponteiro para apenas 1 tipo de dado as fun?s de busca sobreescrevem os dados presentes no ponteiro durante a busca
		//Com isso, devemos passar separadamente os dados a serem pesquisados no ponteiro
		indexHolder = owner->reg_prop;
		
		//Al?de retornar a posi? no arquivo, desloca ponteiro prop.
		response = ownersSelectBy(owner, 2, strEmpty, indexHolder);
	
		//Como j?emos a posi? no arquivo, podemos fazer as altera?s nos im??s associados no propriet?o 
		//Para isso ?ecess?a uma varredura nos 5 im??s permitidos
		while(dy<owner->qtde_casa){
			if((owner->casa+dy)->num_casa == immobiles->reg_imov){
				(owner->casa+dy)->status_casa = 'A';
				dy = owner->qtde_casa;
			}
			dy++;
		}
		
		//Atualiza proprietario
		ownersWriter(owner, update, response);
		
		//Usa a mesma auxiliar para salvar o nmero do im??
		//Por utilizarmos um ponteiro para apenas 1 tipo de dado as fun?s de busca sobreescrevem os dados presentes no ponteiro durante a busca
		//Com isso, devemos passar separadamente os dados a serem pesquisados no ponteiro
		indexHolder = immobiles->reg_imov;
		
		//Retorna a posi? no arquivo e ponteiro deslocado na posi? do n do im??
		response = immobileSearch(immobiles,6,indexHolder,strEmpty,imEmpty);
		
		//Como j?emos a posi? no arquivo, podemos fazer as altera?s no im?? que ser?lugado
		immobiles->status.loc.sigla   = 'A';
		immobiles->status.loc.reg_loc = loc->reg_loc;
		
		//E atualiza-lo
		immobilesWriter(immobiles,update,response);
		
		printf("\n Locatario cadastrado com sucesso!\n");
	}		
}
//Fun? de cadastro do locatario----------------------------

//Fun? que exibe todos os propriet?os----------------------
void ownersSelectAll(prop *owner){
	int   ownerQtd, dx=0;
	FILE  *fpReader=NULL;
	
	//Nome do arquivo a ser manipulado
	char  flName[]="proprietario.bin";
	
	//Recebe quantidade de registros presentes no arquivo de propriet?os
	ownerQtd = checkFile(flName);
	
	if((fpReader=fopen(flName,"rb"))==NULL){
		printf("\nNenhum dado encontrado!\n");
	}
	else{
		while(dx<ownerQtd){
			//Desloca ponteiro do arquivo para realizar a leitura
			fseek(fpReader,dx*sizeof(prop),0);
			fread(owner,sizeof(prop),1,fpReader);
			
			ownersShowOff(owner,'n');
			dx++;
		}
		
		fclose(fpReader);
	}
	system("pause");
	system("cls");
}
//Fun? que exibe todos os propriet?os----------------------

//Fun? para pesquisar propriet?o por cpf -----------------
void OwnersSearchCPF(prop *owner){
	int  response;
	char cpfs[15];
	
	printf("Digite um CPF para consulta: ");
	gets(cpfs);
	fflush(stdin);
	
	//Al?de retornar a posi? no arquivo, desloca ponteiro prop.
	response=ownersSelectBy(owner, 1, cpfs, 0);
	
	if(response==-1)
		printf("\nNenhum proprietario registrado possui o cpf informado, tente novamente por favor!\n");
	else{
		printf("\nUsuario encontrado:\n");
		ownersShowOff(owner,'s');
	}
	
	system("pause");
	system("cls");
}
//Fun? para pesquisar propriet?o por cpf -----------------

//Fun? para fazer buscas em im??s --------------------
void immobilesSearchBed(imovel *immobiles){
	int   op, QtdBA;
	float QtdA;
	char  qbairro[30],imStatus;
	
	//Filtrar tipo de busca
	do{
		printf("Buscar por:\n[1] - Quantidade Quartos\n[2] - Area util em m%c\n[3] - Bairro\n[4] - Sair\n Opcao: ",253);
		scanf("%i",&op);
		fflush(stdin);
		
		switch(op){
			//Caso seja para buscar por quantidade de quartos
			case 1:
					system("cls");
					printf("Digite a quantidade de quartos desejado: ");
					scanf("%i",&QtdBA);
					fflush(stdin);
					immobileSearch(immobiles, 1, QtdBA,qbairro,'L');
					break;
			//Caso seja para buscar pela area til
			case 2:
					system("cls");
					printf("Digite a area util em m%c: ",253);
					scanf("%f",&QtdA);
					fflush(stdin);
					immobileSearch(immobiles, 2, QtdA,qbairro,'L');
					break;
			//Caso seja para buscar por bairro
			case 3: 
					system("cls");
					printf("Digite o bairro: ");
					gets(qbairro);
					fflush(stdin);
					immobileSearch(immobiles, 3, 0,qbairro,'L');
			break;
			default:
				system("cls");
		}
	}while(op!=1 && op!=2 && op!=3 && op!=4);
}
//Fun? para fazer buscas em im??s --------------------

//Fun? que mostra na tela dados do im??------------
void immobileShowOff(imovel *immobile, char type){
	printf(" \n\n Registro do imovel: %d",immobile->reg_imov);
	
	//Conforme a ordem do pdf
	if(type=='T'){
		printf("\n - Endereco -\n Logradouro          : %s",immobile->end_imov.logradouro);
		printf("\n Bairro              : %s",immobile->end_imov.bairro);
		printf("\n CEP                 : %s",immobile->end_imov.CEP);
		printf("\n Cidade              : %s\n",immobile->end_imov.cidade);
	}
	printf("\n Area util           : %.2f m%c",immobile->area,253);
	printf("\n Quartos             : %i quarto(s)\n",immobile->quartos);
	
	//Conforme a ordem do pdf
	if(type=='P'){
		printf("\n Endereco:\n Logradouro          : %s",immobile->end_imov.logradouro);
		printf("\n Bairro              : %s",immobile->end_imov.bairro);
		printf("\n CEP                 : %s",immobile->end_imov.CEP);
		printf("\n Cidade              : %s\n",immobile->end_imov.cidade);
	}
	printf("\n Valor do aluguel    : R$%.2f",immobile->valor);
	
	//Verifica status na union
	if(immobile->status.sigla=='L')
		printf("\n Status do imovel    : %c\n",immobile->status.sigla);
	else{
		printf("\n Status do imovel    : %c\n",immobile->status.loc.sigla);
		printf("\n N%c do locatario     : %d\n",167,immobile->status.loc.reg_loc);
	}
	printf("\n===================================================\n")	;
}
//Fun? que mostra na tela dados do im??------------

//Fun? consulta total imoveis----------------------------
void immobilesSearchAll(imovel *immobiles, locatario *loc, prop *owner){
	char imStatus;
	int  re;
	
	system("cls");
	do{
		printf(" Deseja ver todos imoveis livres ou alugados?");
		printf("\n Digite \"L\" para ver os imoveis livres ou \"A\" para ver os imoveis alugados\n ");
		scanf("%c",&imStatus);
		fflush(stdin);
		if(convertUpperCase(imStatus)!='L' && convertUpperCase(imStatus) !='A')
			system("cls");
	}while(convertUpperCase(imStatus)!='L' && convertUpperCase(imStatus) !='A');
	
	//Realiza busca total, retornando quantidade de im??s exibidos
	re = immobileSearch(immobiles, 4, 0, 0,convertUpperCase(imStatus));
	
	if(re==0)
		printf("\nNenhum imovel foi encontrado na busca!\n");
	
	system("pause");
	system("cls");
}
//Fun? consulta total imoveis----------------------------

//Fun? para alugar im??s----------------------------------
void rentImmobiles(imovel *immobiles, locatario *loc, prop *owner){
	char imStatusEmpty='L', imStatusOccupied='A', askIm, strEmpty[]="";
	int im_num_reg;
	system("cls");
	
	
	if(immobileSearch(immobiles, 7, 0, 0,imStatusEmpty) > 0){
		
		printf("\n Imoveis disponiveis:\n\n");
		//Caso tenha im??s livres eles s?exibidos, uma confirma? ?ecess?a para alugar um deles
		immobileSearch(immobiles, 4, 0, 0,imStatusEmpty);
		do{
			printf("\n\n Deseja alugar um imovel?(s/n)\n ");
			scanf("%c",&askIm);
			fflush(stdin);
		}while(convertUpperCase(askIm)!='N' && convertUpperCase(askIm)!='S');
		
		if(convertUpperCase(askIm) == 'S'){
			
			//Caso confirme, pede-se o nmero do quarto
			do{
				printf("\n Por favor, informe o registro do imovel que voce deseja alugar: ");
				scanf("%d",&im_num_reg);
				fflush(stdin);
			}while(im_num_reg<=0);
			
			
			if(immobileSearch(immobiles,5,im_num_reg,strEmpty,imStatusEmpty)!=0)
			{   //Verifica se nmero do im?? informado est?ealmente livre
				//Levando em considera? que o ponteiro im?? est?eslocado, desloca-se ponteiro do propriet?o para o propriet?o dono do im??
				if(ownersSelectBy(owner,4,strEmpty,immobiles->reg_imov) != -1){
					//Com os ponteiros de prop. e im?? deslocados, realiza-se o cadastro do locat?o
					locRegister(loc,immobiles,owner);
				}
				else{
					//Caso tenha um cadastro inv?do
					printf("\n Algum erro aconteceu, o proprietario do imovel nao foi encontrado\n Por favor, entre em contato conosco e tente novamente!\n");
				}
			}
			else if(immobileSearch(immobiles,5,im_num_reg,strEmpty,imStatusOccupied) != 0)
			{//Como n?encontra nenhum im?? livre, verifica se o nmero do quarto informado ?e um im?? j?lugado
				system("cls");
				printf("\n O imovel informado de n%c %d esta alugado!\n\n Informacoes do aluguel do imovel de n%c %d:\n\n",167,im_num_reg,167,im_num_reg);
				locSearch(loc,5,im_num_reg,strEmpty);
				printf(" Valor do aluguel             : R$%.2f\n",immobiles->valor);
				printf(" Dia de vencimento do aluguel : %02d\n",loc->dia_venc);
				printf(" Data de inicio do contrato   : %s\n",loc->inicio);
				printf(" Data de termino do contrato  : %s\n\n",loc->termino);
			}
			else{
				//Caso n?encontre o im??
				system("cls");
				printf("\n O imovel informado nao esta cadastrado em nossos dados, por favor tente novamente!\n\n");
			}
		}
	}
	else{
		//Caso todos im??s estejam alugados, pode-se exibir as informa?s sobre o aluguel
		if(immobileSearch(immobiles, 7, 0, 0,imStatusOccupied) > 0){
			do{
				system("cls");
				printf("\n Infelizmente todos imoveis estao alugados!\n Deseja consultar as informacoes do aluguel de um imovel alugado?(S/N)\n ");
				scanf("%c",&askIm);
				fflush(stdin);
			}while(convertUpperCase(askIm)!='N' && convertUpperCase(askIm)!='S');
			
			if(convertUpperCase(askIm)=='S'){
				do{
					printf("\n Por favor, informe o registro do imovel que voce deseja consultar: ");
					scanf("%d",&im_num_reg);
					fflush(stdin);
				}while(im_num_reg<=0);
				
				//Realiza-se uma busca para encontrar as infor?s do im?? alugado informado
				if(immobileSearch(immobiles,5,im_num_reg,strEmpty,imStatusOccupied) != 0)
				{
					system("cls");
					printf("\n Informacoes do aluguel do imovel de n%c %d:\n\n",167,im_num_reg,167,im_num_reg);
					
					//Busca dados do locat?o, como data de vencimento, data de ino e data de t?ino
					locSearch(loc,1,im_num_reg,strEmpty);
					printf(" Valor do aluguel             : R$%.2f\n",immobiles->valor);
					printf(" Dia de vencimento do aluguel : %d\n",loc->dia_venc);
					printf(" Data de inicio do contrato   : %s\n",loc->inicio);
					printf(" Data de termino do contrato  : %s\n\n",loc->termino);
				}
				else{
					//Caso n?encontre
					system("cls");
					printf("\n O imovel informado nao esta cadastrado em nossos dados, por favor tente novamente!\n\n");
				}
			}
		}
		else{
			//Nenhum im?? cadastrado
			system("cls");
			printf("\n Infelizmente nenhum imovel esta disponivel para consulta!\n");
		}
	}
	
	system("pause");
	system("cls");
}
//FUn? para alugar im??s----------------------------------------------------

//Fun? para exibir na tela os dados do locat?o-----------------------------
void LocShowOff(locatario *loc){
	if(strcmp(loc->CPF,"@") != 0){
		printf("\n\n Registro do locatario          : %d\n",loc->reg_loc);
		printf(" Nome                           : %s\n",loc->nome);
		printf(" CPF                            : %s\n",loc->CPF);
		printf(" Registro do imovel             : %i\n",loc->reg_imov);
		printf(" Dia do vencimento              : %02d\n",loc->dia_venc);
		printf(" Data de inicio do contrado     : %s\n",loc->inicio);
		printf(" Data de termino do contrato    : %s\n",loc->termino);
		printf("\n========================================================================\n");
	}
}
//Fun? para exibir na tela os dados do locat?o-----------------------------

void reportShowOff(locatario *loc,prop *owners,imovel *immobiles){
		printf(" N%c de registro do imovel        : %d",167,immobiles->reg_imov);
		printf("\n Valor do aluguel                : R$%.2f",immobiles->valor);
		printf("\n N%c de registro do locatario     : %d",167,loc->reg_loc);
		printf("\n Nome do locatario               : %s",loc->nome);
		printf("\n CPF  do locatario               : %s",loc->CPF);
		printf("\n N%c de registro do proprietario  : %d",167,owners->reg_prop);
		printf("\n Nome do proprietario            : %s",owners->nome);
		printf("\n CPF  do proprietario            : %s",owners->CPF);
		printf("\n=====================================================================\n");
}
//Fun? para exibir todos locat?os na tela----------------------------------------

//Fun? para exibir todos locat?os na tela----------------------------------------
void LocSelectAll(locatario *loc){
	int   LocQtd, dx=0, rowCnt=0;
	FILE  *flReader=NULL;
	
	//Nome do arquivo a ser manipulado
	char  flName[]="locatario.bin";
	
	//Recebe quantidade de registros presentes no arquivo de propriet?os
	LocQtd = checkFile(flName);
	
	if((flReader=fopen(flName,"rb"))==NULL){
		printf("\nNenhum locatario encontrado!\n");
	}
	else{
		while(dx<LocQtd){
			//Desloca ponteiro do arquivo para realizar a leitura
			fseek(flReader,dx*sizeof(locatario),0);
			fread(loc,sizeof(locatario),1,flReader);
	
			//Exibir informa?s
			LocShowOff(loc);
			if(strcmp(loc->CPF,"@") != 0)
				rowCnt++;
			dx++;
		}
		
		fclose(flReader);
		if(rowCnt==0)
			printf("\n Nenhum locatario encontrado!\n");
	}
	system("pause");
	system("cls");
}
//Fun? para exibir todos locat?os na tela----------------------------------------

//Fun? gen?ca para pesquisar locat?os----------------------------------------
int locSearch(locatario *loc, int parameter, int queryInt, char* strQuery){
	int  locQtd, dx=0, rowCnt=0, response=-1;
	char flName[]="locatario.bin";
	FILE *flReader=NULL;
	
	/*
		queryInt: par?tro contendo dado int a ser procurado
		parameter: tipo de opera? desejada 
		1 - procurar locat?o pelo numero do im?? informado
		2 - procurar locat?o pelo dia de vencimento do aluguel
		3 - procurar locat?o pelo CPF
		4 - procurar locat?o pelo CPF e retorna posi? no arquivo
		5 - procurar locat?o pelo numero do im?? informado e retorna posi? no arquivo
		6 - procurar locat?o deletado e retorna posi? no arquivo
	*/
	
	//Recebe quantidade de registros presentes no arquivo de locat?o
	locQtd = checkFile(flName);
	
	if((flReader=fopen("locatario.bin","rb"))==NULL){
		if(parameter != 4)
			printf("\nNenhum dado encontrado!\n");
	}
	else
	{
		while(dx<locQtd){
			
			fseek(flReader,dx*sizeof(locatario),0);
			fread(loc,sizeof(locatario),1,flReader);
			
			switch(parameter){
				case 1:
					if(loc->reg_imov == queryInt){
						rowCnt++;
						//Como j?ncontrou, retorna o ponteiro deslocado
						dx=locQtd;
					}
				break;
				case 2:
					if(loc->dia_venc == queryInt && strcmp(loc->CPF,"@") != 0){
						rowCnt++;
						//Como j?ncontrou, retorna o ponteiro deslocado
						dx=locQtd;
					}
				break;
				case 3:
					if(compareStrings(strQuery,(loc->CPF))==0){
						rowCnt++;
						//Como j?ncontrou, retorna o ponteiro deslocado
						dx=locQtd;
					}
				break;
				case 4:
					if(compareStrings(strQuery,(loc->CPF))==0){
						//Neste caso o retorno ser? posi?, n?a quantidade de indices encontrados
						response = dx;
						
						//Como j?ncontrou, retorna o ponteiro deslocado
						dx=locQtd;
					}
				break;
				case 5:
					if(loc->reg_imov == queryInt){
						//Neste caso o retorno ser? posi?, n?a quantidade de indices encontrados
						response = dx;
						
						//Como j?ncontrou, retorna o ponteiro deslocado
						dx=locQtd;
					}
				break;
				case 6:
					if(compareStrings(strQuery,(loc->CPF))==0 && strcmp(loc->CPF,"@") == 0){
						//Neste caso o retorno ser? posi?, n?a quantidade de indices encontrados
						response = dx;
						
						//Como j?ncontrou, retorna o ponteiro deslocado
						dx=locQtd;
					}
				break;
				default:
					dx=locQtd;
			}
			dx++;
		}
		fclose(flReader);
	}
	
	if(parameter == 4 || parameter == 5 || parameter == 6)
		return response;
	
	return rowCnt;
}
//Fun? gen?ca para pesquisar locat?os----------------------------------------

//Fun? gen?ca para pesquisar im??------------
int immobileSearch(imovel *immobile, int parameter, int queryInt, char* queryStr, char status){
    int   immQtd, dx=0, rowCnt=0, response=-1;
	FILE  *fmReader=NULL;
	
	//Nome do arquivo a ser manipulado
	char  flName[]="imovel.bin";
	
	/*
		queryStr: par?tro contendo dado string a ser procurado
		queryInt: par?tro contendo dado int a ser procurado
		parameter: tipo de opera? desejada 
		1- exibir todos im??s por nmero de quartos; 
		2- exibir todos im??s por ?a til; 
		3- exibir todos im??s por bairro; 
		4- exibir todos im??s alugados ou Livres; 
		5- Busca um im?? especco pelo nmero de registro informado; 
		6- Retorna posi? no arquivo buscando pelo registro do im??
		7- Retorna a quantidade de imoveis livres ou alugados
		status   : filtro de status do im??
	*/
	
	//Recebe quantidade de registros presentes no arquivo de im??s
	immQtd = checkFile(flName);
	
	if((fmReader=fopen("imovel.bin","rb"))==NULL){
		printf("\nNenhum dado encontrado!\n");
	}
	else
	{
		while(dx<immQtd){
			
			fseek(fmReader,dx*sizeof(imovel),0);
	
			fread(immobile,sizeof(imovel),1,fmReader);
			
			switch(parameter){
				//Filtro para mostrar por nmero de quartos
				case 1:
					if(queryInt==immobile->quartos && immobile->status.sigla == status){
						immobileShowOff(immobile,'P');
						rowCnt++;
					}
				break;
				//Filtro para mostrar por ?a
				case 2:
					if(queryInt==immobile->area && immobile->status.sigla == status){
						immobileShowOff(immobile,'P');
						rowCnt++;
					}
				break;
				//Filtro para mostrar por bairro
				case 3:
					if(compareStrings(queryStr, immobile->end_imov.bairro)==0  && immobile->status.sigla == status){
						immobileShowOff(immobile,'P');
						rowCnt++;
					}
						
				break;
				//Filtro para consulta total (por im?? alugados ou livres)
				case 4:
					if(status=='L'){
						//Busca im??s livres
						if(immobile->status.sigla == status){
							immobileShowOff(immobile,'T');
							rowCnt++;
						}
					}
					else{
						//Busca im??s Alugados
						if(immobile->status.loc.sigla == status){
							immobileShowOff(immobile,'T');
							rowCnt++;
						}
					}
				break;
				//Filtro para busca por registro de imovel
				case 5:
					if(status=='L'){
						//Busca im??s livres com o registro de imovel informado
						if(immobile->reg_imov == queryInt && immobile->status.sigla == status){
							rowCnt++;
							return rowCnt; // Retorna que o item foi encontrado (1) com o ponteiro de imovel deslocado =)
						}
					}
					else{
						//Busca im??s Alugados com o registro de imovel informado
						if(immobile->reg_imov == queryInt && immobile->status.loc.sigla == status){
							rowCnt++;
							return rowCnt; // Retorna que o item foi encontrado (1) com o ponteiro de imovel deslocado =)
						}
					}
				break;
				//Filtro para buscar posi? no arquivo usando o registro de imovel
				case 6:
					if(immobile->reg_imov == queryInt){
						response = dx;
						dx = immQtd;
					}
				break;
				//Filtro para contagem total (por im?? alugados ou livres)
				case 7:
					if(status=='L'){
						//Busca im??s livres
						if(immobile->status.sigla == status)
							rowCnt++;
					}
					else{
						//Busca im??s Alugados
						if(immobile->status.loc.sigla == status)
							rowCnt++;
					}
				break;
				default:
					printf("\nErro\n Tente novamente!\n");
					dx=immQtd;
			}
			dx++;
		}
		fclose(fmReader);
		if(rowCnt==0 && parameter != 4 && parameter != 5 && parameter != 6)
			printf("\nNenhum imovel foi encontrado na busca!\n");
	}
	
	// Retorno exclusivo do filtro 6, retorna a posi? do im?? no arquivo
	if(response != -1) 
		return response;
	
	//Para os outros arquivos retorna a quantidade de itens encontrados
	return rowCnt;
}
//Fun? gen?ca para pesquisar im??------------

//funcao para procurar e gerar relatorio do locatario
void reportSearch(locatario *loc,int parameter, prop *owner, imovel *immobiles){
	int  locQtd, queryDay, rowCnt=0, dr=0;
	char flName[]="locatario.bin",emptyStr[]="", st='L';
	FILE *frReader=NULL;
	
	do{
		printf("\nDigite o dia para gerar o relatorio: \n");
		scanf("%i",&queryDay);
		fflush(stdin);
		
		if(queryDay<=0 || queryDay>31){
			system("cls");
			printf("\n Informe um dia valido!\n");
		}
	}while(queryDay<=0 || queryDay>31);
	
	locQtd = checkFile(flName);
	
	if((frReader=fopen(flName,"rb"))==NULL){
		printf("\nNenhum dado encontrado!\n");
	}
	else{
		while(dr<locQtd){
			fseek(frReader,dr*sizeof(locatario),0);
			fread(loc,sizeof(locatario),1,frReader);
			
			if(loc->dia_venc==queryDay){
				if(rowCnt==0){
					system("cls");
					printf("\n Relatorio de contratos com o vencimento do aluguel no dia: %02d\n\n",queryDay);
				}
				immobileSearch(immobiles,6,loc->reg_imov,emptyStr,st);
				ownersSelectBy(owner,4,emptyStr,immobiles->reg_imov);
				reportShowOff(loc,owner,immobiles);
				rowCnt++;
			}
			dr++;
		}
		fclose(frReader);
		if(rowCnt==0)
			printf("\n Nenhum contrato possui o dia de vencimento informado!\n");
	}
	system("pause");
	system("cls");
}

//Fun? para encerrar contratos
void shutDownContract(locatario *loc,prop *owners,imovel *immobiles){
	int  flPos, dx=0, inx, response;
	int  contractDay,contractMonth,contractYear;
	int  dateDay,dateMonth, dateYear;
	char auxStr[15], confirm, strEmpty[]="", update[]="rb+", imEmpty='L', nullCpf[]="@";
	
	do{
		printf("\nInforme o CPF do locatario para cancelar o contrato: ");
		gets(auxStr);
		fflush(stdin);
		if(inputFilter(auxStr,1)==-1)
			printf("\nInforme um CPF valido com pontos e hifen!\n");
	}while(inputFilter(auxStr,1)==-1);
	
	flPos = locSearch(loc,3,dx,auxStr);
	
	if(flPos != 0){
		printf("\n Locatario encontrado:\n\n");
		LocShowOff(loc);
		do{
			printf("\n Deseja encerrar o contrato do locatario encontrado? (S/N)");
			scanf("%c",&confirm);
			fflush(stdin);
		}while(convertUpperCase(confirm)!='N' && convertUpperCase(confirm)!='S');
		
		if(convertUpperCase(confirm)=='S'){
			
			//Consultar imovel alugado pelo locat?o para consultar o valor de uma possl multa
			immobileSearch(immobiles,6,loc->reg_imov,strEmpty,imEmpty);
			
			do{
				printf("\nInforme a data atual para encerrar o contrato: ");
				gets(auxStr);
				fflush(stdin);
			}while(inputFilter(auxStr,5)==-1);
			
			// para validar a data de t?ino verificou-se a partir da soma dos respectivos nmeros na tabela ASCII
			/*
				exemplo "23"
				2 = 50 : 50 - 48 (zero na ASC) = 2 * 10 = 20
				3 = 51 : 51 - 48 (zero na ASC) = 3 * 1 = 3
				20+3=23 int
			*/
			
			contractYear  = 10 * (*(loc->termino+6)-48) + 1 * (*(loc->termino+7)-48);
			contractMonth = 10 * (*(loc->termino+3)-48) + 1 * (*(loc->termino+4)-48);
			contractDay   = 10 * (*(loc->termino+0)-48) + 1 * (*(loc->termino+1)-48);
			
			dateYear  =  10 * (*(auxStr+6)-48) + 1 * (*(auxStr+7)-48);
			dateMonth =  10 * (*(auxStr+3)-48) + 1 * (*(auxStr+4)-48);
			dateDay   =  10 * (*(auxStr+0)-48) + 1 * (*(auxStr+1)-48);
			
			//Valida-se se a data atual ?enor que a data de t?ino do contrato
			if(dateYear <= contractYear){
				if(dateYear == contractYear){
					if(dateMonth <= contractMonth){
						if(dateMonth == contractMonth){
							if(dateDay < contractDay){
								printf("\n A data termino do contrato do locatario em questao seria %s.\n Como a data atual(%s) ocorreu antes que o previsto aplica-se uma multa no valor de R$%.2f!\n\n",loc->termino,auxStr,immobiles->valor);
							}
						}
						else{
							printf("\n A data termino do contrato do locatario em questao seria %s.\n Como a data atual (%s) ocorreu antes que o previsto aplica-se uma multa no valor de R$%.2f!\n\n",loc->termino,auxStr,immobiles->valor);
						}
					}
				}
				else{
					printf("\n A data termino do contrato do locatario em questao seria %s.\n Como a data atual (%s) ocorreu antes que o previsto aplica-se uma multa no valor de R$%.2f!\n\n",loc->termino,auxStr,immobiles->valor);
				}		
			}
			
			//===============================================================================================================
			
			//Coloca-se @ para deixar propriet?o livre
			strcpy(auxStr,loc->CPF);
			response = locSearch(loc,4,dx,auxStr);
			
		    strcpy(loc->CPF,"@");
			loc->dia_venc = 0;
			
			locWriter(loc,update,response);
			//===============================================================================================================
			//Procura propriet?o do im?? alugado
			ownersSelectBy(owners,4,strEmpty,immobiles->reg_imov);
			inx = owners->reg_prop;
			//Al?de retornar a posi? no arquivo, desloca ponteiro prop.
			response = ownersSelectBy(owners, 2, strEmpty, inx);
			//Como j?emos a posi? no arquivo, podemos fazer as altera?s nos im??s associados no propriet?o 
			//Para isso ?ecess?a uma varredura nos 5 im??s permitidos
			while(dx<owners->qtde_casa){
				if((owners->casa+dx)->num_casa == immobiles->reg_imov){
					(owners->casa+dx)->status_casa = 'L';
					dx = owners->qtde_casa;
				}
				dx++;
			}
			//Atualiza proprietario
			ownersWriter(owners, update, response);
			//===============================================================================================================
			
			inx = immobiles->reg_imov;
			//Retorna a posi? no arquivo e ponteiro deslocado na posi? do n do im??
			response = immobileSearch(immobiles,6,inx,strEmpty,imEmpty);
			//Como j?emos a posi? no arquivo, podemos fazer as altera?s no im?? que ser?lugado
			immobiles->status.sigla = 'L';
			//Atualiza-se
			immobilesWriter(immobiles,update,response);
			//===============================================================================================================
			printf("\n Contrato encerrado com sucesso!\n");
		}
	}
	else{
		printf("\n Nenhum locatario foi encontrado com o CPF informado, tente novamente!\n");
	}
	system("pause");
	system("cls");
}
//Fun? para encerrar contratos

//Atualiza dados do propriet?o
void ownerUpdate(prop *owner){
	int response,inx,opt;
	char emptyStr[]="", update[]="rb+";
	system("cls");
	
	do{
		inx = owner->reg_prop;
		response = ownersSelectBy(owner,2,emptyStr,inx);
		
		printf("\n\n Alterar proprietario:\n\n");
		printf(" Registro do proprietario: %d\n",owner->reg_prop);
		printf(" Nome                    : %s\n",owner->nome);
		printf(" CPF                     : %s\n",owner->CPF);
		printf(" Logradouro              : %s\n",owner->end_prop.logradouro);
		printf(" Bairro                  : %s\n",owner->end_prop.bairro);
		printf(" CEP                     : %s\n",owner->end_prop.CEP);
		printf(" Cidade                  : %s\n",owner->end_prop.cidade);
		printf(" Estado                  : %s\n",owner->end_prop.estado);
		printf(" Telefone                : %s\n",owner->end_prop.fone);
		printf(" Celular                 : %s\n",owner->end_prop.cel);
		printf(" E-mail                  : %s\n",owner->end_prop.email);
		
		printf("\n Deseja alterar que tipo de dados?\n");
		printf("\n [01] - Nome\n [02] - CPF\n [03] - Logradouro\n [04] - Bairro\n [05] - CEP\n [06] - Cidade\n [07] - Estado\n [08] - Telefone\n [09] - Celular\n [10] - E-mail\n [11] - Finalizar alteracoes\n Opcao:");
		scanf("%d",&opt);
		fflush(stdin);
		
		switch(opt){
			case 1:
				do{
					printf("\n Nome atual:%s\n Informe o novo nome do proprietario: ",owner->nome);
					gets(owner->nome);
					fflush(stdin);
				}while(strlen(owner->nome)==0);
				system("cls");
				//Atualiza proprietario
				ownersWriter(owner, update, response);
				printf("\n Proprietario atualizado!\n");
				system("pause");
			break;
			case 2:
				do{
					printf("\n CPF atual:%s\n Informe o novo CPF do proprietario: ",owner->CPF);
					gets(owner->CPF);
					fflush(stdin);
					if(inputFilter(owner->CPF,1)==-1)
						printf("\nInforme um CPF valido com pontos e hifen!\n");
				}while(inputFilter(owner->CPF,1)==-1);
				if(inputFilter(owner->CPF,2)==-1){
					system("cls");
					printf("\nCPF ja foi cadastrado por um proprietario, tente novamente!\n");
					system("pause");
				}
				else{
					system("cls");
					//Atualiza proprietario
					ownersWriter(owner, update, response);
					printf("\n Proprietario atualizado!\n");
				system("pause");
				}
			break;
			case 3:
				do{
					printf("\n Logradouro atual:%s\n Informe o novo logradouro do proprietario: ",owner->end_prop.logradouro);
					gets(owner->end_prop.logradouro);
					fflush(stdin);
				}while(strlen(owner->end_prop.logradouro)==0);
				system("cls");
				//Atualiza proprietario
				ownersWriter(owner, update, response);
				printf("\n Proprietario atualizado!\n");
				system("pause");
			break;
			case 4:
				do{
					printf("\n Bairro atual:%s\n Informe o novo bairro do proprietario: ",owner->end_prop.bairro);
					gets(owner->end_prop.bairro);
					fflush(stdin);
				}while(strlen(owner->end_prop.bairro)==0);
				system("cls");
				//Atualiza proprietario
				ownersWriter(owner, update, response);
				printf("\n Proprietario atualizado!\n");
				system("pause");
			break;
			case 5:
				do{
					printf("\n CEP atual:%s\n Informe o novo CEP do proprietario: ",owner->end_prop.CEP);
					gets(owner->end_prop.CEP);
					fflush(stdin);
					if(inputFilter(owner->end_prop.CEP,3)==-1)
						printf("\nInforme um CEP valido com hifen e numeros\n");
				}while(inputFilter(owner->end_prop.CEP,3)==-1);
				system("cls");
				//Atualiza proprietario
				ownersWriter(owner, update, response);
				printf("\n Proprietario atualizado!\n");
				system("pause");
			break;
			case 6:
				do{
					printf("\n Cidade atual:%s\n Informe a nova cidade do proprietario: ",owner->end_prop.cidade);
					gets(owner->end_prop.cidade);
					fflush(stdin);
				}while(strlen(owner->end_prop.cidade)==0);
				system("cls");
				//Atualiza proprietario
				ownersWriter(owner, update, response);
				printf("\n Proprietario atualizado!\n");
				system("pause");
			break;
			case 7:
				do{
					printf("\n Estado atual:%s\n Informe o novo estado do proprietario: ",owner->end_prop.estado);
					gets(owner->end_prop.estado);
					fflush(stdin);
				}while(strlen(owner->end_prop.estado)==0);
				system("cls");
				//Atualiza proprietario
				ownersWriter(owner, update, response);
				printf("\n Proprietario atualizado!\n");
				system("pause");
			break;
			case 8:
				do{
					printf("\n Telefone atual:%s\n Informe o novo telefone do proprietario: ",owner->end_prop.fone);
					gets(owner->end_prop.fone);
					fflush(stdin);
				}while(strlen(owner->end_prop.fone)==0);
				system("cls");
				//Atualiza proprietario
				ownersWriter(owner, update, response);
				printf("\n Proprietario atualizado!\n");
				system("pause");
			break;
			case 9:
				do{
					printf("\n Celular atual:%s\n Informe o novo celular do proprietario: ",owner->end_prop.cel);
					gets(owner->end_prop.cel);
					fflush(stdin);
				}while(strlen(owner->end_prop.cel)==0);
				system("cls");
				//Atualiza proprietario
				ownersWriter(owner, update, response);
				printf("\n Proprietario atualizado!\n");
				system("pause");
			break;
			case 10:
				do{
					printf("\n E-mail atual:%s\n Informe o novo e-mail do proprietario: ",owner->end_prop.email);
					gets(owner->end_prop.email);
					fflush(stdin);
				}while(strlen(owner->end_prop.email)==0);
				
				if(inputFilter(owner->end_prop.email,4)==-1){
					system("cls");
					printf("\nE-mail ja cadastrado, tente novamente!\n");
					system("pause");
				}
				else{
					system("cls");
					//Atualiza proprietario
					ownersWriter(owner, update, response);
					printf("\n Proprietario atualizado!\n");
					system("pause");
				}
			break;
			default:
				system("cls");
		}
	}while(opt !=11);
}
//Atualiza dados do propriet?o

//Atualiza dados do im??
void immobileUpdate(imovel *immobile){
	int response,inx,opt;
	char emptyStr[]="", update[]="rb+",imEmpty='L';
	system("cls");
	
	do{
		inx      = immobile->reg_imov;
		//Retorna a posi? no arquivo e ponteiro deslocado na posi? do n do im??
		response = immobileSearch(immobile,6,inx,emptyStr,imEmpty);
		
		printf("\n\n Alterar Imovel:\n\n");
		printf("\n Registro do imovel  : %d",immobile->reg_imov);
		printf("\n Logradouro          : %s",immobile->end_imov.logradouro);
		printf("\n Bairro              : %s",immobile->end_imov.bairro);
		printf("\n CEP                 : %s",immobile->end_imov.CEP);
		printf("\n Cidade              : %s\n",immobile->end_imov.cidade);
		printf("\n Area util           : %.2f m%c",immobile->area,253);
		printf("\n Quartos             : %i quarto(s)\n",immobile->quartos);
		printf("\n Valor do aluguel    : R$%.2f",immobile->valor);
		
		printf("\n Deseja alterar que tipo de dados?\n");
		printf("\n [1] - Logradouro\n [2] - Bairro\n [3] - CEP\n [4] - Cidade\n [5] - Area util\n [6] - Quantidade de quartos\n [7] - Valor do aluguel\n [8] - Finalizar alteracoes\n Opcao:");
		scanf("%d",&opt);
		fflush(stdin);
		
		switch(opt){
			case 1:
				do{
					printf("\n Logradouro atual:%s.\n Informe o novo logradouro do imovel: ",immobile->end_imov.logradouro);
					gets(immobile->end_imov.logradouro);
					fflush(stdin);
				}while(strlen(immobile->end_imov.logradouro)==0);
				system("cls");
				//Atualiza Imovel
				immobilesWriter(immobile,update,response);
				printf("\n Imovel atualizado!\n");
				system("pause");
			break;
			case 2:
				do{
					printf("\n Bairro atual:%s.\n Informe o novo bairro do imovel: ",immobile->end_imov.bairro);
					gets(immobile->end_imov.bairro);
					fflush(stdin);
				}while(strlen(immobile->end_imov.bairro)==0);
				system("cls");
				//Atualiza Imovel
				immobilesWriter(immobile,update,response);
				printf("\n Imovel atualizado!\n");
				system("pause");
			break;
			case 3:
				do{
					printf("\n CEP atual:%s.\n Informe o novo CEP do imovel: ",immobile->end_imov.CEP);
					gets(immobile->end_imov.CEP);
					fflush(stdin);
					if(inputFilter(immobile->end_imov.CEP,3)==-1)
						printf("\nInforme um CEP valido com hifen e numeros\n");
				}while(inputFilter(immobile->end_imov.CEP,3)==-1);
				system("cls");
				//Atualiza Imovel
				immobilesWriter(immobile,update,response);
				printf("\n Imovel atualizado!\n");
				system("pause");
			break;
			case 4:	
				do{
					printf("\n Cidade atual:%s.\n Informe a nova cidade do imovel: ",immobile->end_imov.cidade);
					gets(immobile->end_imov.cidade);
					fflush(stdin);
				}while(strlen(immobile->end_imov.cidade)==0);
				system("cls");
				//Atualiza Imovel
				immobilesWriter(immobile,update,response);
				printf("\n Imovel atualizado!\n");
				system("pause");
			break;
			case 5:	
				do{
					printf("\nArea util atual: %.2fm%c.\n Informe a nova area util do imovel em m%c: ",immobile->area,253,253);
					scanf("%f",&(immobile->area));
					fflush(stdin);
					if(immobile->area<=0)
						printf("\nInforme uma area util valida!\n");
				}while(immobile->area<=0);
				system("cls");
				//Atualiza Imovel
				immobilesWriter(immobile,update,response);
				printf("\n Imovel atualizado!\n");
				system("pause");
			break;
			case 6:	
				do{
					printf("\nQuantidade de quartos atuais: %d.\nInforme a nova quantidade de quartos do imovel: ",immobile->quartos);
					scanf("%i",&(immobile->quartos));
					fflush(stdin);
					if(immobile->quartos<=0)
						printf("\nInforme uma quantidade de quartos valida!\n");
				}while(immobile->quartos<=0);
				system("cls");
				//Atualiza Imovel
				immobilesWriter(immobile,update,response);
				printf("\n Imovel atualizado!\n");
				system("pause");
			break;
			case 7:	
				do{
					printf("\nValor atual do aluguel R$%.2f.\nInforme o novo valor do imovel: ",immobile->valor);
					scanf("%f",&(immobile->valor));
					fflush(stdin);
					if(immobile->valor<=0)
						printf("\nInforme um valor valido!\n");
				}while(immobile->valor<=0);
				system("cls");
				//Atualiza Imovel
				immobilesWriter(immobile,update,response);
				printf("\n Imovel atualizado!\n");
				system("pause");
			break;
			defaulf:
				system("cls");
		}
	}while(opt!=8);
}
//Atualiza dados do im??

//Atualiza dados do locatario
void locUpdate(locatario *loc){
	char emptyStr[]="", update[]="rb+";
	int response,inx,opt;
	int startYear,startMonth,startDay,endYear,endMonth,endDay;
	system("cls");
	
	do{
	inx = loc->reg_loc;
	response = locSearch(loc,5,inx,emptyStr);
	printf("\n\n Alterar locatario:\n\n");
	printf(" Registro do locatario   : %d\n",loc->reg_loc);
	printf(" Nome                    : %s\n",loc->nome);
	printf(" CPF                     : %s\n",loc->CPF);
	printf(" Logradouro              : %s\n",loc->end_loc.logradouro);
	printf(" Bairro                  : %s\n",loc->end_loc.bairro);
	printf(" CEP                     : %s\n",loc->end_loc.CEP);
	printf(" Cidade                  : %s\n",loc->end_loc.cidade);
	printf(" Estado                  : %s\n",loc->end_loc.estado);
	printf(" Telefone                : %s\n",loc->end_loc.fone);
	printf(" Celular                 : %s\n",loc->end_loc.cel);
	printf(" E-mail                  : %s\n",loc->end_loc.email);
	printf(" Dia de vencimento       : %02d\n",loc->dia_venc);
	printf(" Data de inicio          : %s\n",loc->inicio);
	printf(" Data de termino         : %s\n",loc->termino);
	
	printf("\n Deseja alterar que tipo de dados?\n");
	printf("\n [01] - Nome\n [02] - CPF\n [03] - Logradouro\n [04] - Bairro\n [05] - CEP\n [06] - Cidade\n [07] - Estado\n [08] - Telefone\n [09] - Celular\n [10] - E-mail\n [11] - Dia de vencimento\n [12] - Data de inicio\n [13] - Data de termino\n [14] - Finalizar alteracoes\n Opcao:");
	scanf("%d",&opt);
	fflush(stdin);
	
	switch(opt){
		case 1:
			do{
				printf("\n Nome atual:%s\n Informe o novo nome do locatario: ",loc->nome);
				gets(loc->nome);
				fflush(stdin);
			}while(strlen(loc->nome)==0);
			system("cls");
			//Atualiza locatario
			locWriter(loc,update,response);
			printf("\n Locatario atualizado!\n");
			system("pause");
		break;
		case 2:
			do{
				printf("\n CPF atual:%s\n Informe o novo CPF do locatario: ",loc->CPF);
				gets(loc->CPF);
				fflush(stdin);
				if(inputFilter(loc->CPF,1)==-1)
					printf("\nInforme um CPF valido com pontos e hifen!\n");
			}while(inputFilter(loc->CPF,1)==-1);
			if(inputFilter(loc->CPF,6)==-1){
				system("cls");
				printf("\nCPF ja foi cadastrado por um locatario, tente novamente!\n");
				system("pause");
			}
			else{
				system("cls");
				//Atualiza locatario
				locWriter(loc,update,response);
				printf("\n Locatario atualizado!\n");
				system("pause");
			}
		break;
		case 3:
			do{
				printf("\n Logradouro atual:%s\n Informe o novo logradouro do locatario: ",loc->end_loc.logradouro);
				gets(loc->end_loc.logradouro);
				fflush(stdin);
			}while(strlen(loc->end_loc.logradouro)==0);
			system("cls");
			//Atualiza locatario
			locWriter(loc,update,response);
			printf("\n Locatario atualizado!\n");
			system("pause");
		break;
		case 4:
			do{
				printf("\n Bairro atual:%s\n Informe o novo bairro do locatario: ",loc->end_loc.bairro);
				gets(loc->end_loc.bairro);
				fflush(stdin);
			}while(strlen(loc->end_loc.bairro)==0);
			system("cls");
			//Atualiza locatario
			locWriter(loc,update,response);
			printf("\n Locatario atualizado!\n");
			system("pause");
		break;
		case 5:
			do{
				printf("\n CEP atual:%s\n Informe o novo CEP do locatario: ",loc->end_loc.CEP);
				gets(loc->end_loc.CEP);
				fflush(stdin);
				if(inputFilter(loc->end_loc.CEP,3)==-1)
					printf("\nInforme um CEP valido com hifen e numeros\n");
			}while(inputFilter(loc->end_loc.CEP,3)==-1);
			system("cls");
			//Atualiza locatario
			locWriter(loc,update,response);
			printf("\n Locatario atualizado!\n");
			system("pause");
		break;
		case 6:
			do{
				printf("\n Cidade atual:%s\n Informe a nova cidade do locatario: ",loc->end_loc.cidade);
				gets(loc->end_loc.cidade);
				fflush(stdin);
			}while(strlen(loc->end_loc.cidade)==0);
			system("cls");
			//Atualiza locatario
			locWriter(loc,update,response);
			printf("\n Locatario atualizado!\n");
			system("pause");
		break;
		case 7:
			do{
				printf("\n Estado atual:%s\n Informe o novo estado do locatario: ",loc->end_loc.estado);
				gets(loc->end_loc.estado);
				fflush(stdin);
			}while(strlen(loc->end_loc.estado)==0);
			system("cls");
			//Atualiza locatario
			locWriter(loc,update,response);
			printf("\n Locatario atualizado!\n");
			system("pause");
		break;
		case 8:
			do{
				printf("\n Telefone atual:%s\n Informe o novo telefone do locatario: ",loc->end_loc.fone);
				gets(loc->end_loc.fone);
				fflush(stdin);
			}while(strlen(loc->end_loc.fone)==0);
			system("cls");
			//Atualiza locatario
			locWriter(loc,update,response);
			printf("\n Locatario atualizado!\n");
			system("pause");
		break;
		case 9:
			do{
				printf("\n Celular atual:%s\n Informe o novo celular do locatario: ",loc->end_loc.cel);
				gets(loc->end_loc.cel);
				fflush(stdin);
			}while(strlen(loc->end_loc.cel)==0);
			system("cls");
			//Atualiza locatario
			locWriter(loc,update,response);
			printf("\n Locatario atualizado!\n");
			system("pause");
		break;
		case 10:
			do{
				printf("\n E-mail atual:%s\n Informe o novo e-mail do locatario: ",loc->end_loc.email);
				gets(loc->end_loc.email);
				fflush(stdin);
			}while(strlen(loc->end_loc.email)==0);
			
			if(inputFilter(loc->end_loc.email,4)==-1){
				system("cls");
				printf("\nE-mail ja cadastrado, tente novamente!\n");
				system("pause");
			}
			else{
				system("cls");
				//Atualiza locatario
				locWriter(loc,update,response);
				printf("\n Locatario atualizado!\n");
				system("pause");
			}
		break;
		case 11:
			do{
				printf("\n Dia de vencimento atual:%02d\n Informe o novo dia de vencimento do locatario: ",loc->dia_venc);
				scanf("%i",&(loc->dia_venc));
				fflush(stdin);
			}while(loc->dia_venc<=0 || loc->dia_venc>31);
			system("cls");
			//Atualiza locatario
			locWriter(loc,update,response);
			printf("\n Locatario atualizado!\n");
			system("pause");
		break;
		case 12:
			do{
				printf("\n Data de inicio atual:%s\n Informe a nova data de inicio do locatario: ",loc->inicio);
				gets(loc->inicio);
				fflush(stdin);
			}while(inputFilter(loc->inicio,5)==-1);
			
			//Transforma data utilizando a tabela ASCII, formando nmeros inteiros
			// como '0' = 48, utiliza-se de um substra? para converter os nmeros
			startYear  = 10 * (*(loc->inicio+6)-48) + 1 * (*(loc->inicio+7)-48);
			startMonth = 10 * (*(loc->inicio+3)-48) + 1 * (*(loc->inicio+4)-48);
			startDay   = 10 * (*(loc->inicio+0)-48) + 1 * (*(loc->inicio+1)-48);
			
			endYear  = 10 * (*(loc->termino+6)-48) + 1 * (*(loc->termino+7)-48);
			endMonth = 10 * (*(loc->termino+3)-48) + 1 * (*(loc->termino+4)-48);
			endDay   = 10 * (*(loc->termino+0)-48) + 1 * (*(loc->termino+1)-48);
			
			//Compara-se os campos das datas em valores inteiros para validar se a data informada ?nterior a de t?ino
			if(startYear <= endYear){
				if(startYear == endYear ){
					if(startMonth <= endMonth){
						if(startMonth == endMonth){
							if(startDay < endDay){
								system("cls");
								//Atualiza locatario
								locWriter(loc,update,response);
								printf("\n Locatario atualizado!\n");
								system("pause");	
							}
							else{
								system("cls");
								printf("\n Informe uma data de inicio anterior a data de termino!\n");
								system("pause");
							}
						}else{
							system("cls");
							//Atualiza locatario
							locWriter(loc,update,response);
							printf("\n Locatario atualizado!\n");
							system("pause");	
						}
					}
					else{
						system("cls");
						printf("\n Informe uma data de inicio anterior a data de termino!\n");
						system("pause");
					}
				}
				else{
					system("cls");
					//Atualiza locatario
					locWriter(loc,update,response);
					printf("\n Locatario atualizado!\n");
					system("pause");	
				}
			}
			else{
				system("cls");
				printf("\nInforme uma data de inicio anterior a data de termino!\n");
				system("pause");	
			}
			
		break;
		case 13:
			do{
				printf("\n Data de termino atual:%s\n Informe a nova data de termino do locatario: ",loc->termino);
				gets(loc->termino);
				fflush(stdin);
			}while(inputFilter(loc->termino,5)==-1);
			
			//Transforma data utilizando a tabela ASCII, formando nmeros inteiros
			// como '0' = 48, utiliza-se de um substra? para converter os nmeros
			startYear  = 10 * (*(loc->inicio+6)-48) + 1 * (*(loc->inicio+7)-48);
			startMonth = 10 * (*(loc->inicio+3)-48) + 1 * (*(loc->inicio+4)-48);
			startDay   = 10 * (*(loc->inicio+0)-48) + 1 * (*(loc->inicio+1)-48);
			
			endYear  = 10 * (*(loc->termino+6)-48) + 1 * (*(loc->termino+7)-48);
			endMonth = 10 * (*(loc->termino+3)-48) + 1 * (*(loc->termino+4)-48);
			endDay   = 10 * (*(loc->termino+0)-48) + 1 * (*(loc->termino+1)-48);
			
			//Compara-se os campos das datas em valores inteiros para validar se a data informada ?osterior a de inicio
			if(endYear >= startYear){
				if(endYear == startYear ){
					if(endMonth >= startMonth){
						if(endMonth == startMonth){
							if(endDay > startDay){
								system("cls");
								//Atualiza locatario
								locWriter(loc,update,response);
								printf("\n Locatario atualizado!\n");
								system("pause");
							}
							else{
								system("cls");
								printf("\n Informe uma data de termino posterior a data de inicio!\n");
								system("pause");
							}
						}else{
							system("cls");
							//Atualiza locatario
							locWriter(loc,update,response);
							printf("\n Locatario atualizado!\n");
							system("pause");
						}
					}
					else{
						system("cls");
						printf("\n Informe uma data de termino posterior a data de inicio!\n");
						system("pause");
					}
				}
				else{
					system("cls");
					//Atualiza locatario
					locWriter(loc,update,response);
					printf("\n Locatario atualizado!\n");
					system("pause");
				}
			}
			else{
				system("cls");
				printf("\n Informe uma data de termino posterior a data de inicio!\n");
				system("pause");
				system("pause");
			}
			
		break;
		default:
			system("cls");
		}
	}while(opt !=14);
}
//Atualiza dados do locatario

//Atualiza dados
void updateData(locatario *loc,prop *owners,imovel *immobiles){
	int opt, auxReg;
	char auxStr[15],strEmpty[]="",imStatusEmpty='L',imStatusOccupied='A';
	
	do{
		printf("\n Dejesa alterar qual tipo de dados?\n [1] - Dados do proprietario\n [2] - Dados do imovel\n [3] - Dados do locatario\n [4] - Sair\n Opcao:");
		scanf("%d",&opt);
		fflush(stdin);
		if(opt<1 || opt>4)
			system("cls");
	}while(opt<1 || opt>4);
	
	system("cls");
	
	switch(opt){
		//Caso seja para altrar dados do propriet?o
		case 1:
			do{
				printf("\n Informe o CPF do proprietario a ser alterado: ");
				gets(auxStr);
				fflush(stdin);
			}while(inputFilter(auxStr,1)==-1);
			if(ownersSelectBy(owners,1,auxStr,auxReg)!=-1){
				ownerUpdate(owners);
			}
			else{
				printf("\n Nenhum proprietario possui o CPF informado, tente novamente!\n\n");
				system("pause");
			}
		break;
		//Caso seja para altrar dados do im??
		case 2:
			do{
				printf("\n Informe o n%c de registro do imovel a ser alterado: ",167);
				scanf("%d",&auxReg);
				fflush(stdin);
			}while(auxReg<=0);
			
			if(immobileSearch(immobiles,5,auxReg,strEmpty,imStatusEmpty)!=0){
				immobileUpdate(immobiles);
			}
			else if(immobileSearch(immobiles,5,auxReg,strEmpty,imStatusOccupied) != 0){
				immobileUpdate(immobiles);
			}
			else{
				//Caso n?encontre o im??
				system("cls");
				printf("\n O imovel informado nao esta cadastrado em nossos dados, por favor tente novamente!\n\n");
				system("pause");
			}
		break;
		//Caso seja para altrar dados do locat?o
		case 3:
			do{
				printf("\n Informe o CPF do locatario a ser alterado: ");
				gets(auxStr);
				fflush(stdin);
			}while(inputFilter(auxStr,1)==-1);
			if(locSearch(loc,3,auxReg,auxStr)!=0){
				locUpdate(loc);
			}
			else{
				printf("\n Nenhum locatario possui o CPF informado, tente novamente!\n\n");
				system("pause");
			}
			
		break;
		default:
			system("cls");
	}
	system("cls");
}
//Atualiza dados

