// Creating main menu to display in main program
#include <degree.h>

wxBEGIN_EVENT_TABLE(degree, wxPanel)
    EVT_BUTTON(ID_C_DEGREE, degree::OnCreateDegree)
    EVT_GRID_CELL_LEFT_CLICK(degree::OnUpdateDegree)
    EVT_GRID_CELL_LEFT_DCLICK(degree::OnUpdateDegree)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(createDegreeDialog, wxDialog)
    EVT_BUTTON(ID_CLOSE_DEGREE_DLG, createDegreeDialog::closeDialog)
    EVT_BUTTON(ID_ADD_DEGREE, createDegreeDialog::addDegree)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(updateDegreeDialog, wxDialog)
    EVT_BUTTON(ID_UPDATE_DEGREE, updateDegreeDialog::updateDegree)
wxEND_EVENT_TABLE()

degree::degree(wxWindow *parent, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, ID_M_DEGREE_PANEL, pos, size, style, name)
{
    wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);
    this->SetBackgroundColour(*wxRED);

    newDegree = new wxButton(this, ID_C_DEGREE, "New Degree");

    grid = new wxGrid(this, -1);

    env_hope_vars->hopeWxGrid(grid, "degree");

    wxFont *font = new wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxStaticText *title = new wxStaticText(this, -1, "Degrees");
    title->SetFont(*font);
    box->Add(title, 0, wxLEFT, 5);
    box->AddSpacer(10);
    box->Add(newDegree, 0, wxLEFT, 5);
    box->AddSpacer(20);
    box->Add(grid, 0, wxEXPAND | wxLEFT, 5);

    SetSizer(box);
    
    this->Fit();
}

degree::~degree(){}

