
COMMONOBJS = bpf_load.o

EXE= main
TESTOBJS = $(EXE).o

PROGS= $(EXE)

OBJS= $(COMMONOBJS) $(TESTOBJS)

linuxhdrs ?= /kernel-src

LINUXINCLUDE =	-I$(linuxhdrs)/samples/bpf \
		-I$(linuxhdrs)/tools/perf \
		-I$(linuxhdrs)/tools/include \
		-I$(linuxhdrs)/arch/x86/include/uapi \
                -I$(linuxhdrs)/arch/x86/include/generated/uapi \
                -I$(linuxhdrs)/include/generated/uapi \
                -I$(linuxhdrs)/include/uapi \
                -I$(linuxhdrs)/include \
		-I$(linuxhdrs)/tools/lib


BPFTOOLS = $(linuxhdrs)/samples/bpf
BPFLOADER = $(BPFTOOLS)/bpf_load.c

prefix ?= /usr/local

INSTALLPATH = $(prefix)/bin

install_PROGRAM = install
install_DIR = install -d

LDLIBS = -lelf -lbpf

all: $(EXE)

debug: all

.PHONY: clean

clean:
	rm -f $(OBJS) $(PROGS)

bpf_load.o: $(BPFLOADER)
	$(CC) $(DEBUG_FLAGS) -g -Wno-unused-variable -I../include $(LINUXINCLUDE) -c $(BPFLOADER) -o bpf_load.o $(CFLAGS)

%.o: %.c
	$(CC) $(DEBUG_FLAGS) -g -Wno-unused-variable -I../include $(LINUXINCLUDE) -c -o $@ $< $(CFLAGS)

$(PROGS): $(OBJS)
	$(CC) -g -o $@ $(@).o $(COMMONOBJS) $(CFLAGS) $(LDLIBS)


install: $(PROGS) $(SCRIPTS)
	$(install_DIR) -d $(INSTALLPATH) ; \
	$(install_PROGRAM) $^ -t $(INSTALLPATH)

uninstall: $(PROGS) $(SCRIPTS)
	cd $(INSTALLPATH); rm -f $^
