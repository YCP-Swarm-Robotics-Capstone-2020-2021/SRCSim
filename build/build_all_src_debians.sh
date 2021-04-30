#!/bin/bash -e

print_help(){
    echo
    echo "This is a script that builds all of the swarm debians."
    echo "          --help    | -h        Prints this message."
}

while [[ "$1" =~ ^- && ! "$1" == "--" ]]; do
    case $1 in
	-h | --help )
	    print_help
	    exit 0
	    ;;
	* )
	    print_help
	    exit 1
	    ;;
    esac; shift; done
if [[ "$1" == '--' ]]; then shift; fi

for ((i=0 ; i < 5; i++)); do
    /bin/bash build_src_debian.sh -d $i
done

mv dolphin*.deb ./debians
