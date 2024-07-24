# Actividad 1
## _Command line arguments_
Se debe diseñar e implementar un programa en lengiaje C que al ejecutarse reciba por argumentos:

  - Si se ejecuta con la opción _-s_ debe ejecutar el ejercicio 1 del Laboratorio 2.
  - Si se ejecuta con la opción _-a_ debe ejecutar el ejercicio 2 del Laboratorio 2.

## Modo de ejecución

```bash
make
./actividadi -a
./actividadi -s
```

## Resultado

```bash
╰─➤  ./actividadi -a                                                                                                                                                                                    1 ↵
----/proc/meminfo:----
MemTotal:         19811.80 MB
MemFree:          8878.18 MB
MemAvailable:     13523.04 MB
----/proc/meminfo:----
SwapOcupada:      0.00 MB
----/proc/cpuinfo:----
Modelo de CPU:              Intel(R) Core(TM) i5-10500H CPU @ 2.50GHz
Cantidad de cores:                6 
Cantidad de thread por cores:     2
```

```bash
╰─➤  ./actividadi -s
[6] 'LINUX' 
[8] 'VERSION' 
[17] '6.5.0-41-GENERIC' 
[25] '(BUILDD@LCY02-AMD64-120)' 
[25] '(X86_64-LINUX-GNU-GCC-12' 
[8] '(UBUNTU' 
[23] '12.3.0-1UBUNTU1~22.04)' 
[8] '12.3.0,' 
[4] 'GNU' 
[3] 'LD' 
[5] '(GNU' 
[9] 'BINUTILS' 
[4] 'FOR' 
[8] 'UBUNTU)' 
[6] '2.38)' 
[19] '#41~22.04.2-UBUNTU' 
[4] 'SMP' 
[16] 'PREEMPT_DYNAMIC' 
[4] 'MON' 
[4] 'JUN' 
[2] '3' 
[9] '11:32:55' 
[4] 'UTC' 
[2] '2' 
tamanio total del symbols dynamic buffer: [166]
```