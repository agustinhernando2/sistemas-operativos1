# Actividad 2
## _Static Library_
Implementar en el proyecto la librería cJSON, que permita:

 - Si se agrega, junto a las opciones del **punto 1**, la opción _-j_, se debe utilizar la librería estática **cJSON** [1] y mostrar el resultado en dicho formato.
## Modo de ejecución

```bash
make
./actividadii -a -j
./actividadii -s -j
```

## Resultado

```bash
─➤  ./actividadii -a -j                                             
[
{
	"path":	"/proc/meminfo",
	"data":	[{
			"Memoria Total[MB]":	19811.7890625
		}, {
			"Memoria Free[MB]":	11607.6796875
		}, {
			"Memoria Available[MB]":	15082.9453125
		}]
}
,{
	"path":	"/proc/meminfo",
	"data":	[{
			"SwapOcupada [MB]":	0
		}]
}
,{
	"model":	" Intel(R) Core(TM) i5-10500H CPU @ 2.50GHz\n",
	"data":	[{
			"Cantidad_de_cores":	6
		}, {
			"thread_por_cores":	2
		}]
}

]
```

```bash
╰─➤  ./actividadii -s -j
{
	"vesion":	"Linux version 6.5.0-44-generic (buildd@lcy02-amd64-103) (x86_64-linux-gnu-gcc-12 (Ubuntu 12.3.0-1ubuntu1~22.04) 12.3.0, GNU ld (GNU Binutils for Ubuntu) 2.38) #44~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC T",
	"words":	["LINUX", "VERSION", "6.5.0-44-GENERIC", "(BUILDD@LCY02-AMD64-103)", "(X86_64-LINUX-GNU-GCC-12", "(UBUNTU", "12.3.0-1UBUNTU1~22.04)", "12.3.0,", "GNU", "LD", "(GNU", "BINUTILS", "FOR", "UBUNTU)", "2.38)", "#44~22.04.1-UBUNTU", "SMP", "PREEMPT_DYNAMIC", "T"]
}
```


## Referencias
[1] cJSON, https://github.com/DaveGamble/cJSON