#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int matriz[100][100];
int l=0, c=0;
int visitado[100];
int caminho[100];
int caminho_encontrado[100][100];
int custo[100];
int noInicial=0, noFinal=0;

int cont=0;
int aux=0;
int qtd=0;
int soma=0;

int vert_inicial = 0;
int vert_final = 0;

int fatorial(int pos, int vert_disp){
    int fatorial = 1;
     
    for(int i=1; i <= pos; i++){
        fatorial *= vert_disp;
        vert_disp--;
    }
    return fatorial;
}

void calcular_rotas(){
    int vert_disp = l - 2;
    long long int somatorio = 0;

    for (int i = vert_disp; i >=1; i--){
        somatorio += fatorial(i, vert_disp);
    }
    somatorio++;
    printf("\nNumero maximo de rotas %lld ", somatorio);
    getch();
    
}

void limpar_matriz(){
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            matriz[i][j] = 0;  
        }
    }
}
    
void criar_matriz(){
    printf("Digite o numero de linhas: ");
    scanf("%d", &l);
    printf("Digite o numero de colunas: ");
    scanf("%d", &c);

    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            matriz[i][j] = 0;  
        }
    }

    printf("matriz %d x %d criada", l ,c);
    getch();
}

void alimentar_automatico(){
    limpar_matriz();
    criar_matriz();

    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            if(i==j){
                matriz[i][j] = 0;
            }else{
                matriz[i][j] = rand()%10;
            }
        }
    }
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

void alimentar_matriz(){
    int linha, coluna, valor;
    printf("Digite a linha: ");
    scanf("%d", &linha);
    printf("Digite a coluna: ");
    scanf("%d", &coluna);
    printf("Digite o valor: ");
    scanf("%d", &valor);

    matriz[linha][coluna] = valor;

    printf("valor %d inserido na linha: %d, coluna: %d",valor, linha, coluna);
    getch();
}

void matriz_exemplo(){
    limpar_matriz();
    
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

    printf("matriz %d x %d criada e alimentada", l, c);
    getch();

}

void adicionar_caminho(int caminho[]){
    for(int i=0; i<=100; i++){
        caminho_encontrado[cont][i] = caminho[i];
    }
}

void imprimir_rotas(){
    printf("\nNumero de rotas: %d\n", qtd);
    for(int i=0;i < qtd; i++){
        for(int j=0; j < 100;j++){
            if(caminho_encontrado[i][j] == vert_final){
                printf("%d: ", caminho_encontrado[i][j]);
                break;
            }else{
                printf("%d > ", caminho_encontrado[i][j]);
            }
        }
        printf(" Custo: %d", custo[i]);
        printf("\n");
    }
    getch();
}

int pecorrer(int no, int noFinal){
    if(no == noFinal){
        caminho[aux] = no;
        adicionar_caminho(caminho);
        caminho[aux] = 0;
        custo[qtd] = soma;
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
        }
        if(i==c-1){
            visitado[no] = 0;
            aux--;
            caminho[aux] = 0;
        }
    }
    return 0;
}

void pegar_valor(){
    printf("Digite o vertice inicial: \n");
    scanf("%d", &vert_inicial);
    printf("Digite o vertice final: ");
    scanf("%d", &vert_final);
}

void limpar_dados(){
    for(int i=0;i < qtd; i++){
        for(int j=0; j < 100;j++){
            caminho_encontrado[i][j] = 0;
        }
    }
    for(int i=0;i<100;i++){
        caminho[i] = 0;
        visitado[i] = 0;
        custo[i] = 0;
    }
    qtd = 0;
    cont = 0;
    aux = 0;
    soma = 0;

}

int main(){

    int op=0;
    do  
    {
        system("cls");
        printf("[1] Criar matriz \n");
        printf("[2] Gerar matriz teste \n");
        printf("[3] Gerar matriz aleatoria \n");
        printf("[4] Imprimir matriz \n");
        printf("[5] Alimentar matriz \n");
        printf("[6] Número maximo de rotas \n");
        printf("[7] Percorrer matriz \n");
        printf("[8] Sair \n");

        scanf("%d", &op);

        switch (op){
            case 1:
                criar_matriz();
                break;
            case 2:
                matriz_exemplo();
                break;
            case 3:
                alimentar_automatico();
                break;
            case 4:
                imprimir();
                break;
            case 5:
                alimentar_matriz();
                break;
            case 6:
                calcular_rotas();
                break;
            case 7:
                pegar_valor();
                pecorrer(vert_inicial, vert_final);
                imprimir_rotas();
                limpar_dados();
                break;
            case 8:
                break;
            default:
                break;
        }
    } while(op != 8);
    alimentar_automatico();
}
