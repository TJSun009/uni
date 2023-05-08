#include "hope_objs.h"

string trim(const string &s)
{
    string pass1 = regex_replace(s, regex("^\\s+"), "");
    return regex_replace(pass1, regex("\\s+$"), "");
}

variant<int, string, float> sortType (string data)
{
    data = trim(data);

    vector<char> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    vector<char> chars = {};

    bool decimal = false;

    for(char c : data)
    {
        if (find(digits.begin(), digits.end(), c) == digits.end() && c != ' ')
        {
            chars.push_back(c);
        }
    }

    if (chars.empty())
    {
        return stoi(data);
    }
    else if(chars[0] == '.')
    {
        return stof(data);
    }
    
    return data;
}

void hope_vars::load()
{
    loadHelper(assessmentCSV->getResult(), "assessment");

    loadHelper(courseCSV->getResult(), "course");

    loadHelper(degreeCSV->getResult(), "degree");

    //studentMarks must come before students to prevent overwrite of data

    loadHelper(studentMarkCSV->getResult(), "studentMark");
    
    loadHelper(studentCSV->getResult(), "student");
    
    loadHelper(gradeLetterCSV->getResult(), "gradeLetter");

    printhope_vars();
}

void hope_vars::loadHelper(map<string, vector<variant<int, string, float> > > table, string type)
{
    if(table.size() == 0)
    {
        cout << "Please provide a file to load." << endl;
        return;
    }

    int j = 0;

    vector<string> columns; 

    for(const auto &[key, values] : table)
    {
        string columnName = key;

        columns.push_back(columnName);

        j++;
    }

    for(int row = 0; row != table[columns[0]].size(); row++)
    {
        if(type == "assessment")
        {
            string n = get<string>(table["1-name"][row]);
            float w = get<float>(table["2-weighting"][row]);
            string d = get<string>(table["3-deadline"][row]);
            
            assessment *as = new assessment(n, w, d);
            assessments.push_back(as);
        }
        else if(type == "course")
        {
            string n = get<string>(table["1-name"][row]);
            string l = get<string>(table["2-level"][row]);
            string p = get<string>(table["3-portfolios"][row]);
            string c = get<string>(table["4-coursework"][row]);
            string e = get<string>(table["5-exams"][row]);
            
            courseObj *cs = new courseObj(n, l, findAssessments(p), findAssessments(c), findAssessments(e));
            courses.push_back(cs);
        }
        else if(type == "degree")
        {
            string n = get<string>(table["1-name"][row]);
            string s = get<string>(table["2-start"][row]);
            string e = get<string>(table["3-end"][row]);
            string c1 = get<string>(table["4-course1"][row]);
            string c2 = get<string>(table["5-course2"][row]);
            
            degreeObj *dg = new degreeObj(n, s, e, findCourses(c1).front(), findCourses(c2).front());
            degrees.push_back(dg);
        }
        else if(type == "student")
        {
            int i = get<int>(table["1-id"][row]);
            string f = get<string>(table["2-firstname"][row]);
            string s = get<string>(table["3-surname"][row]);
            string sc = get<string>(table["4-degrees"][row]);

            studentObj *st = new studentObj(i, f, s, findDegrees(sc));
            students.push_back(st);

            if(findStudentMarks(i).size() == 0)
            {
                for(degreeObj *d : st->studentDegrees)
                {
                    courseObj *c1 = d->course1;

                    for(assessment *as : c1->assessments["Portfolios"])
                    {
                        studentMarks.push_back(new studentMark(i, d->name, c1->name, as->name, 101));
                    }

                    for(assessment *as : c1->assessments["Coursework"])
                    {
                        studentMarks.push_back(new studentMark(i, d->name, c1->name, as->name, 101));
                    }

                    for(assessment *as : c1->assessments["Exams"])
                    {
                        studentMarks.push_back(new studentMark(i, d->name, c1->name, as->name, 101));
                    }

                    c1 = d->course2;

                    for(assessment *as : c1->assessments["Portfolios"])
                    {
                        studentMarks.push_back(new studentMark(i, d->name, c1->name, as->name, 101));
                    }

                    for(assessment *as : c1->assessments["Coursework"])
                    {
                        studentMarks.push_back(new studentMark(i, d->name, c1->name, as->name, 101));
                    }

                    for(assessment *as : c1->assessments["Exams"])
                    {
                        studentMarks.push_back(new studentMark(i, d->name, c1->name, as->name, 101));
                    }
                }

                updateVar("studentMark");
            }
        }
        else if(type == "studentMark")
        {
            int i = get<int>(table["1-id"][row]);
            string d = get<string>(table["2-degree"][row]);
            string c = get<string>(table["3-course"][row]);
            string a = get<string>(table["4-assessment"][row]);
            int m = get<int>(table["5-marks/100"][row]);
            
            studentMark *stM = new studentMark(i, d, c, a, m);
            studentMarks.push_back(stM);
        }
        else if(type == "gradeLetter")
        { 
            string l = get<string>(table["1-letter"][row]);
            float min = get<float>(table["2-min"][row]);
            float max = get<float>(table["3-max"][row]);
            
            gradeLetter *gL = new gradeLetter(l, min, max);
            gradeLetters.push_back(gL);
        }          
    }
}

