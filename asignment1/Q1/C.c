
/*
 * shm-client - client program to demonstrate shared memory.
 * shm-client - not sure of the origin of these code segments.
 * possibly: David Marshalls course : http://www.cs.cf.ac.uk/Dave/C/CE.html
 * or Steve Holmes : http://www2.its.strath.ac.uk/courses/c/
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define _BSD_SOURCE
#define SHMSZ     40

int main()
{
    int shmid_int, shmid_str, *shm1;
    key_t key_int, key_str;
    char *shm, *s;


    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key_int = 5345;
key_str = 53456;
    /*
     * Locate the segment.
     */
if( (shmid_str = shmget(key_str, SHMSZ, 0600)) < 0 )
    {
        perror("shmget");
        exit(1);
    }
if( (shm = shmat(shmid_str, NULL, 0)) == (char *) -1 )
    {
        perror("shmat");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
if( (shmid_int = shmget(key_int, sizeof(int), 0600)) < 0 )
    {
        perror("shmget");
        exit(1);
    }
   if( (shm1 = shmat(shmid_int, NULL, 0)) == (int *) -1 )
    {
        perror("shmat");
        exit(1);
    }

    
    // * Now read what the server put in the memory.
     
    /*for( s = shm; *s != (char*) NULL; s++ )
        putchar(*s);
    putchar('\n');*/

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
while (*shm1 != 20){
	usleep(100);
}
s= shm;
sprintf(s, "I am Process C");
    *shm1 = 30;

    return 0;
}
