#include <benchmark/benchmark.h>
#include <stdint.h>

// --- TU ARQUITECTURA NDR ---
typedef uint8_t octabit_t;

// Definimos la función una sola vez
static inline octabit_t ndr_rotate(octabit_t estado) {
    // Rotación circular: el bit que sale por la izquierda entra por la derecha
    return (estado << 1) | (estado >> 7);
}

// 1. Benchmark de tu arquitectura NDR (64 estados con dos octavitas)
static void NDR_64_States(benchmark::State& state) {
  octabit_t x = 0x01, y = 0x01;
  for (auto _ : state) {
    // Operación matricial paralela: rotamos y empaquetamos en 16 bits
    uint16_t res = (uint16_t)(ndr_rotate(x) << 8) | ndr_rotate(y);
    benchmark::DoNotOptimize(res);
  }
}
BENCHMARK(NDR_64_States);

// 2. Benchmark de Lógica Binaria (Árbol de decisión tradicional)
static void Binary_Decision_Tree(benchmark::State& state) {
  uint8_t input = 32; 
  for (auto _ : state) {
    uint8_t result;
    // El procesador tiene que evaluar múltiples ramas (saltos condicionales)
    if (input < 32) {
        if (input < 16) result = 1; else result = 2;
    } else {
        if (input < 48) result = 3; else result = 4;
    }
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(Binary_Decision_Tree);