string hope_vars::stringifyVect(vector<variant<int, string, float> > vect)
{
    string output="[";

    int size = vect.size();
    int counter = 0;

    for(variant<int, string, float> s : vect)
    {
        output+=get<string>(s);

        output+= counter == size - 1 ? "]" : ",";
        counter++;
    }

    return output;
}

gradeLetter* hope_vars::findGradeLetter(string letter)
{
    for(auto g : gradeLetters)
    {
        if(g->letter == letter)
        {
            return g;
        }
    }

    return nullptr;
}

vector<string> hope_vars::vectorize(string input)
{
    vector<string> output;

    string temp = "";

    if (!regex_search(input, regex(",")))
    {
        input = regex_replace(input, regex("^\\["), "");
        input = regex_replace(input, regex("\\]$"), "");
        output.push_back(input);
        return output;
    }

    for(char c : input)
    {
        if(c != '[' && c != ']')
        {
            if (c == ',')
            {
                temp = trim(temp);
                output.push_back(temp);
                temp="";
            }
            else
            {
                temp+=c;
            }
        }
    }
    output.push_back(trim(temp));
    return output;
}

vector<assessment*> hope_vars::findAssessments(string arr)
{
    vector<string> list = vectorize(arr);
    vector<assessment*> res;

    for(assessment *a : assessments)
    {
        for(string s : list)
        {
            if(s == a->name)
            {
                res.push_back(a);
            }

            if(list.size() == res.size()) break;
        }

        if(list.size() == res.size()) break;
    }

    try
    {
        if(list.size() != res.size()) throw;
    }
    catch(...)
    {
        cout << "One of the assessments could not be found. Check the assessments.csv file.";
    }

    return res;
}

vector<courseObj*> hope_vars::findCourses(string arr)
{
    vector<string> list = vectorize(arr);
    vector<courseObj*> res;

    for(courseObj *c : courses)
    {
        for(string s : list)
        {
            if(s == c->name)
            {
                res.push_back(c);
            }

            if(list.size() == res.size()) break;
        }

        if(list.size() == res.size()) break;
    }

    try
    {
        if(list.size() != res.size()) throw;
    }
    catch(...)
    {
        cout << "One of the courses could not be found. Check the course.csv file.";
    }

    return res;
}

studentObj* hope_vars::findStudent(int i)
{
    int index = 0;

    for(auto st : students)
    {
        if(i == st->id)
        {
            return st;
        }
        index++;
    }

    return nullptr;
}

