
char *wild_card_prefix = "W";

void parse_with_space(char *line, char *argv[]){
    // parse line with ' ' as delimeter
    // append tokens in argv
    int idx = 0;
    char *token;
    char delim = ' ';
    token = strtok(line, &delim);
    argv[idx] = token;
    while( (token=strtok(NULL, &delim)) != NULL ) {
        idx++;
        //token = strtok(NULL, &delim);
        
        // check for wild card
        if(strcmp(token, wild_card_prefix)==0 ) {
            idx--;
            // wild card present
            // get wildcard match append it to argv
            token = strtok(NULL, &delim);
            idx = get_wildcard_matche(token, argv, &idx);
            continue;
        }

        argv[idx] = token;
    }
    argv[++idx] = NULL;

}