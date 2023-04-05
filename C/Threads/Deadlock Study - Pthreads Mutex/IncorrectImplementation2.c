#include <stdio.h>
#include <pthread.h>

pthread_mutex_t m_1, m_2;
int num_transacoes = 7;
int transacoes1[] = {5, 10, 15, 5, 20, 5, 5};
int transacoes2[] = {10, 10, 10, 10, 10, 10, 10};

void ler_saldo(int option, int* saldo_origem, int* saldo_destino){
  FILE *origem, *destino;
  if (option == 1){
    pthread_mutex_lock(&m_1);
    origem = fopen("saldoA.txt", "r");
    pthread_mutex_lock(&m_2);
    destino = fopen("saldoB.txt", "r");
  } else {
    pthread_mutex_lock(&m_2);
    origem = fopen("saldoB.txt", "r");
    pthread_mutex_lock(&m_1);
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

  pthread_mutex_unlock(&m_1);
  pthread_mutex_unlock(&m_1);
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

  pthread_mutex_init(&m_1, NULL);
  pthread_mutex_init(&m_2, NULL);

  pthread_create(&key_t1, NULL, thread_conta1, NULL);
  pthread_create(&key_t2, NULL, thread_conta2, NULL);
  pthread_join(key_t1, NULL);
  pthread_join(key_t2, NULL);

  return 0;
}
