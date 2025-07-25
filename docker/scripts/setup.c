// Copyright (C) 2025 rgarrigo
// This code is licensed under the GPLv3 License

// Executable to copy file with root permissions

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	filepath_cp[] = "/bin/cp";
	char	src[30];
	char	dest[30];

	if (argc != 3)
		return (1);
	if (strcmp(argv[1], "git") != 0 && strcmp(argv[1], "mail") != 0)
		return (1);
	if (strcmp(argv[1], "git") == 0)
	{
		if (strlen(argv[2]) != 4
			|| strncmp(argv[2], "ex", 2) != 0
			|| !isdigit(argv[2][2])
			|| !isdigit(argv[2][3]))
			return (1);
		sprintf(src, "/usr/local/executables/%s/git", argv[2]);
		sprintf(dest, "/usr/local/bin/git");
	}
	if (strcmp(argv[1], "mail") == 0)
	{
		if (strlen(argv[2]) != 7
			|| strncmp(argv[2], "mail_", 5) != 0
			|| !isdigit(argv[2][5])
			|| !isdigit(argv[2][6]))
			return (1);
		sprintf(src, "/usr/local/mail/%s.eml", argv[2]);
		sprintf(dest, "/var/mail/");
	}
	setreuid(geteuid(), geteuid());
	execl(filepath_cp, filepath_cp, src, dest, NULL);
	return (1);
}
