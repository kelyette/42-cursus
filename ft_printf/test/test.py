import itertools
import subprocess
from pathlib import Path
from tqdm import tqdm

# Reset
RESET = '\033[0m'
BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
WHITE = '\033[0;37m'

specifiers = "cspdux%"
projectdir = ".."
libdir = Path.home() / "libs"
jobidx = 0
result = []

debug = False

basherrorcount = 0


def runwithvars(vformat: str, vvars: str):
	global jobidx
	jobname = f"target/test{jobidx:03}"
	vvarsarg = f"VVARS=\"{vvars}\"" if vvars else ""
	cmd = f"make all EXEC={jobname} {vvarsarg} VFORMAT=\"{vformat}\" ; exit $?"
	try:
		if debug:
			print(f"$ {cmd}\n")
		res = subprocess.check_output(cmd, shell=True, executable="/bin/zsh")
		if (debug):
			print(f"{CYAN}{res.decode('utf-8')}")
		
		jobidx += 1
		return jobname

	except subprocess.CalledProcessError as cperr:
		if "[-Wformat]".encode("utf-8") in cperr.output:
			print(f"{RESET}{YELLOW}format error, passing{RESET}")
			return
		print(f"{RESET}{RED}make error {cperr.returncode}{RESET}\nformat: \"{vformat}\"\nvars: \"{vvars}\"");
		exit(1)


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
outeridx = -1
inneridx = -1
outerrefreshrate = 4


def gtotal(*args):
	tot = 1
	for arg in args:
		tot *= len(arg)
	return tot


for spec, t in (pbar := tqdm(tests.items(), position=1)):
	outeridx += 1
	inneridx = 0
	isvaldebug = False
	for p in (pbar2 := tqdm(itertools.product(*t.values()), total=(total := gtotal(*t.values())), leave=False, position=0)):
		inneridx += 1
		if inneridx % outerrefreshrate == 0:
			pbar.n = round(outeridx + (inneridx + 1) / total, 1)
			pbar.refresh()
		flag, width, precision, val = p
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
