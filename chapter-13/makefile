.PHONY:all clean FORCE

object=popen1 popen2 popen3 popen4 pipe1


all:

popen1:popen1.c FORCE
	@$(CC) $< -o $@
	@./$@
popen2:popen2.c FORCE
	@$(CC) $< -o $@
	@echo "程序输出结果"
	./$@
	@echo "命令行输出结果"
	echo "Once upon a time, there was..."|od -c
popen3:popen3.c FORCE
	@$(CC) $< -o $@
	@./$@
popen4:popen4.c FORCE
	@$(CC) $< -o $@
	@echo "程序输出结果"
	./$@
	@echo "命令行输出结果"
	cat popen*.c|wc -l
pipe1:pipe1.c FORCE
	@$(CC) $< -o $@
	@./$@
clean:
	$(RM) ./a.out $(object)
