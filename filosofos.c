#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void *filosofo (void *arg);

int cantidadFilosofos;
int variableComida = 5000;
int vecesRestaurarComida = 2;
pthread_mutex_t tenedores[];
int estomagos[];
int derrocheEnergia = 0;
int comido = 0;

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

void pensar(int num){
	printf("Filosofo %d esta pensando \n", num );
	estomagos[num] -= 10;
	comido -= 10;
	derrocheEnergia += 10;
	int random = rand() % 10;  // generamos un numero random para dormir al thread
	sleep(random);
}

void comer(int arg){
	int tenedor1 = arg-2;   
	int tenedor2 = arg-1;	
	
	//evitamos el deadlock accediendo en orden a los tenedores, inclusive el ultimo termino
	if(tenedor1 == -1){
		tenedor1 = tenedor2;
		tenedor2 = cantidadFilosofos-1;
	}
	agarrarTenedor(arg, tenedor1);
	agarrarTenedor(arg, tenedor2);

	printf("Filosofo %d esta comiendo \n",arg);
	variableComida = variableComida-100;
	estomagos[arg] += 100;
	comido += 100;

	if(variableComida == 0 && vecesRestaurarComida > 0){
		printf("-----Total comida en estomagos %d -------- \n", comido);
		printf("------Total energia gastada %d ------- \n", derrocheEnergia);
		printf("------Total que se comio %d ------- \n", comido + derrocheEnergia);
		variableComida = 5000;
		printf("-----------------Se restauro la comida --------------\n");
	}

	printf("Estomago de filosofo %d  esta con %d \n",arg, estomagos[arg]);
	printf("Comida restante: %d\n",variableComida);
	dejarTenedores(tenedor1, tenedor2);
	
}

//metodo para cada filosofo
void *filosofo (void *arg){
	int arg2 = *((int *)arg);
	while ( variableComida > 0){ //mientras haya comida se ejecutara el programa
		pensar(arg2);
		comer(arg2);
	}
	return NULL;
}
