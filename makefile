test: matrix.h test_matrix_rc.cpp
	g++ -g -Wall -pedantic -o matrix test_matrix_rc.cpp matrix.h
clean:
	rm matrix
