SHELL := /bin/bash
COMPILER := ../build/compiler
RETURN := return
SRC := $(shell find . -name '*.lit')
TST := $(SRC:.lit=.test)

%.test: %.lit
	@$(COMPILER) < $< > /dev/null 2>&1 ; \
	    if [ "$$?" == `cat $(RETURN) | grep $* | cut -d' ' -f2 -` ] ; then \
	       echo [OK] $< ; \
	    else \
	       echo [FAIL] $< ; \
	       exit 1 ; \
	    fi ; \

.PHONY: test

test: $(TST)

