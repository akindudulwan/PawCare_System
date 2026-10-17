#include "Veterinarian.h"

using namespace PawCare;

Veterinarian::Veterinarian()
{
    veterinarianID = 0;
    name = "";
    telephone = "";
    specialization = "General Veterinary";
}

Veterinarian::Veterinarian(int id, String^ vetName, String^ phone, String^ spec)
{
    veterinarianID = id;
    name = vetName != nullptr ? vetName->Trim() : "";
    telephone = phone != nullptr ? phone->Trim() : "";
    specialization = spec != nullptr ? spec->Trim() : "General Veterinary";
}

int Veterinarian::VeterinarianID::get() { return veterinarianID; }
void Veterinarian::VeterinarianID::set(int value) { veterinarianID = value; }

String^ Veterinarian::Name::get() { return name; }
void Veterinarian::Name::set(String^ value)
{
    name = value != nullptr ? value->Trim() : "";
}

String^ Veterinarian::Telephone::get() { return telephone; }
void Veterinarian::Telephone::set(String^ value)
{
    telephone = value != nullptr ? value->Trim() : "";
}

String^ Veterinarian::Specialization::get() { return specialization; }
void Veterinarian::Specialization::set(String^ value)
{
    specialization = value != nullptr ? value->Trim() : "General Veterinary";
}

String^ Veterinarian::displayVeterinarian()
{
    return "Veterinarian ID: " + veterinarianID.ToString() +
           "\r\nName: " + name +
           "\r\nTelephone: " + (String::IsNullOrWhiteSpace(telephone) ? "None" : telephone) +
           "\r\nSpecialization: " + specialization;
}

bool Veterinarian::isValidTelephone(String^ phone)
{
    if (String::IsNullOrWhiteSpace(phone)) return true;
    String^ t = phone->Trim();
    return t->Length >= 7 && t->Length <= 15;
}
