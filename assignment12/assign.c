#include <stdio.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#define SEM_KEY 0x4324
union semun
{
    int val;              
    struct semid_ds *buf;  
    unsigned short *array; 
    struct seminfo *__buf; 
};
int main()
{
    int pid, s, i, semid, ret;
    union semun su;
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
    su.val = 0;
    ret = semctl(semid, 0, SETVAL, su);

    pid = fork();
    if (pid == 0)
    {
        char *str = "Infotech\n";
        struct sembuf ops[1];
        ops[0].sem_num = 0;
        ops[0].sem_op = -1;
        ops[0].sem_flg = 0;
        ret = semop(semid, ops, 1);
        for (i = 0; str[i] != '\0'; i++)
        {
            putchar(str[i]);
            fflush(stdout);
            sleep(1);
        }
    }
    else 
    {
        char *str = "Sunbeam\n";
        for (i = 0; str[i] != '\0'; i++)
        {
            putchar(str[i]);
            fflush(stdout);
            sleep(1);
        }
        struct sembuf ops[1];
        ops[0].sem_num = 0;
        ops[0].sem_op = +1;
        ops[0].sem_flg = 0;
        ret = semop(semid, ops, 1);

        wait(&s);
        semctl(semid, 0, IPC_RMID);
    }
    return 0;
}
