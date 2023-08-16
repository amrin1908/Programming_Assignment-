import os
import re

def get_running_pids():
    output = os.popen('top -n 1').read()
    lines = output.split("\n") #line by line extraction
    pids = []

    for line in lines[7:]: # To skip header and other unrelated process info
        match = re.match(r"\s*(\d+)", line) # matching with a regular expression
        if match:
            pid = match.group(1) #extracts the first group which is the process id
            pids.append(pid)

    return pids

print("RUNNING PIDS:" ,running_pids=get_running_pids())
