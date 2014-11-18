#!/usr/bin/python
import os
import sys, getopt

libpath = ''
includepath = ''

def main(argv):
    helpmsg='makeino [--auto] [-o outputfile] [-l libraries] inputfile'
    fnamemsg='Filename too short or not .cpp or .ino file given'
    nofilemsg='No file given!'
    try:
        opts, args = getopt.getopt(argv,"h:o:l:",["auto","help","ofile=","libs="])
    except getopt.GetoptError:
        print helpmsg
        sys.exit(2)
    auto = False
    sources = [" %s" % os.environ['GADGETRON_RASPI_PATH'] + '/arduino/core/main.cpp']
    sources += args
    path = '/'.join(args[0].split('/')[:-1])
    if not path:
        path = '.'
    outputfile = '.'.join(args[0].split('.')[:-1]) + '.out'
    libs = ['Arduino']
    cmd = 'g++ -D ARDUINO=100 -L%s -I%s -I%s' % (libpath, path, includepath)
    for opt, arg in opts:
        if opt in ('-h', "--help"):
            print helpmsg
            sys.exit()
        elif opt in ("-o", "--ofile"):
            outputfile = arg
        elif opt in ("-l", "--libs"):
            libs.append(arg)
        elif opt in ("--auto"):
            libs = []
            auto = True

    if auto:
        libs = [lib[3 : -3] for lib in os.listdir(libpath) if lib.startswith('lib') and lib.endswith('.so')]

    assert 'Arduino' in libs
    if not sources:
        print nofilemsg
        sys.exit(1)
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
            print 'ln -sf %s %s' % (fname.split('/')[-1], cpp)
            os.system('ln -sf %s %s' % (fname.split('/')[-1], cpp))
            cmd += " %s" % cpp
        else:
            cmd += " %s" % fname
    print cmd
    os.system(cmd)

if __name__ == "__main__":
    assert 'GADGETRON_RASPI_PATH' in os.environ
    libpath = os.environ['GADGETRON_RASPI_PATH'] + '/lib'
    includepath = os.environ['GADGETRON_RASPI_PATH'] + '/include'
    main(sys.argv[1:])
