#pragma once
using namespace System;

namespace PawCare
{
    public ref class Payment
    {
    private:
        int paymentID;
        int appointmentID;
        double consultationFee;
        double treatmentFee;
        double otherFee;
        double totalAmount;
        String^ paymentMethod;
        String^ paymentStatus;

        void recalculateTotal();

    public:

        literal String^ METHOD_CASH = "Cash";
        literal String^ METHOD_CARD = "Card";
        literal String^ METHOD_BANK_TRANSFER = "Bank Transfer";
        literal String^ METHOD_ONLINE = "Online";

        literal String^ STATUS_PENDING = "PENDING";
        literal String^ STATUS_PAID = "PAID";
        literal String^ STATUS_FAILED = "FAILED";
        literal String^ STATUS_CANCELLED = "CANCELLED";
        literal String^ STATUS_REFUNDED = "REFUNDED";

        Payment();
        Payment(int id, int apptId, double consultFee, double treatFee, double othFee, String^ method);

        property int PaymentID
        {
            int get();
            void set(int value);
        }

        property int AppointmentID
        {
            int get();
            void set(int value);
        }

        property double ConsultationFee
        {
            double get();
            void set(double value);
        }

        property double TreatmentFee
        {
            double get();
            void set(double value);
        }

        property double OtherFee
        {
            double get();
            void set(double value);
        }

        property double TotalAmount
        {
            double get();
        }

        property String^ PaymentMethod
        {
            String^ get();
            void set(String^ value);
        }

        property String^ PaymentStatus
        {
            String^ get();
            void set(String^ value);
        }

        double calculateTotal();
        bool processPayment();
        void markFailed();
        void markRefunded();
        String^ displayPayment();

        static bool isValidMethod(String^ method);
        static bool isValidStatus(String^ status);
    };
}
