.PHONY:all clean FORCE
object=menu1 menu2 menu3 password
all:
	for ob in $(object);\
	do $(CC) $${ob}".c" -o $${ob};\
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
clean:
	$(RM) $(object)
