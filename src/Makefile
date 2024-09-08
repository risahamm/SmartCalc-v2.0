CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17

all: clean check_style tests gcov_report install

cmake:
	mkdir -p build && cd build && cmake ..

install: cmake
	cd build && make
	cd build && open SmartCalc.app

uninstall: clean
	rm -rf build

dvi:


dist:

clean:
	rm -rf test *.gcda *.gcno *.o *.info *.a

check_style:
	clang-format -style=Google -n view/*.cc view/*.h
    clang-format -style=Google -n controller/*.h
    clang-format -style=Google -n model/*.cc model/*.h
	clang-format -style=Google -n view/*.cc view/*.h
	#clang-format -style=Google -n tests/*.cc
	clang-format -style=Google -n main.cc

fix_style:
	clang-format -style=Google -i view/*.cc view/*.h
	clang-format -style=Google -i controller/*.h
	clang-format -style=Google -i model/*.cc model/*.h
	clang-format -style=Google -i view/*.cc view/*.h
	#clang-format -style=Google -i tests/*.cc
	clang-format -style=Google -i main.cc