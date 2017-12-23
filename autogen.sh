#!/usr/bin/env bash
# Builds project dependencies and sets up pwd/.bashrc to be sourced by build scripts
# Build bazel, valgrind and lcov

machine="$(uname -s)"
case "${machine}" in
    Linux*)     OS="Linux";;
    Darwin*)    OS="Mac";;
    *)          OS="UNKNOWN"
esac

if [ ${OS} = "UNKNOWN" ]; then
	echo "Please select you OS and press enter: 1. Linux 2. MacOS 3.exit"
	read choice
	case "${choice}" in
		2)     OS=Mac;;
		3)     OS=Linux;;
		4)     exit 1;;
		*)     echo "Invalid choice, exiting" && exit 1
	esac
fi

if [ ${OS} = "Mac" ]; then
	echo "macOS has not been tested!!!
		you will need to install command line tools,
		devel libs need to be under /usr/include, /usr/lib
		press enter to continue"
	read choice
fi

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
TOOLS_DIR="${SCRIPT_DIR}/tools"
WGET=`which wget`
UNZIP=`which unzip`
TAR=`which tar` 
BZL_DIR="${TOOLS_DIR}/bazel"
BZL_BIN="${BZL_DIR}/output/bazel"
BZL_CACHE_DIR="${SCRIPT_DIR}"
VALGRIND_DIR="${TOOLS_DIR}/valgrind"
VALGRIND_BIN="${VALGRIND_DIR}/bin/valgrind"
LCOV_DIR="${TOOLS_DIR}/lcov"
LCOV_BIN="${LCOV_DIR}/bin/lcov"
GENHTML_BIN="${LCOV_DIR}/bin/genhtml"
BASH_RC="${SCRIPT_DIR}/.bashrc"
HELP_TEXT="bash autogen.sh | bash autogen.sh clean"

function setup_bash_rc ()
{
	echo "export BZL_BIN=${BZL_BIN}" > "${BASH_RC}"
	echo "export TEST_TMPDIR=${BZL_CACHE_DIR}" >> "${BASH_RC}"
	[ -f "${VALGRIND_BIN}" ] && echo "export VALGRIND_BIN=${VALGRIND_BIN}" >> "${BASH_RC}"
	[ -f "${LCOV_BIN}" ] && echo "export LCOV_BIN=${LCOV_BIN}" >> "${BASH_RC}"
	[ -f "${GENHTML_BIN}" ] && echo "export GENHTML_BIN=${GENHTML_BIN}" >> "${BASH_RC}"
	echo "${SCRIPT_DIR}/.bashrc generated, to be sourced by build scripts"
}

function compile_bazel ()
{
BZL_VER=0.9.0
BZL_ARCHIVE="bazel-${BZL_VER}-dist.zip"
BZL_URL="https://github.com/bazelbuild/bazel/releases/download/${BZL_VER}/${BZL_ARCHIVE}"
BZL_ARCHIVE_PATH="${BZL_DIR}/${BZL_ARCHIVE}"

BZL=`which bazel`
[ ! -z "${BZL}" ] && BZL_BIN="${BZL}"

[ -f "${BZL_BIN}" ] && echo "bzl already installed at ${BZL_BIN}" && return 0

[ -z "${WGET}" ] && "wget not found" && return 1
[ -z "${UNZIP}" ] && "unzip not found" && return 1

mkdir -p "${BZL_DIR}"
if [ ! -f "${BZL_ARCHIVE_PATH}" ];then
	"${WGET}" "${BZL_URL}" -P "${BZL_DIR}"
	[ $? -ne 0 ] && echo "Bazel download failed" && return 1
fi

"${UNZIP}" -u "${BZL_ARCHIVE_PATH}" -d "${BZL_DIR}"
[ $? -ne 0 ] && echo "Could not unzip bazel" && return 1
cd "${BZL_DIR}"
[ $? -ne 0 ] && echo "Where am I, incorrect path BUG!" && return 1
./compile.sh
[ $? -ne 0 ] && echo "Bazel compile failed.. pls check dependencies" && return 1
echo "Bazel installed at ${BZL_BIN}"
}

