cc_test(
	name = "file-cache-test",
	srcs = ["file_cache_test.cc"],
	copts = ["-std=c++14", "-Wall", "-Wextra", "-Weffc++",
		"-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    	deps = [
        "@gtest//:gtest_main",
        "//lib:file-cache",
	],
)
