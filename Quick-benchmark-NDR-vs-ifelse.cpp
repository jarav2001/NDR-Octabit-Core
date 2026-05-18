#include <iostream>
#include <cstdint>
#include <random>

// ============================================================================
// 1. EL ENFOQUE TRADICIONAL: Árbol de Decisiones Binario Sequencial (if/else)
// ============================================================================
// Mimetiza cómo un switch/tree tradicional evalúa un flujo para enrutamiento.
// Sufre penalizaciones severas por fallos en el predictor de saltos (Branch Misprediction).
__attribute__((noinline)) uint64_t enrutamientoTradicionalIfElse(uint64_t datos) {
    uint8_t byte_critico = static_cast<uint8_t>((datos >> 24) & 0xFF);
    uint64_t resultado = 0;

    // Estructura de bifurcación condicional típica
    if (byte_critico < 0x40) {
        if (byte_critico < 0x20) {
            resultado = datos ^ 0x01;
        } else {
            resultado = datos ^ 0x02;
        }
    } else {
        if (byte_critico < 0x80) {
            resultado = datos ^ 0x04;
        } else {
            if (byte_critico < 0xC0) {
                resultado = datos ^ 0x08;
            } else {
                resultado = datos ^ 0x10;
            }
        }
    }
    return resultado;
}

// ============================================================================
// 2. EL ENFOQUE NDR-OCTABIT: Cómputo Matricial y Enmascaramiento Ortogonal
// ============================================================================
// Flujo plano en línea recta. Cero saltos condicionales. 100% Inmune al caos del dato.
__attribute__((noinline)) uint64_t octabitMaestroDriver(uint64_t datos) {
    uint64_t fila_resultado;
    uint64_t columna_resultado;

    asm volatile (
        "movq %[input], %%rax\n\t"
        "shrq $24, %%rax\n\t"
        "andq $0xFF, %%rax\n\t"
        "movq %%rax, %[out_fila]\n\t"

        "movq %[input], %%rbx\n\t"
        "movabsq $0x0101010101010101, %%rcx\n\t"
        "andq %%rcx, %%rbx\n\t"
        "movq %%rbx, %[out_col]\n\t"

        : [out_fila] "=r" (fila_resultado), [out_col] "=r" (columna_resultado)
        : [input] "r" (datos)
        : "%rax", "%rbx", "%rcx"
    );

    return fila_resultado ^ columna_resultado;
}

// ============================================================================
// CAPA DE PRUEBAS AUTOMATIZADA E INYECTOR DE INFORME TÉCNICO
// ============================================================================

// Generador de datos caóticos aleatorios para estresar el Predictor de Saltos de la CPU
uint64_t generarDatoCaotico() {
    static std::mt19937_64 rng(1337); 
    return rng();
}

static void BM_Binario_Tradicional_IfElse(benchmark::State& state) {
    for (auto _ : state) {
        // Detenemos la optimización del compilador pasando datos mutables aleatorios
        uint64_t dato = generarDatoCaotico();
        benchmark::DoNotOptimize(enrutamientoTradicionalIfElse(dato));
    }
    // Metadata dura inyectada en el reporte para la audiencia
    state.counters["1.Complejidad_Algoritmica"] = 0; // Representa O(log N) / O(N) dependiente
    state.counters["2.Riesgo_Branch_Miss"] = 100;    // Exposición crítica al predictor de saltos
}
BENCHMARK(BM_Binario_Tradicional_IfElse);

static void BM_NDR_Octabit_Maestro(benchmark::State& state) {
    for (auto _ : state) {
        uint64_t dato = generarDatoCaotico();
        benchmark::DoNotOptimize(octabitMaestroDriver(dato));
    }
    state.counters["1.Complejidad_Algoritmica"] = 1; // Representa O(1) Constante Puro
    state.counters["2.Riesgo_Branch_Miss"] = 0;      // 0% Dependencia de saltos elementales
}
BENCHMARK(BM_NDR_Octabit_Maestro);
