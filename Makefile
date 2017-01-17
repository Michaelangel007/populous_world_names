CC=g++
C_FLAGS=-Wall -Wextra
all: gen_pop_names verify dump_prefix

clean:
	rm gen_pop_names verify dump_prefix

gen_pop_names: gen_pop_names.c
	$(CC) $(C_FLAGS) $< -o $@

verify: verify.c verify.h
	$(CC) $(C_FLAGS) $< -o $@

dump_prefix: dump_prefix.c verify.h
	$(CC) $(C_FLAGS) $< -o $@

