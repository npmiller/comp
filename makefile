src=src
include=include
lib=lib
tests=tests
cc=clang
cflags= -Wall -pedantic -I$(include) -g
ldflags= -L$(lib) -lreadline -llang
ldtestflags= -L$(lib) -llang -lcunit -ltests

comp: $(src)/comp.o $(lib)/liblang.a
	$(cc) $(ldflags) -o comp $^

tests: $(tests)/testMain.o $(lib)/libtests.a $(lib)/liblang.a
	$(cc) $(ldtestflags) -o testMain $^

$(lib)/libtests.a: $(tests)/LinkedList_tests.o $(tests)/Stack_tests.o $(tests)/Parse_tests.o
	ar -r $@ $^

$(lib)/liblang.a: $(src)/Parse.o $(src)/LinkedList.o $(src)/Stack.o $(src)/Identifiers.o $(src)/Eval.o $(src)/Vars.o $(src)/BalancedBinaryTree.o $(src)/Type.o $(src)/stdlib/calc.o $(src)/stdlib/ctrl.o $(src)/stdlib/io.o $(src)/stdlib/string.o
	ar -r $@ $^ 

$(src)/%.o : $(src)/%.c
	$(cc) $(cflags) -o $@ -c $^

$(src)/stdlib/%.o : $(src)/%.c
	$(cc) $(cflags) -o $@ -c $^

$(tests)/%.o : $(tests)/%.c
	$(cc) $(cflags) -o $@ -c $^
clean: 
	@echo "Removing objects files in $(src)..."
	#@if [ -e $(src)/**/*.o ]; then rm $(src)/**/*.o; fi
	rm $(src)/*.o
	rm $(src)/stdlib/*.o
	@echo "done."
	@echo "Removing libraries files in $(lib)..."
	@if [ -e $(lib)/*.a ]; then rm $(lib)/*.a; fi
	@echo "done."
	@echo "Removing objects files in $(tests)..."
	@if [ -e $(tests)/*.o ]; then rm $(tests)/*.o; fi
	@echo "done."
	@echo "Removing libraries files in $(tests)..."
	@if [ -e $(tests)/*.a ]; then rm $(tests)/*.a; fi
	@echo "done."
	@echo "Removing executables files ..."
	@if [ -e comp ]; then rm comp; fi
	@if [ -e testMain ]; then rm testMain; fi
	@echo "done."
