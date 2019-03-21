install : command/custom_cmd.h core/parsing.h core/shell.h misc/color.h cli.c
	clear
	gcc cli.c -o cli