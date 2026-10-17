#pragma once
#include "Models/Pet.h"
#include "Models/Dog.h"
#include "Models/Cat.h"
#include "Models/Owner.h"
#include "Models/Veterinarian.h"
#include "Models/Appointment.h"
#include "Models/MedicalRecord.h"
#include "Models/Payment.h"
#include "Database/DatabaseManager.h"
#include "OwnerForm.h"
#include "PetForm.h"
#include "AppointmentForm.h"
#include "BillingForm.h"
#include "MedicalRecordForm.h"
#include "VetPortalForm.h"
#include "ReceptionistPortalForm.h"

namespace PawCare {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    private:
        DatabaseManager^ db;
        String^ currentUser;
        String^ currentRole;

        System::Windows::Forms::Panel^ panelHeader;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblSubtitle;
        System::Windows::Forms::Panel^ panelNav;
        System::Windows::Forms::Button^ btnNavDashboard;
        System::Windows::Forms::Button^ btnNavVetPortal;
        System::Windows::Forms::Button^ btnNavReceptionPortal;
        System::Windows::Forms::Button^ btnNavOwners;
        System::Windows::Forms::Button^ btnNavPets;
        System::Windows::Forms::Button^ btnNavAppointments;
        System::Windows::Forms::Button^ btnNavMedical;
        System::Windows::Forms::Button^ btnNavBilling;
        System::Windows::Forms::Button^ btnNavLogout;
        System::Windows::Forms::Panel^ panelContent;

        System::Windows::Forms::GroupBox^ grpStats;
        System::Windows::Forms::Label^ lblTotalOwners;
        System::Windows::Forms::Label^ lblTotalPets;
        System::Windows::Forms::Label^ lblTotalAppointments;
        System::Windows::Forms::Label^ lblDbStatus;
        System::Windows::Forms::Button^ btnRefreshStats;
        System::Windows::Forms::Button^ btnOpenVetScreen;
        System::Windows::Forms::Button^ btnOpenReceptionScreen;
        System::Windows::Forms::DataGridView^ dgvRecentAppointments;

        bool isLoggedOut;

    public:
        property bool IsLoggedOut
        {
            bool get() { return isLoggedOut; }
        }

        property String^ CurrentRole
        {
            String^ get() { return currentRole; }
        }

        property String^ CurrentUser
        {
            String^ get() { return currentUser; }
        }

        MainForm(void)
        {
            isLoggedOut = false;
            currentUser = "Administrator";
            currentRole = "Administrator";
            db = gcnew DatabaseManager();
            InitializeComponent();
            ApplyRolePermissions();
            RefreshDashboard();
        }

        MainForm(String^ username, String^ role)
        {
            isLoggedOut = false;
            currentUser = username;
            currentRole = role;
            db = gcnew DatabaseManager();
            InitializeComponent();
            ApplyRolePermissions();
            RefreshDashboard();
        }

    protected:
        ~MainForm()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void SetupNavButton(Button^ btn, String^ text, int top)
        {
            btn->Text = text;
            btn->UseMnemonic = false;
            btn->Font = (gcnew System::Drawing::Font("Segoe UI", 10.5F, System::Drawing::FontStyle::Bold));
            btn->ForeColor = System::Drawing::Color::White;
            btn->BackColor = System::Drawing::Color::FromArgb(55, 71, 79);
            btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->Location = System::Drawing::Point(10, top);
            btn->Size = System::Drawing::Size(180, 45);
            btn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            btn->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
        }

