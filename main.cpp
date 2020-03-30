#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Definição Tipo de No
typedef struct TipoNo{
	int codigo;
	char nome[50];
	float credito;
	struct TipoNo *proximo;
	struct TipoNo *anterior;
}TNo;

//Definição Tipo de Lista
typedef struct TipoLista{
	TNo *inicio = NULL;
	TNo *fim = NULL;
}TLista;

//Protótipo de funções
void inicializaLista(TLista *pLista);
void inserirNoInicio(TLista *pLista);
void inserirNoFim(TLista *pLista);
void removerNoInicio(TLista *pLista);
void removerNoFim(TLista *pLista);
void removerPorCodigo(TLista *pLista);
void salvarEmArquivo(TLista *pLista);
void lerDeArquivo(TLista *pLista);
void limparMemoria(TLista *pLista);
void listarRegistros(TLista *pLista);

//Variaveis globais
TLista ListaDuplEncadeada;
 
//Função principal
int main(int argc, char** argv) {
	setlocale(LC_ALL,"Portuguese"); //inserir assentuação
	
	int op;
	
	//define ponteiro inicio e fim como nulo
	inicializaLista(&ListaDuplEncadeada);
	
	do{
		// system("cls");
		printf("Opções: \n\n");
		printf("1  - insira no início\n");
		printf("2  - insira no fim\n");
		printf("3  - remova do início\n");
		printf("4  - remova do fim\n");
		printf("5  - remova através de um código específico\n");
		printf("6  - liste os registros cadastrados\n");
		printf("7  - salvar em arquivo\n");
		printf("8  - ler de arquivo\n");
		printf("9 - liberar memória\n");
		printf("0  - Sair\n\n");
		printf("Insira a opção desejada: ");
		scanf("%d", &op);
		
		switch(op){	
			case 1:
				inserirNoInicio(&ListaDuplEncadeada);
			break;
			
			case 2:
				inserirNoFim(&ListaDuplEncadeada);
			break;
			
			case 3:
				removerNoInicio(&ListaDuplEncadeada);
			break;
			
			case 4:	
				removerNoFim(&ListaDuplEncadeada);
			break;
			
			case 5:	
				removerPorCodigo(&ListaDuplEncadeada);
			break;
			
			case 6:
				listarRegistros(&ListaDuplEncadeada);
			break;
			
			case 7:	
				salvarEmArquivo(&ListaDuplEncadeada);
			break;
			
			case 8:	
				lerDeArquivo(&ListaDuplEncadeada);		
			break;
			
			case 9:	
				limparMemoria(&ListaDuplEncadeada);			
			break;	
		}
	}while(op != 0);
	return 0;
}

void inicializaLista(TLista *pLista){
	pLista->inicio = NULL;
	pLista->fim = NULL;
}

void inserirNoInicio(TLista *pLista){
	TNo *novoElemento;
	novoElemento = new TNo;
	
	printf("\nDigite o nome: ");
	scanf("%s", &novoElemento->nome);
	fflush(stdin);
	printf("Digite o código: ");
	scanf("%d", &novoElemento->codigo);
	printf("Digite o crédito: ");
	scanf("%f", &novoElemento->credito);
	
	novoElemento->proximo = NULL;
	novoElemento->anterior = NULL;
	
	//Caso lista for vazia
	if(pLista->inicio == NULL ){
		pLista->inicio = novoElemento;
		pLista->fim = novoElemento;
	}else{
		//Caso lista estiver mais de um elemento
		pLista->inicio->anterior = novoElemento;
		novoElemento->proximo = pLista->inicio;
		pLista->inicio = novoElemento;
	}
}

void inserirNoFim(TLista *pLista){
	TNo *novoElemento;
	novoElemento = new TNo;
	
	printf("\nDigite o nome: ");
	scanf("%s", &novoElemento->nome);
	fflush(stdin);
	printf("Digite o código: ");
	scanf("%d", &novoElemento->codigo);
	printf("Digite o crédito: ");
	scanf("%f.2", &novoElemento->credito);
	
	novoElemento->proximo = NULL;
	novoElemento->anterior = NULL;	
	
	//Caso lista for vazia
	if(pLista->inicio == NULL ){
		pLista->inicio = novoElemento;
		pLista->fim = novoElemento;
	}else{
		//Caso lista estiver mais de um elemento
		pLista->fim->proximo = novoElemento;
		novoElemento->anterior = pLista->fim;
		pLista->fim = novoElemento;
	}	
}

void removerNoInicio(TLista *pLista){		
	
	if(pLista->inicio == NULL){
		printf("Lista vazia, impossivel remover\n");
	}else{
		TNo *aux, *atual;
		aux = pLista->inicio;
		
		printf("\nElemento removido:\nNome: %s\nCódigo %d\nCrédito: %.2f\n\n", aux->nome, aux->codigo, aux->credito);
		
		//Quando só restar 1 elemento na lista
		if(pLista->inicio == pLista->fim){
			inicializaLista(&ListaDuplEncadeada);
			aux = NULL;
		}else{
			//Quando a lista possuir mais de 1 elemento
			pLista->inicio = pLista->inicio->proximo;
			atual = pLista->inicio;
			atual->proximo = pLista->inicio->proximo;
			atual->anterior = NULL;
			free(aux);
		}
	}
}

