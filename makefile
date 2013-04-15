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

$(lib)/libtests.a: $(tests)/LinkedList_tests.o
	ar -r $@ $^

$(lib)/liblang.a: $(src)/Parse.o $(src)/LinkedList.o $(src)/Identifiers.o $(src)/Eval.o $(src)/Vars.o $(src)/BalancedBinaryTree.o
	ar -r $@ $^ 

$(src)/%.o : $(src)/%.c
	$(cc) $(cflags) -o $@ -c $^

$(tests)/%.o : $(tests)/%.c
	$(cc) $(cflags) -o $@ -c $^
clean: 
	rm $(src)/*.o
	rm $(lib)/*.a
	rm $(tests)/*.o
	rm comp
	rm testMain
