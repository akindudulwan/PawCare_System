#pragma once
#include "Models/Owner.h"
#include "Models/Pet.h"
#include "Models/Dog.h"
#include "Models/Cat.h"
#include "Models/Appointment.h"
#include "Models/Payment.h"
#include "Database/DatabaseManager.h"
#include "OwnerForm.h"
#include "PetForm.h"
#include "AppointmentForm.h"
#include "BillingForm.h"

namespace PawCare {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class ReceptionistPortalForm : public System::Windows::Forms::Form
    {
    private:
        DatabaseManager^ db;

        System::Windows::Forms::Panel^ panelHeader;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblSubtitle;

        System::Windows::Forms::TabControl^ tabControl;
        System::Windows::Forms::TabPage^ tabOverview;
        System::Windows::Forms::TabPage^ tabOwners;
        System::Windows::Forms::TabPage^ tabPets;
        System::Windows::Forms::TabPage^ tabAppointments;
        System::Windows::Forms::TabPage^ tabBilling;

        System::Windows::Forms::Button^ btnLaunchOwner;
        System::Windows::Forms::Button^ btnLaunchPet;
        System::Windows::Forms::Button^ btnLaunchAppt;
        System::Windows::Forms::Button^ btnLaunchBilling;
        System::Windows::Forms::DataGridView^ dgvOverviewAppts;

        System::Windows::Forms::DataGridView^ dgvOwners;
        System::Windows::Forms::DataGridView^ dgvPets;
        System::Windows::Forms::DataGridView^ dgvAppointments;
        System::Windows::Forms::DataGridView^ dgvPayments;

        System::Windows::Forms::Button^ btnRefreshAll;

    public:
        ReceptionistPortalForm(DatabaseManager^ dbManager)
        {
            db = dbManager;
            InitializeComponent();
            RefreshData();
        }

    protected:
        ~ReceptionistPortalForm()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->panelHeader = (gcnew System::Windows::Forms::Panel());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblSubtitle = (gcnew System::Windows::Forms::Label());

            this->tabControl = (gcnew System::Windows::Forms::TabControl());
            this->tabOverview = (gcnew System::Windows::Forms::TabPage());
            this->tabOwners = (gcnew System::Windows::Forms::TabPage());
            this->tabPets = (gcnew System::Windows::Forms::TabPage());
            this->tabAppointments = (gcnew System::Windows::Forms::TabPage());
            this->tabBilling = (gcnew System::Windows::Forms::TabPage());

            this->btnLaunchOwner = (gcnew System::Windows::Forms::Button());
            this->btnLaunchPet = (gcnew System::Windows::Forms::Button());
            this->btnLaunchAppt = (gcnew System::Windows::Forms::Button());
            this->btnLaunchBilling = (gcnew System::Windows::Forms::Button());
            this->btnRefreshAll = (gcnew System::Windows::Forms::Button());
            this->dgvOverviewAppts = (gcnew System::Windows::Forms::DataGridView());

            this->dgvOwners = (gcnew System::Windows::Forms::DataGridView());
            this->dgvPets = (gcnew System::Windows::Forms::DataGridView());
            this->dgvAppointments = (gcnew System::Windows::Forms::DataGridView());
            this->dgvPayments = (gcnew System::Windows::Forms::DataGridView());

            this->panelHeader->BackColor = System::Drawing::Color::FromArgb(230, 81, 0);
            this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
            this->panelHeader->Height = 75;
            this->panelHeader->Controls->Add(this->lblSubtitle);
            this->panelHeader->Controls->Add(this->lblTitle);

            this->lblTitle->Text = "Receptionist Front Desk Portal (Receptionist Screen)";
            this->lblTitle->Font = (gcnew System::Drawing::Font("Segoe UI", 15, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Location = System::Drawing::Point(20, 12);
            this->lblTitle->AutoSize = true;

            this->lblSubtitle->Text = "Front Desk & Receptionist - Client Registration, Pet Onboarding, Bookings & Invoicing";
            this->lblSubtitle->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F));
            this->lblSubtitle->ForeColor = System::Drawing::Color::FromArgb(255, 224, 178);
            this->lblSubtitle->Location = System::Drawing::Point(22, 43);
            this->lblSubtitle->AutoSize = true;

