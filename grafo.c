#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_VERTICES 100
typedef struct {
 int **adj_matrix;
 int num_vertices;
} Grafo;
int num_vertices; // Variável global para o número de vértices
// Função para criar um grafo com um número específico de vértices
Grafo *criarGrafo(int num_vertices) {
 Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
 grafo->num_vertices = num_vertices;
 
 // Aloca a matriz de adjacência e inicializa com zeros
 grafo->adj_matrix = (int **)malloc(num_vertices * sizeof(int *));
 int i;
 for (i = 0; i < num_vertices; i++) {
 grafo->adj_matrix[i] = (int *)calloc(num_vertices, sizeof(int));
 }
 
 return grafo;
}
// Função para adicionar uma aresta entre dois vértices
void adicionarAresta(Grafo *grafo, int vertice1, int vertice2) {
 grafo->adj_matrix[vertice1][vertice2] = 1;
 grafo->adj_matrix[vertice2][vertice1] = 1;
}
// Função para liberar a memória alocada para o grafo
void liberarGrafo(Grafo *grafo) {
 int i;
 for (i = 0; i < grafo->num_vertices; i++) {
 free(grafo->adj_matrix[i]);
 }
 free(grafo->adj_matrix);
 free(grafo);
}
// Função para imprimir a matriz de adjacência do grafo
void imprimirGrafo(Grafo *grafo) {
 printf("Matriz de Adjacência:\n");
 int i, j;
 for (i = 0; i < grafo->num_vertices; i++) {
 for (j = 0; j < grafo->num_vertices; j++) {
 printf("%d ", grafo->adj_matrix[i][j]);
 }
 printf("\n");
 }
}
// Função para verificar se há um caminho entre origem e destino usando DFS
int temCaminho(Grafo *grafo, int origem, int destino, int *visitados, int 
*caminho, int passo) {
 caminho[passo] = origem; // Adiciona o vértice ao caminho
 if (origem == destino) {
 return 1; // Há um caminho entre origem e destino
 }
 
 visitados[origem] = 1; // Marcar o vértice como visitado
 
 int i;
 for (i = 0; i < grafo->num_vertices; i++) {
 if (grafo->adj_matrix[origem][i] && !visitados[i]) {
 if (temCaminho(grafo, i, destino, visitados, caminho, passo + 
1)) {
 return 1;
 }
 }
 }
 
 // Se não houver caminho, desmarcar o vértice
 visitados[origem] = 0;
 return 0;
}
int main() {
 setlocale(LC_ALL,"Portuguese");
 int opcao, origem, destino;
 Grafo *grafo = NULL;
 int i, j; // Variáveis de controle
 
 do {
 // Menu de opções
 printf("\n[1] Novo Grafo\n[2] Visualizar Grafo\n[3] Visualizar 
Caminho\n[0] Finalizar\n");
 printf("Escolha uma opção: ");
 scanf("%d", &opcao);
 switch (opcao) {
 case 1:
 // Criar um novo grafo
 if (grafo != NULL) {
 liberarGrafo(grafo);// Libera o grafo anterior se 
existir
 }
 printf("\nInsira o número de vértices: \n");
 scanf("%d", &num_vertices); // Captura o número de vértices
 grafo = criarGrafo(num_vertices); // Cria o grafo com o 
número especificado
 printf("\nInsira as conexões entre os vértices (1 para 
conectado, 0 para não conectado):\n");
 for (i = 0; i < num_vertices; i++) {
 for (j = i; j < num_vertices; j++) {
 if (i == j) {
 printf("%d para %d: ", i + 1, j + 1);
scanf("%d", &grafo->adj_matrix[i][j]);
 } else {
 printf("%d para %d: ", i + 1, j + 1);
scanf("%d", &grafo->adj_matrix[i][j]);
grafo->adj_matrix[j][i] = grafo-
>adj_matrix[i][j]; // A matriz é simétrica
 }
 }
 }
 break;
 case 2:
 // Visualizar o grafo
 if (grafo != NULL) {
 system("cls || clear"); // Limpa a tela
imprimirGrafo(grafo);
 } else {
system("cls || clear");
 printf("!!!Grafo não foi criado ainda!!!\n");
 }
 break;
 case 3:
 // Visualizar caminho entre vértices
 if (grafo != NULL) {
 system("cls || clear");
 printf("\nInsira o vértice de origem: ");
 scanf("%d", &origem);
 printf("Insira o vértice de destino: ");
 scanf("%d", &destino);
 
 // Verificar se há um caminho entre origem e 
destino
 int *visitados = (int *)calloc(grafo-
>num_vertices, sizeof(int));
 int *caminho = (int *)calloc(grafo->num_vertices, 
sizeof(int));
 if (temCaminho(grafo, origem - 1, destino - 1, 
visitados, caminho, 0)) {
 system("cls || clear");
 printf("Existe um caminho entre o vértice %d e 
o vértice %d.\n", origem, destino);
 printf("\nCaminho: \n");
 printf("%d", origem);
 int i;
 for (i = 1; caminho[i] != destino - 1; i++) {
 printf(" -> %d", caminho[i] + 1);
 }
 printf(" -> %d\n", destino);
 } else {
 // Se não houver caminho ou os vértices 
estiverem fora do intervalo válido
 if (origem < 1 || origem > grafo->num_vertices 
|| destino < 1 || destino > grafo->num_vertices) {
 printf("\nNão há caminho entre o 
vértice.\n");
 } else {
 printf("\nNão há caminho entre o vértice 
%d e o vértice %d.\n", origem, destino);
 }
 } 
 free(visitados);
 free(caminho);
 } else {
 system("cls || clear");
 printf("\n!!!!Grafo não foi criado ainda!!!\n");
 }
 break;
 case 0:
 // Finalizar o programa
 if (grafo != NULL) {
 liberarGrafo(grafo); // Libera a memória alocada para o 
grafo
 
 }
 system("cls || clear");
 printf("\nPrograma finalizado.\n");
 break;
 default:
 system("cls || clear");
 printf("\nOpção inválida. Tente novamente.\n");
 } 
 } while (opcao != 0);
 return 0;
}
