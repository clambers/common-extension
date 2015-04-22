ARCHIVE = common.tar.xz
MANIFEST = manifest.txt
EXTRA_DIST = $(ARCHIVE)

install-data-hook:
	$(TAR) -xvaf $(ARCHIVE) -C $(COMMON_PATH) > $(MANIFEST)

uninstall-local:
	cd $(COMMON_PATH) && cat $(MANIFEST) | xargs rm -f && rm $(MANIFEST)
