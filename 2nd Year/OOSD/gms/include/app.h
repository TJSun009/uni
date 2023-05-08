#pragma once

#include<mainMenu.h>
#include "csv.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class app: public wxApp
{
    public:
        app();
        ~app();
        virtual bool OnInit();
    private:
        mainMenu* frame = nullptr;
};