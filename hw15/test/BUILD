cc_test(
	name = "file-system-test",
	srcs = glob(["*.cc"]),
	copts = ["-std=c++17", "-Wall", "-Wextra", "-Weffc++", "-Wno-non-virtual-dtor",
		"-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    	deps = [
        "@gtest//:gtest_main",
        "//lib:file-system",
	],
)
