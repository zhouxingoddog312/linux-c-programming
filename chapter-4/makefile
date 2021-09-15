.PHONY:all clean FORCE
LDFLAGS=-lm
object=args argopt longopt environ showenv envtime gmtime localtime ctime strftime tmpnam user hostget syslog logmask limits
all:
	for ob in $(object);\
	do $(CC) $${ob}".c" -o $${ob} $(LDFLAGS) 2>/dev/null;\
	done
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
ctime:ctime.c FORCE
	@$(CC) $< -o $@
	./$@
strftime:strftime.c FORCE
	@$(CC) $< -o $@
	./$@
tmpnam:tmpnam.c FORCE
	@$(CC) $< -o $@ 2>/dev/null
	./$@
user:user.c FORCE
	@$(CC) $< -o $@
	./$@
hostget:hostget.c FORCE
	@$(CC) $< -o $@
	./$@
syslog:syslog.c FORCE
	@$(CC) $< -o $@
	./$@
	tail -n 1 /var/log/syslog
logmask:logmask.c FORCE
	@$(CC) $< -o $@
	./$@
	tail -n 4 /var/log/syslog
limits:limits.c FORCE
	@$(CC) $< -o $@ $(LDFLAGS)
	--./$@
	@echo
	--nice ./$@
clean:
	$(RM) $(object)
