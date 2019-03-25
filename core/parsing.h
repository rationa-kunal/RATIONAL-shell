
char *wild_card_prefix = "W";
char *semicolan = ";";
char *pipe_s = "|";
char *delim = " ";

struct command * parse_with_space(char *line){
    // parse line with ' ' as delimeter
    // append tokens in argv
    struct command * new_cmd = (struct command *) malloc(sizeof(struct command));
    int idx = 0;
    char *token;
    char delim = ' ';
    token = strtok(line, &delim);
    printf("token %s\n", token);
    new_cmd->argv[idx] = token;
    while( (token=strtok(NULL, &delim)) != NULL ) {
        idx++;
        printf("token %s\n", token);
        //token = strtok(NULL, &delim);
        // check for wild card
        if(strcmp(token, wild_card_prefix)==0 ) {
            idx--;
            // wild card present
            // get wildcard match append it to argv
            token = strtok(NULL, &delim);
            idx = get_wildcard_matche(token, new_cmd->argv, &idx);
            continue;
        }

        new_cmd->argv[idx] = token;
    }
    new_cmd->argv[++idx] = NULL;

    return new_cmd;
}

struct queue * parse_with_semicolan(char *line){
    // parse line with ' ' as delimeter
    // append tokens in argv

    // initialize seq queue
    // all sequential commands will be here
    struct queue *seq_q = q_init();

    // parsing line with semicolan
    char *seq_saveptr;
    char *seq_subcmd;
    seq_subcmd=strtok_r(line, semicolan, &seq_saveptr);
    while(seq_subcmd!=NULL){
        
        printf("semic %s\n", seq_subcmd);
        enqueue(seq_q, parse_with_space(seq_subcmd)) ;   
        seq_subcmd=strtok_r(NULL, semicolan, &seq_saveptr);

    }


    return seq_q;
}