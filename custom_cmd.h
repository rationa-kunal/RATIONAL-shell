
char *up = "HUP";
char *down = "HDOWN";
char *all = "HALL";
char *starts = "STARTS";
char *stops = "STOPS";

#define ERR -1
int fd;

int execute_custom_command(char *cmd, char *argv[]){
    if(strcmp(cmd, up)==0){
        get_cmd_frm_history(-1);
        return 1;
    } else if(strcmp(cmd, down)==0){
        get_cmd_frm_history(1);
        return 1;
    } else if(strcmp(cmd, all)==0){
        print_all();
        return 1;
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

    return ERR;
}