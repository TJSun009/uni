// Creating main menu to display in main program
#include <student.h>
#include <math.h> 

wxBEGIN_EVENT_TABLE(student, wxPanel)
    EVT_BUTTON(ID_C_STUDENT, student::OnCreateStudent)
    EVT_BUTTON(ID_U_STUDENT, student::OnUpdateStudent)
    EVT_GRID_CELL_LEFT_CLICK(student::OnClickGrid)
    EVT_GRID_CELL_LEFT_DCLICK(student::OnClickGrid)
    EVT_CHECKBOX(ID_SECOND_ATTEMPT, student::OnSecondAttempt)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(createStudentDialog, wxDialog)
    EVT_BUTTON(ID_CLOSE_STUDENT_DLG, createStudentDialog::closeDialog)
    EVT_BUTTON(ID_ADD_STUDENT, createStudentDialog::addStudent)
    EVT_BUTTON(ID_UPLOAD_STUDENT, createStudentDialog::OnUploadStudent)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(viewMarksDialog, wxDialog)
    EVT_LIST_ITEM_ACTIVATED(ID_UPDATE_MARKS, viewMarksDialog::editMarks)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(editMarksDialog, wxDialog)
    EVT_BUTTON(ID_EDIT_MARKS, editMarksDialog::updateMarks)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(updateStudentDialog, wxDialog)
    EVT_BUTTON(ID_UPDATE_STUDENT, updateStudentDialog::updateStudent)
wxEND_EVENT_TABLE()

//display student info
student::student(wxWindow *parent, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, ID_M_STUDENT_PANEL, pos, size, style, name)
{
    wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);
    this->SetBackgroundColour(*wxRED);

    newStudent = new wxButton(this, ID_C_STUDENT, "New Student");

    grid = new wxGrid(this, -1);

    env_hope_vars->hopeWxGrid(grid, "student");


    wxFont *font = new wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxStaticText *title = new wxStaticText(this, -1, "Students");
    title->SetFont(*font);
    box->Add(title, 0, wxLEFT, 5);
    box->AddSpacer(10);
    box->Add(newStudent, 0, wxLEFT, 5);
    box->AddSpacer(20);
    box->Add(grid, 0, wxLEFT | wxEXPAND, 5);

    SetSizer(box);

    this->Fit();
}

student::~student(){}

void student::OnCreateStudent(wxCommandEvent& event)
{
    //Create window displaying student management frame
    createStudentDialog *dlg = new createStudentDialog("Create Student");
    event.Skip();
}

void student::OnUpdateStudent(wxCommandEvent& event)
{
    //Create window displaying student management frame
    wxMessageBox("Updating Student");
    event.Skip();
}

void student::OnClickGrid(wxGridEvent& event)
{
    //Create window displaying student management frame
    int column = event.GetCol();
    int row = event.GetRow();
    string value = grid->GetCellValue(row, column).ToStdString();

    if(value == "view")
    {
        int id = stoi(grid->GetCellValue(event.GetRow(), 0).ToStdString());
        viewMarksDialog *view = new viewMarksDialog("View Students", id);
    }
    else if(value == "generate")
    {
        id = stoi(grid->GetCellValue(event.GetRow(), 0).ToStdString());

        //transcript_ids.push_back(id);

        viewTranscript(event);
    }
    else if(column < 3)
    {
        wxString title = "Update " + grid->GetColLabelValue(column).ToStdString() + " field";

        string firstname = grid->GetCellValue(row, 1).ToStdString();

        string surname = grid->GetCellValue(row, 2).ToStdString();

        updateStudentDialog *update = new updateStudentDialog(title, event, grid, firstname, surname);

        cout << "created update student dialog" << endl;
    }
    
    event.Skip();
}

