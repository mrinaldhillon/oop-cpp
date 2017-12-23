#!/usr/bin/env bash

[ ! -f "../.bashrc" ] && echo "Building in incorrect path" && exit 1
source "../.bashrc"  

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
HW_NAME="$( basename "${DIR}")"
BUILD_PARAMS=--collect_code_coverage
COVERAGE_DIR="${DIR}/bazel-testlogs/coverage"
COVERAGE_FILE="lcov-coverage.info"
COVERAGE_FILE_PATH="${COVERAGE_DIR}/${COVERAGE_FILE}"
BZL_BIN_DIR="${DIR}/bazel-bin"
BZL_TESTLOGS_DIR="${DIR}/bazel-testlogs"
BZL_TEST_DIR="${BZL_BIN_DIR}/test"
HELP_TEXT="bash build.sh | bash build.sh clean"
USER="${USER}"
function bazel_build ()
{
	"${BZL_BIN}" clean
	"${BZL_BIN}" build //... "${BUILD_PARAMS}"
	[ $? -ne 0 ] && return 1
	return 0
}

function run_test ()
{
	"${VALGRIND_BIN}" "${BZL_TEST_DIR}"/*-test
	[ $? -ne 0 ] && return 1
	return 0
}

function code_coverage ()
{
	if [ -z "${LCOV_BIN}" ]; then
		echo "Code coverage generation requires 'lcov' and 'genhtml' linux utilities installed"
		return 0
	fi
	cd "${BZL_BIN_DIR}"
	mkdir "${COVERAGE_DIR}"
	"${LCOV_BIN}" -q --directory lib --directory test --capture --output-file "${COVERAGE_FILE_PATH}"
	"${LCOV_BIN}" -q --remove "${COVERAGE_FILE_PATH}" '/usr/*' \
		"${TEST_TMPDIR}"'/_bazel_'"${USER}"'/*/execroot/__main__/external/*' \
		-o "${COVERAGE_FILE_PATH}"
	"${GENHTML_BIN}" "${COVERAGE_FILE_PATH}" -o "${COVERAGE_DIR}"
	echo "Code coverage generated at ${COVERAGE_DIR}"
	return 0
}


function build ()
{
	bazel_build
	[ $? -ne 0 ] && exit 1
	run_test
	[ $? -ne 0 ] && exit 1
	code_coverage
	exit 0
}

if [ ! -z "$1" ]; then
	if [ $1 = "clean" ]; then
		"${BZL_BIN}" clean && exit 0
	else
		[ $1 = "help" ] && echo "${HELP_TEXT}" && exit 1
	fi
else 
	build
fi
