# RadonFramework
The main goal of this framework is to simplify the development of a game engine and the necessary toolkit.

The priority order for code is performance, usability, memory usage.

System dependent code is wrapped in the System namespace and will be dispatched at runtime, to get the best option on the running system.

The advantage of the runtime dispatching is the capability to partially port to an other platform, compile and run it, because only not implemented system functions which are called will be crash.

The framework takes use of cpu extensions like SSE2(memory operations), SSE4.2(strings processing), NEON and some more.
It's designed and optimized to run on 64Bit but can be used for 32Bit too.

An C++11 compiler is necessary to compile the code.

The major effort is spend to string/text processing, network communication, multi tasking, window and render context support.

The OpenGL bindings are generated from the specification files of the Khronos group and will be dispatched at runtime to reduce the binary size compared to other extension wrapper.

# Installation
* Install cmake and git
* Get the repo with `git clone https://github.com/tak2004/RadonFramework.git`
* Go into the build directory and create the build files for your build system e.g. `cmake -G "Unix Makefiles" ../`
* Open the generated ide project file or run the generated build script e.g. `make`
* The static library and all tests will be compiled and placed into the dist directory.

# Using

To simplify the project creation and integration the Radon framework use the Radon CMake framework.

It consists of a short Integration.cmake script which loads the [repository](https://github.com/tak2004/RadonCMakeFramework) into the DownloadedDependencies directory of your build location.

You can load the [example project](https://github.com/tak2004/RadonFrameworkExample).
