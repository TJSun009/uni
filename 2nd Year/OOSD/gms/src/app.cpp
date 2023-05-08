#include <wx/wx.h>
#include <app.h>
#include <enums.h>

hope_vars *env_hope_vars = new hope_vars();

wxIMPLEMENT_APP(app);

app::app()
{
}

app::~app()
{
}

bool app::OnInit()
{
    frame = new mainMenu("LHU Grade Management System", wxDefaultPosition, wxDefaultSize);
    frame->Maximize();
    frame->SetMinClientSize(wxSize(600, 250));
    frame->Show();

    return true;
}