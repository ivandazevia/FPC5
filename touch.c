#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h" 

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf(2, "File not specified\n");
    exit();
  }
  else{
    int touch;
    touch=open(argv[1],O_CREATE|O_RDWR);
    close(touch);
    exit();
  }

  exit();
}
