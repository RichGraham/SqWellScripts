# simple make file
# September 2004
SOURCES=OP_mapping.c
PRODUCT=$(HOME)/bin/OP_mapping_sqW


NR=$(HOME)/recipes_c-ansi

VPATH = ./ : $(NR)/misc/ :  $(NR)/recipes/ 

OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

CFLAGS=-O2 
LDFLAGS=-lm

all: $(PRODUCT)

rebuild: clean all

$(PRODUCT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) -c -MMD -MP $(CFLAGS) -I$(NR)/include $< -o $@ 

# Let make read the dependency files and handle them.
-include $(DEPS)

.c.o:	
	$(CC)  $(CFLAGS)-c $< 

clean:
	rm -f *.o
