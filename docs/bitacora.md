# Bitácora

## [2026-10-28] - Sesión 1: Análisis conceptual

**Quienes:**
  * Pablo Andres Bueno Ceron
  * Juan Eduardo Gómez Aguilar

**Trabajo realizado:**
  * Implementación del método `encolar()` con aritmética modular.

  * Creación de la plantilla inicial de `docs/informe-avance.md`.

**Pendiente:**
  * Redactar las citas del texto guía sobre el costo $O(1)$.

  * Diseñar las pruebas de caso límite.


## [2026-10-29] - Sesión 2: Casos de prueba y refinamiento de código

**Quiénes:**
* Pablo Andres Bueno Ceron
* Juan Eduardo Gómez Aguilar

**Trabajo realizado:**
* Adaptación del código fuente de la cola circular para procesar estructuras `Paciente` con `nombre` y `tiempoLlegada`, garantizando la medición del reloj interno.
* Refinamiento del `main` utilizando condicionales `if/else` estrictos para cumplir con la regla de un solo `return` y cero `break`/`continue`.
* Ejecución de los 6 casos de prueba (5 funcionales y 1 límite) documentados en el informe.

**Pendiente:**
* Revisión final de formato del informe (ortografía y ecuaciones LaTeX).
* Push del commit final.
**Pendiente:**
* Revisión final de formato del informe (ortografía y ecuaciones LaTeX).
* Push del commit final antes de la hora límite.


## [2026-10-30] - Sesión 3: Métodos base y destructor

**Quiénes:**
* Pablo Andres Bueno Ceron
* Juan Eduardo Gómez Aguilar

**Trabajo realizado:**
* Implementación de los métodos de validación de estado de la cola circular (`estaVacia()` y `estaLlena()`).
* Creación del destructor de la clase para asegurar la correcta liberación de la memoria dinámica.

**Pendiente:**
* Desarrollar el resto de los métodos principales del código (inserción, extracción y lógica del reloj).
* Terminar de pulir temas pendientes en el informe de avance y añadir algunas agregaciones extra.
* Aprovechar la extensión de la entrega (hasta el lunes) para organizar el código final y revisar detalles.


## [2026-10-31] - Sesión 4: Ajustes menores y comentarios guía

**Quiénes:**
* Juan Eduardo Gómez Aguilar

**Trabajo realizado:**
* Ajustes menores de formato en el archivo del código principal.
* Adición de comentarios guía dentro del código para documentar brevemente el propósito de cada método.

**Pendiente:**
* Hacer una revisión exhaustiva del informe de avance (`docs/informe-avance.md`).
* Terminar de verificar el funcionamiento completo del código con todos los casos de prueba.
* Realizar la integración y preparación final del repositorio para la entrega.


## [2026-11-01] - Sesión 5: Integración de operaciones clave y estructura del main

**Quiénes:**
* Pablo Andres Bueno Ceron

**Trabajo realizado:**
* Implementación de los métodos de inserción y extracción (`encolar()` y `desencolar()`) utilizando aritmética modular para garantizar la complejidad $O(1)$.
* Adición del método `obtenerCantidad()` para la consulta directa de elementos en la cola en tiempo constante.
* Estructuración inicial de la función `main()`, configurando la lectura del total de órdenes, la instanciación dinámica de la estructura y el control inicial del reloj interno.

**Pendiente:**
* Completar el procesamiento de las órdenes (`LLEGA`, `ATIENDE`, `ESPERAN`, `PROMEDIO`) dentro del ciclo principal del `main()`.
* Realizar los retoque finales al informe (`docs/informe-avance.md`) antes de la entrega de mañana.
* Correr la suite completa de casos de prueba y asegurar que la compilación no genere advertencias con `-Wall -Wextra`.


## [2026-11-02] - Sesión 6: Pruebas físicas, correcciones finales y entrega

**Quiénes:**
* Pablo Andres Bueno Ceron
* Juan Eduardo Gómez Aguilar

**Trabajo realizado:**
* Corrección de errores ortográficos, de redacción y de formato en el `docs/informe-avance.md`.
* Inclusión de la justificación formal de complejidad $O(1)$ citando el texto guía (CLRS, Cap. 10) y corrección de las fórmulas matemáticas en LaTeX.
* Generación de los 14 archivos físicos de prueba (`.in` y `.out`) y carga exitosa de los mismos dentro de la carpeta `datos/` del repositorio.
* Verificación de la integración del código fuente en `codigo/principal.cpp` y validación de la estructura final del repositorio en GitHub.

**Pendiente:**
* Ninguno (Entrega del avance finalizada con éxito).


## [2026-11-10] - Sesión 7 (Fase Final): Análisis de retroalimentación e introducción al Montículo Binario

**Quiénes:**
* Pablo Andrés Bueno Cerón
* Juan Eduardo Gómez Aguilar

