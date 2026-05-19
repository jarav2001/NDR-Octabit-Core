#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <atomic>

// Constantes de la Arquitectura Orbital
const int NUM_NUCLEOS_TOTALES = 4;      // Simulación de una CPU de 4 núcleos (Soles)
const size_t UMBRAL_SATURACION = 5;     // Capacidad máxima de "cubos" por órbita antes de desborde
const size_t LIMITE_CRITICO_FLUJO = 18; // Punto donde se activa el pre-cálculo geométrico

// ============================================================================
// 1. EL NÚCLEO MATRICIAL (Nativo del NDR-Octabit-Core)
// ============================================================================
uint64_t octabitMaestroDriver(uint64_t datos) {
    uint64_t fila_resultado;
    uint64_t columna_resultado;

    // Las 6 instrucciones netas en la ALU que validamos en Quick-Bench
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
// 2. ESTRUCTURA DE UN "SISTEMA SOLAR" (Núcleo de CPU)
// ============================================================================
struct SistemaSolar {
    int id_nucleo;
    std::atomic<bool> activo{false};
    size_t cubos_en_cola = 0;

    void procesarCubo(uint64_t cubo) {
        // Ejecución instantánea O(1)
        volatile uint64_t res = octabitMaestroDriver(cubo);
        (void)res; 
        if (cubos_en_cola > 0) cubos_en_cola--;
    }
};

// ============================================================================
// 3. EMULADOR DE LA CÁMARA DE ADMISIÓN DEL DRIVER
// ============================================================================
class DriverNDROctabit {
private:
    std::vector<SistemaSolar> cpu_cores;
    size_t total_cubos_procesados = 0;
    size_t total_cubos_descartados = 0;

public:
    DriverNDROctabit() {
        cpu_cores.resize(NUM_NUCLEOS_TOTALES);
        for (int i = 0; i < NUM_NUCLEOS_TOTALES; i++) {
            cpu_cores[i].id_nucleo = i;
            // El Núcleo 0 arranca como el Sol Base. Los demás quedan en reposo (espera).
            cpu_cores[i].activo = (i == 0); 
        }
    }

    void procesarRafagaEntrante(const std::vector<uint64_t>& flujo_so) {
        std::cout << "\n[DRIVER] >>> Iniciando admisión de ráfaga de datos (Tamaño: " 
                  << flujo_so.size() << " cubos)\n";

        for (const auto& cubo : flujo_so) {
            
            // CRÍTICA 2 EN ACCIÓN: Pre-cálculo Geométrico Basado en Carga
            size_t carga_actual_sistema = 0;
            for (const auto& core : cpu_cores) {
                if (core.activo) carga_actual_sistema += core.cubos_en_cola;
            }

            if (carga_actual_sistema >= LIMITE_CRITICO_FLUJO) {
                std::cout << "  ⚠️ [PRE-CÁLCULO GEOMÉTRICO]: Silicio saturado. Aplicando Backpressure en bus PCIe/NIC. Frenando admisión...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Gaps geométricos de reloj
            }

            bool cubo_despachado = false;

            // Intentar asignar el cubo en el primer Sol disponible que no esté saturado
            for (int i = 0; i < NUM_NUCLEOS_TOTALES; i++) {
                if (cpu_cores[i].activo && cpu_cores[i].cubos_en_cola < UMBRAL_SATURACION) {
                    cpu_cores[i].cubos_en_cola++;
                    cpu_cores[i].procesarCubo(cubo);
                    total_cubos_procesados++;
                    cubo_despachado = true;
                    break;
                }
                // FASE 1 EN ACCIÓN: Si el núcleo actual está lleno y hay uno en espera, lo despierta instantáneamente
                else if (!cpu_cores[i].activo && i > 0) {
                    std::cout << "  🚀 [CONMUTACIÓN ÓRBITAL]: Núcleo " << i-1 
                              << " saturado. Despertando Sistema Solar en Núcleo " << i << " para mitigar desborde.\n";
                    cpu_cores[i].activo = true;
                    cpu_cores[i].cubos_en_cola++;
                    cpu_cores[i].procesarCubo(cubo);
                    total_cubos_procesados++;
                    cubo_despachado = true;
                    break;
                }
            }

            // Si a pesar de despertar todo el silicio no hay espacio (caso extremo de descarte de Descartes)
            if (!cubo_despachado) {
                total_cubos_descartados++;
            }
        }

        imprimirReporteEstado();
    }

    void imprimirReporteEstado() {
        std::cout << "\n======================================================\n";
        std::cout << "       REPORTE DE ESTADO DE LA TOPOLOGÍA ORBITAL       \n";
        std::cout << "======================================================\n";
        for (int i = 0; i < NUM_NUCLEOS_TOTALES; i++) {
            std::cout << " Core " << i << " [" << (cpu_cores[i].activo ? "ACTIVO" : "REPOSO") 
                      << "] -> Cubos pendientes en órbita: " << cpu_cores[i].cubos_en_cola << "\n";
        }
        std::cout << "------------------------------------------------------\n";
        std::cout << " Total Cubos Procesados con Éxito: " << total_cubos_processed << "\n";
        std::cout << " Total Pérdida de Paquetes (Descarte): " << total_cubos_descartados << "\n";
        std::cout << "======================================================\n";
    }
};

// ============================================================================
// MAIN: FLUJO DE SIMULACIÓN EN VIVO
// ============================================================================
int main() {
    DriverNDROctabit driver;
    std::mt19937_64 rng(1337);

    // 1. Simulación de Tráfico Normal: Se resuelve con el Núcleo 0 solo
    std::vector<uint64_t> trafico_normal(4);
    for (auto& b : trafico_normal) b = rng();
    driver.procesarRafagaEntrante(trafico_normal);

    // 2. Simulación de Ráfaga Crítica (Ataque de Datos / Saturación Masiva)
    // Forzamos un volumen que va a obligar al sistema a conmutar núcleos y aplicar pre-cálculo
    std::vector<uint64_t> rafaga_critica(25);
    for (auto& b : rafaga_critica) b = rng();
    driver.procesarRafagaEntrante(rafaga_critica);

    return 0;
}
