#pragma once

#include "csv.h"
#include <enums.h>

class student : public wxPanel
{ 
    public:
        student(wxWindow *parent, const wxPoint& pos, const wxSize& size, long style, const wxString& name);
        ~student();
        
    private:
        wxButton *newStudent = nullptr;
        int id;
        wxGrid * grid;
        wxBoxSizer * box_hm = nullptr;
        wxBoxSizer * box_v = nullptr;
        wxBoxSizer * box_v1 = nullptr;
        wxBoxSizer * box_v2 = nullptr;
        int border_dlg = 10;
        wxDialog *temp;
        int concessions = 7000;
        bool checked;
        
        wxArrayPtrVoid concession;

        void OnCreateStudent(wxCommandEvent& event);
        void OnUpdateStudent(wxCommandEvent& event);
        void OnClickGrid(wxGridEvent& event);
        void OnSecondAttempt(wxCommandEvent& event);

        void viewTranscript();

        string getGrade(float f)
        {
            for(gradeLetter *gl : env_hope_vars->gradeLetters)
            {
                if(f >= gl->min && f < gl->max)
                {
                    return gl->letter;
                }
            }

            return "Out of range/ None provided";
        }
        void getWeights(float arr[3], string l)
        {
            switch(l[0])
            {
                case 'C':
                    arr[0] = 0.34;
                    arr[1] = 0.33;
                    arr[2] = 0.33;
                    break;
                case 'I':
                    arr[0] = 0.50;
                    arr[1] = 0.25;
                    arr[2] = 0.25;
                    break;
                case 'H':
                    arr[0] = 0.67;
                    arr[1] = 0;
                    arr[2] = 0.33;
                break;
            }
        }
        wxDECLARE_EVENT_TABLE();
    
};

class createStudentDialog : public wxDialog
{
    public:
        createStudentDialog(const wxString& title);
        ~createStudentDialog();
    private:
        wxTextCtrl *studentFirstname;
        wxTextCtrl *studentSurname;
        wxTextCtrl *studentId;
        wxCheckListBox *studentCourses;

        wxFilePickerCtrl *studentFile;
        wxBoxSizer *box_v;

        int border_dlg = 10;

        wxArrayString getDegrees()
        {
            //display courses

            wxArrayString degree;

            for(degreeObj *d : env_hope_vars->degrees)
            {
                degree.Add(d->name);
            }

            if(degree.size() == 0)
            {
                cout << "could not find any courses/degrees" << endl;
            }

            return degree;
        }

        void closeDialog(wxCommandEvent& event);
        void addStudent(wxCommandEvent& event);
        void OnUploadStudent(wxCommandEvent& event);

        wxDECLARE_EVENT_TABLE();
};

class viewMarksDialog : public wxDialog
{
    public:
        viewMarksDialog(const wxString& title, int id);
        ~viewMarksDialog();
    private:
        wxBoxSizer *box_v;

        int id;

        int border_dlg = 10;

        void closeDialog(wxCommandEvent& event);
        void editMarks(wxListEvent& event);
        
        wxDECLARE_EVENT_TABLE();
};

class editMarksDialog : public wxDialog
{
    public:
        editMarksDialog(const wxString& title, wxListItem rowSelected, int id);
        ~editMarksDialog();
    private:
        wxBoxSizer *box_v;
        int id;
        wxListItem rowSelected;
        int border_dlg = 10;
        wxSpinCtrl *marksInput;

        void updateMarks(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
};

class updateStudentDialog : public wxDialog
{
    public:
        updateStudentDialog(const wxString& title, wxGridEvent cellSelected, wxGrid *grid, string f, string s);
        ~updateStudentDialog();
    private:
        wxBoxSizer *box_v;
        wxGridEvent *cellSelected;
        int border_dlg = 10;
        wxTextCtrl *input;
        string firstname;
        string surname;
        int colSelected;
        wxCheckListBox *studentCourses;

        wxArrayString getDegrees()
        {
            //display courses
            cout << "displaying courses..." << endl;

            wxArrayString degree;

            for(degreeObj *d : env_hope_vars->degrees)
            {
                degree.Add(d->name);
            }

            if(degree.size() == 0)
            {
                cout << "could not find any courses/degrees" << endl;
            }

            return degree;
        }

        void updateStudent(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
};