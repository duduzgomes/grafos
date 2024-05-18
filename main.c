#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int matriz[100][100];
int l=0, c=0;
int visitado[10];
int caminho[10];
int caminho_encontrado[10][10];
int custo[10];
int noInicial=0, noFinal=0;

    
void criar_matriz(){
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            matriz[i][j] = 0;  
        }
    }
}

void alimentar_automatico(){
    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            matriz[i][j] = rand()%20;
        }
    }
    printf("Matriz alimentada randomicamente.");
    getch();
}

void imprimir(){
    printf("\n   ");
    for(int i=0; i<l;i++){
        if(i <= 9){
            printf("0%d ", i);
        }else{
            printf("%d ", i);
        }
    }
    printf("\n");
    for(int i=0;i<l;i++){
        if(i <= 9){
            printf("0%d ", i);
        }else{
            printf("%d ", i);
        }
        for(int j=0;j<c;j++){
            if(i==j){
                printf("XX ");
            }
            else if(matriz[i][j] <= 9){
                printf("0%d ", matriz[i][j]);
            }else{
                printf("%d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
    getch();
}

void iniciar_matriz(){
    printf("Digite o número de linhas: ");
    scanf("%d", &l);
    printf("Digite o número de colunas: ");
    scanf("%d", &c);
}

void alimentar_matriz(){
    int linha, coluna, valor;
    printf("Digite a linha: ");
    scanf("%d", &linha);
    printf("Digite a coluna: ");
    scanf("%d", &coluna);
    printf("Digite o valor: ");
    scanf("%d", &valor);

    matriz[linha][coluna] = valor;
}

void matriz_exemplo(){
    l=6;
    c=6;

    matriz[0][1] = 12;
    matriz[0][2] = 4;
    matriz[1][3] = 6;
    matriz[3][2] = 8;
    matriz[2][1] = 10;
    matriz[1][2] = 6; 
    matriz[2][4] = 2; 
    matriz[4][5] = 6; 
    matriz[3][5] = 6; 
    matriz[4][1] = 2; 

}

int cont=0;
int aux=0;
int qtd=0;
int soma=0;

void adicionar_caminho(int caminho[]){
    for(int i=0; i<=10; i++){
        caminho_encontrado[cont][i] = caminho[i];
    }
}

void imprimir_rota(){
    for(int i=0;i< qtd; i++){
        for(int j=0; j<10;j++){
            if(caminho_encontrado[i][j] == noFinal){
                printf("%d: ", caminho_encontrado[i][j]);
                break;
            }
            printf("%d > ", caminho_encontrado[i][j]);
        }
        printf(" Custo: %d", custo[i]);
        printf("\n");
    }
}

int pecorrer(int no, int noFinal){
    if(visitado[no] == 1){
        return 0;
    }
    if(no == noFinal){
        caminho[aux] = no;
        adicionar_caminho(caminho);
        custo[qtd] = soma;
        caminho[aux] = 0;
        cont++;
        qtd++;
        return 0;
    }

    visitado[no] = 1;
    caminho[aux] = no;
    aux++;

    for(int i=0;i<c; i++){
        if(matriz[no][i] != 0 && visitado[i] == 0){
            soma += matriz[no][i];
            pecorrer(i, noFinal);
            soma -= matriz[no][i];
            visitado[no] = 0;
        }
    }
    caminho[aux] = 0;
    aux--;
    
    return 0;
}

int main(){
    noInicial =0;
    noFinal = 3;

    criar_matriz();
    matriz_exemplo();

    pecorrer(noInicial,noFinal);
    imprimir_rota();

    return 0;

}
