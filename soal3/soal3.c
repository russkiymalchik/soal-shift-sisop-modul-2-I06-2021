#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>


int main(char *argv[]) {

  pid_t pid, sid;

  pid = fork();  
  

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }


  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }
  

  umask(0);
  

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }


  if ((chdir("/home/asusry/soal3shift2/")) < 0) {
    exit(EXIT_FAILURE);
  }
  

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  

  while (1) {    
   
    //get timestamp
    time_t t = time(NULL);
    struct tm w = *localtime(&t);
    
    char timestamp[100];
    char d[100] = {"/home/asusry/Documents/"};
    
    sprintf(timestamp,"%02d-%02d-%02d_%02d:%02d:%02d",w.tm_mday, w.tm_mon + 1, w.tm_year + 1900, w.tm_hour, w.tm_min, w.tm_sec);
    
    //make a directory with current timestamp name
    mkdir(timestamp,0777);

    //change directory into newly created
    strcat(d,timestamp);
    chdir(d);

    //loop with interval 30s
    sleep(40);
  };
}
