install : command/custom_cmd.h core/parsing.h core/shell.h misc/color.h cli.c
	gcc cli.c -o cli -std=c11
