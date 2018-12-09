cc_test(
  name = "cut-test",
  srcs = glob(["**/*.cc", "**/*.cpp", "**/*.h", "**/*.hpp"]),
  copts = ["-Itest/robot-cleaner/include", 
    "-Itest/quantity/include", 
    "-std=c++11", 
    "-g", 
    "-Wno-invalid-offsetof"],  
  deps = ["//:cut", "//:cut_main"],
)
