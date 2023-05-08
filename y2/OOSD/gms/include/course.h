#pragma once

#include "csv.h"
#include <enums.h>
#include <wx/datectrl.h>

class course : public wxPanel
{ 
    public:
        course(wxWindow *parent, const wxPoint& pos, const wxSize& size, long style, const wxString& name);
        ~course();
        
    private:
        wxButton *newCourse = nullptr;
        int id;
        wxGrid * grid;
        void OnCreateCourse(wxCommandEvent& event);
        void OnUpdateCourse(wxCommandEvent& event);
        void OnClickGrid(wxGridEvent& event);
        wxDECLARE_EVENT_TABLE();
    
};

class createCourseDialog : public wxDialog
{
    public:
        createCourseDialog(const wxString& title);
        ~createCourseDialog();
    private:
        wxTextCtrl *courseName;
        wxComboBox *courseLevel;
        wxListCtrl *portfolios;
        wxListCtrl *coursework;
        wxListCtrl *exams;
        
        wxDialog *temp;
        wxTextCtrl *a_Name;
        wxSpinCtrlDouble *a_Weight;
        wxDatePickerCtrl *a_Deadline;
        wxButton *confirmEdit;

        string type;

        long index = 0;
        wxBoxSizer *box_v;

        int border_dlg = 10;

        void closeDialog(wxCommandEvent& event);
        void addCourse(wxCommandEvent& event);
        void addAssessment(wxListEvent & event);
        void insertAssessment(wxCommandEvent & event);

        wxDECLARE_EVENT_TABLE();
};

class viewAssessmentsDialog : public wxDialog
{
    public:
        viewAssessmentsDialog(const wxString& title, string courseName);
        ~viewAssessmentsDialog();
    private:
        wxBoxSizer *box_v;

        string courseName;

        int border_dlg = 10;

        void closeDialog(wxCommandEvent& event);
        void editAssessments(wxListEvent& event);
        wxDECLARE_EVENT_TABLE();
};

class editAssessmentsDialog : public wxDialog
{
    public:
        editAssessmentsDialog(const wxString& title, wxListItem rowSelected, wxListEvent event, string courseName);
        ~editAssessmentsDialog();
    private:
        wxBoxSizer *box_v;
        string courseName;
        wxListItem rowSelected;
        int colSelected;
        int border_dlg = 10;
        wxTextCtrl *name;
        wxDatePickerCtrl *date = nullptr;
        wxSpinCtrlDouble *weightInput;

        void updateAssessment(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
};

class updateCourseDialog : public wxDialog
{
    public:
        updateCourseDialog(const wxString& title, wxGridEvent cellSelected, wxGrid *grid);
        ~updateCourseDialog();
    private:
        wxBoxSizer *box_v;
        wxGridEvent *cellSelected;
        int border_dlg = 10;
        wxTextCtrl *courseName;
        wxComboBox *courseLevel;
        int colSelected;
        string course;

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

        void updateCourse(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
};