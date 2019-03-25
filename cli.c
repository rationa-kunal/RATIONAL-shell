#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <dirent.h>
#include <fnmatch.h>

#include "misc/color.h"
#include "core/models.h"
#include "core/wildcard.h"
#include "command/history.h"
#include "command/remote_shell.h"
#include "command/custom_cmd.h"
#include "core/parsing.h"
#include "core/exec.h"
#include "core/shell.h"

void main(){
    shell_loop();
}