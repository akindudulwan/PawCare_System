#pragma once
#include "Models/Pet.h"
#include "Models/Dog.h"
#include "Models/Cat.h"
#include "Models/Appointment.h"
#include "Models/MedicalRecord.h"
#include "Database/DatabaseManager.h"

namespace PawCare {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class VetPortalForm : public System::Windows::Forms::Form
    {
    private:
        DatabaseManager^ db;

        System::Windows::Forms::Panel^ panelHeader;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblSubtitle;

        System::Windows::Forms::TabControl^ tabControl;
        System::Windows::Forms::TabPage^ tabQueue;
        System::Windows::Forms::TabPage^ tabRx;
        System::Windows::Forms::TabPage^ tabPatients;

        System::Windows::Forms::DataGridView^ dgvQueue;
        System::Windows::Forms::Button^ btnStartConsult;
        System::Windows::Forms::Button^ btnCompleteConsult;
        System::Windows::Forms::Button^ btnRefreshQueue;

        System::Windows::Forms::Label^ lblRxPet;
        System::Windows::Forms::ComboBox^ cmbRxPet;
        System::Windows::Forms::Label^ lblRxAppt;
        System::Windows::Forms::ComboBox^ cmbRxAppt;
        System::Windows::Forms::Label^ lblRxDiag;
        System::Windows::Forms::TextBox^ txtRxDiag;
        System::Windows::Forms::Label^ lblRxTreat;
        System::Windows::Forms::TextBox^ txtRxTreat;
        System::Windows::Forms::Label^ lblRxVacc;
        System::Windows::Forms::TextBox^ txtRxVacc;
        System::Windows::Forms::Label^ lblRxNotes;
        System::Windows::Forms::TextBox^ txtRxNotes;
        System::Windows::Forms::Button^ btnSaveRx;
        System::Windows::Forms::Button^ btnClearRx;
        System::Windows::Forms::DataGridView^ dgvHistory;

        System::Windows::Forms::DataGridView^ dgvPatients;
        System::Windows::Forms::Button^ btnRefreshPatients;

    public:
        VetPortalForm(DatabaseManager^ dbManager)
        {
            db = dbManager;
            InitializeComponent();
            RefreshAllTabs();
        }

    protected:
        ~VetPortalForm()
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
            this->tabQueue = (gcnew System::Windows::Forms::TabPage());
            this->tabRx = (gcnew System::Windows::Forms::TabPage());
            this->tabPatients = (gcnew System::Windows::Forms::TabPage());

            this->dgvQueue = (gcnew System::Windows::Forms::DataGridView());
            this->btnStartConsult = (gcnew System::Windows::Forms::Button());
            this->btnCompleteConsult = (gcnew System::Windows::Forms::Button());
            this->btnRefreshQueue = (gcnew System::Windows::Forms::Button());

            this->lblRxPet = (gcnew System::Windows::Forms::Label());
            this->cmbRxPet = (gcnew System::Windows::Forms::ComboBox());
            this->lblRxAppt = (gcnew System::Windows::Forms::Label());
            this->cmbRxAppt = (gcnew System::Windows::Forms::ComboBox());
            this->lblRxDiag = (gcnew System::Windows::Forms::Label());
            this->txtRxDiag = (gcnew System::Windows::Forms::TextBox());
            this->lblRxTreat = (gcnew System::Windows::Forms::Label());
            this->txtRxTreat = (gcnew System::Windows::Forms::TextBox());
            this->lblRxVacc = (gcnew System::Windows::Forms::Label());
            this->txtRxVacc = (gcnew System::Windows::Forms::TextBox());
            this->lblRxNotes = (gcnew System::Windows::Forms::Label());
            this->txtRxNotes = (gcnew System::Windows::Forms::TextBox());
            this->btnSaveRx = (gcnew System::Windows::Forms::Button());
            this->btnClearRx = (gcnew System::Windows::Forms::Button());
            this->dgvHistory = (gcnew System::Windows::Forms::DataGridView());

            this->dgvPatients = (gcnew System::Windows::Forms::DataGridView());
            this->btnRefreshPatients = (gcnew System::Windows::Forms::Button());

            this->panelHeader->BackColor = System::Drawing::Color::FromArgb(0, 150, 136);
            this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
            this->panelHeader->Height = 75;
            this->panelHeader->Controls->Add(this->lblSubtitle);
            this->panelHeader->Controls->Add(this->lblTitle);

