#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini
    pid_t child_id;

    time_t t = time(NULL);
    struct tm*w = localtime(&t);
    
    char timestamp[100];
    
    strftime (timestamp, 100, "%Y-%m-%d_%H:%M:%S", w);

    child_id=fork();
    
    if (child_id==0){
    char *arg[]= {"mkdir", timestamp, NULL};
    execv("/bin/mkdir", arg);
    }

    if (child_id<0){
      exit(0);
    }
    sleep(40);
  }
}
