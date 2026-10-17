#pragma once

namespace PawCare {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class LoginForm : public System::Windows::Forms::Form
    {
    private:
        bool loginSuccessful;
        String^ currentUser;
        String^ currentRole;

        System::Windows::Forms::Panel^ panelHeader;
        System::Windows::Forms::Label^ lblBrand;
        System::Windows::Forms::Label^ lblTagline;

        System::Windows::Forms::Label^ lblUsername;
        System::Windows::Forms::TextBox^ txtUsername;
        System::Windows::Forms::Label^ lblPassword;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::Label^ lblRole;
        System::Windows::Forms::ComboBox^ cmbRole;

        System::Windows::Forms::Button^ btnLogin;
        System::Windows::Forms::Button^ btnCancel;
        System::Windows::Forms::Label^ lblHint;

    public:
        LoginForm(void)
        {
            loginSuccessful = false;
            currentUser = "admin";
            currentRole = "Administrator";
            InitializeComponent();
        }

        property bool IsLoginSuccessful
        {
            bool get() { return loginSuccessful; }
        }

        property String^ CurrentUser
        {
            String^ get() { return currentUser; }
        }

        property String^ CurrentRole
        {
            String^ get() { return currentRole; }
        }

    protected:
        ~LoginForm()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->panelHeader = (gcnew System::Windows::Forms::Panel());
            this->lblBrand = (gcnew System::Windows::Forms::Label());
            this->lblTagline = (gcnew System::Windows::Forms::Label());

            this->lblUsername = (gcnew System::Windows::Forms::Label());
            this->txtUsername = (gcnew System::Windows::Forms::TextBox());
            this->lblPassword = (gcnew System::Windows::Forms::Label());
            this->txtPassword = (gcnew System::Windows::Forms::TextBox());
            this->lblRole = (gcnew System::Windows::Forms::Label());
            this->cmbRole = (gcnew System::Windows::Forms::ComboBox());

            this->btnLogin = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->lblHint = (gcnew System::Windows::Forms::Label());

            this->panelHeader->BackColor = System::Drawing::Color::FromArgb(33, 150, 243);
            this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
            this->panelHeader->Height = 90;
            this->panelHeader->Controls->Add(this->lblTagline);
            this->panelHeader->Controls->Add(this->lblBrand);

            this->lblBrand->Text = "PAWCARE CLINIC";
            this->lblBrand->Font = (gcnew System::Drawing::Font("Segoe UI", 16, System::Drawing::FontStyle::Bold));
            this->lblBrand->ForeColor = System::Drawing::Color::White;
            this->lblBrand->Location = System::Drawing::Point(30, 20);
            this->lblBrand->AutoSize = true;

