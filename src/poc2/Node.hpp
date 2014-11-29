#ifndef NODE_HPP
#define	NODE_HPP

class Node {
public:
	
	double *vectorInPDE;
	double *valuesInODEs;
	double coords[3];
	unsigned char sizeOfVectorInPDE;
	unsigned char sizeOfValuesInODEs;
	
	Node(unsigned char _sizeOfVectorInPDE, unsigned char _sizeOfValuesInODEs);
	Node(const Node &orig);
	~Node();
	void operator=(const Node& orig);
	
private:

};

#endif	/* NODE_HPP */