            this->tabControl->Dock = System::Windows::Forms::DockStyle::Fill;
            this->tabControl->Font = (gcnew System::Drawing::Font("Segoe UI", 10));
            this->tabControl->Controls->Add(this->tabOverview);
            this->tabControl->Controls->Add(this->tabOwners);
            this->tabControl->Controls->Add(this->tabPets);
            this->tabControl->Controls->Add(this->tabAppointments);
            this->tabControl->Controls->Add(this->tabBilling);

            this->tabOverview->Text = "Front Desk Dashboard";
            this->tabOverview->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);
            this->tabOverview->Padding = System::Windows::Forms::Padding(15);

            SetupQuickButton(this->btnLaunchOwner, "+ Register Client / Owner", 15, 20, System::Drawing::Color::FromArgb(33, 150, 243));
            SetupQuickButton(this->btnLaunchPet, "+ Register Pet (Dog / Cat)", 245, 20, System::Drawing::Color::FromArgb(0, 150, 136));
            SetupQuickButton(this->btnLaunchAppt, "+ Book / Schedule Appointment", 475, 20, System::Drawing::Color::FromArgb(103, 58, 183));
            SetupQuickButton(this->btnLaunchBilling, "+ Generate Bill & Payment", 705, 20, System::Drawing::Color::FromArgb(230, 81, 0));

            this->btnLaunchOwner->Click += gcnew System::EventHandler(this, &ReceptionistPortalForm::btnLaunchOwner_Click);
            this->btnLaunchPet->Click += gcnew System::EventHandler(this, &ReceptionistPortalForm::btnLaunchPet_Click);
            this->btnLaunchAppt->Click += gcnew System::EventHandler(this, &ReceptionistPortalForm::btnLaunchAppt_Click);
            this->btnLaunchBilling->Click += gcnew System::EventHandler(this, &ReceptionistPortalForm::btnLaunchBilling_Click);

            this->dgvOverviewAppts->Location = System::Drawing::Point(15, 80);
            this->dgvOverviewAppts->Size = System::Drawing::Size(915, 380);
            this->dgvOverviewAppts->ReadOnly = true;
            this->dgvOverviewAppts->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvOverviewAppts->BackgroundColor = System::Drawing::Color::White;

            this->tabOverview->Controls->Add(this->btnLaunchOwner);
            this->tabOverview->Controls->Add(this->btnLaunchPet);
            this->tabOverview->Controls->Add(this->btnLaunchAppt);
            this->tabOverview->Controls->Add(this->btnLaunchBilling);
            this->tabOverview->Controls->Add(this->dgvOverviewAppts);

