int execute_cmd(struct command *cmd){
    int status;
    // fork and execute command in child
    // wait for child
    int pid;
    pid = fork();
    if (pid == 0) { // parent process
        if (execvp(cmd->argv[0], cmd->argv) == -1) perror("lsh");
    } else { // child process
        wait(&status);
    }

    return status;
}

int execute_seq_q(struct queue *seq_q){
    int status = 0;
    struct command *cmd;
    while((cmd=dequeue(seq_q))!=NULL){
        printf("exec\n");
        if(execute_if_custom_command(cmd)!=ERR) continue;
        status = execute_cmd(cmd);
    }

    return status;
}