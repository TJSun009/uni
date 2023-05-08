// Creating main menu to display in main program
#include <course.h>

wxBEGIN_EVENT_TABLE(course, wxPanel)
    EVT_BUTTON(ID_C_COURSE, course::OnCreateCourse)
    EVT_BUTTON(ID_U_COURSE, course::OnUpdateCourse)
    EVT_GRID_CELL_LEFT_CLICK(course::OnClickGrid)
    EVT_GRID_CELL_LEFT_DCLICK(course::OnClickGrid)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(createCourseDialog, wxDialog)
    EVT_BUTTON(ID_CLOSE_COURSE_DLG, createCourseDialog::closeDialog)
    EVT_BUTTON(ID_ADD_COURSE, createCourseDialog::addCourse)
    EVT_LIST_COL_CLICK(wxID_ANY, createCourseDialog::addAssessment)
    EVT_BUTTON(ID_INSERT_ASSESSMENT, createCourseDialog::insertAssessment)
    EVT_BUTTON(ID_ADD_COURSE, createCourseDialog::addCourse)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(viewAssessmentsDialog, wxDialog)
    EVT_LIST_ITEM_ACTIVATED(ID_UPDATE_ASSESSMENTS, viewAssessmentsDialog::editAssessments)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(editAssessmentsDialog, wxDialog)
    EVT_BUTTON(ID_EDIT_ASSESSMENTS, editAssessmentsDialog::updateAssessment)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(updateCourseDialog, wxDialog)
    EVT_BUTTON(ID_UPDATE_COURSE, updateCourseDialog::updateCourse)
wxEND_EVENT_TABLE()

//display course info
course::course(wxWindow *parent, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, ID_M_COURSE_PANEL, pos, size, style, name)
{
    wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);
    this->SetBackgroundColour(*wxRED);

    newCourse = new wxButton(this, ID_C_COURSE, "New Course");

    grid = new wxGrid(this, -1);

    env_hope_vars->hopeWxGrid(grid, "course");

    wxFont *font = new wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxStaticText *title = new wxStaticText(this, -1, "Courses");
    title->SetFont(*font);
    box->Add(title, 0, wxLEFT, 5);
    box->AddSpacer(10);
    box->Add(newCourse, 0, wxLEFT, 5);
    box->AddSpacer(20);
    box->Add(grid, 0, wxLEFT | wxEXPAND, 5);

    SetSizer(box);

    this->Fit();
}

course::~course(){}

void course::OnCreateCourse(wxCommandEvent& event)
{
    //Create window displaying course management frame
    createCourseDialog *dlg = new createCourseDialog("Create Course");
    event.Skip();
}

void course::OnUpdateCourse(wxCommandEvent& event)
{
    //Create window displaying course management frame
    wxMessageBox("Updating Course");
    event.Skip();
}

void course::OnClickGrid(wxGridEvent& event)
{
    //Create window displaying course management frame
    int column = event.GetCol();
    int row = event.GetRow();
    string value = grid->GetCellValue(row, column).ToStdString();

    if(value == "view")
    {
        string courseName = grid->GetCellValue(event.GetRow(), 0).ToStdString();
        viewAssessmentsDialog *view = new viewAssessmentsDialog("View Courses", courseName);
    }
    else
    {
        if(event.GetCol() > 1)
        {
            return;
        }

        wxString title = "Update " + grid->GetColLabelValue(column).ToStdString() + " field";

        string firstname = grid->GetCellValue(row, 1).ToStdString();

        string surname = grid->GetCellValue(row, 2).ToStdString();

        updateCourseDialog *update = new updateCourseDialog(title, event, grid);
    }
    
    event.Skip();
}

