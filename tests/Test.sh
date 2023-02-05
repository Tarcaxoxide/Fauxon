#!/bin/bash

make clean compile

for File in `ls tests/*.faux |grep -iv -- *.faux`
do
    TESTFILE="$File" make run
done