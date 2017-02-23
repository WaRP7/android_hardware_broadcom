#include <stdio.h>
#include "BtCtl.h"
#include "log.h"
#include <stdlib.h>
#define MAGIC_STRING "51872307"

using namespace android;

int main(int argc, char* argv[])
{
    if (argc!=3) 
        LOGI("please use: command 0|1, here 0 disable, 1 enable"); 
    if (atoi(argv[2])==atoi(MAGIC_STRING)) {
        BtCtl objBtCtl;
        int ret = objBtCtl.setN(atoi(argv[1]));
        printf("test setN %d return=%d\n", (atoi(argv[1])), ret);
    }
    return 0;
}
