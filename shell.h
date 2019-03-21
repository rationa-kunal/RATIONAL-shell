#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "color.h"
#include "parsing.h"
#include "history.h"
#include "remote_shell.h"
#include "custom_cmd.h"

#define MAX_CMD 1024
#define MAX_ARGS 32

void shell_loop(){
    // catch cmand line and parse it to argv
    char cmd_line[MAX_CMD];
    char *argv[MAX_ARGS];
    char delim =  ' ';

    int status = 0;

    while(status==0){
        bold("rational > ");

        // get line from cmd line
        char *line;
        fgets(cmd_line, sizeof(cmd_line), stdin);
        // seperate line from '\n'
        line = strtok(cmd_line, "\n");
        // parse line and store args in argv
        parse_with_space(line, argv);

        // check if command is custom command
        if(execute_custom_command(argv[0], argv)!=ERR) continue;
        // if not then execute it
        // add it to history
        add_cmd_to_index(line);

        // fork and execute command in child
        // wait for child
        int pid;
        pid = fork();
        if (pid == 0) { // parent process
            if (execvp(argv[0], argv) == -1) perror("lsh");
        } else { // child process
            wait(&status);
        }

    }
}