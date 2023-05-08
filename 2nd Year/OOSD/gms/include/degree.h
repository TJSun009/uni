#pragma once

#include "csv.h"
#include <wx/datectrl.h>
#include <enums.h>

class degree : public wxPanel
{
    public:
        degree(wxWindow *parent, const wxPoint& pos, const wxSize& size, long style, const wxString& name);
        ~degree();
        
    private:
        wxButton *newDegree = nullptr;
        wxGrid *grid;
        void OnCreateDegree(wxCommandEvent& event);
        void OnUpdateDegree(wxGridEvent& event);
        wxDECLARE_EVENT_TABLE();
};

class createDegreeDialog : public wxDialog
{
    public:
        createDegreeDialog(const wxString& title);
        ~createDegreeDialog();
    private:
        wxTextCtrl *degreeName;
        wxDatePickerCtrl *start;
        wxDatePickerCtrl *end;

        wxComboBox *course1Dropdown;
        wxTextCtrl *course1New;

        wxComboBox *course2Dropdown;
        wxTextCtrl *course2New;
        wxBoxSizer *box_v;

        int border_dlg = 10;

        void closeDialog(wxCommandEvent& event);
        void addDegree(wxCommandEvent& event);

        wxDECLARE_EVENT_TABLE();
};

class updateDegreeDialog : public wxDialog
{
    public:
        updateDegreeDialog(const wxString& title, wxGridEvent cellSelected, wxGrid *grid, string degreeName);
        ~updateDegreeDialog();
    private:
        wxBoxSizer *box_v;
        wxGridEvent *cellSelected;
        int border_dlg = 10;
        wxTextCtrl *input;
        wxDatePickerCtrl *date;
        wxComboBox *courseSelect;
        string name;
        int colSelected;

        void updateDegree(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
};