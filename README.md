# soal-shift-sisop-modul-2-I06-2021
## Group Member Name:
1. Khairi Wiryawan                      (05111942000023)
2. Juan Carlos Tepanus Pardosi          (05111942000017)
3. Hilmy Hanif Ibrahim					(05111942000005)

## Problem 1
Once upon a time, there was a steven who lived a mediocre live. Steven had a girlfriend, but they have broken up before getting together. When he was thinking about his ex, he always watches https://www.youtube.com/watch?v=568DH_9CMKI to relieve his sadness. 

In the meantime, Steven hates SISOP Course very much like no other, Few hours after breaking up with his girlfriend, he found another  woman named Stevany, but Stevany is the opposite of him because she likes SISOP course very much. Steven wanted to look good at SISOP course to impress her.

On her birthday, he wanted to give her a zip file containing all things that she likes. He wanted the zip to be organized by making a new folder for each file extension.

### a
Because she likes the letter Y so much, He wanted the name of the folder as Musyik for mp3, Fylm for mp4, and Pyoto for jpg.

### b
For music, he downloads it from the link below, so are the cases for films and photos.


### c
he didn’t want the folder to contain the zip files so he extracts the files first after downloading it.

### d
moving it to the folder that has been made (only the files).

### e
When it’s her birthday, all folder will be zipped with the name Lopyu_Stevany.zip and all the folders will be deleted. (Only the zip remains).

### f
To make his life easier, he wants all of the above to run automatically 6 hours before her birthday (except for point e of course)

### Note :
- Stevany’s birthday : 09 April Pukul 22.22 WIB
- All points are run by 1 script on the background, that includes downloading the zip file. So you just need to run 1 script and change the time and date to check the result.

## Problem 2
## Problem 3
Ranora is an Informatics Engineering student who is currently undergoing an internship at a well-known company called "FakeKos Corp.", a company engaged in data security. Because Ranora is still an apprentice, the workload is not as big as the workload of the company's permanent workers. On Ranora's first day of work, Ranora's apprentice tutor gave her the task of making a program.

#### a
Ranora must create a C program which every 40 seconds creates a directory with a name according to the timestamp [YYYY-mm-dd_HH:ii:ss].

#### b
Each directory is filled with 10 images downloaded from https://picsum.photos/, where each image will be downloaded every 5 seconds. Each downloaded image will be named with a timestamp format [YYYY-mm-dd_HH:ii:ss] and the image is square with the size (n% 1000) + 50 pixels where n is the Unix Epoch time.

#### c
After the directory has been filled with 10 images, the program will create a file "status.txt", which contains the message "Download Success" which is encrypted with the Caesar Cipher technique and with shift 5. Caesar Cipher is a simple encryption technique which can perform encryption. string according to the shift / key that we specify. For example, the letter "A" will be encrypted with shift 4 it will become "E". Because Ranora is a perfectionist and neat person, he wants after the file is created, the directory will be zipped and the directory will be deleted, leaving only the zip file.

#### d
To make it easier to control the program, the Ranora apprentice supervisor wants the program to produce an executable "Killer" program, where the program will terminate all running program processes and will run itself after the program is run. Because Ranora is interested in something new, Ranora has an idea for the "Killer" program that was made, it must be a bash program.

#### e
The Ranora apprentice supervisor also wants the main program created by Ranora to run in two modes. To activate the first mode, the program must be executed with the -z argument, and when it is executed in the first mode, the main program will immediately execute all its operations when the Killer program is run. Meanwhile, to activate the second mode, the program must be run with the -x argument, and when run in the second mode, the main program will stop allowing the processes in each directory that are still running until it is finished (The directory that has been created will download the image to completion and create a txt file, then zip and delete the directory).

### Answer
```
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
```
