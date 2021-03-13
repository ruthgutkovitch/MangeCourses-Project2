#include "Course.h"

Course::~Course() {
    delete[] arrayLectures;
}

Course::Course(const Course& other) : courseID(other.courseID), size(other.size), numOfClasses(other.numOfClasses),
                                      arrayLectures(new Lecture* [other.size]) {
    for (int i = 0; i < other.size; i++) {
        arrayLectures[i] = other.arrayLectures[i];
    }
}

Course& Course::operator=(const Course& other) {
    if (this == &other) {
        return *this;
    }
    Lecture** tempArray = new Lecture * [other.size];
    for (int i = 0; i < other.size; i++) {
        tempArray[i] = other.arrayLectures[i];
    }
    delete[] arrayLectures;
    courseID = other.courseID;
    size = other.size;
    numOfClasses = other.numOfClasses;
    arrayLectures = tempArray;
    return *this;
}


int Course::GetCourseID() const {
    return this->courseID;
}

int Course::GetNumOfClasses() const {
    return this->numOfClasses;
}

Lecture* Course::GetPtrLecture(int classID) const {
    return this->arrayLectures[classID];
}

void Course::SetPtrLecture(int classID, Lecture* lecture) {
    this->arrayLectures[classID] = lecture;
}

void Course::AddClass() {
    numOfClasses += 1;
    if(numOfClasses == size){
        Lecture** newArray = new Lecture*[size*2];
        for(int i = 0; i < size; i++){
            newArray[i] = arrayLectures[i];
        }
        for(int i = size; i < 2*size; i++){
            newArray[i] = nullptr;
        }
        delete[] arrayLectures;
        arrayLectures = newArray;
        size = 2*size;
    }
}

int Course::GetArraySize() const {
    return this->size;
}

int Course::GetKey() const {
    return GetCourseID();
}

//check if both courses are equal
bool operator==(const Course& c1, const Course& c2) {
    if (c1.GetCourseID() == c2.GetCourseID()) {
        return true;
    }
    return false;
}

//compare between two courses
bool operator>(const Course& c1, const Course& c2) {
    if (c1.GetCourseID() > c2.GetCourseID()) {
        return true;
    }
    return false;
}

//compare between two courses
bool operator<(const Course& c1, const Course& c2) {
    if (c1.GetCourseID() < c2.GetCourseID()) {
        return true;
    }
    return false;
}

//operator output
std::ostream& operator<<(std::ostream& os, const Course& course) {
    int arraySize = course.GetNumOfClasses();
    os << "courseID to print is:" << course.GetCourseID() << std::endl;
    for (int i = 0; i < arraySize; i++) {
        if(i == 0){
            os << "lecturesID:";
        }
        os << " " << i << " ";
    }
    return os;
}