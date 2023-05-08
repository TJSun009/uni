// Creating main menu to display in main program
#include <mainMenu.h>
#include <enums.h>

wxBEGIN_EVENT_TABLE(mainMenu, wxFrame)
    EVT_MENU(ID_M_DEGREE, mainMenu::OnDegree)
    EVT_MENU(ID_M_STUDENT, mainMenu::OnStudent)
    EVT_MENU(ID_M_COURSE, mainMenu::OnCourse)
    EVT_MENU(ID_M_GRADES, mainMenu::OnGrade)
    EVT_MENU(wxID_EXIT, mainMenu::OnExit)
    EVT_MENU(wxID_HELP, mainMenu::OnHelp)
    EVT_MENU(wxID_RESIZE_FRAME, mainMenu::OnResize)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(viewGradeLettersDialog, wxDialog)
    EVT_LIST_ITEM_ACTIVATED(wxID_ANY, editGradeLetters)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(editGradeLettersDialog, wxDialog)
    EVT_BUTTON(ID_UPDATE_GRADES, updateGradeLetters)
wxEND_EVENT_TABLE()

mainMenu::mainMenu(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, M_FRAME, title, pos, size)
{
    m_panel->SetBackgroundColour(*wxWHITE);
    
    wxIcon icon;
    icon.LoadFile("LHU-Logo.ico", wxBITMAP_TYPE_ICO);
    this->SetIcon(icon);
    //Centre();
    //Create Menu and Add Items
    options = new wxMenu();
    options->Append(ID_M_DEGREE, "&Manage Degrees","Create and Update Degree and Course Information.");
    options->Append(ID_M_STUDENT, "&Manage Students","Create Students, Update Student Information, and View or Export Student Transcripts.");
    options->Append(ID_M_GRADES, "&Manage Grade Letters", "Assign Grade Letters");
    options->Append(wxID_HELP, "&Help","View FAQs.");
    options->Append(wxID_EXIT, "&Exit","Close.");

    //Create Menubar and add menu
    m_MenuBar = new wxMenuBar;
    m_MenuBar->Append(options, "&Options");
    SetMenuBar(m_MenuBar);
    CreateStatusBar();
    SetStatusText("Welcome to the LHU Grading Management System (GMS)!");
}

mainMenu::~mainMenu(){}

void mainMenu::OnDegree(wxCommandEvent& event)
{
    if(m_MenuBar->GetMenuCount() == 1)
    {
        wxMenu * courses = new wxMenu();
        courses->Append(ID_M_COURSE, "&Manage Courses");

        m_MenuBar->Append(courses, "&Courses");
        
        SetMenuBar(m_MenuBar);
    }
    
    
    //Clear existing window elements
    if(m_sizer->GetChildren().GetCount() > 0)
    {
        m_panel->DestroyChildren();
        m_sizer->Clear(true);
    }

    m_panel->SetSize(m_panel->GetParent()->GetClientSize());

    //Create window displaying degree management panel
    m_sizer->Add(new degree(m_panel, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "Manage Degree"), wxEXPAND | wxALL, 5);
    m_panel->SetSizer(m_sizer);
    m_panel->Centre();
    //m_panel->SetAutoLayout(true);
    //m_sizer->FitInside(m_panel);
    m_panel->Layout();
    
    event.Skip();
}

void mainMenu::OnStudent(wxCommandEvent& event)
{
    if(m_MenuBar->GetMenuCount() == 2)
    {
        m_MenuBar->Remove(1);

        SetMenuBar(m_MenuBar);
    }
    

    //Clear existing window elements
    if(m_sizer->GetChildren().GetCount() > 0)
    {
        m_panel->DestroyChildren();
        m_sizer->Clear(true);
    }

    m_panel->SetSize(m_panel->GetParent()->GetClientSize());

    //Create window displaying student management panel
    m_sizer->Add(new student(m_panel, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "Manage Student"), wxEXPAND | wxALL, 5);
    m_panel->SetSizer(m_sizer);
    m_panel->Centre();
    //m_panel->SetAutoLayout(true);
    //m_sizer->FitInside(m_panel);
    m_panel->Layout();

    event.Skip();
}

void mainMenu::OnCourse(wxCommandEvent& event)
{

    //Clear existing window elements
    if(m_sizer->GetChildren().GetCount() > 0)
    {
        m_panel->DestroyChildren();
        m_sizer->Clear(true);
    }

    m_panel->SetSize(m_panel->GetParent()->GetClientSize());

    //Create window displaying student management panel
    m_sizer->Add(new course(m_panel, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "Manage Student"), wxEXPAND | wxALL, 5);
    m_panel->SetSizer(m_sizer);
    m_panel->Centre();
    //m_panel->SetAutoLayout(true);
    //m_sizer->FitInside(m_panel);
    m_panel->Layout();

    event.Skip();
}

void mainMenu::OnGrade(wxCommandEvent& event)
{
    new viewGradeLettersDialog("View Grade Letters");
    event.Skip();
}

void mainMenu::OnExit(wxCommandEvent& event)
{
    //Create window displaying degree management options
    Close(true);
}

void mainMenu::OnHelp(wxCommandEvent& event)
{
    //Create window display a scrollable FAQ frame
    //ShellExecute(0, 0, L"" )
    event.Skip();
}