        void InitializeComponent(void)
        {
            this->panelHeader = (gcnew System::Windows::Forms::Panel());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblSubtitle = (gcnew System::Windows::Forms::Label());
            this->panelNav = (gcnew System::Windows::Forms::Panel());
            this->btnNavDashboard = (gcnew System::Windows::Forms::Button());
            this->btnNavVetPortal = (gcnew System::Windows::Forms::Button());
            this->btnNavReceptionPortal = (gcnew System::Windows::Forms::Button());
            this->btnNavOwners = (gcnew System::Windows::Forms::Button());
            this->btnNavPets = (gcnew System::Windows::Forms::Button());
            this->btnNavAppointments = (gcnew System::Windows::Forms::Button());
            this->btnNavMedical = (gcnew System::Windows::Forms::Button());
            this->btnNavBilling = (gcnew System::Windows::Forms::Button());
            this->btnNavLogout = (gcnew System::Windows::Forms::Button());
            this->panelContent = (gcnew System::Windows::Forms::Panel());
            this->grpStats = (gcnew System::Windows::Forms::GroupBox());
            this->lblTotalOwners = (gcnew System::Windows::Forms::Label());
            this->lblTotalPets = (gcnew System::Windows::Forms::Label());
            this->lblTotalAppointments = (gcnew System::Windows::Forms::Label());
            this->lblDbStatus = (gcnew System::Windows::Forms::Label());
            this->btnRefreshStats = (gcnew System::Windows::Forms::Button());
            this->btnOpenVetScreen = (gcnew System::Windows::Forms::Button());
            this->btnOpenReceptionScreen = (gcnew System::Windows::Forms::Button());
            this->dgvRecentAppointments = (gcnew System::Windows::Forms::DataGridView());

            this->panelHeader->BackColor = System::Drawing::Color::FromArgb(33, 150, 243);
            this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
            this->panelHeader->Height = 80;
            this->panelHeader->Controls->Add(this->lblSubtitle);
            this->panelHeader->Controls->Add(this->lblTitle);

            this->lblTitle->Text = "PawCare - Pet Care Clinic Management System";
            this->lblTitle->Font = (gcnew System::Drawing::Font("Segoe UI", 16, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Location = System::Drawing::Point(20, 15);
            this->lblTitle->AutoSize = true;

            this->lblSubtitle->Text = "C++/CLI Object-Oriented Desktop Application with MySQL";
            this->lblSubtitle->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Regular));
            this->lblSubtitle->ForeColor = System::Drawing::Color::FromArgb(227, 242, 253);
            this->lblSubtitle->Location = System::Drawing::Point(22, 48);
            this->lblSubtitle->AutoSize = true;

            this->panelNav->BackColor = System::Drawing::Color::FromArgb(38, 50, 56);
            this->panelNav->Dock = System::Windows::Forms::DockStyle::Left;
            this->panelNav->Width = 200;
            this->panelNav->Controls->Add(this->btnNavLogout);
            this->panelNav->Controls->Add(this->btnNavBilling);
            this->panelNav->Controls->Add(this->btnNavMedical);
            this->panelNav->Controls->Add(this->btnNavAppointments);
            this->panelNav->Controls->Add(this->btnNavPets);
            this->panelNav->Controls->Add(this->btnNavOwners);
            this->panelNav->Controls->Add(this->btnNavReceptionPortal);
            this->panelNav->Controls->Add(this->btnNavVetPortal);
            this->panelNav->Controls->Add(this->btnNavDashboard);

            SetupNavButton(this->btnNavDashboard, "Dashboard", 15);
            SetupNavButton(this->btnNavVetPortal, "Vet Screen", 60);
            this->btnNavVetPortal->BackColor = System::Drawing::Color::FromArgb(0, 150, 136);

            SetupNavButton(this->btnNavReceptionPortal, "Reception Screen", 105);
            this->btnNavReceptionPortal->BackColor = System::Drawing::Color::FromArgb(230, 81, 0);

            SetupNavButton(this->btnNavOwners, "Manage Owners", 150);
            SetupNavButton(this->btnNavPets, "Manage Pets", 195);
            SetupNavButton(this->btnNavAppointments, "Appointments", 240);
            SetupNavButton(this->btnNavMedical, "Medical Records & Rx", 285);
            SetupNavButton(this->btnNavBilling, "Billing & Payments", 330);

            SetupNavButton(this->btnNavLogout, "Log Out", 385);
            this->btnNavLogout->BackColor = System::Drawing::Color::FromArgb(198, 40, 40);

            this->btnNavDashboard->Click += gcnew System::EventHandler(this, &MainForm::btnNavDashboard_Click);
            this->btnNavVetPortal->Click += gcnew System::EventHandler(this, &MainForm::btnNavVetPortal_Click);
            this->btnNavReceptionPortal->Click += gcnew System::EventHandler(this, &MainForm::btnNavReceptionPortal_Click);
            this->btnNavOwners->Click += gcnew System::EventHandler(this, &MainForm::btnNavOwners_Click);
            this->btnNavPets->Click += gcnew System::EventHandler(this, &MainForm::btnNavPets_Click);
            this->btnNavAppointments->Click += gcnew System::EventHandler(this, &MainForm::btnNavAppointments_Click);
            this->btnNavMedical->Click += gcnew System::EventHandler(this, &MainForm::btnNavMedical_Click);
            this->btnNavBilling->Click += gcnew System::EventHandler(this, &MainForm::btnNavBilling_Click);
            this->btnNavLogout->Click += gcnew System::EventHandler(this, &MainForm::btnNavLogout_Click);

            this->panelContent->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panelContent->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);
            this->panelContent->Padding = System::Windows::Forms::Padding(20);

