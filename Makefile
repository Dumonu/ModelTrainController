# Determine Paths
TOP_DIR := $(abspath .)
SRC_DIR := $(TOP_DIR)/src
DEP_DIR := $(TOP_DIR)/dep
OBJ_DIR := $(TOP_DIR)/build
BIN_DIR := $(TOP_DIR)/bin
INC_DIR := $(TOP_DIR)/include

# Set up basic flags
GCC := gcc
EXE := $(BIN_DIR)/program
CFLAGS := -std=c99 -Wall -Wextra -pedantic -I$(INC_DIR)
LFLAGS := -lncurses

# Modify flags and set up windows versus unix building
ifeq ($(OS),Windows_NT)
	CFLAGS += -DWINDOWS -DPDC_DLL_BUILD -DHAVE_NO_INFOEX
	LFLAGS := $(BIN_DIR)/pdcurses.dll
	UNIX := 0
	SHELL := cmd.exe
else ifeq ($(shell uname -s), Darwin)
	CFLAGS += -DMACOSX
	UNIX := 1
else
	CFLAGS += -DLINUX
	UNIX := 1
endif

# Find source files
ifeq ($(UNIX),1)
vpath %.c $(shell find $(SRC_DIR) -type d -print | tr '\n' ':')
vpath %.h $(shell find $(SRC_DIR) -type d -print | tr '\n' ':')

SRC := $(notdir $(shell find $(SRC_DIR) -name *.c))
INC := $(addprefix $(INC_DIR)/,$(notdir $(shell find $(SRC_DIR) -name *.h)))
else 
vpath %.c $(SRC_DIR):$(shell for /F %%G in ('dir /S /B /A:D $(subst /,\,$(SRC_DIR))') do echo %%G:)
vpath %.h $(SRC_DIR):$(shell for /F %%G in ('dir /S /B /A:D $(subst /,\,$(SRC_DIR))') do echo %%G:)

SRC := $(notdir $(shell dir /S /B $(subst /,\,$(SRC_DIR))\*.c))
INC := $(notdir $(shell dir /S /B $(subst /,\,$(SRC_DIR))\*.h))
endif

OBJ := $(addprefix $(OBJ_DIR)/,$(patsubst %.c,%.o,$(SRC)))
DOBJ := $(addprefix $(OBJ_DIR).dbg/,$(patsubst %.c,%.o,$(SRC)))

.PHONY: all release debug clean includes

all: debug release

release: $(OBJ_DIR) $(BIN_DIR) includes $(EXE).exe

debug: $(OBJ_DIR).dbg $(BIN_DIR) includes $(EXE).dbg

includes: $(INC_DIR) $(INC)

include $(addprefix $(DEP_DIR)/,$(patsubst %.c,%.d,$(SRC)))

$(OBJ_DIR)/%.o: %.c
	$(GCC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR).dbg/%.o: %.c
	$(GCC) -c $(CFLAGS) -g -DDEBUG_ -o $@ $<

$(EXE).exe: $(OBJ)
	$(GCC) -o $@ $^ $(LFLAGS)

$(EXE).dbg: $(DOBJ)
	$(GCC) -o $@ $^ $(LFLAGS)

ifeq ($(UNIX),1)
$(DEP_DIR)/%.d: %.c $(DEP_DIR)
	$(GCC) -MM $(CFLAGS) $< | awk 'BEGIN {FS="[:]";OFS=":";RS=""}{$$1="$(OBJ_DIR)/" $$1 " $(OBJ_DIR).dbg/" $$1 " $@"; print $$0}' > $@

$(DEP_DIR):
	mkdir $(DEP_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(INC_DIR):
	mkdir $(INC_DIR)

$(OBJ_DIR).dbg:
	mkdir $(OBJ_DIR).dbg

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(INC_DIR)/%.h: %.h
	cp -f $< $@

clean:
	rm -rf $(DEP_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR).dbg
	rm -rf $(INC_DIR)
	rm -f $(EXE)
	rm -f $(EXE).dbg
else ifeq ($(UNIX),0)

$(DEP_DIR)/%.d: %.c $(DEP_DIR)
	$(GCC) -MM $(CFLAGS) $< | awk "BEGIN {FS=\"[:]\";OFS=\":\";RS=\"\"}{$$1=\"$(OBJ_DIR)/\" $$1 \" $(OBJ_DIR).dbg/\" $$1 \" $@\"; print $$0}" > $@

$(DEP_DIR):
	mkdir $(subst /,\,$(DEP_DIR))

$(OBJ_DIR):
	mkdir $(subst /,\,$(OBJ_DIR))

$(INC_DIR):
	mkdir $(subst /,\,$(INC_DIR))

$(OBJ_DIR).dbg:
	mkdir $(subst /,\,$(OBJ_DIR).dbg)

$(BIN_DIR):
	mkdir $(subst /,\,$(BIN_DIR))

$(INC_DIR)/%.h: %.h
	copy /Y $< $@

clean:
	rd  /S /Q $(subst /,\,$(DEP_DIR)) || Echo:
	rd  /S /Q $(subst /,\,$(OBJ_DIR)) || Echo:
	rd  /S /Q $(subst /,\,$(OBJ_DIR).dbg) || Echo:
	rd  /S /Q $(subst /,\,$(INC_DIR)) || Echo:
	del /F /Q $(subst /,\,$(EXE).exe)
	del /F /Q $(subst /,\,$(EXE).dbg)
endif
