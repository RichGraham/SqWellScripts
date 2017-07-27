# simple make file
# September 2004
SOURCES=OP_mapping.c
PRODUCT=$(HOME)/bin/OP_mapping_sqW




CFLAGS=-lm -O2 

all: $(PRODUCT)

$(PRODUCT) : $(SOURCES)
	$(CC) $(CFLAGS) -o $(PRODUCT) $(SOURCES)
