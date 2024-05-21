s:sum_serial
m:sum_multi_thread
sum_serial:sum_serial.c
	gcc sum_serial.c -o sum_serial
sum_multi_thread:sum_multi_thread.c
	gcc sum_multi_thread.c -pthread -o sum_multi_thread
clean:
	rm -rf sum_multi_thread sum_serial
.phony: clean s m