            this->grpStats->Text = "Clinic Overview & Statistics";
            this->grpStats->Font = (gcnew System::Drawing::Font("Segoe UI", 11, System::Drawing::FontStyle::Bold));
            this->grpStats->Location = System::Drawing::Point(20, 20);
            this->grpStats->Size = System::Drawing::Size(760, 140);

            this->lblTotalOwners->Font = (gcnew System::Drawing::Font("Segoe UI", 10));
            this->lblTotalOwners->Location = System::Drawing::Point(20, 35);
            this->lblTotalOwners->AutoSize = true;

            this->lblTotalPets->Font = (gcnew System::Drawing::Font("Segoe UI", 10));
            this->lblTotalPets->Location = System::Drawing::Point(20, 65);
            this->lblTotalPets->AutoSize = true;

            this->lblTotalAppointments->Font = (gcnew System::Drawing::Font("Segoe UI", 10));
            this->lblTotalAppointments->Location = System::Drawing::Point(320, 35);
            this->lblTotalAppointments->AutoSize = true;

            this->lblDbStatus->Font = (gcnew System::Drawing::Font("Segoe UI", 10));
            this->lblDbStatus->Location = System::Drawing::Point(320, 65);
            this->lblDbStatus->AutoSize = true;

            this->btnRefreshStats->Text = "Refresh Data";
            this->btnRefreshStats->Font = (gcnew System::Drawing::Font("Segoe UI", 9));
            this->btnRefreshStats->Location = System::Drawing::Point(630, 95);
            this->btnRefreshStats->Size = System::Drawing::Size(110, 32);
            this->btnRefreshStats->Click += gcnew System::EventHandler(this, &MainForm::btnRefreshStats_Click);

            this->grpStats->Controls->Add(this->lblTotalOwners);
            this->grpStats->Controls->Add(this->lblTotalPets);
            this->grpStats->Controls->Add(this->lblTotalAppointments);
            this->grpStats->Controls->Add(this->lblDbStatus);
            this->grpStats->Controls->Add(this->btnRefreshStats);

            this->btnOpenVetScreen->Text = "OPEN VETERINARIAN SCREEN\n(Consultation Queue, Rx Prescriptions & Health Directory)";
            this->btnOpenVetScreen->UseMnemonic = false;
            this->btnOpenVetScreen->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnOpenVetScreen->ForeColor = System::Drawing::Color::White;
            this->btnOpenVetScreen->BackColor = System::Drawing::Color::FromArgb(0, 150, 136);
            this->btnOpenVetScreen->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnOpenVetScreen->FlatAppearance->BorderSize = 0;
            this->btnOpenVetScreen->Location = System::Drawing::Point(20, 175);
            this->btnOpenVetScreen->Size = System::Drawing::Size(370, 52);
            this->btnOpenVetScreen->Click += gcnew System::EventHandler(this, &MainForm::btnOpenVetScreen_Click);

