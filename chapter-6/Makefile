.PHONY:clean all FORCE
object=screen1 moveadd ipmode
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

clean:
	$(RM) ./a.out $(object)
