CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17

all: clean check_style test gcov_report install uninstall dvi dist

cmake:
	@mkdir -p build && cd build && cmake ..

install: cmake
	@echo "\033[46mInstallation\033[0m"
	@cd build && make
	@echo "\033[46mApplication installed\033[0m"
	@make dvi
	@cd build && open SmartCalc.app

uninstall: clean
	@rm -rf build
	@rm -rf ../dist
	@echo "\033[46mApplication removed\033[0m"

test: clean
	$(CC) $(CFLAGS) --coverage model/tests/*.cc model/*.cc -lgtest -lgtest_main -pthread -o test
	./test

gcov_report: test
	@lcov -t "test_calculation" -o calculation.info -c -d . --ignore-errors mismatch,inconsistent
	@lcov -e calculation.info '*/src/model/*.cc' -o calculation_filtered.info --ignore-errors mismatch,inconsistent
	@genhtml -o ../gcov_report calculation_filtered.info --ignore-errors mismatch,inconsistent
	@open ./../gcov_report/index.html

dvi:
	@open ./../dvi_report/html/index.html

dist:
	@mkdir -p ../dist
	@cp -R build/SmartCalc.app ../dist
	@cd ../dist && tar cvzf SmartCalc.tar *
	@cd ../dist && rm -rf SmartCalc.app README.md

clean:
	@rm -rf test *.gcda *.gcno *.o *.info *.a ../gcov_report
	@echo "\033[46mCleaned\033[0m"

check_style:
	clang-format -style=Google -n view/*.cc view/*.h
	clang-format -style=Google -n controller/*.h
	clang-format -style=Google -n model/*.cc model/*.h
	clang-format -style=Google -n model/tests/*.cc
	clang-format -style=Google -n main.cc

fix_style:
	clang-format -style=Google -i view/*.cc view/*.h
	clang-format -style=Google -i controller/*.h
	clang-format -style=Google -i model/*.cc model/*.h
	clang-format -style=Google -i model/tests/*.cc
	clang-format -style=Google -i main.cc