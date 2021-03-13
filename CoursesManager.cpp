#include "CoursesManager.h"

///destroy the lectures tree first so we dont need to go over the coursesTree and remove the lecture of each Course
CoursesManager::~CoursesManager() {
    delete lecturesTree;
    delete coursesTable;
}

///check if course already exist. if not ,add course to courses tree
CMResult CoursesManager::AddCourse(int courseID) {
    try {
        Course toAdd(courseID);
        try{
            if(this->coursesTable->Find(toAdd) == nullptr){
                this->coursesTable = this->coursesTable->InsertToTable(toAdd);
            }else{
                return CM_FAILURE;
            }
        }catch(const NodeBadAlloc& e){// node allocation error
            return CM_ALLOCATION_ERROR;
        }
    }catch(const CourseBadAlloc& e){//course allocation error
        return CM_ALLOCATION_ERROR;
    }

    return CM_SUCCESS;
}

//check if course exist.if exist remove lectures of given course from tree lectures and then remove course from courses tree
CMResult CoursesManager::RemoveCourse(int courseID) {
    try{
        Course courseToDelete(courseID);
        Node<Course>* toDelete =this-> coursesTable->Find(courseToDelete);
        if(toDelete == nullptr){
            return CM_FAILURE; ///course does not exist
        }
        int numOfClasses = toDelete->GetData()->GetNumOfClasses();
        for(int i = 0; i < numOfClasses; i++){
            Lecture* ptrLecture = toDelete->GetData()->GetPtrLecture(i);
            if(ptrLecture != nullptr) {// if lecture number i exists in lecture tree- we need to remove
                Lecture lectureToDelete(ptrLecture->GetCourseID(), i, ptrLecture->GetLectureTime());
                this->lecturesTree->RemoveVertex(lecturesTree->GetRoot(), lectureToDelete); // remove lecture
                this->watchedClasses -= 1;//update the num of watched lectures
            }
        }
        this->coursesTable = this->coursesTable->RemoveFromTable(toDelete);// remove course
    }catch(const CourseBadAlloc& e){//course allocation error
        return CM_ALLOCATION_ERROR;

    }

    return CM_SUCCESS;
}

CMResult CoursesManager::AddClass(int courseID, int *classID) {
    try{
        Course courseExist(courseID);
        Node<Course>* exist = this->coursesTable->Find(courseExist);
        if(exist == nullptr){
            return CM_FAILURE; ///course does not exist
        }
        exist->GetData()->AddClass();
        *classID = exist->GetData()->GetNumOfClasses() - 1;
    }catch(const CourseBadAlloc& e){//course allocation error
        return CM_ALLOCATION_ERROR;
    }
    return CM_SUCCESS;
}

// add watching time to a lecture
CMResult CoursesManager::WatchClass(int courseID, int classID, int time) {
    try{
        Course courseExist(courseID);
        Node<Course>* exist = coursesTable->Find(courseExist);
        if(exist == nullptr){
            return CM_FAILURE; ///course does not exist
        }
        int numOfClasses = exist->GetData()->GetNumOfClasses();
        if(classID + 1 > numOfClasses){
            return CM_INVALID_INPUT;
        }

        if(exist->GetData()->GetPtrLecture(classID) == nullptr){///first time that this lecture is watched
            try{
                Lecture lectureToAdd_1(courseID, classID, time);
                this->lecturesTree->AddVertex(lecturesTree->GetRoot(), lectureToAdd_1);// add lecture to lectures tree
                Vertex<Lecture>* ptrLecture = lecturesTree->BinarySearch(lecturesTree->GetRoot(), lectureToAdd_1);
                exist->GetData()->SetPtrLecture(classID, ptrLecture->GetData());
                this->watchedClasses += 1;// update the num of watched lectures
            }catch(const VertexBadAlloc& e) {
                return CM_ALLOCATION_ERROR;// vertex allocation error
            }
        }
        else{///lecture is already in lecturesTree - this lecture was watched before
            try{
                Lecture* ptrLecture = exist->GetData()->GetPtrLecture(classID);
                int oldTime = ptrLecture->GetLectureTime();
                int newTime = time + oldTime;
                Lecture lectureToDelete(courseID, classID, oldTime);
                this->lecturesTree->RemoveVertex(lecturesTree->GetRoot(), lectureToDelete);//remove the lecture
                Lecture lectureToAdd_2(courseID, classID, newTime);
                this->lecturesTree->AddVertex(lecturesTree->GetRoot(), lectureToAdd_2);// add the updated lecture
                Vertex<Lecture>* ptr= lecturesTree->BinarySearch(lecturesTree->GetRoot(), lectureToAdd_2);
                exist->GetData()->SetPtrLecture(classID, ptr->GetData());// change the pointer to its new location
            }catch(const VertexBadAlloc& e) {
                return CM_ALLOCATION_ERROR;
            }
        }
    }catch(const CourseBadAlloc& e){
        return CM_ALLOCATION_ERROR;
    }

    return CM_SUCCESS;
}

//return the watching time of a specific lecture
CMResult CoursesManager::TimeViewed(int courseID, int classID, int *timeViewed) const{
    try{
        Course courseExist(courseID);
        Node<Course>* exist = coursesTable->Find(courseExist);
        if(exist == nullptr){
            return CM_FAILURE; ///course does not exist
        }
        if(classID + 1 > exist->GetData()->GetNumOfClasses()){
            return CM_INVALID_INPUT;
        }
        Lecture* lecturePtr = exist->GetData()->GetPtrLecture(classID);
        if(lecturePtr == nullptr){// lecture does not exist in lecture tree - it means watching time is 0
            *timeViewed = 0;
            return CM_SUCCESS;
        }
        *timeViewed = lecturePtr->GetLectureTime();
    }catch(const CourseBadAlloc& e){//course allocation error
        return CM_ALLOCATION_ERROR;
    }
    return CM_SUCCESS;
}

// return the most viewed lectures
CMResult CoursesManager::GetIthWatchedClass(int i, int *courseID, int *classID) {

    if (watchedClasses < i){
        return CM_FAILURE;
    }
    Vertex<Lecture>* lectureVertex = this->lecturesTree->Select(lecturesTree->GetRoot(), watchedClasses-i+1);///change

    *courseID = lectureVertex->GetData()->GetCourseID();
    *classID = lectureVertex->GetData()->GetClassID();

    return CM_SUCCESS;
}


