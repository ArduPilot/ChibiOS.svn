#!/bin/bash



rlctwrksp() {
  for dir in "$1/workspace"*/
  do
    WPREFS="$dir\.metadata\.plugins\org.eclipse.core.runtime\.settings\org.eclipse.core.resources.prefs"
    echo "Relocating $dir preferences..."
    if test -f "$WPREFS.bak"; 
    then
      echo " - Already relocated... skipping"
    else
      mv $WPREFS $WPREFS".bak"
      RPL=$(echo $1 | sed -e 's|\\|\\\/|g' | sed -e 's|:|\\\\\\:|g')
      cat "$WPREFS.bak" | sed -r 's|C\\\:\/ChibiStudio|'$RPL'|g' > $WPREFS
      echo " - Relocated"
    fi
  done
}
if [ $# -ne 1 ]
then
  echo "Usage: relocator.sh <chibistudio directory path>"
  exit 1
else
## Removing trailing backslash
  CURRPATH=${1%\\}
  DEFAULTPATH="C:\ChibiStudio"
  
  if [ "$CURRPATH" -ef "DEFAULTPATH" ]
  then
    echo "Default location... skipping"
  else
    echo "Relocating to $CURRPATH..."
    
    echo "Relocating Eclipse preferences..."
    EPREFS="$CURRPATH\eclipse\configuration\.settings\org.eclipse.ui.ide.prefs"
    if test -f "$EPREFS.bak"; 
    then
      echo " - Already relocated... skipping"
    else
      mv $EPREFS $EPREFS".bak"
      RPL=$(echo $CURRPATH | sed -e 's|\\|\\\\\\\\|g' | sed -e 's|:|\\\\\\:|g')
      cat "$EPREFS.bak" | sed -r 's|C\\:\\\\ChibiStudio|'$RPL'|g' > $EPREFS
      echo " - Relocated"
    fi     
    rlctwrksp $CURRPATH
    echo "Done"
  fi
fi
exit 0