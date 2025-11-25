#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
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
        pthread_mutex_destroy(&shm->mutex);
        sem_destroy(&shm->empty);
        sem_destroy(&shm->full);
        munmap(shm, sizeof(struct shm_region));
        shm = NULL;
    }
    if (shm_fd != -1) {
        close(shm_fd);
        shm_unlink(SHM_NAME);
        shm_fd = -1;
    }
    _exit(0);
}
int main() {
    signal(SIGINT, cleanup_and_exit);
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
    int created = 1;
    if (shm_fd == -1) {
        shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
        created = 0;
        if (shm_fd == -1) return 1;
    }
    if (created) {
        ftruncate(shm_fd, sizeof(struct shm_region));
    }
    shm = mmap(NULL, sizeof(struct shm_region), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED) return 1;
    if (created) {
        shm->in = 0;
        shm->out = 0;
        pthread_mutexattr_t ma;
        pthread_mutexattr_init(&ma);
        pthread_mutexattr_setpshared(&ma, PTHREAD_PROCESS_SHARED);
        pthread_mutex_init(&shm->mutex, &ma);
        pthread_mutexattr_destroy(&ma);
        sem_init(&shm->empty, 1, BUF_SIZE);
        sem_init(&shm->full, 1, 0);
        for (int i = 0; i < BUF_SIZE; i++) shm->buf[i] = 0;
    }
    printf("Producer started. Enter integers to produce. Ctrl+C to exit.\n");
    while (1) {
        int item;
        printf("Produce: ");
        fflush(stdout);
        if (scanf("%d", &item) != 1) {
            int c;
            while ((c = getchar()) != EOF && c != '\n');
            continue;
        }
        sem_wait(&shm->empty);
        pthread_mutex_lock(&shm->mutex);
        shm->buf[shm->in] = item;
        shm->in = (shm->in + 1) % BUF_SIZE;
        pthread_mutex_unlock(&shm->mutex);
        sem_post(&shm->full);
    }
    return 0;
}
