CC := g++ -lm -pthread --std=c++17
CFLAGS := --std=c++17
CLIBS := -lm -pthread 

BUILDDIR := build/
SRCDIR := src/
TESTDIR := test/
BINDIR := bin/

PROGRAMNAME := myprogram 

# v--v v--v v--v DO NOT TOUCH v--v v--v v--v

RELEASEDIR := $(BINDIR)release/
DEBUGDIR := $(BINDIR)debug/

all: 
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)
	@mkdir -p $(RELEASEDIR)
	@make release

release: $(BUILDDIR)Main.o $(BUILDDIR)Network.o $(BUILDDIR)NeuralMath.o $(BUILDDIR)Optimization.o $(BUILDDIR)Save.o $(BUILDDIR)StringUtils.o 
	$(CC) $(BUILDDIR)Main.o $(BUILDDIR)Network.o $(BUILDDIR)NeuralMath.o $(BUILDDIR)Optimization.o $(BUILDDIR)Save.o $(BUILDDIR)StringUtils.o -o $(RELEASEDIR)$(PROGRAMNAME)

$(BUILDDIR)Main.o: $(SRCDIR)Main.cpp 
	$(CC) -c $(SRCDIR)Main.cpp -o $(BUILDDIR)Main.o

$(BUILDDIR)Network.o: $(SRCDIR)Network.cpp 
	$(CC) -c $(SRCDIR)Network.cpp -o $(BUILDDIR)Network.o

$(BUILDDIR)NeuralMath.o: $(SRCDIR)NeuralMath.cpp 
	$(CC) -c $(SRCDIR)NeuralMath.cpp -o $(BUILDDIR)NeuralMath.o

$(BUILDDIR)Optimization.o: $(SRCDIR)Optimization.cpp 
	$(CC) -c $(SRCDIR)Optimization.cpp -o $(BUILDDIR)Optimization.o

$(BUILDDIR)Save.o: $(SRCDIR)Save.cpp 
	$(CC) -c $(SRCDIR)Save.cpp -o $(BUILDDIR)Save.o

$(BUILDDIR)StringUtils.o: $(SRCDIR)StringUtils.cpp 
	$(CC) -c $(SRCDIR)StringUtils.cpp -o $(BUILDDIR)StringUtils.o

testall: 
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)
	@mkdir -p $(DEBUGDIR)
	@make debug

debug: $(BUILDDIR)Image.o $(BUILDDIR)Main.o $(BUILDDIR)Network.o $(BUILDDIR)NeuralMath.o $(BUILDDIR)Optimization.o $(BUILDDIR)Save.o $(BUILDDIR)StringUtils.o 
	 $(CC) $(BUILDDIR)Main.o $(BUILDDIR)Network.o $(BUILDDIR)NeuralMath.o $(BUILDDIR)Optimization.o $(BUILDDIR)Save.o $(BUILDDIR)StringUtils.o $(BUILDDIR)Image.o -o $(DEBUGDIR)$(PROGRAMNAME) 

$(BUILDDIR)Image.o: $(TESTDIR)Image.cpp 
	 $(CC) -c $(TESTDIR)Image.cpp -o $(BUILDDIR)Image.o

clean:
	rm  $(BUILDDIR)*

cleanall:
	rm -rf $(BUILDDIR) $(BINDIR) 
