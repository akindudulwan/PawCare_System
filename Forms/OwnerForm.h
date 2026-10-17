#pragma once
#include "Models/Owner.h"
#include "Database/DatabaseManager.h"

namespace PawCare {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class OwnerForm : public System::Windows::Forms::Form
    {
    private:
        DatabaseManager^ db;
        int selectedOwnerId;

        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblName;
        System::Windows::Forms::TextBox^ txtName;
        System::Windows::Forms::Label^ lblPhone;
        System::Windows::Forms::TextBox^ txtPhone;
        System::Windows::Forms::Label^ lblEmail;
        System::Windows::Forms::TextBox^ txtEmail;
        System::Windows::Forms::Label^ lblAddress;
        System::Windows::Forms::TextBox^ txtAddress;

        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnUpdate;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnClear;
        System::Windows::Forms::DataGridView^ dgvOwners;

    public:
        OwnerForm(DatabaseManager^ dbManager)
        {
            db = dbManager;
            selectedOwnerId = 0;
            InitializeComponent();
            LoadOwners();
        }

    protected:
        ~OwnerForm()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblName = (gcnew System::Windows::Forms::Label());
            this->txtName = (gcnew System::Windows::Forms::TextBox());
            this->lblPhone = (gcnew System::Windows::Forms::Label());
            this->txtPhone = (gcnew System::Windows::Forms::TextBox());
            this->lblEmail = (gcnew System::Windows::Forms::Label());
            this->txtEmail = (gcnew System::Windows::Forms::TextBox());
            this->lblAddress = (gcnew System::Windows::Forms::Label());
            this->txtAddress = (gcnew System::Windows::Forms::TextBox());

            this->btnAdd = (gcnew System::Windows::Forms::Button());
            this->btnUpdate = (gcnew System::Windows::Forms::Button());
            this->btnDelete = (gcnew System::Windows::Forms::Button());
            this->btnClear = (gcnew System::Windows::Forms::Button());
            this->dgvOwners = (gcnew System::Windows::Forms::DataGridView());

            this->lblTitle->Text = "Owner Management";
            this->lblTitle->Font = (gcnew System::Drawing::Font("Segoe UI", 14, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(33, 150, 243);
            this->lblTitle->Location = System::Drawing::Point(20, 15);
            this->lblTitle->AutoSize = true;

            this->lblName->Text = "Full Name *";
            this->lblName->Location = System::Drawing::Point(25, 60);
            this->lblName->AutoSize = true;
            this->txtName->Location = System::Drawing::Point(25, 80);
            this->txtName->Size = System::Drawing::Size(240, 25);

            this->lblPhone->Text = "Telephone (e.g. 0712345678) *";
            this->lblPhone->Location = System::Drawing::Point(25, 115);
            this->lblPhone->AutoSize = true;
            this->txtPhone->Location = System::Drawing::Point(25, 135);
            this->txtPhone->Size = System::Drawing::Size(240, 25);

            this->lblEmail->Text = "Email Address";
            this->lblEmail->Location = System::Drawing::Point(25, 170);
            this->lblEmail->AutoSize = true;
            this->txtEmail->Location = System::Drawing::Point(25, 190);
            this->txtEmail->Size = System::Drawing::Size(240, 25);

            this->lblAddress->Text = "Home Address";
            this->lblAddress->Location = System::Drawing::Point(25, 225);
            this->lblAddress->AutoSize = true;
            this->txtAddress->Location = System::Drawing::Point(25, 245);
            this->txtAddress->Size = System::Drawing::Size(240, 50);
            this->txtAddress->Multiline = true;

            this->btnAdd->Text = "Add Owner";
            this->btnAdd->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnAdd->ForeColor = System::Drawing::Color::White;
            this->btnAdd->BackColor = System::Drawing::Color::FromArgb(76, 175, 80);
            this->btnAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnAdd->FlatAppearance->BorderSize = 0;
            this->btnAdd->Location = System::Drawing::Point(25, 310);
            this->btnAdd->Size = System::Drawing::Size(110, 35);
            this->btnAdd->Click += gcnew System::EventHandler(this, &OwnerForm::btnAdd_Click);

            this->btnUpdate->Text = "Update";
            this->btnUpdate->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnUpdate->ForeColor = System::Drawing::Color::White;
            this->btnUpdate->BackColor = System::Drawing::Color::FromArgb(33, 150, 243);
            this->btnUpdate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnUpdate->FlatAppearance->BorderSize = 0;
            this->btnUpdate->Location = System::Drawing::Point(155, 310);
            this->btnUpdate->Size = System::Drawing::Size(110, 35);
            this->btnUpdate->Click += gcnew System::EventHandler(this, &OwnerForm::btnUpdate_Click);

            this->btnDelete->Text = "Delete";
            this->btnDelete->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnDelete->ForeColor = System::Drawing::Color::White;
            this->btnDelete->BackColor = System::Drawing::Color::FromArgb(244, 67, 54);
            this->btnDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnDelete->FlatAppearance->BorderSize = 0;
            this->btnDelete->Location = System::Drawing::Point(25, 355);
            this->btnDelete->Size = System::Drawing::Size(110, 35);
            this->btnDelete->Click += gcnew System::EventHandler(this, &OwnerForm::btnDelete_Click);

            this->btnClear->Text = "Clear Form";
            this->btnClear->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnClear->ForeColor = System::Drawing::Color::White;
            this->btnClear->BackColor = System::Drawing::Color::FromArgb(158, 158, 158);
            this->btnClear->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnClear->FlatAppearance->BorderSize = 0;
            this->btnClear->Location = System::Drawing::Point(155, 355);
            this->btnClear->Size = System::Drawing::Size(110, 35);
            this->btnClear->Click += gcnew System::EventHandler(this, &OwnerForm::btnClear_Click);

            this->dgvOwners->Location = System::Drawing::Point(290, 60);
            this->dgvOwners->Size = System::Drawing::Size(560, 400);
            this->dgvOwners->ReadOnly = true;
            this->dgvOwners->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->dgvOwners->MultiSelect = false;
            this->dgvOwners->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvOwners->BackgroundColor = System::Drawing::Color::White;
            this->dgvOwners->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &OwnerForm::dgvOwners_CellClick);

            this->ClientSize = System::Drawing::Size(875, 480);
            this->Text = "PawCare - Owner Registration & Management";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->lblName);
            this->Controls->Add(this->txtName);
            this->Controls->Add(this->lblPhone);
            this->Controls->Add(this->txtPhone);
            this->Controls->Add(this->lblEmail);
            this->Controls->Add(this->txtEmail);
            this->Controls->Add(this->lblAddress);
            this->Controls->Add(this->txtAddress);
            this->Controls->Add(this->btnAdd);
            this->Controls->Add(this->btnUpdate);
            this->Controls->Add(this->btnDelete);
            this->Controls->Add(this->btnClear);
            this->Controls->Add(this->dgvOwners);
        }