//transcripts
void student::viewTranscript(wxGridEvent &event)
{
    temp = new wxDialog(this, -1, wxT("View Transcript"));
    
    wxPanel *d_panel = new wxPanel(temp);

    studentObj* st = env_hope_vars->findStudent(id);

    cout << st->firstname << " " << st->surname << endl;

    vector<degreeObj*> d_objs = st->studentDegrees;

    for(degreeObj* dg : d_objs)
    {
        box_v1 = new wxBoxSizer(wxVERTICAL);

        cout << "Degree: " << dg->name << endl;

        wxFont *fontL = new wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

        wxFont *fontM = new wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true);
        
        cout <<"text input created" << endl;

        wxStaticText *dgText = new wxStaticText(d_panel, -1, dg->name);
        
        dgText->SetFont(*fontL);

        box_v1->Add(dgText, 0, wxLEFT, border_dlg);
        box_v1->AddSpacer(border_dlg);
        
        float c1Percent, c2Percent;
        
        //course1

        wxStaticText *c1Text = new wxStaticText(d_panel, -1, dg->course1->name+" Level "+dg->course1->level, wxDefaultPosition, wxDefaultSize, wxFONTWEIGHT_BOLD);

        cout << c1Text->GetLabelText().ToStdString() << endl;

        cout << "id = " << id << endl;

        c1Text->SetFont(*fontM);

        box_v1->Add(c1Text);

        box_v1->AddSpacer(border_dlg);

        float c1Portfolios = 0;
        float c1Exams = 0;
        float c1Coursework = 0;
        float c2Portfolios = 0;
        float c2Exams = 0;
        float c2Coursework = 0;
        
        float weightings[3];

        for(studentMark* stM : env_hope_vars->studentMarks)
        {
            if(stM->degree == dg->name && id == stM->id && dg->course1->name == stM->course)
            {
                string type = "";
                cout << "Course: " << dg->course1->name << endl;
                
                for(courseObj *c1 : env_hope_vars->findCourses(dg->course1->name))
                {
                    cout << c1->name << endl;
                    
                    string l = c1->level;
                    
                    getWeights(weightings, l);

                    for(assessment *as : c1->assessments["Portfolios"])
                    {
                        c1Portfolios += as->weighting*stM->marks/100;
                    }

                    for(assessment *as : c1->assessments["Coursework"])
                    {
                        c1Coursework += as->weighting*stM->marks/100;
                    }

                    for(assessment *as : c1->assessments["Exams"])
                    {
                        c1Exams += as->weighting*stM->marks/100;
                    }
                } 
            }
        }
        
        c1Percent += c1Portfolios * weightings[0];

        string pGrade = "Portfolios Grade: "+getGrade(c1Portfolios);

        cout << pGrade << "with decimal %" << c1Portfolios << endl;

        wxStaticText * pLbl = new wxStaticText(d_panel, -1, pGrade);
        box_v1->Add(pLbl);

        if(c1Portfolios == 0)
        {
            cout << "No portfolios completed";
            wxBoxSizer * box_h = new wxBoxSizer(wxHORIZONTAL);

            wxStaticText * cLbl = new wxStaticText(d_panel, -1, "Enter Concession Code: ");
            box_h->Add(cLbl);
            box_h->AddSpacer(border_dlg);

            wxTextCtrl * cCode = new wxTextCtrl(d_panel, concessions);

            concession.Add(cCode);

            box_h->Add(cCode);
            box_v1->Add(box_h);
            concessions++;
        }

        c1Percent += c1Coursework* weightings[1];

        string cGrade = "Coursework Grade: "+getGrade(c1Coursework);

        cout << cGrade << "with decimal %" << c1Coursework << endl;

        wxStaticText * cLbl = new wxStaticText(d_panel, -1, cGrade);
        box_v1->Add(cLbl);

        if(c1Coursework == 0)
        {
            cout << "No coursework completed";
            wxBoxSizer * box_h = new wxBoxSizer(wxHORIZONTAL);
            
            wxStaticText * cLbl = new wxStaticText(d_panel, -1, "Enter Concession Code: ");
            box_h->Add(cLbl);
            box_h->AddSpacer(border_dlg);

            wxTextCtrl * cCode = new wxTextCtrl(d_panel, concessions);

            concession.Add(cCode);

            box_h->Add(cCode);
            box_v1->Add(box_h);
            concessions++;
        }

        c1Percent += c1Exams* weightings[2];

        string eGrade = "Exams Grade: "+getGrade(c1Exams);

        cout << eGrade << "with decimal %" << c1Exams << endl;

        wxStaticText * eLbl = new wxStaticText(d_panel, -1, eGrade);
        box_v1->Add(eLbl);

        if(c1Exams == 0)
        {
            cout << "No exams completed";
            wxBoxSizer * box_h = new wxBoxSizer(wxHORIZONTAL);

            wxStaticText * cLbl = new wxStaticText(d_panel, -1, "Enter Concession Code: ");
            box_h->Add(cLbl);
            box_h->AddSpacer(border_dlg);

            wxTextCtrl * cCode = new wxTextCtrl(d_panel, concessions);

            concession.Add(cCode);

            box_h->Add(cCode);
            box_v1->Add(box_h);
            concessions++;
        }

        string c1Grade = "Course 1 Grade: "+ getGrade(c1Percent);

        wxStaticText * c1Lbl = new wxStaticText(d_panel, -1, c1Grade);

        box_v1->Add(c1Lbl);

        box_v1->AddSpacer(border_dlg*2);

        //course2

        wxStaticText *c2Text = new wxStaticText(d_panel, -1, dg->course1->name+" Level "+dg->course1->level, wxDefaultPosition, wxDefaultSize, wxFONTWEIGHT_BOLD);

        c2Text->SetFont(*fontM);

        box_v1->Add(c2Text);

        box_v1->AddSpacer(border_dlg);

        for(studentMark* stM : env_hope_vars->studentMarks)
        {
            if(stM->degree == dg->name && id == stM->id && dg->course2->name == stM->course)
            {
                string type = "";
                cout << "Course: " << dg->course2->name << endl;
                
                for(courseObj *c2 : env_hope_vars->findCourses(dg->course2->name))
                {
                    
                    string l = c2->level;
                    
                    getWeights(weightings, l);                    

                    float temp_percent = 0;

                    for(assessment *as : c2->assessments["Portfolios"])
                    {
                        c2Portfolios += as->weighting*stM->marks/100;
                    }

                    for(assessment *as : c2->assessments["Coursework"])
                    {
                        c2Coursework += as->weighting*stM->marks/100;
                    }

                    for(assessment *as : c2->assessments["Exams"])
                    {
                        c2Exams += as->weighting*stM->marks/100;
                    }
                } 
            }
        }
  
        c2Percent += c2Portfolios * weightings[0];

        pGrade = "Portfolios Grade: "+ getGrade(c2Portfolios);

        wxStaticText * pLbl2 = new wxStaticText(d_panel, -1, pGrade);

        box_v1->Add(pLbl2);

        if(c2Portfolios == 0)
        {
            wxBoxSizer * box_h = new wxBoxSizer(wxHORIZONTAL);

            wxStaticText * cLbl = new wxStaticText(d_panel, -1, "Enter Concession Code: ");
            box_h->Add(cLbl);
            box_h->AddSpacer(border_dlg);

            wxTextCtrl * cCode = new wxTextCtrl(d_panel, concessions);

            concession.Add(cCode);

            box_h->Add(cCode);
            box_v1->Add(box_h);
            concessions++;
        }

        c2Percent += c2Coursework* weightings[1];
        cGrade = "Coursework Grade: "+ getGrade(c2Coursework);

        wxStaticText * cLbl2 = new wxStaticText(d_panel, -1, cGrade);

        box_v1->Add(cLbl2);

        if(c2Coursework == 0)
        {
            wxBoxSizer * box_h = new wxBoxSizer(wxHORIZONTAL);
            
            wxStaticText * cLbl = new wxStaticText(d_panel, -1, "Enter Concession Code: ");
            box_h->Add(cLbl);
            box_h->AddSpacer(border_dlg);

            wxTextCtrl * cCode = new wxTextCtrl(d_panel, concessions);

            concession.Add(cCode);

            box_h->Add(cCode);
            box_v1->Add(box_h);
            concessions++;
        }

        c2Percent += c2Exams* weightings[2];

        eGrade = "Exams Grade: "+ getGrade(c2Exams);

        wxStaticText * eLbl2 = new wxStaticText(d_panel, -1, eGrade);

        box_v1->Add(eLbl2);

        if(c2Exams == 0)
        {
            wxBoxSizer * box_h = new wxBoxSizer(wxHORIZONTAL);

            wxStaticText * cLbl = new wxStaticText(d_panel, -1, "Enter Concession Code: ");
            box_h->Add(cLbl);
            box_h->AddSpacer(border_dlg);

            wxTextCtrl * cCode = new wxTextCtrl(d_panel, concessions);

            concession.Add(cCode);

            box_h->Add(cCode);
            box_v1->Add(box_h);
            concessions++;
        }
        
        string c2Grade = "Course 1 Grade: "+ getGrade(c2Percent);

        wxStaticText * c2Lbl = new wxStaticText(d_panel, -1, c2Grade);

        box_v1->Add(c2Lbl);

        box_v1->AddSpacer(border_dlg*2);

        wxCheckBox *secondattempt = new wxCheckBox(d_panel, ID_SECOND_ATTEMPT, "Second attempt?");

        box_v1->Add(secondattempt);

        float dg_percent = 0.5*(c1Percent+c2Percent);

        wxBoxSizer * box_h2 = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText * prog = new wxStaticText(d_panel, -1, "Progression Code:");

        box_h2->Add(prog);
        box_h2->AddSpacer(border_dlg);

        wxStaticText *prog_code;

        if(isgreater(dg_percent, 0.39))
        {
            prog_code = new wxStaticText(d_panel, -1, "Overall aggregate above 39: Successful progression.");
        }
        else if(isgreater(dg_percent, 0.32))
        {
            if(secondattempt->IsChecked())
            {
                prog_code = new wxStaticText(d_panel, -1, "Overall aggregate above 32 but no further assessment opportunity.");
            }
            else
            {
                prog_code = new wxStaticText(d_panel, -1, "Overall aggregate above 32: Reassessment granted with full attendance.");
            }
        }
        else
        {
            prog_code = new wxStaticText(d_panel, -1, "No further assessment opportunity.");
        }

        box_h2->Add(prog_code);
        box_v1->Add(box_h2);

        box_v->Add(box_v1);
        box_v->AddSpacer(border_dlg*4);
    }
    
    cout << "showing modal" << endl;
    
    d_panel->SetSizer(box_v);
    
    temp->ShowModal();
}

