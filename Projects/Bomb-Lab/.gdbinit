echo Set explode_bomb breakpoint\n
break explode_bomb

echo \n
echo Always display the next instruction to be executed\n"
display/i $pc

#echo \n
#echo Break Phase 2\n
#break phase_2

#echo \n 
#echo Break Phase 3\n
#break phase_3

#echo \n
#echo Break Phase 4\n
#break phase_4

#echo \n
#echo Break Phase 5\n
#break phase_5

echo \n
echo Break Phase 6\n
break phase_6

echo running program\n
run < bomb33.txt
