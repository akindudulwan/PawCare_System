#pragma once
using namespace System;

namespace PawCare
{
    public ref class MedicalRecord
    {
    private:
        int recordID;
        int appointmentID;
        int petID;
        String^ diagnosis;
        String^ treatment;
        String^ vaccination;
        String^ notes;
        String^ recordDate;

    public:
        MedicalRecord();
        MedicalRecord(int id, int apptId, int pId, String^ diag,
                      String^ treat, String^ vacc, String^ note, String^ date);

        property int RecordID
        {
            int get();
            void set(int value);
        }

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

        property String^ Diagnosis
        {
            String^ get();
            void set(String^ value);
        }

        property String^ Treatment
        {
            String^ get();
            void set(String^ value);
        }

        property String^ Vaccination
        {
            String^ get();
            void set(String^ value);
        }

        property String^ Notes
        {
            String^ get();
            void set(String^ value);
        }

        property String^ RecordDate
        {
            String^ get();
            void set(String^ value);
        }

        void addMedicalRecord();
        void updateMedicalRecord(String^ newDiagnosis, String^ newTreatment,
                                 String^ newVaccination, String^ newNotes);
        String^ displayMedicalRecord();

        static bool isValidDateFormat(String^ dateStr);
    };
}
