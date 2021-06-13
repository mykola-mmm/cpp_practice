//https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond   = PTHREAD_COND_INITIALIZER;

void *functionCount1(void);
void *functionCount2(void);

#define COUNT_DONE  10
#define COUNT_HALT1 3
#define COUNT_HALT2 6

void *print_message_function(void *ptr);    //(void *ptr) - should always be like this
void *function_C(void *ptr);
void *thread_function(void *ptr);

void ex1(void);
void ex_mutex(void);
void ex_join(void);
void ex_condition(void);



static int32_t counter;

int main(void) {
    //counter = 0;
    //ex1();
    //ex_mutex();
    //ex_join();
    ex_condition();

    return EXIT_SUCCESS;
}


void ex1(void) {
    pthread_t thread1, thread2; 
    char *message1 = "thread 1";
    char *message2 = "thread 2";
    int32_t iret1, iret2;

    iret1 = pthread_create(&thread1, NULL, print_message_function, (void *) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void *) message2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);
}

void ex_condition(void) {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, &functionCount1, NULL);
    pthread_create(&thread2, NULL, &functionCount2, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(0);
}


void ex_join(void) {
    pthread_t thread_id[NUM_THREADS];
    int32_t i, j;
    for(i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&thread_id[i], NULL, thread_function, NULL);
    }
    for(j = 0; j < NUM_THREADS; ++j) {
        pthread_join(thread_id[j], NULL);
    }
    printf("Final counter value - %d\n", counter);
}


void ex_mutex(void) {
    int32_t rc1, rc2;
    pthread_t thread1, thread2;

    if(rc1 = pthread_create(&thread1, NULL, function_C, NULL)) {
        printf("Thread creating failed %d", rc1);
    }

    if(rc2 = pthread_create(&thread2, NULL, function_C, NULL)) {
        printf("Thread creating failed %d", rc2);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(0);
}

void *functionCount1(void) {
    for(;;) {
        pthread_mutex_lock(&condition_mutex);
        while( counter >= COUNT_HALT1 && counter <= COUNT_HALT2) {
                        //printf("inside fC1 while\n");

            pthread_cond_wait(&condition_cond, &condition_mutex);
        }
        pthread_mutex_unlock(&condition_mutex);

        pthread_mutex_lock(&count_mutex);
        counter++;
        printf("COUNTER VALUE functionCount1 %d\n", counter);
        pthread_mutex_unlock(&count_mutex);

        if(counter >= COUNT_DONE) return(NULL);
    }
}

void *functionCount2(void) {
    for(;;) {
        pthread_mutex_lock(&condition_mutex);
        if(counter < COUNT_HALT1 || counter > COUNT_HALT2) {
                            //printf("inside fC2 while\n");

            pthread_cond_signal(&condition_cond);
        }
        pthread_mutex_unlock(&condition_mutex);
        
        pthread_mutex_lock(&count_mutex);
        counter++;
        printf("COUNTER VALUE functionCount2 %d\n", counter);
        pthread_mutex_unlock(&count_mutex);

        if(counter >= COUNT_DONE) return(NULL);
    }
}

void *thread_function(void *ptr) {
    pthread_mutex_lock(&mutex1);
    printf("Thread number %d\n", pthread_self());
    counter++;
    pthread_mutex_unlock(&mutex1);
}

void *function_C(void *ptr) {
    pthread_mutex_lock(&mutex1);
    counter++;
    printf("Counter value: %d\n", counter);
    pthread_mutex_unlock(&mutex1);
}

void *print_message_function(void *ptr) {
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}