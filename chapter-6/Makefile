.PHONY:clean all FORCE
object=screen1 moveadd ipmode multiw1 subsc1 keypad color pad curses_app
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
subsc1:subsc1.c FORCE
	$(CC) $< -o $@ $(LDFLAGS)
	./$@
keypad:keypad.c FORCE
	$(CC) $< -o $@ $(LDFLAGS)
	./$@
color:color.c FORCE
	$(CC) $< -o $@ $(LDFLAGS)
	./$@
pad:pad.c FORCE
	$(CC) $< -o $@ $(LDFLAGS)
	./$@
curses_app:curses_app.c FORCE
	$(CC) $< -o $@ $(LDFLAGS)
	./$@

clean:
	$(RM) ./a.out $(object)
