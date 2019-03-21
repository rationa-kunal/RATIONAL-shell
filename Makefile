install : custom_parsing.h parsing.h shell.h cli.c
	clear
	gcc cli.c -o cli