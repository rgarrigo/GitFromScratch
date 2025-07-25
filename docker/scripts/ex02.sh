#!/bin/bash
# Copyright (C) 2025 rgarrigo
# This code is licensed under the GPLv3 License

COLOR="\033[35m"
NC="\033[0m"

function check() {
	GIT_DIR=/home/aria/hello_there/
	(/usr/bin/git -C ${GIT_DIR} show HEAD | grep -A 1 "idea.txt" | grep "new file") > /dev/null 2> /dev/null
	RET_VALUE=$?
	if [ ${RET_VALUE} -ne 0 ]
	then
		exit ${RET_VALUE}
	fi
}

function setup_next_exercise() {
	echo -e "${COLOR}Congratulations! That's all for this MVP${NC}"
}

check
setup_next_exercise
