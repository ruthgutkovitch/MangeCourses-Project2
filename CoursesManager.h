#ifndef MAIN_CPP_COURSESMANAGER_H
#define MAIN_CPP_COURSESMANAGER_H

#include "RankTree.h"
#include "HashTable.h"
#include "Course.h"

typedef enum {
    CM_SUCCESS = 0,
    CM_FAILURE = -1,
    CM_ALLOCATION_ERROR = -2,
    CM_INVALID_INPUT = -3
} CMResult;



class CoursesManager {
private:
    HashTable<Course>* coursesTable;
    RankTree<Lecture>* lecturesTree;
    int watchedClasses; ///number of lectures in lectureTree

public:
    CoursesManager() : coursesTable(new HashTable<Course>), lecturesTree(new RankTree<Lecture>),
                       watchedClasses(0) {///set prime size for hashTable???
    };

    ~CoursesManager();

    CMResult AddCourse(int courseID);

    CMResult RemoveCourse(int courseID);

    CMResult AddClass(int courseID, int* classID);

    CMResult WatchClass(int courseID, int classID, int time);

    CMResult TimeViewed(int courseID, int classID, int* timeViewed) const;

    CMResult GetIthWatchedClass(int i, int* courseID, int* classID);

};


#endif //MAIN_CPP_COURSESMANAGER_H
