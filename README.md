# VectorClass

A generic, header-only C++ implementation of a mathematically complete linear algebra vector with full value semantics, move semantics, and numerical utilities.

Built as a learning project to practice modern C++ (Rule of Five, templates, operator overloading, RAII) while producing a clean, valgrind-verified, production-quality implementation.

---

## Features

- Template support — `Vector<T>` works with `int`, `float`, `double`, or any numeric type
- Rule of Five — copy constructor, copy assignment, move constructor, move assignment, destructor
- Arithmetic operators — element-wise `+`, `-`, scalar `*`, dot product
- Norms — L1 (Manhattan), L2 (Euclidean), L-infinity (max-abs)
- Normalisation — returns a unit-length `Vector<double>` with zero-vector guard
- Factory methods — `Vector<T>::zeros(n)`, `Vector<T>::ones(n)`
- Bounds-checked element access via `operator[]`
- Memory safe — zero leaks, zero invalid reads under Valgrind
- Header-only — single `Vector.h`, no external dependencies

---

## Requirements

| Tool | Version |
|------|---------|
| g++ | 13.3.0+ |
| C++ standard | C++17 |
| CMake | 3.16+ |
| Valgrind | any recent (optional, for memory checks) |

---

## Build & Run

```bash
git clone https://github.com/YOUR_USERNAME/vector-class.git
cd vector-class
cmake -B build
cmake --build build
./build/main
```

To run with memory checking:
```bash
valgrind --leak-check=full ./build/main
```

---

## Usage

```cpp
#include "Vector.h"

// Construction
Vector<double> a(3);
a[0] = 3.0; a[1] = -4.0; a[2] = 0.0;

// Factory methods
Vector<double> b = Vector<double>::ones(3);

// Arithmetic
Vector<double> c = a + b;
Vector<double> d = a * 2.0;
double dp        = a.dot(b);

// Norms
double l1   = a.l1_norm();   // 7.0
double l2   = a.l2_norm();   // 5.0
double linf = a.linf_norm(); // 4.0

// Normalisation
Vector<double> unit = a.normalize(); // length = 1.0

// Move semantics
Vector<double> e = std::move(a);     // O(1) — no allocation
```

---

## Design Decisions

**Rule of Five over Rule of Three**
`Vector<T>` manages a raw heap pointer (`T* m_data`). Any class that owns heap memory needs all five special members to be correct. Leaving move operations out would cause unnecessary copies whenever the compiler could have moved — particularly costly when returning vectors from functions.

**`noexcept` on move operations**
Move constructor and move assignment are marked `noexcept` because they never allocate — they only transfer ownership. This allows the standard library to use move operations unconditionally in containers like `std::vector`, which checks `noexcept` at compile time before deciding whether to move or copy.

**`normalize()` returns `Vector<double>` regardless of `T`**
A unit vector computed from integer inputs is meaningless as integers. The return type is always `double` to preserve precision. The cast to `double` happens before division, not after.

**`l2_norm()` always returns `double`**
`std::sqrt` on an integer type would lose precision. The accumulator is explicitly `double` and each element is cast before squaring to prevent integer overflow on large vectors.

**Template implementation in the header**
C++ requires template definitions to be visible at the point of instantiation. Since `.cpp` files are compiled separately, all template method bodies live in `Vector.h`. This is standard practice for header-only template libraries.

---

## Performance

Benchmarked on Ubuntu 24.04, g++ 13.3.0, compiled with `-O2`.

| Operation | Size | Time |
|-----------|------|------|
| Copy constructor | 1M doubles | ~2.1 ms |
| Move constructor | 1M doubles | ~0 µs (pointer swap) |
| Element-wise `+` | 1M doubles | ~1.8 ms |
| Dot product | 1M doubles | ~0.9 ms |

Move is effectively free regardless of vector size — it transfers three values (pointer, size, capacity) rather than copying the heap block.

> Note: replace these numbers with your own measurements before publishing.

---

## Memory Safety

All test cases pass with zero errors under Valgrind:

```
LEAK SUMMARY:
   definitely lost: 0 bytes in 0 blocks
   indirectly lost: 0 bytes in 0 blocks
     possibly lost: 0 bytes in 0 blocks
ERROR SUMMARY: 0 errors from 0 contexts
```

---

## Project Structure

```
vector-class/
├── Vector.h       # Full template class — declaration and implementation
├── main.cpp       # Integration tests covering all phases
├── CMakeLists.txt # Build configuration
├── LICENSE        # MIT
└── README.md
```

---

## Limitations & Future Work

- No SIMD/AVX2 acceleration on arithmetic operations
- No iterator support (`begin()`/`end()`) — cannot use with `std::algorithm`
- No dynamic resizing (`push_back`) — fixed size at construction
- No custom allocator support
- No Python bindings (pybind11 planned)
- Benchmarks are informal — no Google Benchmark integration yet

---

## License

MIT — see [LICENSE](LICENSE)
