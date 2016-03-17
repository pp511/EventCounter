CC      = gcc
RM      = rm -f

default: bbst 

host: bbst.cpp
	$(CC) -o bbst.cpp rbtree.cpp 
	
clean:
	rm -f core *.o bbst rbtree