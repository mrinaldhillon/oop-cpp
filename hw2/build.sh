#!/bin/sh

uname -a | grep Linux >> /dev/null
[ $? -ne 0 ] && echo "Only linux supported for now" && exit 1

which bazel >> /dev/null
[ $? -ne 0 ] && echo "Please install bazel build system" && exit 1


PROJECT_HOME=`pwd`
BIN_TARGET=polygon-test
BUILD_TEST=test:${BIN_TARGET}
BUILD_PARAMS=
COVERAGE_DIR=
COVERAGE_FILE=
COVERAGE_FILE_PATH=
COVERAGE_EXCLUDE_LIST=

bazel clean
bazel build ${BUILD_TEST} ${BUILD_PARAMS}
[ $? -ne 0 ] && echo "Build Failed" && exit 1
./bazel-bin/test/${BIN_TARGET}
