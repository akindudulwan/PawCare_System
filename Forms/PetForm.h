#pragma once
#include "Models/Pet.h"
#include "Models/Dog.h"
#include "Models/Cat.h"
#include "Models/Owner.h"
#include "Database/DatabaseManager.h"

namespace PawCare {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class PetForm : public System::Windows::Forms::Form
    {
    private:
        DatabaseManager^ db;
        int selectedPetId;

        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblOwner;
        System::Windows::Forms::ComboBox^ cmbOwners;
        System::Windows::Forms::Label^ lblName;
        System::Windows::Forms::TextBox^ txtName;
        System::Windows::Forms::Label^ lblType;
        System::Windows::Forms::ComboBox^ cmbType;
        System::Windows::Forms::Label^ lblBreed;
        System::Windows::Forms::TextBox^ txtBreed;
        System::Windows::Forms::Label^ lblAge;
        System::Windows::Forms::NumericUpDown^ numAge;
        System::Windows::Forms::Label^ lblGender;
        System::Windows::Forms::ComboBox^ cmbGender;
        System::Windows::Forms::Label^ lblFeePreview;

        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnUpdate;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnClear;
        System::Windows::Forms::DataGridView^ dgvPets;

    public:
        PetForm(DatabaseManager^ dbManager)
        {
            db = dbManager;
            selectedPetId = 0;
            InitializeComponent();
            LoadOwnersList();
            LoadPets();
        }

    protected:
        ~PetForm()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblOwner = (gcnew System::Windows::Forms::Label());
            this->cmbOwners = (gcnew System::Windows::Forms::ComboBox());
            this->lblName = (gcnew System::Windows::Forms::Label());
            this->txtName = (gcnew System::Windows::Forms::TextBox());
            this->lblType = (gcnew System::Windows::Forms::Label());
            this->cmbType = (gcnew System::Windows::Forms::ComboBox());
            this->lblBreed = (gcnew System::Windows::Forms::Label());
            this->txtBreed = (gcnew System::Windows::Forms::TextBox());
            this->lblAge = (gcnew System::Windows::Forms::Label());
            this->numAge = (gcnew System::Windows::Forms::NumericUpDown());
            this->lblGender = (gcnew System::Windows::Forms::Label());
            this->cmbGender = (gcnew System::Windows::Forms::ComboBox());
            this->lblFeePreview = (gcnew System::Windows::Forms::Label());

            this->btnAdd = (gcnew System::Windows::Forms::Button());
            this->btnUpdate = (gcnew System::Windows::Forms::Button());
            this->btnDelete = (gcnew System::Windows::Forms::Button());
            this->btnClear = (gcnew System::Windows::Forms::Button());
            this->dgvPets = (gcnew System::Windows::Forms::DataGridView());