**Trabajo realizado:**
* **Análisis de la retroalimentación del Avance:** Revisamos los comentarios del profesor. Identificamos que el error de compilación (`make`) fue causado por una llave `}` mal ubicada en `principal.cpp:31`. Confirmamos que la lógica de la cola circular es correcta.
* **Planeación de correcciones (Cola Circular):** Definimos los ajustes requeridos: corregir el error de sintaxis, almacenar la variable `urgencia` en el `struct Paciente` (ya que se estaba perdiendo), inicializar la capacidad de la cola para probar correctamente la aritmética modular, y actualizar la tabla de pruebas del informe (el caso `funcional3` debe dar `2.0` de espera).
* **Investigación teórica (Montículo Binario):** Iniciamos el estudio de la estructura requerida para la entrega final. Comprendimos que el montículo priorizará a los pacientes por su nivel de urgencia (Max-Heap) utilizando representación en arreglo. Definimos las ecuaciones de navegación para la implementación: hijo izquierdo `2i+1`, hijo derecho `2i+2` y padre `(i-1)/2`. 

**Pendiente:**
* Separar la clase `ColaCircular` en sus propios archivos (`.h` y `.cpp`) para compartir la misma interfaz con el futuro montículo.
* Modificar el código fuente de la entrega anterior para agregar la urgencia, remover la llave errónea y garantizar la compilación limpia con `make pruebas`.
* Comenzar a programar la clase del montículo binario implementando los métodos de flotar (inserción) y hundir (extracción).


## [2026-11-12] - Sesión 8 (Fase Final): Modularización de cabeceras e implementación del Montículo Binario

**Quiénes:**

* Pablo Andrés Bueno Cerón
* Juan Eduardo Gómez Aguilar

**Trabajo realizado:**

* **Reestructuración modular en cabeceras independientes:** Eliminamos la llave de cierre errónea en `principal.cpp` y separamos las estructuras en archivos independientes dentro de `codigo/`: `Paciente.h` (incorporando el atributo `urgencia` junto a `nombre` y `tiempoLlegada`), `ColaCircular.h` y `MonticuloBinario.h`.
* **Interfaz pública unificada:** Garantizamos que `ColaCircular` y `MonticuloBinario` expongan exactamente las mismas firmas (`encolar`, `desencolar`, `obtenerCantidad`, `estaLlena`, `estaVacia`) para permitir su intercambio limpio en `principal.cpp`.
* **Reimplementación y verificación de `ColaCircular`:** Reconstruimos la cola circular sobre arreglo dinámico (`new Paciente[capacidad]`) verificando el comportamiento circular con capacidad acotada para comprobar la vuelta modular de los índices `(frente + 1) % capacidad` y `(trasero + 1) % capacidad`.
* **Implementación desde cero de `MonticuloBinario`:** Programamos el Max-Heap sobre arreglo utilizando `tieneMayorPrioridad` (ordenando por mayor `urgencia` y desempatando por menor `tiempoLlegada`) y los métodos iterativos `flotar` (`sift-up`) y `hundir` (`sift-down`) en $O(\log n)$, cumpliendo estrictamente las restricciones de código del curso (sin `break`, `continue` ni múltiples `return`).

**Pendiente:**

* Actualizar los archivos de salida esperada en `datos/` (`funcional3.out`, `funcional5.out` y `funcional6.out`) para el comportamiento del montículo binario y validar con `make pruebas`.
* Ejecutar los experimentos comparativos de rendimiento en `datos/experimentos.csv` y redactar el informe final completo en `docs/informe-final.md`.


## [2026-11-16] - Sesión 9 (Fase Final): Validación con `make pruebas`, experimentos empíricos e Informe Final

**Quiénes:**

* Pablo Andrés Bueno Cerón
* Juan Eduardo Gómez Aguilar

**Trabajo realizado:**

* **Actualización de casos de prueba y ejecución de `make pruebas`:** Corregimos el valor esperado de `datos/funcional3.out` a `2.0` y actualizamos `datos/funcional5.out` y `datos/funcional6.out` según el orden de prioridad del `MonticuloBinario`. Ejecutamos `make pruebas` en Git Bash compilando con `g++ -Wall -Wextra -O2`, obteniendo cero advertencias y estado **OK** en los 7 casos (`funcional1.in` a `funcional6.in` y `limite.in`).
* **Mediciones experimentales (`datos/experimentos.csv`):** Ejecutamos pruebas de rendimiento en la misma máquina bajo `-O2` con `std::chrono::high_resolution_clock` sobre 5 tamaños crecientes ($n \in \{1000, 10000, 50000, 100000, 500000\}$) con carga mixta ($60\%$ llegadas, $40\%$ atenciones), comparando `ColaCircular` ($56.739\text{ ms}$ en $n = 500000$), `MonticuloBinario` ($922.076\text{ ms}$) y `std::priority_queue` ($508.705\text{ ms}$). Limpiamos los binarios y archivos temporales antes de subir al repositorio.
* **Redacción del Informe Final (`docs/informe-final.md`):** Completamos todas las secciones según la plantilla oficial: modelado corregido, justificación de `ColaCircular` frente a lista enlazada y arreglo con desplazamiento, costos completos (incluyendo `estaLlena`, `estaVacia` y espacio $\Theta(\text{capacidad})$), demostraciones formales en cuatro partes con testigos $c$ y $k$ en LaTeX, diagramas estructurales en Mermaid, gráfica comparativa `xychart-beta` y citas a CLRS (Capítulos 6 y 10).

**Pendiente:**

* Realizar la sustentación.
