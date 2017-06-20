# simple make file
# September 2004
SOURCES=collateClip.c
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
PRODUCT=$(HOME)/bin/collateClip_sqW

DEPS := $(OBJECTS:.o=.d)



CFLAGS=-O2 -I$(NR)/include
LDFLAGS=-lm

all: $(PRODUCT)



rebuild: clean all

$(PRODUCT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) -c -MMD -MP $< -o $@ $(CFLAGS)

# Let make read the dependency files and handle them.
-include $(DEPS)
