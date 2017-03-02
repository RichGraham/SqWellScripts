# simple make file
# September 2004
SOURCES=aveNc.c 
PRODUCT=$(HOME)/bin/aveNC_sqW




CFLAGS=-lm -O2 -I$(NR)/include




all: $(PRODUCT)

$(PRODUCT) : $(SOURCES)
	$(CC) $(CFLAGS) -o $(PRODUCT) $(SOURCES)
