#!/usr/bin/env python3.6m
'''Helper script for checking that a submission ZIP file:
- contains all the necessary files
- does not contain unnecessary files
- compiles correctly (with provided files)
- passes basic tests
'''

import glob
import os
import shutil
import subprocess
import sys
import tempfile
import zipfile

### settings: assignement files ###

PROVIDED_PART1_FILES = []
PROVIDED_PART2_FILES = ['MtmParkingLot.cpp', 'ParkingLotPrinter.cpp', 'ParkingLotPrinter.h', 
                        'Time.cpp', 'Time.h', 'ParkingSpot.cpp', 'ParkingSpot.h', 'ParkingLotTypes.h']
PROVIDED_TEST_FILES = ['UniqueArrayTest.cpp']
TESTS_DIR = 'tests'
IO_DIR = 'io_files'
PROVIDED_IO_FILES = os.listdir(IO_DIR)
PROVIDED_MISC_FILES = ['final_check.py']
PROVIDED_FILES = PROVIDED_PART2_FILES + PROVIDED_PART1_FILES + PROVIDED_TEST_FILES + PROVIDED_MISC_FILES + PROVIDED_IO_FILES
PROVIDED_FILES_DIR = os.path.dirname(__file__)

MINIMUM_REQUIRED_TOP_DIR_FILES = ['UniqueArray.h', 'UniqueArrayImp.h', 'ParkingLot.h', 'ParkingLot.cpp']
MINIMUM_REQUIRED_TOP_DIR_FILES_CASE_INSENSITIVE = ['makefile', 'dry.pdf']

### settings: compilation ###

BASIC_GCC_ARGS = ['-std=c++11', '-Wall', '-Werror', '-pedantic-errors']

PART1_NAME = 'UniqueArrayTest'
EXEC_NAME_PART1 = 'UniqueArrayTest'
GCC_ARGS_PART1 = BASIC_GCC_ARGS.copy()
GCC_ARGS_PART1.append('-g')
# list of pairs: (subdirectory, glob pattern)
GCC_SOURCES_PART1 = [(TESTS_DIR, 'UniqueArrayTest.cpp')]
GCC_ARGS_SUFFIX_PART1 = []

PART2_NAME = 'MtmParkingLot'
EXEC_NAME_PART2 = 'MtmParkingLot'
GCC_ARGS_PART2 = BASIC_GCC_ARGS.copy()
GCC_ARGS_PART2.append('-DNDEBUG')
# list of pairs: (subdirectory, glob pattern)
GCC_SOURCES_PART2 = [('', '*.cpp' )]
GCC_ARGS_SUFFIX_PART2 = []



def main():
    if len(sys.argv) != 2:
        print("Usage: %s <zipfile>" % sys.argv[0])
        return

    with tempfile.TemporaryDirectory() as path:
        print("Extracting zip to temporary folder:", path)
        zip_ref = zipfile.ZipFile(sys.argv[1], 'r')
        zip_ref.extractall(path)
        zip_ref.close()
        if not check_folder(path):
            print("Submission has errors, please fix.")
            return
        copy_provided_files(path)
        if not build_and_test(path):
            print("Submission has errors, please fix.")
            return
        print("Congratulations, you passed the provided tests!!!")

def check_folder(path):
    print("Verifying contents...")
    files = os.listdir(path)
    found_errors = check_folder_contents(files,
                                         MINIMUM_REQUIRED_TOP_DIR_FILES,
                                         MINIMUM_REQUIRED_TOP_DIR_FILES_CASE_INSENSITIVE,
                                         PROVIDED_FILES)
    if found_errors:
        print("There are errors in contents of the ZIP file.")
    else:
        print("The ZIP file contains all the necessary files.")
    return not found_errors

def check_folder_contents(contents, required_files, required_files_case_insensitive,
                          forbidden_files, prefix=''):
    found_errors = False
    for filename in required_files:
        pretty_name = os.path.join(prefix, filename)
        if filename in contents:
            print('Found required file/directory:', pretty_name)
        else:
            found_errors = True
            print('ERROR: Missing required file/directory:', pretty_name)

    for filename in required_files_case_insensitive:
        pretty_name = os.path.join(prefix, filename)
        if filename.lower() in map(str.lower, contents):
            print('Found required file/directory:', pretty_name)
        else:
            found_errors = True
            print('ERROR: Missing required file/directory:', pretty_name)

    for filename in forbidden_files:
        if filename in contents:
            found_errors = True
            print('ERROR: Found provided file/directory:', os.path.join(prefix, filename))

    for filename in contents:
        pretty_name = os.path.join(prefix, filename)
        if (filename in required_files or
            filename in forbidden_files or
            filename.lower() in required_files_case_insensitive):
            # already checked above
            continue

        if filename.endswith('.cpp') or filename.endswith('.h'):
            print('Found C++ file:', pretty_name)
            continue

        found_errors = True
        print('ERROR: Found unexpected file/directory:', pretty_name)

    return found_errors

