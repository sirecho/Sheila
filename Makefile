OUTDIR := bin
OBJDIR := build
OBJ := $(addprefix $(OBJDIR)/,sheila.o standardchessboard.o minimax.o piece.o position.o) 

all : sheila

sheila : $(OBJ) | $(OUTDIR)
		g++ -o $(OUTDIR)/Sheila $(OBJ)

$(OBJDIR)/%.o : src/%.cpp | $(OBJDIR)
		g++ -c $^ -o $@

$(OUTDIR) :
		mkdir $(OUTDIR)

$(OBJDIR) :
		mkdir $(OBJDIR)

.PHONY: clean
clean:
		rm $(OBJDIR)/*.o

.PHONY: test
test : sheila
	$(MAKE) unit1 -C test
