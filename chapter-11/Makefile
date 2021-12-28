.PHONY:all clean FORCE

object=system1 system2 pexec fork1 wait fork2 upper useupper ctrlc1 alarm ctrlc2
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
ctrlc1:ctrlc1.c FORCE
	@$(CC) $< -o $@
	@echo "自己运行该文件"
alarm:alarm.c FORCE
	@$(CC) $< -o $@
	@echo "自己运行该文件"
ctrlc2:ctrlc2.c FORCE
	@$(CC) $< -o $@
	@echo "自己运行该文件"
clean:
	$(RM) $(object) ./a.out
