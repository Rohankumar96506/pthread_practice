#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#define THREAD_CAR 6
#define THREAD_FILLER 5

int fuel = 45;
pthread_cond_t fullerCond;
pthread_mutex_t carmutex;

void* carFilling(void* args)
{   
    pthread_mutex_lock(&carmutex);
    while(50>fuel)
    {
        pthread_cond_wait(&fullerCond,&carmutex);
    }
    fuel = fuel - 50;
    printf("car %d fill the tank and remaining fuel %d\n",*(int*)args,fuel);
    pthread_mutex_unlock(&carmutex);

    return args;
}

void* tankFiller(void* args)
{
    pthread_mutex_lock(&carmutex);
    fuel = fuel + 55;
    printf("filler %d fill the fuel %d\n",*(int*)args,fuel);
    pthread_mutex_unlock(&carmutex);
    pthread_cond_broadcast(&fullerCond);
    return args;
}

int main()
{   pthread_t car[THREAD_CAR];
    pthread_t filler[THREAD_FILLER];
    pthread_cond_init(&fullerCond,NULL);
    pthread_mutex_init(&carmutex,NULL);
    for(int i = 0;i<THREAD_CAR;i++)
    {   int* a = new int;
        *a = i;
        pthread_create(&car[i],NULL,&carFilling,a);
    }

    for(int i = 0;i<THREAD_FILLER;i++)
    {
        int* a = new int;
        *a = i;
        pthread_create(&filler[i],NULL,&tankFiller,a);
    }

    for(int i = 0;i<THREAD_CAR;i++)
    {   int* a = NULL;
        pthread_join(car[i],(void**)&a);
        delete a;
    }

    for(int i = 0;i<THREAD_FILLER;i++)
    {
        int* a = NULL;
        pthread_join(filler[i],(void**)&a);
        delete a;
    }

    pthread_mutex_destroy(&carmutex);
    pthread_cond_destroy(&fullerCond);
    pthread_exit(0);
}