vector<degreeObj*> hope_vars::findDegrees(string arr)
{
    vector<string> list = vectorize(arr);

    vector<degreeObj*> res;

    for(degreeObj *dg : degrees)
    {
        for(string s : list)
        {
            if(s == dg->name)
            {
                res.push_back(dg);
            }

            if(list.size() == res.size()) break;
        }

        if(list.size() == res.size()) break;
    }
    
    try
    {
        if(list.size() != res.size()) throw;
    }
    catch(...)
    {
        cout << "One of the degrees could not be found. Check the degree.csv file.";
    }

    return res;
}

vector<studentMark*> hope_vars::findStudentMarks(int i)
{
    vector<studentMark*> res;

    for(auto stM : studentMarks)
    {
        if(stM->id == i)
        {
            res.push_back(stM);
        }
    }
    return res;
}

map<string, vector<variant<int, string, float> > > hope_vars::toCSV(map<string, vector<variant<int, string, float> > > table, string type, int size)
{
    int j = 0;

    vector<string> columns;

    for(const auto &[key, values] : table)
    {
        string columnName = key;

        columns.push_back(columnName);

        j++;
    }

    table = {};

    vector<variant<int, string, float> > res;

    for(int row = 0; row != size; row++)
    {
        if(type == "assessment")
        {
            table["1-name"].push_back(assessments[row]->name);
            table["2-weighting"].push_back(assessments[row]->weighting);
            table["3-deadline"].push_back(assessments[row]->deadline);           
        }
        else if(type == "course")
        {
            table["1-name"].push_back(courses[row]->name);

            table["2-level"].push_back(courses[row]->level);

            vector<variant<int, string, float> > temp;

            for(assessment* a : courses[row]->assessments["Portfolios"])
            {
                temp.push_back(a->name);
            }

            table["3-portfolios"].push_back(stringifyVect(temp));

            temp = {};

            for(assessment* a : courses[row]->assessments["Coursework"])
            {
                temp.push_back(a->name);
            }

            table["4-coursework"].push_back(stringifyVect(temp));

            temp = {};

            for(assessment* a : courses[row]->assessments["Exams"])
            {
                temp.push_back(a->name);
            }

            table["4-exams"].push_back(stringifyVect(temp));

            temp = {};
        }
        else if(type == "degree")
        {
            table["1-name"].push_back(degrees[row]->name);
            table["2-start"].push_back(degrees[row]->start);
            table["3-end"].push_back(degrees[row]->end);
            table["4-course1"].push_back(degrees[row]->course1->name);
            table["5-course2"].push_back(degrees[row]->course2->name);
        }
        else if(type == "student")
        {
            table["1-id"].push_back(students[row]->id);
            table["2-firstname"].push_back(students[row]->firstname);
            table["3-surname"].push_back(students[row]->surname);

            vector<variant<int, string, float> > temp;

            for(degreeObj* c : students[row]->studentDegrees)
            {
                temp.push_back(c->name);
            }

            table["4-degrees"].push_back(stringifyVect(temp));
        }
        else if(type == "studentMark")
        {
            table["1-id"].push_back(studentMarks[row]->id);
            table["2-degree"].push_back(studentMarks[row]->degree);
            table["3-course"].push_back(studentMarks[row]->course);
            table["4-assessment"].push_back(studentMarks[row]->assessment);
            table["5-marks/100"].push_back(studentMarks[row]->marks);
        }    
        else if(type == "gradeLetter")
        {
            table["1-letter"].push_back(gradeLetters[row]->letter);
            table["2-min"].push_back(gradeLetters[row]->min);
            table["3-max"].push_back(gradeLetters[row]->max);
        }      
    }

    return table;
}

