/** 
 * @file Kartoshka.c
 * @brief Simulation of Kartoshka game (Papa Caliente) using pthreads
 * 
 * @author Emmanuel Zúñiga Chaves - B98729
 * Contact: emmanuel.zunigachaves@ucr.ac.cr
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct
{
    size_t total;
    size_t token; //Value
    size_t lastOne;
    size_t gameOver;
    pthread_mutex_t mutex;
} shared_data_t;

typedef struct
{
    size_t id;
    size_t alive;
    size_t local_token;
    shared_data_t *shared_data;
} thread_data_t;

/* Procedures */
void *run(void *);
int collatz(int);

int main(int argc, char *argv[])
{
    /* List of variables */
    size_t thread_count = 0;
    size_t value = 0;
    size_t rotation = 0;
    size_t init = 0;
    size_t index = 0;
    size_t item = 0;

    /* Verifyng the arguments */
    if (argc > 3)
    {
        thread_count = (size_t)strtoul(argv[1], NULL, 10);
        value = (size_t)strtoul(argv[2], NULL, 10);
        rotation = (size_t)strtoul(argv[3], NULL, 10);
    }
    else
    {
        fprintf(stderr, "Error, invalid number of parameters.\n");
    }

    /* List of dynamic arrays */
    pthread_t *threads = (pthread_t *)malloc((size_t)(thread_count * sizeof(pthread_t)));

    shared_data_t *shared_data = (shared_data_t *)calloc(1, sizeof(shared_data_t));

    thread_data_t *thread_data_list = (thread_data_t *)malloc((size_t)(thread_count * sizeof(thread_data_t)));

    srand(time(NULL));
    init = random() % thread_count;
    item = random() & value;
    // To avoid item = 0
    if (item == 0){
        item++;
    }

    printf("The item is %zu \n", item);
    index = init;
    printf("Creating a game with %zu players, start player # %zu with item # %d \n", thread_count, init, (int)item);

    /* Initialize all the threads data */
    for (size_t i = 0; i < thread_count; ++i)
    {
        thread_data_list[i].id = i;
        thread_data_list[i].shared_data = shared_data;
        thread_data_list[i].local_token = item;
        thread_data_list[i].shared_data->gameOver = 0;
        thread_data_list[i].alive = 1; //In the first round, all the players are alive
        thread_data_list[i].shared_data->total = thread_count;
    }

    /* This while loop, simulates the round */
    while (shared_data->gameOver != 1)
    {
        pthread_create(&threads[index], NULL, run, (void *)&thread_data_list[index]);

        index += rotation;

        if (index == thread_count)
        {
            index = 0;
        }
        else if (index == -1)
        {
            index = thread_count - 1;
        }
    }

    /* Suspend execution of the calling thread */
    for (size_t i = 0; i < thread_count; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    printf("The winner is thread # %zu.\n", shared_data->lastOne);

    /* Freeing up the memory */
    pthread_mutex_destroy(&shared_data->mutex);
    free(threads);
    free(shared_data);
    free(thread_data_list);

    return 0;
}
/**
 * @brief Apply the collatz conjecture to the token of every thread
 * @param item the local token of every thread
 * @return returns the new value of the token, after applying the collatz conjecture
 */
int collatz(int item)
{
    if (1 == (item & 0x1))
    {
        item = (item << 1) + item + 1;
    }
    else
    {
        item >>= 1;
    }
    return item;
}

/**
 * @brief The thread executes the kartoshka game with a mutex
 * @param args list of the thread data
 * @return Null
 */
void *run(void *args)
{
    thread_data_t *data = (thread_data_t *)args;
    size_t id = data->id;
    shared_data_t *shared_data = data->shared_data;

    pthread_mutex_lock(&shared_data->mutex);

    if (data->alive)
    {
        data->local_token = collatz((int)data->local_token);
        usleep(100000);
        printf("Thread # %zu changing the token value to %zu \n", id, data->local_token);
    }

    //Verify if the token value of this thread is 1, if it is the thread will left the game
    if (data->local_token == 1 && data->alive)
    {
        data->alive = 0;
        --shared_data->total;
        printf("Thread # %zu has left the game.\n", id);
    }
    
    //Verify if there is only one thread playing
    if (shared_data->total == 1)
    {
        data->shared_data->gameOver = 1;
        data->local_token = -1;
        data->shared_data->lastOne = id;
    }

    pthread_mutex_unlock(&shared_data->mutex);

    return NULL;
}