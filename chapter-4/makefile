.PHONY:all clean
object=args argopt longopt
all:

args:args.c
	@$(CC) $< -o $@
	./$@ -i -lr 'hi there' -f fred.c
argopt:argopt.c
	@$(CC) $< -o $@
	./$@ -i -lr 'hi there' -f fred.c -q
longopt:longopt.c
	@$(CC) $< -o $@
	./$@ --initialize --list 'hi there' --file fred.c -q
	./$@ --init -l --file=fred.c 'hi there'



clean:
	$(RM) $(object)
