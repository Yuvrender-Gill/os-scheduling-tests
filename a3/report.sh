mkdir sim_results

./sim -f ../../../files/traces/page-simpleloop.ref -m 50 -s 10304 -a lru > ./sim_results/simple_lru_50.txt
./sim -f ../../../files/traces/page-simpleloop.ref -m 100 -s 10304 -a lru > ./sim_results/simple_lru_100.txt

./sim -f ../../../files/traces/page-simpleloop.ref -m 50 -s 10304 -a fifo > ./sim_results/simple_fifo_50.txt
./sim -f ../../../files/traces/page-simpleloop.ref -m 100 -s 10304 -a fifo > ./sim_results/simple_fifo_100.txt

./sim -f ../../../files/traces/page-simpleloop.ref -m 50 -s 10304 -a clock > ./sim_results/simple_clock_50.txt
./sim -f ../../../files/traces/page-simpleloop.ref -m 100 -s 10304 -a clock > ./sim_results/simple_clock_100.txt

./sim -f ../../../files/traces/page-matmul.ref -m 50 -s 10304 -a lru > ./sim_results/matmul_lru_50.txt
./sim -f ../../../files/traces/page-matmul.ref -m 100 -s 10304 -a lru > ./sim_results/matmul_lru_50.txt

./sim -f ../../../files/traces/page-matmul.ref -m 50 -s 10304 -a fifo > ./sim_results/matmul_fifo_50.txt
./sim -f ../../../files/traces/page-matmul.ref -m 100 -s 10304 -a fifo > ./sim_results/matmul_fifo_100.txt

./sim -f ../../../files/traces/page-matmul.ref -m 50 -s 10304 -a clock > ./sim_results/matmul_clock_50.txt
./sim -f ../../../files/traces/page-matmul.ref -m 100 -s 10304 -a clock > ./sim_results/matmul_clock_100.txt

./sim -f ../../../files/traces/page-blocked.ref -m 50 -s 10304 -a lru > ./sim_results/blocked_lru_50.txt
./sim -f ../../../files/traces/page-blocked.ref -m 100 -s 10304 -a lru > ./sim_results/blocked_lru_50.txt

./sim -f ../../../files/traces/page-blocked.ref -m 50 -s 10304 -a fifo > ./sim_results/blocked_fifo_50.txt
./sim -f ../../../files/traces/page-blocked.ref -m 100 -s 10304 -a fifo > ./sim_results/blocked_fifo_100.txt

./sim -f ../../../files/traces/page-blocked.ref -m 50 -s 10304 -a clock > ./sim_results/blocked_clock_50.txt
./sim -f ../../../files/traces/page-blocked.ref -m 100 -s 10304 -a clock > ./sim_results/blocked_clock_100.txt
