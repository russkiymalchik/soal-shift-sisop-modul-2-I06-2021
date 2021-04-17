#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>

int main(){
    pid_t child_id, child_id1, child_id2, child_id3,child_id4,child_id5, child_id6,child_id7;
    int status,status1,status2,status3,status4,status5,status6,status7;
    
    //2A
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

            child_id2 = fork();

            if (child_id2 == 0) {
                char *argv[] = {"unzip", "Downloads/pets.zip","-d", "/home/juancarlos/temp", NULL};
                execv("/usr/bin/unzip", argv);
            }
            else {
                while ((wait(&status2)) > 0); 
                
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

                        //2B
                        DIR *dir1;
                        struct dirent *pic1;
                        dir1 = opendir("/home/juancarlos/modul2/petshop");
                        
                        while ((pic1 = readdir(dir1)) != NULL) {
                            if((pic1->d_type == DT_REG) && strcmp(pic1->d_name, ".") != 0 && strcmp(pic1->d_name, "..") != 0) {
                                char path1[100] = "";
                                strcpy(path1, pic1->d_name);
                                char directname [100] = "/home/juancarlos/modul2/petshop/";
                                strtok (path1, ";" );
                                strcat(directname, path1);

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

                                    //2C
                                    
                                }
                            }
                        }
                        (void) closedir (dir1);
                    }
                }
            }
        }
    }
    return 0;
}