            this->lblTitle->Text = "Pet Registration & Profiles (Polymorphic)";
            this->lblTitle->Font = (gcnew System::Drawing::Font("Segoe UI", 14, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(33, 150, 243);
            this->lblTitle->Location = System::Drawing::Point(20, 15);
            this->lblTitle->AutoSize = true;

            this->lblOwner->Text = "Select Owner *";
            this->lblOwner->Location = System::Drawing::Point(25, 55);
            this->lblOwner->AutoSize = true;
            this->cmbOwners->Location = System::Drawing::Point(25, 75);
            this->cmbOwners->Size = System::Drawing::Size(240, 25);
            this->cmbOwners->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

            this->lblName->Text = "Pet Name *";
            this->lblName->Location = System::Drawing::Point(25, 110);
            this->lblName->AutoSize = true;
            this->txtName->Location = System::Drawing::Point(25, 130);
            this->txtName->Size = System::Drawing::Size(240, 25);

            this->lblType->Text = "Pet Type (Polymorphism) *";
            this->lblType->Location = System::Drawing::Point(25, 165);
            this->lblType->AutoSize = true;
            this->cmbType->Location = System::Drawing::Point(25, 185);
            this->cmbType->Size = System::Drawing::Size(240, 25);
            this->cmbType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbType->Items->AddRange(gcnew array<Object^> { "Dog", "Cat", "Other" });
            this->cmbType->SelectedIndex = 0;
            this->cmbType->SelectedIndexChanged += gcnew System::EventHandler(this, &PetForm::cmbType_SelectedIndexChanged);

            this->lblFeePreview->Text = "Consultation Fee: Rs. 1,200.00";
            this->lblFeePreview->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->lblFeePreview->ForeColor = System::Drawing::Color::FromArgb(46, 125, 50);
            this->lblFeePreview->Location = System::Drawing::Point(25, 218);
            this->lblFeePreview->AutoSize = true;

            this->lblBreed->Text = "Breed";
            this->lblBreed->Location = System::Drawing::Point(25, 245);
            this->lblBreed->AutoSize = true;
            this->txtBreed->Location = System::Drawing::Point(25, 265);
            this->txtBreed->Size = System::Drawing::Size(240, 25);

            this->lblAge->Text = "Age (Years)";
            this->lblAge->Location = System::Drawing::Point(25, 300);
            this->lblAge->AutoSize = true;
            this->numAge->Location = System::Drawing::Point(25, 320);
            this->numAge->Size = System::Drawing::Size(110, 25);
            this->numAge->Minimum = 0;
            this->numAge->Maximum = 50;

            this->lblGender->Text = "Gender";
            this->lblGender->Location = System::Drawing::Point(155, 300);
            this->lblGender->AutoSize = true;
            this->cmbGender->Location = System::Drawing::Point(155, 320);
            this->cmbGender->Size = System::Drawing::Size(110, 25);
            this->cmbGender->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbGender->Items->AddRange(gcnew array<Object^> { "Male", "Female", "Unknown" });
            this->cmbGender->SelectedIndex = 0;

            this->btnAdd->Text = "Add Pet";
            this->btnAdd->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnAdd->ForeColor = System::Drawing::Color::White;
            this->btnAdd->BackColor = System::Drawing::Color::FromArgb(76, 175, 80);
            this->btnAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnAdd->FlatAppearance->BorderSize = 0;
            this->btnAdd->Location = System::Drawing::Point(25, 370);
            this->btnAdd->Size = System::Drawing::Size(110, 35);
            this->btnAdd->Click += gcnew System::EventHandler(this, &PetForm::btnAdd_Click);

            this->btnUpdate->Text = "Update";
            this->btnUpdate->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnUpdate->ForeColor = System::Drawing::Color::White;
            this->btnUpdate->BackColor = System::Drawing::Color::FromArgb(33, 150, 243);
            this->btnUpdate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnUpdate->FlatAppearance->BorderSize = 0;
            this->btnUpdate->Location = System::Drawing::Point(155, 370);
            this->btnUpdate->Size = System::Drawing::Size(110, 35);
            this->btnUpdate->Click += gcnew System::EventHandler(this, &PetForm::btnUpdate_Click);

            this->btnDelete->Text = "Delete";
            this->btnDelete->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnDelete->ForeColor = System::Drawing::Color::White;
            this->btnDelete->BackColor = System::Drawing::Color::FromArgb(244, 67, 54);
            this->btnDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnDelete->FlatAppearance->BorderSize = 0;
            this->btnDelete->Location = System::Drawing::Point(25, 415);
            this->btnDelete->Size = System::Drawing::Size(110, 35);
            this->btnDelete->Click += gcnew System::EventHandler(this, &PetForm::btnDelete_Click);

            this->btnClear->Text = "Clear Form";
            this->btnClear->Font = (gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold));
            this->btnClear->ForeColor = System::Drawing::Color::White;
            this->btnClear->BackColor = System::Drawing::Color::FromArgb(158, 158, 158);
            this->btnClear->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnClear->FlatAppearance->BorderSize = 0;
            this->btnClear->Location = System::Drawing::Point(155, 415);
            this->btnClear->Size = System::Drawing::Size(110, 35);
            this->btnClear->Click += gcnew System::EventHandler(this, &PetForm::btnClear_Click);

            this->dgvPets->Location = System::Drawing::Point(290, 55);
            this->dgvPets->Size = System::Drawing::Size(580, 420);
            this->dgvPets->ReadOnly = true;
            this->dgvPets->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->dgvPets->MultiSelect = false;
            this->dgvPets->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvPets->BackgroundColor = System::Drawing::Color::White;
            this->dgvPets->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &PetForm::dgvPets_CellClick);

