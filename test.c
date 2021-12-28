#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <evoluchine.h>
#define NPARAMETERS 6

void train_fuzzy_xor(){
  unsigned char train_inputs[]={0,0,255,0,0,255,255,255,0,128,128,0};
  unsigned char train_grounds[]={0,255,255,0,128,128};
  struct train_parameters p= evoluchine_init_train_parameters(100);
  p.batch_size=sizeof(train_grounds);
  p.ground_truth = train_grounds;
  p.increase_operations_each_n_epoch=1000;
  p.inputs_size=2;
  p.operations_size=10;
  p.train_inputs = train_inputs;
  p.epochs=1000;
  evoluchine_batch_solve(&p);
  printf("----------------------------Results-------------------------\n");
  unsigned char testInput[]={25,0};
  unsigned char res = evoluchine_eval(p.operations,p.operations_size,testInput,p.inputs_order);
  printf("res %d\n",res);
  testInput[0]=0;
  testInput[1]=200;
  res = evoluchine_eval(p.operations,p.operations_size,testInput,p.inputs_order);
  printf("res %d\n",res);
  testInput[0]=200;
  res = evoluchine_eval(p.operations,p.operations_size,testInput,p.inputs_order);
  printf("res %d\n",res);
  
}

int main()
{
  train_fuzzy_xor();
}
