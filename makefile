SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))
TEST_SRCS = $(wildcard test/*.c)
TEST_OBJS = $(patsubst test/%.c, obj/%.o, $(TEST_SRCS))

release: $(filter-out obj/test.o, $(OBJS))
	gcc -Wall -Wextra -g $(filter-out obj/test.o, $(OBJS)) -o release/bin/fornecedora -lcjson

test: $(filter-out obj/main.o, $(OBJS)) $(TEST_OBJS)
	gcc -Wall -Wextra -g $(filter-out obj/main.o, $(OBJS)) $(TEST_OBJS) -o test/bin/test
	./test/bin/test


run: release
	./release/bin/fornecedora


obj/%.o: src/%.c
	gcc -Wall -Wextra -g -Iinclude -c $< -o $@
obj/%.o: test/%.c
	gcc -Wall -Wextra -g -Iinclude -c $< -o $@

libcjson.a:
	cd cJSON && make install