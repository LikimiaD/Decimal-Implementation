CC = gcc
TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
FLAGS = -Wall -Werror -Wextra -std=c11
SOURCES = decimal_arithmetic.c  decimal_comparison.c  decimal_core.c  decimal_parser.c  decimal_rounding.c  decimal_support.c
DOCKER_VERSION = 1.0.0

all: clean test

test: clean decimal.a
	$(CC) $(CFLAGS) tests/*.c decimal.a $(TEST_LIBS) -o test
	./test
	rm -rf *.o tests/*.o

decimal.a:
	for source in $(SOURCES); do \
		$(CC) -c $(CFLAGS) functions/$$source -o functions/$${source%.c}.o; \
	done
	ar rcs decimal.a functions/*.o

gcov_flag:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage)

gcov_report: clean gcov_flag test
	gcov $(SOURCES)
	rm -rf html_report
	gcov -b *.c 
	lcov -d . -c -o coverage.info
	genhtml -o html_report coverage.info

clang:
	cp ../materials/linters/.clang-format ../src
	clang-format -i *.h *.c
	rm -rf .clang-format

style : 
	clang-format --style=google -i *.c *.h
	clang-format --style=google -i tests/*.c

test_leaks: test
	leaks --atExit -- ./test

docker:
	docker build -t ubuntu_test_decimal:$(DOCKER_VERSION) .
	docker run --rm -it ubuntu_test_decimal:$(DOCKER_VERSION)

clean : 
	rm -f *.out functions/*.o functions/*.gcda functions/*.gcno decimal.a test *.gcda *.gcno *.info
	rm -rf html_report
