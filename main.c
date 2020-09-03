
/* Source: https://www.educative.io/edpresso/how-to-sum-an-array-using-threading-in-c
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct data{
    int start;
    int stop;
    int thread_num;
} data;


void *intSum(void *param){
    data *ptr = (data*)param;


    // Declare sum dynamically to return to join:
    long *thread_sum = (long*) calloc(1, sizeof(long));

    for(int i = ptr->start; i <= ptr->stop; i++)
        thread_sum[0] = thread_sum[0] + i;

    printf("Thread Number = %d ;start: %d;stop: %d; get result = %i\n", ptr->thread_num,ptr->start,ptr->stop, thread_sum[0] );

    pthread_exit(thread_sum);
}

int main(int argc, char *argv[]){

    int numThread = atoi(argv[1]);
    int maxNumber = atoi(argv[2]);

    int eachThread  = maxNumber / numThread;


    // Declare arguments for both threads:
    data thread_data[numThread];
    int i=0;
    for(i=0; i<numThread; i++)
    {
        thread_data[i].thread_num = i;
        thread_data[i].start = (eachThread * i) + 1;
        thread_data[i].stop = eachThread * (i+1);
    }
    thread_data[numThread-1].stop += (maxNumber - (eachThread * (numThread))); // if there is remainder


    // Declare thread IDs:
    pthread_t tid[numThread];
    for(i=0; i<numThread; i++)
    {
        // Start threads:
        pthread_create(&tid[i], NULL, intSum, &thread_data[i]);
    }


    // Declare space for sum:
    int *sum[numThread];

    // Retrieve sum of threads:
    for(i=0; i<numThread; i++)
    {
        pthread_join(tid[i], (void**) &sum[i]);
    }

    long result = 0;
    for(i=0; i<numThread; i++)
    {
        result += *sum[i];
    }

    printf("Sum of 1..%d = %i\n", maxNumber, result);
    return 0;
}
