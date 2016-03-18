CC      = g++
RM      = rm -f

default: bbst

bbst: bbst.cpp
	$(CC) -o bbst bbst.cpp rbtree.cpp 
	
clean:
	rm -f core *.o bbst rbtree
	
