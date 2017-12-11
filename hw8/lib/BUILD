cc_library(
	name = "polygon",
	srcs = glob(["*.cc"]),
	hdrs = glob(["*.h"]),
	copts = ["-std=c++14", "-Wall", "-Wextra", "-Weffc++", "-Ithird_party/GSL/include"],
	deps = ["//third_party/GSL:gsl"],
	visibility = ["//test:__pkg__"],
)
