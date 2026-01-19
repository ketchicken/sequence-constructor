COMPILER = "gcc"
FLAGS = ""
OFILES = sequence_constructor.o graph.o

sequence_constructor: $(OFILES)
	$(COMPILER) -g $(FLAGS) -o sequence_constructor sequence_constructor.o graph.o

graph.o: graph.h graph.cpp
	$(COMPILER) -g $(FLAGS) -c graph.cpp

sequence.o: graph.h sequence_constructor.cpp
	$(COMPILER) -g $(FLAGS) -c sequence_constructor.cpp

clean:
	rm -rf *.o 