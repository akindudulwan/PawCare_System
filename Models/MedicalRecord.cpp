#include "MedicalRecord.h"

using namespace PawCare;

MedicalRecord::MedicalRecord()
{
    recordID = 0;
    appointmentID = 0;
    petID = 0;
    diagnosis = "";
    treatment = "";
    vaccination = "";
    notes = "";
    recordDate = "";
}

MedicalRecord::MedicalRecord(int id, int apptId, int pId, String^ diag,
                             String^ treat, String^ vacc, String^ note, String^ date)
{
    recordID = id;
    appointmentID = apptId;
    petID = pId;
    diagnosis = diag != nullptr ? diag->Trim() : "";
    treatment = treat != nullptr ? treat->Trim() : "";
    vaccination = vacc != nullptr ? vacc->Trim() : "";
    notes = note != nullptr ? note->Trim() : "";
    recordDate = date != nullptr ? date->Trim() : "";
}

int MedicalRecord::RecordID::get() { return recordID; }
void MedicalRecord::RecordID::set(int value) { recordID = value; }

int MedicalRecord::AppointmentID::get() { return appointmentID; }
void MedicalRecord::AppointmentID::set(int value) { appointmentID = value; }

int MedicalRecord::PetID::get() { return petID; }
void MedicalRecord::PetID::set(int value) { petID = value; }

String^ MedicalRecord::Diagnosis::get() { return diagnosis; }
void MedicalRecord::Diagnosis::set(String^ value)
{
    diagnosis = value != nullptr ? value->Trim() : "";
}

String^ MedicalRecord::Treatment::get() { return treatment; }
void MedicalRecord::Treatment::set(String^ value)
{
    treatment = value != nullptr ? value->Trim() : "";
}

String^ MedicalRecord::Vaccination::get() { return vaccination; }
void MedicalRecord::Vaccination::set(String^ value)
{
    vaccination = value != nullptr ? value->Trim() : "";
}

String^ MedicalRecord::Notes::get() { return notes; }
void MedicalRecord::Notes::set(String^ value)
{
    notes = value != nullptr ? value->Trim() : "";
}

String^ MedicalRecord::RecordDate::get() { return recordDate; }
void MedicalRecord::RecordDate::set(String^ value)
{
    recordDate = value != nullptr ? value->Trim() : "";
}

void MedicalRecord::addMedicalRecord()
{
}

void MedicalRecord::updateMedicalRecord(String^ newDiagnosis, String^ newTreatment,
                                       String^ newVaccination, String^ newNotes)
{
    if (!String::IsNullOrWhiteSpace(newDiagnosis)) diagnosis = newDiagnosis->Trim();
    if (!String::IsNullOrWhiteSpace(newTreatment)) treatment = newTreatment->Trim();
    if (!String::IsNullOrWhiteSpace(newVaccination)) vaccination = newVaccination->Trim();
    if (!String::IsNullOrWhiteSpace(newNotes)) notes = newNotes->Trim();
}

String^ MedicalRecord::displayMedicalRecord()
{
    return "Record ID: " + recordID.ToString() +
           "\r\nAppointment ID: " + appointmentID.ToString() +
           "\r\nPet ID: " + petID.ToString() +
           "\r\nDiagnosis: " + diagnosis +
           "\r\nTreatment: " + treatment +
           "\r\nVaccination: " + (String::IsNullOrWhiteSpace(vaccination) ? "None" : vaccination) +
           "\r\nNotes: " + (String::IsNullOrWhiteSpace(notes) ? "None" : notes) +
           "\r\nRecord Date: " + recordDate;
}

bool MedicalRecord::isValidDateFormat(String^ dateStr)
{
    return !String::IsNullOrWhiteSpace(dateStr);
}