            this->btnOpenReceptionScreen->Text = "OPEN RECEPTIONIST SCREEN\n(Client Onboarding, Pet Registration, Bookings & Invoicing)";
            this->btnOpenReceptionScreen->UseMnemonic = false;
            this->btnOpenReceptionScreen->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnOpenReceptionScreen->ForeColor = System::Drawing::Color::White;
            this->btnOpenReceptionScreen->BackColor = System::Drawing::Color::FromArgb(230, 81, 0);
            this->btnOpenReceptionScreen->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnOpenReceptionScreen->FlatAppearance->BorderSize = 0;
            this->btnOpenReceptionScreen->Location = System::Drawing::Point(410, 175);
            this->btnOpenReceptionScreen->Size = System::Drawing::Size(370, 52);
            this->btnOpenReceptionScreen->Click += gcnew System::EventHandler(this, &MainForm::btnOpenReceptionScreen_Click);

            this->dgvRecentAppointments->Location = System::Drawing::Point(20, 240);
            this->dgvRecentAppointments->Size = System::Drawing::Size(760, 320);
            this->dgvRecentAppointments->ReadOnly = true;
            this->dgvRecentAppointments->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvRecentAppointments->BackgroundColor = System::Drawing::Color::White;

            this->panelContent->Controls->Add(this->grpStats);
            this->panelContent->Controls->Add(this->btnOpenVetScreen);
            this->panelContent->Controls->Add(this->btnOpenReceptionScreen);
            this->panelContent->Controls->Add(this->dgvRecentAppointments);

