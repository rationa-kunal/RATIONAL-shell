int get_wildcard_matche(char *pattern, char *argv[], int *idx){

    int i  = *idx;
    DIR *dir;
    struct dirent *f;     
    dir = opendir("./");
    printf("ptrn %s\n", pattern);
    if (dir != NULL){
        while (f = readdir (dir)){
            // printf("%s\t", f->d_name);
            // filename f->d_name
            if(fnmatch(pattern, f->d_name, 0)==0){
                printf("%s\t", f->d_name);
                i++;
                argv[i] = f->d_name;
                printf("%s\t", f->d_name);
            }
        }

        closedir(dir);

    } else perror ("wild card faild");

    return i;
}