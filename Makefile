VPATH = src

CFLAGS = --core=65816 --target=Foenix --always-inline

# Library products
ALL_LIBS = Foenix-lc-sd.a Foenix-lc-md.a

# Common source files
ASM_SRCS = Foenix-startup.s stub_exit.s  stub_putchar.s dma.s
C_SRCS = $(STUB_SRCS) vram_copy.c vram_fill.c vdma_wait.c
STUB_SRCS = stub_write.c stub_lseek.c stub_close.c

# Object files
OBJS_LC_SD = $(ASM_SRCS:%.s=%-lc-sd.o) $(C_SRCS:%.c=%-lc-sd.o)
OBJS_LC_MD = $(ASM_SRCS:%.s=%-lc-md.o) $(C_SRCS:%.c=%-lc-md.o)

# Add --rtattr to stub files
$(STUB_SRCS:%.c=%-lc-sd.o) : CFLAGS += --rtattr stubs=foenix
$(STUB_SRCS:%.c=%-lc-md.o) : CFLAGS += --rtattr stubs=foenix

%-lc-sd.o: %.s
	as65816 --debug --core=65816 --target=Foenix --code-model=large --data-model=small --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%-lc-sd.o: %.c
	cc65816 $(CFLAGS) --code-model=large --data-model=small --debug -Iinclude --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%-lc-md.o: %.s
	as65816 --debug --core=65816 --target=Foenix --code-model=large --data-model=medium --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%-lc-md.o: %.c
	cc65816 $(CFLAGS) --code-model=large --data-model=medium --debug -Iinclude --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

all: $(ALL_LIBS)

Foenix-lc-sd.a: $(OBJS_LC_SD)
	(cd obj ; nlib ../$@ $^)

Foenix-lc-md.a: $(OBJS_LC_MD)
	(cd obj ; nlib ../$@ $^)

clean:
	-(cd obj ; rm $(OBJS_LC_SD) $(OBJS_LC_SD:%.o=%.lst))
	-(cd obj ; rm $(OBJS_LC_MD) $(OBJS_LC_MD:%.o=%.lst))
	-rm $(ALL_LIBS)
