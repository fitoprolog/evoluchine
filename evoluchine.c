#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <evoluchine.h>
#define MULTIPLY 0 
#define NEGATE_MULTIPLY 1 
#define SUM  2
#define NEGATE_SUM 3

void evoluchine_randomize(char *operations,int operations_size, int *inputs_order, int input_size){
  for(int o=0;o!= operations_size;o++){
    if ( random()%2)
        operations[o]=random()%4;
    if ( random()%2){
      inputs_order[o]=random()%input_size;
    }
  }
}

char evoluchine_eval(char *operations,int operations_size, char *input,int *input_order)
{
  char SOM=0;
  int op;
  char mulregister=1;
  char cop;
  for(op=0; op!= operations_size; op++)
  {
     cop = operations[op];
     switch(cop){
        case SUM:
          
          SOM += mulregister;
          if (SOM >1 ) 
            SOM=0;
          mulregister=1;
          break;
        case MULTIPLY:
          mulregister*=input[input_order[op]];
          break;
        case NEGATE_MULTIPLY:
          mulregister*=!input[input_order[op]];
          break;
        case NEGATE_SUM:
          SOM += !mulregister;
          if (SOM >1 ) 
            SOM=0;
          break;
     }
  }
  return SOM;
}
float evoluchine_batch_evaluate(char *operations,
                            int *inputs_order,
                            int operations_size ,
                            int inputs_size,
                            char *inputs,
                            char *ground_thruts,
                            int batch_size){
  float err=0;
  char res;
  for(int b=0; b != batch_size; b++)
  {
    res = evoluchine_eval(operations,
                          operations_size,
                          (inputs+b*inputs_size),
                          inputs_order);
    if (res != ground_thruts[b])
      err++;
  }
  return err/batch_size;
}


void evoluchine_batch_solve(char *operations,
                            int *inputs_order,
                            int operations_size ,
                            int inputs_size,
                            char *inputs,
                            char *ground_thruts,
                            int batch_size,
                            int epochs){

  float lastError=0;
  srand(time(0));
   
  lastError=evoluchine_batch_evaluate(operations,inputs_order,operations_size,
                                      inputs_size,inputs,ground_thruts,batch_size);

  char *mutated_operations = (char *)malloc(operations_size);
  int  *mutated_order      = (int  *)malloc(sizeof(int)*operations_size);
  
  for (int e=0; e!= epochs; e++){
    evoluchine_randomize(mutated_operations,operations_size, mutated_order,inputs_size);
    float mError = evoluchine_batch_evaluate(mutated_operations,mutated_order,
                                             operations_size,inputs_size,inputs,ground_thruts,batch_size);
    printf("Mutated Error (%d)=%f\n",e,lastError);
    if (mError < lastError)
    {
      lastError = mError;
      memcpy(operations, mutated_operations, operations_size);
      memcpy(inputs_order, mutated_order, operations_size);
    }
  }
  printf("Error %f\n",lastError);
}


