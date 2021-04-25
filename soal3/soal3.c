#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void encrypt(char folder[]){
   FILE *fp;
   char txtpath[40];
   snprintf(txtpath,sizeof txtpath,"./%s/status.txt",folder);
   fp  = fopen (txtpath, "w");
   int key=5;
   //caesar cipher algorithm
   char message[]="Download Success", ch;
   for(int i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			message[i] = ch;
		}
	}
   //write to txt
   printf("Download Success = %s\n",message);
   for (int i = 0;i<16; i++) 
      fputc(message[i], fp);
   fclose(fp);
}

int main(char *argv[]) {

  char image[30],imagepath[100],link[50];
  char timestamp[20];
  char d[100] = {"/home/asusry/Documents/"};
  int status;

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
    
    
    
    snprintf(timestamp, sizeof timestamp,"%02d-%02d-%02d_%02d:%02d:%02d",w.tm_mday, w.tm_mon + 1, w.tm_year + 1900, w.tm_hour, w.tm_min, w.tm_sec);
    
    //make the folder
    pid_t child1,child2,child3;
      child1=fork();
      if(child1 == 0){
         child2=fork();
         if(child2==0){
            char *argvmk[] = {"mkdir", "-p", timestamp, NULL};
            execv("/bin/mkdir",argvmk);
         }
         else{
            while ((wait(&status)) > 0);

            // download image
            for(int i=0;i<10;i++){
               if(fork()==0){
                  printf("Duar\n");
                  //epoch time
                  int epoch = (int)time(NULL);
                  epoch = (epoch % 1000)+50;
                  //update present time in every loop
                  time_t t = time(NULL);
                  struct tm w = *localtime(&t);

                  //image naming
                  snprintf(image,sizeof image,"%02d-%02d-%02d_%02d:%02d:%02d.jpg",w.tm_mday, w.tm_mon + 1, w.tm_year + 1900, w.tm_hour, w.tm_min, w.tm_sec);
                  snprintf(imagepath,sizeof imagepath, "./%s/%s",timestamp,image); 
                  snprintf(link,sizeof link,"https://picsum.photos/%d.jpg",epoch);
                  
                  execl("/usr/bin/wget", "wget", "-q","-O",imagepath, link,"", NULL);
               }
               sleep(5);
            }
            encrypt(timestamp);
            //zip file
            char zipfile[40];
            snprintf(zipfile,sizeof zipfile,"%s.zip",timestamp);
            execl("/usr/bin/zip","zip","-rm",zipfile,timestamp,"-x","*.c",NULL);
         }
      }

    //loop with interval 40s
    sleep(40);
  };
}
