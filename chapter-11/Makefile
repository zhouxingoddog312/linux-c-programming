.PHONY:all clean FORCE

object=system1 system2 pexec fork1 wait fork2 upper useupper
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
fork2:fork2.c FORCE
	@$(CC) $< -o $@
	@./$@ &
	@sleep 3;ps -al
useupper:upper.c useupper.c FORCE
	@for target in $(filter %.c,$^);\
	do $(CC) $${target} -o $${target%.*};\
	done
	@./$@ text
clean:
	$(RM) $(object) ./a.out
