#
# Makefile for sash
#
# The HAVE_GZIP definition adds the -gzip and -gunzip commands.
# The HAVE_LINUX_ATTR definition adds the -chattr and -lsattr commands.
# The HAVE_LINUX_MOUNT definition makes -mount and -umount work on Linux.
# The HAVE_BSD_MOUNT definition makes -mount and -umount work on BSD.
# The MOUNT_TYPE definition sets the default file system type for -mount.
#
HAVE_GZIP		= 1
HAVE_LINUX_ATTR		= 0
HAVE_LINUX_MOUNT	= 1
HAVE_BSD_MOUNT		= 0
MOUNT_TYPE		= '"ext3"'

# CC = g++
CFLAGS = -g -Wall -Wmissing-prototypes \
	-DHAVE_GZIP=$(HAVE_GZIP) \
	-DHAVE_LINUX_ATTR=$(HAVE_LINUX_ATTR) \
	-DHAVE_LINUX_MOUNT=$(HAVE_LINUX_MOUNT) \
	-DHAVE_BSD_MOUNT=$(HAVE_BSD_MOUNT) \
	-DMOUNT_TYPE=$(MOUNT_TYPE) \

# LDFLAGS = -s

LIBS = -lz # -lfl


BINDIR = /bin
MANDIR = /usr/man/man1

OBJS = sash.o cmds.o cmd_dd.o cmd_ed.o cmd_grep.o cmd_ls.o cmd_tar.o \
        cmd_gzip.o cmd_find.o cmd_file.o cmd_chattr.o cmd_ar.o utils.o \
	y.tab.o lex.yy.o eval_upmc.o

## this is the make rule to use lex to generate the file lex.yy.c from
## our file calc.l


sash:	$(OBJS) y.tab.o lex.yy.o 
	$(CC) $(LDFLAGS) -o sash $(OBJS) $(LIBS)

y.tab.c y.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.o: y.tab.h lex.yy.c 

lex.yy.c: lexer.lex
	$(LEX) lexer.lex

clean:
	rm -f $(OBJS) sash y.tab.* lex.yy.*

install: sash
	cp sash $(BINDIR)/sash
	cp sash.1 $(MANDIR)/sash.1

$(OBJS):	sash.h
