# OCL.Core

[![License: BSL-1.0](https://img.shields.io/badge/license-BSL--1.0-blue.svg)](LICENSE_1_0.txt)

Core module of the **Open C++ Libraries (OCL)**, a collection of modern C++20 utilities built on top of Boost. Covers error handling, memory management, hashing, math, I/O, and cross-platform compatibility.

## Requirements

| Tool | Notes |
|------|-------|
| [CMake](https://cmake.org/) ≥ 3.22.1 | Build system |
| [Clang](https://clang.llvm.org/) | Preferred compiler |
| [Boost](https://www.boost.org/) | Core dependency |
| [Git](https://git-scm.com/) | Source checkout |

C++20 is required (`CMAKE_CXX_STANDARD 20`).

## Building

```sh
git clone <repo-url> ocl-core
cd ocl-core
cmake -B build
cmake --build build
```

**CMake options:**

| Option | Effect |
|--------|--------|
| `INSTALL_OCL=ON` | Install headers and targets via `install_core.cmake` |
| `EXTENSIONS_CXX_OCL=ON` | Enable compiler-specific C++ extensions (off by default) |

## Components

### `ocl::basic_option`, Error handling monad

Wraps a `return_type` (`okay` / `err`) and throws on unwanted states. Use `eval_eq` to construct from a comparison, then `expect` to assert success.

```cpp
#include <ocl/option_fwd.hpp>

// throws if the two pointers are equal (both null)
ocl::option opt{ocl::eval_eq(nullptr, nullptr)};
opt.expect("option::incorrect");

// custom error callable instead of the default throw
ocl::option opt2{ocl::eval_eq(argv, nullptr)};
opt2.expect<MyErrorHandler>("option::incorrect");
```

### `ocl::smart_ptr`, Smart pointer aliases

Thin wrappers over the standard smart pointers plus a `delete_ptr` that holds a raw pointer without taking ownership (uses `boost::null_deleter`).

```cpp
#include <ocl/smart_ptr.hpp>

ocl::smart_ptr::unique_ptr<Foo> u = std::make_unique<Foo>();
ocl::smart_ptr::shared_ptr<Bar> s = std::make_shared<Bar>();

Bar b;
auto non_owning = ocl::smart_ptr::delete_ptr(&b); // shared_ptr that won't delete b
```

### `ocl::crc_hash`, CRC-32 hashing

Compile-time CRC-32 via the `_crc32` UDL; runtime hashing through `std::hash<ocl::crc_hash_trait>`.

```cpp
#include <ocl/crc_hash_fwd.hpp>
#include <ocl/print_fwd.hpp>

ocl::io::print("Hello, World!\n"_crc32);           // compile-time CRC-32

std::hash<ocl::crc_hash_trait> h{};
ocl::io::print(h.operator()<true, false>(argv[1])); // runtime CRC-32
```

### `ocl::scientific`, Math and equation solving

Arithmetic helpers (`add`, `div`, …) and equation/inequality solvers.

```cpp
#include <ocl/math_fwd.hpp>

ocl::scientific::solver::eq_solver_two solver;
solver(4, {ocl::scientific::add(2, 2)});  // true
solver(1, {ocl::scientific::add(2, 2)});  // false

ocl::scientific::solver::ineq_solver_two ineq;
ineq(5, {ocl::scientific::div(2, sqrt_two)});
```

### `ocl::placeholders`, Template string substitution

Find-and-replace for `${key}`-style placeholders in strings.

```cpp
#include <ocl/asio_fwd.hpp>

auto path = ocl::placeholders::find_and_replace(
    "${compiler.name}", "/usr/bin/g++", "compiler.name");
```

### `ocl::asio`, Boost.Asio helpers

Thin wrappers for running `io_context` loops with callable callbacks.

### `ocl::io`, I/O utilities

`ocl::io::print` / `ocl::io::println` and `ocl::io::enable_stdio_sync`.

### Platform compatibility (`ocl/compat/core/`)

Headers for platform-specific code paths:

| Header | Platform |
|--------|----------|
| `posix.hpp` | POSIX (Linux, macOS) |
| `win_nt.hpp` | Windows NT |
| `ne_system.hpp` / `ne_ant.hpp` | NeAnt |
| `ant_os.hpp` | Ant |

## Freestanding Status

OCL tracks which headers are usable in freestanding (no OS) environments.

| Status | Headers |
|--------|---------|
| Half-Verified | `option_fwd.hpp`, `is_same` |

## License

Distributed under the [Boost Software License 1.0](LICENSE_1_0.txt).

&copy; 2023–2026 Amlal El Mahrouss, Ne.app, and OCL Authors.
