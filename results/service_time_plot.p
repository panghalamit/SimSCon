set terminal pdf linewidth 1 enhanced color font ",7" dashed dl 1.5
set output "service_time_vm.pdf"
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                         # set xtics automatically
set ytic auto                          # set ytics automatically
set title "Service time of VM0"
set ylabel "service time"
set xlabel "request time"
#set key 4, 13000
set xr [0:100]
set yr [0:5]

set multiplot layout 4,1
do for [i=0:3] {
	set title "Service time of VM".i
	plot  "service_time_vm".i.".txt" using 1 title "VM".i with lines
}
unset multiplot
set output
