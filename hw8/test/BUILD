cc_test(
	name = "polygon-test",
	srcs = ["polygon_test.cc"],
	copts = ["-std=c++14", "-Wall", "-Wextra", "-Weffc++",
		"-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    	deps = [
        "@gtest//:gtest_main",
        "//lib:polygon",
	],
)
