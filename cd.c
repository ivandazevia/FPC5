#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main (int argc, char *argv[]){

	if(argc<2){
		printf(2,"Input not specified\n");
		exit();
	}
    if(chdir(argv[1])<0){
        printf(2,"folder name uncorrect\n");
    }
    else {
        printf(1,"succeed\n");
    }
	exit();
}
