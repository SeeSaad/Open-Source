#include <stdio.h>

int num_transacoes = 7;
int transacoes1[] = {5, 10, 15, 5, 20, 5, 5};
int transacoes2[] = {10, 10, 10, 10, 10, 10, 10};

void ler_saldo(int option, int* saldo_origem, int* saldo_destino){
  FILE *origem, *destino;
  if (option == 1){
    origem = fopen("saldoA.txt", "r"); 
    destino = fopen("saldoB.txt", "r");
  } else {
    origem = fopen("saldoB.txt", "r");
    destino = fopen("saldoA.txt", "r");
  }
  fscanf(origem, "%d", saldo_origem);
  fscanf(destino, "%d", saldo_destino);
  fclose(origem);
  fclose(destino);
}

void computar_transacao(int option, int saldo_origem, int saldo_destino){
  FILE *origem, *destino;
  if (option == 1){
    origem = fopen("saldoA.txt", "w"); 
    destino = fopen("saldoB.txt", "w");
  } else {
    origem = fopen("saldoB.txt", "w");
    destino = fopen("saldoA.txt", "w");
  }
  fprintf(origem, "%d", saldo_origem);
  fprintf(destino, "%d", saldo_destino);
  fclose(origem);
  fclose(destino);
}

void* thread_conta1(void* arg){
  int saldo_origem;
  int saldo_destino;
  
  for (int i = 0; i < num_transacoes; i++){
    ler_saldo(1, &saldo_origem, &saldo_destino);
    if (saldo_origem >= transacoes1[i]){
      computar_transacao(1, saldo_origem - transacoes1[i], saldo_destino + transacoes1[i]);
    } else {
      printf("transação de conta A para B de R$:%d não foi possivel\n", transacoes1[i]);
    }
  }
  return NULL;
}

void* thread_conta2(){
  int saldo_origem;
  int saldo_destino;
  
  for (int i = 0; i < num_transacoes; i++){
    ler_saldo(2, &saldo_origem, &saldo_destino);
    if (saldo_origem >= transacoes2[i]){
      computar_transacao(2, saldo_origem - transacoes2[i], saldo_destino + transacoes2[i]);
    } else {
      printf("transação de conta B para A de R$:%d não foi possivel\n", transacoes2[i]);
    }
  }
  return NULL;
}


int main(void) {
  pthread_t key_t1, key_t2;

  pthread_create(&key_t1, NULL, thread_conta1, NULL);
  pthread_create(&key_t2, NULL, thread_conta2, NULL);
  pthread_join(key_t1, NULL);
  pthread_join(key_t2, NULL);

  return 0;
}
