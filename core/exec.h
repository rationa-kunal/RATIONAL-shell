int execute_cmd(struct command *cmd, int in, int out){
    int status;
    // fork and execute command in child
    // wait for child
    int pid;
    pid = fork();
    if (pid == 0) {
        if(execute_if_custom_command(cmd)==SUCC) return 0;
        // printf("here %s\n", cmd->argv[0]);
        if (in != 0){
            // stdin -> in then close(in) now stdin points to in
            dup2 (in, 0);
            close (in);
        }
        if (out != 1){
            // stdout -> in then close(out) now stdout points to out
            dup2 (out, 1);
            close (out);
        }
        if (execvp(cmd->argv[0], cmd->argv) == -1) perror("lsh");
    } else { // child process
        wait(&status);
    }

    return status;
}

int execute_pipe_q(struct queue *pipe_q){
    int i;
    pid_t pid;
    int in, fd[2];

    in = 0;
    int count;
    struct command *cmd;
    while((cmd=dequeue(pipe_q))){
        if(pipe_q->head == NULL) break;
        
        pipe(fd);
        int status = execute_cmd(cmd, in, fd[1]);
        close(fd[1]);
        in = fd[0];
        // printf("count %d\n", count++);
    }

    int status = execute_cmd(cmd, in, STDOUT_FILENO);
}

int execute_seq_q(struct queue *seq_q){
    int status = 0;
    struct queue *pipe_q;
    while((pipe_q=dequeue(seq_q))!=NULL){
        // printf("exec\n");
        //if(execute_if_custom_command(cmd)!=ERR) continue;
        status = execute_pipe_q(pipe_q);
    }

    return status;
}