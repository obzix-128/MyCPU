.PHONY : all
all: $(wildcard */.)
	@cd SPU && make $@
	@cd Assembler && make $@

.PHONY : clean
clean: $(wildcard */.)
	@cd SPU && make $@
	@cd Assembler && make $@
