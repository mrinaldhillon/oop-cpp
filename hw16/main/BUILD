cc_binary(
	name = "shell",
	srcs = glob(["shell_main.cc"]),
	copts = ["-std=c++17", "-Wall", "-Wextra", "-Weffc++", "-Wno-non-virtual-dtor"],
    	deps = [
        "//lib:file-system",
	],
)
