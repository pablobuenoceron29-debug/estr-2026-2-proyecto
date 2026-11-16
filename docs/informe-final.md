# Informe final

**Escenario D: Turnos de una clínica**  
**Autores:** Pablo Andrés Bueno Cerón (`9038949`), Juan Eduardo Gómez Aguilar (`9024217`)

---

## 1. El escenario y el modelado

El programa está planteado para ser utilizado en el área de recepción y triage de una clínica como sistema para organizar los turnos de atención de los pacientes. A la clínica llegan pacientes con un nombre y un nivel de urgencia entero en el rango $[1, 5]$, donde $5$ representa la urgencia máxima y $1$ la consulta general más leve. El sistema debe consumir pocos recursos de memoria y procesador para operar de manera estable en equipos institucionales acotados.

### Modelo de tiempo, órdenes y registro `Paciente`
El sistema opera con un reloj lógico discreto (`int reloj = 1`) que avanza una unidad por cada orden procesada (`LLEGA`, `ATIENDE`, `ESPERAN`, `PROMEDIO`):

1. **`LLEGA <nombre> <urgencia>`:** Registra un paciente en la sala de espera. A diferencia del avance —donde se leía la urgencia y se descartaba—, ahora la estructura `Paciente` (`codigo/Paciente.h`) almacena los tres atributos necesarios para ambas estructuras:
   * `nombre` (`std::string`): identificador del paciente.
   * `urgencia` (`int`): nivel de gravedad en $[1, 5]$.
   * `tiempoLlegada` (`int`): valor de `reloj` en el instante de llegada.
2. **`ATIENDE`:** Si la sala de espera está vacía, imprime `nadie espera`. En caso contrario, extrae al paciente que corresponda según la estructura activa, calcula su tiempo de espera individual mediante $t_{\text{espera}} = \text{reloj} - p.\text{tiempoLlegada}$, lo acumula en `sumaTiemposEspera`, incrementa `pacientesAtendidos` e imprime `p.nombre`.
3. **`ESPERAN`:** Imprime la cantidad actual de pacientes en sala de espera (`obtenerCantidad()`).
4. **`PROMEDIO`:** Si `pacientesAtendidos == 0`, imprime `0.0`. De lo contrario, imprime el promedio $\bar{T} = \text{sumaTiemposEspera} / \text{pacientesAtendidos}$ formateado a un decimal fijo (`std::fixed << std::setprecision(1)`).

### Justificación de la estructura lineal (corrección del avance)
En la entrega de avance se eligió una **cola circular sobre arreglo** (`ColaCircular`) para la atención por orden estricto de llegada (FIFO). Se descartaron las otras dos implementaciones lineales por las siguientes razones técnicas:

1. **Por qué no un arreglo lineal con desplazamiento:** En un arreglo lineal donde el frente permanece fijo en el índice `0`, cada operación `ATIENDE` obliga a desplazar los $n - 1$ pacientes restantes una posición hacia la izquierda, degradando `desencolar()` a $\Theta(n)$. La cola circular utiliza índices modulares `(frente + 1) % capacidad` y `(trasero + 1) % capacidad`, reutilizando las posiciones liberadas al inicio del arreglo sin mover registros en memoria, lo que mantiene el costo en $\Theta(1)$.
2. **Por qué no una lista enlazada:** Aunque una lista simplemente enlazada con punteros a cabeza y cola también opera en $\Theta(1)$ en ambos extremos, cada paciente requeriría una llamada a asignación dinámica en el *heap* (`new Nodo`) durante la ejecución y el almacenamiento de un puntero adicional (`8 bytes` en arquitecturas de 64 bits). El arreglo circular preasignado evita la fragmentación de memoria, elimina el costo de punteros por elemento y mejora la localidad espacial de caché.

> **Cita del texto guía:** Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). *Introduction to Algorithms* (4.ª ed.). MIT Press. **Capítulo 10 (Elementary Data Structures), Sección 10.1 (Stacks and queues), pp. 254–258**.

### Casos de prueba corregidos del avance (`make pruebas`)
Se corrigió el caso `funcional3` (cuyo promedio real es `2.0` y no `3.0`, ya que cada paciente espera dos órdenes en promedio) y se actualizaron las salidas esperadas en `datos/` para corresponder con la ejecución del `MonticuloBinario` compilado con `g++ -Wall -Wextra -O2`:

