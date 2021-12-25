.PHONY:all clean FORCE

object=system1 system2 pexec fork1
all:

system1:system1.c FORCE
	@$(CC) $< -o $@
	@./$@
system2:system2.c FORCE
	@$(CC) $< -o $@
	@./$@
pexec:pexec.c FORCE
	@$(CC) $< -o $@
	@./$@
fork1:fork1.c FORCE
	@$(CC) $< -o $@
	@./$@
wait:wait.c FORCE
	@$(CC) $< -o $@
	@./$@
clean:
	$(RM) $(object) ./a.out
