#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#define THREAD_NUM 5

void* print(void* args)
{
    printf("Thread %d hello %lu\n",*(int*)args,pthread_self());
    free(args);
    return NULL;
}


int main()
{ pthread_t th[THREAD_NUM];
  pthread_attr_t detach_attr;
  pthread_attr_init(&detach_attr);
  pthread_attr_setdetachstate(&detach_attr,PTHREAD_CREATE_DETACHED);
  for(int i = 0;i<THREAD_NUM;i++)
  {   int* a = new int;
      *a = i;
      pthread_create(&th[i],&detach_attr,&print,a);
  }    
    
  pthread_attr_destroy(&detach_attr);
  pthread_exit(0);
}
