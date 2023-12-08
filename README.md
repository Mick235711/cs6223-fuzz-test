# Fuzz Project for CS6223
This repo is intended as the implementation for the final project of Yihe Li in CS6223.
The project is about using mutation testing (fuzzing) to test the implementation of C++20 Ranges
in libstdc++, libc++ and range-v3.

Requirements:
- Clang 16+
- CMake 3.19+

To build and run:
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=RelWithDebug -DFUZZTEST_FUZZING_MODE=on ..
cmake --build .  # or make -jN
./range_property  # test for property mutators
./range_view_type_test  # test for view property correctness
./range_view_fuzz --fuzz=MyTestSuite.<view_name>  # fuzz the specific view
```
