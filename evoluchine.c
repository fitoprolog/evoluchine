#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<stdint.h>
#include <evoluchine.h>

struct train_parameters evoluchine_init_train_parameters(int32_t limit,
                                                         int32_t internal_limit){  
  struct train_parameters ret;

  ret.inputs_order = (int32_t *) malloc(sizeof(int32_t)*limit);
  memset(ret.inputs_order,0,sizeof(int32_t)*limit);
  ret.operations   = (unsigned char*) malloc(sizeof(unsigned char)*limit);
  memset(ret.operations,0,sizeof(unsigned char)*limit);
  ret.operations_size=limit;
  ret.internal_constants_size=internal_limit;
  if (internal_limit){
    ret.internal_constants = (unsigned char*) malloc(sizeof(unsigned char)*internal_limit);
    memset(ret.internal_constants,0,sizeof(unsigned char)*internal_limit);
  }
  return ret;
}

void evoluchine_randomize(unsigned char *operations,int32_t operations_size, int32_t *inputs_order, 
                          int32_t input_size,unsigned char *internal_constants,int32_t internal_limit){
  for(int32_t o=0;o!= operations_size;o++){
    if ( random()%2)
        operations[o]=random()%NUMBER_OF_OPERATIONS;
    if ( random()%2)
      inputs_order[o]=random()%(input_size+internal_limit);
  }
  for(int32_t i=0; i!= internal_limit; i++){
    if (random()%2)
      internal_constants[i] = random();
  }
}

unsigned char evoluchine_eval(unsigned char *operations,int32_t operations_size, 
                              unsigned char *input,int32_t *input_order,
                              unsigned char *internal_constants,
                              int32_t internal_limit)
  
{
  unsigned char SOM=0;
  int32_t op;
  unsigned char mulregister=input[0];
  unsigned char cop;
  unsigned char *input_source = input;
  int32_t input_offset =0;
  for(op=0; op!= operations_size+internal_limit; op++)
  {
     if (op == operations_size ){
       input_source = internal_constants;
       input_offset = operations_size;
     }
     cop = operations[op];
     switch(cop){
        case SUM:
          SOM=MAX(mulregister,SOM);
          if ( (op+1) < operations_size+internal_limit)
            mulregister=input_source[input_order[op+1-input_offset]];
          break;
        case REST_ARITHMETIC:
          SOM = SOM-mulregister;
          if ( (op+1) < operations_size+internal_limit)
            mulregister=input_source[input_order[op+1-input_offset]];
          break;
        case MULTIPLY:
          mulregister =MIN(mulregister,input_source[input_order[op-input_offset]]);
          break;
        case NEGATE_MULTIPLY:
          mulregister =MIN(mulregister,255-input_source[input_order[op-input_offset]]); 
          break;
        case NEGATE_SUM:
           SOM=MAX(255-mulregister,SOM);
           if ( (op+1) < operations_size+internal_limit)
             mulregister=input_source[input_order[op+1-input_offset]]; 
           break;
        case  MULTIPLY_ARITHMETIC:
           mulregister *= input_source[input_order[op+1-input_offset]];
           break;
        case SUM_ARITHMETIC:
           SOM+=mulregister;
           if ( (op+1) < operations_size+internal_limit)
             mulregister=input_source[input_order[op+1-input_offset]];
           break;
        case DISPLACE_LEFT:
           mulregister = mulregister << input_source[input_order[op+1-input_offset]];
          break;
        case DISPLACE_RIGHT:
          mulregister = mulregister >> input_source[input_order[op+1-input_offset]];
          break;

        case DO_NOTHING:
          break;

     }
  }
  return SOM;
}
float evoluchine_batch_evaluate(struct train_parameters * p){
  float err=0;
  unsigned char res;
  for(int32_t b=0; b != p->batch_size; b++){
    res = evoluchine_eval(p->operations,
                          p->operations_size,
                          (p->train_inputs+b*p->inputs_size),
                          p->inputs_order,
                          p->internal_constants,
                          p->internal_constants_size);
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
  unsigned char *mutated_constants = (unsigned char *)malloc(p->internal_constants_size);
  struct train_parameters mutated_params=*p;

  mutated_params.operations = mutated_operations;
  mutated_params.inputs_order = mutated_order;
  mutated_params.internal_constants = mutated_constants;

  memset(mutated_operations,0,p->operations_size);
  memset(mutated_order,0,sizeof(int32_t)*p->operations_size);
  memset(mutated_constants,0,p->internal_constants_size);

  for (int32_t e=0; e!= p->epochs; e++){
    evoluchine_randomize(mutated_operations,p->operations_size, mutated_order,p->inputs_size,
                         p->internal_constants,p->internal_constants_size);
    const float mError = evoluchine_batch_evaluate(&mutated_params);
    printf("Mutated Error (%d)=%f\n",e,mError);
    if (mError < lastError){
      lastError = mError;
      memcpy(p->operations, mutated_operations, p->operations_size*sizeof(unsigned char));
      memcpy(p->inputs_order, mutated_order, p->operations_size*sizeof(int32_t));
      memcpy(p->internal_constants,mutated_constants,p->internal_constants_size);
      if (mError <= 1e-16) {
        printf("Bingo %f!\n",mError);
        return;
      }
    }
  }
}


