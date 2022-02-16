.PHONY:all clean FORCE
LDFLAGS=-lpthread
CPPFLAGS=-D_REENTERANT
object=thread1 thread2 thread3 thread3a thread4 thread5 thread6 thread7 thread8 thread8a

all:
	for ob in $(object);\
	do\
		$(CC) $(CPPFLAGS) $${ob}.c -o $${ob} $(LDFLAGS);\
	done
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
thread4:FORCE
	@$(CC) $(CPPFLAGS) $@.c -o $@ $(LDFLAGS)
	@./$@
thread5:FORCE
	@$(CC) $(CPPFLAGS) $@.c -o $@ $(LDFLAGS)
	@./$@
thread6:FORCE
	@$(CC) $(CPPFLAGS) $@.c -o $@ $(LDFLAGS)
	@./$@
thread7:FORCE
	@$(CC) $(CPPFLAGS) $@.c -o $@ $(LDFLAGS)
	@./$@
thread8:FORCE
	@$(CC) $(CPPFLAGS) $@.c -o $@ $(LDFLAGS)
	@./$@
thread8a:FORCE
	@$(CC) $(CPPFLAGS) $@.c -o $@ $(LDFLAGS) &>/dev/null
	@./$@
clean:
	$(RM) ./a.out $(object)
