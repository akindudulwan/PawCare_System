#include "Pet.h"

using namespace PawCare;

Pet::Pet()
{
    petID = 0;
    ownerID = 0;
    name = "";
    petType = "General";
    breed = "";
    age = 0;
    gender = "Male";
}

Pet::Pet(int id, int owner, String^ petName, String^ type,
         String^ petBreed, int petAge, String^ petGender)
{
    petID = id;
    ownerID = owner;
    name = petName != nullptr ? petName->Trim() : "";
    petType = type != nullptr ? type->Trim() : "General";
    breed = petBreed != nullptr ? petBreed->Trim() : "";
    age = petAge >= 0 ? petAge : 0;
    gender = petGender != nullptr ? petGender->Trim() : "Male";
}

int Pet::PetID::get() { return petID; }
void Pet::PetID::set(int value) { petID = value; }

int Pet::OwnerID::get() { return ownerID; }
void Pet::OwnerID::set(int value) { ownerID = value; }

String^ Pet::Name::get() { return name; }
void Pet::Name::set(String^ value)
{
    name = value != nullptr ? value->Trim() : "";
}

String^ Pet::PetType::get() { return petType; }
void Pet::PetType::set(String^ value)
{
    petType = value != nullptr ? value->Trim() : "General";
}

String^ Pet::Breed::get() { return breed; }
void Pet::Breed::set(String^ value)
{
    breed = value != nullptr ? value->Trim() : "";
}

int Pet::Age::get() { return age; }
void Pet::Age::set(int value)
{
    age = value >= 0 ? value : 0;
}

String^ Pet::Gender::get() { return gender; }
void Pet::Gender::set(String^ value)
{
    gender = value != nullptr ? value->Trim() : "Male";
}

double Pet::calculateConsultationFee()
{
    return BASE_CONSULTATION_FEE;
}

String^ Pet::displayPetInfo()
{
    return "Pet ID: " + petID.ToString() +
           "\r\nPet: " + name +
           "\r\nType: " + petType +
           "\r\nBreed: " + breed +
           "\r\nAge: " + age.ToString() + " years" +
           "\r\nGender: " + gender;
}

bool Pet::isValidGender(String^ g)
{
    if (String::IsNullOrWhiteSpace(g)) return false;
    String^ trimmed = g->Trim();
    return String::Equals(trimmed, "Male", StringComparison::OrdinalIgnoreCase) ||
           String::Equals(trimmed, "Female", StringComparison::OrdinalIgnoreCase) ||
           String::Equals(trimmed, "Unknown", StringComparison::OrdinalIgnoreCase);
}