            this->lblTitle->Text = "Veterinarian Clinical Care Portal (Vet Screen)";
            this->lblTitle->Font = (gcnew System::Drawing::Font("Segoe UI", 15, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Location = System::Drawing::Point(20, 12);
            this->lblTitle->AutoSize = true;

            this->lblSubtitle->Text = "Dr. Silva (Chief Veterinarian) - Patient Queues, Clinical Diagnoses, Prescriptions (Rx) & Health Directory";
            this->lblSubtitle->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F));
            this->lblSubtitle->ForeColor = System::Drawing::Color::FromArgb(224, 242, 241);
            this->lblSubtitle->Location = System::Drawing::Point(22, 43);
            this->lblSubtitle->AutoSize = true;

            this->tabControl->Dock = System::Windows::Forms::DockStyle::Fill;
            this->tabControl->Font = (gcnew System::Drawing::Font("Segoe UI", 10));
            this->tabControl->Controls->Add(this->tabQueue);
            this->tabControl->Controls->Add(this->tabRx);
            this->tabControl->Controls->Add(this->tabPatients);

            this->tabQueue->Text = "Consultations & Appointment Queue";
            this->tabQueue->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);
            this->tabQueue->Padding = System::Windows::Forms::Padding(15);

            this->dgvQueue->Location = System::Drawing::Point(15, 15);
            this->dgvQueue->Size = System::Drawing::Size(920, 410);
            this->dgvQueue->ReadOnly = true;
            this->dgvQueue->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->dgvQueue->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvQueue->BackgroundColor = System::Drawing::Color::White;

            this->btnStartConsult->Text = "Start Consultation (Confirm)";
            this->btnStartConsult->Location = System::Drawing::Point(15, 435);
            this->btnStartConsult->Size = System::Drawing::Size(220, 36);
            this->btnStartConsult->BackColor = System::Drawing::Color::FromArgb(0, 150, 136);
            this->btnStartConsult->ForeColor = System::Drawing::Color::White;
            this->btnStartConsult->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnStartConsult->Click += gcnew System::EventHandler(this, &VetPortalForm::btnStartConsult_Click);

            this->btnCompleteConsult->Text = "Mark Consultation Completed";
            this->btnCompleteConsult->Location = System::Drawing::Point(250, 435);
            this->btnCompleteConsult->Size = System::Drawing::Size(230, 36);
            this->btnCompleteConsult->BackColor = System::Drawing::Color::FromArgb(46, 125, 50);
            this->btnCompleteConsult->ForeColor = System::Drawing::Color::White;
            this->btnCompleteConsult->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCompleteConsult->Click += gcnew System::EventHandler(this, &VetPortalForm::btnCompleteConsult_Click);

            this->btnRefreshQueue->Text = "Refresh Queue";
            this->btnRefreshQueue->Location = System::Drawing::Point(495, 435);
            this->btnRefreshQueue->Size = System::Drawing::Size(130, 36);
            this->btnRefreshQueue->Click += gcnew System::EventHandler(this, &VetPortalForm::btnRefreshQueue_Click);

            this->tabQueue->Controls->Add(this->dgvQueue);
            this->tabQueue->Controls->Add(this->btnStartConsult);
            this->tabQueue->Controls->Add(this->btnCompleteConsult);
            this->tabQueue->Controls->Add(this->btnRefreshQueue);

