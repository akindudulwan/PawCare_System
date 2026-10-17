#include "Appointment.h"

using namespace PawCare;

Appointment::Appointment()
{
    appointmentID = 0;
    petID = 0;
    veterinarianID = 0;
    appointmentDate = "";
    appointmentTime = "";
    reason = "";
    status = STATUS_BOOKED;
}

Appointment::Appointment(int id, int pId, int vetId, String^ date, String^ time, String^ apptReason)
{
    appointmentID = id;
    petID = pId;
    veterinarianID = vetId;
    appointmentDate = date != nullptr ? date->Trim() : "";
    appointmentTime = time != nullptr ? time->Trim() : "";
    reason = apptReason != nullptr ? apptReason->Trim() : "";
    status = STATUS_BOOKED;
}

Appointment::Appointment(int id, int pId, int vetId, String^ date, String^ time, String^ apptReason, String^ apptStatus)
{
    appointmentID = id;
    petID = pId;
    veterinarianID = vetId;
    appointmentDate = date != nullptr ? date->Trim() : "";
    appointmentTime = time != nullptr ? time->Trim() : "";
    reason = apptReason != nullptr ? apptReason->Trim() : "";
    status = !String::IsNullOrWhiteSpace(apptStatus) ? apptStatus->Trim() : STATUS_BOOKED;
}

int Appointment::AppointmentID::get() { return appointmentID; }
void Appointment::AppointmentID::set(int value) { appointmentID = value; }

int Appointment::PetID::get() { return petID; }
void Appointment::PetID::set(int value) { petID = value; }

int Appointment::VeterinarianID::get() { return veterinarianID; }
void Appointment::VeterinarianID::set(int value) { veterinarianID = value; }

String^ Appointment::AppointmentDate::get() { return appointmentDate; }
void Appointment::AppointmentDate::set(String^ value)
{
    appointmentDate = value != nullptr ? value->Trim() : "";
}

String^ Appointment::AppointmentTime::get() { return appointmentTime; }
void Appointment::AppointmentTime::set(String^ value)
{
    appointmentTime = value != nullptr ? value->Trim() : "";
}

String^ Appointment::Reason::get() { return reason; }
void Appointment::Reason::set(String^ value)
{
    reason = value != nullptr ? value->Trim() : "";
}

String^ Appointment::Status::get() { return status; }
void Appointment::Status::set(String^ value)
{
    status = !String::IsNullOrWhiteSpace(value) ? value->Trim() : STATUS_BOOKED;
}

void Appointment::createAppointment()
{
    status = STATUS_BOOKED;
}

void Appointment::updateAppointment(String^ date, String^ time, String^ newReason)
{
    if (!String::IsNullOrWhiteSpace(date)) appointmentDate = date->Trim();
    if (!String::IsNullOrWhiteSpace(time)) appointmentTime = time->Trim();
    if (!String::IsNullOrWhiteSpace(newReason)) reason = newReason->Trim();
}

void Appointment::cancelAppointment()
{
    status = STATUS_CANCELLED;
}

void Appointment::completeAppointment()
{
    status = STATUS_COMPLETED;
}

void Appointment::confirmAppointment()
{
    status = STATUS_CONFIRMED;
}

void Appointment::changeStatus(String^ newStatus)
{
    if (!String::IsNullOrWhiteSpace(newStatus))
    {
        status = newStatus->Trim();
    }
}

void Appointment::setPersistedStatus(String^ persistedStatus)
{
    status = !String::IsNullOrWhiteSpace(persistedStatus) ? persistedStatus->Trim() : STATUS_BOOKED;
}

bool Appointment::isModifiable()
{
    return status != STATUS_COMPLETED && status != STATUS_CANCELLED;
}

String^ Appointment::displayAppointment()
{
    return "Appointment ID: " + appointmentID.ToString() +
           "\r\nPet ID: " + petID.ToString() +
           "\r\nVeterinarian ID: " + veterinarianID.ToString() +
           "\r\nDate: " + appointmentDate +
           "\r\nTime: " + appointmentTime +
           "\r\nReason: " + reason +
           "\r\nStatus: " + status;
}

bool Appointment::isValidDateFormat(String^ dateStr)
{
    return !String::IsNullOrWhiteSpace(dateStr);
}

bool Appointment::isValidTimeFormat(String^ timeStr)
{
    return !String::IsNullOrWhiteSpace(timeStr);
}

bool Appointment::isValidStatus(String^ statusStr)
{
    if (String::IsNullOrWhiteSpace(statusStr)) return false;
    return statusStr == STATUS_BOOKED ||
           statusStr == STATUS_CONFIRMED ||
           statusStr == STATUS_COMPLETED ||
           statusStr == STATUS_CANCELLED;
}

bool Appointment::isValidTransition(String^ currentStatus, String^ newStatus)
{
    return true;
}
