CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11
RM = rm -rf
MKDIR = mkdir -p
COPY = cp
CD = cd

SRCDIR = src
DISTDIR = dist
SRCFILE = main.c
EXECFILE = main

build: clean mkdir copy compile

compile:
	$(CC) $(CFLAGS) $(SRCDIR)/$(SRCFILE) -o $(DISTDIR)/$(EXECFILE)

clean:
	$(RM) $(DISTDIR)

mkdir:
	$(MKDIR) $(DISTDIR)

copy:
	$(COPY) $(SRCDIR)/cp1251.txt $(SRCDIR)/iso-8859-5.txt $(SRCDIR)/koi8.txt $(DISTDIR)
