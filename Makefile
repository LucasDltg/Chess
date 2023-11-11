CXX ?= g++
CFLAGS ?= -Wextra -Wall -Werror

LDLIBS?= 

INCLUDE_PATH = ./include

TARGET   = echecs

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(CFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

doc:
	doxygen Doxyfile

.PHONY: clean cov
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(BINDIR)/$(TARGET)
