#!/usr/bin/env bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "${SCRIPT_DIR}"
[ ! -f "./.bashrc" ] && echo "First run autogen.sh" && exit 1

HELP_TEXT="HELP ....
bash build.sh			# builds all
bash build.sh prompt		# all with continue prompt
bash build.sh clean		# clean all
bash build.sh hwN		# build  Nth homework"

function build_all ()
{
	find * -prune -type d | grep hw | while IFS= read -r d; do
		echo "Starting Build for ${d} *****************************  "
		cd "${SCRIPT_DIR}/${d}" && bash build.sh
		echo "Finshed Build for ${d} ***************************** "
	done
}

function build_all_prompt ()
{
	find * -prune -type d | grep hw | while IFS= read -r d; do
		echo "Starting Build for ${d} *****************************"
		cd "${SCRIPT_DIR}/${d}" && bash build.sh
		echo "Finshed Build for ${d} *****************************"
		echo "Press key to continue";
		read -p "Conitnue? [yn]" answer </dev/tty
		[ $answer = "n" ] && return 0
	done
}

function clean_all ()
{
	find * -prune -type d | grep hw | while IFS= read -r d; do
		echo "Starting cleanup for ${d} *****************************"
		cd "${SCRIPT_DIR}/${d}" && bash build.sh clean
		echo "Finshed cleanup for ${d} *****************************"
	done
}

function build_hw ()
{
	echo "Starting Build for $@ ***************************** "
	cd $@ && bash build.sh
	echo "Finished Build for $@ ***************************** "
}


if [ ! -z "$1" ]; then
	if [ $1 = "clean" ]; then
		clean_all
	elif [ -d "${1}" ]; then
		build_hw "${1}"
	elif [ "${1}" = "prompt" ]; then
		build_all_prompt
	else

		echo "${HELP_TEXT}" && exit 1
	fi
else 
	build_all
fi
