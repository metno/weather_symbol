
#-----------------------------------------------------------------------------
# Debian stuff
#-----------------------------------------------------------------------------

PKG_DIR = $(PACKAGE)-$(VERSION)
DEBIAN_DIR = $(PKG_DIR)/debian
DEBIAN_PACKAGE = `head -n1 $(top_srcdir)/debian_files/changelog | sed "s/ (/_/" | sed "s/_.*//"`_$(VERSION)
#DEBIAN_PACKAGE = $(PACKAGE)_$(VERSION)
ARCH = `dpkg-architecture -qDEB_HOST_ARCH_CPU`
DEBIAN_PACKAGE_NAME_BASE = `head -n1 $(top_srcdir)/debian_files/changelog | sed "s/ (/_/" | sed "s/).*//"`
DEBIAN_PACKAGE_NAME = *.deb
DEBIAN_SOURCE_PACKAGE_NAME = *.dsc

dist-debian: dist clean-debian
	tar xvzf $(PKG_DIR).tar.gz
	cp $(PKG_DIR).tar.gz $(DEBIAN_PACKAGE).orig.tar.gz

prepare-debian:
	rm -rf $(DEBIAN_DIR)
	mkdir -p $(DEBIAN_DIR)
	cp -r $(top_srcdir)/debian_files/* $(DEBIAN_DIR)
	chmod 774 $(DEBIAN_DIR)/rules
	if [ -e $(DEBIAN_DIR)/templates ]; then  debconf-updatepo --podir=$(DEBIAN_DIR)/po; fi

update-debian: prepare-debian
	cd $(PKG_DIR) && dpkg-buildpackage -rfakeroot -us -uc -nc
	lintian $(DEBIAN_PACKAGE_NAME) $(DEBIAN_SOURCE_PACKAGE_NAME)

build-debian:
	cd $(PKG_DIR) && dpkg-buildpackage -rfakeroot -us -uc -sa
	lintian $(DEBIAN_PACKAGE_NAME) $(DEBIAN_SOURCE_PACKAGE_NAME)

debian: dist-debian prepare-debian build-debian

clean-debian:
	debclean
	rm -rf $(PKG_DIR) $(DEBIAN_PACKAGE)*