void hope_vars::printhope_vars()
{
    int size = 0;
    int counter = 0;

    cout << "Assessments:" << endl;
    for(assessment *a : assessments)
    {
        cout << "Name: " << a->name << endl;
        cout << "Weighting: " << a->weighting << " | ";
        cout << "Deadline: " << a->deadline << endl << endl;
    }

    cout << endl;

    cout << "Courses:" << endl;
    for(courseObj *c : courses)
    {
        cout << "Name: " << c->name << endl;
        cout << "Level: " << c->level << endl;

        //Portfolios
        cout << "Portfolios: " << " [";
        vector<assessment*> p = c->assessments["Portfolios"];
        size = p.size();
        counter = 0;
        for(assessment* a: p)
        {
            cout << a->name;

            if(counter != size - 1)
            {
                cout << ", ";
            }
            counter++;
        }
        cout << "]" << endl << endl;

        //Coursework
        cout << "Coursework: " << " [";
        p = c->assessments["Coursework"];
        size = p.size();
        counter = 0;
        for(assessment* c: p)
        {
            cout << c->name;

            if(counter != size - 1)
            {
                cout << ", ";
            }
            counter++;
        }
        cout << "]" << endl << endl;

        //Exams
        cout << "Exams: " << " [";
        p = c->assessments["Exams"];
        size = p.size();
        counter = 0;
        for(assessment* c: p)
        {
            cout << c->name;

            if(counter != size - 1)
            {
                cout << ", ";
            }
            counter++;
        }
        cout << "]" << endl << endl;
    }

    cout << endl;

    cout << "Degrees:" << endl;
    for(degreeObj *dg : degrees)
    {
        cout << "Name: " << dg->name << endl;
        cout << "\tStart: " << dg->start << " | ";
        cout << "End: " << dg->end << " | ";

        //Course 1
        cout << "\tCourse 1: ";
        cout << dg->course1->name << endl;

        //Course 2
        cout << "\tCourse 2: ";
        cout << dg->course2->name << endl;
    }

    cout << endl;

    cout << "Students:" << endl;
    for(studentObj *st : students)
    {
        cout << "Name: " << st->firstname << " " << st->surname << endl;

        //Courses
        cout << "\tCourses: [";
        vector<degreeObj*> stVect = st->studentDegrees;
        size = stVect.size();
        counter = 0;

        for(degreeObj* degree: st->studentDegrees)
        {
            cout << degree->name;

            if(counter != size - 1)
            {
                cout << ", ";
            }
            counter++;
        }
        cout << "]" << endl << endl;
    }

    cout << endl;

    cout << "Grade Letters:" << endl;
    for(gradeLetter *gl : gradeLetters)
    {
        cout << "Letter: " << gl->letter << endl;

        cout << "Min: " << gl->min << endl;

        cout << "Max: " << gl->max << endl;
    }

    cout << endl;

}

void hope_vars::updateVar(string type)
{
    if (type == "assessment")
    {
        assessmentCSV->write(toCSV(assessmentCSV->getResult(), type, assessments.size()));
    }
    else if (type == "course")
    {
        courseCSV->write(toCSV(courseCSV->getResult(), type, courses.size()));
    }
    else if (type == "degree")
    {
        degreeCSV->write(toCSV(degreeCSV->getResult(), type, degrees.size()));
    }
    else if (type == "student")
    {
        studentCSV->write(toCSV(studentCSV->getResult(), type, students.size()));
    }
    else if (type == "studentMark")
    {
        studentMarkCSV->write(toCSV(studentMarkCSV->getResult(), type, studentMarks.size()));
    }
    else if (type == "gradeLetter")
    {
        gradeLetterCSV->write(toCSV(gradeLetterCSV->getResult(), type, gradeLetters.size()));
    }
    else
    {
        cout << "Could not update variables." << endl;
    }
}


