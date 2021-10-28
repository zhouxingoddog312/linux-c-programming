.PHONY:all clean FORCE
object=memory1 memory2 memory3
all:

memory1:memory1.c FORCE
	@echo "申请一个1M的内存空间，并写入hello world，然后打印出来"
	@$(CC) $< -o $@
	./$@
memory2:memory2.c FORCE
	@echo "申请机器物理内存两被的内存空间"
	@$(CC) $< -o $@
	./$@
memory3:memory3.c FORCE
	@echo "每次申请1K内存空间并写入内容，等待系统终止这个进程"
	@$(CC) $< -o $@
	./$@
clean:
	$(RM) $(object)
