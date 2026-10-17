#pragma once
#include "Models/MedicalRecord.h"
#include "Models/Pet.h"
#include "Models/Appointment.h"
#include "Database/DatabaseManager.h"

namespace PawCare {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MedicalRecordForm : public System::Windows::Forms::Form
    {
    private:
        DatabaseManager^ db;
        String^ userRole;

        System::Windows::Forms::Panel^ panelHeader;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblSubtitle;

        System::Windows::Forms::Label^ lblPet;
        System::Windows::Forms::ComboBox^ cmbPet;
        System::Windows::Forms::Label^ lblAppointment;
        System::Windows::Forms::ComboBox^ cmbAppointment;

        System::Windows::Forms::Label^ lblDate;
        System::Windows::Forms::DateTimePicker^ dtpRecordDate;

        System::Windows::Forms::Label^ lblDiagnosis;
        System::Windows::Forms::TextBox^ txtDiagnosis;

        System::Windows::Forms::Label^ lblTreatment;
        System::Windows::Forms::TextBox^ txtTreatment;

        System::Windows::Forms::Label^ lblVaccination;
        System::Windows::Forms::TextBox^ txtVaccination;

        System::Windows::Forms::Label^ lblNotes;
        System::Windows::Forms::TextBox^ txtNotes;

        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnClear;
        System::Windows::Forms::Button^ btnRefresh;

        System::Windows::Forms::Label^ lblFilter;
        System::Windows::Forms::TextBox^ txtSearch;
        System::Windows::Forms::DataGridView^ dgvRecords;

        int selectedRecordId;

    public:
        MedicalRecordForm(DatabaseManager^ dbManager, String^ role)
        {
            db = dbManager;
            userRole = role;
            selectedRecordId = 0;
            InitializeComponent();
            LoadPets();
            LoadAppointments();
            LoadRecords();
        }

    protected:
        ~MedicalRecordForm()
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

            this->lblPet = (gcnew System::Windows::Forms::Label());
            this->cmbPet = (gcnew System::Windows::Forms::ComboBox());
            this->lblAppointment = (gcnew System::Windows::Forms::Label());
            this->cmbAppointment = (gcnew System::Windows::Forms::ComboBox());
            this->lblDate = (gcnew System::Windows::Forms::Label());
            this->dtpRecordDate = (gcnew System::Windows::Forms::DateTimePicker());

            this->lblDiagnosis = (gcnew System::Windows::Forms::Label());
            this->txtDiagnosis = (gcnew System::Windows::Forms::TextBox());
            this->lblTreatment = (gcnew System::Windows::Forms::Label());
            this->txtTreatment = (gcnew System::Windows::Forms::TextBox());
            this->lblVaccination = (gcnew System::Windows::Forms::Label());
            this->txtVaccination = (gcnew System::Windows::Forms::TextBox());
            this->lblNotes = (gcnew System::Windows::Forms::Label());
            this->txtNotes = (gcnew System::Windows::Forms::TextBox());

            this->btnSave = (gcnew System::Windows::Forms::Button());
            this->btnClear = (gcnew System::Windows::Forms::Button());
            this->btnRefresh = (gcnew System::Windows::Forms::Button());

            this->lblFilter = (gcnew System::Windows::Forms::Label());
            this->txtSearch = (gcnew System::Windows::Forms::TextBox());
            this->dgvRecords = (gcnew System::Windows::Forms::DataGridView());

            this->panelHeader->BackColor = System::Drawing::Color::FromArgb(0, 150, 136);
            this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
            this->panelHeader->Height = 70;
            this->panelHeader->Controls->Add(this->lblSubtitle);
            this->panelHeader->Controls->Add(this->lblTitle);

