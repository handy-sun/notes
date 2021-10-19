#!/bin/bash
function down_check_move(){
    deb_name=$1
    pkg_dir=$2
    record_name=$3
    if [ `egrep ^${deb_name}$ $record_name | wc -l` != "0" ]; then
        echo -e "\033[33m[Warning]\033[0m <$deb_name> might has already been downloaded."        
        return 255
    fi
    
    sudo apt-get --reinstall install -d -y $deb_name
    cd "/var/cache/apt/archives"
    deb_count=$(ls *.deb 2>/dev/null | wc -l)

    if [ "$deb_count" == "0" ]; then
        echo -e "\033[31m[Error]\033[0m $deb_name install failed." 
        return 250
    fi

    sudo mkdir -p $pkg_dir
    sudo mv -f ./*.deb $pkg_dir
    echo $deb_name >> $record_name
    echo -e "\033[32m[Info]\033[0m $deb_name download successfully (include $deb_count debfile)."
    return 0
}

# begin
sudo apt-get clean
root_dir="/offline"
record_file="$root_dir/downloaded.list"

if [ ! -x "$root_dir" ]; then
    sudo mkdir -p "$root_dir"
    sudo chmod 777 $root_dir
fi

if [ ! -e "$record_file" ]; then
    sudo touch "$record_file"
    sudo chmod 777 $record_file
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
    down_check_move $x $root_dir $record_file
    # value=$?; echo -e "return value = $value"
done

sudo chmod 777 $root_dir -R
