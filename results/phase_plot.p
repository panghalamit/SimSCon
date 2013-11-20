set terminal pdf linewidth 1 enhanced color font ",7" dashed dl 1.5
set output "response_time_phase_vm.pdf"
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                         # set xtics automatically
set ytic auto                          # set ytics automatically
set title "avg response time at vms during each phase"
set ylabel "average response time"
set xlabel "phase number"
set xr [0:4]
set yr [0:]
plot  "response_time_phase.txt" using 1 title "VM0" with linespoint , \
"response_time_phase.txt" using 2 title "VM1" with linespoint, \
"response_time_phase.txt" using 3 title "VM2" with linespoint, \
"response_time_phase.txt" using 4 title "VM3" with linespoint
set output

set terminal pdf linewidth 1 enhanced color font ",7" dashed dl 1.5
set output "waiting_time_phase_vm.pdf"
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                         # set xtics automatically
set ytic auto                          # set ytics automatically
set title "avg waiting time at vms during each phase"
set ylabel "average waiting time"
set xlabel "phase number"
set xr [0:4]
set yr [0:]
plot  "waiting_time_phase.txt" using 1 title "VM0" with linespoint , \
"waiting_time_phase.txt" using 2 title "VM1" with linespoint, \
"waiting_time_phase.txt" using 3 title "VM2" with linespoint, \
"waiting_time_phase.txt" using 4 title "VM3" with linespoint
set output


set terminal pdf linewidth 1 enhanced color font ",7" dashed dl 1.5
set output "queue_length_phase_vm.pdf"
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                         # set xtics automatically
set ytic auto                          # set ytics automatically
set title "avg queue length at vms during each phase"
set ylabel "average queue length"
set xlabel "phase number"
set xr [0:4]
set yr [0:]
plot  "queuelength_phase.txt" using 1 title "VM0" with linespoint , \
"queuelength_phase.txt" using 2 title "VM1" with linespoint, \
"queuelength_phase.txt" using 3 title "VM2" with linespoint, \
"queuelength_phase.txt" using 4 title "VM3" with linespoint
set output

set terminal pdf linewidth 1 enhanced color font ",7" dashed dl 1.5
set output "profit_phase_vm.pdf"
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                         # set xtics automatically
set ytic auto                          # set ytics automatically
set title "profit of vms during each phase"
set ylabel "profit"
set xlabel "phase number"
set xr [0:4]
set yr [0:]
plot  "response_time_phase.txt" using 1 title "VM0" with linespoint , \
"profit_phase.txt" using 2 title "VM1" with linespoint, \
"profit_phase.txt" using 3 title "VM2" with linespoint, \
"profit_phase.txt" using 4 title "VM3" with linespoint
set output