while read line
do
  echo -e "\e[1;31m$line"
  read line
  echo -e "\e[1;32m$line"
 # read line
 # echo -e "\e[1;34m$line"
done
echo -en "\e[0m"
