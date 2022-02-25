.PHONY:all clean FORCE

object=popen1 popen2 popen3 popen4 pipe1 pipe2 pipe3 pipe4 pipe5 fifo1 fifo2 fifo3 fifo4 server client


all:
	for target in $(object);\
	do\
		$(CC) $${target}.c -o $${target};\
	done
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
pipe2:pipe2.c FORCE
	@$(CC) $< -o $@
	@./$@
pipe3andpipe4:pipe3 pipe4
	./$<
pipe3:
pipe4:
pipe5:pipe5.c FORCE
	@$(CC) $< -o $@
	@./$@
fifo1:fifo1.c FORCE
	@$(CC) $< -o $@
	@./$@
	ls -lF /tmp/my_fifo
	cat /tmp/my_fifo&
	echo "Hello World">/tmp/my_fifo
fifo2:fifo2.c FORCE
	$(CC) $< -o $@
fifo3andfifo4:fifo3 fifo4
	./$(word 1,$^)&
	time ./$(word 2,$^)
fifo3:
fifo4:
serverandclient:server client
	./$(word 1,$^)&
	for((i=0;i<5;i++));\
	do\
		./$(word 2,$^)&	\
	done
server:
client:
clean:
	$(RM) ./a.out /tmp/my_fifo $(object)
