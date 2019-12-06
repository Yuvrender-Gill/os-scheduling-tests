./sim -f Trace1.ref -m 8 -s 10000 -a fifo > ./sim_results/trace1_fifo.txt
./sim -f Trace1.ref -m 8 -s 10000 -a clock > ./sim_results/trace1_clock.txt
./sim -f Trace1.ref -m 8 -s 10000 -a lru > ./sim_results/trace1_lru.txt

./sim -f Trace2.ref -m 8 -s 10000 -a fifo > ./sim_results/trace2_fifo.txt
./sim -f Trace2.ref -m 8 -s 10000 -a clock > ./sim_results/trace2_clock.txt
./sim -f Trace2.ref -m 8 -s 10000 -a lru > ./sim_results/trace2_lru.txt

./sim -f Trace3.ref -m 8 -s 10000 -a fifo > ./sim_results/trace3_fifo.txt
./sim -f Trace3.ref -m 8 -s 10000 -a clock > ./sim_results/trace3_clock.txt
./sim -f Trace3.ref -m 8 -s 10000 -a lru > ./sim_results/trace3_lru.txt