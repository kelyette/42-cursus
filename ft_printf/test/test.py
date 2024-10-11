import os
import itertools
import subprocess

# Reset
RESET='\033[0m'		  # Text Reset

# Regular Colors
BLACK='\033[0;30m'		  # Black
RED='\033[0;31m'		  # Red
GREEN='\033[0;32m'		  # Green
YELLOW='\033[0;33m'		  # Yellow
BLUE='\033[0;34m'		  # Blue
PURPLE='\033[0;35m'		  # Purple
CYAN='\033[0;36m'		  # Cyan
WHITE='\033[0;37m'		  # White

specifiers = "cspdux%"
projectdir = ".."
libdir = "/home/kcsajka/libs"
jobidx = 0;
jobname = "test{:03}"
buildlibcmd = f"cd {projectdir} && make"
buildtestcmd = "ccw -o test.o {}.c -D'{}'"
linkcmd = f"ccw -L{libdir}/ -I{libdir}/ -lft -I{projectdir}/include {projectdir}/printf.a test.o -o {{}}"
runcmd = "leaks -atExit -- {}"

result = []

basherrorcount = 0

def runbash(cmd):
	print(cmd)
	res = subprocess.check_output(cmd, shell=True, executable="/bin/bash")
	print(res)

def runwithvars(vformat: str, vvars: str):
	global jobidx
	jobname = f"target/test{jobidx:03}";
	vvarsarg = f"VVARS=\"{vvars}\"" if vvars else ""
	cmd = f"make all EXEC={jobname} {vvarsarg} VFORMAT=\"{vformat}\" ; exit $?"
	try:
		print(f"$ {cmd}\n");
		res = subprocess.check_output(cmd, shell=True, executable="/bin/zsh")
		print(f"{CYAN}{res.decode('utf-8')}");
		
		jobidx += 1
		return jobname

	except subprocess.CalledProcessError as cperr:
		if "[-Wformat]".encode("utf-8") in cperr.output:
			print(f"{RESET}{YELLOW}format error, passing{RESET}")
			return
		print(f"{RESET}{RED}make error {cperr.returncode}{RESET}\nformat: \"{vformat}\"\nvars: \"{vvars}\"");
		exit(1)

def runjob(jobpath):
	res = subprocess.check_output(cmd);
	print(f"{CYAN}{res.decode('utf-8')}{RESET}")

tests = {
	"c": {
		"f": ["", "-"],
		"w": ["", "4", ["*", "-10"], ["*", "0"], ["*", "0"]],
		"p": [""],
		"v": ["'\\'k\\''", "(char)0"]
	},
	"s": {
		"f": ["", "-"],
		"w": ["", "4", "3", ["*", "-10"], ["*", "0"]],
		"p": ["", ".4", ".0", [".*", "10"]],
		"v": ["(char *)0", "\\\"alessia\\\""]
	},
	"p": {
		"f": ["", "-"],
		"w": ["", "4", "-3", ["*", "-10"], ["*", "0"]],
		"p": [""],
		"v": ["(void *)0", "(void *)0xe04f053f450"]
	},
	"d": {
		"f": ["", "-", "0"],
		"w": ["", "4", ["*", "-10"], ["*", "0"]],
		"p": ["", ".4", ".0", [".*", "10"]],
		"v": ["INT_MIN", "0", "INT_MAX"]
	},
	"u": {
		"f": ["", "-", "0"],
		"w": ["", "4", ["*", "-10"], ["*", "0"]],
		"p": ["", ".4", ".0", [".*", "10"]],
		"v": ["0", "UINT_MAX"]
	},
	"x": {
		"f": ["", "-", "0"],
		"w": ["", "4", ["*", "-10"], ["*", "0"]],
		"p": ["", ".4", ".0", [".*", "10"]],
		"v": ["0", "UINT_MAX"],
	},
	"%": {
		"f": ["", "-", "0"],
		"w": ["", "10", ["*", "-10"], ["*", "0"]],
		"p": ["", ".4", ".0", [".*", "10"]],
		"v": [""]
	}
}

buildfmts = []
buildvars = []

i = 0;

tmp_fmt = []
tmp_vars = []
tmp_idx = 0
specs_per = 2
isvaldebug = False
for spec, t in tests.items():
	isvaldebug = False
	for p in itertools.product(*t.values()):
		flag, width, precision, val = p;
		if isinstance(width, list):
			isvaldebug = True
			tmp_vars.append(width[1])
			width = width[0]
		if isinstance(precision, list):
			isvaldebug = True
			tmp_vars.append(precision[1])
			precision = precision[0]

		if (val):
			tmp_vars.append(val)
		tmp_fmt.append("/{}/".format(''.join(["%", flag, width, precision, spec])))
		tmp_idx += 1
		if tmp_idx % specs_per == 0:
			runwithvars('\\n'.join(tmp_fmt), ', '.join(tmp_vars))
			tmp_idx = 0
			tmp_fmt.clear()
			tmp_vars.clear()
