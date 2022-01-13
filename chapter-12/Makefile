.PHONY:all clean FORCE
LDFLAGS=-lpthread
CPPFLAGS=-D_REENTERANT
object=thread1 thread2 thread3 thread3a

all:

thread1:FORCE
	@$(CC) $(CPPFLAGS) $@.c -o $@ $(LDFLAGS)
	@./$@
thread2:FORCE
	@$(CC) $(CPPFLAGS) $@.c -o $@ $(LDFLAGS)
	@echo "可能需要等待数秒"
	@./$@
thread3:FORCE
	@$(CC) $(CPPFLAGS) $@.c -o $@ $(LDFLAGS)
	@./$@
thread3a:FORCE
	@$(CC) $(CPPFLAGS) $@.c -o $@ $(LDFLAGS)
	@./$@

clean:
	$(RM) ./a.out $(object)
