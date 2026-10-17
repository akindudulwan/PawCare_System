#include "Forms/LoginForm.h"
#include "Forms/MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    while (true)
    {

        PawCare::LoginForm^ login = gcnew PawCare::LoginForm();
        if (login->ShowDialog() != DialogResult::OK || !login->IsLoginSuccessful)
        {
            break;
        }

        PawCare::MainForm^ mainForm = gcnew PawCare::MainForm(login->CurrentUser, login->CurrentRole);
        Application::Run(mainForm);

        if (!mainForm->IsLoggedOut)
        {
            break;
        }
    }

    return 0;
}