            this->tabOwners->Text = "Registered Owners";
            this->tabOwners->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);
            this->tabOwners->Padding = System::Windows::Forms::Padding(15);
            SetupGrid(this->dgvOwners, this->tabOwners);

            this->tabPets->Text = "Registered Pets (Dogs & Cats)";
            this->tabPets->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);
            this->tabPets->Padding = System::Windows::Forms::Padding(15);
            SetupGrid(this->dgvPets, this->tabPets);

            this->tabAppointments->Text = "All Scheduled Appointments";
            this->tabAppointments->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);
            this->tabAppointments->Padding = System::Windows::Forms::Padding(15);
            SetupGrid(this->dgvAppointments, this->tabAppointments);

            this->tabBilling->Text = "Invoices & Payments";
            this->tabBilling->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);
            this->tabBilling->Padding = System::Windows::Forms::Padding(15);
            SetupGrid(this->dgvPayments, this->tabBilling);

            this->ClientSize = System::Drawing::Size(975, 600);
            this->Text = "PawCare - Receptionist Front Desk Portal";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->MinimizeBox = true;
            this->MaximizeBox = true;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;

            this->Controls->Add(this->tabControl);
            this->Controls->Add(this->panelHeader);
        }

        void SetupQuickButton(Button^ btn, String^ text, int left, int top, System::Drawing::Color color)
        {
            btn->Text = text;
            btn->UseMnemonic = false;
            btn->Location = System::Drawing::Point(left, top);
            btn->Size = System::Drawing::Size(220, 42);
            btn->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            btn->ForeColor = System::Drawing::Color::White;
            btn->BackColor = color;
            btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
        }

        void SetupGrid(DataGridView^ dgv, TabPage^ page)
        {
            dgv->Location = System::Drawing::Point(15, 15);
            dgv->Size = System::Drawing::Size(915, 450);
            dgv->ReadOnly = true;
            dgv->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            dgv->BackgroundColor = System::Drawing::Color::White;
            page->Controls->Add(dgv);
        }

        void RefreshData()
        {
            try
            {
                if (!db->isConnected() && !db->connect()) return;

                auto appts = db->getAllAppointments();
                DataTable^ dtAppts = gcnew DataTable();
                dtAppts->Columns->Add("Appt ID");
                dtAppts->Columns->Add("Pet ID");
                dtAppts->Columns->Add("Vet ID");
                dtAppts->Columns->Add("Date");
                dtAppts->Columns->Add("Time");
                dtAppts->Columns->Add("Reason");
                dtAppts->Columns->Add("Status");
                if (appts != nullptr)
                {
                    for (int i = 0; i < appts->Count; i++)
                    {
                        PawCare::Appointment^ a = (PawCare::Appointment^)appts[i];
                        dtAppts->Rows->Add(a->AppointmentID, a->PetID, a->VeterinarianID, a->AppointmentDate, a->AppointmentTime, a->Reason, a->Status);
                    }
                }
                this->dgvOverviewAppts->DataSource = dtAppts;
                this->dgvAppointments->DataSource = dtAppts;

                auto owners = db->getAllOwners();
                DataTable^ dtOwners = gcnew DataTable();
                dtOwners->Columns->Add("Owner ID");
                dtOwners->Columns->Add("Name");
                dtOwners->Columns->Add("Telephone");
                dtOwners->Columns->Add("Email");
                dtOwners->Columns->Add("Address");
                if (owners != nullptr)
                {
                    for (int i = 0; i < owners->Count; i++)
                    {
                        PawCare::Owner^ o = (PawCare::Owner^)owners[i];
                        dtOwners->Rows->Add(o->OwnerID, o->Name, o->Telephone, o->Email, o->Address);
                    }
                }
                this->dgvOwners->DataSource = dtOwners;

                auto pets = db->getAllPets();
                DataTable^ dtPets = gcnew DataTable();
                dtPets->Columns->Add("Pet ID");
                dtPets->Columns->Add("Owner ID");
                dtPets->Columns->Add("Name");
                dtPets->Columns->Add("Species");
                dtPets->Columns->Add("Breed");
                dtPets->Columns->Add("Age");
                dtPets->Columns->Add("Gender");
                dtPets->Columns->Add("Standard Consult Fee (Rs.)");
                if (pets != nullptr)
                {
                    for (int i = 0; i < pets->Count; i++)
                    {
                        PawCare::Pet^ p = (PawCare::Pet^)pets[i];
                        dtPets->Rows->Add(p->PetID, p->OwnerID, p->Name, p->PetType, p->Breed, p->Age, p->Gender, p->calculateConsultationFee().ToString("F2"));
                    }
                }
                this->dgvPets->DataSource = dtPets;
            }
            catch (Exception^ ex)
            {
                Console::WriteLine("[ReceptionPortal] RefreshData error: " + ex->Message);
            }
        }

        void btnLaunchOwner_Click(System::Object^ sender, System::EventArgs^ e)
        {
            OwnerForm^ f = gcnew OwnerForm(db);
            f->ShowDialog();
            RefreshData();
        }

        void btnLaunchPet_Click(System::Object^ sender, System::EventArgs^ e)
        {
            PetForm^ f = gcnew PetForm(db);
            f->ShowDialog();
            RefreshData();
        }

        void btnLaunchAppt_Click(System::Object^ sender, System::EventArgs^ e)
        {
            AppointmentForm^ f = gcnew AppointmentForm(db);
            f->ShowDialog();
            RefreshData();
        }

        void btnLaunchBilling_Click(System::Object^ sender, System::EventArgs^ e)
        {
            BillingForm^ f = gcnew BillingForm(db);
            f->ShowDialog();
            RefreshData();
        }
    };
}
