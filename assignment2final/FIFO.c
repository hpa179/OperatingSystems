#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>      // for O_CREAT and O_EXCL
#include <sys/mman.h>   // for shared memory and semaphore functions
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#define SIZE 20
#define NUMB_THREADS 6
#define PRODUCER_LOOPS 2
#define CLOCK_REALTIME 0
struct print_job{
    int user_id;
    int job_size;
   // clock_t begin;
  //  clock_t end;
    //double time;
    double *value;
};
double *total_jobs;

typedef struct print_job buffer_t;
buffer_t *buffer;
//int *buffer_index;
sem_t *buffer_mutex;
sem_t *full_sem; /* when 0, buffer is full */
sem_t *empty_sem; /* when 0, buffer is empty. Kind of
             like an index for the buffer */
//sem_t *read_sem;
//sem_t *write_sem;
sem_t *count_producer;
int *shmid_mutex;
int *shmid_buffer;
int *producer1;
int *shmid_index;
int *in, *out;
double *shmid_value;
int consumer_consumed;
int *producer_produced;

pthread_t *thread;
int *term;
int num_producers = 0;
int num_consumers = 0;
pid_t *pid;
int i;
struct timespec start, end;


void sigint_handler(int){
    for(i=0;i < num_producers;i++){    
    kill(pid[i], SIGKILL);
    }
    exit(0);
}
void sigkill_handler(int){
    shmdt(full_sem);
    shmdt(empty_sem);
     shmdt(in);
     shmdt(out);
    shmdt(buffer_mutex);
    shmdt(producer_produced);
    shmdt(buffer);
   // shmdt(buffer_index);
    shmdt(shmid_value);
    shmdt(total_jobs);
    exit(0);
}

