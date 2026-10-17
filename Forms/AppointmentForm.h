#pragma once
#include "Models/Appointment.h"
#include "Models/Pet.h"
#include "Models/Veterinarian.h"
#include "Database/DatabaseManager.h"

namespace PawCare {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class AppointmentForm : public System::Windows::Forms::Form
    {
    private:
        DatabaseManager^ db;
        int selectedApptId;
        String^ selectedApptStatus;

        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblPet;
        System::Windows::Forms::ComboBox^ cmbPets;
        System::Windows::Forms::Label^ lblVet;
        System::Windows::Forms::ComboBox^ cmbVets;
        System::Windows::Forms::Label^ lblDate;
        System::Windows::Forms::DateTimePicker^ dtpDate;
        System::Windows::Forms::Label^ lblTime;
        System::Windows::Forms::DateTimePicker^ dtpTime;
        System::Windows::Forms::Label^ lblReason;
        System::Windows::Forms::TextBox^ txtReason;
        System::Windows::Forms::Label^ lblStatus;
        System::Windows::Forms::ComboBox^ cmbStatus;

        System::Windows::Forms::Button^ btnBook;
        System::Windows::Forms::Button^ btnUpdate;
        System::Windows::Forms::Button^ btnCancel;
        System::Windows::Forms::Button^ btnClear;
        System::Windows::Forms::DataGridView^ dgvAppts;

    public:
        AppointmentForm(DatabaseManager^ dbManager)
        {
            db = dbManager;
            selectedApptId = 0;
            selectedApptStatus = PawCare::Appointment::STATUS_BOOKED;
            InitializeComponent();
            LoadDropdowns();
            LoadAppointments();
        }

    protected:
        ~AppointmentForm()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblPet = (gcnew System::Windows::Forms::Label());
            this->cmbPets = (gcnew System::Windows::Forms::ComboBox());
            this->lblVet = (gcnew System::Windows::Forms::Label());
            this->cmbVets = (gcnew System::Windows::Forms::ComboBox());
            this->lblDate = (gcnew System::Windows::Forms::Label());
            this->dtpDate = (gcnew System::Windows::Forms::DateTimePicker());
            this->lblTime = (gcnew System::Windows::Forms::Label());
            this->dtpTime = (gcnew System::Windows::Forms::DateTimePicker());
            this->lblReason = (gcnew System::Windows::Forms::Label());
            this->txtReason = (gcnew System::Windows::Forms::TextBox());
            this->lblStatus = (gcnew System::Windows::Forms::Label());
            this->cmbStatus = (gcnew System::Windows::Forms::ComboBox());

            this->btnBook = (gcnew System::Windows::Forms::Button());
            this->btnUpdate = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->btnClear = (gcnew System::Windows::Forms::Button());
            this->dgvAppts = (gcnew System::Windows::Forms::DataGridView());

