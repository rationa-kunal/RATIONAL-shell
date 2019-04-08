
char *up = "HUP";
char *down = "HDOWN";
char *all = "HALL";
char *starts = "STARTS";
char *stops = "STOPS";

#define ERR -1
#define SUCC 1
int fd;

int execute_if_custom_command(struct command *cmd_l){
    // if else if statement to search for right cmd to execute
    // finally else if right cmd not found the return ERR
    char *cmd = cmd_l->argv[0];

    if (strcmp(cmd, starts)==0){
        danger("connecting\n");
        int pid, status;
        pid = fork();
        if (pid == 0) {
            printf("here\n");
            fd = remote_shell_connect(cmd_l->argv[1]);
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

int execute_history_command(char *cmd_start, char *cmd){
    if(strcmp(cmd_start, up)==0){
        get_cmd_frm_history(-1);
    } else if(strcmp(cmd_start, down)==0){
        get_cmd_frm_history(1);
    } else if(strcmp(cmd_start, all)==0){
        print_all();
    }

    else{
        add_cmd_to_index(cmd);
        return ERR;
    }

    return SUCC;
}