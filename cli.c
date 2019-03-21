#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "misc/color.h"
#include "parsing.h"
#include "history.h"
#include "remote_shell.h"
#include "custom_cmd.h"

#include "core/shell.h"

void main(){
    shell_loop();
}