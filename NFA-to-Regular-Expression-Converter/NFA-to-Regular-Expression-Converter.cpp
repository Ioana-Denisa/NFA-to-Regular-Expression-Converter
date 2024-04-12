#include<iostream>
#include"NFA.h"

int main()
{
	NFA afd;
	afd.printAutomaton();
	afd.updateAutomaton();
	std::string regularExpression = afd.getRegularExpresion();
	std::cout << "Expresia regulata este: " << regularExpression << "\n\n";


	return 0;
}


//6
//q0 q1 a
//q0 q2 b
//q1 q2 a
//q1 q1 b
//q2 q2 a
//q2 q2 b
//q0
//q2

//4
//q0 q1 a
//q0 q0 b
//q1 q1 a
//q1 q0 b
//q0
//q1


//6
//q0 q1 b
//q1 q0 a
//q1 q1 b
//q1 q2 a
//q1 q2 b
//q2 q2 b
//q0
//q2


//7
//q0 q1 a
//q0 q2 b
//q1 q2 a
//q1 q1 a
//q1 q3 a
//q1 q3 b
//q2 q1 b
//q0
//q3