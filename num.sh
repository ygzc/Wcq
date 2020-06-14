#!/bin/bash
read -p "请输入要租赁的车辆编号: " num 
if [ -z $num ];then             
  echo "车辆编号不为空"
  exit 0
else
  res=`echo "$num*1" | bc `  
  if [ $res -eq 0 ];then          
   echo "车辆编号为整型请重新输入！"
   exit 0
  else exit 1
  fi
fi
