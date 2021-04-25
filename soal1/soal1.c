#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>
#include <dirent.h>

void makeDirectory()
{ 
  char *mkdir[] = {"mkdir", "-p", "Pyoto", "Musyik", "Fylm", NULL};
  execv("/bin/mkdir", mkdir);
}

void downloadMusyik()
{
  char *wget[] = {"wget" "--no-check-certificate" "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download" "-O" "Musyik_for_Stevany.zip", NULL};
  execv("/bin/wget", wget);
}

void downloadPyoto()
{
  char *wget1[] = {"wget" "--no-check-certificate" "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download" "-O" "Pyoto_for_Stevany.zip", NULL};
  execv("/bin/wget", wget1);
}

void downloadFylm()
{
  char *wget2[] = {"wget" "--no-check-certificate" "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download" "-O" "Fylm_for_Stevany.zip", NULL};
  execv("/bin/wget", wget2);
}

void unzipMusyik()
{
  char *unzip[] = {"unzip", "-q", "Musyik_for_Stevany.zip", "-d", "./Musyik", NULL};
  execv("/bin/unzip", unzip);
}

void unzipPyoto()
{
  char *unzip2[] = {"unzip", "-q", "Pyoto_for_Stevany", "-d", "./Pyoto", NULL};
  execv("/bin/unzip", unzip2);
}

void unzipFylm()
{
  char *unzip3[] = {"unzip", "-q", "Fylm_for_Stevany", "-d", "./Fylm", NULL};
  execv("/bin/unzip", unzip3);
}

void zip()
{
  char *zip[] = {"zip", "-q", "-r", "Lopyu_Stevany.zip", "Musyik", "Pyoto", "Fylm", NULL};
  execv("/bin/zip", zip);
}

void removeTheRest()
{
  char *rm[] = {"rm","-r","Fylm","Musyik","Pyoto","Photo_for_Stevany.zip","Music_for_Stevany.zip","Film_for_Stevany.zip", NULL};
  execv("/bin/rm", rm);
}

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

  if ((chdir("/home/hilmyhnf/modul2/soal1")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
		time_t t = time (NULL);
		struct tm *tmp = localtime(&t);
		if(tmp->tm_mon+1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 16 && tmp->tm_min == 22 && tmp->tm_sec == 0)
    {
		  pid_t child_id = fork();
		  if (child_id < 0) 
        exit(EXIT_FAILURE);
		  if (child_id == 0) 
        makeDirectory();
		  
      else 
      {
		    while((wait(&status))>0);
		    pid_t child_id2 = fork();
		    if (child_id2 < 0) 
          exit(EXIT_FAILURE);
		    if (child_id2 == 0) 
          downloadMusyik();
		    
        else 
        {
		      while((wait(&status))>0);
		      pid_t child_id3 = fork();
		      if (child_id3 < 0) 
            exit(EXIT_FAILURE);
		      if (child_id3 == 0) 
            downloadPyoto();
		      
          else 
          {
		        while((wait(&status))>0);
		        pid_t child_id4 = fork();
		        if (child_id4 < 0) 
              exit(EXIT_FAILURE);
		        if (child_id4 == 0) 
              downloadFylm();
		        
            else 
            {
		          while((wait(&status))>0);
		          pid_t child_id5 = fork();
		          if (child_id5 < 0) 
                exit(EXIT_FAILURE);
		          if (child_id5 == 0) 
                unzipMusyik();
		                                        
              else 
              {
		            while((wait(&status))>0);
		            pid_t child_id6 = fork();
		            if (child_id6 < 0) 
                  exit(EXIT_FAILURE);
		            if (child_id6 == 0) 
                  unzipPyoto();
  
                else 
                {
		              while((wait(&status))>0);
		              pid_t child_id7 = fork();
		              if (child_id7 < 0) 
                    exit(EXIT_FAILURE);
		              if (child_id7 == 0) 
                    unzipFylm();
		            }

		          }

		        }

		      }

		    }

		  }

		}

    else if(tmp->tm_mon+1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 22 && tmp->tm_min == 22 && tmp->tm_sec == 0)
    {
      pid_t child_id8 = fork();
		  if (child_id8 < 0) 
        exit(EXIT_FAILURE);
		  if (child_id8 == 0) 
        zip();

      else
      {
        while((wait(&status))>0);
        pid_t child_id9 = fork();
		    if (child_id9 < 0) 
         exit(EXIT_FAILURE);
		    if (child_id9 == 0) 
          removeTheRest();
      }

    }

		sleep(1);
	}

}