void student::OnSecondAttempt(wxCommandEvent& event)
{
    temp->Close();
    checked = event.IsChecked();
    viewTranscript();
}


//display dialog for creating students
createStudentDialog::createStudentDialog(const wxString& title) : wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    env_hope_vars->printhope_vars();

    wxPanel *p_dialog = new wxPanel(this, -1);

    box_v = new wxBoxSizer(wxVERTICAL);

    wxStaticBox *singleStudent = new wxStaticBox(this, -1, "Add Student");

    wxStaticBoxSizer *singleStudentSizer = new wxStaticBoxSizer(singleStudent, wxVERTICAL);

    wxBoxSizer *firstnameSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *firstnameLabel = new wxStaticText(p_dialog, -1, wxT("Firstname: "));

    studentFirstname = new wxTextCtrl(p_dialog, -1, wxT(""));
    
    firstnameSizer->Add(firstnameLabel);
    firstnameSizer->AddSpacer(border_dlg);
    firstnameSizer->Add(studentFirstname);

    wxBoxSizer *surnameSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *surnameLabel = new wxStaticText(p_dialog, -1, wxT("Surname: "));

    studentSurname = new wxTextCtrl(p_dialog, -1, wxT(""));
    
    surnameSizer->Add(surnameLabel);
    surnameSizer->AddSpacer(border_dlg*1.3);
    surnameSizer->Add(studentSurname);

    wxBoxSizer *idSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *idLabel = new wxStaticText(p_dialog, -1, wxT("Student ID: "));

    studentId = new wxTextCtrl(p_dialog, -1, wxT(""));

    idSizer->Add(idLabel);
    idSizer->AddSpacer(border_dlg*0.8);
    idSizer->Add(studentId);

    wxArrayString d_string = getDegrees();

    studentCourses = new wxCheckListBox(p_dialog, -1, wxDefaultPosition, wxDefaultSize, d_string);

    singleStudentSizer->Add(firstnameSizer);
    singleStudentSizer->AddSpacer(border_dlg);
    singleStudentSizer->Add(surnameSizer);
    singleStudentSizer->AddSpacer(border_dlg);
    singleStudentSizer->Add(idSizer);
    singleStudentSizer->AddSpacer(border_dlg);
    singleStudentSizer->Add(new wxStaticText(p_dialog, -1, wxT("Assign to Degrees:")));
    singleStudentSizer->AddSpacer(border_dlg);
    singleStudentSizer->Add(studentCourses);
    singleStudentSizer->AddSpacer(border_dlg);
    
    wxButton *add = new wxButton(p_dialog, ID_ADD_STUDENT, wxT("Add"));
    add->SetBackgroundColour(*wxRED);
    add->SetForegroundColour(*wxWHITE);

    singleStudentSizer->Add(add);

    //vertical box sizer
    box_v->Add(singleStudentSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
    box_v->AddSpacer(border_dlg);
    box_v->Add(new wxStaticText(p_dialog, -1, wxT("OR")), wxEXPAND | wxALL, 5);
    box_v->AddSpacer(border_dlg);

    wxStaticBox *multipleStudent = new wxStaticBox(this, -1, "Add via CSV");

    wxStaticBoxSizer *multipleStudentSizer = new wxStaticBoxSizer(multipleStudent, wxVERTICAL);

    wxBoxSizer *fileSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *fileLabel = new wxStaticText(p_dialog, -1, wxT("Select File: "));

    studentFile = new wxFilePickerCtrl(p_dialog, -1, wxEmptyString, wxT("Open Students CSV"), wxT("csv files (*.csv)|*.csv"));

    fileSizer->Add(fileLabel);
    fileSizer->AddSpacer(border_dlg);
    fileSizer->Add(studentFile);

    multipleStudentSizer->AddSpacer(border_dlg);
    multipleStudentSizer->Add(fileSizer);
    multipleStudentSizer->AddSpacer(border_dlg);

    wxButton *upload = new wxButton(p_dialog, ID_UPLOAD_STUDENT, wxT("Upload File"));
    upload->SetBackgroundColour(*wxBLUE);
    upload->SetForegroundColour(*wxWHITE);

    multipleStudentSizer->Add(upload);

    box_v->Add(multipleStudentSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
    box_v->AddSpacer(border_dlg/2);

    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

createStudentDialog::~createStudentDialog(){}

void createStudentDialog::closeDialog(wxCommandEvent& event)
{
    Close();
}

void createStudentDialog::addStudent(wxCommandEvent& event)
{
    string f = studentFirstname->GetValue().ToStdString();
    string s = studentSurname->GetValue().ToStdString();
    string temp = studentId->GetValue().ToStdString();
    
    int id;

    if(f == "" || s == "" || temp == "")
    {
        wxMessageBox("All fields must be complete.");
        return;
    }
    else
    {
        id =  stoi(temp);
    }
    
    for(studentObj *st : env_hope_vars->students)
    {
        if(st->id == id)
        {
            wxMessageBox("The id " + to_string(id) + " is already taken");
            return;
        }
        else if(st->firstname == f && st->surname == s)
        {
            wxMessageBox(f + " " + s + " is already a student in the database.");
            return;
        }
    }
    
    wxArrayInt checkedItems;

    int size = studentCourses->GetCheckedItems(checkedItems);

    for(int i :checkedItems)
    {
        cout << "Item " << i << " is selected." << endl;
    }
    
    if(size == 0)
    {
        wxMessageBox("No degrees selected.");
        return;
    }

    vector<degreeObj*> studentDegrees;

    for(degreeObj *d : env_hope_vars->degrees)
    {
        for(int i : checkedItems)
        {
            wxString dg_name = studentCourses->GetString(i);
            if(d->name == dg_name)
            {
                studentDegrees.push_back(d);
            }
        }
    }
    
    env_hope_vars->students.push_back(new studentObj(id, f, s, studentDegrees));
    

    env_hope_vars->printhope_vars();
    env_hope_vars->updateVar("student");
    env_hope_vars->updateVar("studentMark");

    wxMessageBox("Reopen 'Manage Students' to view students.\nReopen program to view student assessments.");

    Close();
}

void createStudentDialog::OnUploadStudent(wxCommandEvent& event)
{
    string f_path = studentFile->GetTextCtrlValue().ToStdString();

    cout << f_path << endl;

    f_path = regex_replace(f_path, regex(R"(\\)"), R"(\\)");
    f_path = regex_replace(f_path, regex(R"(.csv)"), R"()");

    cout << "f_path = " << f_path;

    if(f_path == "")
    {
        wxMessageBox("Nothing to upload.");
        return;
    }

    csv upload(f_path);

    upload.displayResult();

    map<string, vector<variant<int, string, float>>> stTable = upload.getResult();

    vector<variant<int, string, float>> ids = stTable["1-id"];

    for(auto val: ids)
    {
        for(studentObj *st : env_hope_vars->students)
        {
            int id = get<int>(val);
            if(id == st->id)
            {
                wxMessageBox("The id " + to_string(id) + " is already taken");
                return;
            }
        }
    }

    vector<variant<int, string, float>> fnames = stTable["2-firstname"];
    int r = 0;

    for(auto val: fnames)
    {
        for(studentObj *st : env_hope_vars->students)
        {
            string f = get<string>(val);
            string s = get<string>(stTable["3-surname"][r]);
            if(f == st->firstname && s == st->surname)
            {
                wxMessageBox(f +" "+ s + " "+ " is already in the database");
                return;
            }
        }
        r++;
    }

    env_hope_vars->loadHelper(stTable, "student");
    
    env_hope_vars->updateVar("student");
    
    env_hope_vars->updateVar("studentMark");

    wxMessageBox("Reopen 'Manage Students' to view changes.");

    Close();
}


//view marks
viewMarksDialog::viewMarksDialog(const wxString& title, int student_id) : wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    id = student_id;

    env_hope_vars->printhope_vars();

    wxPanel *p_dialog = new wxPanel(this, -1);

    box_v = new wxBoxSizer(wxVERTICAL);
    box_v->AddSpacer(border_dlg);

    studentObj* student = env_hope_vars->findStudent(id);

    vector<degreeObj*> d_objs = student->studentDegrees;

    for(degreeObj* dg : d_objs)
    {
        wxBoxSizer *box_v1 = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *box_v2 = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *box_h = new wxBoxSizer(wxHORIZONTAL);

        wxFont *fontL = new wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

        wxFont *fontM = new wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true);

        wxStaticText *dgText = new wxStaticText(p_dialog, -1, dg->name);
        
        dgText->SetFont(*fontL);

        box_v->Add(dgText, 0, wxLEFT, border_dlg);
        box_v->AddSpacer(border_dlg);

        //course1

        wxStaticText *c1Text = new wxStaticText(p_dialog, -1, dg->course1->name+" Level "+dg->course1->level, wxDefaultPosition, wxDefaultSize, wxFONTWEIGHT_BOLD);

        c1Text->SetFont(*fontM);

        box_v1->Add(c1Text);

        box_v1->AddSpacer(border_dlg);

        wxListCtrl *course1List = new wxListCtrl(p_dialog, ID_UPDATE_MARKS, wxDefaultPosition, wxDefaultSize, wxLC_VRULES | wxLC_REPORT);

        course1List->InsertColumn(0, wxT("Name"));
        course1List->InsertColumn(1, wxT("Type"));
        course1List->InsertColumn(2, wxT("Marks"));

        for(studentMark* stM : env_hope_vars->studentMarks)
        {
            if(stM->degree == dg->name && id == stM->id && dg->course1->name == stM->course)
            {
                string aName = stM->assessment;
                long index = course1List->InsertItem(0, aName);

                string type = "";

                for(courseObj *c1 : env_hope_vars->findCourses(dg->course1->name))
                {
                    for(assessment *as : c1->assessments["Portfolios"])
                    {
                        if(as->name == aName)
                        {
                            type = "Portfolios";
                            break;
                        }
                    }

                    if(type != "")
                    {
                        break;
                    }

                    for(assessment *as : c1->assessments["Coursework"])
                    {
                        if(as->name == aName)
                        {
                            type = "Coursework";
                            break;
                        }
                    }

                    if(type != "")
                    {
                        break;
                    }

                    for(assessment *as : c1->assessments["Exams"])
                    {
                        if(as->name == aName)
                        {
                            type = "Exams";
                            break;
                        }
                    }

                    if(type != "")
                    {
                        break;
                    }
                }

                course1List->SetItem(index, 1, type);

                string mark = to_string(stM->marks)== "101" ? "None" : to_string(stM->marks);

                course1List->SetItem(index, 2, mark);
            }
        }

        box_v1->Add(course1List, wxEXPAND | wxLEFT |wxRIGHT);


        //course2
        wxStaticText *c2Text = new wxStaticText(p_dialog, -1, dg->course2->name+" Level "+dg->course2->level, wxDefaultPosition, wxDefaultSize, wxFONTWEIGHT_BOLD);

        c2Text->SetFont(*fontM);

        box_v2->Add(c2Text);

        box_v2->AddSpacer(border_dlg);

        wxListCtrl *course2List = new wxListCtrl(p_dialog, ID_UPDATE_MARKS, wxDefaultPosition, wxDefaultSize, wxLC_VRULES | wxLC_REPORT);

        course2List->InsertColumn(0, wxT("Name"));
        course2List->InsertColumn(1, wxT("Type"));
        course2List->InsertColumn(2, wxT("Marks"));
        
        for(studentMark* stM : env_hope_vars->studentMarks)
        {
            if(stM->degree == dg->name && id == stM->id && dg->course2->name == stM->course)
            {
                string aName = stM->assessment;

                long index = course2List->InsertItem(0, aName);

                string type = "";

                for(courseObj *c2 : env_hope_vars->findCourses(dg->course1->name))
                {
                    for(assessment *as : c2->assessments["Portfolios"])
                    {
                        if(as->name == aName)
                        {
                            type = "Portfolios";
                            break;
                        }
                    }

                    if(type != "")
                    {
                        break;
                    }

                    for(assessment *as : c2->assessments["Coursework"])
                    {
                        if(as->name == aName)
                        {
                            type = "Coursework";
                            break;
                        }
                    }

                    if(type != "")
                    {
                        break;
                    }

                    for(assessment *as : c2->assessments["Exams"])
                    {
                        if(as->name == aName)
                        {
                            type = "Exams";
                            break;
                        }
                    }

                    if(type != "")
                    {
                        break;
                    }
                }

                course2List->SetItem(index, 1, type);

                string mark = to_string(stM->marks)== "101" ? "None" : to_string(stM->marks);

                course2List->SetItem(index, 2, mark);
            }
        }

        box_v2->Add(course2List, wxEXPAND | wxLEFT |wxRIGHT);

        box_h->Add(box_v1);
        box_h->AddSpacer(border_dlg);
        box_h->Add(box_v2);

        box_v->Add(box_h, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);
        box_v->AddSpacer(border_dlg*2);
    }

    wxStatusBar *help = new wxStatusBar(p_dialog);
    help->SetStatusText("Double-click on an assessment to edit the students grades");

    box_v->Add(help, 0, wxEXPAND, 0);

    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

viewMarksDialog::~viewMarksDialog(){}

void viewMarksDialog::editMarks(wxListEvent& event)
{
    Close();
    wxListItem row = event.GetItem();
    editMarksDialog *edit = new editMarksDialog("Edit Mark", row, id);
    event.Skip();
}


//edit marks
editMarksDialog::editMarksDialog(const wxString&  title, wxListItem row, int student_id): wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    id = student_id;
    rowSelected = row;

    wxPanel *p_dialog = new wxPanel(this, -1);

    box_v = new wxBoxSizer(wxVERTICAL);

    box_v->AddSpacer(border_dlg/2);

    wxBoxSizer *box_h = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *marksLbl = new wxStaticText(p_dialog, -1, wxT("Enter Marks:"));

    marksInput = new wxSpinCtrl(p_dialog, -1, "100");
    marksInput->SetRange(0, 100);

    box_h->Add(marksLbl);
    box_h->AddSpacer(border_dlg);
    box_h->Add(marksInput);

    box_v->Add(box_h, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

    box_v->AddSpacer(border_dlg/2);
    
    wxButton *confirmEdit = new wxButton(p_dialog, ID_EDIT_MARKS, wxT("Confirm"));
    confirmEdit->SetBackgroundColour(*wxYELLOW);
    confirmEdit->SetForegroundColour(*wxWHITE);

    box_v->Add(confirmEdit, 0, wxEXPAND | wxLEFT | wxRIGHT, border_dlg);

    p_dialog->SetSizer(box_v);
    p_dialog->Fit();
    this->Fit();

    ShowModal();
}

editMarksDialog::~editMarksDialog(){}

void editMarksDialog::updateMarks(wxCommandEvent& event)
{
    string listItem = rowSelected.GetText().ToStdString();

    for(studentMark *stM : env_hope_vars->studentMarks)
    {
        if(stM->assessment == listItem && stM->id == id)
        {
            stM->marks = marksInput->GetValue();
            break;
        }
    }
    Close();

    env_hope_vars->updateVar("studentMark");
    viewMarksDialog *view = new viewMarksDialog("View Students", id);
}

updateStudentDialog::updateStudentDialog(const wxString&  title, wxGridEvent cell, wxGrid *grid, string f, string s): wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    env_hope_vars->printhope_vars();

    wxPanel *p_dialog = new wxPanel(this, -1);
    
    cellSelected = &cell;
    colSelected = cellSelected->GetCol();

    firstname = f;
    surname = s;

    box_v = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *box_h = new wxBoxSizer(wxHORIZONTAL);
    
    string originalVal =  grid->GetCellValue(cellSelected->GetRow(), cellSelected->GetCol()).ToStdString();

    cout << "originalVal = " << originalVal << endl;

    wxStaticText *inputLbl = new wxStaticText(p_dialog, -1, wxT("Enter New Value:"));
    
    box_h->Add(inputLbl);
    box_h->AddSpacer(border_dlg);

    
    input = new wxTextCtrl(p_dialog, -1, originalVal);

    box_h->Add(input);

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

updateStudentDialog::~updateStudentDialog(){}

void updateStudentDialog::updateStudent(wxCommandEvent& event)
{
    string val;

    for(studentObj *st : env_hope_vars->students)
    {
        if(st->firstname == firstname && st->surname == surname)
        {
            switch(colSelected)
            {
                case 0:
                    val = input->GetValue().ToStdString();
                    
                    for(studentObj *st : env_hope_vars->students)
                    {
                        if(st->id == stoi(val))
                        {
                            wxMessageBox("The id " + val + " is already taken");
                            return;
                        }
                    }

                    st->id = stoi(val);
                    break;
                case 1:
                    val = input->GetValue().ToStdString();

                    st->firstname = val;
                    break;
                case 2:
                    val = input->GetValue().ToStdString();

                    st->surname = val;
                    break;
                case 3:
                    wxArrayInt checkedItems;

                    int size = studentCourses->GetCheckedItems(checkedItems);



                    for(int i :checkedItems)
                    {
                        cout << "Item " << i << " is selected." << endl;
                    }
                    
                    if(size == 0)
                    {
                        wxMessageBox("No degrees selected.");
                        return;
                    }

                    vector<degreeObj*> studentDegrees;

                    for(studentObj *st : env_hope_vars->students)
                    {
                        if(st->firstname == firstname && st->surname == surname)
                        {
                            for(degreeObj *d : st->studentDegrees)
                            {
                                for(int i : checkedItems)
                                {
                                    wxString dg_name = studentCourses->GetString(i);
                                    if(d->name == dg_name)
                                    {
                                        studentDegrees.push_back(d);

                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }
            }
        } 
    }

    env_hope_vars->updateVar("degree");

    wxMessageBox("Reopen 'Manage Degrees' to view changes.");
    
    Close();
}