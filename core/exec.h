
// execute command in fork 
// in and out is parameter for input and output file descriptor
int execute_cmd(struct command *cmd, int in, int out){
    int status;
    
    // fork and execute command in child
    // wait for child
    int pid;
    pid = fork();
    if (pid == 0) { // child process

        // if custom command exesits execute it
        if(execute_if_custom_command(cmd)==SUCC) return 0;
        
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
    
    } else { // parent process process
        wait(&status);
    }

    return status;
}

// execute every command from queue in pipe format
int execute_pipe_q(struct queue *pipe_q){
    int i;
    pid_t pid;
    int in, fd[2];

    // first command will have input from stdin
    in = 0;
    struct command *cmd;
    while((cmd=dequeue(pipe_q))){
        if(pipe_q->head == NULL) break; // this command is last one
        
        pipe(fd);
        // execute command with custom in and out
        int status = execute_cmd(cmd, in, fd[1]);
        close(fd[1]);
        // cnage next in to previous out
        in = fd[0];
    }

    // last command
    // in is prev out
    // out is stdout
    int status = execute_cmd(cmd, in, STDOUT_FILENO);
}

// execute every command from queue in sequential format
int execute_seq_q(struct queue *seq_q){
    int status = 0;
    struct queue *pipe_q;
    while((pipe_q=dequeue(seq_q))!=NULL){
        status = execute_pipe_q(pipe_q);
    }

    return status;
}