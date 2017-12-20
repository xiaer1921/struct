#!/bin/bash
#achieve a progress_bar
function bar()
{

    i=0
    str=""
    #echo $arr : |/-\ echo ${arr[*]} ,echo ${arr[0]}, blank space isseparator, like arr=(1 2),arr have two elements.
    arr=("|" "/" "-" "\\")
    while [ $i -le 100 ]
    do
	    let index=i%4
        let indexcolor=i%8
        let color=30+indexcolor
        if [ $i -eq 100 ];then
            arr[0]=' '
        fi
        # \e[n1,n2,n3m to set bar
        #n1: display like bold, underline
        #n2:font colour  scope: 30+(0,7)
        #0 (black), 1 (red), 2 (green), 3 (yellow), 4 (blue), 5 (Yang Hong), 6 (green), 7 (white).
        #n3:backgroud colour scope: 40+(0,7)
	    printf "\e[0;$color;1m[%-100s][%d%%]%c\r" "$str" "$i" "${arr[$index]}"
	    #usleep will be removed in near future
        sleep 0.1
	    let i++
	    str+='='
    done
    echo
}
bar
