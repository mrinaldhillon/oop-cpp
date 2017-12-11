cc_test(
	name = "comparator-test",
	srcs = ["comparator_test.cc"],
	copts = ["-std=c++14", "-Wall", "-Wextra", "-Weffc++",
		"-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    	deps = [
        "@gtest//:gtest_main",
        "//lib:comparator",
	],
)
