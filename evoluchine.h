#ifndef _EVOLUCHINE_H_ 
#define _EVOLUCHINE_H_
#define MULTIPLY 0 
#define NEGATE_MULTIPLY 1 
#define SUM  2
#define NEGATE_SUM 3
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void evoluchine_randomize(unsigned char *operations,int operations_size, int *inputs_order, int input_size);
unsigned char evoluchine_eval(unsigned char *operations,int operations_size, unsigned char *input,int *input_order);
float evoluchine_batch_evaluate(unsigned char *operations,
                            int *inputs_order,
                            int operations_size ,
                            int inputs_size,
                            unsigned char *inputs,
                            unsigned char *ground_thruts,
                            int batch_size); 
void evoluchine_batch_solve(unsigned char *operations,
                            int *inputs_order,
                            int operations_size ,
                            int inputs_size,
                            unsigned char *inputs,
                            unsigned char *ground_thruts,
                            int batch_size,
                            int epochs);

#endif 
