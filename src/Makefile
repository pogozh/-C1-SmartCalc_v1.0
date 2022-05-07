CC = gcc
target = s21_calc

MATH_LIB = -lm
CHECK_LIB = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
EXTRA_WARNING = -Wall -Wextra
DEBUG_FLAG = -g3 -fsanitize=address
COVERAGE_FLAG = -fprofile-arcs -ftest-coverage # -g


# FOLDERS
INCLUDE_PATH = -I. -I./unit_tests
BUILD_DIR = ./build
calc_DIR = ./
TEST_DIR = ./unit_tests
calc_OBJ_DIR = $(BUILD_DIR)/${target}
TEST_OBJ_DIR = $(BUILD_DIR)/test


# CREATE CALC FILES
calc_SOURCE =\
    stack.c\
	stack_queue.c\
    calc.c\
    pars.c\

calc_OBJ = $(calc_SOURCE:%.c=%.o)
calc_OBJ_PATH = $(addprefix $(calc_OBJ_DIR)/, $(calc_OBJ))
calc_DEP_PATH = $(calc_OBJ_PATH:%.o=%.d)
-include $(calc_DEP_PATH)

$(calc_OBJ_DIR): 
	mkdir $@
$(TEST_OBJ_DIR):
	mkdir $@


# CREATE TEST FILES
TEST_SOURCE =\
	main.c\
	utils_suite.c\
	calc_suite.c\

TEST_OBJ = $(TEST_SOURCE:%.c=%.o) $(calc_SOURCE:%.c=%.o)
TEST_OBJ_PATH = $(addprefix $(TEST_OBJ_DIR)/, $(TEST_OBJ))
TEST_DEP_PATH = $(TEST_OBJ_PATH:%.o=%.d)
-include $(calc_DEP_PATH)


# ALL TARGET
all: s21_calc.a tests

# S21_CALC.A BUILD
$(calc_OBJ_DIR)/%.o: $(calc_DIR)/%.c
	$(CC) $(INCLUDE_PATH) $(MATH_LIB) $(DEBUG_FLAG) $(EXTRA_WARNING) -MD -c $< -o $@

s21_calc.a: $(calc_OBJ_PATH)
	ar rcs $@ $^
	ranlib $@

# S21_TEST.OUT BUILD
$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(INCLUDE_PATH) $(MATH_LIB) $(CHECK_LIB) $(EXTRA_WARNING) $(DEBUG_FLAG) -MD -c $< -o $@

$(TEST_OBJ_DIR)/%.o: %.c
	$(CC) $(COVERAGE_FLAG) $(INCLUDE_PATH) $(MATH_LIB) $(CHECK_LIB) $(EXTRA_WARNING) $(DEBUG_FLAG) -MD -c $< -o $@

test.out: $(TEST_OBJ_PATH)
	$(CC) $^ $(COVERAGE_FLAG) $(INCLUDE_PATH) $(MATH_LIB) $(CHECK_LIB) $(EXTRA_WARNING) $(DEBUG_FLAG) -o $@

# TESTS COVERAGE
gcov_report: test.out
	./$<
	lcov -t "$<" -o gcovreport.info -c -d $(TEST_OBJ_DIR)
	genhtml -o $@ gcovreport.info

tests: test.out
#clear
	./test.out


# CLEAN TARGET
clean:
	# rm ./gcov_report/*.*
	# rm ./gcov_report/src/*.*
	find . -type f -name "*.o" -delete
	find . -type f -name "*.d" -delete
	find . -type f -name "*.a" -delete
	find . -name "*.out" -delete
	find . -name "*.gcno" -delete
	find . -name "*.gcda" -delete
	rm -rf /gcov_report/*.*
	rm -rf report
	rm -rf gcovreport.info
	rm -rf gcovreport
	rm -rf CPPLINT.cfg

#RUN CPP CHECK
cppcheck:
	cppcheck ${calc_SOURCE}

# RUN LINTER
CPPLINT.cfg:
	cp ../materials/linters/CPPLINT.cfg .

check: CPPLINT.cfg
	python3 ../materials/linters/cpplint.py *.c
	python3 ../materials/linters/cpplint.py *.h
	python3 ../materials/linters/cpplint.py ./unit_tests/*.c
	python3 ../materials/linters/cpplint.py ./unit_tests/*.h
	rm -rf CPPLINT.cfg


# PHONY TARGET
PHONY: clean check test


# PERSONAL TARGETS SHOULD BE WRITTEN BELLOW, FOUND TARGETS ABOVE WILL BE DELETED
clear:
	clear

# jdreama targets
2all: clear clean check cppcheck gcov_report

jd: clean clear all
