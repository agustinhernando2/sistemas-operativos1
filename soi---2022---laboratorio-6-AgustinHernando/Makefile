CFLAGS = -Wall -Werror -pedantic
src = ./src
inc = ./include
bin = ./build/bin
build = ./build

$(bin)/main: $(build)/main.o $(build)/measurement.o
	mkdir -p $(bin)/
	gcc $(CFLAGS) -o $@ $(build)/main.o $(build)/measurement.o
	echo "Ejecutable generado en $(bin)/main"

$(build)/main.o: $(src)/main.c $(inc)/measurement.h
	mkdir -p $(build)/
	gcc $(CFLAGS) -c -o $@ $(src)/main.c

$(build)/measurement.o: $(src)/measurement.c $(inc)/measurement.h
	gcc $(CFLAGS) -c -o $@ $(src)/measurement.c

clean:
	rm -rf $(build)