VPATH = src

# Library products
ALL_LIBS = foenix.a

# Common source files
ASM_SRCS = foenix-startup.s stub_putchar.s
C_SRCS = stub_write.c stub_lseek.c stub_close.c

# Object files
OBJS = $(ASM_SRCS:%.s=%.o) $(C_SRCS:%.c=%.o)

%.o: %.s
	as65816 --core=65816 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%.o: %.c
	cc65816 --core=65816 -O2 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

all: $(ALL_LIBS)

foenix.a: $(OBJS)
	(cd obj ; nlib ../$@ $^)

clean:
	-(cd obj ; rm $(OBJS) $(OBJS:%.o=%.lst))
	-rm $(ALL_LIBS)
