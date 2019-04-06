#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>



# define CHAIRS 7
# define DELAY 1000000
# define CUSTOMERS 120

void *customer();
void *stylist ();



sem_t mutex ;
sem_t stylistSem ;
sem_t customerSem ;

int waiting = 0;
int numHaircut = 0;


void main(void){
int i;
int j;
	sem_init(&mutex , 0 , 1);
	sem_init(&stylistSem , 0 , 0);
	sem_init(&customerSem , 0 , 0);


    pthread_t stylistThread;
    pthread_t customerThread[CUSTOMERS];

    //creating a thread 
    pthread_create(&stylistThread,NULL,(void *)stylist,  NULL);

	for( i = 0; i < CUSTOMERS; i++) {
	    pthread_create(&customerThread[i], NULL,(void *)customer, NULL);

	}
    
    //joining the thread

	for( j = 0; j < CUSTOMERS ; j++ ){
		pthread_join(customerThread[j] , NULL);
	}
    pthread_join(stylistThread , NULL);



}


void *stylist (){

	int j;
	while(1){

		sem_wait(&customerSem);
		sem_wait(&mutex);
		waiting = waiting -1 ;
		sem_post(&stylistSem);
		sem_post(&mutex);
		numHaircut = numHaircut +1 ;
       
       printf("No of haircut: %i , No of waiting for haircut: %i\n" , numHaircut , waiting);


		for(j = 0 ; j <DELAY ;j++) {//cut hair
		}

	}
}


void *customer(){
	int j;
	while(1){
		sem_wait(&mutex);
		if(waiting < CHAIRS){
			waiting = waiting + 1;

			sem_post(&customerSem);
			sem_post(&mutex);
			sem_wait(&stylistSem);
			printf("No of haircut: %i , No of waiting for haircut: %i\n" , numHaircut , waiting);
			break;

		}
		else{
			sem_post(&mutex);
			for(j = 0 ; j <DELAY ; j++){
				// go shopping
			} 
		}
	}
}