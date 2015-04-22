ARCHIVE = common.tar.xz
MANIFEST = manifest.txt
EXTRA_DIST = $(ARCHIVE)

commondir = $(datadir)/common

install-data-hook:
	$(TAR_J) -xvf $(ARCHIVE) -C $(commondir) > $(MANIFEST)

uninstall-local:
	cd $(commondir) && cat $(MANIFEST) | xargs rm -f && rm $(MANIFEST)
