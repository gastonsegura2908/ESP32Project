## type: ignore
#Import("env")
#import os
#import subprocess
#
#def generate_coverage(source, target, env):
#    print("Generating test coverage report with gcov...")
#    gcov_files = [f for f in os.listdir(".pio/build/native") if f.endswith(".gcno")]
#    for gcno_file in gcov_files:
#        subprocess.call(["gcov", f".pio/build/native/{gcno_file}", "-o", ".pio/build/native"])
#
#env.AddPostAction("test", generate_coverage)
