cc_library(
	name = "mirror",
	hdrs = glob(["include/*.hpp"]),
	strip_include_prefix = "include",
	visibility = [
		"//visibility:public",
	],
)

cc_library(
	name = "catch2",
	hdrs = ["test/catch.hpp"],
)

cc_test(
	name = "mirror_ut",
	srcs =  ["test/mirror.cpp"],
	deps = [":mirror", ":catch2"],
)