//display dialog for creating courses
createCourseDialog::createCourseDialog(const wxString& title) : wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    env_hope_vars->printhope_vars();

    wxPanel *p_dialog = new wxPanel(this, -1);

    box_v = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *coursenameSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *coursenameLabel = new wxStaticText(p_dialog, -1, wxT("Course Name: "));

    courseName = new wxTextCtrl(p_dialog, -1, wxT(""));
    
    coursenameSizer->Add(coursenameLabel);
    coursenameSizer->AddSpacer(border_dlg);
    coursenameSizer->Add(courseName);

    wxBoxSizer *levelSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *levelLabel = new wxStaticText(p_dialog, -1, wxT("Level: "));

    char temp[3] = {'C', 'I', 'H'};

    wxArrayString levels;

    for(char c : temp)
    {
        levels.Add(c);
    }

    courseLevel = new wxComboBox(p_dialog, -1, "", wxDefaultPosition, wxDefaultSize, levels, wxCB_READONLY);

    levelSizer->Add(levelLabel);
    levelSizer->AddSpacer(border_dlg*0.8);
    levelSizer->Add(courseLevel);

    box_v->Add(coursenameSizer);
    box_v->AddSpacer(border_dlg);
    box_v->Add(levelSizer);
    box_v->AddSpacer(border_dlg);
    box_v->Add(new wxStaticText(p_dialog, -1, wxT("Add Assessments:")));
    box_v->AddSpacer(border_dlg);

    box_v->Add(new wxStaticText(p_dialog, -1, wxT("Portfolios"), wxDefaultPosition, wxDefaultSize, wxFONTWEIGHT_BOLD));

    box_v->AddSpacer(border_dlg);

    portfolios = new wxListCtrl(p_dialog, P_ASSESSMENTS, wxDefaultPosition, wxDefaultSize, wxLC_VRULES | wxLC_REPORT);

    portfolios->InsertColumn(0, wxT("Name"));
    portfolios->InsertColumn(1, wxT("Weighting"));
    portfolios->InsertColumn(2, wxT("Deadline"));
    portfolios->InsertColumn(3, wxT("Add"));

    box_v->Add(portfolios);

    box_v->Add(new wxStaticText(p_dialog, -1, wxT("Coursework"), wxDefaultPosition, wxDefaultSize, wxFONTWEIGHT_BOLD));

    box_v->AddSpacer(border_dlg);

    coursework = new wxListCtrl(p_dialog, C_ASSESSMENTS, wxDefaultPosition, wxDefaultSize, wxLC_VRULES | wxLC_REPORT);

    coursework->InsertColumn(0, wxT("Name"));
    coursework->InsertColumn(1, wxT("Weighting"));
    coursework->InsertColumn(2, wxT("Deadline"));
    coursework->InsertColumn(3, wxT("Add"));

    box_v->Add(coursework);

    box_v->Add(new wxStaticText(p_dialog, -1, wxT("Exams"), wxDefaultPosition, wxDefaultSize, wxFONTWEIGHT_BOLD));

    box_v->AddSpacer(border_dlg);

    exams = new wxListCtrl(p_dialog, E_ASSESSMENTS, wxDefaultPosition, wxDefaultSize, wxLC_VRULES | wxLC_REPORT);

    exams->InsertColumn(0, wxT("Name"));
    exams->InsertColumn(1, wxT("Weighting"));
    exams->InsertColumn(2, wxT("Deadline"));
    exams->InsertColumn(3, wxT("Add"));

    box_v->Add(exams);
    
    wxButton *add = new wxButton(p_dialog, ID_ADD_COURSE, wxT("Add"));
    add->SetBackgroundColour(*wxRED);
    add->SetForegroundColour(*wxWHITE);

    box_v->Add(add, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

    //vertical box sizer
    box_v->AddSpacer(border_dlg);
    
    wxButton *cancel = new wxButton(p_dialog, ID_CLOSE_DEGREE_DLG, wxT("Cancel"));
    cancel->SetBackgroundColour(*wxRED);
    cancel->SetForegroundColour(*wxWHITE);
    
    box_v->Add(cancel, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

createCourseDialog::~createCourseDialog(){}

void createCourseDialog::closeDialog(wxCommandEvent& event)
{
    Close();
}

void createCourseDialog::addCourse(wxCommandEvent& event)
{
    string n = courseName->GetValue().ToStdString();
    string l = courseLevel->GetValue().ToStdString();

    if(n == "" || l == "")
    {
        wxMessageBox("All fields must be complete.");
        return;
    }

    float weightings[3];
    //weightings {C, P, E}

    switch(l[0])
    {
        case 'C':
            weightings[0] = 0.34;
            weightings[1] = 0.33;
            weightings[2] = 0.33;
            break;
        case 'I':
            weightings[0] = 0.50;
            weightings[1] = 0.25;
            weightings[2] = 0.25;
            break;
        case 'H':
            weightings[0] = 0.67;
            weightings[1] = 0;
            weightings[2] = 0.33;
        break;
    }

    vector<assessment*> c_portfolios;
    vector<assessment*> c_coursework;
    vector<assessment*> c_exams;
    
    long rows = portfolios->GetItemCount();
    
    float p_weights = 0;
    float c_weights = 0;
    float e_weights = 0;

    for(long r = 0; r < rows; r++)
    {
        p_weights += stof(portfolios->GetItemText(r, 1).ToStdString());
        c_weights += stof(portfolios->GetItemText(r, 2).ToStdString());
        e_weights += stof(portfolios->GetItemText(r, 3).ToStdString());
    }

    if(p_weights != weightings[0])
    {
        wxMessageBox("The portfolio weightings should add to " + to_string(weightings[0]));
        return;
    }
    else if(c_weights != weightings[1])
    {
        wxMessageBox("The coursework weightings should add to " + to_string(weightings[1]));
        return;
    }
    else if(e_weights != weightings[2])
    {
        wxMessageBox("The exam weightings should add to " + to_string(weightings[2]));;
        return;
    }

    for(long r = 0; r < rows; r++)
    {
        string a_name = portfolios->GetItemText(r, 0).ToStdString();
        float a_weights = stof(portfolios->GetItemText(r, 1).ToStdString());
        string a_deadline = portfolios->GetItemText(r, 2).ToStdString();
        assessment *as = new assessment(a_name, a_weights, a_deadline);
        env_hope_vars->assessments.push_back(as);
        c_portfolios.push_back(as);
        env_hope_vars->updateVar("assessment");
    }

    rows = coursework->GetItemCount();

    for(long r = 0; r < rows; r++)
    {
        string a_name = coursework->GetItemText(r, 0).ToStdString();
        float a_weights = stof(coursework->GetItemText(r, 1).ToStdString());
        string a_deadline = coursework->GetItemText(r, 2).ToStdString();
        assessment *as = new assessment(a_name, a_weights, a_deadline);
        env_hope_vars->assessments.push_back(as);
        c_coursework.push_back(as);
        env_hope_vars->updateVar("assessment");
    }

    rows = exams->GetItemCount();

    for(long r = 0; r < rows; r++)
    {
        string a_name = exams->GetItemText(r, 0).ToStdString();
        float a_weights = stof(exams->GetItemText(r, 1).ToStdString());
        string a_deadline = exams->GetItemText(r, 2).ToStdString();
        assessment *as = new assessment(a_name, a_weights, a_deadline);
        env_hope_vars->assessments.push_back(as);
        c_exams.push_back(as);
        env_hope_vars->updateVar("assessment");
    }
    
    
    env_hope_vars->courses.push_back(new courseObj(n, l, c_portfolios, c_coursework, c_exams));
    

    env_hope_vars->printhope_vars();
    env_hope_vars->updateVar("course");
    env_hope_vars->updateVar("courseMark");

    wxMessageBox("Reopen 'Manage Courses' to view changes.");

    Close();
}

void createCourseDialog::addAssessment(wxListEvent& event)
{
    if(event.GetColumn() == 3)
    {
        cout << event.GetId() << endl;

        if(event.GetId() == P_ASSESSMENTS)
        {
            type = "portfolio";
        }
        else if(event.GetId() == C_ASSESSMENTS)
        {
            type = "coursework";
        }
        else if(event.GetId() == E_ASSESSMENTS)
        {
            type = "exams";
        }

        temp = new wxDialog(NULL, -1, "Enter Assessment Details");

        wxPanel *x_panel = new wxPanel(temp);

        box_v = new wxBoxSizer(wxVERTICAL);

        box_v->AddSpacer(border_dlg/2);

        wxBoxSizer *box_h1 = new wxBoxSizer(wxHORIZONTAL);
        wxBoxSizer *box_h2 = new wxBoxSizer(wxHORIZONTAL);
        wxBoxSizer *box_h3 = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText *nameLbl = new wxStaticText(x_panel, -1, wxT("Enter Name:"));
        box_h2->Add(nameLbl);
        box_h2->AddSpacer(border_dlg);

        a_Name = new wxTextCtrl(x_panel, -1);
        box_h2->Add(a_Name);

        wxStaticText *weightLbl = new wxStaticText(x_panel, -1, wxT("Enter Weighting:"));
        box_h2->Add(weightLbl);
        box_h2->AddSpacer(border_dlg);

        a_Weight = new wxSpinCtrlDouble(x_panel, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 16384L, 0.00, 1.00, 0, 0.01);;

        box_h2->Add(a_Weight);

        //adapted from https://stackoverflow.com/questions/37306895/c-converting-a-string-to-a-time-t-variable - Steve Lorimer
        
        wxStaticText *dateLbl = new wxStaticText(x_panel, -1, wxT("Enter Deadline:"));
        
        box_h3->Add(dateLbl);
        box_h3->AddSpacer(border_dlg);

        a_Deadline = new wxDatePickerCtrl(x_panel, -1);
        box_h3->Add(a_Deadline);

        box_v->Add(box_h2, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
        box_v->AddSpacer(border_dlg);
        box_v->Add(box_h3, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

        box_v->AddSpacer(border_dlg/2);
        
        confirmEdit = new wxButton(x_panel, ID_INSERT_ASSESSMENT, wxT("Confirm"));
        confirmEdit->SetBackgroundColour(*wxYELLOW);
        confirmEdit->SetForegroundColour(*wxWHITE);

        box_v->Add(confirmEdit, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

        x_panel->SetSizer(box_v);
        x_panel->Fit();
        this->Fit();

        temp->ShowModal();
    }
    event.Skip();
}

void createCourseDialog::insertAssessment(wxCommandEvent& event)
{
    cout << "Inserting Assessment" << endl;
    string n = a_Name->GetValue().ToStdString();
    float w = a_Weight->GetValue();
    string d = a_Deadline->GetValue().FormatISODate().ToStdString();

    if(n == "" || w <= 0 || d == "")
    {
        wxMessageBox("All fields must be complete");
        return;
    }

    if(type == "portfolio")
    {
        index = portfolios->InsertItem(index, n);
        portfolios->SetItem(index, 0, n);
        portfolios->SetItem(index, 2, to_string(w));
        portfolios->SetItem(index, 3, d);
        index++;
    }
    else if(type == "coursework")
    {
        index = coursework->InsertItem(index, n);
        coursework->SetItem(index, 0, n);
        coursework->SetItem(index, 2, to_string(w));
        coursework->SetItem(index, 3, d);
        index++;
    }
    else if(type == "exams")
    {
        index = exams->InsertItem(index, n);
        exams->SetItem(index, 0, n);
        exams->SetItem(index, 2, to_string(w));
        exams->SetItem(index, 3, d);
        index++;
    }

    temp->Close();
    event.Skip();
}

//view assessments
viewAssessmentsDialog::viewAssessmentsDialog(const wxString& title, string courseName) : wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{

    env_hope_vars->printhope_vars();

    wxPanel *p_dialog = new wxPanel(this, -1);

    box_v = new wxBoxSizer(wxVERTICAL);
    box_v->AddSpacer(border_dlg);

    wxBoxSizer *box_v1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *box_v2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *box_v3 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *box_h = new wxBoxSizer(wxHORIZONTAL);
    
    wxFont *fontL = new wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxFont *fontM = new wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true);

    wxStaticText *asText = new wxStaticText(p_dialog, -1, courseName);
    
    asText->SetFont(*fontL);

    box_v->Add(asText, 0, wxLEFT, border_dlg);
    box_v->AddSpacer(border_dlg);

    map<string, vector<assessment*>> courseAssessments = env_hope_vars->findCourses(courseName).front()->assessments;
    
    //portfolios

    wxStaticText *pText = new wxStaticText(p_dialog, -1, "Portfolios", wxDefaultPosition, wxDefaultSize, wxFONTWEIGHT_BOLD);

    pText->SetFont(*fontM);

    box_v1->Add(pText);

    box_v1->AddSpacer(border_dlg);

    wxListCtrl *portfolioList = new wxListCtrl(p_dialog, ID_UPDATE_ASSESSMENTS, wxDefaultPosition, wxDefaultSize, wxLC_VRULES | wxLC_REPORT);

    portfolioList->InsertColumn(0, wxT("Name"));
    portfolioList->InsertColumn(1, wxT("Weighting"));
    portfolioList->InsertColumn(2, wxT("Deadline"));

    for(assessment * as : courseAssessments["Portfolios"])
    {
        long index = portfolioList->InsertItem(0, as->name);
        portfolioList->SetItem(index, 1, to_string(as->weighting));
        portfolioList->SetItem(index, 2, as->deadline);            
    }

    box_v1->Add(portfolioList, wxEXPAND | wxLEFT |wxRIGHT);
    box_v1->AddSpacer(border_dlg*2);


    //coursework

    wxStaticText *cText = new wxStaticText(p_dialog, -1, "Coursework", wxDefaultPosition, wxDefaultSize, wxFONTWEIGHT_BOLD);

    cText->SetFont(*fontM);

    box_v2->Add(cText);

    box_v2->AddSpacer(border_dlg);

    wxListCtrl *courseworkList = new wxListCtrl(p_dialog, ID_UPDATE_ASSESSMENTS, wxDefaultPosition, wxDefaultSize, wxLC_VRULES | wxLC_REPORT);

    courseworkList->InsertColumn(0, wxT("Name"));
    courseworkList->InsertColumn(1, wxT("Weighting"));
    courseworkList->InsertColumn(2, wxT("Deadline"));

    for(assessment * as : courseAssessments["Coursework"])
    {
        long index = courseworkList->InsertItem(0, as->name);
        courseworkList->SetItem(index, 1, to_string(as->weighting));
        courseworkList->SetItem(index, 2, as->deadline);            
    }

    box_v2->Add(courseworkList, wxEXPAND | wxLEFT |wxRIGHT);
    box_v2->AddSpacer(border_dlg*2);

    //exams

    wxStaticText *eText = new wxStaticText(p_dialog, -1, "Exams", wxDefaultPosition, wxDefaultSize, wxFONTWEIGHT_BOLD);

    eText->SetFont(*fontM);

    box_v3->Add(eText);

    box_v3->AddSpacer(border_dlg);

    wxListCtrl *examList = new wxListCtrl(p_dialog, ID_UPDATE_ASSESSMENTS, wxDefaultPosition, wxDefaultSize, wxLC_VRULES | wxLC_REPORT);

    examList->InsertColumn(0, wxT("Name"));
    examList->InsertColumn(1, wxT("Weighting"));
    examList->InsertColumn(2, wxT("Deadline"));

    for(assessment * as : courseAssessments["Exams"])
    {
        long index = examList->InsertItem(0, as->name);
        examList->SetItem(index, 1, to_string(as->weighting));
        examList->SetItem(index, 2, as->deadline);            
    }

    box_v3->Add(examList, wxEXPAND | wxLEFT |wxRIGHT);
    box_v3->AddSpacer(border_dlg*2);

    box_h->Add(box_v1);
    box_h->AddSpacer(border_dlg);
    box_h->Add(box_v2);
    box_h->AddSpacer(border_dlg);
    box_h->Add(box_v3);

    box_v->Add(box_h, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
    box_v->AddSpacer(border_dlg*2);
    
    wxStatusBar *help = new wxStatusBar(p_dialog);
    help->SetStatusText("Double-click on an assessment to edit the weightings or deadline");

    box_v->Add(help, 0, wxEXPAND, 0);

    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

viewAssessmentsDialog::~viewAssessmentsDialog(){}

void viewAssessmentsDialog::editAssessments(wxListEvent& event)
{
    wxListItem row = event.GetItem();
    editAssessmentsDialog *edit = new editAssessmentsDialog("Edit Mark", row, event, courseName);
    event.Skip();
}

//edit marks
editAssessmentsDialog::editAssessmentsDialog(const wxString&  title, wxListItem row, wxListEvent event, string courseName): wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    rowSelected = row;
    courseName = courseName;

    cout << row.GetText().ToStdString() << endl;

    wxPanel *p_dialog = new wxPanel(this, -1);

    box_v = new wxBoxSizer(wxVERTICAL);

    box_v->AddSpacer(border_dlg/2);

    wxBoxSizer *box_h1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *box_h2 = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *weightLbl = new wxStaticText(p_dialog, -1, wxT("Enter Weighting:"));
    box_h1->Add(weightLbl);
    box_h1->AddSpacer(border_dlg);

    weightInput = new wxSpinCtrlDouble(p_dialog, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 16384L, 0.00, 1.00, 0, 0.01);

    box_h1->Add(weightInput);

    /*adapted from https://stackoverflow.com/questions/37306895/c-converting-a-string-to-a-time-t-variable - Steve Lorimer*/
    
    wxStaticText *dateLbl = new wxStaticText(p_dialog, -1, wxT("Enter Deadline:"));
    
    box_h2->Add(dateLbl);
    box_h2->AddSpacer(border_dlg);

    struct tm tm;

    int Y, m, d;

    /*const char *temp = originalVal.c_str();

    cout << "date = " << temp << endl;

    try
    {
        sscanf(temp, "%d-%d-%d", &Y, &m, &d);
    }
    catch(...)
    {
        cout << "could not convert time" << endl;
        Close();
        return;
    }

    tm.tm_year = Y - 1900;
    tm.tm_mon = m - 1;
    tm.tm_mday = d;

    wxDateTime(mktime(&tm))

    */

    date = new wxDatePickerCtrl(p_dialog, -1, wxDefaultDateTime);
    box_h2->Add(date);

    box_v->Add(box_h1, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
    box_v->AddSpacer(border_dlg);
    box_v->Add(box_h2, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

    box_v->AddSpacer(border_dlg/2);
    
    wxButton *confirmEdit = new wxButton(p_dialog, ID_EDIT_ASSESSMENTS, wxT("Confirm"));
    confirmEdit->SetBackgroundColour(*wxYELLOW);
    confirmEdit->SetForegroundColour(*wxWHITE);

    box_v->Add(confirmEdit, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

editAssessmentsDialog::~editAssessmentsDialog(){}

void editAssessmentsDialog::updateAssessment(wxCommandEvent& event)
{
    string listItem = rowSelected.GetText().ToStdString();

    cout << "listItem = " << listItem << endl;

    float w = weightInput->GetValue();
    string d = date->GetValue().FormatISODate().ToStdString();
    cout << "Date = " << d << endl;

    if(!w || w <= 0 || d == "")
    {
        wxMessageBox("All fields must be complete and valid!");
        return;
    }

    for(assessment *as : env_hope_vars->assessments)
    {
        if(as->name == listItem)
        {
            as->weighting = w;
            as->deadline = d;
            env_hope_vars->updateVar("assessment");
            break;
        }
    }

    Close();
    viewAssessmentsDialog *view = new viewAssessmentsDialog("View Assessments", courseName);
}

updateCourseDialog::updateCourseDialog(const wxString&  title, wxGridEvent cell, wxGrid *grid): wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    
    env_hope_vars->printhope_vars();

    wxPanel *p_dialog = new wxPanel(this, -1);
    
    cellSelected = &cell;
    colSelected = cellSelected->GetCol();

    course = grid->GetCellValue(cellSelected->GetRow(), 0).ToStdString();

    box_v = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *box_h = new wxBoxSizer(wxHORIZONTAL);
    
    string originalVal =  grid->GetCellValue(cellSelected->GetRow(), cellSelected->GetCol()).ToStdString();

    cout << "originalVal = " << originalVal << endl;

    wxStaticText *inputLbl = new wxStaticText(p_dialog, -1, wxT("Enter New Value:"));
    
    box_h->Add(inputLbl);
    box_h->AddSpacer(border_dlg);

    switch(colSelected)
    {
        case 0:
            courseName = new wxTextCtrl(p_dialog, -1, originalVal);

            box_h->Add(courseName);
            break;
        case 1:
            char temp[3] = {'C', 'I', 'H'};

            wxArrayString levels;

            for(char c : temp)
            {
                levels.Add(c);
            }

            courseLevel = new wxComboBox(p_dialog, -1, "", wxDefaultPosition, wxDefaultSize, levels, wxCB_READONLY);
            box_h->Add(courseLevel);
            break;

    }

    box_v->Add(box_h, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
    
    wxButton *confirmUpdate = new wxButton(p_dialog, ID_UPDATE_COURSE, wxT("Update"));
    confirmUpdate->SetBackgroundColour(*wxBLUE);
    confirmUpdate->SetForegroundColour(*wxWHITE);

    box_v->Add(confirmUpdate, 0, wxEXPAND, border_dlg);

    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

updateCourseDialog::~updateCourseDialog(){}

void updateCourseDialog::updateCourse(wxCommandEvent& event)
{
    string val;

    for(courseObj *cs : env_hope_vars->courses)
    {
        if(cs->name == course)
        {  
            switch(colSelected)
            {
                case 1:
                    val = courseLevel->GetStringSelection().ToStdString();

                    cs->level = val[0];
                    break;
            }
        } 
    }

    env_hope_vars->updateVar("course");

    wxMessageBox("Reopen 'Manage Courses' to view changes.");
    
    Close();
}
