#include "Lecture.h"

int Lecture::GetCourseID() const {
    return this->courseID;
}

int Lecture::GetClassID() const {
    return this->classID;
}

int Lecture::GetLectureTime() const {
    return this->time;
}

// operator assignment
Lecture &Lecture::operator=(const Lecture &other) {
    this->courseID = other.courseID;
    this->classID = other.classID;
    this->time = other.time;
    return *this;
}

// check if two lectures are equal
bool operator==(const Lecture& l1, const Lecture& l2){
    if(l1.GetClassID() == l2.GetClassID() &&
       l1.GetCourseID() == l2.GetCourseID() &&
       l1.GetLectureTime() == l2.GetLectureTime()){
        return true;
    }
    return false;
}

// compare two lectures
bool operator>(const Lecture& l1, const Lecture& l2){
    if(l1.GetLectureTime() > l2.GetLectureTime()){
        return true;
    }
    if(l1.GetLectureTime() == l2.GetLectureTime()){
        if(l1.GetCourseID() < l2.GetCourseID()){
            return true;
        }
        if(l1.GetCourseID() == l2.GetCourseID()){
            if(l1.GetClassID() < l2.GetClassID()){
                return true;
            }
        }
    }
    return false;

}

// compare two lectures
bool operator<(const Lecture& l1, const Lecture& l2){
    if(l1.GetLectureTime() < l2.GetLectureTime()){
        return true;
    }
    if(l1.GetLectureTime() == l2.GetLectureTime()){
        if(l1.GetCourseID() > l2.GetCourseID()){
            return true;
        }
        if(l1.GetCourseID() == l2.GetCourseID()){
            if(l1.GetClassID() > l2.GetClassID()){
                return true;
            }
        }
    }
    return false;

}

// output operator
std::ostream& operator<<(std::ostream& os, const Lecture& lecture){
    os << lecture.GetCourseID() << " " << lecture.GetClassID() << " " << lecture.GetLectureTime();
    return os;
}