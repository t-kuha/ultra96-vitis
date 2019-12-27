#
# This file is the freeimage recipe.
#

SUMMARY = "Freeimage"
SECTION = "PETALINUX/apps"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://license-gplv2.txt;md5=1fbed70be9d970d3da399f33dae9cc51"

SRC_URI = " \
	file://libfreeimage.so \
	file://libfreeimage.so.3 \
	file://libfreeimage-3.18.0.so \
	file://license-gplv2.txt \
	"

S = "${WORKDIR}"

INSANE_SKIP_${PN} += "already-stripped"

do_install() {
	     install -d ${D}/${libdir}
             install -m 0655 ${S}/libfreeimage-3.18.0.so ${D}/${libdir}
	     install -m 0655 ${S}/libfreeimage.so.3 ${D}/${libdir}
             install -m 0655 ${S}/libfreeimage.so ${D}/${libdir}
}

INSANE_SKIP_${PN} += "ldflags"
INSANE_SKIP_${PN} += "dev-so"

FILES_SOLIBSDEV = ""

FILES_${PN} = "${libdir}/*"
