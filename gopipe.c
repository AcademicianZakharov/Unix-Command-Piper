/* gopipe.c
 *
 * Author: Gabriel Maryshev
 */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#define MAX_INPUT_LINE 80

void pipe4(char **cmd_1, char** cmd_2, char** cmd_3, char** cmd_4){
    int status;
    int pid_1, pid_2, pid_3, pid_4;
    int fd_1[2], fd_2[2], fd_3[2];

    (void)pipe(fd_1); 
    (void)pipe(fd_2);
    (void)pipe(fd_3);
    //4 forks and execvps for 4 commands
    if ((pid_1 = fork()) == 0) {
        (void)dup2(fd_1[1], 1);
        (void)close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);
        (void)execvp(cmd_1[0], cmd_1);
    }

    if ((pid_2 = fork()) == 0) {
        (void)dup2(fd_1[0], 0);
        (void)dup2(fd_2[1], 1);
        close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);
        (void)execvp(cmd_2[0], cmd_2);
    }

    if ((pid_3 = fork()) == 0) {
        (void)dup2(fd_2[0], 0);
        (void)dup2(fd_3[1], 1);
        close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);
        (void)execvp(cmd_3[0], cmd_3);
    }

    if ((pid_4 = fork()) == 0) {
        (void)dup2(fd_3[0], 0);
        close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);
        (void)execvp(cmd_4[0], cmd_4);
    }

    close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);

    (void)waitpid(pid_1, &status, 0);
    (void)waitpid(pid_2, &status, 0);
    (void)waitpid(pid_3, &status, 0);
    (void)waitpid(pid_4, &status, 0);
}

void pipe3(char** cmd_1, char** cmd_2, char** cmd_3){
    int status;
    int pid_1, pid_2, pid_3;
    int fd_1[2], fd_2[2], fd_3[2];

    (void)pipe(fd_1);
    (void)pipe(fd_2);
    (void)pipe(fd_3);

    if ((pid_1 = fork()) == 0) {
        (void)dup2(fd_1[1], 1);
        close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);
        (void)execvp(cmd_1[0], cmd_1);
    }

    if ((pid_2 = fork()) == 0) {
        (void)dup2(fd_1[0], 0);
        (void)dup2(fd_2[1], 1);
        close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);
        (void)execvp(cmd_2[0], cmd_2);
    }

    if ((pid_3 = fork()) == 0) {
        (void)dup2(fd_2[0], 0);
        close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);
        (void)execvp(cmd_3[0], cmd_3);
    }

    close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);

    (void)waitpid(pid_1, &status, 0);
    (void)waitpid(pid_2, &status, 0);
    (void)waitpid(pid_3, &status, 0);

}

void pipe2(char** cmd_1, char** cmd_2){
    int status;
    int pid_1, pid_2;
    int fd_1[2], fd_2[2], fd_3[2];

    (void)pipe(fd_1);
    (void)pipe(fd_2);
    (void)pipe(fd_3);

    if ((pid_1 = fork()) == 0) {
        (void)dup2(fd_1[1], 1);
        close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]); close(fd_3[0]); close(fd_3[1]);
        (void)execvp(cmd_1[0], cmd_1);
    }

    if ((pid_2 = fork()) == 0) {
        (void)dup2(fd_1[0], 0);
        close(fd_1[0]); close(fd_1[1]); close(fd_2[0]); close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);
        (void)execvp(cmd_2[0], cmd_2);
    }

    close(fd_1[0]);close(fd_1[1]);close(fd_2[0]);close(fd_2[1]);close(fd_3[0]);close(fd_3[1]);

    (void)waitpid(pid_1, &status, 0);
    (void)waitpid(pid_2, &status, 0);    
}

void pipe1(char** cmd_1){
    (void)execvp(cmd_1[0], cmd_1);    
}

int main() {
    char input[4][MAX_INPUT_LINE];
    int usedLines = 0;
    //read the input
    //here chatgpt helped me fix null characters
    for (int l = 0; l < 4; l++) {
        ssize_t bytesRead = read(0, input[l], sizeof(input[l]));
        if (bytesRead <= 0) {
            break;
        }
        int lineLength = bytesRead / sizeof(char);
        int writeIndex = 0;
        for (int i = 0; i < lineLength; i++) {
            if (input[l][i] != '\0') {
                input[l][writeIndex++] = input[l][i];
            }
            if (input[l][i] == '\n') {
                input[l][i] = '\0';
            }
        }
        input[l][writeIndex] = '\0';
        if (input[l][0] == '\n') {
            break;
        }
        if(bytesRead == 1) {
            break;
        }
        usedLines++;
    }
    //end of some code from chatgpt
    //tokenize the input most code from appendix d
    char *token[MAX_NUM_TOKENS];
    char *t;
    int  num_tokens;

    char *tknarray[50][50];
    for(int j = 0; j < usedLines; j++){
        num_tokens = 0;
        t = strtok(input[j], " ");
        while (t != NULL && num_tokens < MAX_NUM_TOKENS) {
            token[num_tokens] = t;
            num_tokens++;
            t = strtok(NULL, " ");
        }
        for (int w = 0; w < num_tokens; w++) {
            tknarray[w][j] = token[w];
        }
        
    }
    char *cmd_1[] = { tknarray[0][0], tknarray[1][0], tknarray[2][0], tknarray[3][0], tknarray[4][0] ,tknarray[5][0] ,tknarray[6][0] ,tknarray[7][0], tknarray[8][0], NULL};//used appendix c
    char *cmd_2[] = { tknarray[0][1], tknarray[1][1], tknarray[2][1], tknarray[3][1], tknarray[4][1] ,tknarray[5][1] ,tknarray[6][1] ,tknarray[7][1], tknarray[8][1], NULL};//used appendix c
    char *cmd_3[] = { tknarray[0][2], tknarray[1][2], tknarray[2][2], tknarray[3][2], tknarray[4][2] ,tknarray[5][2] ,tknarray[6][2] ,tknarray[7][2], tknarray[8][2], NULL};//used appendix c
    char *cmd_4[] = { tknarray[0][3], tknarray[1][3], tknarray[2][3], tknarray[3][3], tknarray[4][3] ,tknarray[5][3] ,tknarray[6][3] ,tknarray[7][3], tknarray[8][3], NULL};//used appendix c
    
    //pipe input depending on number of lines entered
    if(usedLines == 4){
        pipe4(cmd_1, cmd_2, cmd_3, cmd_4);
   }
    else if(usedLines == 3){
        pipe3(cmd_1, cmd_2, cmd_3);
   }
    else if(usedLines == 2){
        pipe2(cmd_1, cmd_2);
   }
    else if(usedLines == 1){
        pipe1(cmd_1);
   }
    return EXIT_SUCCESS;
}
