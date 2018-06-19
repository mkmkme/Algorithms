#!/usr/bin/env python3

import argparse
import os
import sys

from collections import OrderedDict
from distutils.spawn import find_executable


def die(msg):
    sys.stderr.write(msg + '\n')
    sys.exit(1)


try:
    import ninja
    import pkgconfig
except ModuleNotFoundError as err:
    die(f'python import error: {err}')


def check_pkgconfig(progs):
    for prog in progs:
        sys.stdout.write(f'checking for "{prog}" (via pkg-config)... ')
        if pkgconfig.exists(prog):
            sys.stdout.write('found\n')
        else:
            sys.stdout.write('not found\n')
            die(f'please install "{prog}" dependency first')


def get_targets(suffix):
    for el in os.listdir():
        fname, ext = os.path.splitext(el)
        if ext == suffix:
            yield fname, el


if __name__ == '__main__':
    check_pkgconfig(['dbus-1'])
    p = argparse.ArgumentParser()
    p.add_argument('--clang', action='store_true', default=False)
    clang = p.parse_args().clang

    ninja_vars = OrderedDict(
        cxx=find_executable('clang++' if clang else 'c++'),
        cxxflags='-std=c++1z -Wall -Wextra -g -D_GNU_SOURCE',
        dbus_cflags=pkgconfig.cflags('dbus-1'),
        dbus_libs=pkgconfig.libs('dbus-1'),
        ninja=find_executable('ninja'))

    with open('build.ninja', 'w') as bf, open('.gitignore', 'w') as gign:
        bf.write('# Created by configure.py\n# DO NOT EDIT\n\n')
        n = ninja.ninja_syntax.Writer(bf)

        for key, val in ninja_vars.items():
            n.variable(key, val)
        n.newline()

        n.rule('link', '$cxx $cxxflags -o $out $in', 'CXXLD $out')
        n.rule('link-dbus',
               '$cxx $cxxflags $dbus_cflags -o $out $in $dbus_libs',
               'CXXLD $out')
        n.newline()

        gign.write('.ninja*\n')

        for elf, src in sorted(get_targets('.cpp')):
            print(f'generating target for "{elf}"...')
            n.build(elf, 'link%s' % ('-dbus' * elf.startswith('dbus')), src)
            gign.write(f'{elf}\n')

    print('done')
