CXX = g++

AUTOR = thucydil AKA Darkhan-Sol0

VERSION = 0.69
BRANCH = develop

EXEC = 3D_Viewer
APP = build/opengl_cmake

MAIN = $(wildcard main.cpp)
MAIN_O = $(patsubst %.cpp, %.o, $(MAIN))


SOURCE_GUI = $(wildcard opengl_cmake/*.cpp)
HEADER_GUI = $(wildcard opengl_cmake/*.hpp)

SOURCE = $(wildcard common/*.cpp)
HEADER = $(wildcard common/*.hpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCE))

SOURCE_TESTFILE = $(wildcard test_files/*.cpp)
HEADER_TESTFILE = $(wildcard test_files/*.hpp)
OBJECTS_TESTFILE = $(patsubst %.cpp, %.o, $(SOURCE_TESTFILE))

CXXFLAGS = -std=c++17 -pthread -Wall -Werror -Wextra -lncurses -lGL $(QTLIBS)
CXXLIBFLAGS = -std=c++17 -lgtest_main -lgtest -lGL $(QTLIBS)

VALGRIND = valgrind --tool=memcheck --leak-check=yes

CLANG = clang-format -style=Google

all: install

clean: clean_test clean_report
	rm -rf *.o build gui/ui_mainwindow.hpp

install: clean uninstall
	mkdir build
	cd ./build/ && cmake ../opengl_cmake && make
	# $(CXX) $(MAIN_O) $(EXEC_GUI) $(EXEC_A) -o $(EXEC) $(CXXFLAGS) 
	# rm -rf *.a
	# @mkdir -p ~/$(EXEC)
	# install ./$(EXEC) ~/$(EXEC)/

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)


%.a: %.moc %.o 
	ar rc $@ $^
	ranlib $@
	rm -rf $^

uninstall:
	rm -rf ~/$(EXEC) $(EXEC)

run:
	./$(APP)

val_test:
	$(VALGRIND) ./test

dvi:
	doxygen Doxyfile

dvi_open:
	xdg-open DVI/html/index.html

dvi_clean:
	rm -rf DVI

dist:
	mkdir dist
	cp -a ./common ./dist/
	cp -a ./opengl_cmake/ ./dist/
	cp -a ./primitives/ ./dist/ 
	cp -a ./test_files/ ./dist/
	cp -a ./Makefile ./dist/ 
	cp -a ./readme.texi ./dist/ 
	cp -a ./ui.cfg ./dist/ 
	tar -czf $(EXEC)_$(VERSION).tar.gz ./dist/
	rm -rf ./dist/


test: $(OBJECTS) $(OBJECTS_TESTFILE)
	$(CXX) $(OBJECTS_TESTFILE) $(OBJECTS) -o test $(CXXLIBFLAGS) 
	rm -rf $(OBJECTS_TESTFILE) $(OBJECTS)
	./test

gcov_report: clean_test clean_report gcov_test open_report

gcov_test:
	$(CXX) --coverage $(SOURCE_TESTFILE) $(SOURCE) $(CXXLIBFLAGS) -o test
	./test
	gcovr -r . --html-details -o gcov_report.html
	# ~/.local/bin/gcovr -r . --html-details -o gcov_report.html
	mkdir GCOVRreport
	mv *.html *.css GCOVRreport
	rm -rf *.gcno *.gcda

lcov_report: clean_test clean_report lcov_test open_report_l

lcov_test: clean_test clean_report
	$(CXX) -fprofile-arcs -ftest-coverage $(SOURCE_TESTFILE) $(SOURCE) $(CXXLIBFLAGS) -o test
	./test
	lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,mismatch --ignore-errors inconsistent 
	lcov --remove coverage.info '/usr/include/*' -o coverage.info
	genhtml coverage.info --output-directory coverage_report
	rm -rf *.gcno *.gcda

open_report_l:
	xdg-open coverage_report/index.html

open_report:
	xdg-open GCOVRreport/gcov_report.html

clean_test:
	rm -rf test

clean_report:
	rm -rf *.gcno *.gcda *.html *.css GCOVRreport *.info coverage_report

check_format:
	$(CLANG) -n $(SOURCE) $(HEADER) $(SOURCE_GUI) $(HEADER_GUI) $(SOURCE_TESTFILE) $(HEADER_TESTFILE)

set_format:
	$(CLANG) -i $(SOURCE) $(HEADER) $(SOURCE_GUI) $(HEADER_GUI) $(SOURCE_TESTFILE) $(HEADER_TESTFILE)

commit:
	@read -p "Enter commit message: " input; \
	git add -A; \
	git commit -m "$$input - $(EXEC) v:$(VERSION) - $(shell date +'%Y-%m-%d %H:%M')"; \
	git push origin $(BRANCH)