            this->tabRx->Text = "Diagnoses & Prescriptions (Rx)";
            this->tabRx->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);
            this->tabRx->Padding = System::Windows::Forms::Padding(15);

            this->lblRxPet->Text = "Select Patient (Pet) *";
            this->lblRxPet->Location = System::Drawing::Point(15, 15);
            this->lblRxPet->AutoSize = true;
            this->cmbRxPet->Location = System::Drawing::Point(15, 38);
            this->cmbRxPet->Size = System::Drawing::Size(280, 26);
            this->cmbRxPet->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbRxPet->SelectedIndexChanged += gcnew System::EventHandler(this, &VetPortalForm::cmbRxPet_SelectedIndexChanged);

            this->lblRxAppt->Text = "Linked Appointment *";
            this->lblRxAppt->Location = System::Drawing::Point(15, 75);
            this->lblRxAppt->AutoSize = true;
            this->cmbRxAppt->Location = System::Drawing::Point(15, 98);
            this->cmbRxAppt->Size = System::Drawing::Size(280, 26);
            this->cmbRxAppt->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

            this->lblRxDiag->Text = "Clinical Diagnosis *";
            this->lblRxDiag->Location = System::Drawing::Point(15, 135);
            this->lblRxDiag->AutoSize = true;
            this->txtRxDiag->Location = System::Drawing::Point(15, 158);
            this->txtRxDiag->Size = System::Drawing::Size(280, 26);

            this->lblRxTreat->Text = "Prescription & Medication (Rx) *";
            this->lblRxTreat->Location = System::Drawing::Point(15, 195);
            this->lblRxTreat->AutoSize = true;
            this->txtRxTreat->Location = System::Drawing::Point(15, 218);
            this->txtRxTreat->Size = System::Drawing::Size(280, 50);
            this->txtRxTreat->Multiline = true;

            this->lblRxVacc->Text = "Vaccination / Batch Details";
            this->lblRxVacc->Location = System::Drawing::Point(15, 280);
            this->lblRxVacc->AutoSize = true;
            this->txtRxVacc->Location = System::Drawing::Point(15, 303);
            this->txtRxVacc->Size = System::Drawing::Size(280, 26);

            this->lblRxNotes->Text = "Clinical Observations / Notes";
            this->lblRxNotes->Location = System::Drawing::Point(15, 340);
            this->lblRxNotes->AutoSize = true;
            this->txtRxNotes->Location = System::Drawing::Point(15, 363);
            this->txtRxNotes->Size = System::Drawing::Size(280, 45);
            this->txtRxNotes->Multiline = true;

            this->btnSaveRx->Text = "Save Clinical Record";
            this->btnSaveRx->Location = System::Drawing::Point(15, 425);
            this->btnSaveRx->Size = System::Drawing::Size(170, 36);
            this->btnSaveRx->BackColor = System::Drawing::Color::FromArgb(0, 150, 136);
            this->btnSaveRx->ForeColor = System::Drawing::Color::White;
            this->btnSaveRx->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnSaveRx->Click += gcnew System::EventHandler(this, &VetPortalForm::btnSaveRx_Click);

            this->btnClearRx->Text = "Clear";
            this->btnClearRx->Location = System::Drawing::Point(195, 425);
            this->btnClearRx->Size = System::Drawing::Size(100, 36);
            this->btnClearRx->Click += gcnew System::EventHandler(this, &VetPortalForm::btnClearRx_Click);

            this->dgvHistory->Location = System::Drawing::Point(315, 15);
            this->dgvHistory->Size = System::Drawing::Size(620, 450);
            this->dgvHistory->ReadOnly = true;
            this->dgvHistory->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvHistory->BackgroundColor = System::Drawing::Color::White;

            this->tabRx->Controls->Add(this->lblRxPet);
            this->tabRx->Controls->Add(this->cmbRxPet);
            this->tabRx->Controls->Add(this->lblRxAppt);
            this->tabRx->Controls->Add(this->cmbRxAppt);
            this->tabRx->Controls->Add(this->lblRxDiag);
            this->tabRx->Controls->Add(this->txtRxDiag);
            this->tabRx->Controls->Add(this->lblRxTreat);
            this->tabRx->Controls->Add(this->txtRxTreat);
            this->tabRx->Controls->Add(this->lblRxVacc);
            this->tabRx->Controls->Add(this->txtRxVacc);
            this->tabRx->Controls->Add(this->lblRxNotes);
            this->tabRx->Controls->Add(this->txtRxNotes);
            this->tabRx->Controls->Add(this->btnSaveRx);
            this->tabRx->Controls->Add(this->btnClearRx);
            this->tabRx->Controls->Add(this->dgvHistory);

            this->tabPatients->Text = "Patients (Dogs & Cats) Health Directory";
            this->tabPatients->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);
            this->tabPatients->Padding = System::Windows::Forms::Padding(15);

            this->dgvPatients->Location = System::Drawing::Point(15, 15);
            this->dgvPatients->Size = System::Drawing::Size(920, 410);
            this->dgvPatients->ReadOnly = true;
            this->dgvPatients->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvPatients->BackgroundColor = System::Drawing::Color::White;

            this->btnRefreshPatients->Text = "Refresh Directory";
            this->btnRefreshPatients->Location = System::Drawing::Point(15, 435);
            this->btnRefreshPatients->Size = System::Drawing::Size(180, 36);
            this->btnRefreshPatients->Click += gcnew System::EventHandler(this, &VetPortalForm::btnRefreshPatients_Click);

            this->tabPatients->Controls->Add(this->dgvPatients);
            this->tabPatients->Controls->Add(this->btnRefreshPatients);

            this->ClientSize = System::Drawing::Size(980, 600);
            this->Text = "PawCare - Veterinarian Clinical Portal";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->MinimizeBox = true;
            this->MaximizeBox = true;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;

            this->Controls->Add(this->tabControl);
            this->Controls->Add(this->panelHeader);
        }

        void RefreshAllTabs()
        {
            LoadQueue();
            LoadRxPets();
            LoadHistory();
            LoadPatients();
        }

        void LoadQueue()
        {
            try
            {
                if (!db->isConnected() && !db->connect()) return;
                auto list = db->getAllAppointments();
                DataTable^ dt = gcnew DataTable();
                dt->Columns->Add("Appt ID");
                dt->Columns->Add("Pet ID");
                dt->Columns->Add("Date");
                dt->Columns->Add("Time");
                dt->Columns->Add("Reason / Symptoms");
                dt->Columns->Add("Status");

                if (list != nullptr)
                {
                    for (int i = 0; i < list->Count; i++)
                    {
                        PawCare::Appointment^ a = (PawCare::Appointment^)list[i];
                        dt->Rows->Add(a->AppointmentID, a->PetID, a->AppointmentDate, a->AppointmentTime, a->Reason, a->Status);
                    }
                }
                this->dgvQueue->DataSource = dt;
            }
            catch (Exception^ ex)
            {
                Console::WriteLine("[VetPortal] LoadQueue error: " + ex->Message);
            }
        }

        void LoadRxPets()
        {
            try
            {
                cmbRxPet->Items->Clear();
                if (db->isConnected() || db->connect())
                {
                    auto list = db->getAllPets();
                    if (list != nullptr)
                    {
                        for (int i = 0; i < list->Count; i++)
                        {
                            PawCare::Pet^ p = (PawCare::Pet^)list[i];
                            cmbRxPet->Items->Add(p->PetID.ToString() + " - " + p->Name + " (" + p->PetType + ", " + p->Breed + ")");
                        }
                    }
                }
                if (cmbRxPet->Items->Count > 0) cmbRxPet->SelectedIndex = 0;
            }
            catch (Exception^ ex)
            {
                Console::WriteLine("[VetPortal] LoadRxPets error: " + ex->Message);
            }
        }

        int GetSelectedRxPetId()
        {
            if (cmbRxPet->SelectedIndex < 0 || cmbRxPet->SelectedItem == nullptr) return 0;
            String^ s = cmbRxPet->SelectedItem->ToString();
            int dash = s->IndexOf(" - ");
            if (dash > 0)
            {
                int id = 0;
                Int32::TryParse(s->Substring(0, dash)->Trim(), id);
                return id;
            }
            return 0;
        }

        void LoadRxAppts()
        {
            try
            {
                cmbRxAppt->Items->Clear();
                int petId = GetSelectedRxPetId();
                if (db->isConnected() || db->connect())
                {
                    auto list = (petId > 0) ? db->getAppointmentsByPetId(petId) : db->getAllAppointments();
                    if (list != nullptr)
                    {
                        for (int i = 0; i < list->Count; i++)
                        {
                            PawCare::Appointment^ a = (PawCare::Appointment^)list[i];
                            cmbRxAppt->Items->Add(a->AppointmentID.ToString() + " - " + a->AppointmentDate + " (" + a->Reason + ")");
                        }
                    }
                }
                if (cmbRxAppt->Items->Count > 0) cmbRxAppt->SelectedIndex = 0;
            }
            catch (Exception^ ex)
            {
                Console::WriteLine("[VetPortal] LoadRxAppts error: " + ex->Message);
            }
        }

        void LoadHistory()
        {
            try
            {
                if (!db->isConnected() && !db->connect()) return;
                auto list = db->getAllMedicalRecords();
                DataTable^ dt = gcnew DataTable();
                dt->Columns->Add("ID");
                dt->Columns->Add("Pet ID");
                dt->Columns->Add("Date");
                dt->Columns->Add("Diagnosis");
                dt->Columns->Add("Treatment / Rx");
                dt->Columns->Add("Vaccination");
                dt->Columns->Add("Notes");

                if (list != nullptr)
                {
                    for (int i = 0; i < list->Count; i++)
                    {
                        PawCare::MedicalRecord^ r = (PawCare::MedicalRecord^)list[i];
                        dt->Rows->Add(r->RecordID, r->PetID, r->RecordDate, r->Diagnosis, r->Treatment, r->Vaccination, r->Notes);
                    }
                }
                this->dgvHistory->DataSource = dt;
            }
            catch (Exception^ ex)
            {
                Console::WriteLine("[VetPortal] LoadHistory error: " + ex->Message);
            }
        }

        void LoadPatients()
        {
            try
            {
                if (!db->isConnected() && !db->connect()) return;
                auto list = db->getAllPets();
                DataTable^ dt = gcnew DataTable();
                dt->Columns->Add("Pet ID");
                dt->Columns->Add("Owner ID");
                dt->Columns->Add("Name");
                dt->Columns->Add("Species");
                dt->Columns->Add("Breed");
                dt->Columns->Add("Age");
                dt->Columns->Add("Gender");
                dt->Columns->Add("Standard Consult Fee (Rs.)");

                if (list != nullptr)
                {
                    for (int i = 0; i < list->Count; i++)
                    {
                        PawCare::Pet^ p = (PawCare::Pet^)list[i];
                        dt->Rows->Add(p->PetID, p->OwnerID, p->Name, p->PetType, p->Breed,
                                      p->Age, p->Gender, p->calculateConsultationFee().ToString("F2"));
                    }
                }
                this->dgvPatients->DataSource = dt;
            }
            catch (Exception^ ex)
            {
                Console::WriteLine("[VetPortal] LoadPatients error: " + ex->Message);
            }
        }

        void cmbRxPet_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            LoadRxAppts();
        }

        void btnStartConsult_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dgvQueue->SelectedRows->Count == 0)
            {
                MessageBox::Show("Please select an appointment from the queue to start consultation.", "Queue Notice", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }
            int apptId = Convert::ToInt32(dgvQueue->SelectedRows[0]->Cells["Appt ID"]->Value);
            bool ok = db->changeAppointmentStatus(apptId, Appointment::STATUS_CONFIRMED);
            if (ok)
            {
                MessageBox::Show("Appointment #" + apptId + " status updated to CONFIRMED (In Consultation).", "Consultation Started", MessageBoxButtons::OK, MessageBoxIcon::Information);
                LoadQueue();
            }
        }

        void btnCompleteConsult_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dgvQueue->SelectedRows->Count == 0)
            {
                MessageBox::Show("Please select an appointment from the queue to complete.", "Queue Notice", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }
            int apptId = Convert::ToInt32(dgvQueue->SelectedRows[0]->Cells["Appt ID"]->Value);
            bool ok = db->changeAppointmentStatus(apptId, Appointment::STATUS_COMPLETED);
            if (ok)
            {
                MessageBox::Show("Appointment #" + apptId + " marked as COMPLETED. Ready for front-desk billing.", "Consultation Finished", MessageBoxButtons::OK, MessageBoxIcon::Information);
                LoadQueue();
            }
        }

        void btnRefreshQueue_Click(System::Object^ sender, System::EventArgs^ e)
        {
            LoadQueue();
        }

        void btnSaveRx_Click(System::Object^ sender, System::EventArgs^ e)
        {
            try
            {
                int petId = GetSelectedRxPetId();
                if (petId <= 0)
                {
                    MessageBox::Show("Please select a pet.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                int apptId = 0;
                if (cmbRxAppt->SelectedItem != nullptr)
                {
                    String^ s = cmbRxAppt->SelectedItem->ToString();
                    int dash = s->IndexOf(" - ");
                    if (dash > 0) Int32::TryParse(s->Substring(0, dash)->Trim(), apptId);
                }

                String^ diag = txtRxDiag->Text->Trim();
                String^ treat = txtRxTreat->Text->Trim();

                if (String::IsNullOrWhiteSpace(diag))
                {
                    MessageBox::Show("Clinical diagnosis is required.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    txtRxDiag->Focus();
                    return;
                }
                if (String::IsNullOrWhiteSpace(treat))
                {
                    MessageBox::Show("Prescription and treatment are required.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    txtRxTreat->Focus();
                    return;
                }

                MedicalRecord^ r = gcnew MedicalRecord();
                r->PetID = petId;
                r->AppointmentID = apptId;
                r->RecordDate = DateTime::Now.ToString("yyyy-MM-dd");
                r->Diagnosis = diag;
                r->Treatment = treat;
                r->Vaccination = txtRxVacc->Text->Trim();
                r->Notes = txtRxNotes->Text->Trim();

                if (db->insertMedicalRecord(r))
                {
                    MessageBox::Show("Prescription & medical record saved successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    btnClearRx_Click(nullptr, nullptr);
                    LoadHistory();
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void btnClearRx_Click(System::Object^ sender, System::EventArgs^ e)
        {
            txtRxDiag->Text = "";
            txtRxTreat->Text = "";
            txtRxVacc->Text = "";
            txtRxNotes->Text = "";
        }

        void btnRefreshPatients_Click(System::Object^ sender, System::EventArgs^ e)
        {
            LoadPatients();
        }
    };
}