void hope_vars::hopeWxGrid(wxGrid *grid, string type)
{
    // Create a wxGrid object
    grid->SetRowLabelSize(0);

    if(type == "student")
    {
        int rows = students.size();
        
        grid->CreateGrid(rows, 6);
        
        grid->SetColLabelValue(0, "ID");
        grid->SetColLabelValue(1, "Firstname");
        grid->SetColLabelValue(2, "Surname");
        grid->SetColLabelValue(3, "Degrees");
        grid->SetColLabelValue(4, "View Marks");
        grid->SetColLabelValue(5, "Generate Transcript");

        if(rows == 0)
        {
            cout << "Nothing in output";
            return;
        }

        for(int r = 0; r < rows; r++)
        {
            grid->SetCellValue(r, 0, to_string(students[r]->id));
            grid->SetCellValue(r, 1, students[r]->firstname);
            grid->SetCellValue(r, 2, students[r]->surname);

            vector<variant<int, string, float>> d_strings;

            for(degreeObj *dg : students[r]->studentDegrees)
            {
                d_strings.push_back(dg->name);
            }

            grid->SetCellValue(r, 3, stringifyVect(d_strings));

            grid->SetCellHighlightPenWidth(2);
            grid->SetCellValue(r, 4, wxT("view"));
            grid->SetCellBackgroundColour(r, 4, *wxGREEN);
            grid->SetCellTextColour(r, 4, *wxWHITE);
            grid->SetCellAlignment(r, 4, wxALIGN_CENTRE, wxALIGN_CENTRE);

            grid->SetCellValue(r, 5, wxT("generate"));
            grid->SetCellBackgroundColour(r, 5, *wxBLUE);
            grid->SetCellTextColour(r, 5, *wxWHITE);
            grid->SetCellAlignment(r, 5, wxALIGN_CENTRE, wxALIGN_CENTRE);

        }
        
    }
    else if(type == "course")
    {
        int rows = courses.size();

        grid->CreateGrid(rows, 6);
        
        grid->SetColLabelValue(0, "Name");
        grid->SetColLabelValue(1, "Level");
        grid->SetColLabelValue(2, "Portfolios");
        grid->SetColLabelValue(3, "Coursework");
        grid->SetColLabelValue(4, "Exams");
        grid->SetColLabelValue(5, "View Assessments");

        if(rows == 0)
        {
            cout << "Nothing in output";
            return;
        }
        
        for(int r = 0; r < rows; r++)
        {
            grid->SetCellValue(r, 0, courses[r]->name);
            grid->SetCellValue(r, 1, courses[r]->level);

            vector<variant<int, string, float>> a_strings;

            for(assessment *as : courses[r]->assessments["Portfolios"])
            {
                a_strings.push_back(as->name);
            }

            grid->SetCellValue(r, 3, stringifyVect(a_strings));

            a_strings = {};

            for(assessment *as : courses[r]->assessments["Coursework"])
            {
                a_strings.push_back(as->name);
            }

            grid->SetCellValue(r, 2, stringifyVect(a_strings));

            a_strings = {};

            for(assessment *as : courses[r]->assessments["Exams"])
            {
                a_strings.push_back(as->name);
            }

            grid->SetCellValue(r, 4, stringifyVect(a_strings));

            grid->SetCellHighlightPenWidth(2);
            grid->SetCellValue(r, 5, wxT("view"));
            grid->SetCellBackgroundColour(r, 5, *wxGREEN);
            grid->SetCellTextColour(r, 5, *wxWHITE);
            grid->SetCellAlignment(r, 5, wxALIGN_CENTRE, wxALIGN_CENTRE);

        }
        
    }
    else if(type == "degree")
    {
        int rows = degrees.size();

        grid->CreateGrid(rows, 5);
        
        grid->SetColLabelValue(0, "Name");
        grid->SetColLabelValue(1, "Start Date");
        grid->SetColLabelValue(2, "End Date");
        grid->SetColLabelValue(3, "Course 1");
        grid->SetColLabelValue(4, "Course 2");

        if(rows == 0)
        {
            cout << "Nothing in output";
            return;
        }
        
        for(int r = 0; r < rows; r++)
        {
            grid->SetCellValue(r, 0, degrees[r]->name);
            grid->SetCellValue(r, 1, degrees[r]->start);
            grid->SetCellValue(r, 2, degrees[r]->end);
            grid->SetCellValue(r, 3, degrees[r]->course1->name);
            grid->SetCellValue(r, 4, degrees[r]->course2->name);

        }        
    }

    grid->AutoSize();
}