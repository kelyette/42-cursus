import itertools
import subprocess
from pathlib import Path
from tqdm import tqdm
import re
import argparse
from random import random

parser = argparse.ArgumentParser(
	prog="ft_printf tester",
	description="test and compare ft_printf with printf"
)
parser.add_argument(
	'-d', '--debug',
	help="print shell commands outputs",
	action="store_true",
	default=False
)
parser.add_argument(
	'-t', '--tests',
	help="specifiers to run tests for",
	type=str,
	default="*"
)
parser.add_argument(
	'-c', '--count-per',
	help="set number of test specifiers per executable",
	type=int,
	default=16
)
parser.add_argument(
	'--ulimit',
	help="compile ftprintf with ULIMIT macro",
	type=int
)
parser.add_argument(
	'--throwerr',
	help="compile ftprintf with THROWERR enabled",
	action="store_true",
	default=True
)
args = parser.parse_args()
debug = args.debug
test_specs = args.tests
specs_per = args.count_per
ulimit = args.ulimit
throwerr = args.throwerr

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

projectdir = ".."
libdir = Path.home() / "libs"
jobidx = 0
result = []
makeargs = ""

if ulimit:
	makeargs += f" ULIMIT={ulimit}"
if throwerr:
	makeargs += " THROWERR=1"


def shtore(s):
	return re.sub(r"'\\'(.)\\''", r"'\1'", s)


def runwithvars(vformat: str, vvars: str, pbar=None):
	global jobidx
	print_f = print
	if isinstance(pbar, tqdm):
		print_f = pbar.write
	jobname = f"target/test{jobidx:03}"
	vvarsarg = f"VVARS=\"{vvars}\"" if vvars else ""
	cmd = f"timeout 5 make checkoutput EXEC={jobname} {makeargs} {vvarsarg} VFORMAT=\"{vformat}\" ; exit $?"
	try:
		if (debug):
			print_f(f"{CYAN}$> {cmd}{RESET}")
		res = subprocess.run(
			cmd, shell=True, executable="/bin/zsh",
			capture_output=True, text=True, check=True
		)
		if (debug):
			print_f(f"{CYAN}{res.stdout}{RESET}")
		jobidx += 1
		return jobname

	except subprocess.CalledProcessError as cperr:
		print_f(f"{RED}make error {cperr.returncode}");
		print_f(f"output:\n{RESET}{YELLOW}$> {cmd}\n{cperr.output}{RESET}{RED}{cperr.stderr}{RESET}")
		exit(1)

alltests = {
	"c": {
		"f": ["", "-"],
		"w": ["", "4", ["*", "-10"], ["*", "0"], ["*", "3"]],
		"p": [""],
		"v": [r"'\'k\''", "(char)0"]
	},
	"s": {
		"f": ["", "-"],
		"w": ["", "4", "3", ["*", "-10"], ["*", "0"]],
		"p": ["", ".4", ".0", [".*", "10"]],
		"v": ["(char *)0", r'\"alessia\"']
	},
	"p": {
		"f": ["", "-"],
		"w": ["", "4", "-3", ["*", "-10"], ["*", "0"]],
		"p": [""],
		"v": ["(void *)0", "(void *)0xe5053f", "(void *)-42"]
	},
	"d": {
		"f": ["", "-", "0", " ", "+"],
		"w": ["", "4", ["*", "-10"], ["*", "0"]],
		"p": ["", ".4", ".0", [".*", "10"]],
		"v": ["INT_MIN", "0", "INT_MAX", "-42"]
	},
	"u": {
		"f": ["", "-", "0"],
		"w": ["", "4", ["*", "-10"], ["*", "0"]],
		"p": ["", ".4", ".0", [".*", "10"]],
		"v": ["0", "UINT_MAX", "-42"]
	},
	"x": {
		"f": ["", "-", "0", "#"],
		"w": ["", "4", ["*", "-10"], ["*", "0"]],
		"p": ["", ".4", ".0", [".*", "10"]],
		"v": ["0", "UINT_MAX", "-42"],
	},
	"%": {
		"f": ["", "-", "0"],
		"w": ["", "10", ["*", "-10"], ["*", "0"]],
		"p": ["", ".4", ".0", [".*", "10"]],
		"v": [""]
	}
}

