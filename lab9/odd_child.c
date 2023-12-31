#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    int i = 1, n;
    void *shmptr;
    int shmid = shmget((key_t)1122, 4096, 0666);
    shmptr = shmat(shmid, NULL, 0666);

    printf("\nChild Printing:\n");
    n = atoi(argv[1]);

    int j = 1;
    for (int i = 1; i <= n; i++)
    {
        sprintf(shmptr, "%d ", j);
        printf("%d ", j);
        shmptr += strlen(shmptr);
        j += 2;
    }

    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
/*
gcc odd_parent.c -o parent
gcc odd_child.c -o odd
./parent 10

Child Printing:
1 3 5 7 9 11 13 15 17 19 
[PARENT] Child completed

Parent printing:
1 3 5 7 9 11 13 15 17 19 
*/
