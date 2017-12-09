cc_test(
	name = "account-test",
	srcs = ["account_test.cc"],
	copts = ["-std=c++14","-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    	deps = [
        "@gtest//:gtest_main",
        "//lib:account",
	],
)
