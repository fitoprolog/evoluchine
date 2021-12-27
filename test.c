#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <evoluchine.h>
#define NPARAMETERS 4
int main()
{
  srand(time(0));
  //char xor_equation[]={MULTIPLY,NEGATE_MULTIPLY,SUM,NEGATE_MULTIPLY,MULTIPLY,SUM};
  //int xor_order[]={0,1,-1,0,1,-1}; 
  char xor_equation[]={1,2,1,2};
  int xor_order[] = { 1,0,0,0};
  char a[]={0,0};
  char b[]={1,0};
  char c[]={0,1};
  char d[]={1,1};
  printf("%d\n",evoluchine_eval(xor_equation,4,a,xor_order));
  printf("%d\n",evoluchine_eval(xor_equation,4,b,xor_order));
  printf("%d\n",evoluchine_eval(xor_equation,4,c,xor_order));
  printf("%d\n",evoluchine_eval(xor_equation,4,d,xor_order));
  char rand_opers[NPARAMETERS]={0};//={MULTIPLY,NEGATE_MULTIPLY,SUM,NEGATE_MULTIPLY,MULTIPLY,SUM};
  int rand_inputs[NPARAMETERS]={0};//={0,1,-1,0,1,-1};
  evoluchine_randomize(rand_opers,NPARAMETERS,rand_inputs,2);
  //printf("RANDOMIZED %d\n",evoluchine_eval(rand_opers,6,a,rand_inputs));
  char train_inputs[]={0,0,1,0,0,1,1,1};
  char train_grounds[]={0,1,1,0};
  evoluchine_batch_solve(rand_opers,rand_inputs,NPARAMETERS,2,train_inputs,train_grounds,4,100);
  for (int i=0; i!= NPARAMETERS; i++)
  {
    printf(" %d ",rand_opers[i]);
  }
  printf("\n");
  printf("--------------------\n");
  for (int i=0; i!= NPARAMETERS; i++)
  {
    printf(" %d ",rand_inputs[i]);
  }
  printf("\n");

}
