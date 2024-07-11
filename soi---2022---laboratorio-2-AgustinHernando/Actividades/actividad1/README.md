# Actividad 1
## _C-strings_
Realice las siguientes actividades:
   - Obtener la **memoria ram total**, **libre** y **disponible** en *Megabytes*. A partir del archivo */proc/meminfo*. 
   - Obtener la memoria *swap* **Ocupada**. A partir del archivo */proc/meminfo*.
   - Crear un programa en C que imprima información referida al CPU, a partir del archivo */proc/cpuinfo*:
       - Modelo de CPU.
       - Cantidad de cores 
       - Cantidad de thread por cores.

## Archivos `/proc/meminfo` y `/proc/cpuinfo`
### `/proc/meminfo`
El archivo /proc/meminfo proporciona información sobre el uso de la memoria del sistema. Contiene múltiples campos de los cuales los más relevantes para esta actividad son:

- MemTotal: Memoria RAM total.
- MemFree: Memoria RAM libre.
- MemAvailable: Memoria RAM disponible.
- SwapTotal: Memoria swap total.
- SwapFree: Memoria swap libre.
### `/proc/cpuinfo`
El archivo /proc/cpuinfo contiene detalles sobre el procesador de la máquina. Los campos relevantes son:

- model name: Modelo del CPU.
- cpu cores: Número de núcleos físicos.
- siblings: Número de hilos (threads) por CPU.

## Modo de ejecución

```bash
make
./actividadi
```

## Resultado

```bash
----/proc/meminfo:----
MemTotal:         19811.80 MB
MemFree:          9859.34 MB
MemAvailable:     14327.08 MB
SwapOcupada:      0.00 mb
----/proc/cpuinfo:----
Modelo de CPU:              Intel(R) Core(TM) i5-10500H CPU @ 2.50GHz
 
Cantidad de cores:                6 
Cantidad de thread por cores:     2
```