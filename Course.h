#ifndef MAIN_CPP_COURSE_H
#define MAIN_CPP_COURSE_H

#include "Lecture.h"

class Course {
private:
    int courseID;
    int size;
    int numOfClasses;
    Lecture** arrayLectures;
public:
    explicit Course(int courseID, int size = 1, int numOfClasses = 0) : courseID(courseID), size(size), numOfClasses(numOfClasses), arrayLectures(new Lecture*[size]) {
        for(int i = 0; i < size; i++){
            arrayLectures[i] = nullptr;
        }
    };
    ~Course();
    Course(const Course& other);
    Course& operator=(const Course& other);
    int GetCourseID() const;
    int GetNumOfClasses() const;
    int GetArraySize() const;
    int GetKey() const;
    Lecture* GetPtrLecture(int classID) const;
    void SetPtrLecture(int classID, Lecture* lecture);
    void AddClass();

};

std::ostream& operator<<(std::ostream& os, const Course& course);
bool operator==(const Course& c1, const Course& c2);
bool operator<(const Course& c1, const Course& c2); ///change
bool operator>(const Course& c1, const Course& c2); ///change


#endif //MAIN_CPP_COURSE_H
