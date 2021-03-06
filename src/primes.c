#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../inc/primes.h"

sem_t semaphore;
int num_detected_primes = 0;
int candidates[MAX_PRIME] = {0};
int * primes_array = NULL;

int * create_primes_array() {
    int * new_primes_array = (int *) malloc(sizeof(int) * num_detected_primes);
    int j = 0;
    for(int i = 0; i < MAX_PRIME; i++)
        if(candidates[i] == 1) 
            new_primes_array[j++] = i;
    return new_primes_array;
}

void * check_primes(void * args) {
    int  j, k, p;
    int local_primes = 0;
    int i = (int) (long long int) args;
    // printf("%d\n", i);
    while(i < MAX_PRIME) {
        p = 1;
        k = floor(sqrt(i));
        if (i > 1) {
            if (i % 2 != 0) {
                for(int j = 3; j <= k; j += 2) {
                    if (i % j == 0) {
                        p = 0; break;
                    }
                }
            } else if ( i != 2 ) {
                p = 0;
            }
        } else {
            p = 0;
        }
        if (p == 1) {
            candidates[i] = 1;
            local_primes++;
        }
        i+=MAX_THREADS;
    }
    sem_wait(&semaphore);
    num_detected_primes += local_primes;
    sem_post(&semaphore);
    return NULL;
}

void gen_primes() {
    sem_init(&semaphore, 0, 1);
    pthread_t tid[MAX_THREADS] = { 0 };
    for(int i=0; i < MAX_THREADS; i++)
        pthread_create(&tid[i], NULL, check_primes, (void *) i);
    for(int i=0; i < MAX_THREADS; i++)
        pthread_join(tid[i], NULL);
    primes_array = create_primes_array();
    return;
 }
