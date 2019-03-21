int execute_cmd(char *argv[]){
    int status;
    // fork and execute command in child
    // wait for child
    int pid;
    pid = fork();
    if (pid == 0) { // parent process
        if (execvp(argv[0], argv) == -1) perror("lsh");
    } else { // child process
        wait(&status);
    }

    return status;
}