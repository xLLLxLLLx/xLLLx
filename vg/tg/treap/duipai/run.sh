#!/bin/bash
while true;do
          ./gen > input
                ./my <input> my.out
                      ./std <input> std.out
                            diff my.out std.out
                                  if [ $? -ne 0 ];then break;fi
                                        echo OK
                                    done



