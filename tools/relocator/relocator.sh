##!/bin/bash

# Script identifier and version.
_ID="Relocator for Windows"
_VER=1.0.0

# Default path: this is used for replace purposes. Do not touch it.
_DEFAULTPATH="C:\ChibiStudio"

# Script path. Do not touch it.
_SCRIPTPATH="${BASH_SOURCE[0]}"

rlcecl() {
  EPREFS="$2\eclipse\configuration\.settings\org.eclipse.ui.ide.prefs"
  
  if test -f "$EPREFS"
  then
    if [ $1 == "-r" ]
    then
      if test -f "$EPREFS.bak"
      then
        rm $EPREFS
        mv $EPREFS".bak" $EPREFS
        echo " - Restoring Eclipse preferences                  Done"
      else
        echo " - Restoring Eclipse preferences                  Skipped"
      fi
    elif [ $1 == "-s" ]
    then
      if test -f "$EPREFS.bak"; 
      then
        echo " - Updating Eclipse preferences                   Skipped"
      else
        mv $EPREFS $EPREFS".bak"
        RPL=$(echo $2 | sed -e 's|\\|\\\\\\\\|g' | sed -e 's|:|\\\\\\:|g')
        SRCH=$(echo $3 | sed -e 's|\\|\\\\\\\\|g' | sed -e 's|:|\\\\\\:|g')
        cat "$EPREFS.bak" | sed -r 's|'$SRCH'|'$RPL'|g' > $EPREFS
        echo " - Updating Eclipse preferences                   Done"
      fi 
    elif [ $1 == "-f" ]
    then
      if test -f "$EPREFS.bak"
      then
        rm $EPREFS
        cp $EPREFS".bak" $EPREFS
      else
        mv $EPREFS $EPREFS".bak"
      fi
      RPL=$(echo $2 | sed -e 's|\\|\\\\\\\\|g' | sed -e 's|:|\\\\\\:|g')
      SRCH=$(echo $3 | sed -e 's|\\|\\\\\\\\|g' | sed -e 's|:|\\\\\\:|g')
      cat "$EPREFS.bak" | sed -r 's|'$SRCH'|'$RPL'|g' > $EPREFS
      echo " - Updating Eclipse preferences                   Done"

    fi
  else
    echo "Error: Cannot find Eclipse preferences            Aborting"
    exit 1
  fi    
}

rlcwrksppref() {
  _OPT=$1
  _WP=$2
  _DEST=$3
  _DEF=$4

  WPREFS=$_WP"\.metadata\.plugins\org.eclipse.core.runtime\.settings\org.eclipse.core.resources.prefs"
  if test -f "$WPREFS"
  then
    if [ $_OPT == "-r" ]
    then
      if test -f "$WPREFS.bak"
      then
        rm $WPREFS
        mv $WPREFS".bak" $WPREFS
        echo "   - Restoring Workspace preferences              Done"
      else
        echo "   - Restoring Workspace preferences              Skipped"
      fi
    elif [ $_OPT == "-s" ]
    then
      if test -f "$WPREFS.bak"; 
      then
        echo "   - Updating Workspace preferences               Skipped"
      else
        mv $WPREFS $WPREFS".bak"
        RPL=$(echo $_DEST | sed -e 's|\\|\\\/|g' | sed -e 's|:|\\\\\\:|g')
        SRCH=$(echo $_DEF | sed -e 's|\\|\\/|g' | sed -e 's|:|\\\\\\:|g')
        cat "$WPREFS.bak" | sed -r 's|'$SRCH'|'$RPL'|g' > $WPREFS
        echo "   - Updating Workspace preferences               Done"
      fi 
    elif [ $_OPT == "-f" ]
    then
      if test -f "$WPREFS.bak"
      then
        rm $WPREFS
        cp $WPREFS".bak" $WPREFS
      else
        mv $WPREFS $WPREFS".bak"
      fi
      RPL=$(echo $_DEST | sed -e 's|\\|\\\/|g' | sed -e 's|:|\\\\\\:|g')
      SRCH=$(echo $_DEF | sed -e 's|\\|\\/|g' | sed -e 's|:|\\\\\\:|g')
      cat "$WPREFS.bak" | sed -r 's|'$SRCH'|'$RPL'|g' > $WPREFS
      echo "   - Updating Workspace preferences               Done"
    fi
  else
    echo "   WARNING: $WPREFS not found."
  fi 
}

