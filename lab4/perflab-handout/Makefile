# Student's Makefile for the CS:APP Performance Lab
TEAM = myteam
VERSION = 1
HANDINDIR = /home/cjb/csapp_lab/lab4/perflab-handout

CC = gcc
CFLAGS = -Wall -O2 -m32
LIBS = -lm -lpthread

OBJS = driver.o kernels.o fcyc.o clock.o

all: driver

driver: $(OBJS) fcyc.h clock.h defs.h config.h
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o driver

handin:
	cp kernels.c $(HANDINDIR)/$(TEAM)-$(VERSION)-kernels.c

clean: 
	-rm -f $(OBJS) driver core *~ *.o


