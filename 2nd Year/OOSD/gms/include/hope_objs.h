#pragma once

#include "csv.h"

/*building upon csv.h methods can be used to parse data from the csv's into objects
    - i.e. see csv.cpp:
    - handles types, string, int and float
    - they are accessed using a map i.e.
    - Create csv obj
        - csv obj_name("file_name(no extension)")
    - Add objects from named file:
        - obj_name.read() - return void places results in a map called obj_name.output
        - Alternatively obj.getResult() returns theoutput map
    - Accessing data from obj_name  
        - csv_map['name'], gives access to the name column of the csv file
        - This is a vector containing ints, strings and floats
        - Other types can be handled in the hope_objs.h file and converted back to these basic types

*/

class assessment
{
    public:
        string name;
        float weighting;
        string deadline;
        friend class hope_vars;
        
        assessment(){};

        assessment(string name, float weighting, string deadline) : name(name), weighting(weighting), deadline(deadline){};

        ~assessment(){};
        
        void updateAssessment();
        void getAssessment();
        void setAssessment(vector<variant<int, string, float> > assessment);
};

class courseObj
{
    public:
        string name;
        string level;
        //three vectors, one for portfolios, one for coursework and another for exams
        map<string, vector<assessment*>> assessments
        {
            {"Portfolios", {}},
            {"Coursework", {}},
            {"Exams", {}}
        };
        friend class hope_vars;
        
        courseObj(){};

        courseObj(string name, string level, vector<assessment*> portfolios, vector<assessment*> coursework, vector<assessment*> exams ) : name(name), level(level)
        {
            assessments["Portfolios"] = portfolios;
            assessments["Coursework"] = coursework;
            assessments["Exams"] = exams;
        };

        ~courseObj(){};

        bool checkWeights();
        void updateCourse();
        void getCourse();

};

class degreeObj
{
    public:
        string name;
        string start;
        string end;
        courseObj* course1;
        courseObj* course2;
        friend class hope_vars;
    
        degreeObj(){};

        degreeObj(string name, string start, string end, courseObj* c1, courseObj* c2) : name(name), start(start), end(end)
        {
            course1 = c1;
            course2 = c2;
        };

        ~degreeObj(){};

        vector<variant<int, string, float> > getDegree();
        void setCourse1();
        void setCourse2();
        void updateDegree(string name=NULL, string start=NULL, string end=NULL);
};

class gradeLetter
{
    public:
        string letter;
        float min;
        float max;
        
        gradeLetter(){};

        gradeLetter(string letter, float min, float max): letter(letter), min(min), max(max){};

        ~gradeLetter(){};

        void updateGrade(string letter, float min, float max);
        void addGradeLetters(string letter, float min, float max);
};

class studentObj
{
    public:
        int id;
        string firstname;
        string surname;
        vector<degreeObj*>studentDegrees;
        friend class hope_vars;
        
        studentObj();
        studentObj(int id, string firstname, string surname, vector<degreeObj*>degrees): id(id), firstname(firstname), surname(surname)
        {
            studentDegrees = degrees;
        };

        ~studentObj(){};

        void enrol(vector<string> courseNames);
        void view_transcript();
};

class studentMark
{
    public:
        int id;
        string degree;
        string course;
        string assessment;
        int marks;

        studentMark(){};

        studentMark(int id, string degree, string course, string assessment, int marks):id(id), degree(degree), course(course), assessment(assessment), marks(marks){};

        ~studentMark(){};
};

class hope_vars
{
    public:
        vector<assessment*> assessments;
        vector<courseObj*> courses;
        vector<degreeObj*> degrees;
        vector<studentObj*> students;
        vector<studentMark*> studentMarks;
        vector<gradeLetter*> gradeLetters;

        csv *assessmentCSV = nullptr;
        csv *courseCSV = nullptr;
        csv *degreeCSV = nullptr;
        csv *studentCSV = nullptr;
        csv *studentMarkCSV = nullptr;
        csv *gradeLetterCSV = nullptr;
        
        hope_vars()
        {
            assessmentCSV = new csv("tables/assessment");
            courseCSV = new csv("tables/course");
            degreeCSV = new csv("tables/degree");
            studentCSV = new csv("tables/student");
            studentMarkCSV = new csv("tables/studentMark");
            gradeLetterCSV = new csv("tables/gradeLetter");

            load();
        }

        ~hope_vars()
        {
            assessmentCSV->write(toCSV(assessmentCSV->getResult(), "assessment", assessments.size()));
            courseCSV->write(toCSV(courseCSV->getResult(), "course", courses.size()));
            degreeCSV->write(toCSV(degreeCSV->getResult(), "degree", degrees.size()));
            studentCSV->write(toCSV(studentCSV->getResult(), "student", students.size()));
            studentMarkCSV->write(toCSV(studentMarkCSV->getResult(), "studentMark", studentMarks.size()));
            gradeLetterCSV->write(toCSV(gradeLetterCSV->getResult(), "gradeLetter", gradeLetters.size()));
            
        };

        void load();

        void loadHelper(map<string, vector<variant<int, string, float> > > table, string type);

        map<string, vector<variant<int, string, float> > > toCSV(map<string, vector<variant<int, string, float> > > table, string type, int size);
        void printhope_vars();

        vector<string> vectorize(string input);

        string stringifyVect(vector<variant<int, string, float> > vect);

        gradeLetter* findGradeLetter(string letter);

        vector<assessment*> findAssessments(string arr);

        vector<courseObj*> findCourses(string arr);

        vector<degreeObj*> findDegrees(string arr);

        studentObj* findStudent(int i);

        vector<studentMark*> findStudentMarks(int i);

        void updateVar(string type);

        void hopeWxGrid(wxGrid *grid, string type="");
};