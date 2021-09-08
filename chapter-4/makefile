.PHONY:all clean FORCE
object=args argopt longopt environ showenv envtime gmtime localtime
all:

args:args.c FORCE
	@$(CC) $< -o $@
	./$@ -i -lr 'hi there' -f fred.c
argopt:argopt.c FORCE
	@$(CC) $< -o $@
	./$@ -i -lr 'hi there' -f fred.c -q
longopt:longopt.c FORCE
	@$(CC) $< -o $@
	./$@ --initialize --list 'hi there' --file fred.c -q
	./$@ --init -l --file=fred.c 'hi there'
environ:environ.c FORCE
	@$(CC) $< -o $@
	./$@ HOME
	./$@ FRED
	./$@ FRED hello
	./$@ FRED
showenv:showenv.c FORCE
	@$(CC) $< -o $@
	./$@
envtime:envtime.c FORCE
	@$(CC) $< -o $@
	./$@
gmtime:gmtime.c FORCE
	@$(CC) $< -o $@
	./$@
	date
localtime:localtime.c FORCE
	@$(CC) $< -o $@
	./$@
	date
clean:
	$(RM) $(object)