            this->ClientSize = System::Drawing::Size(895, 500);
            this->Text = "PawCare - Pet Registration";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->lblOwner);
            this->Controls->Add(this->cmbOwners);
            this->Controls->Add(this->lblName);
            this->Controls->Add(this->txtName);
            this->Controls->Add(this->lblType);
            this->Controls->Add(this->cmbType);
            this->Controls->Add(this->lblFeePreview);
            this->Controls->Add(this->lblBreed);
            this->Controls->Add(this->txtBreed);
            this->Controls->Add(this->lblAge);
            this->Controls->Add(this->numAge);
            this->Controls->Add(this->lblGender);
            this->Controls->Add(this->cmbGender);
            this->Controls->Add(this->btnAdd);
            this->Controls->Add(this->btnUpdate);
            this->Controls->Add(this->btnDelete);
            this->Controls->Add(this->btnClear);
            this->Controls->Add(this->dgvPets);
        }

        void LoadOwnersList()
        {
            cmbOwners->Items->Clear();
            if (db->isConnected() || db->connect())
            {
                auto list = db->getAllOwners();
                for (int i = 0; i < list->Count; i++)
                {
                    PawCare::Owner^ o = (PawCare::Owner^)list[i];
                    cmbOwners->Items->Add(o->OwnerID.ToString() + " - " + o->Name);
                }
            }
            if (cmbOwners->Items->Count > 0) cmbOwners->SelectedIndex = 0;
        }

        void LoadPets()
        {
            DataTable^ dt = gcnew DataTable();
            dt->Columns->Add("Pet ID");
            dt->Columns->Add("Owner ID");
            dt->Columns->Add("Name");
            dt->Columns->Add("Type");
            dt->Columns->Add("Breed");
            dt->Columns->Add("Age");
            dt->Columns->Add("Gender");
            dt->Columns->Add("Consultation Fee");

            if (db->isConnected() || db->connect())
            {
                auto list = db->getAllPets();
                for (int i = 0; i < list->Count; i++)
                {
                    PawCare::Pet^ p = (PawCare::Pet^)list[i];
                    dt->Rows->Add(p->PetID, p->OwnerID, p->Name, p->PetType, p->Breed,
                                  p->Age, p->Gender, "Rs. " + p->calculateConsultationFee().ToString("F2"));
                }
            }
            this->dgvPets->DataSource = dt;
        }

        int GetSelectedOwnerId()
        {
            if (cmbOwners->SelectedItem == nullptr) return 0;
            String^ s = cmbOwners->SelectedItem->ToString();
            int dashIdx = s->IndexOf(" - ");
            if (dashIdx > 0) return Convert::ToInt32(s->Substring(0, dashIdx));
            return 0;
        }

        void ClearFields()
        {
            selectedPetId = 0;
            txtName->Text = "";
            txtBreed->Text = "";
            numAge->Value = 0;
            cmbType->SelectedIndex = 0;
            cmbGender->SelectedIndex = 0;
        }

        void cmbType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            String^ t = cmbType->SelectedItem != nullptr ? cmbType->SelectedItem->ToString() : "";
            if (t == "Dog")
            {
                lblFeePreview->Text = "Consultation Fee: Rs. " + Dog::DOG_CONSULTATION_FEE.ToString("F2");
            }
            else if (t == "Cat")
            {
                lblFeePreview->Text = "Consultation Fee: Rs. " + Cat::CAT_CONSULTATION_FEE.ToString("F2");
            }
            else
            {
                lblFeePreview->Text = "Consultation Fee: Rs. " + Pet::BASE_CONSULTATION_FEE.ToString("F2");
            }
        }

        void btnAdd_Click(System::Object^ sender, System::EventArgs^ e)
        {
            int ownerId = GetSelectedOwnerId();
            if (ownerId <= 0)
            {
                MessageBox::Show("Please select a valid owner.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            try
            {
                String^ t = cmbType->SelectedItem->ToString();
                PawCare::Pet^ p;
                if (t == "Dog")
                {
                    p = gcnew PawCare::Dog(0, ownerId, txtName->Text, txtBreed->Text, (int)numAge->Value, cmbGender->SelectedItem->ToString());
                }
                else if (t == "Cat")
                {
                    p = gcnew PawCare::Cat(0, ownerId, txtName->Text, txtBreed->Text, (int)numAge->Value, cmbGender->SelectedItem->ToString());
                }
                else
                {
                    p = gcnew PawCare::Pet(0, ownerId, txtName->Text, t, txtBreed->Text, (int)numAge->Value, cmbGender->SelectedItem->ToString());
                }

                if (db->insertPet(p))
                {
                    MessageBox::Show("Pet registered successfully with ID: " + p->PetID, "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    ClearFields();
                    LoadPets();
                }
                else
                {
                    MessageBox::Show("Failed to save pet to database.", "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Validation Error: " + ex->Message, "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (selectedPetId <= 0)
            {
                MessageBox::Show("Please select a pet from the table to update.", "Selection Required", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            int ownerId = GetSelectedOwnerId();
            try
            {
                String^ t = cmbType->SelectedItem->ToString();
                PawCare::Pet^ p;
                if (t == "Dog")
                {
                    p = gcnew PawCare::Dog(selectedPetId, ownerId, txtName->Text, txtBreed->Text, (int)numAge->Value, cmbGender->SelectedItem->ToString());
                }
                else if (t == "Cat")
                {
                    p = gcnew PawCare::Cat(selectedPetId, ownerId, txtName->Text, txtBreed->Text, (int)numAge->Value, cmbGender->SelectedItem->ToString());
                }
                else
                {
                    p = gcnew PawCare::Pet(selectedPetId, ownerId, txtName->Text, t, txtBreed->Text, (int)numAge->Value, cmbGender->SelectedItem->ToString());
                }

                if (db->updatePet(p))
                {
                    MessageBox::Show("Pet updated successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    ClearFields();
                    LoadPets();
                }
                else
                {
                    MessageBox::Show("Failed to update pet in database.", "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Validation Error: " + ex->Message, "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (selectedPetId <= 0)
            {
                MessageBox::Show("Please select a pet from the table to delete.", "Selection Required", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            if (MessageBox::Show("Are you sure you want to delete this pet profile?", "Confirm Deletion",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
            {
                if (db->deletePet(selectedPetId))
                {
                    MessageBox::Show("Pet profile deleted successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    ClearFields();
                    LoadPets();
                }
                else
                {
                    MessageBox::Show("Could not delete pet. The pet might have active appointments or medical records.", "Constraint Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        void btnClear_Click(System::Object^ sender, System::EventArgs^ e)
        {
            ClearFields();
        }

        void dgvPets_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0 && e->RowIndex < dgvPets->Rows->Count)
            {
                auto row = dgvPets->Rows[e->RowIndex];
                if (row->Cells["Pet ID"]->Value != nullptr)
                {
                    selectedPetId = Convert::ToInt32(row->Cells["Pet ID"]->Value);
                    txtName->Text = row->Cells["Name"]->Value->ToString();
                    txtBreed->Text = row->Cells["Breed"]->Value != nullptr ? row->Cells["Breed"]->Value->ToString() : "";
                    numAge->Value = Convert::ToInt32(row->Cells["Age"]->Value);

                    String^ t = row->Cells["Type"]->Value->ToString();
                    if (t == "Dog") cmbType->SelectedIndex = 0;
                    else if (t == "Cat") cmbType->SelectedIndex = 1;
                    else cmbType->SelectedIndex = 2;

                    String^ g = row->Cells["Gender"]->Value->ToString();
                    if (g == "Male") cmbGender->SelectedIndex = 0;
                    else if (g == "Female") cmbGender->SelectedIndex = 1;
                    else cmbGender->SelectedIndex = 2;
                }
            }
        }
    };
}
