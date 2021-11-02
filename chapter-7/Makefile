.PHONY:all clean FORCE
LDFLAGS=-lgdbm_compat
object=memory1 memory2 memory3 memory4 memory5a memory5b memory6 lock1 lock2 lock3 lock4 lock5 dbm1 dbm2
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
	-./$@
memory4:memory4.c FORCE
	@echo "申请1K内存空间,并一直写入内容直到超过分配的内存，等待系统终止这个进程"
	@$(CC) $< -o $@
	-./$@
memory5a:memory5a.c FORCE
	@echo "先访问空指针，再尝试向空指针写入数据"
	@$(CC) $< -o $@
	-./$@
memory5b:memory5b.c FORCE
	@echo "尝试从0地址处读数据"
	@$(CC) $< -o $@
	-./$@
memory6:memory6.c FORCE
	@echo "申请一块内存，然后释放它"
	@$(CC) $< -o $@
	-./$@
lock1:lock1.c FORCE
	@$(RM) -f /tmp/LCK.test
	@echo "创建一个锁文件，再次检测这个锁文件"
	@$(CC) $< -o $@
	./$@
lock2:lock2.c FORCE
	@$(RM) -f /tmp/LCK.test2
	@echo "启动两个该进程，并观察它们如何协调利用锁文件表示独占权"
	@$(CC) $< -o $@
	./$@ & ./$@
lock3_lock4:lock3.c lock4.c FORCE
	@echo "先对文件进行局部锁定，再测试文件的锁"
	@$(RM) /tmp/test_lock
	@for src in $(filter-out FORCE,$^);\
	do \
		$(CC) $${src} -o $${src%.*}; \
	done
	@./lock3 &
	@sleep 1
	@./lock4
	@$(RM) /tmp/test_lock

lock3_lock5:lock3.c lock5.c FORCE
	@echo "先对文件进行局部锁定，再尝试对文件设置锁"
	@$(RM) /tmp/test_lock
	@for src in $(filter-out FORCE,$^);\
	do \
		$(CC) $${src} -o $${src%.*}; \
	done
	@./lock3 &
	@sleep 1
	@./lock5
	@$(RM) /tmp/test_lock
dbm1:dbm1.c FORCE
	@echo "尝试dbm数据库的写入与读取"
	@$(CC) -I/usr/include/gdbm  $< -o $@  $(LDFLAGS)
	@./$@
	@$(RM) /tmp/dbm1_test*
dbm2:dbm2.c FORCE
	@echo "尝试dbm数据库的删除与遍历"
	@$(CC) -I/usr/include/gdbm  $< -o $@  $(LDFLAGS)
	@./$@
	@$(RM) /tmp/dbm2_test*
clean:
	$(RM) ./a.out $(object)
