#!/usr/bin/python
import os
import sys, getopt


def main(argv):
    helpmsg='makeino.py -o <outputfile> -l <libraries> <inputfile>'
    fnamemsg='Filename too short or not .cpp or .ino file given'
    sources = []
    outputfile = ''
    libs = []
    cmd = 'g++ -L%s/lib -I. -I%s/include -lArduino' % (os.environ['GADGETRON_RASPI_PATH'],\
        os.environ['GADGETRON_RASPI_PATH'])
    try:
        opts, args = getopt.getopt(argv,"h:o:l:",["help","ofile=","libs="])
    except getopt.GetoptError:
        print helpmsg
        sys.exit(2)
    for opt, arg in opts:
        if opt in ('-h', "--help"):
            print helpmsg
            sys.exit()
        elif opt in ("-o", "--ofile"):
            outputfile = arg
        elif opt in ("-l", "--libs"):
            libs.append(arg)
    sources = args
    for fname in sources:
        if len(fname) <= 4 or fname[-4:] not in ['.ino', '.cpp']:
            print fnamemsg
            sys.exit(1)
    if outputfile:
        cmd += " -o %s" % outputfile
    for lib in libs:
        cmd += " -l%s" % lib
    for fname in sources:
        if fname.endswith('.ino'):
            cpp = fname[:-4] + '.cpp'
            os.system('ln -s %s %s' % (fname, cpp))
            cmd += " %s" % cpp
        else:
            cmd += " %s" % fname
    cmd += " %s" % os.environ['GADGETRON_RASPI_PATH'] + '/arduino/core/main.cpp'
    os.system(cmd)

if __name__ == "__main__":
    main(sys.argv[1:])
