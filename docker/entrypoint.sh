#!/bin/sh
# Copyright (C) 2025 rgarrigo
# This code is licensed under the GPLv3 License

setup_ssh()
{
	ssh-keygen -A
	sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config
}

setup_users()
{
	(echo aria && echo aria && yes '') | adduser aria
	(echo stuck && echo stuck && yes '') | adduser stuck

	# Add color to the aria shell prompt
	echo "export PS1='\e[01;32m\h\e[0m:\e[01;34m\w\e[0m\$ '" > /home/aria/.profile
	chown aria /home/aria/.profile
}

setup_executables()
{
	# git executables to restrict access to a few git subcommands
	cd /usr/local/git
	for exo in ex00 ex01 ex02
	do
		make clean
		EXO=${exo} make
		mkdir -p ../executables/${exo}/
		mv git ../executables/${exo}/git
		chmod 711 ../executables/${exo}/git
	done

	# setup executable to copy specific root files
	gcc /usr/local/scripts/setup.c -o /usr/local/scripts/setup
	chmod 7711 /usr/local/scripts/setup

	# mail executable to read the latest mail
	mv /usr/local/scripts/mail /usr/local/bin/mail
	chmod 755 /usr/local/bin/mail
}

setup_first_exercise()
{
	cp /usr/local/mail/mail_00.eml /usr/local/mail/mail_01.eml /var/mail/
	cp /usr/local/executables/ex00/git /usr/local/bin/git
	cp /usr/local/man/*.gz /usr/share/man/man1/
}

setup_ssh
setup_users
setup_executables
setup_first_exercise

exec /usr/sbin/sshd -D
