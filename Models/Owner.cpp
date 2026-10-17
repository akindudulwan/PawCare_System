#include "Owner.h"

using namespace PawCare;

Owner::Owner()
{
    ownerID = 0;
    name = "";
    telephone = "";
    email = "";
    address = "";
}

Owner::Owner(int id, String^ ownerName, String^ phone, String^ ownerEmail, String^ addr)
{
    ownerID = id;
    name = ownerName != nullptr ? ownerName->Trim() : "";
    telephone = phone != nullptr ? phone->Trim() : "";
    email = ownerEmail != nullptr ? ownerEmail->Trim() : "";
    address = addr != nullptr ? addr->Trim() : "";
}

int Owner::OwnerID::get() { return ownerID; }
void Owner::OwnerID::set(int value) { ownerID = value; }

String^ Owner::Name::get() { return name; }
void Owner::Name::set(String^ value)
{
    name = value != nullptr ? value->Trim() : "";
}

String^ Owner::Telephone::get() { return telephone; }
void Owner::Telephone::set(String^ value)
{
    telephone = value != nullptr ? value->Trim() : "";
}

String^ Owner::Email::get() { return email; }
void Owner::Email::set(String^ value)
{
    email = value != nullptr ? value->Trim() : "";
}

String^ Owner::Address::get() { return address; }
void Owner::Address::set(String^ value)
{
    address = value != nullptr ? value->Trim() : "";
}

String^ Owner::displayOwner()
{
    return "Owner ID: " + ownerID.ToString() +
           "\r\nName: " + name +
           "\r\nTelephone: " + telephone +
           "\r\nEmail: " + (String::IsNullOrWhiteSpace(email) ? "None" : email) +
           "\r\nAddress: " + (String::IsNullOrWhiteSpace(address) ? "None" : address);
}

bool Owner::isValidTelephone(String^ phone)
{
    if (String::IsNullOrWhiteSpace(phone)) return false;
    String^ t = phone->Trim();
    return t->Length >= 7 && t->Length <= 15;
}

bool Owner::isValidEmail(String^ emailStr)
{
    if (String::IsNullOrWhiteSpace(emailStr)) return true;
    return emailStr->Contains("@") && emailStr->Contains(".");
}
