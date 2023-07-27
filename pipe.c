/* pipe.c
 *
 * Author: Gabriel Maryshev
 */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#define MAX_INPUT_LINE 80
#define MAX_COMMANDS 50
#define MAX_TOKENS 50

void execPipe(char*** cmds, int n) {
    int i;
    int in = 0;
    int fd[2];
    int status;

    for (i = 0; i < n - 1; ++i) {
        pipe(fd);
        if (fork() == 0) {
            dup2(in, 0);
            dup2(fd[1], 1);
            close(fd[0]);
            execvp(cmds[i][0], cmds[i]);
            exit(EXIT_FAILURE);
        }
        else {
            wait(&status);
            close(fd[1]);
            in = fd[0];
        }
    }

    if (fork() == 0) {
        dup2(in, 0);
        execvp(cmds[i][0], cmds[i]);
    }
    else {
        wait(&status);
    }
}

int main() {
    char input[MAX_COMMANDS][MAX_INPUT_LINE];
    int usedLines = 0;

    //read the input
    for (int l = 0; l < MAX_COMMANDS; l++) {
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

    char *token[MAX_TOKENS];
    char *t;
    int  num_tokens;
    char ***cmds = malloc(usedLines * sizeof(char**));

    for(int j = 0; j < usedLines; j++){
        num_tokens = 0;
        t = strtok(input[j], " ");
        while (t != NULL && num_tokens < MAX_TOKENS) {
            token[num_tokens] = t;
            num_tokens++;
            t = strtok(NULL, " ");
        }

        cmds[j] = malloc((num_tokens + 1) * sizeof(char*));
        for (int w = 0; w < num_tokens; w++) {
            cmds[j][w] = token[w];
        }
        cmds[j][num_tokens] = NULL;
    }

    //execute pipe
    execPipe(cmds, usedLines);

    //free memory
    for(int j = 0; j < usedLines; j++){
        free(cmds[j]);
    }
    free(cmds);

    return EXIT_SUCCESS;
}
