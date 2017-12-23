#cc_test(
#	name = "file-system-test",
#	srcs = glob(["file_system_test.cc"]),
#	copts = ["-std=c++17", "-Wall", "-Wextra", "-Weffc++", "-Wno-non-virtual-dtor",
#		"-Iexternal/gtest/include", "-Iexternal/gmock/include"],
#    	deps = [
#        "@gtest//:gtest_main",
#        "//lib:file-system",
#	],
#)

cc_test(
	name = "shell-test",
	srcs = glob(["shell_test.cc"]),
	copts = ["-std=c++17", "-Wall", "-Wextra", "-Weffc++", "-Wno-non-virtual-dtor",
		"-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    	deps = [
        "@gtest//:gtest_main",
        "//lib:file-system",
	],
)
