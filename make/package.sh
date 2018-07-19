#!/bin/bash
if [ $# -lt 1 ]; then
    echo "params error"
    echo "pls input version"
    exit
fi
version=$1
rm -rf ../package
mkdir -p  ../package/$version
cd ../package/$version
pwd
cp ../../output/dbc ./
cp -R ../../conf/ ./
cp ../../tool/add_dbc_user.sh ./
cp ../../tool/p ./
cp ../../tool/mining_install.sh ./
cp ../../tool/stopapp ./
cp ../../tool/startapp ./
cp ../../tool/startaiserver ./
cp ../../tool/rm_containers.sh ./
cp ../../tool/docker_gpg.key ./
cp ../../tool/plog           ./
cp ../../tool/swarm.key      ./
chmod +x *
cd ../
tar -cvf dbc-linux-$version.tar $version 
gzip *.tar
