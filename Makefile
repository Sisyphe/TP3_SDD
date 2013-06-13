########################################################################
##                      Makefile generique                            ##
########################################################################

# Nom du projet
TARGET   = tp3

# Compilateur
CC       = gcc

# Options de compilation
CFLAGS   = -g -ansi -Wall -pedantic

# Editeur de liens
LINKER   = gcc -o

# Options de l'editeur de liens
LFLAGS   = -Wall

# Dossier des sources, des binaires et des fichiers de compilation
SRCDIR   = .
OBJDIR   = ./obj
BINDIR   = ./bin

SOURCES  = $(wildcard $(SRCDIR)/*.c)
INCLUDES = $(wildcard $(SRCDIR)/*.h)
OBJECTS  = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -frv

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

-include $(OBJECTS:.o=.d)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

	@$(CC) -MM $(CFLAGS) $(SRCDIR)/$*.c > $(OBJDIR)/$*.d
	@mv -f $(OBJDIR)/$*.d $(OBJDIR)/$*.d.tmp
	@sed -e 's|.*:|$(OBJDIR)/$*.o:|' < $(OBJDIR)/$*.d.tmp > $(OBJDIR)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJDIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJDIR)/$*.d
	@rm -f $(OBJDIR)/$*.d.tmp
	@echo "Compiled "$<" successfully!"


# Creation des dossiers utiles a la compilation (si necessaire)
mkdirs:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

# Generation du compte rendu
texcr: $(TARGET).tex $(SRCDIR)/*.c $(SRCDIR)/*.h
	#valgrind --leak-check=full --log-file=reportincludes/valgrind-report \
	#	$(BINDIR)/$(TARGET) datafiles/sorted.dat datafiles/unsorted.dat
	#$(BINDIR)/$(TARGET) datafiles/sorted.dat \
	#	datafiles/unsorted.dat > reportincludes/output 2>&1
	#iconv -f UTF-8 -t ISO-8859-1 reportincludes/output -o \
	#	reportincludes/output.tmp && \
	#	mv reportincludes/output.tmp reportincludes/output
	../mkcr ./sourcefiles.tex $(SRCDIR)/*.c $(SRCDIR)/*.h
	pdflatex -interaction=nonstopmode $(TARGET).tex

# Nettoyages
.PHONY: texclean
texclean:
	@$(rm) *.aux *.bbl *.blg *.log
	@echo "Latex cleanup complete!"

.PHONY: clean
clean: texclean
	@$(rm) $(OBJDIR)/*
	@$(rm) sourcefiles.tex
	@echo "Cleanup complete!"

.PHONY: mrproprer
mrproprer: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@$(rm) $(TARGET).pdf
	@echo "Executable removed!"
