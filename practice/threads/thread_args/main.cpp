#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

#define NUM_THREADS 5

struct thread_data {
    int32_t thread_id;
    char *message;
};

void *PrintHi(void *thread_arg) {
    struct thread_data *my_data;
    my_data = (struct thread_data *) thread_arg;

    std::cout << "thread id : " << my_data->thread_id;
    std::cout << " // message : " << my_data->message << std::endl;
    pthread_exit(NULL);

}


int main(void) {
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int32_t rc;
    int8_t i;
    std::string _message;

    for(i = 0; i < NUM_THREADS; ++i) {
        std::cout << "main() : creating thread " << std::to_string(i) << std::endl;
        td[i].thread_id = i;
        _message = "Message " + std::to_string(i);
        std::cout << std::to_string(i) << std::endl;    //why all mesasges have the same number???
        td[i].message = _message.c_str();
        rc = pthread_create(&threads[i], NULL, PrintHi, (void *)&td[i]);
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