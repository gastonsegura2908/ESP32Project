# type: ignore
Import("env")

import subprocess
import glob

def run_clang_tidy(source, target, env):
    print("Running clang-tidy...")

    files_to_check = glob.glob("src/*.cpp") + glob.glob("test/*.cpp")

    for file in files_to_check:
        subprocess.call([
            "clang-tidy",
            "-p", ".",
            "-extra-arg=-Iinclude",
            file
        ])

env.AddPreAction("buildprog", run_clang_tidy)