def copy_provided_files(dst_dir):
    src_dir = PROVIDED_FILES_DIR
    src_tests_dir = os.path.join(src_dir, TESTS_DIR)
    src_io_dir = os.path.join(src_dir, IO_DIR)
    dst_tests_dir = os.path.join(dst_dir, TESTS_DIR)
    dst_io_dir = os.path.join(dst_dir, IO_DIR)
    os.makedirs(dst_tests_dir)
    os.makedirs(dst_io_dir)
    for f in PROVIDED_PART1_FILES + PROVIDED_PART2_FILES:
        shutil.copy(os.path.join(src_dir, f), dst_dir)
    for f in PROVIDED_TEST_FILES:
        shutil.copy(os.path.join(PROVIDED_FILES_DIR, TESTS_DIR, f), dst_tests_dir)
    for f in PROVIDED_IO_FILES:
        shutil.copy(os.path.join(PROVIDED_FILES_DIR, IO_DIR, f), dst_io_dir)

def relative_glob(pattern, path, subdir=''):
    return [os.path.join(subdir, os.path.basename(f)) for f in
            glob.glob(os.path.join(path, subdir, pattern))]

def build_and_test(path):
    part1_sources = sum([relative_glob(pattern, path, subdir=subdir)
                         for (subdir, pattern) in GCC_SOURCES_PART1],
                        [])
    part1_compiled = compile_test(path, PART1_NAME, EXEC_NAME_PART1,
                                  GCC_ARGS_PART1 + part1_sources + GCC_ARGS_SUFFIX_PART1)
    part2_sources = sum([relative_glob(pattern, path, subdir=subdir)
                         for (subdir, pattern) in GCC_SOURCES_PART2],
                        [])
    part2_compiled = compile_test(path, PART2_NAME, EXEC_NAME_PART2,
                                  GCC_ARGS_PART2 + part2_sources + GCC_ARGS_SUFFIX_PART2)
    if not (part1_compiled and part2_compiled):
        return False
    if not run_test(path, PART1_NAME, EXEC_NAME_PART1):
        return False
    import re
    infiles = [file for file in PROVIDED_IO_FILES if re.match('in.*\d.txt', file)]
    iopairs = zip(infiles, [file.replace('in','out') for file in infiles])
    for iopair in iopairs:
        if not run_test_with_io(path, iopair, EXEC_NAME_PART2):
            return False
    return True

def compile_test(path, test_name, exec_file, gcc_args):
    command = ['g++'] + gcc_args + ['-o', exec_file]
    print("Compiling %s... (command: %s)" % (test_name, ' '.join(command)))
    if subprocess.call(command, shell=False, cwd=path):
        print("ERROR: couldn't compile %s" % test_name)
        return False
    return True

def run_test(path, test_name, exec_file, inputfile = None, outputfile = None):
    print("Testing %s..." % test_name)
    proc = subprocess.Popen(os.path.join('.', exec_file), shell=False, cwd=path,
                            stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                            universal_newlines=True)
    inputstr = ''
    if inputfile:
        inputstr = open(inputfile,'r').read()
    out, _ = proc.communicate(inputstr)
    if not outputfile:
        print(out)
    if outputfile:
        expectedout = open(outputfile,'r').read()
        if expectedout != out:
            print("ERROR: %s test failed output" % test_name)
            print("Expected output: ")
            print(expectedout)
            print("Actual output: ")
            print(out)
            return False
    if proc.returncode != 0:
        print("ERROR: %s test errored" % test_name)
        return False
    if 'FAIL' in out or 'Failed' in out:
        print("ERROR: %s test failed" % test_name)
        return False
    return True

def run_test_with_io(path, iopair, exec_file):
    if not run_test(path, iopair[0], exec_file, IO_DIR + '/' + iopair[0], IO_DIR + '/' + iopair[1]):
        return False
    return True


if __name__ == '__main__':
    main()
