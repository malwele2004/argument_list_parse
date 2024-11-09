CFLAGS = -g
COMMON = gcc -c $^ -o $@
BIN_PARSE = bin/parse.o
BIN_MAIN = bin/main.o
SRC_PARSE = src/parse/parse.c
SRC_MAIN = src/main/main.c
BUILD_TEST = build/test
BUILD_STATIC = build/libarglist.a

clean:
	rm build/* bin/*

$(BIN_MAIN): $(SRC_MAIN)
	$(COMMON)

$(BIN_PARSE): $(SRC_PARSE)
	$(COMMON)

$(BUILD_TEST): $(BIN_PARSE) $(BIN_MAIN)
	gcc $(CFLAGS) bin/* -o $@

$(BUILD_STATIC): $(BIN_PARSE)
	ar rcs $@ $^

prepare:
	-mkdir bin build || true

debug: prepare
	$(MAKE) $(BUILD_TEST)

release: prepare
	$(MAKE) $(BUILD_STATIC)
