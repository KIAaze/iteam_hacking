#! /bin/bash
# compile GP2D and i-team

# Check if all parameters are present
# If no, exit
if [ $# -ne 1 ]
then
        echo
        echo "usage :"
        echo "$0 architecture"
	  echo "This shellscript will compile GP2D and i-team."
	  echo "architecture=32 or 64"
        echo
        exit 0
fi

cd ../../gamepower/GP2D/trunk
make linux$1
cd ../../../i-team/trunk
make linux$1
