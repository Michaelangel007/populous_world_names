CC=g++
C_FLAGS=-Wall -Wextra
all: gen_pop_names

clean:
	rm gen_pop_names

gen_pop_names: gen_pop_names.c
	$(CC) $(C_FLAGS) $< -o $@

