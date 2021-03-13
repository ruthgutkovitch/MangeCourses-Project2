#ifndef MAIN_CPP_LECTURE_H
#define MAIN_CPP_LECTURE_H

#include <iostream>

class Lecture{
private:
    int courseID;
    int classID;
    int time;

public:
    Lecture(int courseID, int classID, int time) :
            courseID(courseID), classID(classID), time(time){};
    ~Lecture() = default;
    Lecture(const Lecture& other) : courseID(other.courseID), classID(other.classID), time(other.time){};
    Lecture& operator=(const Lecture& other);
    int GetCourseID() const;
    int GetClassID() const;
    int GetLectureTime() const;

};

std::ostream& operator<<(std::ostream& os, const Lecture& lecture);
bool operator==(const Lecture& l1, const Lecture& l2);
bool operator>(const Lecture& l1, const Lecture& l2);
bool operator<(const Lecture& l1, const Lecture& l2);


#endif //MAIN_CPP_LECTURE_H
