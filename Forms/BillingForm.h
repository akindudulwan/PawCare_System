#pragma once
#include "Models/Payment.h"
#include "Models/Appointment.h"
#include "Models/Pet.h"
#include "Database/DatabaseManager.h"

namespace PawCare {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class BillingForm : public System::Windows::Forms::Form
    {
    private:
        DatabaseManager^ db;

        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblAppt;
        System::Windows::Forms::ComboBox^ cmbAppointments;
        System::Windows::Forms::Label^ lblConsultFee;
        System::Windows::Forms::TextBox^ txtConsultFee;
        System::Windows::Forms::Label^ lblTreatmentFee;
        System::Windows::Forms::TextBox^ txtTreatmentFee;
        System::Windows::Forms::Label^ lblOtherFee;
        System::Windows::Forms::TextBox^ txtOtherFee;
        System::Windows::Forms::Label^ lblTotal;
        System::Windows::Forms::TextBox^ txtTotal;
        System::Windows::Forms::Label^ lblMethod;
        System::Windows::Forms::ComboBox^ cmbMethod;

        System::Windows::Forms::Button^ btnCalculate;
        System::Windows::Forms::Button^ btnProcess;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::DataGridView^ dgvPayments;

    public:
        BillingForm(DatabaseManager^ dbManager)
        {
            db = dbManager;
            InitializeComponent();
            LoadAppointments();
            LoadPayments();
        }

    protected:
        ~BillingForm()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblAppt = (gcnew System::Windows::Forms::Label());
            this->cmbAppointments = (gcnew System::Windows::Forms::ComboBox());
            this->lblConsultFee = (gcnew System::Windows::Forms::Label());
            this->txtConsultFee = (gcnew System::Windows::Forms::TextBox());
            this->lblTreatmentFee = (gcnew System::Windows::Forms::Label());
            this->txtTreatmentFee = (gcnew System::Windows::Forms::TextBox());
            this->lblOtherFee = (gcnew System::Windows::Forms::Label());
            this->txtOtherFee = (gcnew System::Windows::Forms::TextBox());
            this->lblTotal = (gcnew System::Windows::Forms::Label());
            this->txtTotal = (gcnew System::Windows::Forms::TextBox());
            this->lblMethod = (gcnew System::Windows::Forms::Label());
            this->cmbMethod = (gcnew System::Windows::Forms::ComboBox());

            this->btnCalculate = (gcnew System::Windows::Forms::Button());
            this->btnProcess = (gcnew System::Windows::Forms::Button());
            this->btnRefresh = (gcnew System::Windows::Forms::Button());
            this->dgvPayments = (gcnew System::Windows::Forms::DataGridView());

