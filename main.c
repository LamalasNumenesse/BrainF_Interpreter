# include <stdio.h>
# include <string.h>
# include "Helper.h"

int main(int argc, char* argv[]){
    if (argc == 2){
        const char* ext = strrchr(argv[1], '.');
        if (strcmp(ext, ".bf") == 0) {
            struct Array* BF_Array = Create_arraY(30000);
            struct Queue* Instructions = Create_queuE();
            Read_filE(Instructions, argv[1]);
            Execute_orderS(BF_Array, Instructions);
            Destroy_queuE(Instructions);
            Destroy_arraY(BF_Array);
            printf("\n");
        }else{
            printf("Sorry, we don't support %s file format. Please make sure the file is a .bf file.\n", ext);
        }
    }else{
        printf("Missing File argument. Pleasy try ./BFC [File].bf\n");
    }
    return 0;
}