#ifndef _TYPEFACTORY_H
#define _TYPEFACTORY_H

#include <vector>
#include <complex>
#include <sstream>

#define _MD_DIM 3 // default to MD in 3 dimensional space

typedef float RealType;
typedef std::vector<RealType> PosType;
typedef std::complex<RealType> ComplexType;

template <typename T>
std::string str(std::vector<T> v){
	std::ostringstream os;
	os << "( ";
	for (int i=0;i<v.size();i++){
		os << v[i] << " ";
	} os << ")";
	return os.str();
}

#endif