rlcwrksp() {
  # Iterating all the workspace in the folder
  for WRKSPPATH in "$2/workspace"*/
  do
    # Normalizing paths: replacing slash with backslash and removing trailing
    #  backslash
    WRKSPPATH=$(echo $WRKSPPATH | sed -e 's|\/|\\|g' | sed -e 's|\\\\|\\|g')
    WRKSPPATH=${WRKSPPATH%\\}
    
    # Computing the workspace name
    SRCH=$(echo "$2\\" | sed -e 's|\\|\\\\|g')
    WRKSPNAME=$(echo $WRKSPPATH | sed -e 's|'$SRCH'||g')
    
    if [ $1 == "-r" ]
    then
      echo " - Restoring $WRKSPNAME..."
      rlcwrksppref $1 $WRKSPPATH $2 
    elif [ $1 == "-s" ]
    then
      echo " - Updating $WRKSPNAME..."
      rlcwrksppref $1 $WRKSPPATH $2 $3 
    elif [ $1 == "-f" ]
    then
      echo " - Updating $WRKSPNAME..."
      rlcwrksppref $1 $WRKSPPATH $2 $3 
    fi    
  done
}

rlcman() {
  echo "NAME"
  echo "      relocator.sh"
  echo "SYNOPSIS"
  echo "      relocator.sh [OPTIONS] [DIRECTORY]" 
  echo "      relocator.sh [-man]" 
  echo "      relocator.sh [-r DIRECTORY | -s DIRECTORY | -f DIRECTORY]"
  echo "DESCRIPTION"
  echo "      relocator.sh modifies some eclipse file in order to relocate the directory"
  echo "      of ChibiStudio for Windows. It also allows to revert the changes."
  echo " "
  echo "      Extract the ChibiStudio toolchain in a arbitrary folder. Then call"
  echo "      bash relocator.sh -s [THE ARBITRARY DIRECTORY]"
  echo "      e.g. bash relocator.sh -s D:\ChibiStudio"
  echo ""
  echo "      Note: you may need to update the project location from Eclipse."
  echo "      Select all the project and choose Update Project Location(s)."
  echo "OPTIONS"
  echo "      -man"
  echo "            Shows this manual."
  echo "      -r DIRECTORY"
  echo "            Revert all the changes restoring all the files. Requires the current"
  echo "            installation directory."
  echo "      -s DIRECTORY"
  echo "            Changes the files to the new directory. Files are skipped if they have"
  echo "            been already modified once."
  echo "      -f DIRECTORY"
  echo "            Changes the files to the new directory forcefully. All the files are" 
  echo "            reverted and reprocessed."
  echo " " 
}
echo "==============================="
echo "$_ID v$_VER"
echo "==============================="
echo ""
if [ $# -eq 1 ]
then
  if [ $1 == "-man" ]
  then
    rlcman
  else
    echo "Wrong usage. Try relocator.sh -man"
    echo ""
  fi
elif [ $# -eq 2 ]
then

  # Normalizing paths: replacing slash with backslash and removing trailing
  #  backslash
  _DESTPATH=$(echo $2 | sed -e 's|\/|\\|g' | sed -e 's|\\\\|\\|g')
  _DESTPATH=${_DESTPATH%\\}
  _DEFAULTPATH=$(echo $_DEFAULTPATH | sed -e 's|\/|\\|g' | sed -e 's|\\\\|\\|g')
  _DEFAULTPATH=${_DEFAULTPATH%\\}
  _SCRIPTPATH=$(echo $_SCRIPTPATH | sed -e 's|\/|\\|g' | sed -e 's|\\\\|\\|g')
  _SCRIPTPATH=${_SCRIPTPATH%\\}

  if [ $1 == "-s" -a -d $_DESTPATH ]
  then
    echo "Relocating to $_DESTPATH"
    rlcecl $1 $_DESTPATH $_DEFAULTPATH
    rlcwrksp $1 $_DESTPATH $_DEFAULTPATH
  elif [ $1 == "-f" -a -d $_DESTPATH ]
  then
    echo "Forcefully relocating to $_DESTPATH"
    rlcecl $1 $_DESTPATH $_DEFAULTPATH
    rlcwrksp $1 $_DESTPATH $_DEFAULTPATH
  elif [ $1 == "-r" -a -d $_DESTPATH ] 
  then
    echo "Reverting modifications..."
    rlcecl $1 $_DESTPATH
    rlcwrksp $1 $_DESTPATH
  elif ! [ -d $_DESTPATH ] 
  then
    echo "$_DESTPATH is not a valid directory"
    echo ""
    exit 1
  else
    echo "Wrong usage. Try relocator.sh -man"
    echo ""
    exit 1
  fi
else
  echo "Wrong usage. Try relocator.sh -man"
  echo ""
  exit 1
fi
echo "Done"
echo ""
echo "Note: you may need to update the project location from Eclipse."
echo "Select all the project and choose Update Project Location(s)."
exit 0


