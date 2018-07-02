perl : test.o perl_num_ip.o
	g++ test.o perl_num_ip.o -lpthread -lgtest -lhs -o test/perl
	./test/perl
test.o : test.cc perl_num_ip.h
	g++ -c test.cc
perl_num_ip.o : perl_num_ip.cc perl_num_ip.h
	g++ -c perl_num_ip.cc
exec:
	./test/perl
clean:
	rm -f test.o perl_num_ip.o test/perl 
