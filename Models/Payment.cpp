#include "Payment.h"

using namespace PawCare;

Payment::Payment()
{
    paymentID = 0;
    appointmentID = 0;
    consultationFee = 0.0;
    treatmentFee = 0.0;
    otherFee = 0.0;
    totalAmount = 0.0;
    paymentMethod = METHOD_CASH;
    paymentStatus = STATUS_PENDING;
}

Payment::Payment(int id, int apptId, double consultFee, double treatFee, double othFee, String^ method)
{
    paymentID = id;
    appointmentID = apptId;
    consultationFee = consultFee >= 0 ? Math::Round(consultFee, 2) : 0.0;
    treatmentFee = treatFee >= 0 ? Math::Round(treatFee, 2) : 0.0;
    otherFee = othFee >= 0 ? Math::Round(othFee, 2) : 0.0;
    paymentMethod = !String::IsNullOrWhiteSpace(method) ? method->Trim() : METHOD_CASH;
    paymentStatus = STATUS_PENDING;
    recalculateTotal();
}

void Payment::recalculateTotal()
{
    totalAmount = Math::Round(consultationFee + treatmentFee + otherFee, 2);
}

int Payment::PaymentID::get() { return paymentID; }
void Payment::PaymentID::set(int value) { paymentID = value; }

int Payment::AppointmentID::get() { return appointmentID; }
void Payment::AppointmentID::set(int value) { appointmentID = value; }

double Payment::ConsultationFee::get() { return consultationFee; }
void Payment::ConsultationFee::set(double value)
{
    consultationFee = value >= 0 ? Math::Round(value, 2) : 0.0;
    recalculateTotal();
}

double Payment::TreatmentFee::get() { return treatmentFee; }
void Payment::TreatmentFee::set(double value)
{
    treatmentFee = value >= 0 ? Math::Round(value, 2) : 0.0;
    recalculateTotal();
}

double Payment::OtherFee::get() { return otherFee; }
void Payment::OtherFee::set(double value)
{
    otherFee = value >= 0 ? Math::Round(value, 2) : 0.0;
    recalculateTotal();
}

double Payment::TotalAmount::get()
{
    recalculateTotal();
    return totalAmount;
}

String^ Payment::PaymentMethod::get() { return paymentMethod; }
void Payment::PaymentMethod::set(String^ value)
{
    paymentMethod = !String::IsNullOrWhiteSpace(value) ? value->Trim() : METHOD_CASH;
}

String^ Payment::PaymentStatus::get() { return paymentStatus; }
void Payment::PaymentStatus::set(String^ value)
{
    paymentStatus = !String::IsNullOrWhiteSpace(value) ? value->Trim() : STATUS_PENDING;
}

double Payment::calculateTotal()
{
    recalculateTotal();
    return totalAmount;
}

bool Payment::processPayment()
{
    paymentStatus = STATUS_PAID;
    return true;
}

void Payment::markFailed()
{
    paymentStatus = STATUS_FAILED;
}

void Payment::markRefunded()
{
    paymentStatus = STATUS_REFUNDED;
}

String^ Payment::displayPayment()
{
    recalculateTotal();
    return "Payment ID: " + paymentID.ToString() +
           "\r\nAppointment ID: " + appointmentID.ToString() +
           "\r\nConsultation Fee: Rs. " + consultationFee.ToString("F2") +
           "\r\nTreatment Fee: Rs. " + treatmentFee.ToString("F2") +
           "\r\nOther Fee: Rs. " + otherFee.ToString("F2") +
           "\r\nTotal: Rs. " + totalAmount.ToString("F2") +
           "\r\nMethod: " + paymentMethod +
           "\r\nStatus: " + paymentStatus;
}

bool Payment::isValidMethod(String^ method)
{
    if (String::IsNullOrWhiteSpace(method)) return false;
    return method == METHOD_CASH ||
           method == METHOD_CARD ||
           method == METHOD_BANK_TRANSFER ||
           method == METHOD_ONLINE;
}

bool Payment::isValidStatus(String^ status)
{
    if (String::IsNullOrWhiteSpace(status)) return false;
    return status == STATUS_PENDING ||
           status == STATUS_PAID ||
           status == STATUS_FAILED ||
           status == STATUS_CANCELLED ||
           status == STATUS_REFUNDED;
}
