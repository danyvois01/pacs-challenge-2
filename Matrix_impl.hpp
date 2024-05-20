#ifndef MATRIX_IMPL_HPP
#define MATRIX_IMPL_HPP
// clang-format off
#include <iostream>
#include <iomanip>

#include "Matrix.hpp"

namespace algebra {

    /// Resize the matrix to the specified number of rows and columns
    template<typename T, StorageOrder Order>
    void Matrix<T, Order>::resize(std::size_t numRows, std::size_t numCols) {
        // Update the number of rows and columns
        rows = numRows;
        cols = numCols;
        // Clear the existing data
        data_map.clear();
        val.clear();
        inner_idx.clear();
        outer_idx.clear();
        //@note This is not what the user expects when resizing a matrix. You should keep the original data if the resized matrix is larger. 
        // Of course this is easy to do only if you are in an uncompressed state.
        //Here you are not resizing, you are setting the matrix to zero.
        // Moreover, remember that for vectors, clear() does not free memory. You need to use shrink_to_fit() to free memory after clear().
    }

    /// Compress the matrix
    template<typename T, StorageOrder Order>
    void Matrix<T, Order>::compress() {
        // Check if the matrix is already compressed
        if (is_compressed()) {
            return;
        }
        // Clear existing compressed storage
        val.clear();
        inner_idx.clear();
        outer_idx.clear();
        //@note You need shrink_to_fit() here to free memory.

        std::size_t nnz = data_map.size();

        // Preallocate memory for val, outer_idx, and inner_idx
        val.resize(nnz);
        outer_idx.resize(nnz);
        inner_idx.resize((Order == StorageOrder::RowMajor) ? rows + 1 : cols + 1);

        int n_nnz = 0;
        std::size_t current_outer_index = 0;

        if constexpr (Order == StorageOrder::RowMajor) {
            for (const auto& entry : data_map) {
                const auto& indices = entry.first;
                const auto& value = entry.second;

                // Check if we moved to the next row 
                //@todo you do not need to be so complicated.
                // std::map has methods lower_bound and upper_bound that can be used to find the range of elements in a row (column).
                // and simplify a lot the code.
                if (indices[0] != current_outer_index) {
                    current_outer_index = indices[0];
                    inner_idx[current_outer_index] = n_nnz;
                }

                // Store the value and the column index
                val[n_nnz] = value;
                outer_idx[n_nnz] = indices[1];
                ++n_nnz;
            }
        } else { // Order == StorageOrder::ColumnMajor
            for (const auto& entry : data_map) {
                const auto& indices = entry.first;
                const auto& value = entry.second;

                // Check if we moved to the next column
                if (indices[1] != current_outer_index) {
                    current_outer_index = indices[1];
                    inner_idx[current_outer_index] = n_nnz;
                }

                // Store the value and the row index
                val[n_nnz] = value;
                outer_idx[n_nnz] = indices[0];
                ++n_nnz;
            }
        }

        // Assign the last element to the inner index
        inner_idx[current_outer_index + 1] = n_nnz;

        // Clear the data_map to avoid waste of memory
        data_map.clear();
    }

    /// Uncompress the matrix from either CSR or CSC format
    template<typename T, StorageOrder Order>
    void Matrix<T, Order>::uncompress() {
        // Check if the matrix is already uncompressed
        if (!is_compressed()) {
            return;
        }
        // Clear the existing data map
        data_map.clear();

        // Uncompress the matrix from row-major order (CSR format)
        if constexpr (Order == StorageOrder::RowMajor) {
            // Iterate over each row
            for (size_t i = 0; i < rows; ++i) {
                // Iterate over each non-zero element in the row
                for (size_t j = inner_idx[i]; j < inner_idx[i + 1]; ++j) {
                    // Add the value to the data map
                    std::array<std::size_t, 2> index = {i, outer_idx[j]};
                    data_map[index] = val[j];
                    //@note why not simply data_map[{i, outer_idx[j]}] = val[j];
                }
            }
        }
        // Uncompress the matrix from column-major order (CSC format)
        else {
            // Iterate over each column
            for (size_t i = 0; i < cols; ++i) {
                // Iterate over each non-zero element in the column
                for (size_t j = inner_idx[i]; j < inner_idx[i + 1]; ++j) {
                    // Add the value to the data map
                    std::array<std::size_t, 2> index = {outer_idx[j], i};
                    data_map[index] = val[j];
                }
            }
        }

        // Clear the compressed storage to free up memory
        val.clear();
        inner_idx.clear();
        outer_idx.clear();
    }

    // Check if the matrix is compressed
    template<typename T, StorageOrder Order>
    bool Matrix<T, Order>::is_compressed() const {
        // The matrix is compressed if the val vector is not empty
        return !val.empty();
    }

    /// Print the matrix
    template<typename T, StorageOrder Order>
    void Matrix<T, Order>::print() const {
        // If the matrix is not compressed
        if (!is_compressed()) {
            std::cout << "Matrix:" << std::endl;
            // Iterate over each row
            for (size_t i = 0; i < rows; ++i) {
                // Iterate over each column
                for (size_t j = 0; j < cols; ++j) {
                    // Print the element at (i, j)
                    std::cout << std::setw(4) << (*this)(i, j) << " ";
                }
                // Move to the next line after printing each row
                std::cout << std::endl;
            }
        }
            // If the matrix is compressed
        else {
            // Print the compressed matrix in CSR or CSC format
            if constexpr (Order == StorageOrder::RowMajor)
                std::cout << "Compressed matrix in CSR format:" << std::endl;
            else
                std::cout << "Compressed matrix in CSC format:" << std::endl;

            // Print the val vector
            std::cout << "val: [ ";
            for (auto& ele: val)
                std::cout << ele << " ";
            std::cout << "]" << std::endl;

            // Print the outer_idx vector
            std::cout << "outer_idx: [ ";
            for (auto& ele: outer_idx)
                std::cout << ele << " ";
            std::cout << "]" << std::endl;

            // Print the inner_idx vector
            std::cout << "inner_idx: [ ";
            for (auto& ele: inner_idx)
                std::cout << ele << " ";
            std::cout << "]" << std::endl;
        }
    }

} // namespace algebra

#endif