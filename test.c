#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <evoluchine.h>
#include <math.h>
#define NPARAMETERS 6

void train_fuzzy_xor(){
  unsigned char train_inputs[]={5,1,  2,2, 200,1,  10,4,  100,1,  200,1};
  unsigned char train_grounds[]={4,   0,    199,   6,      99,    199};

 
  struct train_parameters p= evoluchine_init_train_parameters(100,11);
  p.batch_size=sizeof(train_grounds);
  p.ground_truth = train_grounds;
  p.increase_operations_each_n_epoch=1000;
  p.train_inputs = train_inputs;
  p.epochs=1000000;
  p.inputs_size=2;
  evoluchine_batch_solve(&p);
  printf("----------------------------Results-------------------------\n");
  unsigned char testInput[]={2,2};
  unsigned char res = evoluchine_eval(p.operations,p.operations_size,testInput,p.inputs_order,
                                      p.internal_constants,p.internal_constants_size);
  printf("res %d\n",res);
  testInput[0]=198;
  testInput[1]=20;
  res = evoluchine_eval(p.operations,p.operations_size,testInput,p.inputs_order,
                        p.internal_constants,p.internal_constants_size);
  printf("res %d\n",res);
  testInput[0]=7;
  res = evoluchine_eval(p.operations,p.operations_size,testInput,p.inputs_order,
                        p.internal_constants,p.internal_constants_size);
  printf("res %d\n",res);
  printf("%d %d",p.operations[0],p.operations[1]);
  
}
void test_sum(){
  unsigned char train_inputs[]={100,1};
  struct train_parameters p= evoluchine_init_train_parameters(2,0);
  p.inputs_order[0]=0;
  p.inputs_order[1]=1;
  p.operations[0]=SUM_ARITHMETIC;
  p.operations[1]=REST_ARITHMETIC;
  unsigned char res = evoluchine_eval(p.operations,p.operations_size,train_inputs,
                             p.inputs_order,p.internal_constants,p.internal_constants_size);
  printf("%d\n",res);
  /*struct train_parameters p= evoluchine_init_train_parameters(1,0);
  p.batch_size=sizeof(train_grounds);
  p.ground_truth = train_grounds;
  p.increase_operations_each_n_epoch=1000;
  p.inputs_size=2;
  p.operations_size=1;
  p.train_inputs = train_inputs;
  p.epochs=1000000;
  evoluchine_batch_solve(&p);*/
 
}

void train_sin(){
  unsigned char train_inputs[]={0,0,255,0,0,255,255,255,0,128,128,0};
  unsigned char train_grounds[]={0,255,255,0,128,128};
  struct train_parameters p= evoluchine_init_train_parameters(10,6);
  p.batch_size=sizeof(train_grounds);
  p.ground_truth = train_grounds;
  p.increase_operations_each_n_epoch=1000;
  p.inputs_size=2;
  p.operations_size=10;
  p.train_inputs = train_inputs;
  p.epochs=10000;
  evoluchine_batch_solve(&p);
}

int main()
{
  train_fuzzy_xor();
  //test_sum();
}
