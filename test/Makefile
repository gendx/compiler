SHELL := /bin/bash
COMPILER := ../build/compiler
RETURN := return
SRC := $(shell find . -name '*.lit')
TST := $(SRC:.lit=.test)

%.test: %.lit
	@$(eval RET=$(shell $(COMPILER) < $< > /dev/null 2>&1 ; echo $$?) ) \
	 $(eval EXPECT=`cat $(RETURN) | grep '$* ' | cut -d' ' -f2 -`) \
	    if [ "$(EXPECT)" == "" ] ; then \
	       echo [ERROR] $< ; \
	       echo No exit code expected ; \
	       exit 2 ; \
	    elif [ $(RET) == $(EXPECT) ] ; then \
	       echo [OK] $< ; \
	    else \
	       echo [FAIL] $< ; \
	       echo Expected exit code $(EXPECT) but got $(RET) ; \
	       exit 1 ; \
	    fi ; \

.PHONY: test

test: $(TST)

