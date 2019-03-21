
void parse_with_space(char *line, char *argv[]){
    // parse line with ' ' as delimeter
    // append tokens in argv
    int idx = 0;
    char *token;
    char delim = ' ';
    token = strtok(line, &delim);
    argv[idx] = token;
    while( token != NULL ) {
        idx++;
        token = strtok(NULL, &delim);
        argv[idx] = token;
    }

}