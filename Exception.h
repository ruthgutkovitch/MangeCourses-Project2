#ifndef MAIN_CPP_EXCEPTION_H
#define MAIN_CPP_EXCEPTION_H

#include <iostream>

class Exceptions : public std::exception {
};

class VertexAlreadyExist : public Exceptions {
};

class VertexDoesNotExist : public Exceptions {
};

class CourseBadAlloc : public std::bad_alloc {

};

class LectureBadAlloc : public std::bad_alloc {

};

class VertexBadAlloc : public Exceptions {

};

class NodeBadAlloc : public Exceptions {

};


#endif //MAIN_CPP_EXCEPTION_H
