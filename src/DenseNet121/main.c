#include <stdio.h>
#include "model/samples/car.c"
#include "model/samples/catan.c"
#include "model/codegen/host/include/tvmgen_default.h"

uint8_t output1[2];
uint8_t output2[2];

int main(void){

    struct tvmgen_default_inputs inputs = {
            .serving_default_input_2_0 = (void*)&CAR_IMAGE,
    };
    struct tvmgen_default_outputs outputs1 = {
            .StatefulPartitionedCall_0 = (void*)&output1,
    };
    
    struct tvmgen_default_outputs outputs2 = {
            .StatefulPartitionedCall_0 = (void*)&output2,
    };

    printf("Evaluating DenseNet121 model using microTVM:\n");

    inputs.serving_default_input_2_0 = (void*)&CAR_IMAGE;
    tvmgen_default_run(&inputs, &outputs1);
    printf("Car Result: random = %d, car = %d\n", output1[0], output1[1]);
    
    inputs.serving_default_input_2_0 = (void*)&CATAN_IMAGE;
    tvmgen_default_run(&inputs, &outputs2);
    printf("Random Result: random = %d, car = %d\n", output2[0], output2[1]);
    
    return 0;
}
