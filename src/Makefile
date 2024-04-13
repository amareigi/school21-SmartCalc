TARGETS=s21_smartcalc.c credit.c
CFLAGS=-std=c11 -Wall -Werror -Wextra 
TESTS=test.c
FLAG_TEST=-lcheck
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
VALGRIND = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
ifeq ($(shell uname), Linux)
	FLAG_TEST +=-lsubunit -lm
endif

all: clean uninstall install gcov_report 

s21_smartcalc.a:$(OBJS)
	ar -rc s21_smartcalc.a $^
	ranlib s21_smartcalc.a
	rm -rf *.o

install:
	mkdir Calculator
	cp s21_smartcalc.c Calculator/s21_smartcalc.c
	cp credit.c Calculator/credit.c 
	cp s21_smartcalc.h Calculator/s21_smartcalc.h
	cd Qt && qmake -o ../Calculator/Makefile
	cd Calculator; make

uninstall:
	rm -rf Calculator

dist:
	tar -czf SmartCalc.install.tar.gz ./* *.c *.h
	
test: clean s21_smartcalc.a
	gcc --coverage $(CFLAGS) $(TESTS) s21_smartcalc.a $(FLAG_TEST) -o test -g
	./test

gcov_report:
	gcc --coverage $(TARGETS) $(TESTS) $(FLAG_TEST) -o greport
	./greport
	lcov -t "test" -o s21_smartcalc.info -c -d .
	genhtml -o ./report s21_smartcalc.info --exclude test.c
	open ./report/index.html

dvi:
	open ./instruction.md


style:
	clang-format -n --style=google *.c s21_smartcalc.h Qt/*.cpp Qt/*.h
	clang-format -i --style=google *.c s21_smartcalc.h Qt/*.cpp Qt/*.h

clean:
	rm -rf *.o s21_smartcalc.a gcov_report report greport *.info
	rm -rf build*/ Calculator/
	rm -rf *.out *.dSYM/ test *.gcda *.gcno
