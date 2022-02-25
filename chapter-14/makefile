.PHONY:all clean FORCE
object=sem1 shm1 shm2 msg1 msg2
temp=$(word 1,$(object))
all:shm1 shm2 msg1 msg2
	$(CC) $(temp).c -o $(temp) 
sem1:FORCE
	@$(CC) $@.c -o $@
	./$@ 1 &
	./$@
shm1andshm2:shm1 shm2
	./$(word 1,$^) &
	./$(word 2,$^)
shm1: shm1.c shm_com.h
shm2: shm2.c shm_com.h
msg1andmsg2:msg1 msg2 FORCE
	./msg2;./msg1
msg1: msg1.c
msg2: msg2.c
clean:
	$(RM) ./a.out ./debug $(object)
