# matrix-cpp

Class representing a matrix. Used reference counting in the implementation. Implemented the following functionality:

copy constructor,
assignment operator,
display operator <<,
arithmetic operators: + - * += -= *=,
comparison operators: == !=,
ability to read matrix from input file stream,
single element access - you can overload the () operator, so that m(2, 3) means element placed in row 2, column 3 of the matrix object m,
distinguish between the reading and writing operations,
not allowed to use containers from the C++ standard library except the std::string class
