install : custom_cmd.h parsing.h core/shell.h misc/color.h cli.c
	clear
	gcc cli.c -o cli