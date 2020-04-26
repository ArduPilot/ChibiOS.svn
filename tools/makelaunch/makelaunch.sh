#!/bin/bash


relpath() {
    local pos="${1%%/}" ref="${2%%/}" down=''

    while :; do
        test "$pos" = '/' && break
        case "$ref" in $pos/*) break;; esac
        down="../$down"
        pos=${pos%/*}
    done

    echo "$down${ref##$pos/}"
}

if [ $# -ne 3 ]
then
  echo "Usage: makelaunch.sh <project directory path> <elf file path> <\"Eclipse Project Name\">"
  exit 1
else
  P1="${1//\\//}"
  P2="${2//\\//}"
  DEBUGDIR=debug
#  ELFRELPATH=$(realpath --relative-to=$P1 $P2)
  ELFRELPATH=$(relpath $P1 $P2)
  echo "Creating debug launch configurations for \"$ELFRELPATH\" ..."
  ELFNAME=$(echo "$ELFRELPATH" | sed -r "s|/|-|g")
  LAUNCHNAME1="$3 ($ELFNAME)(OpenOCD, Flash and Run)"
  LAUNCHNAME2="$3 ($ELFNAME)(OpenOCD, Just Run)"
  mkdir -p $1/$DEBUGDIR
  cat ./arm_flash-and-run.launch.template | sed -r "s|EEEEEEEE|$P2|g" | sed -r "s|PPPPPPPP|$3|g" > "$P1/$DEBUGDIR/$LAUNCHNAME1.launch"
  cat ./arm_just-run.launch.template | sed -r "s|EEEEEEEE|$P2|g" | sed -r "s|PPPPPPPP|$3|g" > "$P1/$DEBUGDIR/$LAUNCHNAME2.launch"
  echo
  echo "Done"
fi
exit 0

