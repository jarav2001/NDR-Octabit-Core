#include <iostream>
#include <chrono>
#include <vector>

// Lógica Tradicional (Árbol de Decisión)
int binary_logic(int input) {
    if (input == 0) return 10;
    else if (input == 1) return 20;
    else if (input == 2) return 30;
    else if (input == 3) return 40;
    else if (input == 4) return 50;
    else if (input == 5) return 60;
    else if (input == 6) return 70;
    return 80;
}

// Lógica NDR-Base8 (Acceso Directo por Índice)
int ndr_logic(int input, const int* table) {
    return table[input]; // O(1) puro
}

int main() {
    const int iterations = 100000000;
    int ndr_table[] = {10, 20, 30, 40, 50, 60, 70, 80};
    
    // Test Binario
    auto s1 = std::chrono::high_resolution_clock::now();
    for(int i=0; i<iterations; ++i) binary_logic(i % 8);
    auto e1 = std::chrono::high_resolution_clock::now();
    
    // Test NDR
    auto s2 = std::chrono::high_resolution_clock::now();
    for(int i=0; i<iterations; ++i) ndr_logic(i % 8, ndr_table);
    auto e2 = std::chrono::high_resolution_clock::now();

    std::cout << "Binario: " << std::chrono::duration<double>(e1-s1).count() << "s" << std::endl;
    std::cout << "NDR-Base8: " << std::chrono::duration<double>(e2-s2).count() << "s" << std::endl;

    return 0;
}
