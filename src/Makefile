CC=gcc
CFLAGS=-std=c++17 -g -Wall -Wextra -Werror
FLAGS_PLATFORM = -lcheck
FLAGS_LIBA= -lgtest -lstdc++ -lpthread -std=c++17 -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
REPORT = GcovReport
SRC=Set/*.hpp Map/*.hpp Multiset/*.hpp \
	List/*.hpp Queue/*.hpp Stack/*.hpp \
	Array/*.hpp Vector/*.hpp
TEST= Test/*.cpp
SRC_ASSOTITIVE = Test/test_assotiative_cont.cpp
SRC_ARRAY = Test/test_array.cpp
SRC_VECTOR = Test/test_vector.cpp
SRC_LIST = Test/list_tests.cpp
SRC_QUEUE = Test/queue_tests.cpp
SRC_STACK = Test/stack_tests.cpp

ifeq ($(OS), Darwin)
	FLAGS_PLATFORM = -lcheck
else
	FLAGS_PLATFORM = -lcheck -lsubunit -lrt -lm -lpthread -g
endif

OBJ=$(patsubst %.cpp, %.o, $(SRC))
HEADER=s21_containers.hpp s21_containersplus.hpp

.PHONY: all build s21_containers test report clean m

all: build

leaks:
	@echo -------------------MEMORY_LEAKS-------------------
	$(CC) $(FLAGS_LIBA) $(SRC_ARRAY) -lcheck -o unit1.out
	CK_FORK=no leaks --atExit -- ./unit1.out
	$(CC) $(FLAGS_LIBA) $(SRC_VECTOR) -lcheck -o unit2.out
	CK_FORK=no leaks --atExit -- ./unit2.out
	$(CC) $(FLAGS_LIBA) $(SRC_LIST) -lcheck -o unit3.out
	CK_FORK=no leaks --atExit -- ./unit3.out
	$(CC) $(FLAGS_LIBA) $(SRC_QUEUE) -lcheck -o unit4.out
	CK_FORK=no leaks --atExit -- ./unit4.out
	$(CC) $(FLAGS_LIBA) $(SRC_STACK) -lcheck -o unit5.out
	CK_FORK=no leaks --atExit -- ./unit5.out

build:
	$(CC) $(CFLAGS) $(HEADER) -o s21_containers.a

s21_containers: build

check: $(NAME)

	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -style=file --dry-run --Werror $(SRC) *.hpp $(TEST)
	@echo NO ERRORS
	@say "NO ERRORS"	

test: clean set_map_mset_test vector_test queue_test array_test stack_test

set_map_mset_test:
	$(CC) $(SRC_ASSOTITIVE) $(FLAGS_LIBA) -o test_set
	./test_set --gtest_brief=1

vector_test:
	$(CC) $(SRC_VECTOR) $(FLAGS_LIBA) -o test_vector
	./test_vector --gtest_brief=1

list_test:
	$(CC) $(SRC_LIST) $(FLAGS_LIBA) -o test_list
	./test_list --gtest_brief=1

queue_test:
	$(CC) $(SRC_QUEUE) $(FLAGS_LIBA) -o test_queue
	./test_queue --gtest_brief=1

stack_test:
	$(CC) $(SRC_STACK) $(FLAGS_LIBA) -o test_stack
	./test_stack --gtest_brief=1

array_test:
	$(CC) $(SRC_ARRAY) $(FLAGS_LIBA) -o test_array
	./test_array --gtest_brief=1

clean:
	@rm -rf *.gch *.out *.o *.a m *.gcda *.gcdo *.gcno *.dSYM coverage_report gcov_test g_test \
	*.html report  test_vector test_queue test_array test_stack test_list test_set GcovReport
