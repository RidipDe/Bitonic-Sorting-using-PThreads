#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval startwtime, endwtime;
double seq_time;

int N;          // data array size
int *a;         // data array to be sorted
const int ASCENDING  = 1;
const int DESCENDING = 0;
void init(void);
void print(void);
void sort(void);
void test(void);
inline void exchange(int i, int j);
void compare(int i, int j, int dir);
void bitonicMerge(int lo, int cnt, int dir);
void recBitonicSort(int lo, int cnt, int dir);
void impBitonicSort(void);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: Please provide size of the problem as argument(number of elements in the array)");
    exit(1);
  }
  N = atoi(argv[1]);
  a = (int *) malloc(N * sizeof(int));
  init();
  gettimeofday (&startwtime, NULL);
  sort();
  gettimeofday (&endwtime, NULL);
  //printf("After Sorting\n");
  //print();
  seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
		      + endwtime.tv_sec - startwtime.tv_sec);
  printf("Time taken = %f\n", seq_time);
  test();
  // print();
}
//test the result
void test() {
  int pass = 1;
  int i;
  for (i = 1; i < N; i++) {
    pass &= (a[i-1] <= a[i]);
  }
  printf(" TEST %s\n",(pass) ? "PASSED" : "FAILED!");
}
//Initialize the the array with data
void init() {
  int i;
  for (i = 0; i < N; i++) {
     a[i] = rand() % N; // (N - i);
    //a[i] = (N - i);
  }
   printf("before\n");
   //print();
}
//Display
void print() {
  int i;
  for (i = 0; i < N; i++) {
    printf("%d\n", a[i]);
  }
  printf("\n");
}
//Swap
inline void exchange(int i, int j) {
  int t;
  t = a[i];
  a[i] = a[j];
  a[j] = t;
}
//Compare
void compare(int i, int j, int dir) {
  if (dir==(a[i]>a[j])) 
    exchange(i,j);
}
//Bitonic merge
void bitonicMerge(int lo, int cnt, int dir) {
  if (cnt>1) {
    int k=cnt/2;
    int i;
    for (i=lo; i<lo+k; i++)
      compare(i, i+k, dir);
    bitonicMerge(lo, k, dir);
    bitonicMerge(lo+k, k, dir);
  }
}
//Bitonic sort
void recBitonicSort(int lo, int cnt, int dir) {
  if (cnt>1) {
    int k=cnt/2;
    recBitonicSort(lo, k, ASCENDING);
    recBitonicSort(lo+k, k, DESCENDING);
    bitonicMerge(lo, cnt, dir);
  }
}
//Initial call to bitonic sort on lenght N
void sort() {
  recBitonicSort(0, N, ASCENDING);
}
