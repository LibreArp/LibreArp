#!/bin/bash

JUCER_FILE="LibreArp.jucer"
HELP_TEXT="Usage: ${0} <switches>

Switches:
    -c      rebuild Projucer
    -h -?   show this help
"

exit_print_help() {
    echo "${HELP_TEXT}"
    exit
}

# Options
while getopts "ch?" opt; do
    case "${opt}" in
        c)
            CLEAN=1
            ;;
        h|\?|*)
            exit_print_help
            ;;
    esac
done

# Get source directory
SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ ${SOURCE} != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

# Change to Projucer build dir
cd "${DIR}/Vendor/juce/extras/Projucer/Builds/LinuxMakefile"

# Clean Projucer
if [[ ${CLEAN} -eq 1 ]]; then
    echo "Rebuilding Projucer ..."
    make clean
fi

# Make Projucer (if it does not exist)
if [ ! -f "build/Projucer" ]; then
    echo "Building Projucer ..."
    make
fi

echo "Starting Projucer ..."
build/Projucer "${DIR}/${JUCER_FILE}"
