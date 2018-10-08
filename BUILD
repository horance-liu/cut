cc_library(
  name = "cut",
  srcs = glob(
      ["src/**/*.cc", "src/**/*.cpp"],
      exclude = ["src/cut/startup/main.cpp"]    
  ),
  hdrs = glob(["include/**/*.h", "include/**/*.hpp"]),
  copts = ["-Iinclude", "-std=c++14", "-Wno-invalid-offsetof"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "cut_main",
  srcs = ["src/cut/startup/main.cpp"],
  hdrs = [
      "include/cut/cut.h",
      "include/cut/startup/StartUp.h",
  ],
  copts = ["-Iinclude", "-std=c++14", "-Wno-invalid-offsetof"],
  visibility = ["//visibility:public"],
)
