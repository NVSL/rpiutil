#!/usr/bin/python
import os
import sys, getopt
#from lxml import etree

usage = 'Usage: makelib install|uninstall [-l library][-e filename][-h][--auto] path/libXXX.so'
libpath = ''
includepath = ''
helpmsg = {'install'    : 'makelib install [-l library][-e filename][--auto] path/libXXX.so',
           'uninstall'  : 'makelib uninstall path/libXXX.so'}

def install(opts, sopath):
    assert sopath and sopath.endswith('.so')
    auto = False
    sources = []
    headers = []
    path = '/'.join(sopath.split('/')[:-1])
    if not path:
        path = '.'
    libs = ['Arduino']
    excludes = []
    cmd = 'g++ -D ARDUINO=100 -o %s -shared -fPIC -L%s/lib -I%s -I%s/include' % (sopath, os.environ['GADGETRON_RASPI_PATH'],\
        path, os.environ['GADGETRON_RASPI_PATH'])
    for opt, arg in opts:
        if opt in ('-l', '--libs'):
            libs.append(arg)
        elif opt in ('-e', '--exclude'):
            excludes.append(arg)
        elif opt in('--auto'):
            libs = []
            excludes = []
            auto = True
            break
    sources = [path + '/' + f for f in os.listdir(path) if f not in excludes and (f.endswith('.c') or f.endswith('.cpp'))]
    headers = [path + '/' + f for f in os.listdir(path) if f not in excludes and f.endswith('.h')]
    if auto:
        libs = [lib[3 : -3] for lib in os.listdir(libpath) if lib.startswith('lib') and lib.endswith('.so')]
    assert 'Arduino' in libs
    for lib in libs:
        cmd += ' -l%s' % lib
    for s in sources:
        cmd += ' %s' % s
    print cmd
    os.system(cmd)
    print 'cp %s %s' % (sopath, libpath)
    os.system('cp %s %s' % (sopath, libpath))
    for header in headers:
        print 'cp %s %s' % (header, includepath)
        os.system('cp %s %s' % (header, includepath))

def uninstall(libname):
    assert libname and libname.endswith('.so')
    path = '/'.join(libname.split('/')[:-1])
    if not path:
        path = '.'
    library = libname.split('/')[-1]
    assert library in os.listdir(libpath)
    headers = [includepath + '/' + f for f in os.listdir(path) if f in os.listdir(includepath) and f.endswith('.h')]
    print 'rm %s' % libname
    os.system('rm %s' % libname)
    print 'rm %s/%s' % (libpath, library)
    os.system('rm %s/%s' % (libpath, library))
    for header in headers:
        print 'rm %s' % header
        os.system('rm %s' % header)

if __name__ == "__main__":
    assert 'GADGETRON_RASPI_PATH' in os.environ
    if len(sys.argv) == 1:
        print usage
        sys.exit(1)
    libpath = os.environ['GADGETRON_RASPI_PATH'] + '/lib'
    includepath = os.environ['GADGETRON_RASPI_PATH'] + '/include'
    option = sys.argv[1]
    if option not in helpmsg:
        print 'Unknown option %s' % sys.argv[1]
        print usage
        sys.exit(1)
    try:
        opts, args = getopt.getopt(sys.argv[2:],"h:e:l:",["auto","help","exclude=","libs="])
    except getopt.GetoptError:
        print usage
        sys.exit(1)
    for opt, arg in opts:
        if opt in ('-h', "--help"):
            print helpmsg[option]
            sys.exit()
    if option == 'install':
        if not args:
            print helpmsg[option]
            sys.exit(1)
        install(opts, args[0])
    elif option == 'uninstall':
        for lib in args:
            uninstall(lib)