            this->ClientSize = System::Drawing::Size(1000, 680);
            this->Text = "PawCare - Pet Care System";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Controls->Add(this->panelContent);
            this->Controls->Add(this->panelNav);
            this->Controls->Add(this->panelHeader);
        }

        void ApplyRolePermissions()
        {
            if (currentRole == "Veterinarian")
            {
                this->panelHeader->BackColor = System::Drawing::Color::FromArgb(0, 150, 136);
                this->lblTitle->Text = "PawCare - Clinical Veterinary Portal";
                this->lblSubtitle->Text = "Logged in: " + currentUser + " | Role: Veterinarian [Clinical Diagnostics & Rx]";

                this->btnNavDashboard->Visible = true;
                this->btnNavVetPortal->Visible = true;
                this->btnNavVetPortal->Text = ">> Vet Screen";
                this->btnNavReceptionPortal->Visible = false;
                this->btnNavPets->Visible = true;
                this->btnNavAppointments->Visible = true;
                this->btnNavMedical->Visible = true;

                this->btnNavOwners->Visible = false;
                this->btnNavBilling->Visible = true;
                this->btnNavBilling->Enabled = false;
                this->btnNavBilling->Text = "Billing [Restricted]";
                this->btnNavBilling->BackColor = System::Drawing::Color::FromArgb(70, 70, 70);

                this->btnOpenVetScreen->Visible = true;
                this->btnOpenVetScreen->Location = System::Drawing::Point(20, 175);
                this->btnOpenVetScreen->Width = 760;
                this->btnOpenReceptionScreen->Visible = false;

                this->btnNavDashboard->Top = 15;
                this->btnNavVetPortal->Top = 60;
                this->btnNavPets->Top = 110;
                this->btnNavAppointments->Top = 155;
                this->btnNavMedical->Top = 200;
                this->btnNavBilling->Top = 245;
                this->btnNavLogout->Top = 310;
            }
            else if (currentRole == "Receptionist")
            {
                this->panelHeader->BackColor = System::Drawing::Color::FromArgb(230, 81, 0);
                this->lblTitle->Text = "PawCare - Front Desk & Reception Portal";
                this->lblSubtitle->Text = "Logged in: " + currentUser + " | Role: Receptionist [Client Onboarding & Invoicing]";

                this->btnNavDashboard->Visible = true;
                this->btnNavReceptionPortal->Visible = true;
                this->btnNavReceptionPortal->Text = ">> Reception Screen";
                this->btnNavVetPortal->Visible = false;
                this->btnNavOwners->Visible = true;
                this->btnNavPets->Visible = true;
                this->btnNavAppointments->Visible = true;
                this->btnNavBilling->Visible = true;
                this->btnNavBilling->Enabled = true;
                this->btnNavBilling->Text = "Billing & Payments";
                this->btnNavBilling->BackColor = System::Drawing::Color::FromArgb(55, 71, 79);

                this->btnNavMedical->Visible = false;

                this->btnOpenReceptionScreen->Visible = true;
                this->btnOpenReceptionScreen->Location = System::Drawing::Point(20, 175);
                this->btnOpenReceptionScreen->Width = 760;
                this->btnOpenVetScreen->Visible = false;

                this->btnNavDashboard->Top = 15;
                this->btnNavReceptionPortal->Top = 60;
                this->btnNavOwners->Top = 110;
                this->btnNavPets->Top = 155;
                this->btnNavAppointments->Top = 200;
                this->btnNavBilling->Top = 245;
                this->btnNavLogout->Top = 310;
            }
            else
            {
                this->panelHeader->BackColor = System::Drawing::Color::FromArgb(33, 150, 243);
                this->lblTitle->Text = "PawCare - Clinic Management System";
                this->lblSubtitle->Text = "Logged in: " + currentUser + " | Role: Administrator [Full Access]";

                this->btnNavDashboard->Visible = true;
                this->btnNavVetPortal->Visible = true;
                this->btnNavReceptionPortal->Visible = true;
                this->btnNavOwners->Visible = true;
                this->btnNavPets->Visible = true;
                this->btnNavAppointments->Visible = true;
                this->btnNavMedical->Visible = true;
                this->btnNavBilling->Visible = true;
                this->btnNavBilling->Enabled = true;
                this->btnNavBilling->Text = "Billing & Payments";
                this->btnNavBilling->BackColor = System::Drawing::Color::FromArgb(55, 71, 79);

                this->btnOpenVetScreen->Visible = true;
                this->btnOpenVetScreen->Location = System::Drawing::Point(20, 175);
                this->btnOpenVetScreen->Width = 370;
                this->btnOpenReceptionScreen->Visible = true;
                this->btnOpenReceptionScreen->Location = System::Drawing::Point(410, 175);
                this->btnOpenReceptionScreen->Width = 370;

                this->btnNavDashboard->Top = 15;
                this->btnNavVetPortal->Top = 58;
                this->btnNavReceptionPortal->Top = 101;
                this->btnNavOwners->Top = 144;
                this->btnNavPets->Top = 187;
                this->btnNavAppointments->Top = 230;
                this->btnNavMedical->Top = 273;
                this->btnNavBilling->Top = 316;
                this->btnNavLogout->Top = 375;
            }
        }

        void RefreshDashboard()
        {
            try
            {
                bool connected = db->isConnected() || db->connect();
                this->lblDbStatus->Text = "Database: " + (connected ? "Connected (pawcare_db)" : "Offline (Local mode)");
                this->lblDbStatus->ForeColor = connected ? System::Drawing::Color::DarkGreen : System::Drawing::Color::DarkRed;

                if (connected)
                {
                    auto owners = db->getAllOwners();
                    auto pets = db->getAllPets();
                    auto appts = db->getAllAppointments();

                    int ownersCount = (owners != nullptr) ? owners->Count : 0;
                    int petsCount = (pets != nullptr) ? pets->Count : 0;
                    int apptsCount = (appts != nullptr) ? appts->Count : 0;

                    if (currentRole == "Veterinarian")
                    {
                        auto records = db->getAllMedicalRecords();
                        int recordsCount = (records != nullptr) ? records->Count : 0;
                        this->grpStats->Text = "Clinical Veterinary Overview (Dr. Care Portal)";
                        this->lblTotalOwners->Text = "Patients Under Care: " + petsCount.ToString();
                        this->lblTotalPets->Text = "Clinical Medical Records: " + recordsCount.ToString();
                        this->lblTotalAppointments->Text = "Scheduled Consultations: " + apptsCount.ToString();
                    }
                    else if (currentRole == "Receptionist")
                    {
                        this->grpStats->Text = "Front Desk & Reception Overview";
                        this->lblTotalOwners->Text = "Registered Owners: " + ownersCount.ToString();
                        this->lblTotalPets->Text = "Registered Pets: " + petsCount.ToString();
                        this->lblTotalAppointments->Text = "Appointments Scheduled: " + apptsCount.ToString();
                    }
                    else
                    {
                        this->grpStats->Text = "Clinic System Overview & Statistics";
                        this->lblTotalOwners->Text = "Registered Owners: " + ownersCount.ToString();
                        this->lblTotalPets->Text = "Registered Pets: " + petsCount.ToString();
                        this->lblTotalAppointments->Text = "Total Appointments: " + apptsCount.ToString();
                    }

                    DataTable^ dt = gcnew DataTable();
                    dt->Columns->Add("Appt ID");
                    dt->Columns->Add("Pet ID");
                    dt->Columns->Add("Vet ID");
                    dt->Columns->Add("Date");
                    dt->Columns->Add("Time");
                    dt->Columns->Add("Reason");
                    dt->Columns->Add("Status");

                    if (appts != nullptr)
                    {
                        for (int i = 0; i < appts->Count; i++)
                        {
                            PawCare::Appointment^ a = (PawCare::Appointment^)appts[i];
                            dt->Rows->Add(a->AppointmentID, a->PetID, a->VeterinarianID,
                                          a->AppointmentDate, a->AppointmentTime, a->Reason, a->Status);
                        }
                    }
                    this->dgvRecentAppointments->DataSource = dt;
                }
                else
                {
                    this->lblTotalOwners->Text = "Registered Owners: N/A";
                    this->lblTotalPets->Text = "Registered Pets: N/A";
                    this->lblTotalAppointments->Text = "Total Appointments: N/A";
                }
            }
            catch (Exception^ ex)
            {
                this->lblDbStatus->Text = "Database: Error (" + ex->Message + ")";
                this->lblDbStatus->ForeColor = System::Drawing::Color::Red;
            }
        }

        void btnRefreshStats_Click(System::Object^ sender, System::EventArgs^ e)
        {
            RefreshDashboard();
        }

        void btnNavDashboard_Click(System::Object^ sender, System::EventArgs^ e)
        {
            RefreshDashboard();
        }

        void btnNavVetPortal_Click(System::Object^ sender, System::EventArgs^ e)
        {
            VetPortalForm^ f = gcnew VetPortalForm(db);
            f->ShowDialog();
            RefreshDashboard();
        }

        void btnNavReceptionPortal_Click(System::Object^ sender, System::EventArgs^ e)
        {
            ReceptionistPortalForm^ f = gcnew ReceptionistPortalForm(db);
            f->ShowDialog();
            RefreshDashboard();
        }

        void btnOpenVetScreen_Click(System::Object^ sender, System::EventArgs^ e)
        {
            btnNavVetPortal_Click(sender, e);
        }

        void btnOpenReceptionScreen_Click(System::Object^ sender, System::EventArgs^ e)
        {
            btnNavReceptionPortal_Click(sender, e);
        }

        void btnNavOwners_Click(System::Object^ sender, System::EventArgs^ e)
        {
            OwnerForm^ f = gcnew OwnerForm(db);
            f->ShowDialog();
            RefreshDashboard();
        }

        void btnNavPets_Click(System::Object^ sender, System::EventArgs^ e)
        {
            PetForm^ f = gcnew PetForm(db);
            f->ShowDialog();
            RefreshDashboard();
        }

        void btnNavAppointments_Click(System::Object^ sender, System::EventArgs^ e)
        {
            AppointmentForm^ f = gcnew AppointmentForm(db);
            f->ShowDialog();
            RefreshDashboard();
        }

        void btnNavMedical_Click(System::Object^ sender, System::EventArgs^ e)
        {
            MedicalRecordForm^ f = gcnew MedicalRecordForm(db, currentRole);
            f->ShowDialog();
            RefreshDashboard();
        }

        void btnNavBilling_Click(System::Object^ sender, System::EventArgs^ e)
        {
            BillingForm^ f = gcnew BillingForm(db);
            f->ShowDialog();
            RefreshDashboard();
        }

        void btnNavLogout_Click(System::Object^ sender, System::EventArgs^ e)
        {
            System::Windows::Forms::DialogResult res = System::Windows::Forms::MessageBox::Show(
                "Are you sure you want to log out of PawCare?",
                "Confirm Logout",
                System::Windows::Forms::MessageBoxButtons::YesNo,
                System::Windows::Forms::MessageBoxIcon::Question
            );

            if (res == System::Windows::Forms::DialogResult::Yes)
            {
                this->isLoggedOut = true;
                this->Close();
            }
        }
    };
}
