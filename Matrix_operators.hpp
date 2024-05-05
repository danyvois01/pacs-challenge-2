#ifndef MATRIX_OPERATORS_HPP
#define MATRIX_OPERATORS_HPP

#include <complex> // Include if using std::complex
#include "Matrix.hpp"

namespace algebra {

    /// Overloaded operator to access elements of the matrix
    template<typename T, StorageOrder Order>
    T& Matrix<T, Order>::operator()(std::size_t row, std::size_t col) {
        // Check if the indices are out of bounds
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Indices are out of bounds.");
        }

        // If the matrix is not compressed
        if (!is_compressed()) {
            return data_map[{row, col}];
        }
        // If the matrix is compressed
        else {
            if constexpr (Order == StorageOrder::RowMajor) {
                // Check if the element is present in the compressed representation
                for (size_t i = inner_idx[row]; i < inner_idx[row + 1]; ++i) {
                    if (outer_idx[i] == col) {
                        // Return the element from the compressed representation
                        return val[i];
                    }
                }
            } else {
                for (size_t i = inner_idx[col]; i < inner_idx[col + 1]; ++i) {
                    if (outer_idx[i] == row) {
                        // Return the element from the compressed representation
                        return val[i];
                    }
                }
            }
            // If the matrix is in compressed state, new elements cannot be added
            throw std::runtime_error("Cannot add new elements when the matrix is in compressed state.");
        }
    }

    /// Const version of operator() to access elements of the matrix
    template<typename T, StorageOrder Order>
    const T Matrix<T, Order>::operator()(std::size_t row, std::size_t col) const {
        // Check if the indices are out of bounds
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Indices are out of bounds.");
        }

        // If the matrix is not compressed
        if (!is_compressed()) {
            // Check if the element is present in the data map
            auto it = data_map.find({row, col});
            // If the element exists, return its value
            if (it != data_map.end()) {
                return it->second;
            }
                // If the element does not exist, return a zero value
            else {
                return T();
            }
        }
            // If the matrix is compressed
        else {
            if constexpr (Order == StorageOrder::RowMajor) {
                // Check if the element is present in the compressed representation
                for (size_t i = inner_idx[row]; i < inner_idx[row + 1]; ++i) {
                    if (outer_idx[i] == col) {
                        // Return the element from the compressed representation
                        return val[i];
                    }
                }
            } else {
                for (size_t i = inner_idx[col]; i < inner_idx[col + 1]; ++i) {
                    if (outer_idx[i] == row) {
                        // Return the element from the compressed representation
                        return val[i];
                    }
                }
            }
            // If the element is not present, return a zero value
            return T();
        }
    }


    /// Overloaded operator for matrix-vector multiplication
    template<typename T, StorageOrder Order>
    std::vector<T> operator*(const Matrix<T, Order> &mat, const std::vector<T> &vec) {
        // Check if the dimensions of the matrix and vector are compatible for multiplication
        if (mat.cols != vec.size()) {
            throw std::runtime_error("Error: Matrix and vector dimensions are not compatible for matrix-vector multiplication.");
        }

        // Initialize the result vector with zeros
        std::vector<T> result(mat.rows, T{});

        // If the matrix is compressed
        if (mat.is_compressed()) {
            if constexpr (Order == StorageOrder::RowMajor) {
                for (std::size_t i = 0; i < mat.rows; ++i) {
                    for (std::size_t j = mat.inner_idx[i]; j < mat.inner_idx[i + 1]; ++j) {
                        result[i] += mat.val[j] * vec[mat.outer_idx[j]];
                    }
                }
            } else {
                for (std::size_t j = 0; j < mat.cols; ++j) {
                    for (std::size_t i = mat.inner_idx[j]; i < mat.inner_idx[j + 1]; ++i) {
                        result[mat.outer_idx[i]] += mat.val[i] * vec[j];
                    }
                }
            }
        }
        // If the matrix is not compressed
        else {
            // Perform the multiplication using the data map
            for (const auto& entry : mat.data_map) {
                const auto& index = entry.first;
                const auto& value = entry.second;
                result[index[0]] += value * vec[index[1]];
            }
        }
        return result;
    }
}

#endif