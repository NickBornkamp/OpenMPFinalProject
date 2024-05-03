/****************************************************************************** 
*  Name: Nicholas Bornkamp                                                    *
*  ID: 916320670                                                              *
*  Final Project                                                              *
*   I vow that my work is my own, unless otherwise explained or outlined.     *
*  To Compile: gcc -o primes.out Project.c -fopenmp -lm                         *
*  To run: ./primes.out <number> <threads>                                    *
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>

double gettime(void) {
  struct timeval tval;

  gettimeofday(&tval, NULL);

  return( (double)tval.tv_sec + (double)tval.tv_usec/1000000.0 );
}

int *allocarray(int value) {
  int i;
  int *a;
  
  
  a = (int *)malloc(value*sizeof(int));

  
  return a;
}

// Function to free an array
void freearray(int *arr) {

    free(arr);
}

int *initarray(int *a, int value) {
  int i;
    
  for (i=2; i<=value; i++)

      a[i-2] = i;
  
  return a;
}

void printarray(int *a, int value) {
  int i;
  
  for (i=0; i<value-1; i++) {
      printf("%d ", a[i]);
  }
  printf("\n");
}

void printLastTen(int *a, int value) {
  int i;
  
  for (i=0; i < 10; i++) {
      printf("%d ", a[value - 1 - i]);
  }
  printf("\n");
}

int findIndex(int *a, int size, int value )
{
    int index = 0;

    while ( index < size && a[index] != value ) ++index;

    return ( index == size ? -1 : index );
}

int length(int *a){
   
     int i;
    int count = 0;
    for(i=0; a[i]!='\0'; i++)
    {
        count++;
    }
    return count;
}

int countPrimes(int *a){
  int count = 0;
  
  for(int i = 0; a[i]!='\0'; i++){
    if (a[i] != -1)
    count++;
  
  }
    printf("Total primes: %d\n", count);
    return count;
}

int *listPrimes(int *a, int threads, int N){
    int value, index;
    int finalSize = N - 1;
    printf("Array Size: %d\n", finalSize);
    
    int count = 0;
    int n;
    int endValue = (int)(sqrt(N) + 1);
    
    printf("Final Value: %d\n", endValue);
    
    #pragma omp parallel num_threads(threads) private(n)
    {
    
    #pragma omp for private(n)
    
    for (n = 2; n < endValue; n++){
    int tid = omp_get_thread_num();
    
      for(int j = 0; j < n + 1; j++) 
          if(a[j] == n)
            continue;
    
      value = n * n;
      index = findIndex(a, finalSize, value);
      
      for(int i = index; i < N - 1; i++){
        if (a[i] % n == 0)
          a[i] = -1;
          //finalSize -= 1;
      }
      
      count += 1;
      
     // #pragma omp barrier
      if(count % 10 == 0 && tid == threads-1 ){
        printf("\rCurrent value for Thread %d: %d", tid, n);
        fflush(stdout);
        } 
    
    }
    
    } //end of parallel
    printf("\n"); 
    count = countPrimes(a);
    int *result = NULL;
    result = allocarray(count);
    //result = initarray(result, finalSize+1);
    //printf("%d is result length\n", length(result));
    
    int resInd = 0;
    for (int i = 0; i < N-1; i++)
      if(a[i] != -1 && i < finalSize){
        result[resInd] = a[i];
        resInd += 1;
        //printf("%d is i\n", i);
      }
    
    //printArra
    return result;
}

int main(int argc, char **argv){

  printf("Hello World\n");
  double starttime, endtime;
   
  if (argc != 3) {
      printf("Two argument needed. Usage: %s <Highest Value>, <ThreadCount>\n", argv[0]);
      exit(-1);
    }
  
  
  int N = atoi(argv[1]);
  int threads = atoi(argv[2]);
  int *full, *result = NULL;
  full = allocarray(N-1);
  full = initarray(full, N);
  
  //printarray(full, N);
  int spot = length(full);
   
  printf("Length: %d\n", spot);
  starttime = gettime();
  
  
  result = listPrimes(full, threads, N);
  endtime = gettime();
  spot = length(result);
  printLastTen(result, spot);
  spot = length(result);
  printf("Length: %d\n", spot);
  
  printf("Time taken = %lf seconds\n", endtime-starttime);
  
  
return 0;
}



