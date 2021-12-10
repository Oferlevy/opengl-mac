CXX = g++
CXXFLAGS = -Wall -std=c++20 $(INCLUDES)
LDFLAGS = -framework OpenGL -lglfw -lglew $(LIBS)

INCLUDES = $(addprefix -I,$(shell find * -name 'include' -type d))
LIBS = $(addprefix -L,$(shell find * -name 'lib' -type d))

TARGET = program
BUILDDIR = build

CPP_FILES = $(shell find * -name '*.cpp')
OBJECTS = $(addprefix $(BUILDDIR)/,$(CPP_FILES:.cpp=.o))

all: $(BUILDDIR)/$(TARGET)
	@$(BUILDDIR)/$(TARGET)

$(BUILDDIR)/$(TARGET): $(OBJECTS)
	@$(CXX) -o $@ $(LDFLAGS) $^

$(OBJECTS): $(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CXX) -MD -MP -c $< $(CXXFLAGS) -o $@

-include $(OBJECTS:.o=.d)

.PHONY: clean
clean:
	@rm -r $(BUILDDIR)