void mainMenu::OnResize(wxCommandEvent& event)
{
    //Resize window when expanded
    m_panel->SetSize(m_panel->GetParent()->GetClientSize());
    m_sizer->FitInside(this);
    m_panel->Layout();
    m_sizer->Layout();

    event.Skip();
}

//view grade letters
viewGradeLettersDialog::viewGradeLettersDialog(const wxString& title) : wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{

    env_hope_vars->printhope_vars();

    wxPanel *p_dialog = new wxPanel(this, -1);

    box_v = new wxBoxSizer(wxVERTICAL);
    box_v->AddSpacer(border_dlg);

    wxFont *fontM = new wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true);

    wxStaticText *glTitle = new wxStaticText(p_dialog, -1, "Grade Letters");
    
    glTitle->SetFont(*fontM);

    box_v->Add(glTitle, 0, wxLEFT, border_dlg);
    box_v->AddSpacer(border_dlg);
    
    //grade letters

    wxListCtrl *gList = new wxListCtrl(p_dialog, ID_UPDATE_ASSESSMENTS, wxDefaultPosition, wxDefaultSize, wxLC_VRULES | wxLC_REPORT);

    gList->InsertColumn(0, wxT("Grade"));
    gList->InsertColumn(1, wxT("Min (inc)"));
    gList->InsertColumn(2, wxT("Max"));

    long index;

    for(gradeLetter* g : env_hope_vars->gradeLetters)
    {
        string l = g->letter;
        float min = g->min;
        float max = g->max;

        index = gList->InsertItem(index, l);
        gList->SetItem(index, 0, l);
        gList->SetItem(index, 1, to_string(min));
        gList->SetItem(index, 2, to_string(max));
        index++;
    }

    box_v->Add(gList, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
    box_v->AddSpacer(border_dlg*2);
    
    wxStatusBar *help = new wxStatusBar(p_dialog);
    help->SetStatusText("Double-click on a grade to edit the letter, minimum mark or maximum mark");

    box_v->Add(help, 0, wxEXPAND, 0);

    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

viewGradeLettersDialog::~viewGradeLettersDialog(){}

void viewGradeLettersDialog::editGradeLetters(wxListEvent& event)
{
    Close();
    wxListItem row = event.GetItem();
    editGradeLettersDialog *edit = new editGradeLettersDialog("Edit Mark", row, event);
    event.Skip();
}

//edit marks
editGradeLettersDialog::editGradeLettersDialog(const wxString&  title, wxListItem row, wxListEvent event): wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    
    rowSelected = row;

    cout << row.GetText().ToStdString() << endl;

    wxPanel *p_dialog = new wxPanel(this, -1);

    box_v = new wxBoxSizer(wxVERTICAL);

    box_v->AddSpacer(border_dlg/2);

    wxBoxSizer *box_h1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *box_h2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *box_h3 = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *nameLbl = new wxStaticText(p_dialog, -1, wxT("Enter New Grade:"));
    box_h1->Add(nameLbl);
    box_h1->AddSpacer(border_dlg);

    name = new wxTextCtrl(p_dialog, -1, row.GetText());

    box_h1->Add(name);

    wxStaticText *minLbl = new wxStaticText(p_dialog, -1, wxT("Enter Minimum:"));
    box_h2->Add(minLbl);
    box_h2->AddSpacer(border_dlg);

    min = new wxSpinCtrlDouble(p_dialog, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 16384L, 0.00, 1.00, 0, 0.01);

    box_h2->Add(min);

    wxStaticText *maxLbl = new wxStaticText(p_dialog, -1, wxT("Enter Maximum:"));
    box_h2->Add(maxLbl);
    box_h2->AddSpacer(border_dlg);

    max = new wxSpinCtrlDouble(p_dialog, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 16384L, 0.00, 1.00, 0, 0.01);

    box_h2->Add(max);

    box_v->Add(box_h1, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
    box_v->AddSpacer(border_dlg);
    box_v->Add(box_h2, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
    box_v->AddSpacer(border_dlg);
    box_v->Add(box_h3, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

    box_v->AddSpacer(border_dlg/2);
    
    wxButton *confirmEdit = new wxButton(p_dialog, ID_UPDATE_GRADES, wxT("Confirm"));
    confirmEdit->SetBackgroundColour(*wxYELLOW);
    confirmEdit->SetForegroundColour(*wxWHITE);

    box_v->Add(confirmEdit, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

editGradeLettersDialog::~editGradeLettersDialog(){}

void editGradeLettersDialog::updateGradeLetters(wxCommandEvent& event)
{
    string listItem = rowSelected.GetText().ToStdString();

    cout << "listItem = " << listItem << endl;

    float mi = min->GetValue();
    float ma = max->GetValue();

    string n = name->GetValue().ToStdString();

    if(!mi || mi <= 0 || !ma || ma <= 0 || n == "")
    {
        wxMessageBox("All fields must be complete and valid!");
        return;
    }

    for(gradeLetter *gl : env_hope_vars->gradeLetters)
    {
        if(gl->letter == listItem)
        {
            gl->letter = n;
            gl->min = mi;
            gl->max = ma;
            env_hope_vars->updateVar("gradeLetter");
            
            break;
        }
    }

    Close();
    
    wxMessageBox("Close and reopen the grade letters dialog to see changes.");
}