            this->lblTitle->Text = "Billing & Payments (Transaction Protected)";
            this->lblTitle->Font = (gcnew System::Drawing::Font("Segoe UI", 14, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(33, 150, 243);
            this->lblTitle->Location = System::Drawing::Point(20, 15);
            this->lblTitle->AutoSize = true;

            this->lblAppt->Text = "Select Appointment to Bill *";
            this->lblAppt->Location = System::Drawing::Point(25, 55);
            this->lblAppt->AutoSize = true;
            this->cmbAppointments->Location = System::Drawing::Point(25, 75);
            this->cmbAppointments->Size = System::Drawing::Size(240, 25);
            this->cmbAppointments->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbAppointments->SelectedIndexChanged += gcnew System::EventHandler(this, &BillingForm::cmbAppointments_SelectedIndexChanged);

            this->lblConsultFee->Text = "Consultation Fee (Rs.) *";
            this->lblConsultFee->Location = System::Drawing::Point(25, 110);
            this->lblConsultFee->AutoSize = true;
            this->txtConsultFee->Location = System::Drawing::Point(25, 130);
            this->txtConsultFee->Size = System::Drawing::Size(240, 25);
            this->txtConsultFee->TextChanged += gcnew System::EventHandler(this, &BillingForm::Fee_TextChanged);

            this->lblTreatmentFee->Text = "Treatment Fee (Rs.)";
            this->lblTreatmentFee->Location = System::Drawing::Point(25, 165);
            this->lblTreatmentFee->AutoSize = true;
            this->txtTreatmentFee->Text = "0.00";
            this->txtTreatmentFee->Location = System::Drawing::Point(25, 185);
            this->txtTreatmentFee->Size = System::Drawing::Size(240, 25);
            this->txtTreatmentFee->TextChanged += gcnew System::EventHandler(this, &BillingForm::Fee_TextChanged);

            this->lblOtherFee->Text = "Other Charges (Rs.)";
            this->lblOtherFee->Location = System::Drawing::Point(25, 220);
            this->lblOtherFee->AutoSize = true;
            this->txtOtherFee->Text = "0.00";
            this->txtOtherFee->Location = System::Drawing::Point(25, 240);
            this->txtOtherFee->Size = System::Drawing::Size(240, 25);
            this->txtOtherFee->TextChanged += gcnew System::EventHandler(this, &BillingForm::Fee_TextChanged);

            this->lblTotal->Text = "Total Amount (Dynamic Auto-sync):";
            this->lblTotal->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->lblTotal->Location = System::Drawing::Point(25, 275);
            this->lblTotal->AutoSize = true;
            this->txtTotal->Location = System::Drawing::Point(25, 295);
            this->txtTotal->Size = System::Drawing::Size(240, 25);
            this->txtTotal->ReadOnly = true;
            this->txtTotal->Font = (gcnew System::Drawing::Font("Segoe UI", 10.5F, System::Drawing::FontStyle::Bold));
            this->txtTotal->ForeColor = System::Drawing::Color::FromArgb(46, 125, 50);

            this->lblMethod->Text = "Payment Method *";
            this->lblMethod->Location = System::Drawing::Point(25, 330);
            this->lblMethod->AutoSize = true;
            this->cmbMethod->Location = System::Drawing::Point(25, 350);
            this->cmbMethod->Size = System::Drawing::Size(240, 25);
            this->cmbMethod->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbMethod->Items->AddRange(gcnew array<Object^> { "Cash", "Card", "Bank Transfer", "Online" });
            this->cmbMethod->SelectedIndex = 0;

            this->btnProcess->Text = "Process Payment";
            this->btnProcess->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnProcess->ForeColor = System::Drawing::Color::White;
            this->btnProcess->BackColor = System::Drawing::Color::FromArgb(76, 175, 80);
            this->btnProcess->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnProcess->FlatAppearance->BorderSize = 0;
            this->btnProcess->Location = System::Drawing::Point(25, 395);
            this->btnProcess->Size = System::Drawing::Size(240, 35);
            this->btnProcess->Click += gcnew System::EventHandler(this, &BillingForm::btnProcess_Click);

            this->dgvPayments->Location = System::Drawing::Point(290, 55);
            this->dgvPayments->Size = System::Drawing::Size(600, 410);
            this->dgvPayments->ReadOnly = true;
            this->dgvPayments->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvPayments->BackgroundColor = System::Drawing::Color::White;

            this->ClientSize = System::Drawing::Size(915, 490);
            this->Text = "PawCare - Billing & Invoicing";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->MinimizeBox = true;
            this->MaximizeBox = true;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->lblAppt);
            this->Controls->Add(this->cmbAppointments);
            this->Controls->Add(this->lblConsultFee);
            this->Controls->Add(this->txtConsultFee);
            this->Controls->Add(this->lblTreatmentFee);
            this->Controls->Add(this->txtTreatmentFee);
            this->Controls->Add(this->lblOtherFee);
            this->Controls->Add(this->txtOtherFee);
            this->Controls->Add(this->lblTotal);
            this->Controls->Add(this->txtTotal);
            this->Controls->Add(this->lblMethod);
            this->Controls->Add(this->cmbMethod);
            this->Controls->Add(this->btnProcess);
            this->Controls->Add(this->dgvPayments);
        }

        void LoadAppointments()
        {
            cmbAppointments->Items->Clear();
            if (db->isConnected() || db->connect())
            {
                auto list = db->getAllAppointments();
                for (int i = 0; i < list->Count; i++)
                {
                    PawCare::Appointment^ a = (PawCare::Appointment^)list[i];
                    if (a->Status != Appointment::STATUS_CANCELLED && a->Status != Appointment::STATUS_COMPLETED)
                    {
                        cmbAppointments->Items->Add(a->AppointmentID.ToString() + " - Pet ID: " + a->PetID + " (" + a->AppointmentDate + ")");
                    }
                }
            }
            if (cmbAppointments->Items->Count > 0)
            {
                cmbAppointments->SelectedIndex = 0;
            }
            else
            {
                txtConsultFee->Text = "1000.00";
                RecalculateTotal();
            }
        }