alltests = {
	"c": {
		"f": [""],
		"w": [""],
		"p": [""],
		"v": [r"'\'k\''", r"'\'0\''", '(char)0']
	},
	"s": {
		"f": [""],
		"w": [""],
		"p": [""],
		"v": [r'\"alessia\"', r'\"\"', "(char *)0"]
	},
	"p": {
		"f": [""],
		"w": [""],
		"p": [""],
		"v": ["(void *)0x0", "(void *)-231", "(void *)0xfe", "(void *)UINTPTR_MAX"]
	},
	"d": {
		"f": [""],
		"w": [""],
		"p": [""],
		"v": ["0", "10", "INT_MAX", "INT_MIN", "-42"]
	},
	"u": {
		"f": [""],
		"w": [""],
		"p": [""],
		"v": ["0", "414", "UINT_MAX", "-42", "0xffff"]
	},
	"x": {
		"f": [""],
		"w": [""],
		"p": [""],
		"v": ["0x034f", "UINT_MAX", "0"]
	},
	"%": {
		"f": [""],
		"w": [""],
		"p": [""],
		"v": [""]
	},
}

aliases = {"i": "d", "X": "x"}

if test_specs == "*":
	tests = alltests
else:
	tests = dict()
	for ct in test_specs:
		ct = aliases.get(ct, ct)
		if ct not in alltests.keys():
			print(f"{YELLOW}warning: --tests: no tests for '{ct}'{RESET}")
			continue
		if ct in tests.keys():
			print(f"{YELLOW}warning: --tests: duplicate test '{ct}', skipping{RESET}")
			continue
		tests[ct] = alltests[ct]

print(f"{CYAN}testing: {''.join(tests.keys())}{RESET}")

buildfmts = []
buildvars = []

i = 0

tmp_fmt = []
tmp_vars = []
tmp_idx = 0
isvaldebug = False
outeridx = 0
inneridx = 0
outerrefreshrate = 8


def gtotal(*args):
	tot = 1
	for arg in args:
		tot *= len(arg)
	return tot


varfile_data = ""
pbar = tqdm(total=len(tests.values()), position=1, smoothing=0)
for spec, t in tests.items():
	inneridx = 0
	for p in (pbar2 := tqdm(itertools.product(*t.values()), total=(total := gtotal(*t.values())), leave=False, position=0)):
		flag, width, precision, val = p
		inneridx += 1

		if (spec == 'x' and random() > 0.5):
			spec == 'X'
		# values
		lvars = []
		if isinstance(width, list):
			lvars.append(width[1])
			width = width[0]
		if isinstance(precision, list):
			lvars.append(precision[1])
			precision = precision[0]
		if (val):
			lvars.append(val)
		tmp_vars.extend(lvars)

		# format
		fmt = ''.join([flag, width, precision, spec])
		tmp_fmt.append(f"| {fmt.replace('%', '^'):<10} | /%{fmt}/")
		readable_vars = [v.replace(r'\"', '"') if spec != 'c' else shtore(v) for v in lvars]
		varfile_data += f"{tmp_idx:03} | {fmt:<6} | {', '.join(readable_vars)}\n"

		tmp_idx += 1
		if tmp_idx % specs_per == 0:
			with open(".varfile", "w") as varfile:
				varfile.write(varfile_data)
			varfile_data = ""
			runwithvars('\\n'.join(tmp_fmt), ', '.join(tmp_vars), pbar2)
			tmp_idx = 0
			tmp_fmt.clear()
			tmp_vars.clear()

		# tqdm outer bar progress
		if inneridx % outerrefreshrate == 0:
			pbar.n = round(outeridx + (inneridx + 1) / total, 1)
			pbar.refresh()
	outeridx += 1
