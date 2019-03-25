#include <unistd.h>

struct command{
  const char **argv;
};

int spawn_proc (int in, int out, struct command *cmd){
  pid_t pid;

    if ((pid = fork ()) == 0){
        // if in or out is not stdin or stdout
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

      return execvp (cmd->argv [0], cmd->argv);
    }

  return pid;
}

int fork_pipes (int n, struct command *cmd){
    int i;
    pid_t pid;
    int in, fd [2];

    /* The first process should get its input from the original file descriptor 0.  */
    in = 0;

    /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
    for (i = 0; i < n - 1; ++i){
        pipe(fd);

        // write output in fd[1]
        spawn_proc (in, fd [1], cmd + i);

        // close write end
        close (fd [1]);

        // pass the read end -- eventually output 
        in = fd [0];
    }

    // last command
    // stdin -> read from prev
    // stdout -> 1
    if (in != 0)
        dup2 (in, 0);

    return execvp (cmd [i].argv [0], (char * const *)cmd [i].argv);

}

int
main ()
{
  const char *ls[] = { "ls", "-l", 0 };
  const char *awk[] = { "awk", "{print $1}", 0 };
  const char *sort[] = { "sort", 0 };
  const char *uniq[] = { "uniq", 0 };

  struct command cmd [] = { {ls}, {awk}, {sort}, {uniq} };

  return fork_pipes (4, cmd);
}