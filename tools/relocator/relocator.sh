#!/bin/bash
if [ $# -ne 1 ]
then
  echo "Usage: relocator.sh <chibistudio directory path>"
  exit 1
else
  if [ "$1" -ef "C:/ChibiStudio" ]
  then
    echo "Default location... skipping"
  else
    PRFS=$1/eclipse/configuration/.settings/org.eclipse.ui.ide.prefs
    if test -f "$PRFS.bak"; 
    then
      echo "Already relocated... skipping"
    else
      echo "Relocating to $1..."
      
      echo "Relocating Eclipse Workspace preferences..."
      mv $PRFS $PRFS".bak"
      RPL=$(echo $1 | sed -e 's|\\|\\\\\\\\|g' | sed -e 's|:|\\\\\\:|g')
      cat "$PRFS.bak" | sed -r 's|C\\:\\\\ChibiStudio\\\\|'$RPL'|g' > $PRFS
      echo "Done"
    fi
  fi
fi

exit 0