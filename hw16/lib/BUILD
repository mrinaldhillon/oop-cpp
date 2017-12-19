cc_library(
	name = "file-system",
	srcs = glob(["*.cc"]),
	hdrs = glob(["*.h"]),
	copts = ["-std=c++17", "-Wall", "-Wextra", "-Weffc++", "-Wno-non-virtual-dtor"],
	linkopts = ["-lstdc++fs"],
	visibility = ["//test:__pkg__"],
)
