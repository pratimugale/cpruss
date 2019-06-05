#include "cpruss.h"

int main(){

    start(1);
    char temp[48] = "/tmp/pru0-gen/hello.out";
    load_firmware(temp, 0);
    return 0;
}
