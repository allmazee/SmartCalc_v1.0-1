.PHONY: all clean tests install uninstall dvi dist gcov_report

CC=gcc 
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOVFLAGS=-fprofile-arcs -ftest-coverage
QMAKE = qmake6
C_FILES = *.c
O_FILES = *.o
TEST_FILE = Tests/tests.c
REPORT_FILE = report
OS = $(shell uname)

INST_DIR = build
DIST_DIR = dist
EXE_DIR = SmartCalc
TEST_DIR = Tests
REPORT_DIR = report

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
	EXE_FILE=SmartCalc.app
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lcheck_pic -lrt -lm
	EXE_FILE=SmartCalc
endif

all: install

install:
	mkdir -p $(INST_DIR)
	cd $(EXE_DIR) && \
	$(QMAKE) && \
	make && \
	mv $(EXE_FILE) ../$(INST_DIR)

uninstall: 
	rm -rf $(INST_DIR)


clean:
	cd $(EXE_DIR) && \
	$(QMAKE) && \
	rm -rf $(EXE_FILE) .qmake.stash && \
	make clean && \
	rm Makefile
	cd $(TEST_DIR) && \
	rm -rf *.gcno *.gcda tests.out report *.info
	rm -rf $(DIST_DIR).tar RESULT_VALGRIND.txt

dvi:
	open dvi/dvi.html

dist:
	mkdir $(DIST_DIR)
	cp *.c *.h $(DIST_DIR)
	mkdir $(DIST_DIR)/$(EXE_DIR)
	cp $(EXE_DIR)/* $(DIST_DIR)/$(EXE_DIR)
	tar --totals -cvf $(DIST_DIR).tar $(DIST_DIR)
	rm -rf $(DIST_DIR)

test: $(C_FILES) $(TEST_FILE)
	$(CC) $(CFLAGS) $^ -o $(TEST_DIR)/tests.out $(TEST_LIBS) $(GCOVFLAGS)
	./$(TEST_DIR)/tests.out

gcov_report: test
	cd $(TEST_DIR) && \
	lcov -t "tests.out" -o s21_smart_calc_tests.info -c -d . && \
	genhtml -o report s21_smart_calc_tests.info && \
	open report/index.html

valgrind:
	valgrind --leak-check=full --log-file=RESULT_VALGRIND.txt ./$(TEST_DIR)/tests.out
