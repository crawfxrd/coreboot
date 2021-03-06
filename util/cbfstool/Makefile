top ?= $(abspath ../..)
objutil ?= $(top)/util

CONFIG_FMD_GENPARSER ?= n

HOSTCC ?= $(CC)
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
INSTALL ?= /usr/bin/env install
OBJCOPY ?= objcopy

VBOOT_SOURCE ?= $(top)/3rdparty/vboot
VBOOT_HOST_BUILD ?= $(abspath $(objutil)/vboot_lib)

.PHONY: all
all: cbfstool ifittool fmaptool rmodtool ifwitool cbfs-compression-tool

cbfstool: $(objutil)/cbfstool/cbfstool

fmaptool: $(objutil)/cbfstool/fmaptool

rmodtool: $(objutil)/cbfstool/rmodtool

ifwitool: $(objutil)/cbfstool/ifwitool

ifittool: $(objutil)/cbfstool/ifittool

cbfs-compression-tool: $(objutil)/cbfstool/cbfs-compression-tool

.PHONY: clean cbfstool ifittool fmaptool rmodtool ifwitool cbfs-compression-tool
clean:
	$(RM) fmd_parser.c fmd_parser.h fmd_scanner.c fmd_scanner.h
	$(RM) $(objutil)/cbfstool/cbfstool $(cbfsobj)
	$(RM) $(objutil)/cbfstool/fmaptool $(fmapobj)
	$(RM) $(objutil)/cbfstool/rmodtool $(rmodobj)
	$(RM) $(objutil)/cbfstool/ifwitool $(ifwiobj)
	$(RM) $(objutil)/cbfstool/ifittool $(ifitobj)
	$(RM) $(objutil)/cbfstool/cbfs-compression-tool $(cbfscompobj)
	$(RM) -r $(VBOOT_HOST_BUILD)

linux_trampoline.c: linux_trampoline.S
	rm -f linux_trampoline.c
	$(CC) -m32 -o linux_trampoline linux_trampoline.S -ffreestanding -nostdlib -nostdinc -Wl,--defsym=_start=0
	$(OBJCOPY) -Obinary -j .data linux_trampoline trampoline
	echo "/* This file is automatically generated. Do not manually change */" > trampoline.c
	echo "/* SPDX-License-Identifier: GPL-2.0-only */" >> trampoline.c
	xxd -c 16 -i trampoline >> trampoline.c
	mv trampoline.c linux_trampoline.c
	rm linux_trampoline trampoline

.PHONY: install distclean help
install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	$(INSTALL) cbfstool $(DESTDIR)$(BINDIR)
	$(INSTALL) fmaptool $(DESTDIR)$(BINDIR)
	$(INSTALL) rmodtool $(DESTDIR)$(BINDIR)
	$(INSTALL) ifwitool $(DESTDIR)$(BINDIR)
	$(INSTALL) ifittool $(DESTDIR)$(BINDIR)
	$(INSTALL) cbfs-compression-tool $(DESTDIR)$(BINDIR)

distclean: clean

help:
	@echo "cbfstool & associated tools"
	@echo "Targets: all, clean, distclean, help"
	@echo "  cbfstool - Manipulate CBFS images"
	@echo "  fmaptool - Compile Flashmap descriptor (fmd) files"
	@echo "  rmodtool - Create relocatable modules"
	@echo "  ifwitool - Manipulate Intel FW Image (IFWI)"
	@echo "  ifittool - Manipulate Intel FW Interface Table (FIT)"
	@echo "  cbfs-compression-tool - benchmark compression algorithms"

ifneq ($(V),1)
.SILENT:
endif

include Makefile.inc

$(objutil)/cbfstool/cbfstool.o: $(VBOOT_SOURCE)/firmware/include/vb2_sha.h

$(VBOOT_SOURCE)/firmware/include/vb2_sha.h:
	cd $(VBOOT_SOURCE) && git submodule update --init .
