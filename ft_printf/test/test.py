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
libdir = "/Users/kely/libs"
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
	cmd = f"make all EXEC={jobname} VVARS=\"{vvars}\" VFORMAT=\"{vformat}\" ; exit $?"
	try:
		print(f"$ {cmd}\n");
		res = subprocess.check_output(cmd, shell=True, executable="/bin/zsh")
		print(f"{CYAN}{res.decode("utf-8")}");
		
		jobidx += 1
		return jobname

	except subprocess.CalledProcessError as cperr:
		if "[-Wformat]".encode("utf-8") in cperr.output:
			print(f"{RESET}{YELLOW}format error, passing{RESET}")
			return
		print(f"{RESET}{RED}make error {cperr.returncode}{RESET}");
		exit(1)

def runjob(jobpath):
	res = subprocess.check_output(cmd);
	print(f"{CYAN}{res.decode("utf-8")}{RESET}")

tests = {
	"c": {
		"f": ["", "-", "0"],
		"w": ["", "4", "0", "-3", "*"],
		"p": ["", ".4", ".0", ".*"],
		"v": ["a"]
	},
	"s": {
		"f": ["", "-", "0"],
		"w": ["", "4", "0", "-3", "*"],
		"p": ["", ".4", ".0", ".*"],
		"v": ["(char *)0", "\\\"alessia\\\""]
	},
	"p": {
		"f": ["", "-", "0"],
		"w": ["", "4", "0", "-3", "*"],
		"p": ["", ".4", ".0", ".*"],
		"v": ["(void *)0", "(void *)0xe04f053f450"]
	},
	"d": {
		"f": ["", "-", "0"],
		"w": ["", "4", "0", "-3", "*"],
		"p": ["", ".4", ".0", ".*"],
		"v": ["INT_MIN", "0", "INT_MAX"]
	},
	"u": {
		"f": ["", "-", "0"],
		"w": ["", "4", "0", "-3", "*"],
		"p": ["", ".4", ".0", ".*"],
		"v": ["0", "UINT_MAX"]
	},
	"x": {
		"f": ["", "-", "0"],
		"w": ["", "4", "0", "-3", "*"],
		"p": ["", ".4", ".0", ".*"],
		"v": ["0", "UINT_MAX"],
	},
	"%": {
		"f": ["", "-", "0"],
		"w": ["", "10", "0", ],
		"p": ["", ".4", ".0", ".*"],
		"v": []
	}
}

buildfmts = []
buildvars = []

i = 0;

tmp_fmt = []
tmp_vars = []
tmp_idx = 0
specs_per = 2
for spec, t in tests.items():
	for p in itertools.product(*t.values()):
		tmp_fmt.append(''.join(p[:3]))
		if "*" in p[1]:
			tmp_vars.append([1 + tests["varvals"]["width"][0]])
			tests["varvals"]["width"][0] ^= 1
		if "*" in p[2]:
			tmp_vars.append(tests["varvals"]["precision"][1 + tests["varvals"]["precision"][0]])
			tests["varvals"]["precision"][0] ^= 1
		if tests["vals"][p[3]]:
			tmp_vars.append(tests["vals"][p[3]])
		tmp_idx += 1
		if tmp_idx % specs_per == 0:
			runwithvars('\\n'.join(['%' + c for c in tmp_fmt]), ', '.join(tmp_vars))
			tmp_idx = 0
			tmp_fmt.clear()
			tmp_vars.clear()
