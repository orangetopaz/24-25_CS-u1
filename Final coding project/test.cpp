#include <iostream>
#include <variant>
#include <string>
#include <vector>

using namespace std;

struct Variable {
    string name;
    variant<int, float, string> value;  // Your variant type
};

// Function to print the variable and its type
void printVariable(const Variable& var) {
    cout << var.name << " = ";
    
    // Use std::visit to determine the type and print accordingly
    visit([&](auto&& arg) {
        using T = decay_t<decltype(arg)>;  // Get the underlying type
        cout << arg;  // Print the value

        // Print the type based on the variant type
        if constexpr (is_same_v<T, int>) {
            cout << " (int)";
        } else if constexpr (is_same_v<T, float>) {
            cout << " (float)";
        } else if constexpr (is_same_v<T, string>) {
            cout << " (string)";
        }
    }, var.value);  // Pass the variant to visit
    cout << endl;
}

int main() {
    // Create a vector of variables
    vector<Variable> variables = {
        {"x", 10},                 // int
        {"y", 3.14f},             // float
        {"z", string("Hello")}     // string
    };

    // Print each variable with its type
    for (const auto& var : variables) {
        printVariable(var);
    }

    return 0;
}
