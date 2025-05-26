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

    if(output1[0] < 50 && output1[1] > 200) {
        asm volatile ("lui x25, 0xBA55");
        asm volatile ( "li x26, 0xBA");
        asm volatile ( "or x25, x25, x26");
    } else {
        asm volatile ("lui x25, 0xDEAD");
        asm volatile ( "li x26, 0xBE");
        asm volatile ( "or x25, x25, x26");
    }

    if(output2[1] < 50 && output2[0] > 200) {
        asm volatile ("lui x26, 0xBA55");
        asm volatile ( "li x27, 0xBA");
        asm volatile ( "or x26, x26, x27");
    } else {
        asm volatile ("lui x26, 0xDEAD");
        asm volatile ( "li x27, 0xBE");
        asm volatile ( "or x26, x26, x27");
    }
    
    return 0;
}
