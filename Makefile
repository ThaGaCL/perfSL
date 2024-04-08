# PROGRAMA
    PROG = perfSL
    OBJS = main.o perfSL.o utils.o matrix.o
	
# Compilador
    CC     = gcc
	
	LIKWID_PERFMON = -DLIKWID_PERFMON
	LIKWID_INCLUDE = /home/soft/likwid/include
	LIKWID_LIB = /home/soft/likwid/lib


# Acrescentar onde apropriado as opções para incluir uso da biblioteca LIKWID
CFLAGS= -g --debug -Wall -O3 -mavx -march=native -I$(LIKWID_HOME)/include -DLIKWID_PERFMON
LFLAGS= -lm -L$(LIKWID_HOME)/lib -llikwid
LIKWID_HOME=/home/soft/likwid
# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) $(OBJS) core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
