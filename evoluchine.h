#ifndef _EVOLUCHINE_H_ 
#define _EVOLUCHINE_H_
#define MULTIPLY 0 
#define NEGATE_MULTIPLY 1 
#define SUM  2
#define NEGATE_SUM 3
void evoluchine_randomize(char *operations,int operations_size, int *inputs_order, int input_size);
char evoluchine_eval(char *operations,int operations_size, char *input,int *input_order);
float evoluchine_batch_evaluate(char *operations,
                            int *inputs_order,
                            int operations_size ,
                            int inputs_size,
                            char *inputs,
                            char *ground_thruts,
                            int batch_size); 
void evoluchine_batch_solve(char *operations,
                            int *inputs_order,
                            int operations_size ,
                            int inputs_size,
                            char *inputs,
                            char *ground_thruts,
                            int batch_size,
                            int epochs);

#endif 
