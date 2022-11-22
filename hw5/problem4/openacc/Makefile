target: GPUvecAdd.c
	pgcc -acc -Minfo=accel GPUvecAdd.c -o accOut

.PHONY: clean init

run:
	./accOut

clean:
	rm accOut
