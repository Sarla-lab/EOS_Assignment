#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pipe1[2]; // child → parent
    int pipe2[2]; // parent → child
    pid_t pid;

    // Create two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
        // ---------- CHILD PROCESS ----------
        close(pipe1[0]); // close read end of pipe1
        close(pipe2[1]); // close write end of pipe2

        int num1 = 10, num2 = 20, sum;

        printf("Child: sending numbers %d and %d to parent...\n", num1, num2);

        // Send numbers to parent
        write(pipe1[1], &num1, sizeof(num1));
        write(pipe1[1], &num2, sizeof(num2));

        // Wait for sum from parent
        read(pipe2[0], &sum, sizeof(sum));

        printf("Child: received sum = %d\n", sum);

        // Close pipes
        close(pipe1[1]);
        close(pipe2[0]);

        exit(0);
    }
    else {
        // ---------- PARENT PROCESS ----------
        close(pipe1[1]); // close write end of pipe1
        close(pipe2[0]); // close read end of pipe2

        int a, b, sum;

        // Read numbers from child
        read(pipe1[0], &a, sizeof(a));
        read(pipe1[0], &b, sizeof(b));

        printf("Parent: received numbers %d and %d\n", a, b);

        // Calculate sum
        sum = a + b;

        // Send result back to child
        write(pipe2[1], &sum, sizeof(sum));

        // Close pipes
        close(pipe1[0]);
        close(pipe2[1]);

        // Wait for child completion
        wait(NULL);

        printf("Parent: child completed. Exiting.\n");
    }

    return 0;
}

