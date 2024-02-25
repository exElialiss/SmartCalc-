LIB = S21_SmartCalc.a
CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
CFLAGS = -fprofile-arcs -ftest-coverage

BUILD = ../build
INSTALL = ./build/S21_SmartCalc
ARCHIVE = ../archive
TEST = ./test
EXEC = /build/S21_SmartCalc

OS = $(shell uname)
SRC = *.c
OBJ = $(SRC: .c=.o)

ifeq ($(OS), Darwin)
	APP = S21_SmartCalc.app
	GCOV_FLAGS = -lcheck -lm
	LEAK = CK_FORK=no leaks --atExit -- $(TEST)/test
else
	APP = S21_SmartCalc
	GCOV_FLAGS = `pkg-config --cflags --libs check`
	LEAK = valgrind --leak-check=full --leak-resolution=low --quiet --log-file=$(TEST)/leaks.txt $(TEST)/test
endif

all: install open

$(LIB): $(OBJ)
	rm -f $(BUILD)/$(LIB)
	ar rc $@ $(OBJ) 
	ranlib $@
	mv $(LIB) $(BUILD)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: test
test:
	@lcov --directory . --zerocounters
	@rm -f $(TEST)/test
	@gcc $(CFLAGS) -g $(SRC) $(TEST)/test.c -o $(TEST)/test $(GCOV_FLAGS)
	@$(TEST)/test

gcov_report: test
	@rm -rf $(TEST)/coverage_results
	@mkdir $(TEST)/coverage_results
	@lcov --directory . --capture -o $(TEST)/coverage_results/lcov.info
	@genhtml -o $(TEST)/coverage_results/ $(TEST)/coverage_results/lcov.info --highlight --legend --title "S21_SmartCalc_v1.0 project coverage"
	@rm -f $(TEST)/*.gc*

install: uninstall
	@mkdir -p $(INSTALL)
	@chmod +rwx $(INSTALL)
	@qmake6 S21_SmartCalc.pro -o $(INSTALL)/Makefile && make -C $(INSTALL)/
	@chmod +rwx $(INSTALL)/$(APP)
	@rm -f $(INSTALL)/*.o

open:
ifeq ($(shell uname), Linux)
	sudo .$(EXEC)/S21_SmartCalc 
else
	open .$(EXEC)/S21_SmartCalc 
endif

uninstall:
	rm -rf $(INSTALL)

dvi:
	open readme.md

dist: install
	rm -rf $(ARCHIVE)
	mkdir $(ARCHIVE)
	mkdir $(ARCHIVE)/S21_SmartCalc_v1.0
	cp -r $(INSTALL)/$(APP) $(ARCHIVE)/S21_SmartCalc_v1.0
	cp -r readme.md $(ARCHIVE)/S21_SmartCalc_v1.0
	cd $(ARCHIVE) && tar cvzf Archive_S21_SmartCalc_v1.0.tgz S21_SmartCalc_v1.0 && rm -rf S21_SmartCalc_v1.0

clean:
	rm -f $(BUILD)/$(LIB)
	rm -f $(TEST)/test
	rm -rf $(TEST)/coverage_results
	rm -f $(TEST)/test.log
	rm -f $(TEST)/leaks.txt
	rm -rf $(BUILD)/S21_SmartCalc
	rm -rf $(ARCHIVE)
	rm -f *.o
	lcov --directory . --zerocounters

style:
	clang-format -i *.c *.h *.cpp
	clang-format -i ./test/*.c

leaks: test
	rm -f $(TEST)/leaks.txt
	$(LEAK)
	@rm -f $(TEST)/*.gc*

rebuild: clean install