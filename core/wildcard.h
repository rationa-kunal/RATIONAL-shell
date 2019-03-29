
int get_wildcard_matche(char *pattern, char *argv[], int *idx){

    // idx is current index of argv
    int i  = *idx;

    DIR *dir;
    struct dirent *f;     
    dir = opendir("./");
    
    if (dir != NULL){
        while (f = readdir (dir)){
            // filename f->d_name
            if(fnmatch(pattern, f->d_name, 0)==0){
                // file name matched with pattern
                i++;
                argv[i] = f->d_name;
            }
        }

        closedir(dir);

    } else perror ("wild card faild");

    return i;
}