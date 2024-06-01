#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <pthread.h>

#define TAM 200

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int matriz[TAM][TAM];
int tamanho = 0;
int src = 0;
int dst = 0;

typedef struct {
    int* v;
    int size;
}Vetor;

typedef struct {
    int src;
    int dst;
    Vetor* caminho;
}Args;

void limpar_matriz(){
    for(int i=0;i<TAM;i++){
        for(int j=0;j<TAM;j++){
            matriz[i][j] = 0;  
        }
    }
}
    
void criar_matriz(){
    printf("\nDigite o tamanho da matriz: ");
    scanf("%d", &tamanho);

    for(int i=0;i<tamanho;i++){
        for(int j=0;j<tamanho;j++){
            matriz[i][j] = 0;  
        }
    }

    printf("matriz %d x %d criada", tamanho ,tamanho);
    getch();
}

void alimentar_automatico(){
    limpar_matriz();
    criar_matriz();

    for(int i=0;i<tamanho;i++){
        for(int j=0;j<tamanho;j++){
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
    for(int i=0; i<tamanho;i++){
        if(i <= 9){
            printf("0%d ", i);
        }else{
            printf("%d ", i);
        }
    }
    printf("\n");
    for(int i=0;i<tamanho;i++){
        if(i <= 9){
            printf("0%d ", i);
        }else{
            printf("%d ", i);
        }
        for(int j=0;j<tamanho;j++){
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

    tamanho = 6;

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
    
    // tamanho = 12;

    // matriz[0][1] = 17;
    // matriz[0][2] = 25;
    // matriz[0][4] = 21;
    // matriz[1][0] = 21;
    // matriz[1][3] = 10;
    // matriz[1][5] = 15;
    // matriz[2][0] = 25;
    // matriz[2][6] = 20;
    // matriz[3][1] = 10;
    // matriz[3][5] = 9;
    // matriz[3][7] = 23;
    // matriz[4][0] = 21;
    // matriz[4][5] = 12;
    // matriz[4][6] = 19;
    // matriz[5][1] = 15;
    // matriz[5][3] = 19;
    // matriz[5][4] = 12;
    // matriz[5][7] = 8;
    // matriz[6][2] = 20;
    // matriz[6][4] = 19;
    // matriz[6][7] = 17;
    // matriz[6][10] = 12;
    // matriz[6][11] = 22;
    // matriz[7][3] = 23;
    // matriz[7][5] = 8;
    // matriz[7][8] = 10;
    // matriz[7][9] = 13;
    // matriz[8][5] = 7;
    // matriz[8][7] = 10;
    // matriz[8][9] = 12;
    // matriz[8][10] = 15;
    // matriz[8][6] = 17;
    // matriz[9][7] = 13;
    // matriz[9][8] = 12;
    // matriz[9][10] = 14;
    // matriz[9][11] = 21;
    // matriz[10][6] = 12;
    // matriz[10][8] = 15;
    // matriz[10][9] = 14;
    // matriz[10][11] = 10;
    // matriz[11][6] = 22;
    // matriz[11][10] = 10;
    // matriz[11][9] = 21;
     

    printf("matriz %d x %d criada e alimentada", tamanho, tamanho);
    getch();

}

void imprimir_rotas(Vetor* vetor){
    for (int i = 0; i < vetor->size; i++){
        printf("%d > ", vetor->v[i]);
    }
    printf("\n");
}

boolean naoEstaNoVetor(Vetor* vetor, int num){
    for (int i = 0; i < vetor->size; i++){
        if(vetor->v[i] == num) return FALSE;
    }
    return TRUE;
}


Vetor* novo_caminho(Vetor* caminho, int src){
    if(caminho == NULL){
        Vetor* vetor = (Vetor*)malloc(sizeof(Vetor));
        vetor->size = 1;
        vetor->v = (int*)malloc(sizeof(int));
        vetor->v[0] = src;
        return vetor;
    }
    Vetor* vetor = (Vetor*)malloc(sizeof(Vetor));
    vetor->size = caminho->size + 1;
    vetor->v = (int*)malloc((vetor->size) * sizeof(int));

    for(int i=0; i< caminho->size;i++){
        vetor->v[i] = caminho->v[i];
    }
    vetor->v[vetor->size - 1] = src;
    return vetor;

}

void* percorrer(void* arg){
    Args* params = (Args*)arg;
    int src = params->src;
    int dst = params->dst;
    Vetor* caminho = params->caminho;

    if(src == dst){
        Vetor* v = novo_caminho(caminho, src);
        imprimir_rotas(v);
        pthread_exit( NULL );
        return NULL;
    }

    Vetor* novoCaminho = novo_caminho(caminho, src);

    pthread_t threads;

    for (int i = 0; i < tamanho; i++){
        if(matriz[src][i] != 0 && naoEstaNoVetor(novoCaminho, i)){
            Args* param = (Args*) malloc(sizeof(Args));
            param->src = i;
            param->dst = dst;
            param->caminho = novoCaminho;
            pthread_create(&threads, NULL, percorrer, param);
            pthread_detach(threads);
        }
    }
    return NULL;
}


void pegar_valor(){
    printf("Digite o vertice inicial: ");
    scanf("%d", &src);
    printf("Digite o vertice final: ");
    scanf("%d", &dst);
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
        printf("[6] Percorrer matriz \n");
        printf("[7] Sair \n");

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
                pegar_valor();
                clock_t inicio = clock();   
                pthread_t thread;
                Args params = {src, dst, NULL};
                pthread_create(&thread, NULL, percorrer, &params);
                pthread_detach(thread);
                clock_t fim = clock();
                double temp = (double)(fim - inicio ) / CLOCKS_PER_SEC;
                printf("\nTempo de execucao: %f ms \n", temp);
                getch();
                break;
            default:
                break;
        }
    } while(op != 7);
}
