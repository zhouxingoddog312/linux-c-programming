.PHONY:all clean FORCE
LDFLAGS=-lcurses
object=menu1 menu2 menu3 menu4 menu5 password badterm sizeterm kbhit
all:
	for ob in $(object);\
	do \
		if [ $${ob} = "badterm" ] || [ $${ob} = "sizeterm" ];then\
	       		$(CC) $${ob}".c" -o $${ob} $(LDFLAGS);\
		else\
	       		$(CC) $${ob}".c" -o $${ob};\
		fi \
	done
menu1:menu1.c FORCE
	@$(CC) $< -o $@
	@./$@
menu2:menu2.c FORCE
	@$(CC) $< -o $@
	--@./$@ > test
	@$(RM) test
menu3:menu3.c FORCE
	@$(CC) $< -o $@
	./$@ > test
	cat test
	@$(RM) test
password:password.c FORCE
	@$(CC) $< -o $@
	@./$@
menu4:menu4.c FORCE
	@$(CC) $< -o $@
	@./$@
badterm:badterm.c FORCE
	@$(CC) $< -o $@ $(LDFLAGS)
	@./$@
sizeterm:sizeterm.c FORCE
	@$(CC) $< -o $@ $(LDFLAGS)
	@./$@
menu5:menu5.c FORCE
	@$(CC) $< -o $@ $(LDFLAGS)
	@./$@
kbhit:kbhit.c FORCE
	@$(CC) $< -o $@
	@./$@
clean:
	$(RM) $(object)
