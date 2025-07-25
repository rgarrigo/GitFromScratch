// Copyright (C) 2025 rgarrigo
// This code is licensed under the GPLv3 License

#ifndef PARAMS_H
# define PARAMS_H

#include "git.h"

#define SUBCOMMANDS_NB 2

const t_subcommand	subcommands[SUBCOMMANDS_NB] = {
	{"init", {}, "usage: git init\n", {}},
	{"config", {}, "usage: git config [--global] <name> <value>\n", {
		{"--global", "\
    --global              use global config file\n"},
	}},
};

#endif