        void LoadOwners()
        {
            DataTable^ dt = gcnew DataTable();
            dt->Columns->Add("Owner ID");
            dt->Columns->Add("Name");
            dt->Columns->Add("Telephone");
            dt->Columns->Add("Email");
            dt->Columns->Add("Address");

            if (db->isConnected() || db->connect())
            {
                auto list = db->getAllOwners();
                for (int i = 0; i < list->Count; i++)
                {
                    PawCare::Owner^ o = (PawCare::Owner^)list[i];
                    dt->Rows->Add(o->OwnerID, o->Name, o->Telephone, o->Email, o->Address);
                }
            }
            this->dgvOwners->DataSource = dt;
        }

        void ClearFields()
        {
            selectedOwnerId = 0;
            txtName->Text = "";
            txtPhone->Text = "";
            txtEmail->Text = "";
            txtAddress->Text = "";
        }

        void btnAdd_Click(System::Object^ sender, System::EventArgs^ e)
        {
            try
            {
                PawCare::Owner^ o = gcnew PawCare::Owner(0, txtName->Text, txtPhone->Text, txtEmail->Text, txtAddress->Text);
                if (db->insertOwner(o))
                {
                    MessageBox::Show("Owner registered successfully with ID: " + o->OwnerID, "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    ClearFields();
                    LoadOwners();
                }
                else
                {
                    MessageBox::Show("Failed to save owner to database.", "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Validation Error: " + ex->Message, "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (selectedOwnerId <= 0)
            {
                MessageBox::Show("Please select an owner from the table to update.", "Selection Required", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            try
            {
                PawCare::Owner^ o = gcnew PawCare::Owner(selectedOwnerId, txtName->Text, txtPhone->Text, txtEmail->Text, txtAddress->Text);
                if (db->updateOwner(o))
                {
                    MessageBox::Show("Owner updated successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    ClearFields();
                    LoadOwners();
                }
                else
                {
                    MessageBox::Show("Failed to update owner in database.", "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Validation Error: " + ex->Message, "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (selectedOwnerId <= 0)
            {
                MessageBox::Show("Please select an owner from the table to delete.", "Selection Required", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            if (MessageBox::Show("Are you sure you want to delete this owner? (All linked pets must be removed first)", "Confirm Deletion",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
            {
                if (db->deleteOwner(selectedOwnerId))
                {
                    MessageBox::Show("Owner deleted successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    ClearFields();
                    LoadOwners();
                }
                else
                {
                    MessageBox::Show("Could not delete owner. The owner might have registered pets or appointments.", "Constraint Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        void btnClear_Click(System::Object^ sender, System::EventArgs^ e)
        {
            ClearFields();
        }

        void dgvOwners_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0 && e->RowIndex < dgvOwners->Rows->Count)
            {
                auto row = dgvOwners->Rows[e->RowIndex];
                if (row->Cells["Owner ID"]->Value != nullptr)
                {
                    selectedOwnerId = Convert::ToInt32(row->Cells["Owner ID"]->Value);
                    txtName->Text = row->Cells["Name"]->Value->ToString();
                    txtPhone->Text = row->Cells["Telephone"]->Value->ToString();
                    txtEmail->Text = row->Cells["Email"]->Value != nullptr ? row->Cells["Email"]->Value->ToString() : "";
                    txtAddress->Text = row->Cells["Address"]->Value != nullptr ? row->Cells["Address"]->Value->ToString() : "";
                }
            }
        }
    };
}
