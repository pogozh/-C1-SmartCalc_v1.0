CC = gcc
e_flags = -Wall -Wextra #-Werror
c_flags = -g
target = a.o
clean_files = *.o* *.a
srcs = stack.c\
       calc.c\
	   pars.c\

#lexeme.c

all: clean check programm cppcheck run_programm clean

clean:
	rm -rf $(clean_files)

cls:
	clear

programm:
	$(CC) $(e_flags) ${srcs} -o $(target) -g -fsanitize=address 

run_programm:
	./$(target)

cppcheck:
	cppcheck ${srcs}

# RUN LINTER
CPPLINT.cfg:
	cp ../../materials/linters/CPPLINT.cfg .

check: CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py ${srcs}
#	python3 ../materials/linters/cpplint.py *.h
#	python3 ../materials/linters/cpplint.py ./unit_tests/*.c
#	python3 ../materials/linters/cpplint.py ./unit_tests/*.h
	rm -rf CPPLINT.cfg


# PHONY TARGET
PHONY: clean check test
 
test: clean
	$(CC) $(e_flags) test1.c -o test1.o -g -fsanitize=address
	./test1.o
	cppcheck test1.c



