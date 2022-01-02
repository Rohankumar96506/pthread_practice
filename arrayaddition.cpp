
#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#define THREAD_NUM 1

int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

void* arraySum(void* args)
{   int* sum = new int;
    *sum = 0;
    int* id = (int*)args;
    int length = (sizeof(arr))/sizeof(arr[0]);
    int div = length/THREAD_NUM;
    int rem = length%THREAD_NUM;
    int i = 0;

    if(*id==THREAD_NUM-1 && rem!=0)
        {*id = *id * div;
         rem = div+rem;
         while(rem--)
         {  
            *sum = *sum + arr[*id+i++];
         }

        }
    else{
        *id = *id * div;
        while(div--)
        { *sum = *sum + arr[*id+i++];
            

        }
    }
   free(args);

   return sum;



}


int main()
{   
    int* temp[THREAD_NUM];
    

    int sum = 0;
    pthread_t th[THREAD_NUM];
    for(int i = 0;i<THREAD_NUM;i++)
    {   int* a = new int;
        *a = i;
        if(pthread_create(&th[i],NULL,&arraySum,a)!=0)
        {
            perror("Error 1");
        }

    }
    
    for(int i = 0;i<THREAD_NUM;i++)
    {
        if(pthread_join(th[i],(void**)&temp[i])!=0)
        {
            perror("Error 1");
        }
    }

    for(int i =0;i<THREAD_NUM;i++)
    {
       sum = sum + *temp[i];
    }

    std::cout<<sum<<std::endl;
    
    pthread_exit(0);
}