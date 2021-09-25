.PHONY:clean all FORCE
object=screen1 moveadd ipmode multiw1
LDFLAGS=-lncurses
all:

screen1:screen1.c FORCE
	$(CC) $< -o $@ $(LDFLAGS)
	./$@
moveadd:moveadd.c FORCE
	$(CC) $< -o $@ $(LDFLAGS)
	./$@
ipmode:ipmode.c FORCE
	$(CC) $< -o $@ $(LDFLAGS)
	./$@
multiw1:multiw1.c FORCE
	$(CC) $< -o $@ $(LDFLAGS)
	./$@

clean:
	$(RM) ./a.out $(object)
