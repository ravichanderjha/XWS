################################################################################
# Makefile                                                                     #
#                                                                              #
# Description: This file contains the make rules for Liso server project.      #
#                                                                              #
# Authors: Wenjun Zhang <wenjunzh@andrew.cmu.edu>                              #
#                                                                              #
################################################################################
CC = gcc
LD = gcc
CFLAGS = `pkg-config --cflags glib-2.0 gio-2.0 gtk+-3.0`
LDFLAGS = `pkg-config --libs glib-2.0 gio-2.0 gtk+-3.0`

PROG = pro.c xorz.c log.c


pro:
	$(CC) -o $@ $(PROG) $(CFLAGS) $(LDFLAGS)

clean:
	@rm -rf pro.exe
