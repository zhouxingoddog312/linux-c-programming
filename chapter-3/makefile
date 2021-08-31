all:

define run-test
@$(CC) $@.c -o $@
endef
simple_write:FORCE
	$(run-test)
	@./$@
	@$(RM) ./$@
simple_read:FORCE
	$(run-test)
	echo "hello there"|./$@
	./$@<draft1.txt
	@$(RM) ./$@
copy_system:FORCE
	@cd $@;$(CC) $@.c -o $@;sh createinputfile.sh;TIMEFORMAT="" time ./$@;echo;echo "This is file.in";cat file.in;echo;echo "This is file.out";cat file.out;echo;$(RM) ./$@ ./file.in ./file.out
copy_block:FORCE
	@cd copy_system;$(CC) $@.c -o $@;sh createinputfile.sh;TIMEFORMAT="" time ./$@;echo;echo "This is file.in";cat file.in;echo;echo "This is file.out";cat file.out;echo;$(RM) ./$@ ./file.in ./file.out
.PHONY:clean FORCE

clean:
	$(RM) a.out