compile_valgrind ()
{
VALGRIND_VER=3.13.0
VALGRIND_ARCHIVE="valgrind-${VALGRIND_VER}.tar.bz2"
VALGRIND_URL="ftp://sourceware.org/pub/valgrind/${VALGRIND_ARCHIVE}"
VALGRIND_ARCHIVE_PATH="${VALGRIND_DIR}/${VALGRIND_ARCHIVE}"

VALGRIND=`which valgrind`
[ ! -z "${VALGRIND}" ] && VALGRIND_BIN="${VALGRIND}"

[ -f "${VALGRIND_BIN}" ] && echo "valgrind already installed at ${VALGRIND_BIN}" && return 0

[ -z "${WGET}" ] && "wget not found" && return 1
[ -z "${TAR}" ] && "tar not found" && return 1

mkdir -p "${VALGRIND_DIR}"
if [ ! -f "${VALGRIND_ARCHIVE_PATH}" ];then
	"${WGET}" "${VALGRIND_URL}" -P "${VALGRIND_DIR}"
	[ $? -ne 0 ] && echo "valgrind download failed" && return 1
fi

"${TAR}" --skip-old-files --strip-components 1 -xjf "${VALGRIND_ARCHIVE_PATH}" -C "${VALGRIND_DIR}"
[ $? -ne 0 ] && echo "Could not untar valgrind" && return 1
cd "${VALGRIND_DIR}"
[ $? -ne 0 ] && echo "Where am I, incorrect path BUG!" && return 1
./configure --prefix="${VALGRIND_DIR}"
[ $? -ne 0 ] && echo "Valgrind configuration failed.. pls check dependencies" && return 1
make && make install
[ $? -ne 0 ] && echo "Valgrind compilation failed.. pls check dependencies" && return 1
echo "Valgrind installed at ${VALGRIND_BIN}"
}

compile_lcov ()
{

LCOV_VER=1.13
LCOV_ARCHIVE="lcov-${LCOV_VER}.tar.gz"
LCOV_URL="https://github.com/linux-test-project/lcov/releases/download/v${LCOV_VER}/${LCOV_ARCHIVE}"
LCOV_ARCHIVE_PATH="${LCOV_DIR}/${LCOV_ARCHIVE}"

GCOV=`which gcov`
[ -z "${GCOV}" ] && echo "gcov dependency of lcov is not installed.. failing out" && return 1

LCOV=`which lcov`
[ ! -z "${LCOV}" ] && LCOV_BIN="${LCOV}"
GENHTML=`which genhtml`
[ ! -z "${GENHTML}" ] && GENHTML_BIN="${GENHTML}"

if [ -f "${LCOV_BIN}" ]; then
	echo "lcov is already installed at ${LCOV_BIN}"
	[ -f "${GENHTML}" ] && return 0
fi

[ -z "${WGET}" ] && "wget not found" && return 1
[ -z "${TAR}" ] && "tar not found" && return 1

mkdir -p "${LCOV_DIR}"
if [ ! -f "${LCOV_ARCHIVE_PATH}" ];then
	"${WGET}" "${LCOV_URL}" -P "${LCOV_DIR}"
	[ $? -ne 0 ] && echo "lcov download failed" && return 1
fi

"${TAR}" --skip-old-files --strip-components 1 -xf "${LCOV_ARCHIVE_PATH}" -C "${LCOV_DIR}"
[ $? -ne 0 ] && echo "Could not untar lcov" && return 1
echo "lcov installed at ${LCOV_BIN}"
echo "genhtml installed at ${GENHTML_BIN}"
}

function compile () {
	compile_bazel
	[ $? -ne 0 ] && return 1
	BAZEL_INSTALLED=1
	compile_valgrind
	[ $? -ne 0 ] && "Valgrind compilation failure is non critical to builds.. continue"
	VALGRIND_INSTALLED=1
	compile_lcov
	[ $? -ne 0 ] && "LCOV compilation failure is non critical to builds.. continue"
	LCOV_INSTALLED=1
	[ 1 -eq $BAZEL_INSTALLED ] && echo "Bazel install at ${BZL_BIN}"
	[ 1 -eq $VALGRIND_INSTALLED ] && echo "Valgrind install at ${VALGRIND_BIN}"
	[ 1 -eq $LCOV_INSTALLED ] && echo "LCOV and GENHTML install at ${LCOV_BIN} and ${GENHTML_BIN}"
	setup_bash_rc
	return 0
}

if [ ! -z "$1" ]; then
	if [ $1 = "clean" ]; then
		rm -rf "${TOOLS_DIR}" && exit 0
		rm -rf "${SCRIPT_DIR}/_bazel_${USER}"
	else
		[ $1 = "help" ] && echo "${HELP_TEXT}" && exit 1
	fi
else 
	compile
	exit $?
fi
