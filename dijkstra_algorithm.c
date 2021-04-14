#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

struct vertice{
	int id;
	int idPrev;
	int d;
	int flag;
};
typedef struct vertice v;

void carregarValoresDeVertices(v **vertices);
void menorCaminho(v **vertices, int vOrigem);
int buscaAberto(v **vertices);
int vericarPercurso(v **vertices, int vOrigem, int vDestino);
void mostrarMatrizDeAdjacencia();
void analisarCaminho(v **vertices);
void adicionarVertice(v **vertices);
void retirarVertice(v **vertices);
void editarConexoes();

int nVertices = 3;
int mAdjacentes[20][20] = {
	
	{-1, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int main(int argc, char **argv)
{
	v *vertices = NULL;
	int switchOptions = 0;
	
	printf("\nOlá, por default, temos 3 vertices.");
	mostrarMatrizDeAdjacencia();
	while(switchOptions != 6){

		printf("\nEscolha uma das opções: \n1. Analisar um caminho\n2. Adicionar um vértice\n3. Retirar um vértice\n4. Editar conexoes\n5. Mostra matriz de adjacência\n6. Sair\nEscreva a opção: ");
		scanf("%d", &switchOptions);

		switch (switchOptions){
			case 1:
				analisarCaminho(&vertices);
				break;
			case 2:
				adicionarVertice(&vertices);
				break;
			case 3:
				retirarVertice(&vertices);
				break;
			case 4:
				editarConexoes();
				break;
			case 5:
				mostrarMatrizDeAdjacencia();
				break;
			case 6:
				printf("\n\nSaindo...\n\n");
				break;
			default:
				printf("\nInvalid choice... Try again...\n");
		}
	}
	free(vertices);
	return 0;
}

void carregarValoresDeVertices(v **vertices){
	
	*vertices = (v*) malloc(nVertices*sizeof(v));
	v *p;
	int i = 0;
	
	if(!(*vertices)){
		printf("No memory avaliable! Exiting... ");
		exit(1);
	}
	while(i < nVertices){
		p = *vertices;
		p = p + (sizeof(v)*i);
		p->id = i;
		p->idPrev = -1;
		p->d = INT_MAX/2;
		p->flag = 0;
		i++;
	}
}
void menorCaminho(v **vertices, int vOrigem){
	
	v *p1, *p2;
	int count = nVertices;
	int tmpId = 0;
	p1 = p2 = *vertices;
	p1 = p1 + (sizeof(v)*vOrigem);
	p1->d = 0;
	p1->idPrev = p1->id;
	
	do{
		
		for(int i = 0; i<nVertices; i++){
		
			if(mAdjacentes[p1->id][i] > 0 && i != vOrigem){
				p2 = *vertices + (sizeof(v)*i);
				if((mAdjacentes[p1->id][i] + p1->d) < p2->d){
					p2->d = mAdjacentes[p1->id][i] + p1->d;
					p2->idPrev = p1->id;
				} 
			}
		}
	
		p1->flag = 1;
		tmpId = buscaAberto(&(*vertices));
		
		if(tmpId == -1){
			break;
		}
		p1 = *vertices + (tmpId * sizeof(v));
		count--;
		
	}while(count > 0);
	
}
int buscaAberto(v **vertices){
	
	v *p1;
	int tmpId = - 1, tmp = INT_MAX-1;
	p1 = *vertices;
	
	for(int i = 0; i<nVertices; i++){
		if(p1->flag == 0 && p1->d != INT_MAX/2){
			if(p1->d < tmp){
				tmp = p1->d;
				tmpId = p1->id;
			}
		}
		p1 = p1 + (sizeof(v));
	}
	return tmpId;
}
int vericarPercurso(v **vertices, int vOrigem, int vDestino){
	
	v *p = *vertices;
	int i = -1;
	int flag = 0;
	p = p + (vDestino * sizeof(v));
	
	if((vOrigem >= nVertices || vOrigem < 0)){
		flag = 1;
		return flag; 
	}
	if((vDestino >= nVertices || vDestino < 0)){
		flag = 1;
		return flag; 
	}
	while(i != vOrigem){
		if(p->d != INT_MAX/2){
			p = *vertices + (p->idPrev * sizeof(v));
			i = p->id;
		}else{
			flag = 1;
			return flag;
		}
	}
	return flag;
}
void mostrarMatrizDeAdjacencia(){

	printf("\nEsta é a sua matriz de adjacencia: \n\n");
	printf("     ");
	for(int k = 0; k<nVertices; k++){
		printf("   %d   ", k);
	}
	printf("\n");
	for(int i = 0; i<nVertices; i++){
		printf("   %d", i);
			for(int j = 0; j<nVertices; j++){
				if(mAdjacentes[i][j] > 0){
					printf("   %d   ", mAdjacentes[i][j]);
				}else
					printf("       ");

		}
		
		printf("\n");
	}
}
void analisarCaminho(v **vertices){

	int n = 0, m = 0;
	int flag = -1, flag2 = 0;
	int vOrigem, vDestino;
	int vetPercurso[nVertices];
	v *p;

	while(n==0){
		
		carregarValoresDeVertices(&(*vertices));
		printf("\nQual o vértice de origem? ");
		scanf("%d", &vOrigem);
		printf("Qual o vértice de destino? ");
		scanf("%d", &vDestino);
		
		if(vDestino != vOrigem){
			menorCaminho(&(*vertices), vOrigem);
			flag2 = vericarPercurso(&(*vertices), vOrigem, vDestino);
			
			if(flag2 == 0){
			
				p = (*vertices) + (sizeof(v) * vDestino);
				printf("\nO percurso mais curto tem a distancia de %d e passa por: %d", p->d, vOrigem);
				
				flag = p->id;
				
				while(flag != vOrigem){
					
					vetPercurso[m] = p->id;
					p = (*vertices) + (sizeof(v) * p->idPrev);
					flag = p->id;
					m++;
				}
				while(m>0){
					printf(" -> %d",vetPercurso[m-1]);
					m--;
				}

			}else{
				printf("\nCaminho inexistente\n");}
		}else{
			printf("\nA vertice de origem e destino é a mesma. Distância = 0\n");}
		
		printf("\nDeseja sair ou analisar outro caminho? \n0. Ficar \n1. Sair\n");
		scanf("%d", &n);
	}
}
void adicionarVertice(v **vertices){

	int id = 0, tamAresta = 0, x = 0;
	int sentidoAresta = 0;
	nVertices++;
	*vertices = (v*) realloc(*vertices, sizeof(v) * nVertices);

	printf("\n\nO novo vertice tera o id: %d \nVamos digitar suas conexoes...\n", nVertices-1);
	do{
		
		printf("\nDigite o id do vertice com o qual sera feito conexao: ");
		scanf("%d", &id);
		printf("\nA nova vertice leva ou recebe a aresta?\n");
		printf("0. Leva\n1. Recebe\n2. Leva e Recebe\nEscreva a opcao: ");
		scanf("%d", &sentidoAresta);
		printf("\nDigite a distancia da aresta: ");
		scanf("%d", &tamAresta);
		
		if(id >= 0 && id < nVertices){
			if(sentidoAresta == 0){
				mAdjacentes[nVertices-1][id] = tamAresta;
			}
			else if(sentidoAresta == 1){
				mAdjacentes[id][nVertices-1] = tamAresta;
			}
			else if(sentidoAresta == 2){
				mAdjacentes[nVertices-1][id] = tamAresta;
				mAdjacentes[id][nVertices-1] = tamAresta;
			}
			else{
				printf("\n\nOpcao invalida\n\n");
			}

		}else{
			printf("\nVertice inexistente, tente novamente");
		}
		printf("\nDeseja adicionar outra conexao? \n0. Não\n1. Sim\nEscreva a opcao: ");
		scanf("%d", &x);

	}while(x != 0);
}
void retirarVertice(v **vertices){

	int idOut = 0;

	printf("Digite o id da vertice que queres retirar: ");
	scanf("%d", &idOut);

	if(idOut >= 0 && idOut < nVertices){

		for(int i = 0; i < nVertices; i++){

			mAdjacentes[idOut][i] = mAdjacentes[nVertices-1][i];
			if(mAdjacentes[i][nVertices-1]>-1){
				mAdjacentes[i][idOut] = mAdjacentes[i][nVertices-1];
			}
			else{
				mAdjacentes[i][idOut] = -1;
			}
		}
		nVertices--;
		*vertices = (v*) realloc(*vertices, sizeof(v) * nVertices);
		printf("\n\nRetirado com sucesso. O ultimo vertice recebera o id do vertice retirado\n\n");
	}
	else{
		printf("\nNao existe essa vertice...\n");
	}
}
void editarConexoes(){

	int editVert;
	int editArest;
	int tamAresta;
	int idAresta;

	printf("Qual vertice queres editar? ");
	scanf("%d", &editVert);
	printf("\nEste vertice tem aresta(s) orientada(s) para:");
	for(int i = 0; i < nVertices; i++){
		if(mAdjacentes[editVert][i] > -1){
			printf(" -- %d", i);
		}
	}
	printf("\n\nEscolha uma opcao: \n1. Retirar aresta\n2. Adicionar aresta\nEscrever opcao: ");
	scanf("%d", &editArest);
	if(editArest == 1){

		printf("\nEscreva o id da vertice para qual vai a aresta a ser retirada\nEscrever opcao: ");
		scanf("%d", &idAresta);
		if(idAresta >= 0 && idAresta<nVertices && idAresta != editVert){
			mAdjacentes[editVert][idAresta] = -1;
		}
		else
			printf("\n\nInvalid option...\n\n");
	}
	else if(editArest == 2){

		printf("\nEscreva o id da vertice para qual vai a aresta a ser adicionada\nEscrever opcao: ");
		scanf("%d", &idAresta);
		if(idAresta != editVert){
			printf("Qual o tamanho da aresta? ");
			scanf("%d", &tamAresta);
			if(idAresta >= 0 && idAresta<nVertices){
				mAdjacentes[editVert][idAresta] = tamAresta;
			}
			else
				printf("\n\nInvalid option...\n\n");
		}
		else
			printf("\n\nInvalid option...\n\n");
	}
	else{
		printf("\n\nInvalid Option...\n");
	}
}
