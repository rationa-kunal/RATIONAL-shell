
char *wild_card_prefix = "W";
char *semicolan = ";";
char *pipe_s = "|";
char *space_s = " ";

struct command * parse_with_space(char *line){
    // parse line with ' ' as delimeter
    struct command * new_cmd = (struct command *) malloc(sizeof(struct command));
    
    int idx = 0;
    char *token;
    token = strtok(line, space_s);
    new_cmd->argv[idx] = token;
    
    while( (token=strtok(NULL, space_s)) != NULL ) {
        idx++;

        // check for wild card
        if(strcmp(token, wild_card_prefix)==0 ) {
            idx--;
            // wild card present
            // get wildcard match append it to argv
            token = strtok(NULL, space_s);
            idx = get_wildcard_matche(token, new_cmd->argv, &idx);
            continue;
        }

        new_cmd->argv[idx] = token;
    }
    new_cmd->argv[++idx] = NULL;

    return new_cmd;
}

struct queue *parse_with_pipe(char *line){
    // parse line with '|' as delimeter

    struct queue *pipe_q = q_init();

    char *seq_saveptr;
    char *pipe_subcmd;
    pipe_subcmd=strtok_r(line, pipe_s, &seq_saveptr);
    while(pipe_subcmd!=NULL){
        
        // enque the command resulted from parsing
        enqueue(pipe_q, parse_with_space(pipe_subcmd)) ;   
        pipe_subcmd=strtok_r(NULL, pipe_s, &seq_saveptr);

    }

    return pipe_q;
}

struct queue *parse_with_semicolan(char *line){
    // parse line with ';' as delimeter

    struct queue *seq_q = q_init();

    // parsing line with semicolan
    char *seq_saveptr;
    char *seq_subcmd;
    seq_subcmd=strtok_r(line, semicolan, &seq_saveptr);
    while(seq_subcmd!=NULL){
        
        // enque the pipe_q resulted ffrom parsing
        enqueue(seq_q, parse_with_pipe(seq_subcmd)) ;   
        seq_subcmd=strtok_r(NULL, semicolan, &seq_saveptr);

    }


    return seq_q;
}