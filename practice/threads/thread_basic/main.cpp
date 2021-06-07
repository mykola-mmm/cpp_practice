//https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function(void *ptr);


int main(void) {
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


    return EXIT_SUCCESS;
}

void *print_message_function(void *ptr) {
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}