NAME = Project
CLANG_FORMAT ?= clang-format

.PHONY: all
all: clean install

.PHONY: dvi
dvi:
	open readme.html

.PHONY: clean
clean:
	@rm -rf ../Archive_3dViewer_v2.1
	@rm -rf *tgz
	@rm -rf build*
	@rm -rf ./3dViewer/build*
	@rm -rf ../Archive_3dViewer_v2.1.zip
	@rm -rf ../Archive_3dViewer_v2.1.tgz
	@rm -rf ./Tests/build*

.PHONY: install
install:
	make clean
	mkdir build && cd build && cmake ../CMakeLists.txt && make -j8
	cd build/3dViewer.app/Contents/MacOS/ && ./3dViewer

.PHONY: test
test:
	cd Tests && rm -rf build*
	cd Tests && mkdir build && cd build && cmake ../CMakeLists.txt && cmake --build . -j8 && ctest

.PHONY: uninstall
uninstall:
	@rm -rf build*
	@rm -rf ./3dViewer/build*

.PHONY: open
open:
	cd build/3dViewer.app/Contents/MacOS/ && ./3dViewer

.PHONY: open_leaks
open_leaks:
	cd build/3dViewer.app/Contents/MacOS/ && CK_FORK=no leaks --atExit -- ./3dViewer

.PHONY: dist
dist:
	rm -rf ../Archive_3dViewer_v2.1/
	mkdir ../Archive_3dViewer_v2.1/
	mkdir ../Archive_3dViewer_v2.1/src
	cp build/3dViewer.app/Contents/MacOS/3dViewer ../Archive_3dViewer_v2.1/src/
	cd .. && tar cvzf Archive_3dViewer_v2.1.tgz ./Archive_3dViewer_v2.1
	@rm -rf ../Archive_3dViewer_v2.1

.PHONY: check
check:
	@find Controlers -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find Models -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find Settings -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find Views -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find Tests -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google

.PHONY: correct
correct:
	@find Controlers -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find Models -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find Settings -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find Views -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find Tests -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google

.PHONY: rebuild
rebuild:
	$(MAKE) clean
	$(MAKE) all

