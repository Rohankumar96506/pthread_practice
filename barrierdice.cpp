#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#define THREAD_NUM 51


pthread_barrier_t br;


void* barrierDice(void* args)
{  int n = rand()%5+1;
   printf("waitting for berrier %d\n",*(int*)args);
   sleep(n);
   pthread_barrier_wait(&br);
   int dice = rand()%5+1;
   printf("thread %d -> %d\n",*(int*)args,dice);
   return args;
}

int main()
{   pthread_barrier_init(&br,NULL,3);
    pthread_t th[THREAD_NUM];
    for(int i =0;i<THREAD_NUM;i++)
    {   int* a = new int;
        *a = i;
        if(pthread_create(&th[i],NULL,&barrierDice,a)!=0)
        {
            perror("Error 1");
        }

    }

    for(int i = 0;i<THREAD_NUM;i++)
    {   int * a = NULL;
        if(pthread_join(th[i],(void**)&a));
        delete a;
    }
    pthread_barrier_destroy(&br);
    pthread_exit(0);
}