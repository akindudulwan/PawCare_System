#pragma once
using namespace System;

namespace PawCare
{
    public ref class Appointment
    {
    private:
        int appointmentID;
        int petID;
        int veterinarianID;
        String^ appointmentDate;
        String^ appointmentTime;
        String^ reason;
        String^ status;

    public:

        literal String^ STATUS_BOOKED = "BOOKED";
        literal String^ STATUS_CONFIRMED = "CONFIRMED";
        literal String^ STATUS_COMPLETED = "COMPLETED";
        literal String^ STATUS_CANCELLED = "CANCELLED";

        Appointment();
        Appointment(int id, int pId, int vetId, String^ date, String^ time, String^ apptReason);
        Appointment(int id, int pId, int vetId, String^ date, String^ time, String^ apptReason, String^ apptStatus);

        property int AppointmentID
        {
            int get();
            void set(int value);
        }

        property int PetID
        {
            int get();
            void set(int value);
        }

        property int VeterinarianID
        {
            int get();
            void set(int value);
        }

        property String^ AppointmentDate
        {
            String^ get();
            void set(String^ value);
        }

        property String^ AppointmentTime
        {
            String^ get();
            void set(String^ value);
        }

        property String^ Reason
        {
            String^ get();
            void set(String^ value);
        }

        property String^ Status
        {
            String^ get();
            void set(String^ value);
        }

        void createAppointment();
        void updateAppointment(String^ date, String^ time, String^ newReason);
        void cancelAppointment();
        void completeAppointment();
        void confirmAppointment();
        void changeStatus(String^ newStatus);
        void setPersistedStatus(String^ persistedStatus);
        bool isModifiable();
        String^ displayAppointment();

        static bool isValidDateFormat(String^ dateStr);
        static bool isValidTimeFormat(String^ timeStr);
        static bool isValidStatus(String^ statusStr);
        static bool isValidTransition(String^ currentStatus, String^ newStatus);
    };
}
