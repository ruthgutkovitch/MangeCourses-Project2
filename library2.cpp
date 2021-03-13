#include "library2.h"
#include "CoursesManager.h"

void *Init(){
    CoursesManager* DS = new CoursesManager();
    return (void*)DS;
}

StatusType AddCourse(void* DS, int courseID){
    if (DS == nullptr || courseID <= 0) {
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->AddCourse(courseID);
    return (StatusType)res;
}

StatusType RemoveCourse(void *DS, int courseID){
    if (DS == nullptr || courseID <= 0) {
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->RemoveCourse(courseID);
    return (StatusType)res;
}

StatusType AddClass(void* DS, int courseID, int* classID){
    if (DS == nullptr || courseID <= 0) {
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->AddClass(courseID, classID);
    return (StatusType)res;
}

StatusType WatchClass(void *DS, int courseID, int classID, int time){
    if (DS == nullptr || courseID <= 0 || classID < 0 || time <= 0) {
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->WatchClass(courseID, classID, time);
    return (StatusType)res;
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed){
    if (DS == nullptr || courseID <= 0 || classID < 0) {
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->TimeViewed(courseID, classID, timeViewed);
    return (StatusType)res;
}

StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID){
    if (DS == nullptr || i <= 0) {
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->GetIthWatchedClass(i, courseID, classID);
    return (StatusType)res;
}

void Quit(void** DS){
    delete (CoursesManager*)DS[0];
    *DS = nullptr;
}