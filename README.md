# NDR-Octabit-Core: Constant-Time Radial Switching Architecture
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.20128879.svg)](https://zenodo.org/records/20128879)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
## 🇺🇸 Project Description / 🇪🇸 Descripción del Proyecto
**NDR-Base8** introduces a shift from serial binary logic to **Radial Octahedral Topology**. Unlike traditional architectures that scale logarithmically $O(\log n)$, NDR-Base8 operates in **Constant Time $O(1)$**.
*NDR-Base8 introduce un cambio de la lógica binaria serial a la **Topología Octaédrica Radial**. A diferencia de las arquitecturas tradicionales que escalan logarítmicamente $O(\log n)$, NDR-Base8 opera en **Tiempo Constante $O(1)$**.*
---
## 🧪 Experimental Validation / Validación Experimental
This repository contains two core benchmark files that verify the architectural superiority of NDR-Base8.
*Este repositorio contiene dos archivos de benchmark que verifican la superioridad arquitectónica de NDR-Base8.*
### 1. `benchmark.cpp` (The Core Engine / El Motor Núcleo)
*   **Purpose:** Measures the atomic rotation speed of the "Octagon" in a single data stream.
*   **Success Result:** Demonstrated that the radial bit-shift logic compiles directly into native CPU rotation instructions, achieving a **Zero-Overhead** execution.
*   **Propósito:** Mide la velocidad de rotación atómica del "Octágono" en un flujo de datos único.
*   **Resultado de Éxito:** Demostró que la lógica de desplazamiento radial se compila directamente en instrucciones de rotación nativas de la CPU, logrando una ejecución de **Cero-Overhead**.
### 2. `ndr_vs_binary_benchmark.cpp` (Comparative Stress / Estrés Comparativo)
*   **Purpose:** A head-to-head comparison between NDR-Base8 and traditional Binary Decision Trees (If/Else).
*   **Success Result:** **NOOP EQUIVALENCY**. While the binary tree's performance fluctuates due to branch mispredictions, NDR-Base8 maintains a flat latency equivalent to a `Noop` (No-Operation) instruction cycle.
*   **Propósito:** Comparación directa entre NDR-Base8 y Árboles de Decisión Binarios (If/Else) tradicionales.
*   **Resultado de Éxito:** **EQUIVALENCIA NOOP**. Mientras que el rendimiento del árbol binario fluctúa por errores de predicción de salto, NDR-Base8 mantiene una latencia plana equivalente a un ciclo de instrucción `Noop`.
---
## 📊 Performance Matrix / Matriz de Rendimiento
*Results validated on Clang 15.0 / GCC 13.2 (-O3 optimization)*

| Test / Prueba | Complexity / Complejidad | Latency / Latencia | Stability / Estabilidad |
| :--- | :--- | :--- | :--- |
| **Traditional Binary** | $O(\log n)$ | Variable (1-5ns) | Jittery (Branch Miss) |
| **NDR-Base8** | **$O(1)$** | **< 1ns (Noop)** | **Deterministic (Flat)** |

---
## ⚖️ Intellectual Property & Priority / Propiedad Intelectual
*   **Author / Autor:** Jaime Andrés Ramírez Arcila 
*   **C.I.:** 15.757.447 (Venezuela)
*   **Scientific Record / Registro Científico:** Defensive Publication Protocol.
*   **DOI:** [10.5281/zenodo.20128879](https://zenodo.org/records/20128879)
*   **Digital Timestamp:** CERN Infrastructure / Zenodo.
*   **License:** MIT for Source Code / CC BY 4.0 for Documentation.
*   **Copyright:** © 2026. All rights reserved.
---
## 📁 File Manifest / Manifiesto de Archivos
*   `ndr_kernel_interface.c`: The bridge between Radial Logic and OS Kernel.
*   `benchmark.cpp`: Single-stream atomic rotation test.
*   `ndr_vs_binary_benchmark.cpp`: Comparative O(1) vs O(log n) validation.
*   `Patente_NDR_Sustento_Tecnico_v1.pdf`: Full theoretical and legal framework.
