cc_test(
	name = "stock-observer-test",
	srcs = glob(["stock_observer_test.cc"]),
	copts = ["-std=c++17", "-Wall", "-Wextra", "-Weffc++", "-Wno-non-virtual-dtor", "-Wno-unused-parameter",
		"-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    	deps = [
        "@gtest//:gtest_main",
        "//lib:stock-observer",
	],
)
