SUBDIRS := $(wildcard *)

all: $(SUBDIRS)
$(SUBDIRS):
	@if [ -d "$@" ]; then echo "Day $@: $$(make -C $@ run | grep 'TIME')"; fi

.PHONY: all $(SUBDIRS)
