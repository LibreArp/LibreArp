#!/usr/bin/env bash

#
# This file is part of LibreArp
#
# LibreArp is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# LibreArp is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see https://librearp.gitlab.io/license/.
#

#############################################################
# Supplemental script for installing LibreArp via Homebrew. #
#############################################################

set -e

# Get script source directory (https://stackoverflow.com/a/246128/3833894)
SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do
  DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE"
done
DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )"


LIB_DIR="$(cd "$DIR/../lib/librearp" >/dev/null 2>&1 && pwd)"
TARGET_VST3_PATH="$LIB_DIR/LibreArp.vst3"

if [ $# == 0 ]; then
  ACTION="install"
  TYPE="local"
elif [ $# == 1 ]; then
  ACTION="$1"
  TYPE="local"
elif [ $# == 2 ]; then
  ACTION="$1"
  TYPE="$2"
fi

case "$TYPE" in
  "local")
    if [ "$EUID" == 0 ]; then
      echo "Type 'local' is not allowed with sudo!" > /dev/stderr
      echo "Did you mean 'sudo update-librearp $ACTION global'?" > /dev/stderr
      exit 1
    fi

    if [ "$(uname -s)" = "Darwin" ]; then
      ROOT_VST3_PATH="$HOME/Library/Audio/Plug-ins/VST3"
    else
      ROOT_VST3_PATH="$HOME/.vst3"
    fi
    ;;

  "global")
    if [ "$(uname -s)" = "Darwin" ]; then
      ROOT_VST3_PATH="/Library/Audio/Plug-ins/VST3"
    else
      ROOT_VST3_PATH="/usr/lib/vst3"
    fi
    ;;

  *)
    echo "Unknown installation type '$1'" > /dev/stderr
    echo "Available types: local, global" > /dev/stderr
    exit 1
    ;;
esac

mkdir -p "$ROOT_VST3_PATH"
LINK_VST3_PATH="$ROOT_VST3_PATH/LibreArp.vst3"

case "$ACTION" in
  "install")
    if [ -h "$LINK_VST3_PATH" ]; then
      echo "Removing existing '$LINK_VST3_PATH'."
      rm -f "$LINK_VST3_PATH"
    fi

    echo "Creating link '$LINK_VST3_PATH' to '$TARGET_VST3_PATH'."
    ln -s "$TARGET_VST3_PATH" "$LINK_VST3_PATH"
    ;;

  "remove")
    echo "Removing '$LINK_VST3_PATH'."
    rm -rf "$LINK_VST3_PATH"
    ;;

  *)
    echo "Unknown action '$1'" > /dev/stderr
    echo "Available actions: install, remove" > /dev/stderr
    exit 1
esac