            this->lblTitle->Text = "Appointment Scheduling & Status Control";
            this->lblTitle->Font = (gcnew System::Drawing::Font("Segoe UI", 14, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(33, 150, 243);
            this->lblTitle->Location = System::Drawing::Point(20, 15);
            this->lblTitle->AutoSize = true;

            this->lblPet->Text = "Select Pet *";
            this->lblPet->Location = System::Drawing::Point(25, 55);
            this->lblPet->AutoSize = true;
            this->cmbPets->Location = System::Drawing::Point(25, 75);
            this->cmbPets->Size = System::Drawing::Size(240, 25);
            this->cmbPets->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

            this->lblVet->Text = "Select Veterinarian *";
            this->lblVet->Location = System::Drawing::Point(25, 110);
            this->lblVet->AutoSize = true;
            this->cmbVets->Location = System::Drawing::Point(25, 130);
            this->cmbVets->Size = System::Drawing::Size(240, 25);
            this->cmbVets->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

            this->lblDate->Text = "Date *";
            this->lblDate->Location = System::Drawing::Point(25, 165);
            this->lblDate->AutoSize = true;
            this->dtpDate->Format = System::Windows::Forms::DateTimePickerFormat::Short;
            this->dtpDate->Location = System::Drawing::Point(25, 185);
            this->dtpDate->Size = System::Drawing::Size(115, 25);

            this->lblTime->Text = "Time *";
            this->lblTime->Location = System::Drawing::Point(150, 165);
            this->lblTime->AutoSize = true;
            this->dtpTime->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
            this->dtpTime->CustomFormat = "HH:mm";
            this->dtpTime->ShowUpDown = true;
            this->dtpTime->Location = System::Drawing::Point(150, 185);
            this->dtpTime->Size = System::Drawing::Size(115, 25);

            this->lblReason->Text = "Reason for Visit *";
            this->lblReason->Location = System::Drawing::Point(25, 220);
            this->lblReason->AutoSize = true;
            this->txtReason->Location = System::Drawing::Point(25, 240);
            this->txtReason->Size = System::Drawing::Size(240, 50);
            this->txtReason->Multiline = true;

            this->lblStatus->Text = "Status (State Machine)";
            this->lblStatus->Location = System::Drawing::Point(25, 300);
            this->lblStatus->AutoSize = true;
            this->cmbStatus->Location = System::Drawing::Point(25, 320);
            this->cmbStatus->Size = System::Drawing::Size(240, 25);
            this->cmbStatus->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbStatus->Items->AddRange(gcnew array<Object^> { "BOOKED", "CONFIRMED", "COMPLETED", "CANCELLED" });
            this->cmbStatus->SelectedIndex = 0;

            this->btnBook->Text = "Book Appt";
            this->btnBook->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnBook->ForeColor = System::Drawing::Color::White;
            this->btnBook->BackColor = System::Drawing::Color::FromArgb(76, 175, 80);
            this->btnBook->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnBook->FlatAppearance->BorderSize = 0;
            this->btnBook->Location = System::Drawing::Point(25, 365);
            this->btnBook->Size = System::Drawing::Size(110, 35);
            this->btnBook->Click += gcnew System::EventHandler(this, &AppointmentForm::btnBook_Click);

            this->btnUpdate->Text = "Update";
            this->btnUpdate->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnUpdate->ForeColor = System::Drawing::Color::White;
            this->btnUpdate->BackColor = System::Drawing::Color::FromArgb(33, 150, 243);
            this->btnUpdate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnUpdate->FlatAppearance->BorderSize = 0;
            this->btnUpdate->Location = System::Drawing::Point(155, 365);
            this->btnUpdate->Size = System::Drawing::Size(110, 35);
            this->btnUpdate->Click += gcnew System::EventHandler(this, &AppointmentForm::btnUpdate_Click);

            this->btnCancel->Text = "Cancel Appt";
            this->btnCancel->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnCancel->ForeColor = System::Drawing::Color::White;
            this->btnCancel->BackColor = System::Drawing::Color::FromArgb(244, 67, 54);
            this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCancel->FlatAppearance->BorderSize = 0;
            this->btnCancel->Location = System::Drawing::Point(25, 410);
            this->btnCancel->Size = System::Drawing::Size(110, 35);
            this->btnCancel->Click += gcnew System::EventHandler(this, &AppointmentForm::btnCancel_Click);

            this->btnClear->Text = "Clear Form";
            this->btnClear->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnClear->ForeColor = System::Drawing::Color::White;
            this->btnClear->BackColor = System::Drawing::Color::FromArgb(158, 158, 158);
            this->btnClear->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnClear->FlatAppearance->BorderSize = 0;
            this->btnClear->Location = System::Drawing::Point(155, 410);
            this->btnClear->Size = System::Drawing::Size(110, 35);
            this->btnClear->Click += gcnew System::EventHandler(this, &AppointmentForm::btnClear_Click);

            this->dgvAppts->Location = System::Drawing::Point(290, 55);
            this->dgvAppts->Size = System::Drawing::Size(600, 410);
            this->dgvAppts->ReadOnly = true;
            this->dgvAppts->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->dgvAppts->MultiSelect = false;
            this->dgvAppts->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvAppts->BackgroundColor = System::Drawing::Color::White;
            this->dgvAppts->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &AppointmentForm::dgvAppts_CellClick);

            this->ClientSize = System::Drawing::Size(915, 490);
            this->Text = "PawCare - Appointment Management";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->lblPet);
            this->Controls->Add(this->cmbPets);
            this->Controls->Add(this->lblVet);
            this->Controls->Add(this->cmbVets);
            this->Controls->Add(this->lblDate);
            this->Controls->Add(this->dtpDate);
            this->Controls->Add(this->lblTime);
            this->Controls->Add(this->dtpTime);
            this->Controls->Add(this->lblReason);
            this->Controls->Add(this->txtReason);
            this->Controls->Add(this->lblStatus);
            this->Controls->Add(this->cmbStatus);
            this->Controls->Add(this->btnBook);
            this->Controls->Add(this->btnUpdate);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnClear);
            this->Controls->Add(this->dgvAppts);
        }

        void LoadDropdowns()
        {
            cmbPets->Items->Clear();
            cmbVets->Items->Clear();
            if (db->isConnected() || db->connect())
            {
                auto pets = db->getAllPets();
                for (int i = 0; i < pets->Count; i++)
                {
                    PawCare::Pet^ p = (PawCare::Pet^)pets[i];
                    cmbPets->Items->Add(p->PetID.ToString() + " - " + p->Name + " (" + p->PetType + ")");
                }

                auto vets = db->getAllVeterinarians();
                for (int i = 0; i < vets->Count; i++)
                {
                    PawCare::Veterinarian^ v = (PawCare::Veterinarian^)vets[i];
                    cmbVets->Items->Add(v->VeterinarianID.ToString() + " - " + v->Name);
                }
            }
            if (cmbPets->Items->Count > 0) cmbPets->SelectedIndex = 0;
            if (cmbVets->Items->Count > 0) cmbVets->SelectedIndex = 0;
        }

        void LoadAppointments()
        {
            DataTable^ dt = gcnew DataTable();
            dt->Columns->Add("Appt ID");
            dt->Columns->Add("Pet ID");
            dt->Columns->Add("Vet ID");
            dt->Columns->Add("Date");
            dt->Columns->Add("Time");
            dt->Columns->Add("Reason");
            dt->Columns->Add("Status");

            if (db->isConnected() || db->connect())
            {
                auto list = db->getAllAppointments();
                for (int i = 0; i < list->Count; i++)
                {
                    PawCare::Appointment^ a = (PawCare::Appointment^)list[i];
                    dt->Rows->Add(a->AppointmentID, a->PetID, a->VeterinarianID,
                                  a->AppointmentDate, a->AppointmentTime, a->Reason, a->Status);
                }
            }
            this->dgvAppts->DataSource = dt;
        }

        int GetSelectedId(ComboBox^ cmb)
        {
            if (cmb->SelectedItem == nullptr) return 0;
            String^ s = cmb->SelectedItem->ToString();
            int dashIdx = s->IndexOf(" - ");
            if (dashIdx > 0) return Convert::ToInt32(s->Substring(0, dashIdx));
            return 0;
        }

        void ClearFields()
        {
            selectedApptId = 0;
            selectedApptStatus = PawCare::Appointment::STATUS_BOOKED;
            txtReason->Text = "";
            cmbStatus->SelectedIndex = 0;
            dtpDate->Value = DateTime::Now;
            dtpTime->Value = DateTime::Now;
        }

        void btnBook_Click(System::Object^ sender, System::EventArgs^ e)
        {
            int petId = GetSelectedId(cmbPets);
            int vetId = GetSelectedId(cmbVets);
            if (petId <= 0 || vetId <= 0)
            {
                MessageBox::Show("Valid Pet and Veterinarian must be selected.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            try
            {
                String^ dateStr = dtpDate->Value.ToString("yyyy-MM-dd");
                String^ timeStr = dtpTime->Value.ToString("HH:mm");

                PawCare::Appointment^ appt = gcnew PawCare::Appointment(0, petId, vetId, dateStr, timeStr, txtReason->Text);
                appt->createAppointment();

                if (db->insertAppointment(appt))
                {
                    MessageBox::Show("Appointment booked successfully with ID: " + appt->AppointmentID, "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    ClearFields();
                    LoadAppointments();
                }
                else
                {
                    MessageBox::Show("Could not book appointment. Veterinarian may already be booked at this date and time.", "Conflict Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Validation Error: " + ex->Message, "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (selectedApptId <= 0)
            {
                MessageBox::Show("Please select an appointment from the table to update.", "Selection Required", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            int petId = GetSelectedId(cmbPets);
            int vetId = GetSelectedId(cmbVets);
            try
            {
                String^ dateStr = dtpDate->Value.ToString("yyyy-MM-dd");
                String^ timeStr = dtpTime->Value.ToString("HH:mm");

                PawCare::Appointment^ appt = gcnew PawCare::Appointment(selectedApptId, petId, vetId, dateStr, timeStr, txtReason->Text, selectedApptStatus);
                String^ newStatus = cmbStatus->SelectedItem->ToString();
                if (newStatus != selectedApptStatus)
                {
                    appt->changeStatus(newStatus);
                }

                if (db->updateAppointment(appt))
                {
                    MessageBox::Show("Appointment updated successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    ClearFields();
                    LoadAppointments();
                }
                else
                {
                    MessageBox::Show("Failed to update appointment. Check for scheduling conflicts.", "Update Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Validation Error: " + ex->Message, "State Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (selectedApptId <= 0)
            {
                MessageBox::Show("Please select an appointment from the table to cancel.", "Selection Required", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            if (MessageBox::Show("Are you sure you want to cancel this appointment?", "Confirm Cancellation",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
            {
                if (db->changeAppointmentStatus(selectedApptId, Appointment::STATUS_CANCELLED))
                {
                    MessageBox::Show("Appointment cancelled successfully.", "Cancelled", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    ClearFields();
                    LoadAppointments();
                }
                else
                {
                    MessageBox::Show("Failed to cancel appointment in database.", "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        void btnClear_Click(System::Object^ sender, System::EventArgs^ e)
        {
            ClearFields();
        }

        void dgvAppts_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0 && e->RowIndex < dgvAppts->Rows->Count)
            {
                auto row = dgvAppts->Rows[e->RowIndex];
                if (row->Cells["Appt ID"]->Value != nullptr)
                {
                    selectedApptId = Convert::ToInt32(row->Cells["Appt ID"]->Value);
                    txtReason->Text = row->Cells["Reason"]->Value->ToString();

                    String^ stat = row->Cells["Status"]->Value->ToString();
                    selectedApptStatus = stat;
                    for (int i = 0; i < cmbStatus->Items->Count; i++)
                    {
                        if (cmbStatus->Items[i]->ToString() == stat)
                        {
                            cmbStatus->SelectedIndex = i;
                            break;
                        }
                    }
                }
            }
        }
    };
}
