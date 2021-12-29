#include<stdint.h>
#ifndef _EVOLUCHINE_H_ 
#define _EVOLUCHINE_H_
#define MULTIPLY 0 
#define NEGATE_MULTIPLY 1 
#define SUM  2
#define NEGATE_SUM 3
#define MULTIPLY_INTERNAL 4
#define NEGATE_MULTIPLY_INTERNAL 5

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void evoluchine_randomize(unsigned char *operations,int32_t operations_size, 
                         int *inputs_order, int input_size,
                         unsigned char *internal_constants,int32_t internal_limit);
unsigned char evoluchine_eval(unsigned char *operations,int32_t operations_size, 
                              unsigned char *input,int *input_order,
                              unsigned char *internal_constants,
                              int32_t internal_constants_size);

struct train_parameters{
  unsigned char *operations; 
  int32_t *inputs_order; 
  int32_t inputs_size;
  int32_t operations_size;
  unsigned char *train_inputs;
  unsigned char *ground_truth;
  unsigned char *internal_constants; 
  int32_t internal_constants_size;
  int32_t batch_size;
  int32_t increase_operations_each_n_epoch;
  int32_t parameter_increase_limit;
  int32_t epochs;
};

float evoluchine_batch_evaluate(struct train_parameters *params); 
void  evoluchine_batch_solve(struct train_parameters *params);
struct train_parameters evoluchine_init_train_parameters(int32_t limitParameters,
                                                         int32_t internal_limit);

#endif 
