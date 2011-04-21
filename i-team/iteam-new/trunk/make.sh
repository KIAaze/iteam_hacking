#!/bin/bash
export CPLUS_INCLUDE_PATH=/usr/include/:$GP2DINCDIR
make -f Makefile.linux32 $@