        void LoadPayments()
        {
            DataTable^ dt = gcnew DataTable();
            dt->Columns->Add("Pay ID");
            dt->Columns->Add("Appt ID");
            dt->Columns->Add("Consult Fee");
            dt->Columns->Add("Treatment Fee");
            dt->Columns->Add("Other Fee");
            dt->Columns->Add("Total (Rs.)");
            dt->Columns->Add("Method");
            dt->Columns->Add("Status");

            if (db->isConnected() || db->connect())
            {
                MySqlCommand^ cmd = gcnew MySqlCommand("SELECT payment_id, appointment_id, consultation_fee, treatment_fee, other_fee, total_amount, payment_method, payment_status FROM payments ORDER BY payment_id DESC;", db->getConnection());
                try
                {
                    MySqlDataReader^ reader = cmd->ExecuteReader();
                    while (reader->Read())
                    {
                        dt->Rows->Add(
                            reader->GetInt32("payment_id"),
                            reader->GetInt32("appointment_id"),
                            reader->GetDecimal("consultation_fee").ToString("F2"),
                            reader->GetDecimal("treatment_fee").ToString("F2"),
                            reader->GetDecimal("other_fee").ToString("F2"),
                            reader->GetDecimal("total_amount").ToString("F2"),
                            reader->GetString("payment_method"),
                            reader->GetString("payment_status")
                        );
                    }
                    reader->Close();
                }
                catch (Exception^) {}
            }
            this->dgvPayments->DataSource = dt;
        }

        int GetSelectedApptId()
        {
            if (cmbAppointments->SelectedItem == nullptr) return 0;
            String^ s = cmbAppointments->SelectedItem->ToString();
            int dashIdx = s->IndexOf(" - ");
            if (dashIdx > 0) return Convert::ToInt32(s->Substring(0, dashIdx));
            return 0;
        }

        void RecalculateTotal()
        {
            try
            {
                double c = 0, t = 0, o = 0;
                Double::TryParse(txtConsultFee->Text, c);
                Double::TryParse(txtTreatmentFee->Text, t);
                Double::TryParse(txtOtherFee->Text, o);

                PawCare::Payment^ temp = gcnew PawCare::Payment(0, 1, c, t, o, Payment::METHOD_CASH);
                txtTotal->Text = "Rs. " + temp->TotalAmount.ToString("F2");
            }
            catch (Exception^)
            {
                txtTotal->Text = "Rs. 0.00";
            }
        }

        void Fee_TextChanged(System::Object^ sender, System::EventArgs^ e)
        {
            RecalculateTotal();
        }

        void cmbAppointments_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            int apptId = GetSelectedApptId();
            if (apptId > 0 && (db->isConnected() || db->connect()))
            {
                PawCare::Appointment^ appt = db->getAppointmentById(apptId);
                if (appt != nullptr)
                {
                    PawCare::Pet^ pet = db->getPetById(appt->PetID);
                    if (pet != nullptr)
                    {

                        txtConsultFee->Text = pet->calculateConsultationFee().ToString("F2");
                        RecalculateTotal();
                    }
                }
            }
        }

        void btnProcess_Click(System::Object^ sender, System::EventArgs^ e)
        {
            int apptId = GetSelectedApptId();
            if (apptId <= 0)
            {
                MessageBox::Show("Please select an active appointment to process payment.", "Selection Required", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            try
            {
                double c = Convert::ToDouble(txtConsultFee->Text);
                double t = Convert::ToDouble(txtTreatmentFee->Text);
                double o = Convert::ToDouble(txtOtherFee->Text);
                String^ method = cmbMethod->SelectedItem->ToString();

                PawCare::Payment^ pay = gcnew PawCare::Payment(0, apptId, c, t, o, method);

                if (db->processAppointmentPayment(apptId, pay))
                {
                    MessageBox::Show("Payment of Rs. " + pay->TotalAmount.ToString("F2") + " processed successfully!\nAppointment marked as COMPLETED.",
                        "Transaction Succeeded", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    LoadAppointments();
                    LoadPayments();
                }
                else
                {
                    MessageBox::Show("Payment failed or rolled back by database transaction.", "Transaction Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Validation Error: " + ex->Message, "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }
    };
}
