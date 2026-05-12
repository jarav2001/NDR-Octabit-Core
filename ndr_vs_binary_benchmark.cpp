#include <benchmark/benchmark.h>
#include <stdint.h>

// Arquitectura NDR-Base8: Conmutación Radial
typedef uint8_t octabit_t;

static inline octabit_t ndr_rotate(octabit_t estado) {
    // Operación atómica de rotación (El octágono rotando)
    return (estado << 1) | (estado >> 7);
}

// TEST 1: Arquitectura NDR (Tiempo Constante O(1))
static void NDR_64_States(benchmark::State& state) {
  octabit_t x = 0x01, y = 0x01;
  for (auto _ : state) {
    // Procesamiento paralelo de dos octavitas
    uint16_t res = (uint16_t)(ndr_rotate(x) << 8) | ndr_rotate(y);
    benchmark::DoNotOptimize(res);
  }
}
BENCHMARK(NDR_64_States);

// TEST 2: Lógica Binaria Tradicional (Árbol de Decisión)
static void Binary_Decision_Tree(benchmark::State& state) {
  uint8_t input = 32; 
  for (auto _ : state) {
    uint8_t result;
    if (input < 32) {
        if (input < 16) result = 1; else result = 2;
    } else {
        if (input < 48) result = 3; else result = 4;
    }
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(Binary_Decision_Tree);

BENCHMARK_MAIN();
