#define MAX_CMD 1024
#define MAX_ARGS 32

void shell_loop(){

    char cmd_line[MAX_CMD];
    int status = 0;

    while(status==0){
        
        // start new command catching
        bold("rational > ");

        // get line from cmd line
        char *line;
        fgets(cmd_line, sizeof(cmd_line), stdin);
        
        // seperate line from '\n'
        line = strtok(cmd_line, "\n");
        
        // parse line and store args in argv
        // entries from seq_q will execute in sequential manner
        // entries from pipe_1 will execute in piped manner
        struct queue *seq_q = parse_with_semicolan(line);

        // execute the seq q
        status = execute_seq_q(seq_q); 
    }

}