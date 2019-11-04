COMPILER = cc

all:
		$(COMPILER) -o shell shell.c
		
clean:
		rm shell		