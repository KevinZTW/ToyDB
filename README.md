# Toy DB

Aiming to build a simple, naive RDBMS to deepen my understanding.

## Build

To build and test the Toy DB project, follow these steps:

```
cd src
mkdir build
cd build
cmake ..
make

# Run tests
ctest
```

## Glossary

- **Page**: The basic unit of data storage on disk with a fixed size (e.g., 4KB)
- **Frame**: A fixed-size block of memory that is used for `BufferManager` to hold a page when it is read from disk. 