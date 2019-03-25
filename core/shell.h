#define MAX_CMD 1024
#define MAX_ARGS 32

void shell_loop(){
    // catch cmand line and parse it to argv
    char cmd_line[MAX_CMD];
    char *std_argv[MAX_ARGS];
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
        struct queue *seq_q = parse_with_semicolan(line);

        int pid;
        pid = fork();
        if(pid==0){
            status = execute_seq_q(seq_q);    
        }else {
            wait(&status);
        }
        // execute command
        //status = execute_seq_q(seq_q);
    }
}