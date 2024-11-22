#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        printf("Executing child process (PID : %d)..\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Parent process (PID: %d) waiting for child process to finish..\n", getpid());
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        else
            printf("Child did not exit successfully\n");
    }
    return 0;
}