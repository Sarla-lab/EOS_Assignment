#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t sem1, sem2;
void* print_sunbeam(void* arg) {
    while (1) {
        sem_wait(&sem1);
        printf("SUNBEAM\n");
        fflush(stdout);
        sleep(1);
        sem_post(&sem2);
    }
    return NULL;
}
void* print_infotech(void* arg) {
    while (1) {
        sem_wait(&sem2);
        printf("INFOTECH\n");
        fflush(stdout);
        sleep(1);
        sem_post(&sem1);
    }
    return NULL;
}
int main() {
    pthread_t t1, t2;
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);
    pthread_create(&t1, NULL, print_sunbeam, NULL);
    pthread_create(&t2, NULL, print_infotech, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    return 0;
}
