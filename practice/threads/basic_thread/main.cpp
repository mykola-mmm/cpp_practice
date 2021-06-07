#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHi(void *thread_id) {
    int64_t t_id;
    t_id = (int64_t) thread_id;
    std::cout << "Hi world, thread id - " << t_id << std::endl;
    pthread_exit(NULL);

}


int main(void) {
    pthread_t threads[NUM_THREADS];
    int32_t rc;
    int8_t i;

    for(i = 0; i < NUM_THREADS; ++i) {
        std::cout << "main() : creating thread" << i << std::endl;
        rc = pthread_create(&threads[i], NULL, PrintHi, (void *)i);
        //rc = pthread_create(&threads[i], NULL, PrintHi, NULL);

        //pthread_create returns 0 on success
        if(rc) {
            std::cout << "Error: unable to create thread, " << rc << std::endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
    //pthread_create(thread, attr, start_routine, arg);


    return EXIT_SUCCESS;
}