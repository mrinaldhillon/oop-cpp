cc_test(
	name = "account-test",
	srcs = ["account_test.cc"],
	copts = ["-std=c++14", "-Wall", "-Wextra", "-Weffc++",
		"-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    	deps = [
        "@gtest//:gtest_main",
        "//lib:account",
	],
)
