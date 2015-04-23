ARCHIVE = $(srcdir)/common.tar.xz
MANIFEST = manifest.txt
OUTDIR = $(DESTDIR)$(datadir)/common
MKDIR_CMD = $(MKDIR_P) '$(OUTDIR)'
TAR_CMD = $(TAR_J) -xvf $(ARCHIVE) -C '$(OUTDIR)' > '$(OUTDIR)/$(MANIFEST)'
EXTRA_DIST = $(ARCHIVE)

install-data-local:
	@echo " $(MKDIR_CMD)"; \
	$(MKDIR_CMD) || exit 1; \
	echo " $(TAR_CMD)"; \
	$(TAR_CMD) || exit 1

uninstall-local:
	( cd '$(OUTDIR)' && cat $(MANIFEST) | xargs rm -f && rm $(MANIFEST) )
