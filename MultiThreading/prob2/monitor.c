#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CHAIR 7

int stylist = 0;   // it is not available right now

sem_t mutex;

int customer = 0;
int barberSleep = 0;
int count1 = 0;
int numHaircut = 0;




void monitor();
void mon_checkCustomer();
int mon_checkStylist();
void mon_debugPrint ();




typedef struct
{
  int numThreadBlocked;
  sem_t threadBlocked;

}cond;



cond stylistAvailable;
cond customerAvailable;



// inializing the mutex
void monitor(){

    sem_init(&mutex , 0 , 1);
	sem_init(&(stylistAvailable.threadBlocked) , 0 , 0);
	stylistAvailable.numThreadBlocked = 0;



	sem_init(&(customerAvailable.threadBlocked) , 0 , 0);
	customerAvailable.numThreadBlocked = 0;

	
  }

// return no of threads that blocked
int count(cond *cv){
	return cv->numThreadBlocked;
}


// this increase the no of blocked thread  along with suspending the thread
void wait(cond *cv){


    cv->numThreadBlocked = cv->numThreadBlocked +1 ;
    sem_post(&mutex);
	sem_wait(&(cv->threadBlocked));
	

}


//it resumes the thread that was blocked 
void signal(cond *cv){
 //doesn't suspend the thread 

	if(count(cv) == 0){
    
	}

else{
	
	cv->numThreadBlocked = cv->numThreadBlocked -1 ;
	sem_post(&(cv->threadBlocked));
	sem_wait(&mutex);
}
}

void mon_checkCustomer(){ 

    sem_wait(&mutex);
    if(numHaircut >=120){
        sem_post(&mutex);
        pthread_exit(NULL);
    }
   
	stylist = stylist + 1;

// check of stylist avvailable 
	signal(&stylistAvailable);

	// this means if there is no custmoer just wait for another customer
	if(customer == 0){
		printf("There is no customer right now");
		wait(&customerAvailable);
	}
	
	customer  = customer -1;
	numHaircut = numHaircut + 1;  // hair cut increment 
    sem_post(&mutex);
}

int mon_checkStylist(){ // producer

	sem_wait(&mutex);
    if(numHaircut >=120){
        sem_post(&mutex);
        pthread_exit(NULL);
    }
	int status = 0;
	 // looops only if customer no is less than chair otherwiseunlock the lock so that other can use
	if(customer <CHAIR){
		customer = customer +1;
		signal(&customerAvailable);
		if(stylist ==0){
			wait(&stylistAvailable);
		}
		stylist = stylist -1 ;
		status = 1;
	}
sem_post(&mutex);
return status;

}


// just print statement to see the haircut 

void mon_debugPrint (){ // print how many customers are waiting 





switch(customer){

	case 0:
       barberSleep = barberSleep +1;
       break;

	case 1 : 
	   printf("position of chair with customer: %d | %d | %d| %d | %d| %d | %d , and customer: %i\n" , 1 , 0,0,0,0,0,0 , customer);
	   break;

	case 2 : 
	   printf("position of chair with customer: %d | %d | %d| %d | %d| %d | %d  , and customer: %i\n" , 1 , 1,0,0,0,0,0 , customer);
	   break;

	case 3 : 
	   printf("position of chair with customer: %d | %d | %d| %d | %d| %d | %d  , and customer: %i\n" , 1 , 1,1,0,0,0,0 , customer);
	   break;

	case 4 : 
	   printf("position of chair with customer: %d | %d | %d| %d | %d| %d | %d  , and customer: %i\n" , 1 , 1,1,1,0,0,0 , customer);
	   break;

	case 5 : 
	   printf("position of chair with customer: %d | %d | %d| %d | %d| %d | %d  , and customer: %i\n" , 1 , 1,1,1,1,0,0 , customer);
	   break;

	case 6 : 
	   printf("position of chair with customer: %d | %d | %d| %d | %d| %d | %d  , and customer: %i\n" , 1 , 1,1,1,1,1,0 , customer);
	   break;

	case 7 : 
	   count1 = count1 +1;
	   printf("position of chair with customer: %d | %d | %d| %d | %d| %d | %d  , and customer: %i\n" , 1 , 1,1,1,1,1,1 , customer);
	   break;



}


printf(" No of haircut: %d \n"  ,numHaircut);
printf(" No of time saloon was full: %d \n"  ,count1);
printf(" No of time stylis  was on sleep: %d \n"  ,barberSleep);

printf("--------------------------------------------------------\n");





}









