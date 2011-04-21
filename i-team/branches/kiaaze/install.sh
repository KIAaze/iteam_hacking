#!/bin/bash

#check out from svn
#svn co https://gamepower.svn.sourceforge.net/svnroot/gamepower/GP2D/trunk/ GP2D
svn co https://gamepower.svn.sourceforge.net/svnroot/gamepower/GP2D/branches/kiaaze/ GP2D
svn co https://i-team.svn.sourceforge.net/svnroot/i-team/branches/kiaaze/ kiaaze
svn co https://i-team.svn.sourceforge.net/svnroot/i-team/trunk/data kiaaze/data

#store working directory
WORKDIR=`pwd`

#build libraries
cd $WORKDIR/GP2D/
make linux32

#copy library
cp $WORKDIR/GP2D/libgp2d.so $WORKDIR/kiaaze/

#copy lib headers
cp -r $WORKDIR/GP2D/lib/ $WORKDIR/kiaaze

#build games
cd $WORKDIR/kiaaze/
make linux32

#create the run script
cat >$WORKDIR/kiaaze/run <<_ACEOF
export LD_LIBRARY_PATH=.:\$LD_LIBRARY_PATH
./iteam
_ACEOF

#make it executable
chmod 755 $WORKDIR/kiaaze/run

#add some pics to data
cp $WORKDIR/kiaaze/angle_pointer.png $WORKDIR/kiaaze/data/gui/ingame/
cp $WORKDIR/kiaaze/dynamite.png $WORKDIR/kiaaze/data/weapons/
cp $WORKDIR/kiaaze/weapon_selector.png $WORKDIR/kiaaze/data/weapons/
cp $WORKDIR/kiaaze/pistol.png $WORKDIR/kiaaze/data/weapons/
cp $WORKDIR/kiaaze/cluster_bomb.png $WORKDIR/kiaaze/data/weapons/
cp $WORKDIR/kiaaze/missile.png $WORKDIR/kiaaze/data/weapons/

#Check that all worked
ls -l $WORKDIR/kiaaze/run
ls -l $WORKDIR/kiaaze/iteam

#tell user what to do
echo "If there haven't been any error messages, you should be able to run the game with:"
echo "cd $WORKDIR/kiaaze/; ./run"
