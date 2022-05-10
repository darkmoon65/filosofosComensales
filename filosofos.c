#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void *filosofo (void *arg);

int cantidadFilosofos;
int variableComida = 5000;
int vecesRestaurarComida = 2;
pthread_mutex_t tenedores[];


int main(void){ 
	printf("Ingrese la cantidad de filosofos: ");
	scanf("%d", &cantidadFilosofos);
	pthread_t filosofos[cantidadFilosofos];
	int ids[5];
	int i;

	for(i = 0; i < cantidadFilosofos; i++){
		pthread_mutex_init(&tenedores[i], NULL);
	}
	for(i = 0; i < cantidadFilosofos; i++){
		ids[i] = i+1;
		pthread_create(&filosofos[i],NULL, &filosofo, &ids[i]);
	}
	for(i = 0; i < cantidadFilosofos; i++){
		pthread_join(filosofos[i],NULL);
	}

	return 0;
}

void agarrarTenedor(int f, int p){
	pthread_mutex_lock(&tenedores[p]);
	printf("Filosofo %d agarro tenedor %d \n", f,p);
}

void dejarTenedores(int p1,int p2){
	pthread_mutex_unlock(&tenedores[p1]);
	pthread_mutex_unlock(&tenedores[p2]);
}


void comer(int arg){
	int tenedor1 = arg-2;   
	int tenedor2 = arg-1;	
	
	if(tenedor1 == -1){
		tenedor1 = 4;
	}
	agarrarTenedor(arg, tenedor1);
	agarrarTenedor(arg, tenedor2);

	printf("Filosofo %d esta comiendo \n",arg);

	if(variableComida == 0 && vecesRestaurarComida > 0){
		variableComida = 5000;
		printf("-----------------Se restauro la comida --------------\n");
	}
	printf("Comida restante: %d\n",variableComida);
	dejarTenedores(tenedor1, tenedor2);
	
}

//metodo para cada filosofo
void *filosofo (void *arg){
	int arg2 = *((int *)arg);
	for ( int i = 0; i < 5 ; i++){ 
		comer(arg2);
	}
	return NULL;
}
