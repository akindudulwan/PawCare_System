#pragma once
#using <System.dll>
#using <System.Data.dll>
#using <MySql.Data.dll>

#include "../Models/Owner.h"
#include "../Models/Veterinarian.h"
#include "../Models/Pet.h"
#include "../Models/Dog.h"
#include "../Models/Cat.h"
#include "../Models/Appointment.h"
#include "../Models/MedicalRecord.h"
#include "../Models/Payment.h"

using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;

namespace PawCare
{
    public ref class DatabaseManager
    {
    private:
        MySqlConnection^ connection;
        String^ connectionString;

        literal String^ DEFAULT_SERVER = "localhost";
        literal int DEFAULT_PORT = 3306;
        literal String^ DEFAULT_DATABASE = "pawcare_db";
        literal String^ DEFAULT_UID = "root";
        literal String^ DEFAULT_PASSWORD = "2004";

    public:
        DatabaseManager();
        DatabaseManager(String^ connStr);
        DatabaseManager(String^ server, int port, String^ database, String^ uid, String^ password);
        virtual ~DatabaseManager();
        !DatabaseManager();

        property String^ ConnectionString
        {
            String^ get();
            void set(String^ value);
        }

        bool connect();
        void disconnect();
        bool isConnected();
        MySqlConnection^ getConnection();

        MySqlTransaction^ beginTransaction();

        bool insertOwner(Owner^ owner);
        Owner^ getOwnerById(int ownerId);
        List<Owner^>^ getAllOwners();
        bool updateOwner(Owner^ owner);
        bool deleteOwner(int ownerId);

        bool insertVeterinarian(Veterinarian^ vet);
        Veterinarian^ getVeterinarianById(int vetId);
        List<Veterinarian^>^ getAllVeterinarians();
        bool updateVeterinarian(Veterinarian^ vet);
        bool deleteVeterinarian(int vetId);

        bool insertPet(Pet^ pet);
        Pet^ getPetById(int petId);
        List<Pet^>^ getPetsByOwnerId(int ownerId);
        List<Pet^>^ getAllPets();
        bool updatePet(Pet^ pet);
        bool deletePet(int petId);

        bool insertAppointment(Appointment^ appt);
        Appointment^ getAppointmentById(int apptId);
        List<Appointment^>^ getAllAppointments();
        List<Appointment^>^ getAppointmentsByPetId(int petId);
        bool updateAppointment(Appointment^ appt);
        bool changeAppointmentStatus(int apptId, String^ newStatus);
        bool isVeterinarianAvailable(int vetId, String^ date, String^ time, int excludeApptId);

        bool insertMedicalRecord(MedicalRecord^ record);
        MedicalRecord^ getMedicalRecordById(int recordId);
        List<MedicalRecord^>^ getMedicalRecordsByPetId(int petId);
        List<MedicalRecord^>^ getAllMedicalRecords();
        bool updateMedicalRecord(MedicalRecord^ record);

        bool insertPayment(Payment^ payment);
        Payment^ getPaymentById(int paymentId);
        Payment^ getPaymentByAppointmentId(int apptId);
        bool updatePaymentStatus(int paymentId, String^ newStatus);

        bool processAppointmentPayment(int apptId, Payment^ payment);

        static String^ buildConnectionString(String^ server, int port, String^ database, String^ uid, String^ password);
    };
}
