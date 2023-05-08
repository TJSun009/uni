#pragma once

#include "hope_objs.h"

enum{ID_M_DEGREE = 0001};
enum{ID_M_STUDENT = 0002};
enum{ID_M_COURSE = 1003};
enum{ID_M_GRADES = 1004};
enum{M_FRAME = 1005};

//degree IDs
enum{ID_C_DEGREE = 1001};
enum{ID_U_DEGREE = 1002};
enum{ID_M_DEGREE_PANEL = 1003};
enum{ID_CLOSE_DEGREE_DLG = 1004};
enum{ID_ADD_DEGREE = 1005};
enum{ID_UPDATE_DEGREE = 1006};


//student IDs
enum{ID_C_STUDENT = 3001};
enum{ID_U_STUDENT = 3002};
enum{ID_M_STUDENT_PANEL = 3003};
enum{ID_CLOSE_STUDENT_DLG = 3004};
enum{ID_ADD_STUDENT = 3005};
enum{ID_UPLOAD_STUDENT = 3006};
enum{ID_EDIT_MARKS = 3007};
enum{ID_UPDATE_MARKS = 3008};
enum{ID_UPDATE_STUDENT = 3009};
enum{ID_SECOND_ATTEMPT = 3010};
// student button ids starting from 7000

//course IDs
enum{ID_C_COURSE = 4001};
enum{ID_U_COURSE = 4002};
enum{ID_M_COURSE_PANEL = 4003};
enum{ID_CLOSE_COURSE_DLG = 4004};
enum{ID_ADD_COURSE = 4005};
enum{ID_UPLOAD_COURSE = 4006};
enum{ID_EDIT_ASSESSMENTS = 4007};
enum{ID_UPDATE_ASSESSMENTS = 4008};
enum{ID_UPDATE_COURSE = 4009};
enum{ID_ADD_ASSESSMENT = 4010};
enum{P_ASSESSMENTS= 4011};
enum{C_ASSESSMENTS = 4012};
enum{E_ASSESSMENTS = 4013};
enum{ID_INSERT_ASSESSMENT = 4014};

//gradeLetter IDs
enum{ID_UPDATE_GRADES = 4100};
extern hope_vars *env_hope_vars;