#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>
#define SHM_NAME "/pc_shm_12345"
#define BUF_SIZE 5
struct shm_region {
    pthread_mutex_t mutex;
    sem_t empty;
    sem_t full;
    int in;
    int out;
    int buf[BUF_SIZE];
};
static struct shm_region *shm = NULL;
static int shm_fd = -1;
void cleanup_and_exit(int sig) {
    if (shm) {
        munmap(shm, sizeof(struct shm_region));
        shm = NULL;
    }
    if (shm_fd != -1) {
        close(shm_fd);
        shm_fd = -1;
    }
    _exit(0);
}
int main() {
    signal(SIGINT, cleanup_and_exit);
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        fprintf(stderr, "Consumer: shared memory not found. Run producer first.\n");
        return 1;
    }
    shm = mmap(NULL, sizeof(struct shm_region), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED) return 1;
    printf("Consumer started. Press Ctrl+C to exit.\n");
    while (1) {
        sem_wait(&shm->full);
        pthread_mutex_lock(&shm->mutex);
        int item = shm->buf[shm->out];
        shm->out = (shm->out + 1) % BUF_SIZE;
        pthread_mutex_unlock(&shm->mutex);
        sem_post(&shm->empty);
        printf("Consumed: %d\n", item);
        fflush(stdout);
        sleep(1);
    }
    return 0;
}
