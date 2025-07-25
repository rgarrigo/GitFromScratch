// Copyright (C) 2025 rgarrigo
// This code is licensed under the GPLv3 License

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "git.h"
#include "params.h"

void	print_git_subcommand_usage(const t_subcommand *subcommand)
{
	const t_option	*options = subcommand->options;

	printf("%s", subcommand->description);
	for (int i = 0; options[i].name[0]; ++i)
		printf("%s", options[i].description);
}

void	print_git_error_subcommand_required_option_not_found(
	const t_subcommand *subcommand,
	const char *required_option_name
)
{
	if (required_option_name[1] == '-')
		printf("error: expected option `%s' not found\n", required_option_name);
	else
		printf("error: expected switch `%s' not found\n", required_option_name);
	print_git_subcommand_usage(subcommand);
}

void	print_git_error_subcommand_option_not_found(
	const t_subcommand *subcommand,
	const char *option_name
)
{
	if (option_name[1] == '-')
		printf("error: unknown option `%s'\n", option_name + 2);
	else
		printf("error: unknown switch `%s'\n", option_name + 1);
	print_git_subcommand_usage(subcommand);
}

void	print_git_error_subcommand_not_found(const char *subcommand)
{
	printf("git: '%s' is not a git command. See 'git --help'.\n", subcommand);
}

int	check_option(const t_subcommand *subcommand, const char *option_name)
{
	const t_option	*options = subcommand->options;

	for (int i = 0; options[i].name[0]; ++i)
		if (strcmp(option_name, options[i].name) == 0)
			return (0);
	if (strcmp(option_name, "-h") == 0
		|| strcmp(option_name, "--help") == 0)
		return (0);
	return (-1);
}

int	check_required_option(const char *required_option, char *option_names[MAX_PARAMS])
{
	for (int i = 0; option_names[i]; ++i)
		if (strcmp(option_names[i], required_option) == 0)
			return (0);
	return (-1);
}

int	check_input_options(const t_subcommand *subcommand, char *option_names[MAX_PARAMS])
{
	for (int i = 0; option_names[i]; ++i)
	{
		if (check_option(subcommand, option_names[i]) == 0)
			continue ;
		print_git_error_subcommand_option_not_found(subcommand, option_names[i]);
		return (-1);
	}
	for (int i = 0; option_names[i]; ++i)
		if (strcmp(option_names[i], "-h") == 0
			|| strcmp(option_names[i], "--help") == 0)
			return (0);
	for (int i = 0; subcommand->required_option_names[i][0]; ++i)
	{
		if (check_required_option(subcommand->required_option_names[i], option_names) == 0)
			continue ;
		print_git_error_subcommand_required_option_not_found(subcommand, subcommand->required_option_names[i]);
		return (-1);
	}
	return (0);
}

const t_subcommand	*get_subcommand(const char *subcommand_name)
{
	for (int i = 0; i < SUBCOMMANDS_NB; ++i)
		if (strcmp(subcommand_name, subcommands[i].name) == 0)
			return (&subcommands[i]);
	return (NULL);
}

int	check_input(const char *subcommand_name, char *option_names[MAX_PARAMS])
{
	const t_subcommand	*subcommand;

	subcommand = get_subcommand(subcommand_name);
	if (!subcommand)
		return (print_git_error_subcommand_not_found(subcommand_name), -1);
	return (check_input_options(subcommand, option_names));
}

int	help_option_set(char *option_names[MAX_PARAMS])
{
	for (int i = 0; option_names[i]; ++i)
		if (strcmp(option_names[i], "-h") == 0
			|| strcmp(option_names[i], "--help") == 0)
			return (1);
	return (0);
}

int	manage_simple_git(void)
{
	printf("usage: git <command>\n");
	printf("Available commands:\n");
	for (int i = 0; i < SUBCOMMANDS_NB; ++i)
		printf("\t%s\n", subcommands[i].name);
	printf("For more information: git <command> --help\n");
	return (0);
}

int	is_option(const char *str)
{
	return (*str == '-');
}

void	get_subcommand_name(char **subcommand_name, int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		if (is_option(argv[i]))
			continue ;
		*subcommand_name = argv[i];
		break ;
	}
}

void	get_option_names(char *option_names[MAX_PARAMS], int argc, char *argv[])
{
	int	i = 0;

	for (int j = 1; j < argc; ++j)
	{
		if (!is_option(argv[j]))
			continue ;
		option_names[i++] = argv[j];
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*subcommand_name = NULL;
	char	*option_names[MAX_PARAMS] = {};
	pid_t	pid;
	int	wstatus;
	char	*script_argv[2] = {};

	get_subcommand_name(&subcommand_name, argc, argv);
	get_option_names(option_names, argc, argv);
	if (!subcommand_name)
		return (manage_simple_git(), 1);
	if (check_input(subcommand_name, option_names) == -1)
		return (1);
	if (help_option_set(option_names))
		return (print_git_subcommand_usage(get_subcommand(subcommand_name)), 0);
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/git", argv, envp);
		return (0);
	}
	pid = waitpid(pid, &wstatus, 0);
	if (WEXITSTATUS(wstatus) != 0)
		return (WEXITSTATUS(wstatus));
	script_argv[0] = SCRIPT_PATH;
	execve(SCRIPT_PATH, script_argv, NULL);
	return (0);
}
