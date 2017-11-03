#include "stats.h"

int main(){

  struct stat s_buff;
  stat("stats.c",&s_buff);
  long fSize = s_buff.st_size;
  int mode = s_buff.st_mode % 01000;

  printf("file size: %ld\n", fSize);//print file size
  printf("file mode: %o\n", mode);//print mode (permissions)
  printf("file time: %s\n", ctime(&s_buff.st_atime)); //print time of last access

  //modify size display
  char sDisplay[50] = {0};
  while( fSize ){
    if( fSize >= 1000000000){
      sprintf(sDisplay,"%ld GB ",fSize/1000000000);
      fSize %= 1000000000;
    }
    if( fSize >= 1000000){
      sprintf(sDisplay,"%ld MB ",fSize/1000000);
      fSize %= 1000000;
    }
    else if( fSize >= 1000){
      sprintf(sDisplay,"%s%ld KB ", sDisplay, fSize/1000);
      fSize %= 1000;
    }
    else{
      sprintf(sDisplay,"%s%ld B", sDisplay, fSize);
      fSize = 0;
    }
    //printf("fSize: %ld\n", fSize);
  }
  printf("file size formatted: %s\n",sDisplay);

  //print in ls -l form
  char lsMode[50];
  int i;
  
  for(i=3; i>0; i--){
    //printf("%o\n",mode);
    if( mode >= 0100 ){
      sprintf(lsMode, "%s", permission(mode / 0100));
      mode %= 0100;
    }
    else if( mode >= 010 ){
      sprintf(lsMode, "%s%s", lsMode, permission(mode / 010));
      mode %= 010;
    }
    else sprintf(lsMode, "%s%s", lsMode, permission(mode));
  }
  printf("ls -l format: %s\n",lsMode);
  
}

char * permission(int n){
  if( n == 0 ) return "---";
  if( n == 1 ) return "--x";
  if( n == 2 ) return "-w-";
  if( n == 3 ) return "-wx";
  if( n == 4 ) return "r--";
  if( n == 5 ) return "r-x";
  if( n == 6 ) return "rw-";
  if( n == 7 ) return "rwx";
}