            this->lblTagline->Text = "Pet Care Management System - User Login";
            this->lblTagline->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Regular));
            this->lblTagline->ForeColor = System::Drawing::Color::FromArgb(227, 242, 253);
            this->lblTagline->Location = System::Drawing::Point(32, 53);
            this->lblTagline->AutoSize = true;

            this->lblUsername->Text = "Username";
            this->lblUsername->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->lblUsername->ForeColor = System::Drawing::Color::FromArgb(55, 71, 79);
            this->lblUsername->Location = System::Drawing::Point(40, 115);
            this->lblUsername->AutoSize = true;

            this->txtUsername->Font = (gcnew System::Drawing::Font("Segoe UI", 10.5F));
            this->txtUsername->Location = System::Drawing::Point(40, 140);
            this->txtUsername->Size = System::Drawing::Size(320, 28);
            this->txtUsername->Text = "admin";

            this->lblPassword->Text = "Password";
            this->lblPassword->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->lblPassword->ForeColor = System::Drawing::Color::FromArgb(55, 71, 79);
            this->lblPassword->Location = System::Drawing::Point(40, 185);
            this->lblPassword->AutoSize = true;

            this->txtPassword->Font = (gcnew System::Drawing::Font("Segoe UI", 10.5F));
            this->txtPassword->Location = System::Drawing::Point(40, 210);
            this->txtPassword->Size = System::Drawing::Size(320, 28);
            this->txtPassword->UseSystemPasswordChar = true;
            this->txtPassword->Text = "admin123";

            this->lblRole->Text = "Role";
            this->lblRole->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->lblRole->ForeColor = System::Drawing::Color::FromArgb(55, 71, 79);
            this->lblRole->Location = System::Drawing::Point(40, 255);
            this->lblRole->AutoSize = true;

            this->cmbRole->Font = (gcnew System::Drawing::Font("Segoe UI", 10));
            this->cmbRole->Location = System::Drawing::Point(40, 280);
            this->cmbRole->Size = System::Drawing::Size(320, 28);
            this->cmbRole->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbRole->Items->AddRange(gcnew array<Object^> { "Administrator", "Veterinarian", "Receptionist" });
            this->cmbRole->SelectedIndex = 0;
            this->cmbRole->SelectedIndexChanged += gcnew System::EventHandler(this, &LoginForm::cmbRole_SelectedIndexChanged);

            this->btnLogin->Text = "Login";
            this->btnLogin->Font = (gcnew System::Drawing::Font("Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->btnLogin->ForeColor = System::Drawing::Color::White;
            this->btnLogin->BackColor = System::Drawing::Color::FromArgb(33, 150, 243);
            this->btnLogin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnLogin->FlatAppearance->BorderSize = 0;
            this->btnLogin->Location = System::Drawing::Point(40, 335);
            this->btnLogin->Size = System::Drawing::Size(150, 38);
            this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);

            this->btnCancel->Text = "Exit";
            this->btnCancel->Font = (gcnew System::Drawing::Font("Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->btnCancel->ForeColor = System::Drawing::Color::White;
            this->btnCancel->BackColor = System::Drawing::Color::FromArgb(120, 144, 156);
            this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCancel->FlatAppearance->BorderSize = 0;
            this->btnCancel->Location = System::Drawing::Point(210, 335);
            this->btnCancel->Size = System::Drawing::Size(150, 38);
            this->btnCancel->Click += gcnew System::EventHandler(this, &LoginForm::btnCancel_Click);

            this->lblHint->Text = "admin/admin123 (Admin) | vet/vet123 (Vet) | reception/rec123 (Reception)";
            this->lblHint->Font = (gcnew System::Drawing::Font("Segoe UI", 8.0F, System::Drawing::FontStyle::Italic));
            this->lblHint->ForeColor = System::Drawing::Color::Gray;
            this->lblHint->Location = System::Drawing::Point(20, 390);
            this->lblHint->AutoSize = true;

            this->ClientSize = System::Drawing::Size(400, 435);
            this->Text = "PawCare - Login";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->BackColor = System::Drawing::Color::FromArgb(250, 250, 250);

            this->Controls->Add(this->panelHeader);
            this->Controls->Add(this->lblUsername);
            this->Controls->Add(this->txtUsername);
            this->Controls->Add(this->lblPassword);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->lblRole);
            this->Controls->Add(this->cmbRole);
            this->Controls->Add(this->btnLogin);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->lblHint);

            this->AcceptButton = this->btnLogin;
        }

        void cmbRole_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (cmbRole->SelectedIndex == 0)
            {
                txtUsername->Text = "admin";
                txtPassword->Text = "admin123";
            }
            else if (cmbRole->SelectedIndex == 1)
            {
                txtUsername->Text = "vet";
                txtPassword->Text = "vet123";
            }
            else if (cmbRole->SelectedIndex == 2)
            {
                txtUsername->Text = "reception";
                txtPassword->Text = "rec123";
            }
        }

        void btnLogin_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ u = txtUsername->Text->Trim();
            String^ p = txtPassword->Text->Trim();

            bool isValid = false;
            if (u == "admin" && p == "admin123")
            {
                isValid = true;
                currentUser = "Administrator";
                currentRole = "Administrator";
            }
            else if (u == "vet" && p == "vet123")
            {
                isValid = true;
                currentUser = "Dr. Silva (Veterinarian)";
                currentRole = "Veterinarian";
            }
            else if (u == "reception" && p == "rec123")
            {
                isValid = true;
                currentUser = "Reception Desk";
                currentRole = "Receptionist";
            }

            if (isValid)
            {
                loginSuccessful = true;
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            else
            {
                MessageBox::Show("Invalid username or password.\n\nPlease check your credentials and try again.",
                    "Login Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
                txtPassword->Text = "";
                txtPassword->Focus();
            }
        }

        void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
        {
            loginSuccessful = false;
            this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->Close();
        }
    };
}
