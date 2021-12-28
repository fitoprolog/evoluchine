#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<stdint.h>
#include <evoluchine.h>
#define MULTIPLY 0 
#define NEGATE_MULTIPLY 1 
#define SUM  2
#define NEGATE_SUM 3

struct train_parameters evoluchine_init_train_parameters(int32_t limit){  
  struct train_parameters ret;

  ret.inputs_order = (int32_t *) malloc(sizeof(int32_t)*limit);
  memset(ret.inputs_order,0,sizeof(int32_t)*limit);
  ret.operations   = (unsigned char*) malloc(sizeof(unsigned char)*limit);
  memset(ret.operations,0,sizeof(unsigned char)*limit);

  return ret;
}

void evoluchine_randomize(unsigned char *operations,int32_t operations_size, int32_t *inputs_order, int32_t input_size){
  for(int32_t o=0;o!= operations_size;o++){
    if ( random()%2)
        operations[o]=random()%4;
    if ( random()%2){
      inputs_order[o]=random()%input_size;
    }
  }
}

unsigned char evoluchine_eval(unsigned char *operations,int32_t operations_size, unsigned char *input,int32_t *input_order)
{
  unsigned char SOM=0;
  int32_t op;
  unsigned char mulregister=input[0];
  unsigned char cop;
  for(op=0; op!= operations_size; op++)
  {
     cop = operations[op];
     switch(cop){
        case SUM:
          SOM+=mulregister;
          if ( (op+1) < operations_size)
            mulregister=input[input_order[op+1]];
          break;
        case MULTIPLY:
          mulregister =MIN(mulregister,input[input_order[op]]);
          break;
        case NEGATE_MULTIPLY:
          mulregister =MIN(mulregister,255-input[input_order[op]]); 
          break;
        case NEGATE_SUM:
           SOM+=255-mulregister;
           if ( (op+1) < operations_size)
             mulregister=input[input_order[op+1]]; 
           break;
     }
  }
  return SOM;
}
float evoluchine_batch_evaluate(struct train_parameters * p){
  float err=0;
  unsigned char res;
  for(int32_t b=0; b != p->batch_size; b++)
  {
    res = evoluchine_eval(p->operations,
                          p->operations_size,
                          (p->train_inputs+b*p->inputs_size),
                          p->inputs_order);
    if (p->ground_truth[b] != res )
      printf("Expected %d Got %d\n",p->ground_truth[b],res);
    err += abs(res-p->ground_truth[b]);
  }
  return err;
}


void evoluchine_batch_solve(struct train_parameters *p){

  float lastError=0;
  srand(time(0));
  
  lastError=evoluchine_batch_evaluate(p);
  unsigned char *mutated_operations = 
                (unsigned char *)malloc(p->parameter_increase_limit * sizeof (unsigned char));
  int32_t  *mutated_order  = (int32_t  *)malloc(sizeof(int32_t)*p->parameter_increase_limit);

  struct train_parameters mutated_params=*p;
  mutated_params.operations = mutated_operations;
  mutated_params.inputs_order = mutated_order;
  memset(mutated_operations,0,p->operations_size);
  memset(mutated_order,0,sizeof(int32_t)*p->operations_size);
  for (int32_t e=0; e!= p->epochs; e++){
    evoluchine_randomize(mutated_operations,p->operations_size, mutated_order,p->inputs_size);
    const float mError = evoluchine_batch_evaluate(&mutated_params);
    printf("Mutated Error (%d)=%f\n",e,mError);
    if (mError < lastError)
    {
      lastError = mError;
      memcpy(p->operations, mutated_operations, p->operations_size*sizeof(unsigned char));
      memcpy(p->inputs_order, mutated_order, p->operations_size*sizeof(int32_t));
      if (mError <= 1e-12) {
        printf("Bingo %f!\n",mError);
        return;
      }
    }
  }
}


