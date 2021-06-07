#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <unistd.h>


#define NUM_THREADS 5



void *wait(void *t) {
    int32_t i;
    int64_t t_id;

    t_id = (int64_t) t;

    sleep(1);
    std::cout << "Sleeping in thread " << std::endl;
    std::cout << "Thread with id : " << t_id << "\t ... exiting ..." << std::endl;
    pthread_exit(NULL);
}



int main(void) {
    int32_t rc, i;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    void *status;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(i = 0; i < NUM_THREADS; ++i) {
        std::cout << "main() : crating thread, " << i << std::endl;
        rc = pthread_create(&threads[i], &attr, wait, (void *)i);
        if(rc) {
            std::cout << "Error: unable to create thread, " << rc << std::endl;
            exit(-1);
        }
        
    }

    pthread_attr_destroy(&attr);
    for(i = 0; i < NUM_THREADS; ++i) {
        rc = pthread_join(threads[i], &status);
        if(rc) {
            std::cout << "Error unable to join, " << rc << std::endl;
            exit(-1);
        }
        std::cout << "Main completed thread id : " << i;
        std::cout << " exiting with status :" << status << std::endl; 
    }

    std::cout << "Main: program exiting." << std::endl;
    pthread_exit(NULL);

    return EXIT_SUCCESS;
}

