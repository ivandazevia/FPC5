#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void
rm_rf(char *path){
  //ambil dari ls yang print diganti unlink
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
      printf(2, "rm: cannot open %s\n", path);
      exit();
    }

    if(fstat(fd, &st) < 0){
      printf(2, "rm: cannot stat %s\n", path);
      close(fd);
      exit();
    }

    switch(st.type){
    case T_FILE:
      //printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
      if(unlink(path) < 0){
        printf(2, "rm: %s failed to delete\n", path);
        break;
      }
      break;

    case T_DIR:
      if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
        printf(1, "rm: path too long\n");
        break;
      }
      strcpy(buf, path);
      p = buf+strlen(buf);
      *p++ = '/';
      while(read(fd, &de, sizeof(de)) == sizeof(de)){
        // . dan .. di skip
        if(de.inum == 0||strcmp(de.name, ".")==0||strcmp(de.name,"..")==0)
          continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
          printf(1, "rm: cannot stat %s\n", buf);
          continue;
        }
        if(st.type == T_DIR) rm_rf(buf);
        //printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
        else if(unlink(buf) < 0){
          printf(2, "rm: %s failed to delete\n", buf);
        }
      }
      break;
    }
    close(fd);
    unlink(path);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    printf(2, "Usage: rm files...\n");
    exit();
  }


  if(argv[1][0]=='-' && argv[1][1]=='r' && argv[1][2]=='f'){
    rm_rf(argv[2]);
  }

  else{ //untuk banyak file terpilih
    for(i = 1; i < argc; i++){
      if(unlink(argv[i]) < 0){
        printf(2, "rm: %s failed to delete\n", argv[i]);
        break;
      }
    }
  }
  exit();
}