            this->lblTitle->Text = "Clinical Medical Records & Prescriptions (Rx)";
            this->lblTitle->Font = (gcnew System::Drawing::Font("Segoe UI", 14, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Location = System::Drawing::Point(20, 12);
            this->lblTitle->AutoSize = true;

            this->lblSubtitle->Text = "Veterinarian Clinical Diagnostic & Treatment Management (OOP Encapsulated)";
            this->lblSubtitle->Font = (gcnew System::Drawing::Font("Segoe UI", 9.0F, System::Drawing::FontStyle::Regular));
            this->lblSubtitle->ForeColor = System::Drawing::Color::FromArgb(224, 242, 241);
            this->lblSubtitle->Location = System::Drawing::Point(22, 40);
            this->lblSubtitle->AutoSize = true;

            this->lblPet->Text = "Select Patient (Pet) *";
            this->lblPet->Font = (gcnew System::Drawing::Font("Segoe UI", 9.0F, System::Drawing::FontStyle::Bold));
            this->lblPet->Location = System::Drawing::Point(20, 85);
            this->lblPet->AutoSize = true;
            this->cmbPet->Location = System::Drawing::Point(20, 105);
            this->cmbPet->Size = System::Drawing::Size(280, 25);
            this->cmbPet->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbPet->SelectedIndexChanged += gcnew System::EventHandler(this, &MedicalRecordForm::cmbPet_SelectedIndexChanged);

            this->lblAppointment->Text = "Linked Appointment *";
            this->lblAppointment->Font = (gcnew System::Drawing::Font("Segoe UI", 9.0F, System::Drawing::FontStyle::Bold));
            this->lblAppointment->Location = System::Drawing::Point(20, 140);
            this->lblAppointment->AutoSize = true;
            this->cmbAppointment->Location = System::Drawing::Point(20, 160);
            this->cmbAppointment->Size = System::Drawing::Size(280, 25);
            this->cmbAppointment->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

            this->lblDate->Text = "Record / Exam Date *";
            this->lblDate->Font = (gcnew System::Drawing::Font("Segoe UI", 9.0F, System::Drawing::FontStyle::Bold));
            this->lblDate->Location = System::Drawing::Point(20, 195);
            this->lblDate->AutoSize = true;
            this->dtpRecordDate->Location = System::Drawing::Point(20, 215);
            this->dtpRecordDate->Size = System::Drawing::Size(280, 25);
            this->dtpRecordDate->Format = System::Windows::Forms::DateTimePickerFormat::Short;

            this->lblDiagnosis->Text = "Clinical Diagnosis *";
            this->lblDiagnosis->Font = (gcnew System::Drawing::Font("Segoe UI", 9.0F, System::Drawing::FontStyle::Bold));
            this->lblDiagnosis->Location = System::Drawing::Point(20, 250);
            this->lblDiagnosis->AutoSize = true;
            this->txtDiagnosis->Location = System::Drawing::Point(20, 270);
            this->txtDiagnosis->Size = System::Drawing::Size(280, 25);

            this->lblTreatment->Text = "Prescription & Treatment *";
            this->lblTreatment->Font = (gcnew System::Drawing::Font("Segoe UI", 9.0F, System::Drawing::FontStyle::Bold));
            this->lblTreatment->Location = System::Drawing::Point(20, 305);
            this->lblTreatment->AutoSize = true;
            this->txtTreatment->Location = System::Drawing::Point(20, 325);
            this->txtTreatment->Size = System::Drawing::Size(280, 50);
            this->txtTreatment->Multiline = true;

            this->lblVaccination->Text = "Vaccination / Immunization";
            this->lblVaccination->Font = (gcnew System::Drawing::Font("Segoe UI", 9.0F, System::Drawing::FontStyle::Bold));
            this->lblVaccination->Location = System::Drawing::Point(20, 385);
            this->lblVaccination->AutoSize = true;
            this->txtVaccination->Location = System::Drawing::Point(20, 405);
            this->txtVaccination->Size = System::Drawing::Size(280, 25);

            this->lblNotes->Text = "Clinical Notes & Observations";
            this->lblNotes->Font = (gcnew System::Drawing::Font("Segoe UI", 9.0F, System::Drawing::FontStyle::Bold));
            this->lblNotes->Location = System::Drawing::Point(20, 440);
            this->lblNotes->AutoSize = true;
            this->txtNotes->Location = System::Drawing::Point(20, 460);
            this->txtNotes->Size = System::Drawing::Size(280, 45);
            this->txtNotes->Multiline = true;

            this->btnSave->Text = "Save Clinical Record";
            this->btnSave->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnSave->ForeColor = System::Drawing::Color::White;
            this->btnSave->BackColor = System::Drawing::Color::FromArgb(0, 150, 136);
            this->btnSave->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnSave->FlatAppearance->BorderSize = 0;
            this->btnSave->Location = System::Drawing::Point(20, 520);
            this->btnSave->Size = System::Drawing::Size(155, 36);
            this->btnSave->Click += gcnew System::EventHandler(this, &MedicalRecordForm::btnSave_Click);

            this->btnClear->Text = "Clear";
            this->btnClear->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnClear->ForeColor = System::Drawing::Color::White;
            this->btnClear->BackColor = System::Drawing::Color::FromArgb(120, 144, 156);
            this->btnClear->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnClear->FlatAppearance->BorderSize = 0;
            this->btnClear->Location = System::Drawing::Point(185, 520);
            this->btnClear->Size = System::Drawing::Size(115, 36);
            this->btnClear->Click += gcnew System::EventHandler(this, &MedicalRecordForm::btnClear_Click);

            this->lblFilter->Text = "Filter by Diagnosis / Pet ID:";
            this->lblFilter->Font = (gcnew System::Drawing::Font("Segoe UI", 9.0F, System::Drawing::FontStyle::Bold));
            this->lblFilter->Location = System::Drawing::Point(330, 85);
            this->lblFilter->AutoSize = true;

            this->txtSearch->Location = System::Drawing::Point(510, 82);
            this->txtSearch->Size = System::Drawing::Size(260, 25);
            this->txtSearch->TextChanged += gcnew System::EventHandler(this, &MedicalRecordForm::txtSearch_TextChanged);

            this->btnRefresh->Text = "Refresh";
            this->btnRefresh->Font = (gcnew System::Drawing::Font("Segoe UI", 9.0F));
            this->btnRefresh->Location = System::Drawing::Point(780, 80);
            this->btnRefresh->Size = System::Drawing::Size(90, 28);
            this->btnRefresh->Click += gcnew System::EventHandler(this, &MedicalRecordForm::btnRefresh_Click);

            this->dgvRecords->Location = System::Drawing::Point(330, 115);
            this->dgvRecords->Size = System::Drawing::Size(620, 440);
            this->dgvRecords->ReadOnly = true;
            this->dgvRecords->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->dgvRecords->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvRecords->BackgroundColor = System::Drawing::Color::White;
            this->dgvRecords->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MedicalRecordForm::dgvRecords_CellClick);

            this->ClientSize = System::Drawing::Size(975, 580);
            this->Text = "PawCare - Veterinary Clinical Medical Records";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->MinimizeBox = true;
            this->MaximizeBox = true;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;

            this->Controls->Add(this->panelHeader);
            this->Controls->Add(this->lblPet);
            this->Controls->Add(this->cmbPet);
            this->Controls->Add(this->lblAppointment);
            this->Controls->Add(this->cmbAppointment);
            this->Controls->Add(this->lblDate);
            this->Controls->Add(this->dtpRecordDate);
            this->Controls->Add(this->lblDiagnosis);
            this->Controls->Add(this->txtDiagnosis);
            this->Controls->Add(this->lblTreatment);
            this->Controls->Add(this->txtTreatment);
            this->Controls->Add(this->lblVaccination);
            this->Controls->Add(this->txtVaccination);
            this->Controls->Add(this->lblNotes);
            this->Controls->Add(this->txtNotes);
            this->Controls->Add(this->btnSave);
            this->Controls->Add(this->btnClear);
            this->Controls->Add(this->lblFilter);
            this->Controls->Add(this->txtSearch);
            this->Controls->Add(this->btnRefresh);
            this->Controls->Add(this->dgvRecords);
        }

