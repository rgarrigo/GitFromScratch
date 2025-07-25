// Copyright (C) 2025 rgarrigo
// This code is licensed under the GPLv3 License

#ifndef GIT_H
# define GIT_H
 
#define MAX_PARAMS 200

#define SUBCOMMAND_NAME_MAX_LEN 20
#define SUBCOMMAND_DESCRIPTION_MAX_LEN 200
#define SUBCOMMAND_OPTIONS_MAX_NB 20

#define OPTION_MAX_LEN 25
#define OPTION_DESCRIPTION_MAX_LEN 200

#define SCRIPT_PATH "/usr/local/scripts/" EXO ".sh"

typedef struct s_option{
	char	name[OPTION_MAX_LEN];
	char	description[OPTION_DESCRIPTION_MAX_LEN];
}	t_option;

typedef struct s_subcommand
{
	char		name[SUBCOMMAND_NAME_MAX_LEN];
	char		required_option_names[SUBCOMMAND_OPTIONS_MAX_NB][OPTION_MAX_LEN];
	char		description[SUBCOMMAND_DESCRIPTION_MAX_LEN];
	t_option	options[SUBCOMMAND_OPTIONS_MAX_NB];
}	t_subcommand;

#endif
