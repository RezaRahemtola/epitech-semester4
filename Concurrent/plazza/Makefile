##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

all: build/Makefile plazza

build:
	mkdir -p build

build/Makefile: build
	cd build && $(RM) CMakeCache.txt && cmake -G "Unix Makefiles" ..
	$(MAKE) -C build

build/plazza: build/Makefile
	$(MAKE) -C build plazza

build/tests_plazza: build/Makefile
	$(MAKE) -C build tests_plazza

plazza: build/plazza
	cp build/plazza .

clean:
	$(MAKE) -C build clean

fclean: clean
	$(RM) plazza tests_plazza

tests_run:
	cd build && $(RM) CMakeCache.txt && cmake -G "Unix Makefiles" -DENABLE_TESTS=ON ..
	$(MAKE) -C build tests_plazza
	build/tests_plazza
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re tests_run