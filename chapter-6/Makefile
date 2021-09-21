.PHONY:clean all FORCE
object=screen1
LDFLAGS=-lcurses
all:

screen1:screen1.c FORCE
	$(CC) $< -o $@ $(LDFLAGS)
	./$@


clean:
	$(RM) ./a.out $(object)
