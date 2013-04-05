src=src
include=include
lib=lib
cc=clang
cflags= -Wall -pedantic -I$(include) -g
ldflags= -L$(lib) -lreadline -llang

comp: $(src)/comp.o $(lib)/liblang.a
	$(cc) $(ldflags) -o comp $^

$(lib)/liblang.a: $(src)/Parse.o $(src)/LinkedList.o $(src)/Identifiers.o $(src)/Eval.o $(src)/Vars.o $(src)/BalancedBinaryTree.o
	ar -r $@ $^ 

$(src)/%.o : $(src)/%.c
	$(cc) $(cflags) -o $@ -c $^

clean: 
	rm $(src)/*.o
	rm $(lib)/*.a
	rm comp