/*void insertbuffer(buffer_t *job_size) {
    if (*in < SIZE) {
        buffer[(*in)++] = *job_size;
    } else {
        printf("Buffer overflow\n");
    }
}*/
void insertbuffer( buffer_t *job_size) {
    while (((*in + 1 ) % SIZE) == *out ) {
        sleep(1);
    }
        buffer[*in] = *job_size;
      (*in) = ((*in) + 1) % 20;
}
/*buffer_t dequeuebuffer() {
    if (*out > 0) {
        return buffer[--(*out)]; // buffer_index-- would be error!
    } else {
        printf("Buffer underflow\n");
    }
    buffer_t job_size = {0};
    return job_size;
}*/
buffer_t dequeuebuffer() {
    buffer_t job_size = {0};
   while (*out == *in) {
    sleep(1);
    }
    job_size = buffer[*out];
     (*out) = ((*out) + 1) % 20;
    return job_size;
}
void *producer(int user_id) {
    //int thread_numb = thread_n;
typedef struct print_job buffer_t;
    buffer_t value;
    int i=0;
    int jobs = rand() % 20 + 1;
     //  float total_sleep_time = 0;
    while (i++ < jobs) {
     /* float random_sleep = (float)rand() / RAND_MAX * (1.0 - 0.1) + 0.1;
        total_sleep_time += random_sleep;
        struct timespec req;
    struct timespec rem;
    req.tv_sec = (time_t)total_sleep_time;
    req.tv_nsec = (total_sleep_time - req.tv_sec) * 1e9;
    if (nanosleep(&req, &rem) == -1) {
        perror("nanosleep");
        return 1;
    }*/
        srand(getpid());
        sleep(rand() % 10);
        value.job_size = rand() % 100;
	clock_gettime(CLOCK_REALTIME, &start);	/* mark start time */
    sleep(10);
       value.user_id = getpid();
        sem_wait(full_sem); // sem=0: wait. sem>0: go and decrement it
        sem_wait(count_producer); /* protecting critical section */
        insertbuffer(&value);
         (*producer_produced)+= 1;
         printf("Producer %d added %d to buffer\n", value.user_id, value.job_size);
        sem_post(count_producer);
        sem_post(empty_sem); // post (increment) emptybuffer semaphore
    }
    pthread_exit(0);
}
void *consumer(void *thread_n) {
    int thread_numb = *(int *)thread_n;
    buffer_t value;
    int i=0;
    while (1) {
        sem_wait(empty_sem);
        /* there could be race condition here, that could cause
           buffer underflow error */
        sem_wait(buffer_mutex);
        value = dequeuebuffer(&value);
        (consumer_consumed) += 1;
          printf("Consumer %ld dequeue <%d, %d> from buffer\n", pthread_self(), value.user_id, value.job_size);
        sem_post(buffer_mutex);
        sem_post(full_sem); // post (increment) fullbuffer semaphore
       clock_gettime(CLOCK_REALTIME, &end);		/* mark the end time */
       sleep(10);
        (*total_jobs)++;
        *shmid_value += ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0); 
    }
    pthread_exit(0);
}
int main(int argc, char **argv) {
    int numproducers = atoi(argv[1]);
    int numconsumers = atoi(argv[2]);
    pid = malloc(numproducers * sizeof(int));
    key_t key_full, key_empty, key_mutex, key_buffer, key_index, key_value, key_job, key_producer, key_in, key_out, key_produce;
    key_full = 5343;
    key_empty = 5342;
    key_in = 5341;
   key_out = 5340;
    key_mutex = 4567;
    key_buffer = 3145;
    key_index = 3142;
    key_value = 3141;
    key_job = 3140;
    key_producer = 3124;
     key_produce = 3214;

signal(SIGKILL, sigkill_handler);
 
    //pthread_mutex_init(buffer_mutex, NULL);
    int shmid_full = shmget(key_full, sizeof(sem_t), IPC_CREAT | 0600);
    full_sem = shmat(shmid_full, NULL, 0);

    int shmid_empty = shmget(key_empty, sizeof(sem_t), IPC_CREAT | 0600);
    empty_sem = shmat(shmid_empty, NULL, 0);

    int shmid_in = shmget(key_in, sizeof(int), IPC_CREAT | 0600);
   in = shmat(shmid_in, NULL, 0);

   int shmid_out = shmget(key_out, sizeof(int), IPC_CREAT | 0600);
    out = shmat(shmid_out, NULL, 0);

    int shmid_mutex = shmget(key_mutex, sizeof(sem_t), IPC_CREAT | 0600);
    buffer_mutex = shmat(shmid_mutex, NULL, 0);

    int shmid_buffer = shmget(key_buffer, sizeof(buffer_t) * SIZE, IPC_CREAT | 0600);
    buffer = shmat(shmid_buffer, NULL, 0);

   // int shmid_index = shmget(key_index, sizeof(buffer_t) * SIZE, IPC_CREAT | 0600);
   // buffer_index = shmat(shmid_index, NULL, 0);

    int total_value = shmget(key_value, sizeof(double), IPC_CREAT | 0600);
    shmid_value = shmat(total_value, NULL, 0);

    int jobs = shmget(key_job, sizeof(double), IPC_CREAT | 0600);
    total_jobs = shmat(jobs, NULL, 0);

    int producer1 = shmget(key_producer, sizeof(sem_t), IPC_CREAT | 0600);
    count_producer = shmat(producer1, NULL, 0);

 int producer2 = shmget(key_produce, sizeof(int), IPC_CREAT | 0600);
    producer_produced = shmat(producer2, NULL, 0);

    sem_init(full_sem, 1,SIZE); // unsigned int value. Initial value
    sem_init(empty_sem, 1, 0);
   // sem_init(write_sem, 1, 1);
    //sem_init(read_sem,1,1);
    sem_init(buffer_mutex,1,1);
    sem_init(count_producer,1,1);

    //*buffer_index = 0;
     *producer_produced = 0;
    consumer_consumed = 0;
    pid_t ppid;
       for(int i=0; i < numproducers; i++){
        //if(fork() == 0){
          ppid =fork();
           if (ppid < 0) {
               perror("fork error");
               exit(1);
            } 
            else if(ppid ==0){
            producer(i);
            exit(0);
           }
           else{
            pid[i] = ppid;
           }
    //   }
       }
 thread = (pthread_t *) malloc(sizeof(pthread_t) * NUMB_THREADS);
    //thread= malloc(numconsumers * sizeof(pthread_t));
    //int thread_numb[NUMB_THREADS];
    int *thread_numb = malloc(numconsumers * sizeof(int));
    int i;

    if(thread_numb == NULL){
        perror("malloc error");
        exit(1);
    }
    for (i = 0; i < numconsumers; i++) {
        thread_numb[i] = i;
        /*pthread_create(thread + i, // pthread_t *t
                NULL, // const pthread_attr_t *attr
                producer, // void *(*start_routine) (void *)
                thread_numb + i); // void *arg
        i++;
        thread_numb[i] = i;*/
        // playing a bit with thread and thread_numb pointers...
        pthread_create(&thread[i], NULL, consumer, &thread_numb[i]); 
    }
    signal(SIGINT, sigint_handler);


      for (i = 0; i < numproducers; i++) {
        wait(NULL);
    }
    while(*in != *out ){
        sleep(1);
    }
    for(i = 0; i < numconsumers; i++){
            pthread_cancel(thread[i]); 
    }
    sleep(1);
    
    
   // for (i = 0; i < NUMB_THREADS; i++)
   // pthread_join(thread[i], NULL);
    //printf("The job size was %d\n", SIZE);
     printf("The producer produced %d\n", *producer_produced);
      printf("The consumer consumed %d\n", consumer_consumed);
    printf("Total execution time: %f seconds\n", *shmid_value);
    double average_time = (*shmid_value)/(*total_jobs);
    printf("Average waiting time: %f microseconds\n", average_time);
  
    sem_destroy(full_sem);
    sem_destroy(empty_sem);
    //sem_destroy(read_sem);
   // sem_destroy(write_sem);
    sem_destroy(buffer_mutex);
    sem_destroy(count_producer);


    shmdt(full_sem);
    shmdt(count_producer);
     shmdt(producer_produced);
    shmdt(empty_sem);
    shmdt(in);
    shmdt(out);
    shmdt(buffer_mutex);
    shmdt(buffer);
    //shmdt(buffer_index);
    shmdt(shmid_value);
    shmdt(total_jobs);

    shmctl(shmid_full, IPC_RMID, NULL);
    shmctl(shmid_empty, IPC_RMID, NULL);
    shmctl(shmid_in, IPC_RMID, NULL);
    shmctl(shmid_out, IPC_RMID, NULL);
    shmctl(shmid_mutex, IPC_RMID, NULL);
    shmctl(shmid_buffer, IPC_RMID, NULL);
  //  shmctl(shmid_index, IPC_RMID, NULL);
    shmctl(total_value, IPC_RMID, NULL);
    shmctl(jobs, IPC_RMID, NULL);
     shmctl(producer1, IPC_RMID, NULL);
      shmctl(producer2, IPC_RMID, NULL);
    
    return 0;
}






