#!/usr/bin/env bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "${SCRIPT_DIR}"
[ ! -f "./.bashrc" ] && echo "First run autogen.sh" && exit 1

HELP_TEXT="HELP ....
bash build.sh			# builds all
bash build.sh prompt		# all with continue prompt
bash build.sh clean		# clean all
bash build.sh hwN		# build Nth homework"

function build_one ()
{
		echo "Starting Build for $@ *****************************"
		cd "${SCRIPT_DIR}/$@" && bash build.sh
		echo "Finshed Build for $@ *****************************"
}

function build_all ()
{
	find * -prune -type d | grep hw | while IFS= read -r d; do
		build_one "${d}"
	done
}

function build_all_prompt ()
{
	find * -prune -type d | grep hw | while IFS= read -r d; do
		build_one "${d}"
		echo "Press key to continue";
		read -p "Conitnue? [y/n]" answer </dev/tty
		[ $answer = "n" ] && return 0
	done
}

function clean_one ()
{
		echo "Starting cleanup for $@ *****************************"
		cd "${SCRIPT_DIR}/$@" && bash build.sh clean
		echo "Finshed cleanup for $@ *****************************"
}

function clean_all ()
{
	[ ! -z "$@" ] && clean_one "$@" && return $?
	find * -prune -type d | grep hw | while IFS= read -r d; do
		clean_one "${d}"
	done
}

if [ ! -z "$1" ]; then
	if [ $1 = "clean" ]; then
		clean_all "${2}"
	elif [ -d "${1}" ]; then
		build_one "${1}"
	elif [ "${1}" = "prompt" ]; then
		build_all_prompt
	else

		echo "${HELP_TEXT}" && exit 1
	fi
	exit $?
else 
	build_all
fi
