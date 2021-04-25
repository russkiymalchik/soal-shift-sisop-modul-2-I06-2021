# soal-shift-sisop-modul-2-I06-2021
## Group Member Name:
1. Hilmy Hanif Ibrahim                  (05111942000005)
2. Juan Carlos Tepanus Pardosi          (05111942000017)
3. Khairi Wiryawan    				          (05111942000023)

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
#include <wait.h>
#include <time.h>
#include <dirent.h>

int status;

//sudo date --set="2021-04-09 16:21:59"
//sudo date --set="2021-04-09 22:21:59"

void makeDirectory()
{
  char *mkdir[] = {"mkdir", "-p", "Pyoto", "Musyik", "Fylm", NULL};
  execv("/bin/mkdir", mkdir);
}

void downloadMusyik()
{
  char *wget1[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musyik_for_Stevany.zip", NULL};
  execv("/bin/wget", wget1);
}

void downloadPyoto()
{
  char *wget2[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Pyoto_for_Stevany.zip", NULL};
  execv("/bin/wget", wget2);
}

void downloadFylm()
{
  char *wget3[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Fylm_for_Stevany.zip", NULL};
  execv("/bin/wget", wget3);
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
  char *rm[] = {"rm", "-r", "Fylm", "Musyik", "Pyoto", "Pyoto_for_Stevany.zip", "Musyik_for_Stevany.zip", "Fylm_for_Stevany.zip", NULL};
  execv("/bin/rm", rm);
}

int main()
{
  pid_t pid, sid;

  pid = fork();

  if (pid < 0)
  {
    exit(EXIT_FAILURE);
  }

  if (pid > 0)
  {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0)
  {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/hilmyhnf/modul2/soal1")) < 0)
  {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1)
  {
    time_t t = time(NULL);
    struct tm *tmp = localtime(&t);
    if (tmp->tm_mon + 1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 16 && tmp->tm_min == 22 && tmp->tm_sec == 0)
    {
      pid_t child_id = fork();
      if (child_id < 0)
        exit(EXIT_FAILURE);
      if (child_id == 0)
        makeDirectory();

      else
      {
        while ((wait(&status)) > 0);
        pid_t child_id2 = fork();
        if (child_id2 < 0)
          exit(EXIT_FAILURE);
        if (child_id2 == 0)
          downloadMusyik();

        else
        {
          while ((wait(&status)) > 0);
          pid_t child_id3 = fork();
          if (child_id3 < 0)
            exit(EXIT_FAILURE);
          if (child_id3 == 0)
            downloadPyoto();

          else
          {
            while ((wait(&status)) > 0);
            pid_t child_id4 = fork();
            if (child_id4 < 0)
              exit(EXIT_FAILURE);
            if (child_id4 == 0)
              downloadFylm();

            else
            {
              while ((wait(&status)) > 0);
              pid_t child_id5 = fork();
              if (child_id5 < 0)
                exit(EXIT_FAILURE);
              if (child_id5 == 0)
                unzipMusyik();

              else
              {
                while ((wait(&status)) > 0);
                pid_t child_id6 = fork();
                if (child_id6 < 0)
                  exit(EXIT_FAILURE);
                if (child_id6 == 0)
                  unzipPyoto();

                else
                {
                  while ((wait(&status)) > 0);
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

    else if (tmp->tm_mon + 1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 22 && tmp->tm_min == 22 && tmp->tm_sec == 0)
    {
      pid_t child_id8 = fork();
      if (child_id8 < 0)
        exit(EXIT_FAILURE);
      if (child_id8 == 0)
        zip();

      else
      {
        while ((wait(&status)) > 0);
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
```

## Problem 2

Loba works in a famous pet shop, one day he got a zip containing lots of pets photos and he was ordered to categorize the photos of these pets. Loba finds it difficult to do his work manually, moreover there is the possibility that he will be ordered to do the same thing multiple times. You are Loba's best friend and he is asking for your help to help with his work.

### 2a
First, the program needs to extract the given zip into the folder “/home/[user]/modul2/petshop”. Because Loba's boss is careless, the zip may contain unimportant folders, so the program must be able to distinguish between files and folders so that it can process files that should be worked on and delete unnecessary folders.

### Problem Solving

First, make two directory to store the data, in this case we use temp and petshop.

```

    child_id = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE);
    }

    if (child_id == 0) {
        char *argv[] = {"mkdir", "-p","/home/juancarlos/temp", NULL};
        execv("/usr/bin/mkdir", argv);
    }
    else {
        while ((wait(&status)) > 0); 
    
        child_id1 = fork();

        if (child_id1 == 0) {
            char *argv[] = {"mkdir", "-p","/home/juancarlos/modul2/petshop", NULL};
            execv("/usr/bin/mkdir", argv);
        }
        else {
            while ((wait(&status1)) > 0);
            
```

After that, unzip the given data in Downloads/pets.zip into temp directory.

```

            child_id2 = fork();

            if (child_id2 == 0) {
                char *argv[] = {"unzip", "Downloads/pets.zip","-d", "/home/juancarlos/temp", NULL};
                execv("/usr/bin/unzip", argv);
            }
            else {
                while ((wait(&status2)) > 0); 
                
```

Separate file from unimportant folder using DT_REG, and move the file into petshop directory.

```

                child_id3 = fork();

                if (child_id3 == 0) {
                    struct dirent *pic;
                    DIR *dir = opendir ("/home/juancarlos/temp");

                    if (dir == NULL){
                        return 0;
                    }

                    while ((pic = readdir(dir)) != NULL) {
                        if(pic->d_type == DT_REG){
                            child_id4 = fork();
                            if (child_id4 == 0){
                                char path[500];
                                sprintf(path, "/home/juancarlos/temp/%s", pic->d_name);
                                char *argv[] = {"mv", path, "/home/juancarlos/modul2/petshop", NULL};
                                execv("/usr/bin/mv", argv);
                            }
                            while ((wait(&status4)) > 0); 
                        }
                    }
                (void) closedir (dir);
                }
                else {
                    while ((wait(&status3)) > 0);
                    
```

Last step, remove temp directory with its unimportant folder inside.

```

                    child_id5 = fork();

                    if (child_id5 < 0) {
                        exit(EXIT_FAILURE);
                    }

                    if (child_id5 == 0) {
                        char *argv[] = {"rm","-r", "/home/juancarlos/temp", NULL};
                        execv("/usr/bin/rm", argv);
                    }
                    else {
                        while ((wait(&status5)) > 0);

```

Below is the result of 2a

![alt text](https://github.com/russkiymalchik/soal-shift-sisop-modul-2-I06-2021/blob/main/screenshots/result2a.png)

### 2b
Pet photos need to be categorized based on the pet's species, so you will need to create a folder for each species that is in the zip file. Since you can't possibly check manually, the program needs to create the required folders according to the contents of the zip file.
Example: Cats will be stored in "/petshop/cat", turtles will be stored in "/petshop/turtle".

### Problem Solving

First, read the petshop directory in our device.

```
                        DIR *dir1;
                        struct dirent *pic1;
                        dir1 = opendir("/home/juancarlos/modul2/petshop");

```

The foler will be named according to pet type. So, for the solution the program only read the file name until it meets ";". 

```

                        while ((pic1 = readdir(dir1)) != NULL) {
                            if((pic1->d_type == DT_REG) && strcmp(pic1->d_name, ".") != 0 && strcmp(pic1->d_name, "..") != 0) {
                                char path1[100] = "";
                                strcpy(path1, pic1->d_name);
                                char directname [100] = "/home/juancarlos/modul2/petshop/";
                                strtok (path1, ";" );
                                strcat(directname, path1);

```
Use mkdir to make the folder according to its type and place the folder inside petshop directory.

```

                                child_id6 = fork();

                                if (child_id6 < 0) {
                                    exit(EXIT_FAILURE);
                                }
                        
                                if (child_id6 == 0) {
                                    char *argv[] = {"mkdir", "-p",directname, "/home/juancarlos/modul2/petshop", NULL};
                                    execv("/usr/bin/mkdir", argv);
                                }
                                else {
                                    while ((wait(&status6)) > 0);

```

Below is the result of 2b

![alt text](https://github.com/russkiymalchik/soal-shift-sisop-modul-2-I06-2021/blob/main/screenshots/result2b.png)

### 2c
After the folders are created, your program should move the photos to the folder based on their respective species and rename the photo with the pet's name.
Example: "/petshop/cat/joni.jpg"

### 2d
Because 1 photo may have more than 1 pet in it, photos must be moved to each corresponding category.
Example: photo with the name "dog;baro;1_cat;joni;2.jpg" is moved to the folder "/petshop/cat/joni.jpg" and "/petshop/dog/baro.jpg"

### 2e
In each folder, create a file "keterangan.txt" that contains names and ages of all the pets in the folder.

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
First, we need to get the Daemon template from modul that has been taught to us and changing the value inside sleep into 40
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

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
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

    sleep(40);
  }
}
```
Answering 3a. we need to get the current time. after getting the current time, we put it as string as a directory name that we are creating.
```
char timestamp[20];

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
```
By doing so, number 3a is answered.

For 3b, we need to download 10 picture each 5 seconds and with certain pixel. to do so, we certainly need a looping for 10 times for downloading 10 pictures. next, we set the epoch time, present time, and set the naming based on the time that the image being downloaded. after that, before ending each loop, we need to make sleep(5) in order to give gap 5 seconds each loop.
```
// download image
            for(int i=0;i<10;i++){
               if(fork()==0){
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
```

Answering 3c, we need to create txt everytime the downloading process finish. inside of the txt is a sentence "Download Success". but, the sentence need to be configured as Caesar cipher encryption shift 5. after that, we need to zip all the entire folder/directory

here is a void for the encryption. that will be called later.
```
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
```

next, after 3a and 3b process done, we can continue by calling the void encrypt and also make it into zip.
```
encrypt(timestamp);
            //zip file
            char zipfile[40];
            snprintf(zipfile,sizeof zipfile,"%s.zip",timestamp);
            execl("/usr/bin/zip","zip","-rm",zipfile,timestamp,"-x","*.c",NULL);
```

and the result is

![alt text](https://github.com/russkiymalchik/soal-shift-sisop-modul-2-I06-2021/blob/main/screenshots/soal3shift2.jpg)
