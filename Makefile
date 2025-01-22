_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -I./include
LDFLAGS = -lSDL -lm

.PHONY: clean doc check-syntax compile-all launch-tests

# rule to generate the doxygen documentation
doc:
	doxygen conf/doxygen.conf

# rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

# compile rules
%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

# you should put all the .o files corresponding to your .c files as prerequisites of
# this rule (see examples)
# \ allows to go on the next line
check-syntax: example-main.o read-file-formatted.o read-file-text.o \
	write-fact.o particles.o test-dummy.o disc.o snow.o 

# put all the rules to build your applications and tests here (see examples)
example-main: example-main.o
	$(CC) $(CFLACS) -o example-main example-main.o

example-string: example-string.o
	$(CC) $(CFLACS) -o example-string example-string.o

read-file-formatted: read-file-formatted.o
	$(CC) $(CFLACS) -o read-file-formatted read-file-formatted.o

read-file-text: read-file-text.o
	$(CC) $(CFLACS) -o read-file-text read-file-text.o

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o write-fact write-fact.o

test-dummy: test-dummy.o
	$(CC) $(CFLACS) -o test-dummy test-dummy.o

particle: particle.o
	$(CC) $(CFLAGS) -o particle -lm particle.o

loader: loader.o
	$(CC) $(CFLACS) -o loader loader.o

events: events.o
	$(CC) $(CFLACS) -o events events.o

simulation: simulation.o 
	$(CC) $(CFLACS) -o simulation simulation.o $(LDFLAGS)

# the snow app. Beware, for graphical applications, you MUST add $(LDFLAGS)!
snow: snow.o disc.o ./include/disc.h
	$(CC) $(CFLAGS) -o snow snow.o disc.o $(LDFLAGS)

# put all your applications and tests executables as prerequisite of this rule
# \ allows to go to the next line
compile-all: test-particle test-loader test-events clash-of-particles

# add all your test executables in the following variable. You should respect
# the order given in the project text
# \ allows to go to the next line
ALL_TESTS = test-particle test-loader test-events

launch-tests: $(ALL_TESTS)
	for x in $(ALL_TESTS); do ./$$x --all; done


test-particle: ./tests/test-particle.c ./src/particle.c ./include/particle.h 
	$(CC) $(CFLAGS) -o test-particle ./tests/test-particle.c ./src/particle.c $(LDFLAGS)


test-loader: ./tests/test-loader.c ./src/loader.c ./include/loader.h 
	$(CC) $(CFLAGS) -o test-loader ./tests/test-loader.c ./src/loader.c $(LDFLAGS)

test-events: ./tests/test-events.c ./src/events.c ./include/events.h 
	$(CC) $(CFLAGS) -o test-events ./tests/test-events.c ./src/events.c $(LDFLAGS)


# add all .c, .h and .txt files in repository
svn-add-all-files:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q


clash-of-particles: ./src/particle.c ./include/particle.h ./src/disc.c ./include/disc.h ./src/loader.c ./include/loader.h ./src/events.c ./include/events.h ./src/simulation.c ./include/simulation.h ./tests/clash-of-particles.c
	$(CC) $(CFLAGS) -o clash-of-particles ./src/particle.c ./src/disc.c ./src/loader.c ./src/events.c ./src/simulation.c ./tests/clash-of-particles.c $(LDFLAGS)


