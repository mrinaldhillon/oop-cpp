#!/bin/sh

uname -a | grep Linux >> /dev/null
[ $? -ne 0 ] && echo "Only linux supported for now" && exit 1

which bazel >> /dev/null
[ $? -ne 0 ] && echo "Please install bazel build system" && exit 1


PROJECT_HOME=`pwd`
BIN_TARGET=comparator-test
BUILD_TEST=test:${BIN_TARGET}
BUILD_PARAMS=--collect_code_coverage
COVERAGE_DIR=${PROJECT_HOME}/bazel-testlogs/test/${BIN_TARGET}
COVERAGE_FILE=lcov-coverage.info
COVERAGE_FILE_PATH=${COVERAGE_DIR}/${COVERAGE_FILE}
COVERAGE_EXCLUDE_LIST="'/usr/*' '${HOME}/.cache/bazel/*/*/execroot/__main__/external/*'"
RUN_UNDER=`which valgrind`

bazel clean
bazel build ${BUILD_TEST} ${BUILD_PARAMS}
[ $? -ne 0 ] && echo "Build Failed" && exit 1

${RUN_UNDER} ./bazel-bin/test/${BIN_TARGET}

which lcov >> /dev/null && which genhtml >> /dev/null
if [ $? -eq 0 ]; then
	cd bazel-bin
	lcov -q --directory lib --directory test --capture --output-file ${COVERAGE_FILE_PATH}
	lcov -q --remove ${COVERAGE_FILE_PATH} '/usr/*' ${HOME}'/.cache/bazel/*/*/execroot/__main__/external/*' -o ${COVERAGE_FILE_PATH}
	genhtml ${COVERAGE_FILE_PATH} -o ${COVERAGE_DIR}
else
	echo "Code coverage generation requires 'lcov' and 'genhtml' linux utilities installed"
fi
