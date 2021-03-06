# Script for compiling unit tests on PC.

# Name for output binary hex, bin files
BIN_NAME := comm_protocol

# Folder containing compilation result files
OUT_DIR := out/

###############################################################################
# Paths for code under test

# Paths to header files (.h).
INC_DIRS := \
. \
src \

# Paths for source files (.c) and (.S)
# In these paths files are searched recursively in subfolders.
SRC_DIRS := \

# Additional source files (.c)
C_SRC_FILES := \
src/comm/comm_master.c \

#
###############################################################################

###############################################################################
# Paths for test code

# Dot . shouldn't be followed by slash /, because include paths wouldn't be
# found.
TEST_INC_DIRS := \
. \

# Dot . should be followed by slash /, otherwise files from upper folder are
# also taken.
TEST_SRC_DIRS := \
unity/ \
unit_test/comm_master/ \

TEST_SRC_FILES := \

#
###############################################################################

###############################################################################
# Toolchain defines

TOOLCHAIN := 

CC := $(TOOLCHAIN)gcc

#
###############################################################################

# Function for searching folders recursively for given pattern
rwildcard=$(wildcard $(addsuffix $2, $1))\
$(foreach d,$(wildcard $(addsuffix *, $1)),$(call rwildcard,$d/,$2))

###############################################################################
# Files and paths defines

C_EXT := c
CODE_SRC := $(call rwildcard,$(SRC_DIRS),*.$(C_EXT)) $(C_SRC_FILES)
TEST_SRC := $(call rwildcard,$(TEST_SRC_DIRS),*.$(C_EXT)) $(TEST_SRC_FILES)

CODE_SRC := $(filter-out $(C_SRC_EXCLUDE), $(CODE_SRC))
TEST_SRC := $(filter-out $(C_SRC_EXCLUDE), $(TEST_SRC))

CODE_OBJ := $(addprefix $(OUT_DIR)code/, $(sort $(notdir $(CODE_SRC:.$(C_EXT)=.o))))
TEST_OBJ := $(addprefix $(OUT_DIR)test/, $(sort $(notdir $(TEST_SRC:.$(C_EXT)=.o))))

OBJS := $(CODE_OBJ) $(TEST_OBJ)

VPATH := $(sort $(dir $(TEST_SRC) $(CODE_SRC)) $(TEST_INC_DIRS))
#
###############################################################################

###############################################################################
# Compiler and linker defines

# Code under tests is compiled with extended warning flags
C_FLAGS_CODE := -Wall -Wextra -Wstrict-prototypes
# Test files are compiled with only standard flags set
C_FLAGS_TEST := -Wall

# Include paths
INC_FLAGS_CODE := $(patsubst %, -I%, $(INC_DIRS))
INC_FLAGS_TEST := -I. $(patsubst %, -I%, $(TEST_INC_DIRS))

# Global defines
GLOBAL_DEFS_F = $(patsubst %, -D%, $(GLOBAL_DEFS))

# Compiler flags
C_FLAGS_CODE += $(GLOBAL_DEFS_F) $(INC_FLAGS_CODE) -g
C_FLAGS_TEST += $(GLOBAL_DEFS_F) $(INC_FLAGS_CODE) $(INC_FLAGS_TEST) -g

# Linker flags
LD_FLAGS := -Wl,-Map=$(OUT_DIR)bin/$(BIN_NAME).map -Wl,--gc-sections
LD_LIBS := -L$(LIB_DIRS) -l$(LIBS)

#
###############################################################################

###############################################################################
# Targets

all: init out_dir $(OUT_DIR)bin/$(BIN_NAME) run

run:
	@echo '-----------------------------'
	@echo 'Running tests for $(BIN_NAME)'
	@$(OUT_DIR)bin/$(BIN_NAME)

# Creating resulting binary file
$(OUT_DIR)bin/$(BIN_NAME) : $(TEST_OBJ) $(CODE_OBJ)
	@echo 'Linking target: $(OUT_DIR)bin/$(BIN_NAME)'
	$(CC) $(LD_FLAGS) $(TEST_OBJ) $(CODE_OBJ) $(LD_LIBS) -o $@
	@echo ''

# Pattern for code under test compilation
$(OUT_DIR)code/%.o : %.$(C_EXT)
	@echo 'Compiling file: $<'
	$(CC) -c $(C_FLAGS_CODE) $< -o $@
	@echo ''

# Pattern for test files compilation
$(OUT_DIR)test/%.o : %.$(C_EXT)
	@echo 'Compiling file: $<'
	$(CC) -c $(C_FLAGS_TEST) $< -o $@
	@echo ''

out_dir :
	@mkdir -p $(OUT_DIR)bin
	@mkdir -p $(OUT_DIR)code
	@mkdir -p $(OUT_DIR)test

init :
	@echo ''
	@echo 'Building $(BIN_NAME) PC unit tests:'
	@echo 'SRC files under test:'
	@echo $(CODE_SRC)
	@echo 'Test file sources:'
	@echo $(TEST_SRC)
	@echo ''

clean:
	@rm -rf test_results.txt
	@rm -rf $(subst /,,$(OUT_DIR))