void removerNoFim(TLista *pLista){
	
	if(pLista->inicio == NULL){
		printf("Lista vazia, impossivel remover\n");
	}else{
		TNo *aux, *atual;
		aux = pLista->fim;
		
		printf("\nElemento removido:\nNome: %s\nCódigo %d\nCrédito: %.2f\n\n", aux->nome, aux->codigo, aux->credito);
		
		//Quando só restar 1 elemento na lista
		if(pLista->inicio == pLista->fim){
			inicializaLista(&ListaDuplEncadeada);
			aux = NULL;
		}else{
			//Quando a lista possuir mais de 1 elemento
			pLista->fim = pLista->fim->anterior;
			atual = pLista->fim;
			atual->anterior = pLista->fim->anterior;
			atual->proximo = NULL;
			free(aux);
		}
	}
}

void removerPorCodigo(TLista *pLista){
	TNo *atual, *aux;
	
	atual = pLista->inicio;
	//Se a lista for fazia
	if(pLista->inicio == NULL){
		printf("\n--- Lista vazia ---\n\n");
	}else{
		//Caso lista possua elemento
		int codigo;
		printf("Digite o codigo que deseja buscar: ");
		scanf("%d", &codigo);
		
		while(atual != NULL){
		
			//quando código estiver no primeiro elemento
			if(codigo == atual->codigo && codigo == pLista->inicio->codigo){
				removerNoInicio(&ListaDuplEncadeada);
				return;
			} 	
			//quando código estiver no ultimo elemento
			else if(codigo == atual->codigo && codigo == pLista->fim->codigo){
				removerNoFim(&ListaDuplEncadeada);
				return;
			}
			//quando código for diferente do primeiro ou ultimo elemento
			else if(codigo == atual->codigo && codigo != pLista->fim->codigo && codigo != pLista->inicio->codigo){			
				printf("\nElemento removido:\nNome: %s\nCódigo %d\nCrédito: %.2f\n\n", atual->nome, atual->codigo, atual->credito);
				aux = atual;
				atual->anterior->proximo = atual->proximo;
				atual->proximo->anterior = atual->anterior;
				free(aux);
				return;
			}
		atual= atual->proximo;
		}
		printf("\nCódigo não encontrado!\n\n");
	}
}

void salvarEmArquivo(TLista *pLista){
	FILE *file;
	//Cria um arquivo texto para salvar lista
	file = fopen("arqGrav.txt", "w+");  
	
	TNo *aux;
	aux = pLista->inicio;
	
	if(pLista->inicio == NULL){
		printf("\n--- Lista vazia ---\n\n");
	}else{
		while(aux != NULL){
			fprintf(file, "%d;%s;%f\n", aux->codigo, aux->nome, aux->credito);
			aux = aux->proximo;
		}		
	}
	fclose(file);
}

void lerDeArquivo(TLista *pLista){
	FILE *pFile;
	pFile = fopen("arqLer.txt", "r");
	
	//Caso ponteiro que aponta para lista não encontrar o arquivo de texto criado
	if(pFile == NULL){
		printf("Arquivo não pode ser aberto\n");
		system("pause");
		return;
	}
	
	char string[100];
	char delimiters[] = ";";
	char *token;
	 
	while(fgets(string, 100, pFile) != NULL){
		TNo *novoElemento;
		novoElemento = new TNo;
		
		novoElemento->proximo = NULL;
		novoElemento->anterior = NULL;
		
		//converte string para inteiro através do delimitador 
		token = strtok (string, delimiters); 
		novoElemento->codigo = strtol(token,NULL,10); //converte string para inteiro
		
		//copia chave que possui nome para novoElemento->nome
		token = strtok (NULL, delimiters); 
		strcpy(novoElemento->nome,token);
		
		//Converte string para float 
		token = strtok (NULL, delimiters); 
		novoElemento->credito = strtof(token,NULL); 
		
		if(pLista->inicio == NULL ){
			pLista->inicio = novoElemento;
			pLista->fim = novoElemento;
		}else{
			//Incrementa elemento adquirido no arquivo para dentro da lista
			pLista->fim->proximo = novoElemento;
			novoElemento->anterior = pLista->fim;
			pLista->fim = novoElemento;
		}	
	}
}

void limparMemoria(TLista *pLista){
	TNo *atual, *aux;
	atual = pLista->inicio;
	
	if(pLista->inicio == NULL){
		printf("\n--- Lista vazia ---\n\n");
		return;
	}else{
		while(atual != NULL){
			
			aux = atual; 				//elemento atual é salvo em ponteiro auxiliar
			atual = atual->proximo; 	//elemento atual atribui o proximo elemento
			free(aux);					//ponteiro elemento atual tem sua memoria limpada
		}
		//Limpa ponteiro de inicio e fim
		inicializaLista(&ListaDuplEncadeada);
		
		printf("\n--- memória liberada --- \n\n");	
		return;
	}
}

void listarRegistros(TLista *pLista){
	TNo *aux;
	aux = pLista->inicio;
	
	if(pLista->inicio == NULL){
		printf("\n--- Lista vazia ---\n\n");
	}else{
		while(aux != NULL){
			printf("\nNome: %s\n", aux->nome);
			printf("Código: %d\n", aux->codigo);
			printf("Crédito: %.2f\n", aux->credito);

			aux = aux->proximo;
		}
		printf("\n--- fim da lista --- \n\n");
		system("pause");		
	}
}
