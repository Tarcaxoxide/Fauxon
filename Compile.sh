#!/bin/bash

objs=""
for SourceDirectory in $(find Sources/ -type d)
do
    irectory="$(echo $SourceDirectory|cut -d'/' -f2)"
    BuildDirectory="Build/$irectory"
    mkdir -p $BuildDirectory

    for DFilePath in $(find $SourceDirectory -type f)
    do
        FilePath="$(echo $DFilePath|cut -d'/' -f2)"
        Flags="$(head -1 "$DFilePath" |cut -d'/' -f3)"
        clang++ -IHeaders -ferror-limit=0 $Flags -c "$DFilePath" -o "$BuildDirectory/$FilePath.o" || exit 1
        objs="$BuildDirectory/$FilePath.o $objs"
    done
done

clang++ -IHeaders -o exe $objs
