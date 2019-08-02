#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include "malloc.h"

pthread_t tid[4];
int counter;
pthread_mutex_t lock;
void* trythis(void *arg) 
{
    char *s;

    counter += 1; 
    //printf("counter = %d\n", counter);
    //printf("\n Job %d has started\n", counter); 
    //printf("counter = %d\n", counter);
    if (counter == 1)
    {
        printf("-----malloc---------\n");
        s = (char*)malloc(15);
        printf("-----Fin malloc-----\n");
    }
    if (counter == 2)
    {
        printf("-----Realloc---------\n");
        s = (char*)realloc(NULL, 40);
        printf("-----Fin realloc-----\n");
    }
    if (counter == 3)
    {
        printf("-----free---------\n");
        free(NULL);
        printf("-----Fin free-----\n");
    }
    if (counter == 4)
    {
        printf("-----calloc---------\n");
        s = (char*)calloc(15, 1);
        printf("-----Fin calloc-----\n");
    }
    return NULL; 
}

int main(void) 
{ 
    int i = 0; 
    int error; 

    if (pthread_mutex_init(&lock, NULL) != 0) 
    {
       printf("\n mutex init has failed\n"); 
       return 1; 
    }
    while(i < 4) 
    {
       error = pthread_create(&(tid[i]), NULL, &trythis, NULL); 
       if (error != 0) 
           printf("\nThread can't be created : [%s]", strerror(error)); 
       i++; 
    } 
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    pthread_mutex_destroy(&lock); 
    return 0; 
} 
