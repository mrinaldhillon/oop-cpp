CS680 Object Oriented Design and Programming
- Language C++
- Standard: C++14/17
- gcc >= 5.0
- Unit Testing: Google Test(gtest), Google Mock(gmock)
- Code Standards: ISOCpp core guidelines
	http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
- Code Style: Based on Google Style Guide
	https://google.github.io/styleguide/cppguide.html

Build Instruction:

Depenedencies:
- If a dependency is not already installed autogen.sh attempts to build each of the following packages.
- It is faster to install dependencies by package manager on your system
- Even if all of the following packages are installed, autogen.sh still needs to generate ./.bashrc

1. Bazel Build System:			Required!
	- https://bazel.build/
	- Package manager: https://docs.bazel.build/versions/master/install.html
	- Dependencies: JDK 8, Python, bash, zip, tar, and the usual C/C++ build toolchain

2. Valgrind : Memory leak checker	Optional
	
3. LCOV: Code coverage generator	Optional

Build Steps:
1. Build dependencies:

- autogen.sh:
	- bash script
	- compiles from source if target is not installed
	- Installs dependencies under tools/
	- Creates ./.bash.rc to export dependency paths
	- Usage: bash autogen.sh | bash autogen.sh clean

2. Build homeworks 

- build.sh		// bash script
	- Usage: bash build.sh [options] [target]
	-Options:
		- prompt:	sequentially builds homework, prompts to continue after each build.
		- clean:	sequentially cleans all homeworks
	- Examples:
		- bash build.sh			// build all without prompt
		- bash build.sh hw#
		- bash build.sh prompt
		- bash build.sh clean
		- bash build.sh clean hw#

- You may also run build.sh under hw# // requires current dir to be hw#
				// sources ../.bashrc
3. Source Directories:
	- hw#/lib/
	- hw#/test/
	- hw#/main/
4. Build Generated Directories
	- hw#/bazel-bin/test/
	- hw#/bazel-bin/main/
	- hw#/bazel-bin/lib/
	- hw#/bazel-testlogs/converage/
	- hw#/bazel-testlogs/test/*/
