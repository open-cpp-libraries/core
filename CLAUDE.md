# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

OCL.Core is a header-only C++ library providing core containers and utilities. It is part of the OCL (Open C++ Libraries) project, licensed under the Boost Software License.

**Key characteristics:**
- Header-only library (all code in `include/ocl/`)
- Requires C++20 or greater
- Uses Boost extensively for cross-platform functionality
- Supports freestanding mode via `OCL_FREESTANDING` macro
- All headers follow include guard pattern `OCL_CORE_*`

## Build System & Commands

### Testing

Tests use Boost.Test framework and are built with Boost.Build (b2):

```bash
# Build and run all tests
cd test
b2

# Build specific test
b2 option.test.o
b2 allocator_op.test.o

# Clean tests
b2 --clean

# Run compiled test directly
./bin/*/option.test.o
./bin/*/allocator_op.test.o
```

Tests use `BOOST_AUTO_TEST_CASE` and include Boost.Test with:
```cpp
#define BOOST_TEST_MODULE <module_name>
#include <boost/test/included/unit_test.hpp>
```

### Code Formatting

```bash
# Format all source files using clang-format
./format.sh
```

Code style: Microsoft-based with tabs, unlimited column width, pointer alignment left.

### Compilation Requirements

- C++20 standard (`-std=c++20`)
- Boost headers must be in include path
- Include OCL headers: `-Iinclude/`
- Compiler: Clang (primary), GCC compatible

## Architecture & Core Components

### Library Structure

```
include/ocl/
├── detail/
│   └── config.hpp          # Core configuration, Boost includes, platform macros
├── option.hpp              # Result/error handling with eval predicates
├── allocator_op.hpp        # Memory pool allocators with custom allocator operations
├── smart_ptr.hpp           # Smart pointer aliases and helpers
├── tracked_ptr.hpp         # Strict pointer type with allocation tracking
├── crc_hash.hpp           # CRC32 hash implementation and hash maps
├── basic_hash.hpp         # Basic hashing utilities
├── equiv.hpp              # Equivalence utilities
├── print.hpp              # Printing utilities
└── io.hpp                 # I/O utilities
```

### Key Design Patterns

**1. Option/Result Pattern (`option.hpp`)**
- Similar to Rust's Result type but exception-based
- Uses `return_type` enum: `okay`, `err`, `invalid`
- Evaluation functions: `eval()`, `eval_eq()`, `eval_less_than()`, `eval_greater_than()`, `eval_true()`, `eval_false()`
- Call `expect()` to unwrap or throw on error
- Non-copyable, move-only semantics

**2. Memory Management**

Two allocation strategies:

a) **allocator_op.hpp** - Policy-based allocators:
```cpp
allocator_op<Type, NewOp, DeleteOp>  // Generic
allocator<Type>                       // Alias using global new/delete
```
Returns `std::shared_ptr` with custom deleters. Use `construct_array<N>()` or `construct_var(args...)`.

b) **tracked_ptr.hpp** - Allocation tracking:
```cpp
tracked_ptr<Type>                     // Move-only unique pointer
tracked_allocator<Type>               // Tracks allocated_count_ and deallocated_count_
tracked_mgr<Type>                     // Manager with retain/dispose
```
Use `make_tracked<Type>(args...)` factory. Provides runtime allocation/deallocation statistics.

**3. Smart Pointers (`smart_ptr.hpp`)**
- Type aliases for `std::unique_ptr` and `std::shared_ptr`
- `delete_ptr()` creates a shared_ptr with `boost::null_deleter` (no-op deletion)

**4. Hashing (`crc_hash.hpp`)**
- `crc_hash_trait::crc<uint32_t>(data, len)` for CRC32
- Custom `std::hash` specialization for CRC hashing
- Type aliases: `string_hash_map<V>`, `hash_map<K,V>`
- User-defined literal: `""_crc`

### Configuration System (`detail/config.hpp`)

Central configuration header that:
- Imports all Boost dependencies (except in freestanding mode)
- Defines platform macros (`OCL_WINDOWS`, `OCL_USE_CRLF_ENDINGS`)
- Export/visibility macros (`OCL_EXPORT_DECL`, `OCL_DECL`)
- Deprecation attributes (`OCL_DEPRECATED()`, `OCL_DEPRECATED_MSG()`)
- Common error throwing: `detail::throw_runtime_error(location)`

**Always include this first** in OCL headers.

### Freestanding Status

The library tracks "freestanding status" - whether components work without standard library:
- Currently **Half-Verified**: `option.hpp` and `is_same.hpp` (referenced but not in repo)
- Define `OCL_FREESTANDING` to disable Boost includes

## Development Guidelines

### Adding New Components

1. Create header in `include/ocl/`
2. Use include guard: `#ifndef OCL_CORE_<NAME>`
3. Include `ocl/detail/config.hpp` first
4. Place implementation in `ocl` namespace
5. Internal helpers go in `ocl::detail` namespace
6. Document with Doxygen-style comments (`@brief`, `@author`, `@note`)
7. File header should include: File, Purpose, Author, Copyright with BSL license

### Writing Tests

1. Create `*.test.cpp` in `test/` directory
2. Include the header under test
3. Define test module: `#define BOOST_TEST_MODULE <name>`
4. Use `BOOST_AUTO_TEST_CASE(test_name)` for test cases
5. Use `BOOST_TEST()` for assertions
6. Add test target to `test/Jamfile.v2`:
```
exe <name>.test.o
    : <name>.test.cpp
    : <cxxstd>20 ;
```

### Type Safety & Error Handling

- Use `option` for functions that can fail with error messages
- Use `tracked_ptr` when allocation tracking matters (debugging, resource limits)
- Use standard smart pointers for general ownership
- Mark evaluation functors as `noexcept` - failed predicates indicate undefined state
- Use `assert()` for invariant checks, exceptions for runtime errors
- Leverage `BOOST_CURRENT_LOCATION` for error location tracking

### Template Guidelines

- Policy-based design for customization (see `allocator_op`)
- Use concepts for constraints (`std::concepts`)
- Delete unwanted template specializations explicitly
- Prefer `std::forward` for perfect forwarding

## Repository Conventions

- Main branch: `stable` (use for PRs)
- Current branch: `develop`
- All authors tracked in `MailMap`
- License symlink: `LICENSE_1_0.txt` -> `LICENSE`
- Examples in `example/` subdirectories (not main development focus)
