PROG        = gr
VERSION     = 1.0
EXEEXT      = .exe

CC          = gcc
LIBDIR      = lib
SHAREDFLAGS = -Wall -pedantic -std=c99 -I $(LIBDIR)/gr-data-structs/includes -L$(LIBDIR)/gr-data-structs -lgr-data-structs-1.0
CFLAGS      = $(SHAREDFLAGS) -g3
CRELFLAGS   = $(SHAREDFLAGS) -Os -s -DNDEBUG
SRCDIR      = src
OBJDIR      = obj
BINDIR      = bin

TARGET	    = $(BINDIR)/$(PROG)$(EXEEXT)
RELTARGET   = $(BINDIR)/$(PROG)-$(VERSION)$(EXEEXT)
GENPREFIX   = gen.
LEXDEF      = lexer.l
PARSERDEF   = parser.y
LEXGENC     = $(GENPREFIX)$(PROG).lexer.c
PARSEGENC   = $(GENPREFIX)$(PROG).parser.c
TOKENGENH   = $(GENPREFIX)$(PROG).tokens.h
SRCS        = ${wildcard $(SRCDIR)/*.c} $(SRCDIR)/$(LEXGENC) $(SRCDIR)/$(PARSEGENC)
OBJS        = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: exe

gen: bison flex

bison: $(SRCDIR)/$(TOKENGENH) $(SRCDIR)/$(PARSEGENC)

flex: $(SRCDIR)/$(LEXGENC)

$(SRCDIR)/$(LEXGENC): $(SRCDIR)/$(LEXDEF) $(SRCDIR)/$(TOKENGENH) $(SRCDIR)/parser-support.h
	cd $(SRCDIR); flex -CF -o $(LEXGENC) $(LEXDEF)

$(SRCDIR)/$(TOKENGENH) $(SRCDIR)/$(PARSEGENC): $(SRCDIR)/$(PARSERDEF) $(SRCDIR)/parser-support.h
	cd $(SRCDIR); bison -d --verbose -o $(PARSEGENC) $(PARSERDEF)
	@cd $(SRCDIR); mv $(PARSEGENC:.c=.h) $(TOKENGENH)

compile: $(OBJS)

$(OBJDIR)/%.o: $(SRCS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $(@:$(OBJDIR)%.o=$(SRCDIR)%.c) -o $@ 

exe: $(TARGET) copylib

copylib: $(BINDIR)/libgr-data-structs-1.0.dll

$(BINDIR)/libgr-data-structs-1.0.dll: $(LIBDIR)/gr-data-structs/libgr-data-structs-1.0.dll
	@mkdir -p $(BINDIR)
	@cp -f $< $@

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	@echo 'Building target: $@'
	$(CC) $(CFLAGS) -I$(SRCDIR) -o $(TARGET) $^
	@echo 'Finished building target: $@'

rel: $(RELTARGET) copylib

$(RELTARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	@echo 'Building target: $@'
	$(CC) $(CRELFLAGS) -I$(SRCDIR) -o $(RELTARGET) $^
	@echo 'Finished building target: $@'

test: exe
	$(TARGET) test/test.txt

testrel: rel
	$(RELTARGET) test/test.txt

clean:
	@echo Clean files
	@rm -rf $(TARGET) $(OBJDIR) $(BINDIR)
	@cd $(SRCDIR); rm -rf $(PROG).tab.h $(PROG).yy.c $(PROG).tab.c $(PARSEGENC:.c=.h)
	@cd $(SRCDIR); rm -rf $(PARSEGENC:.c=.output)

cleangen:
	@echo Clean generated source
	@rm -rf $(SRCDIR)/$(GENPREFIX)*

clear: clean cleangen