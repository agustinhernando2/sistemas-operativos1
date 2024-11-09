# Actividad 3
## _Dynamic Library_
Se debe diseñar e implementar una librería dinámica que actúe como _plugin_, extendiendo las opciones y que permita lo siguiente:
  - Se debe cargar dinámicamente al ejecutarse con la opción -d
  - Debe mostrar, utilizando la librería cJSON del punto 2, la información sobre los filesystems soportado por el kernel en uso: /proc/filesystems.
## Modo de ejecución

```bash
make
./actividad.elf -a -j -d 
./actividad.elf -s -j -d
```

## Resultado

```bash
╰─➤  ./actividad.elf -a -j -d


Copy and paste the json to validate format:
 https://jsonformatter.org/

{
  "filesystems": {
    "path": "/proc/filesystems",
    "data": [
      "nodev sysfs",
      "nodev tmpfs",
      "nodev bdev",
      "nodev proc",
      "nodev cgroup",
      "nodev cgroup2",
      "nodev cpuset",
      "nodev devtmpfs",
      "nodev configfs",
      "nodev debugfs",
      "nodev tracefs",
      "nodev securityfs",
      "nodev sockfs",
      "nodev bpf",
      "nodev pipefs",
      "nodev ramfs",
      "nodev hugetlbfs",
      "nodev devpts",
      "      ext3",
      "      ext2",
      "      ext4",
      "      squashfs",
      "      vfat",
      "nodev ecryptfs",
      "      fuseblk",
      "nodev fuse",
      "nodev fusectl",
      "nodev efivarfs",
      "nodev mqueue",
      "nodev pstore",
      "nodev autofs",
      "nodev binfmt_misc",
      "nodev overlay"
    ]
  },
  "activity_1": [
    {
      "path": "/proc/meminfo",
      "data": [
        {
          "Memoria Total[MB]": 19820.1328125
        },
        {
          "Memoria Free[MB]": 11429.75
        },
        {
          "Memoria Available[MB]": 15054.6796875
        }
      ]
    },
    {
      "path": "/proc/meminfo",
      "data": [
        {
          "SwapOcupada [MB]": 0
        }
      ]
    },
    {
      "model": " Intel(R) Core(TM) i5-10500H CPU @ 2.50GHz\n",
      "data": [
        {
          "Cantidad_de_cores": 6
        },
        {
          "thread_por_cores": 2
        }
      ]
    }
  ]
}

```