# https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# https://gitlab.fit.cvut.cz/husekrad/pa2-cvika-2022/blob/master/cv10/semestralka/Makefile

LOGIN = rezackry
CXX = g++
BASIC_FLAGS = -std=c++17 -O2 -g -Wall -pedantic
FLAGS =
LIBS = -lSDL2

ZIP = Makefile Doxyfile DOCUMENTATION.md zadani.txt prohlaseni.txt \
  .gitignore $(wildcard examples/*) $(wildcard src/*)

SOURCES = $(call rwildcard,src, *.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, ${SOURCES})
DEPS = $(patsubst src/%.cpp, build/%.dep, ${SOURCES})
BUILD_DIRS = build/engine/components build/engine/processors build/game/level/scripts build/game/scripts

.PHONY: all compile run valgrind doc clean count zip

all: compile doc

compile: ${LOGIN}

${LOGIN}: ${OBJECTS}
	@mkdir -p ${BUILD_DIRS}
	${CXX} ${BASIC_FLAGS} ${FLAGS} $^ -o $@ ${LIBS}

build/main.o: src/main.cpp
	@mkdir -p ${BUILD_DIRS}
	${CXX} ${BASIC_FLAGS} ${FLAGS} -c $< -o $@

build/%.o: src/%.cpp src/%.hpp
	@mkdir -p ${BUILD_DIRS}
	${CXX} ${BASIC_FLAGS} ${FLAGS} -c $< -o $@

run: compile
	./${LOGIN}

__test-setup:
	@rm -f build/main.o # Force rebuild main.cpp
	$(eval FLAGS=-fsanitize=address -DTEST)

test: __test-setup compile
	./${LOGIN} test

__dev-setup:
	@rm -f build/main.o # Force rebuild main.cpp
	$(eval FLAGS=-fsanitize=address)

dev: __dev-setup compile
	./${LOGIN}

valgrind: compile
	valgrind ./${LOGIN}

doc: Doxyfile
	doxygen

open-doc: doc
	google-chrome doc/index.html &

count:
	@cat $(call rwildcard,src, *.cpp) | wc -l
	@cat $(call rwildcard,src/engine, *.hpp) | wc -l
	@cat $(call rwildcard,src/game, *.hpp) | wc -l

clean:
	rm -rf build doc
	rm -f ${LOGIN}
	rm -f examples/singlePlayerSave

zip: ${LOGIN}.zip

format:
	find src -path "vendor/*" -prune -iname "*.hpp" -o -iname "*.cpp" | xargs clang-format -i

${LOGIN}.zip: ${ZIP}
	rm -rf tmp/
	rm -f $@
	mkdir -p tmp/${LOGIN}/
	cp --parents -r $^ tmp/${LOGIN}/
	cd tmp/ && zip -r ../$@ ${LOGIN}/
	rm -rf tmp/

build/%.dep: src/%.cpp ${SOURCES}
	@mkdir -p ${BUILD_DIRS}
	${CXX} -MM -MT $(patsubst src/%.cpp, build/%.o, $<) $< > $@

include ${DEPS}