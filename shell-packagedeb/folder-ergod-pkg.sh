#!/bin/bash
function down_and_move(){
    pkg_dir="$2/$1"
    if [ -x $pkg_dir ]; then
        if [ `ls $pkg_dir/*.deb 2>/dev/null | wc -l` != "0" ]; then
            echo ">>> $1 might has already been downloaded and moved."        
            return 2
        fi
    fi
    
    sudo apt-get --reinstall install -d -y $1
    cd "/var/cache/apt/archives"
    deb_count=$(ls *.deb 2>/dev/null | wc -l)

    if [ "$deb_count" == "0" ]; then
        echo ">>> $1 install failed."
        return 3
    fi

    sudo mkdir -p $pkg_dir
    sudo mv ./*.deb $pkg_dir
    sudo chmod 777 $pkg_dir -R
    return 0
}

# begin
sudo apt-get clean
root_dir="/offline"
if [ ! -x "$root_dir" ]; then
    sudo mkdir -p "$root_dir"
fi

files=$1
if [ "${files##*.}"x = "deb"x ]; then 
    arr=$(dpkg -I $1 | grep Depends | sed 's/Depends://g' | sed -r "s/[(][^)]*[)]//g" | tr "| ," " ")
elif [ -e $1 ]; then
    arr=$(cat $1)
else
    arr=$@
fi

for x in ${arr[@]}; do
    echo "------ $x ------" 
    down_and_move $x $root_dir
    value=$?
    echo "return value = $value"
done