        void LoadPets()
        {
            cmbPet->Items->Clear();
            if (db->isConnected() || db->connect())
            {
                auto list = db->getAllPets();
                for (int i = 0; i < list->Count; i++)
                {
                    PawCare::Pet^ p = (PawCare::Pet^)list[i];
                    cmbPet->Items->Add(p->PetID.ToString() + " - " + p->Name + " (" + p->PetType + ", " + p->Breed + ")");
                }
            }
            if (cmbPet->Items->Count > 0) cmbPet->SelectedIndex = 0;
        }

        void LoadAppointments()
        {
            cmbAppointment->Items->Clear();
            int petId = GetSelectedPetId();
            if (db->isConnected() || db->connect())
            {
                auto list = (petId > 0) ? db->getAppointmentsByPetId(petId) : db->getAllAppointments();
                for (int i = 0; i < list->Count; i++)
                {
                    PawCare::Appointment^ a = (PawCare::Appointment^)list[i];
                    cmbAppointment->Items->Add(a->AppointmentID.ToString() + " - " + a->AppointmentDate + " (" + a->Reason + ")");
                }
            }
            if (cmbAppointment->Items->Count > 0) cmbAppointment->SelectedIndex = 0;
        }

        int GetSelectedPetId()
        {
            if (cmbPet->SelectedIndex < 0 || cmbPet->SelectedItem == nullptr) return 0;
            String^ sel = cmbPet->SelectedItem->ToString();
            int dashIdx = sel->IndexOf(" - ");
            if (dashIdx > 0)
            {
                int id = 0;
                Int32::TryParse(sel->Substring(0, dashIdx)->Trim(), id);
                return id;
            }
            return 0;
        }

        int GetSelectedAppointmentId()
        {
            if (cmbAppointment->SelectedIndex < 0 || cmbAppointment->SelectedItem == nullptr) return 0;
            String^ sel = cmbAppointment->SelectedItem->ToString();
            int dashIdx = sel->IndexOf(" - ");
            if (dashIdx > 0)
            {
                int id = 0;
                Int32::TryParse(sel->Substring(0, dashIdx)->Trim(), id);
                return id;
            }
            return 0;
        }

