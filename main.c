#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>


union senum {
    int val;
    struct semid_ds *buff;
    unsigned short *array;
};

//offset of semaphores
const int OFFSET_FS = 0; //semaphore1
const int OFFSET_CS = 1; //semaphore2 etc
const int OFFSET_CTR = 2;
const int OFFSET_TS = 3;

int N, M;
int shmid;
int semid;

int * first;    //points to int to shared memory
struct timeval * second;  //points to timeval of shared memory

void check(int returnvalue) {   //checking values
    if (returnvalue <= 0) {
        perror("call error: ");
        printf("Return value: %d \n", returnvalue);
        exit(0);
    }
}

void p(int s) {
    struct sembuf semopr = {s, -1, 0};
    check(semop(semid, &semopr, 1) == 0);
}

void v(int s) {
    struct sembuf semopr = {s, 1, 0};
    check(semop(semid, &semopr, 1) == 0);
}

void pn(int s) {
    struct sembuf semopr = {s, -N, 0};
    check(semop(semid, &semopr, 1) == 0);
}

void vn(int s) {
    struct sembuf semopr = {s, N, 0};
    check(semop(semid, &semopr, 1) == 0);
}

int main(int argc, char** argv) {
    int TIME_SIZE = sizeof (struct timeval);    //for shared memory
    int INT_SIZE = sizeof (int);                //for shared memory
    int i;

    if (argc == 3) {
        N = atoi(argv[1]);
        M = atoi(argv[2]);

        char *pmem;

        pid_t feeder_pid = fork();

        if (feeder_pid == 0) {
            // feeder
            int * numbers = malloc(INT_SIZE * M);      //array of numbers of feeder

            check(shmid = shmget(IPC_PRIVATE, TIME_SIZE + INT_SIZE, 0666 | IPC_CREAT));
            check(semid = semget(IPC_PRIVATE, 4, 0666 | IPC_CREAT));        //four semaphores as you see above
            check((first = (int*) (pmem = shmat(shmid, 0, 0))) != NULL);   //for shared memory and first(points there) and check it
            second = (struct timeval *) (pmem + INT_SIZE);                  //for timeval of shared memory

               //arxikopoiisi semaphore
            union senum args[4];
            args[OFFSET_FS].val = N;
            args[OFFSET_CS].val = 0;
            args[OFFSET_CTR].val = 0;
            args[OFFSET_TS].val = 0;

            for (i = 0; i < 4; i++) {
                check(semctl(semid, i, SETVAL, args[i]) == 0);
            }

            // ---------------------------------------------------- CHILD FORK
            for (i = 0; i < N; i++) {
                pid_t reader_pid = fork();

                if (reader_pid == 0) {
                    // -------------------------------------------- CHILD MAIN
                    struct timeval timecheck;           //second timeval to sub with the first
                    long sum = 0;
                    int file_id = i;                    //for number of file to put the data
                    FILE * fp;

                    char buffer[100];
                    sprintf(buffer, "file%d", file_id);


                    check((fp = fopen(buffer, "w+")) != NULL);

                    for (i = 0; i < M; i++) {
                        numbers[i] = 0;
                    }

                    for (i = 0; i < M; i++) {
                        p(OFFSET_CS);   //down for consumer(one by one)

                        numbers[i] = *first;
                        long start = (long) second->tv_sec * 1000 + (long) second->tv_usec / 1000;   //counting first time
                        gettimeofday(&timecheck, NULL);
                        long end = (long) timecheck.tv_sec * 1000 + (long) timecheck.tv_usec / 1000; //counting last time
                        long diff = (end - start);  //regular time
                        sum = sum + diff;   //summary

                        v(OFFSET_CTR); //counter for counting all, one by one


                        p(OFFSET_TS); //keep one

                        v(OFFSET_FS);  //up feeder(basically with the last consumer)
                    }


                    printf("I am %ld and my running average is: %f \n", (long int) getpid(), sum / (float) M);  //print average

                    fprintf(fp, "I am %ld and my running average is: %f \n", (long int) getpid(), sum / (float) M); //print it to file

                    for (i = 0; i < M; i++) {
                        fprintf(fp, "%d - %d \n", i, numbers[i]);
                    }

                    fclose(fp);

                    free(numbers);

                    return 0;
                }
            }

            // ---------------------------------------------------- FEEDER MAIN
            srand(time(0));

            for (i = 0; i < M; i++) {
                numbers[i] = rand();
            }

            // feeder LOOP
            for (i = 0; i < M; i++) {
                pn(OFFSET_FS); // wait for last consumer(2nd) and then feeder
                *first = numbers[i];
                gettimeofday(second, NULL);
                vn(OFFSET_CS); // signal consumers/readers to read

                pn(OFFSET_CTR); // wait all readers to read

                vn(OFFSET_TS); // signal for all readers(2nd) to keep them
            }


            for (i = 0; i < N; i++) {
                wait(NULL);        //we don't want zombies
            }

            free(numbers);

            check(shmdt(pmem) == 0);         //delete the 3 of them, true returns 0 here
            check(shmctl(shmid, 0, IPC_RMID) == 0);
            check(semctl(semid, 0, IPC_RMID, 0) == 0);

            return 0;
        } else {
            wait(NULL);   //same
        }

        return 0;
    } else {
        printf("Wrong number of inputs\n" );
        return -1;
    }

}
