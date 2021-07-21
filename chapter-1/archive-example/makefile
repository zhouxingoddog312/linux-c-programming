ARFLAGS=crv
program:libfoo.a
	$(CC) -o program program.c -L. -lfoo
libfoo.a:fred.o bill.o
	$(AR) $(ARFLAGS) $@ $^
.PHONY:clean

clean:
	$(RM) ./program ./*.o ./*.a