| Caso | Entrada | Salida esperada | Salida obtenida | Estado |
| :--- | :--- | :--- | :--- | :---: |
| `funcional1` | `2` / `LLEGA ana 2` / `ATIENDE` | `ana` | `ana` | OK |
| `funcional2` | `3` / `LLEGA ana 2` / `LLEGA beto 5` / `ESPERAN` | `2` | `2` | OK |
| `funcional3` | `5` / `LLEGA ana 2` / `LLEGA beto 5` / `ATIENDE` / `ATIENDE` / `PROMEDIO` | `beto`, `ana`, `2.0` | `beto`, `ana`, `2.0` | OK |
| `funcional4` | `5` / `LLEGA elena 4` / `LLEGA fabio 2` / `ESPERAN` / `ATIENDE` / `PROMEDIO` | `2`, `elena`, `3.0` | `2`, `elena`, `3.0` | OK |
| `funcional5` | `7` / `LLEGA ana 2` / `LLEGA beto 5` / `ESPERAN` / `ATIENDE` x2 / `ESPERAN` / `PROMEDIO` | `2`, `beto`, `ana`, `0`, `3.0` | `2`, `beto`, `ana`, `0`, `3.0` | OK |
| `funcional6` | `4` / `LLEGA carlos 3` / `LLEGA diana 5` / `ATIENDE` / `ATIENDE` | `diana`, `carlos` | `diana`, `carlos` | OK |
| `limite` | `1` / `ATIENDE` (estructura vacía) | `nadie espera` | `nadie espera` | OK |

---

## 2. Las dos estructuras

Ambas estructuras fueron separadas en sus propios archivos de cabecera (`codigo/ColaCircular.h` y `codigo/MonticuloBinario.h`) y exponen **exactamente la misma interfaz pública**. Esto permite que el programa principal (`codigo/principal.cpp`) utilice una plantilla genérica (`ejecutarSimulacion<Estructura>`) e intercambie una estructura por otra sin modificar la lectura de órdenes ni el cálculo de métricas.

### Operaciones expuestas por la interfaz unificada

| Operación | Firma | Qué hace | Precondición |
| :--- | :--- | :--- | :--- |
| `encolar` | `void encolar(Paciente p)` | Inserta un paciente en la estructura manteniendo su invariante. | `!estaLlena()` |
| `desencolar` | `Paciente desencolar()` | Extrae y retorna el siguiente paciente a ser atendido. | `!estaVacia()` |
| `obtenerCantidad` | `int obtenerCantidad() const` | Retorna el entero `cantidad` de pacientes en espera. | Ninguna |
| `estaLlena` | `bool estaLlena() const` | Retorna `true` si `cantidad == capacidad`, `false` en caso contrario. | Ninguna |
| `estaVacia` | `bool estaVacia() const` | Retorna `true` si `cantidad == 0`, `false` en caso contrario. | Ninguna |

### 2.1 Estructura 1: Cola Circular (`ColaCircular`)
Implementa atención estrictamente FIFO sobre un bloque contiguo `new Paciente[capacidad]`. Mantiene los índices enteros `frente` y `trasero` avanzando en módulo `capacidad`. Cuando el arreglo se llena parcialmente y se liberan celdas al frente, el índice `trasero` da la vuelta (`(trasero + 1) % capacidad`) reutilizando el inicio del arreglo.

**Invariante de `ColaCircular`:**
$$I_{\text{cola}}: \quad (0 \le \text{cantidad} \le \text{capacidad}) \land (0 \le \text{frente} < \text{capacidad}) \land \big(\text{cantidad} > 0 \implies \text{trasero} = (\text{frente} + \text{cantidad} - 1) \bmod \text{capacidad}\big)$$

```mermaid
graph LR
    subgraph ColaCircular ["Cola Circular sobre Arreglo (capacidad = 5)"]
        0["[0]: (diana, u=5, t=6) Trasero (vuelta modular)"]
        1["[1]: Vacío (liberado)"]
        2["[2]: (beto, u=5, t=2) Frente"]
        3["[3]: (carlos, u=3, t=4)"]
        4["[4]: (elena, u=4, t=5)"]
    end
    2 --> 3 --> 4 --> 0
