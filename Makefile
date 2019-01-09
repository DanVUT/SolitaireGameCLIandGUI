all:
	$(MAKE) -C src/cli
	$(MAKE) -C src/gui
doxygen:
	$(MAKE) doxygen -C src/cli
	$(MAKE) doxygen -C src/gui
clean:
	$(MAKE) clean -C src/cli
	$(MAKE) clean -C src/gui
