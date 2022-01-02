#include<iostream>
#include<pthread.h>
#include<unistd.h>
#define THREAD_NUM 50

using namespace std;

pthread_mutex_t mutex;

void* dice(void* args)
{   int i = *(int*)args;
    int n = rand()%6+1;
    pthread_mutex_lock(&mutex);
    cout<<"thread "<<i<<" -> "<<n<<endl;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{   pthread_mutex_init(&mutex,NULL);
    pthread_t th[THREAD_NUM];
    for(int i = 0;i<THREAD_NUM;i++)
    {   int* a = new int;
        *a = i;
        pthread_create(&th[i],NULL,&dice,a);

    }

    for(int i = 0;i<THREAD_NUM;i++)
    {
        pthread_join(th[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_exit(0);
}