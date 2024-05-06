# pacs-challenge-2

## A sparse matrix class

This repository hosts the second assignment of the APSC course 2023-2024.

The C++ program implements a class which is designed to represent a dynamic sparse matrix with flexible storage ordering. The class is implemented in the **algebra** namespace.

## Requirements

- C++ compiler with C++11 support.
- [JSON for Modern C++](https://github.com/nlohmann/json) library for JSON file parsing.

## Features

- Dynamic construction of sparse matrices.
- Capable of storing elements in row-wise or column-wise order.
- Provides methods for compression, decompression, resizing, and checking compression status.
- Includes friend operators for matrix-vector multiplication.

## Project Overview

The project consists of the following files:

1. **Matrix.hpp**:
   - Defines the `Matrix` class for representing a sparse matrix.
   - Includes method declarations for compression, element extraction, and more.

2. **Matrix_impl.hpp**:
   - Implements the following methods of the `Matrix` class defined in `Matrix.hpp`:
     - `resize`: Resizes the matrix to the specified number of rows and columns.
     - `compress`: Compresses the matrix.
     - `uncompress`: Uncompresses the matrix from either CSR or CSC format.
     - `is_compressed`: Checks if the matrix is compressed.
     - `print`: Prints the matrix.

3. **Matrix_operators.hpp**:
   - Defines the following operators for the `Matrix` class:
     - `operator()`: Overloaded for accessing matrix elements.
     - `operator*`: Overloaded for matrix-vector multiplication.

4. **Matrix_reader.hpp**:
   - Contains the method for reading a matrix from a file in Matrix Market format.

5. **test.hpp**:
   - Contains test functions.

## Usage

The program will read parameters from a JSON file named `storage_order.json`. This file should contain a key `storage_order`, where:
   - `0` indicates RowMajor storage order.
   - `1` indicates ColumnMajor storage order.

1. Clone the repository.
2. Compile and execute the program with the following command:

```
make run
```

## Output

Upon execution, the program performs the following steps:

- Reads the storage order from `storage_order.json`.
- Initializes a sparse matrix based on the specified storage order.
- Populates the matrix with values.
- Prints the original matrix.
- Compresses the matrix.
- Prints the compressed matrix.
- Uncompresses the matrix.
- Prints the uncompressed matrix.
- Reads a matrix from a file in Matrix Market format.
- Performs matrix-vector multiplication before compression and measures the time taken.
- Compresses the matrix.
- Performs matrix-vector multiplication after compression and measures the time taken.
- Outputs the compression time, matrix-vector product time before compression, and matrix-vector product time after compression.

## Example Output

Selected storage order: RowMajor
Original matrix:
0  2  0  3
0  4  5  0
0  0  0  6

Compressed matrix:
[Compressed matrix output]

Uncompressed matrix:
[Uncompressed matrix output]

Matrix from file "lnsp_131.mtx":
[Matrix from file output]

Compression time: [time] microseconds
Matrix-vector product before compression took: [time] microseconds
Matrix-vector product after compression took: [time] microseconds

