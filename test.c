#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <evoluchine.h>
#define NPARAMETERS 6
int main()
{
  srand(time(0));
  unsigned char xor_equation[]={MULTIPLY,NEGATE_MULTIPLY,SUM,NEGATE_MULTIPLY,MULTIPLY,SUM};
  int xor_order[]={0,1,-1,0,1,-1}; 
  //unsigned char xor_equation[]={1,2,1,2};
  //int xor_order[] = { 1,0,1,0};
  unsigned char a[]={0,0};
  unsigned char b[]={255,0};
  unsigned char c[]={0,255};
  unsigned char d[]={255,255};
  printf("%d\n",evoluchine_eval(xor_equation,4,a,xor_order));
  printf("%d\n",evoluchine_eval(xor_equation,4,b,xor_order));
  printf("%d\n",evoluchine_eval(xor_equation,4,c,xor_order));
  printf("%d\n",evoluchine_eval(xor_equation,4,d,xor_order));
  //return 1;
  unsigned char rand_opers[NPARAMETERS]={0};//={MULTIPLY,NEGATE_MULTIPLY,SUM,NEGATE_MULTIPLY,MULTIPLY,SUM};
  int rand_inputs[NPARAMETERS]={0};//={0,1,-1,0,1,-1};
  unsigned char train_inputs[]={0,0,255,0,0,255,255,255,0,128,128,0};
  unsigned char train_grounds[]={0,255,255,0,128,128};
  evoluchine_batch_solve(rand_opers,rand_inputs,NPARAMETERS,2,train_inputs,train_grounds,6,100000);
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
  unsigned char fuzzy_input[]={128,0};
  printf("%d\n",evoluchine_eval(rand_opers,NPARAMETERS,fuzzy_input,rand_inputs)); 
  fuzzy_input[0]=83;
  fuzzy_input[1]=0;
  printf("%d\n",evoluchine_eval(rand_opers,NPARAMETERS,fuzzy_input,rand_inputs));

}
