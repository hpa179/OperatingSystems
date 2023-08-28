#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> /* for exit */
#include <sys/wait.h>

/*
 * shm-server - not sure of the origin of code segment.
 * Old source, not sure of the origin
 *  possibly: David Marshalls course : http://www.cs.cf.ac.uk/Dave/C/CE.html
 * or Steve Holmes : http://www2.its.strath.ac.uk/courses/c/
 */


#define _B_SOURCE
#define SHMSZ     40


int main()
{
    char c;
    int shmid_int, shmid_str;
    key_t key_int, key_str;
    char *shm, *s;
    int *shm1, shmc;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key_int = 5345;
    key_str = 53456;
    /*
     * Create the segment.
     */
    if( (shmid_int = shmget(key_int, sizeof(int), IPC_CREAT | 0600)) < 0 )
    {
        perror("shmget");
        exit(1);
    }
 if( (shmid_str = shmget(key_str, SHMSZ, IPC_CREAT | 0600)) < 0 )
    {
        perror("shmget");
        exit(1);
    }


    /*
     * Now we attach the segment to our data space.
     */
    if( (shm1 = shmat(shmid_int, NULL, 0)) == (int *) -1)
    {
        perror("shmat");
        exit(1);
    }
    if( (shm = shmat(shmid_str, NULL, 0)) == (char *) -1 )
    {
        perror("shmat");
        exit(1);
    }

    *shm1 = 10;
    sprintf(shm, "I am Process A");
    printf("%s\n", shm);

    /*
     * Now fork a child process for Process B
     */
    pid_t pidB = fork();
    if(pidB == 0){
        *shm1 =20;
        sprintf(shm, "I am Process B");
        printf("%s\n", shm);
        /*
         * Now fork a child process for Process C
         */
        pid_t pidC = fork();
        if(pidC == 0){
            *shm1 = 30;
            sprintf(shm, "I am Process C");
            printf("%s\n", shm);
            shmdt(shm1);
            shmdt(shm);
            exit(0);
        }
        else if (pidC < 0){
            perror("fork");
            exit(1);
        }
        wait(NULL);
        shmdt(shm1);
        shmdt(shm);
        exit(0);
    }
    else if (pidB < 0){
        perror("fork");
        exit(1);
    }

    /*
     * Wait for child process B to complete and exit.
     */
    wait(NULL);

    shmdt(shm1);
    shmdt(shm);
    shmctl(shmid_int, IPC_RMID, NULL);
    shmctl(shmid_str, IPC_RMID, NULL);

    printf("Goodbye!\n");
    return 0;
}
