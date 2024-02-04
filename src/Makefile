CC=gcc
COMLFAGS=-Wall -Werror -Wextra -std=c11 -pedantic 
TFLAGS=-o testing -lcheck --coverage 
ASC = ./App/SmartCalc_release/

ifeq ($(shell uname), Linux)
	TFLAGS += -lm -lsubunit
endif

ifeq ($(shell uname), Darwin)
 TFLAGS += -fprofile-arcs -ftest-coverage
endif

all: test gcov_report dist install dvi start 

.PHONY: all clean build format test gcov_report

rebuild: clean clean_dist uninstall format all

build:
	$(CC) $(COMLFAGS) -c *.c
	ar -rc libcalc.a *.o


install:
	@echo "Installing SmartCalc..."
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@cp -R ./App/SmartCalc ./App/SmartCalc_release
	qmake6 $(ASC)SmartCalc.pro -o $(ASC)SmartCalc_makefile
	-cd $(ASC) && make install -f SmartCalc_makefile
	@cat App/SmartCalc/completed.txt

	

uninstall:
	@echo "Removing SmartCalc..."
	-cd $(ASC) && make uninstall -f SmartCalc_makefile
	@-rm -rf ./App/SmartCalc_release
	@cat App/SmartCalc/rem.txt

start:
	open ./App/SmartCalc_release/SmartCalc.app

dvi:
	open -o "Google Chrome" ./documentation/dvi.html
	

dist:
	@mkdir -p SmartCalc_v1.0/src/
	@cp -r Makefile s21_calc.c s21_calc.h credit.c stack.c stack.h test.check documentation App SmartCalc_v1.0/src/
	tar cvzf SmartCalc_v1.0.tgz SmartCalc_v1.0/
	@if [ ! -d ./SmartCalc_dist ] ; then mkdir ./SmartCalc_dist ; fi
	@mv SmartCalc_v1.0.tgz ./SmartCalc_dist/
	@rm -rf SmartCalc_v1.0

clean_dist:
	@rm -rf SmartCalc_dist


test: build
	checkmk clean_mode=1  test.check > testing.c
	$(CC) *.c libcalc.a $(TFLAGS)
	./testing

gcov_report:
	@gcov -b *.c 
	@lcov -d . -c -o coverage.info
	@genhtml -o html_report coverage.info
	@open html_report/index.html

clean:
	@-rm -rf $(ASC)
	@-rm *.o testing.c testing *.a *.gcno *.gcda *.gcov *.info
	@-rm -rf html_report

clean_all:
	@make clean
	@make clean_dist
	make uninstall


format:
	@find . -type f -name "*.c" -exec clang-format --style=Google -i {} \;
	@find . -type f -name "*.h" -exec clang-format --style=Google -i {} \;

format_check:
	find . -type f -name "*.c" -exec clang-format --style=Google -n {} \;
	find . -type f -name "*.h" -exec clang-format --style=Google -n {} \;