
#define MAX_HISTORY 256

char *history[MAX_HISTORY];

int present_cmd = 0;
int past_cmd = 0;

void get_cmd_frm_history(int step){
    int _past_cmd = past_cmd + step;
    if(_past_cmd < 0) {
        danger("NO HISTORY\n");
        return;
    }else if(_past_cmd == present_cmd){
        danger("INVALID\n");
        return;
    }
    past_cmd += step;
    printf("%d %s\n", past_cmd, history[past_cmd]);
}

void add_cmd_to_index(char *cmd){
    char * _cmd = (char *) malloc(sizeof(cmd));
    strcpy(_cmd, cmd);
    if(present_cmd==MAX_HISTORY) {
        danger("HISTRORY FULL CANT SAVE\n");
    }
    history[present_cmd] = _cmd;

    present_cmd ++;
    past_cmd = present_cmd;
}

void print_all(){
    printf("\n");
    for(int i=0; i<present_cmd; i++) printf("%d %s\n", i, history[i]);
    printf("\n");
}