        void LoadRecords()
        {
            if (!db->isConnected() && !db->connect()) return;

            auto records = db->getAllMedicalRecords();
            DataTable^ dt = gcnew DataTable();
            dt->Columns->Add("Record ID");
            dt->Columns->Add("Pet ID");
            dt->Columns->Add("Appt ID");
            dt->Columns->Add("Exam Date");
            dt->Columns->Add("Diagnosis");
            dt->Columns->Add("Treatment / Rx");
            dt->Columns->Add("Vaccination");
            dt->Columns->Add("Notes");

            String^ search = txtSearch->Text->Trim()->ToLower();

            for (int i = 0; i < records->Count; i++)
            {
                PawCare::MedicalRecord^ r = (PawCare::MedicalRecord^)records[i];
                if (!String::IsNullOrEmpty(search))
                {
                    bool match = r->Diagnosis->ToLower()->Contains(search) ||
                                 r->PetID.ToString()->Contains(search) ||
                                 r->Treatment->ToLower()->Contains(search);
                    if (!match) continue;
                }

                dt->Rows->Add(r->RecordID, r->PetID, r->AppointmentID,
                              r->RecordDate, r->Diagnosis, r->Treatment,
                              r->Vaccination, r->Notes);
            }

            dgvRecords->DataSource = dt;
        }

        void cmbPet_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            LoadAppointments();
        }

        void btnSave_Click(System::Object^ sender, System::EventArgs^ e)
        {
            try
            {
                int petId = GetSelectedPetId();
                if (petId <= 0)
                {
                    MessageBox::Show("Please select a registered patient (pet).", "Validation Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }

                int apptId = GetSelectedAppointmentId();
                if (apptId <= 0)
                {
                    MessageBox::Show("Please select an appointment associated with this exam.", "Validation Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }

                String^ diag = txtDiagnosis->Text->Trim();
                String^ treat = txtTreatment->Text->Trim();

                if (String::IsNullOrWhiteSpace(diag))
                {
                    MessageBox::Show("Please provide a clinical diagnosis.", "Validation Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    txtDiagnosis->Focus();
                    return;
                }

                if (String::IsNullOrWhiteSpace(treat))
                {
                    MessageBox::Show("Please specify the prescribed treatment or medication.", "Validation Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    txtTreatment->Focus();
                    return;
                }

                MedicalRecord^ record = gcnew MedicalRecord();
                record->PetID = petId;
                record->AppointmentID = apptId;
                record->RecordDate = dtpRecordDate->Value.ToString("yyyy-MM-dd");
                record->Diagnosis = diag;
                record->Treatment = treat;
                record->Vaccination = txtVaccination->Text->Trim();
                record->Notes = txtNotes->Text->Trim();

                bool ok = db->insertMedicalRecord(record);
                if (ok)
                {
                    MessageBox::Show("Clinical record successfully saved for Pet #" + petId + "!", "Record Saved", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    btnClear_Click(nullptr, nullptr);
                    LoadRecords();
                }
                else
                {
                    MessageBox::Show("Failed to save medical record to the database.", "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Validation Error: " + ex->Message, "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void btnClear_Click(System::Object^ sender, System::EventArgs^ e)
        {
            selectedRecordId = 0;
            txtDiagnosis->Text = "";
            txtTreatment->Text = "";
            txtVaccination->Text = "";
            txtNotes->Text = "";
            dtpRecordDate->Value = DateTime::Now;
            btnSave->Text = "Save Clinical Record";
        }

        void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e)
        {
            LoadPets();
            LoadAppointments();
            LoadRecords();
        }

        void txtSearch_TextChanged(System::Object^ sender, System::EventArgs^ e)
        {
            LoadRecords();
        }

        void dgvRecords_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0 && e->RowIndex < dgvRecords->Rows->Count)
            {
                auto row = dgvRecords->Rows[e->RowIndex];
                if (row->Cells["Record ID"]->Value != nullptr)
                {
                    Int32::TryParse(row->Cells["Record ID"]->Value->ToString(), selectedRecordId);
                    txtDiagnosis->Text = row->Cells["Diagnosis"]->Value != nullptr ? row->Cells["Diagnosis"]->Value->ToString() : "";
                    txtTreatment->Text = row->Cells["Treatment / Rx"]->Value != nullptr ? row->Cells["Treatment / Rx"]->Value->ToString() : "";
                    txtVaccination->Text = row->Cells["Vaccination"]->Value != nullptr ? row->Cells["Vaccination"]->Value->ToString() : "";
                    txtNotes->Text = row->Cells["Notes"]->Value != nullptr ? row->Cells["Notes"]->Value->ToString() : "";
                }
            }
        }
    };
}
