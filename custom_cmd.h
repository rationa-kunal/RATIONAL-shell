
char *up = "HUP";
char *down = "HDOWN";
char *all = "HALL";
char *starts = "STARTS";
char *stops = "STOPS";

#define ERR -1
#define SUCC 1
int fd;

int execute_if_custom_command(char *cmd, char *argv[]){
    // if else if statement to search for right cmd to execute
    // finally else if right cmd not found the return ERR

    if(strcmp(cmd, up)==0){
        get_cmd_frm_history(-1);
    } else if(strcmp(cmd, down)==0){
        get_cmd_frm_history(1);
    } else if(strcmp(cmd, all)==0){
        print_all();
    } else if (strcmp(cmd, starts)==0){
        danger("connecting\n");
        int pid, status;
        pid = fork();
        if (pid == 0) {
            fd = remote_shell_connect(argv[1]);
        } else {
            wait(&status);
        }
    } else if (strcmp(cmd, stops)==0){
        danger("stoping server\n");
        remote_shell_stop(fd);
    }

    else{
        return ERR;
    }

    return SUCC;
}