DIST_DIR=$(PWD)/cncocr_distrib

all: dist

parser:
	cd CnCLPGParser && ant dist -Ddist.dir=$(DIST_DIR)

prepare:
	mkdir -p $(DIST_DIR)/include $(DIST_DIR)/lib

dist: prepare parser dist_src

dist_src:
	$(MAKE) -C src dist DIST_DIR=$(DIST_DIR)

clean:
	-rm -Rf $(DIST_DIR)
	-rm -Rf CnCLPGParser/classes/
	-make -C src clean
