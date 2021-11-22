########################################################################
####################### Makefile Template ##############################
## builds dependency .d files into DEPDIR
## compiles all c++ files in the SRCDIR directory into OBJDIR
## build APPNAME in same folder as makefiel
##
## just using make , you will get a debug build
## if you want a release build use make RELEASE=YES 

# Compiler settings - Can be customized.
CC = clang
CXX = clang++

## if you wish to change to g++, use this LDFLAGS
LDFLAGS = -lstdc++

# Makefile settings - Can be customized.
APPNAME = sudoku
EXT = .cpp
SRCDIR = src
OBJDIR = obj
DEPDIR = dep

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=$(DEPDIR)/%.d)

# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
DELDEP = $(DEP) 

# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)
WDELDEP = $(SRC:$(SRCDIR)/%$(EXT)=$(DEPDIR)\\%.d) 

# switch to release build if requested
ifeq (YES,$(RELEASE))   
CXXFLAGS = -std=c11 -std=c++11 -Wall -O3 -DNDEBUG
CCFLAGS = -std=c11 -std=c++11 -Wall -O3 -DNDEBUG
else
CXXFLAGS = -std=c++11 -Wall -g -DDEBUG 
CCFLAGS = -std=c++11 -Wall -g -DDEBUG 
endif

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
$(DEPDIR)/%.d: $(SRCDIR)/%$(EXT)
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	@mkdir -p $(@D)	
	$(CXX) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)
