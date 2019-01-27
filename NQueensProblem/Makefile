################################################################################
# File: Makefile
#
# Author: Alexy Torres Aurora Dugo
#
# Date: 26/01/2019
#
# Version: 1.0
#
# Makefile to compile the solvers (thanks to @jblefoul for the initial version)
################################################################################
TARGET = core

SRC_DIR   = src
BUILD_DIR = build
INC_DIR   = include
BIN_DIR   = bin
COV_DIR   = cov_data
DOXY_DIR  = doxygen

DOXY_CONF_FILE = .doxy_config

NAMESPACES = core solver

TARGET = $(BIN_DIR)/NQueensSolver

TEST_DIR = tests
TEST_TARGETS =\
  tests/solver/testGreedyAttackCount\
  tests/solver/testGreedySolve\
  tests/solver/testHillAttackCount\
  tests/solver/testHillSolve\
  tests/solver/testGeneticAttackCount\
  tests/solver/testGeneticSolve\
  tests/solver/testGeneticInitPopulation\
  tests/solver/testGeneticComputeFitness\
  tests/solver/testFitnessPropMatingPoolSelector\
  tests/solver/testOrderOneCrossoverOperator\
  tests/solver/testSwapMutationOperator\
  tests/solver/testTossProbability

# C++ Flags
EXTRAFLAGS = -std=c++11 -Wall -Wextra -Werror -O2

# COVERAGE_ENABLE
ifeq ($(COVERAGE), true)
  EXTRAFLAGS +=-fprofile-arcs -ftest-coverage -fPIC -O0
endif
ifeq ($(DEBUG), true)
  EXTRAFLAGS += -g -O0
endif

ifdef test
  EXTRAFLAGS += -D_TESTMODE
endif

.PHONY: all clean

all: preclean build
	$(CXX) $(EXTRAFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

preclean:
	@rm -rf $(BIN_DIR)
	@mkdir -p $(BIN_DIR)

run:
	./$(TARGET) $(ARGUMENTS)

clean:
	$(RM) -rf $(BUILD_DIR) *~ $(BIN_DIR) $(COV_DIR) $(DOXY_DIR)


####################### Project code section #######################
SRC_DIRS = $(NAMESPACES:%=$(SRC_DIR)/%)
OBJ_DIRS = $(NAMESPACES:%=$(BUILD_DIR)/%)
SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

#creates build directories if they they don't already exist
$(OBJ_DIRS):
	@mkdir -p $@

#compiles source files to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(EXTRAFLAGS) -c $< -o $@ -I $(INC_DIR)

#compiles all source files
build: $(OBJ_DIRS) $(OBJS)

####################### Test section ########################
TEST_SRC_DIRS = $(NAMESPACES:%=$(TEST_DIR)/%)
TEST_OBJ_DIRS = $(NAMESPACES:%=$(BUILD_DIR)/$(TEST_DIR)/%)
TEST_BIN_DIRS = $(NAMESPACES:%=$(BIN_DIR)/$(TEST_DIR)/%)

TEST_SRCS =  $(foreach dir,$(TEST_SRC_DIRS),$(wildcard $(dir)/*.cpp))
TEST_OBJS = $(TEST_SRCS:%.cpp=$(BUILD_DIR)/%.o)
VERBOSE = false

$(TEST_OBJ_DIRS):
	mkdir -p $@

$(TEST_BIN_DIRS):
	mkdir -p $@

$(TEST_OBJS): $(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(EXTRAFLAGS) -c $< -o $@ -I $(INC_DIR)

$(TEST_TARGETS): %: build $(TEST_OBJ_DIRS) $(BUILD_DIR)/%.o $(TEST_BIN_DIRS)
	@rm -f $(BIN_DIR)/$@
	$(CXX) $(EXTRAFLAGS) -o $(BIN_DIR)/$@ $(OBJS) $(BUILD_DIR)/$@.o $(LIBS)
	./$(BIN_DIR)/$@ $(ARGUMENTS) $(VERBOSE)

testGreedyAttackCount: tests/solver/testGreedyAttackCount
testGreedySolve: tests/solver/testGreedySolve
testHillAttackCount: tests/solver/testHillAttackCount
testHillSolve: tests/solver/testHillSolve
testGeneticAttackCount: tests/solver/testGeneticAttackCount
testGeneticSolve: tests/solver/testGeneticSolve
testGeneticInitPopulation: tests/solver/testGeneticInitPopulation
testGeneticComputeFitness: tests/solver/testGeneticComputeFitness
testFitnessPropMatingPoolSelector: tests/solver/testFitnessPropMatingPoolSelector
testOrderOneCrossoverOperator: tests/solver/testOrderOneCrossoverOperator
testSwapMutationOperator: tests/solver/testSwapMutationOperator
testTossProbability: tests/solver/testTossProbability

tests: testGreedyAttackCount testGreedySolve testHillAttackCount testHillSolve \
       testGeneticAttackCount testGeneticInitPopulation \
	   testGeneticComputeFitness testFitnessPropMatingPoolSelector \
	   testOrderOneCrossoverOperator testSwapMutationOperator \
	   testTossProbability testGeneticSolve

####################### COVERAGE section #######################


COV_DIRS = $(OBJ_DIRS:$(BUILD_DIR)/%=$(COV_DIR)/%)
COV_GCDA_FILES = $(OBJS:$(BUILD_DIR)/%.o=$(COV_DIR)/%.gcda)
COV_GCNO_FILES = $(OBJS:$(BUILD_DIR)/%.o=$(COV_DIR)/%.gcno)

$(COV_DIRS):
	@mkdir -p $@

$(COV_GCDA_FILES): $(COV_DIR)/%.gcda: $(BUILD_DIR)/%.gcda
	-@mv $< $@ 2>/dev/null
$(COV_GCNO_FILES): $(COV_DIR)/%.gcno: $(BUILD_DIR)/%.gcno
	-@mv $< $@ 2>/dev/null

#generate coverage files
gen_cov: $(COV_DIRS)
	for dir in $(NAMESPACES); do\
		if ls $(BUILD_DIR)/$$dir/*.gcda 1> /dev/null 2>&1; then\
			mv $(BUILD_DIR)/$$dir/*.gcda $(COV_DIR)/$$dir/;\
		fi;\
		if ls $(BUILD_DIR)/$$dir/*.gcno 1> /dev/null 2>&1; then\
			mv $(BUILD_DIR)/$$dir/*.gcno $(COV_DIR)/$$dir/;\
		fi;\
	done

	gcovr -r . --html --html-details -o $(COV_DIR)/gcovr-report.html


####################### Doxygen section #######################

INC_DIRS = $(NAMESPACES:%=$(INC_DIR)/%)
HEADERS = $(foreach dir,$(INC_DIRS),$(wildcard $(dir)/*.h)) \
		  $(foreach dir,$(INC_DIRS),$(wildcard $(dir)/*.hpp))

doxygen: $(DOXY_CONF_FILE) $(HEADERS)
	@rm -rf $(DOXY_DIR)
	@mkdir -p $(DOXY_DIR)
	doxygen $(DOXY_CONF_FILE)