# simple make file
# September 2004
SOURCES=updateConfigDist.c
PRODUCT=$(HOME)/bin/updateConfigDist_sqW




CFLAGS=-lm -O2 

all: $(PRODUCT)

$(PRODUCT) : $(SOURCES)
	$(CC) $(CFLAGS) -o $(PRODUCT) $(SOURCES)
