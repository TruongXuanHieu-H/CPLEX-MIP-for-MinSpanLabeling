CPLEXDIR=/opt/ibm/ILOG/CPLEX_Studio222
CONCERTDIR=$(CPLEXDIR)/concert

SYSTEM=x86-64_linux
LIBFORMAT=static_pic

CXX=g++

CXXFLAGS= \
    -std=c++20 \
    -O3 \
    -fPIC \
    -fexceptions \
    -DNDEBUG \
    -DIL_STD \
    -I$(CPLEXDIR)/cplex/include \
    -I$(CONCERTDIR)/include \
    -Isrc

LDFLAGS= \
    -L$(CPLEXDIR)/cplex/lib/$(SYSTEM)/$(LIBFORMAT) \
    -L$(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT) \

LIBS= \
    -lilocplex \
    -lconcert \
    -lcplex \
    -lm \
    -lpthread \
    -ldl

TARGET := build/cplex

SRC := $(shell find src -type f -name '*.cpp')
OBJ := $(patsubst src/%.cpp,build/obj/%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(dir $@)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

build/obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)