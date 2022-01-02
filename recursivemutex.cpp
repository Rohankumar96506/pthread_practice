#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutexattr_t mutexRecursion;
pthread_mutex_t tempMutex;

void* recursion(void* args)
{   pthread_mutex_lock(&tempMutex);
    pthread_mutex_lock(&tempMutex);
    printf("I am the only thread expect main thread\n");
    pthread_mutex_unlock(&tempMutex);
    pthread_mutex_unlock(&tempMutex);
    return NULL;
}

int main()
{   pthread_t th;
    pthread_mutexattr_init(&mutexRecursion);
    pthread_mutexattr_settype(&mutexRecursion,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&tempMutex,&mutexRecursion);
    if(pthread_create(&th,NULL,&recursion,NULL)!=0)
    {
        perror("Error 1");
    }

    if(pthread_join(th,NULL)!=0)
    {
        perror("Error 2");
    }
    pthread_mutex_destroy(&tempMutex);
    pthread_mutexattr_destroy(&mutexRecursion);
    pthread_exit(0);
}