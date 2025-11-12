# ---------------------------------------------------------------------
# Platform detection
# ---------------------------------------------------------------------
UNAME_S := $(shell uname -s)

# ---------------------------------------------------------------------
# Tooling and default flags (can be overridden from environment)
# ---------------------------------------------------------------------
CXX        ?= g++
CXXFLAGS   ?= -std=c++17 -Wall -Wextra -O2
CPPFLAGS   ?=
LDFLAGS    ?=
LDLIBS     ?=
LOG_LEVEL  ?= 0

# Include project headers and expose LOG_LEVEL to sources
CPPFLAGS  += -DLOG_LEVEL=$(LOG_LEVEL) -I include

# On macOS with Homebrew, add Homebrew include path
ifeq ($(UNAME_S),Darwin)
CPPFLAGS += -I/opt/homebrew/include
endif

RM := rm -f

# ---------------------------------------------------------------------
# Project naming and source layout
# ---------------------------------------------------------------------
NAME ?= project

SRCS := $(wildcard *.cpp) $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

# ---------------------------------------------------------------------
# Targets
# ---------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

SINGLE_HEADER := generated/cpp_logger.hpp
fclean: clean
	$(RM) $(NAME) $(SINGLE_HEADER)

re: fclean all

# ---------------------------------------------------------------------
# Single-header amalgamation
# Generates: generated/cpp_logger.hpp
# - collects include/*.hpp (strips guards)
# - appends src/*.cpp definitions (makes inline where required)
# The actual assembly is performed by: ./scripts/assemble_single_header.sh
# ---------------------------------------------------------------------
HEADERS := $(sort $(wildcard include/*.hpp))
SOURCES := $(sort $(wildcard src/*.cpp))
single_header: $(SINGLE_HEADER)

$(SINGLE_HEADER): $(HEADERS) $(SOURCES)
	@echo "Generating $(SINGLE_HEADER)"
	@mkdir -p $(dir $(SINGLE_HEADER))
	@./scripts/assemble_single_header.sh "$(SINGLE_HEADER)" "$(HEADERS)" "$(SOURCES)"

# ---------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------
TEST_BINARY := tests_runner
TEST_SRCS   := tests/main/main.cpp $(wildcard tests/components/*/*.cpp)

test: $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TEST_SRCS) src/*.cpp -o $(TEST_BINARY)
	./$(TEST_BINARY)

# ---------------------------------------------------------------------
# Phony targets
# ---------------------------------------------------------------------
.PHONY: all clean fclean re single_header test
