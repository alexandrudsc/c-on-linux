###############################################################################
# !/bin/python
# Reader from a named pipe to which the writer.cpp writes
###############################################################################
import os, sys, stat

path= "/tmp/fifopipe"

#if pipe does not exist, create it
if not os.path.isfile(path) or stat.S_ISFIFO(os.stat(path).st_mode) == 0:
    try:
        os.mkfifo(path, 0777)
    except:
        # writer has already created pipe
        pass
# open pipe is blocking, until writer opens it
pipe=os.open(path, os.O_RDONLY)

# open as file object for easy reading
fifo = os.fdopen(pipe)
print ("Start reading ...")
cnt = 0;
###############################################################################
while True:
    str=fifo.readline()
    if len(str) == 0:
        print ("Writer closed pipe")
        break
    cnt += 1
    revstr=str[::-1]
    print ("The {}th reversed String is: {}".format(cnt, revstr))