createDegreeDialog::createDegreeDialog(const wxString& title) : wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    env_hope_vars->printhope_vars();
    wxPanel *p_dialog = new wxPanel(this, -1);

    box_v = new wxBoxSizer(wxVERTICAL);

    box_v->AddSpacer(border_dlg);

    wxBoxSizer *degree_h = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *course_h = new wxBoxSizer(wxHORIZONTAL);

    //degree details static box and content
    wxStaticBox *degreeBox = new wxStaticBox(p_dialog, -1, wxT("Degree Details"));
    
    wxStaticBoxSizer *degreeStaticBoxSizer = new wxStaticBoxSizer(degreeBox, wxVERTICAL);
    wxBoxSizer *degreeNameSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *degreeNameLabel = new wxStaticText(p_dialog, -1, wxT("Name: "));

    degreeName = new wxTextCtrl(p_dialog, -1, wxT(""));
    
    degreeNameSizer->Add(degreeNameLabel);
    degreeNameSizer->AddSpacer(border_dlg*1.8);
    degreeNameSizer->Add(degreeName);

    wxBoxSizer *datesSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *startLabel = new wxStaticText(p_dialog, -1, wxT("Start Date: "));

    start = new wxDatePickerCtrl(p_dialog, -1);

    wxStaticText *endLabel = new wxStaticText(p_dialog, -1, wxT("End Date: "));

    end = new wxDatePickerCtrl(p_dialog, -1);

    datesSizer->Add(startLabel);
    datesSizer->Add(start);
    datesSizer->AddSpacer(20);
    datesSizer->Add(endLabel);
    datesSizer->Add(end);

    degreeStaticBoxSizer->Add(degreeNameSizer);
    degreeStaticBoxSizer->AddSpacer(border_dlg);
    degreeStaticBoxSizer->Add(datesSizer);

    degree_h->Add(degreeStaticBoxSizer, 0, 0, border_dlg);

    //courses static box
    wxArrayString courses;

    for(courseObj *c : env_hope_vars->courses)
    {
        courses.Add(c->name);
    }

    wxStaticBox *course1Box = new wxStaticBox(p_dialog, -1, wxT("Courses"));

    wxStaticBoxSizer *coursesStaticBoxSizer = new wxStaticBoxSizer(course1Box, wxVERTICAL);

    wxBoxSizer *course1Sizer = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *course2Sizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *course1Label = new wxStaticText(p_dialog, -1, wxT("Course 1: "));
    course1Dropdown = new wxComboBox(p_dialog, -1, "Select Course", wxDefaultPosition, wxDefaultSize, courses, wxCB_READONLY);
    
    wxStaticText *course2Label = new wxStaticText(p_dialog, -1, wxT("Course 2: "));
    course2Dropdown = new wxComboBox(p_dialog, -1, "Select Course", wxDefaultPosition, wxDefaultSize, courses, wxCB_READONLY);

    course1Sizer->Add(course1Label);
    course1Sizer->AddSpacer(border_dlg);
    course1Sizer->Add(course1Dropdown);

    course2Sizer->Add(course2Label);
    course2Sizer->AddSpacer(border_dlg);
    course2Sizer->Add(course2Dropdown);
    
    coursesStaticBoxSizer->Add(course1Sizer);
    coursesStaticBoxSizer->AddSpacer(2*border_dlg);
    coursesStaticBoxSizer->Add(course2Sizer);

    course_h->Add(coursesStaticBoxSizer, 0, 0, border_dlg);

    //horizontal box sizer

    //vertical box sizer
    box_v->Add(degree_h, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
    box_v->AddSpacer(2*border_dlg);
    box_v->Add(course_h, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

    wxBoxSizer *btnSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *add = new wxButton(p_dialog, ID_ADD_DEGREE, wxT("Add"));
    add->SetBackgroundColour(*wxRED);
    add->SetForegroundColour(*wxWHITE);

    wxButton *cancel = new wxButton(p_dialog, ID_CLOSE_DEGREE_DLG, wxT("Cancel"));
    cancel->SetBackgroundColour(*wxRED);
    cancel->SetForegroundColour(*wxWHITE);

    btnSizer->Add(add);
    btnSizer->AddSpacer(border_dlg);
    btnSizer->Add(cancel);
    
    box_v->AddSpacer(20);
    box_v->Add(btnSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg/2);
    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

createDegreeDialog::~createDegreeDialog(){};

void createDegreeDialog::closeDialog(wxCommandEvent& event)
{
    Close();
}

void createDegreeDialog::addDegree(wxCommandEvent& event)
{
    string n = degreeName->GetValue().ToStdString();

    string s = regex_replace(start->GetValue().FormatISODate().ToStdString(), regex("/"), "-");
    string e = regex_replace(end->GetValue().FormatISODate().ToStdString(), regex("/"), "-");

    if(n == "" || s == "" || e == "")
    {
        wxMessageBox("All fields must be complete.");
        return;
    }

    courseObj *c1 = nullptr;
    courseObj *c2 = nullptr;

    string temp = course1Dropdown->GetValue().ToStdString();

    for(courseObj *c: env_hope_vars->courses)
    {
        if(temp == c->name)
        {
            c1 = c;
            break;
        }
    }

    temp = course2Dropdown->GetValue().ToStdString();

    for(courseObj *c: env_hope_vars->courses)
    {
        if(temp == c->name)
        {
            c2 = c;
            break;
        }
    }

    if(c1 == nullptr || c2 == nullptr)
    {
        wxMessageBox("All fields must be complete.");
        return;
    }

    env_hope_vars->degrees.push_back(new degreeObj(n, s, e, c1, c2));
    env_hope_vars->printhope_vars();
    env_hope_vars->updateVar("degree");
    
    Close();
    
    wxMessageBox("Reopen 'Manage Degrees' to view changes.");

    
}

void degree::OnCreateDegree(wxCommandEvent& event)
{
    //Create window displaying degree management frame
    createDegreeDialog *dlg = new createDegreeDialog("Create Degree");
    event.Skip();
}

void degree::OnUpdateDegree(wxGridEvent& event)
{
    //Create window displaying student management frame

    wxString title = "Update " + grid->GetColLabelValue(event.GetCol()).ToStdString() + " field";

    string degreeName = grid->GetCellValue(event.GetRow(), 0).ToStdString();
    
    updateDegreeDialog *update = new updateDegreeDialog(title, event, grid, degreeName);
    event.Skip();
}

//update degree
updateDegreeDialog::updateDegreeDialog(const wxString&  title, wxGridEvent cell, wxGrid *grid, string degreeName): wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    env_hope_vars->printhope_vars();

    wxPanel *p_dialog = new wxPanel(this, -1);
    
    cellSelected = &cell;
    colSelected = cellSelected->GetCol();

    name = degreeName;

    box_v = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *box_h = new wxBoxSizer(wxHORIZONTAL);
    
    string originalVal = grid->GetCellValue(cellSelected->GetRow(), cellSelected->GetCol()).ToStdString();

    wxStaticText *inputLbl = new wxStaticText(p_dialog, -1, wxT("Enter New Value:"));
    
    box_h->Add(inputLbl);
    box_h->AddSpacer(border_dlg);

    switch(colSelected)
    {
        case 0:
            input = new wxTextCtrl(p_dialog, -1, originalVal);

            box_h->Add(input);
            break;
        case 1:
        case 2:
            struct tm tm;

            get_time(&tm, "%Y-%m-%d");

            date = new wxDatePickerCtrl(p_dialog, -1, wxDateTime(mktime(&tm)));

            box_h->Add(date);
            break;
        case 3:
        case 4:
            wxArrayString courses;

            for(courseObj *c : env_hope_vars->courses)
            {
                courses.Add(c->name);
            }

            courseSelect = new wxComboBox(p_dialog, -1, "Select Course", wxDefaultPosition, wxDefaultSize, courses, wxCB_READONLY);

            box_h->Add(courseSelect);
            break;
    }

    box_v->Add(box_h, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
    
    wxButton *confirmUpdate = new wxButton(p_dialog, ID_UPDATE_DEGREE, wxT("Update"));
    confirmUpdate->SetBackgroundColour(*wxBLUE);
    confirmUpdate->SetForegroundColour(*wxWHITE);

    box_v->Add(confirmUpdate, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

updateDegreeDialog::~updateDegreeDialog(){}

void updateDegreeDialog::updateDegree(wxCommandEvent& event)
{
    for(degreeObj *dg : env_hope_vars->degrees)
    {
        if(dg->name == name)
        {
            switch(colSelected)
            {
                case 0:
                    dg->name = input->GetValue().ToStdString();
                    break;
                case 1:
                case 2:
                    dg->start = regex_replace(date->GetValue().FormatISODate().ToStdString(), regex("/"), "-");
                    break;
                case 3:
                    for(courseObj * c: env_hope_vars->courses)
                    {
                        if(c->name == courseSelect->GetValue().ToStdString())
                        {
                            dg->course1 = c;
                            break;
                        }
                    }
                    break;
                case 4:
                    for(courseObj * c: env_hope_vars->courses)
                    {
                        if(c->name == courseSelect->GetValue().ToStdString())
                        {
                            dg->course2 = c;
                            break;
                        }
                    }
                    break;
            }
        } 
    }

    env_hope_vars->updateVar("degree");

    wxMessageBox("Reopen 'Manage Degrees' to view changes.");
    
    Close();
}