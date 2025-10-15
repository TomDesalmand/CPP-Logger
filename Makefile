# Detect platform
UNAME_S := $(shell uname -s)

CXX       ?= g++
LOG_LEVEL ?= 0

CXXFLAGS  ?= -std=c++17 -Wall -Wextra -O2
CPPFLAGS  ?=
CPPFLAGS  += -DLOG_LEVEL=$(LOG_LEVEL) -Iinclude -Isrc

# Platform-specific include paths (Homebrew on macOS)
ifeq ($(UNAME_S),Darwin)
CPPFLAGS  += -I/opt/homebrew/include
endif

LDFLAGS   ?=
LDLIBS    ?=

RM        := rm -f

NAME      ?= project

SRCS      := $(wildcard *.cpp) \
			 $(wildcard src/*.cpp)

OBJS      := $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(SINGLE_HEADER)

re: fclean all

# -----------------------------------------------------------------------------
# Single-header amalgamation
# Generates a header-only file at project root: generated/cpp_logger.hpp
# This file contains:
#   - All public headers from include/*.hpp (with project header guards stripped)
#   - All source definitions from src/*.cpp (with local includes stripped and
#     function/constructor definitions marked inline to avoid ODR violations)
# -----------------------------------------------------------------------------

SINGLE_HEADER      := generated/cpp_logger.hpp
HEADERS            := $(sort $(wildcard include/*.hpp))
SOURCES            := $(sort $(wildcard src/*.cpp))

single_header: $(SINGLE_HEADER)

# Use the external helper script to assemble the single header. The script
# accepts: <output-file> "<headers...>" "<sources...>"
# Keep the invocation simple and portable.
$(SINGLE_HEADER): $(HEADERS) $(SOURCES)
	@echo "Generating $(SINGLE_HEADER)"
	@mkdir -p $(dir $(SINGLE_HEADER))
	@./scripts/assemble_single_header.sh "$(SINGLE_HEADER)" "$(HEADERS)" "$(SOURCES)"

# Test runner target: builds and runs the tests located under tests/
# The test target uses the same compiler flags as the project to ensure
# tests are built with the same configuration (including LOG_LEVEL).
TEST_BINARY := tests_runner

TEST_SRCS := tests/main/main.cpp tests/components/*/*.cpp

test: $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TEST_SRCS) src/*.cpp -o $(TEST_BINARY)
	./$(TEST_BINARY)

.PHONY: all clean fclean re single_header test
