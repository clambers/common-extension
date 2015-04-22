ARCHIVE = common.tar.xz
MANIFEST = manifest.txt
OUTDIR = $(DESTDIR)/$(commondir)
EXTRA_DIST = $(ARCHIVE)

install-data-local:
	$(MKDIR_P) $(OUTDIR)
	$(TAR_J) -xvf $(ARCHIVE) -C $(OUTDIR) > $(MANIFEST)

uninstall-local:
	cd $(OUTDIR) && cat $(MANIFEST) | xargs rm -f && rm $(MANIFEST)
