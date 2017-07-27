# simple make file
# September 2004
SOURCES=multiAverage.c 
PRODUCT=$(HOME)/bin/multiAverage_sqW


OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

CFLAGS=-O2 
LDFLAGS=-lm

all: $(PRODUCT)

rebuild: clean all

$(PRODUCT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) -c -MMD -MP $< -o $@ $(CFLAGS)

# Let make read the dependency files and handle them.
-include $(DEPS)
