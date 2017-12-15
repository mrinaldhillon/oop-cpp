cc_test(
	name = "file-system-test",
	srcs = ["file_system_test.cc"],
	copts = ["-std=c++14", "-Wall", "-Wextra", "-Weffc++",
		"-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    	deps = [
        "@gtest//:gtest_main",
        "//lib:file-system",
	],
)
