#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "monitor.h"




# define CHAIRS 7
# define DELAY 1000000
# define CUSTOMERS 120



void *cust();
void *barber ();





void main (void){
int i ;
int j;

   monitor();

   // creating stylist thread 
  pthread_t stylistThread;

  //creating customer thread
    pthread_t customerThread[CUSTOMERS];
     
    pthread_create(&stylistThread,NULL,(void*) barber,  NULL);

  for( i = 0; i < CUSTOMERS; i++) {
      pthread_create(&customerThread[i], NULL,(void *)cust, NULL);

  }
    
    //joining the thread

  for(j = 0; j < CUSTOMERS ; j++ ){
    pthread_join(customerThread[j] , NULL);
  }
    pthread_join(stylistThread , NULL);

}





void *barber (){

int j;
while(1){

  
  mon_debugPrint();
  
  mon_checkCustomer();


  for(j = 0 ; j < DELAY ; j++){

  } // cut hair

}


}


void *cust(){
  
  int j;
  while(1){

    mon_debugPrint();
    if(mon_checkStylist())
        break;


    for(j = 0 ; j <DELAY ; j++){

    }
  }


}

