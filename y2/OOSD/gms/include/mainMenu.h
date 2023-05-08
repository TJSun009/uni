#include <wx/wx.h>
#include<degree.h>
#include<student.h>
#include<course.h>

class mainMenu : public wxFrame
{
    public:
        mainMenu(const wxString& title, const wxPoint& pos, const wxSize& size);
        ~mainMenu();
    
    private:
        wxMenu * options = nullptr;
        wxBoxSizer * m_sizer = new wxBoxSizer(wxVERTICAL);
        wxPanel * m_panel = new wxPanel(this, -1);
        wxMenuBar * m_MenuBar = nullptr;
        
        void OnDegree(wxCommandEvent& event);
        void OnStudent(wxCommandEvent& event);
        void OnCourse(wxCommandEvent& event);
        void OnGrade(wxCommandEvent& event);
        void OnHelp(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnResize(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
};

class viewGradeLettersDialog : public wxDialog
{
    public:
        viewGradeLettersDialog(const wxString& title);
        ~viewGradeLettersDialog();
    private:
        wxBoxSizer *box_v;

        int border_dlg = 10;

        void closeDialog(wxCommandEvent& event);
        void editGradeLetters(wxListEvent& event);
        wxDECLARE_EVENT_TABLE();
};

class editGradeLettersDialog : public wxDialog
{
    public:
        editGradeLettersDialog(const wxString& title, wxListItem rowSelected, wxListEvent event);
        ~editGradeLettersDialog();
    private:
        wxBoxSizer *box_v;
        wxListItem rowSelected;
        int colSelected;
        int border_dlg = 10;
        wxTextCtrl *name;
        wxSpinCtrlDouble *min;
        wxSpinCtrlDouble *max;

        void updateGradeLetters(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
};