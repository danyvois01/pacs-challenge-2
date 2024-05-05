#include <iostream>

#include "json.hpp" // JSON library
using json = nlohmann::json;

#include "Matrix.hpp"
#include "test.hpp"

int main() {

    using namespace algebra;

    // Read parameters from JSON file
    std::ifstream file("storage_order.json");
    json j = json::parse(file);

    int storage_order = j.value("storage_order", 0);

    if (storage_order == 0) {
        // Use RowMajor storage order
        std::cout << "Selected storage order: RowMajor" << std::endl;
        test<StorageOrder::RowMajor>();
    } else {
        // Use ColumnMajor storage order
        std::cout << "Selected storage order: ColumnMajor" << std::endl;
        test<StorageOrder::ColumnMajor>();
    }

    return 0;
}
