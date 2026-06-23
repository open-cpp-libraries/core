# OCL.Core

[![License: BSL](https://img.shields.io/badge/license-BSL-blue.svg)](LICENSE)

The core set of containers from the OCL. These containers are used to develop modern C++ applications on top of Boost based ones.

It's easy to clone and get up and running. Use CMake for this!

## Requirements:

The OCL requires:

- [Boost](https://www.boost.org/)
- [Clang](https://clang.llvm.org/)
- [CMake](https://cmake.org/)
- [Git](https://git-scm.com/)

The OCL aims to be easily installable and to get up and running.

## Core by Examples:

You can have a look at the examples in order to get familiar with the library.

```cpp
int main(int argc, char** argv)
{
	ocl::option opt{ocl::eval_eq(nullptr, nullptr)};
	opt.expect("option::incorrect");

	opt = ocl::option{ocl::eval_eq(argv, nullptr)};
	opt.expect<invalid_callable>("option::incorrect");

	return 0;
}
```

This one implements an `ocl::option` container, which is used for error handling and other related tasks.

## Freestanding Status:

The Freestanding Status is a concept where a module is evaluated on whether it has or is fully freestanding or not.

- Half-Verified ({option, is_same}.hpp)

##### (c) 2023-2026 Amlal El Mahrouss and OCL Authors, licensed under the Boost Software License.
