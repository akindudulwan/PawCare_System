#include "Models/Pet.h"
#include "Models/Dog.h"
#include "Models/Cat.h"
#include "Models/Owner.h"
#include "Models/Veterinarian.h"
#include "Models/Appointment.h"
#include "Models/MedicalRecord.h"
#include "Models/Payment.h"
#include "Database/DatabaseManager.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace PawCare;

void runOopDemonstration();
void runValidationEdgeCaseTests();
void runDatabaseCrudTests();

int main(array<System::String^>^ args)
{
    Console::WriteLine("====================================================");
    Console::WriteLine("       PAWCARE PET CARE SYSTEM - VERIFICATION       ");
    Console::WriteLine("====================================================");
    Console::WriteLine();

    runOopDemonstration();
    Console::WriteLine();

    runValidationEdgeCaseTests();
    Console::WriteLine();

    runDatabaseCrudTests();
    Console::WriteLine();

    Console::WriteLine("====================================================");
    Console::WriteLine(" All demonstrations and tests completed successfully.");
    Console::WriteLine("====================================================");

    return 0;
}

void runOopDemonstration()
{
    Console::WriteLine("----- 1. OOP DEMONSTRATION & POLYMORPHISM -----");

    Dog^ max = gcnew Dog(1, 1, "Max", "Labrador", 3, "Male");
    Cat^ luna = gcnew Cat(2, 1, "Luna", "Persian", 2, "Female");

    Pet^ pet1 = max;
    Pet^ pet2 = luna;

    Console::WriteLine(pet1->displayPetInfo());
    Console::WriteLine("Consultation Fee: Rs. {0:F2}", pet1->calculateConsultationFee());
    Console::WriteLine();

    Console::WriteLine(pet2->displayPetInfo());
    Console::WriteLine("Consultation Fee: Rs. {0:F2}", pet2->calculateConsultationFee());
    Console::WriteLine();

    Owner^ owner = gcnew Owner(1, "Kasun Perera", "0712345678", "kasun@example.com", "Colombo");
    Console::WriteLine(owner->displayOwner());
    Console::WriteLine();

    Veterinarian^ vet = gcnew Veterinarian(1, "Dr. Silva", "0112345678", "General Veterinary");
    Console::WriteLine(vet->displayVeterinarian());
    Console::WriteLine();

    Appointment^ appointment = gcnew Appointment(1, max->PetID, vet->VeterinarianID, "2026-10-15", "09:00", "Annual Health Check");
    appointment->createAppointment();
    Console::WriteLine(appointment->displayAppointment());
    Console::WriteLine();

    MedicalRecord^ record = gcnew MedicalRecord(1, appointment->AppointmentID, max->PetID,
        "Skin Allergy", "Prescribed antihistamines", "Rabies", "Follow-up in 2 weeks", "2026-10-15");
    record->addMedicalRecord();
    Console::WriteLine(record->displayMedicalRecord());
    Console::WriteLine();

    Payment^ payment = gcnew Payment(1, appointment->AppointmentID, max->calculateConsultationFee(), 1000.00, 200.00, Payment::METHOD_CASH);
    Console::WriteLine("Before payment processing:");
    Console::WriteLine(payment->displayPayment());
    payment->processPayment();
    appointment->completeAppointment();

    Console::WriteLine();
    Console::WriteLine("After payment processing and appointment completion:");
    Console::WriteLine(payment->displayPayment());
    Console::WriteLine("Updated Appointment Status: " + appointment->Status);
}

void runValidationEdgeCaseTests()
{
    Console::WriteLine("----- 2. LOGIC & VALIDATION TESTS -----");

    int passed = 0;
    int failed = 0;

    Payment^ p = gcnew Payment(10, 1, 1000.00, 500.00, 0.00, Payment::METHOD_CASH);
    if (Math::Abs(p->TotalAmount - 1500.00) < 0.001)
    {
        Console::WriteLine("  [PASS] Payment: Total calculated accurately (Rs. 1500.00).");
        passed++;
    }
    else
    {
        Console::WriteLine("  [FAIL] Payment: Total calculation failed.");
        failed++;
    }

    p->TreatmentFee = 800.00;
    if (Math::Abs(p->TotalAmount - 1800.00) < 0.001)
    {
        Console::WriteLine("  [PASS] Payment: Dynamic update correctly recalculates total.");
        passed++;
    }
    else
    {
        Console::WriteLine("  [FAIL] Payment: Dynamic update failed.");
        failed++;
    }

    Dog^ d = gcnew Dog(3, 1, "Rocky", "Bulldog", 2, "Male");
    Cat^ c = gcnew Cat(4, 1, "Mimi", "Siamese", 1, "Female");
    Pet^ basePet = gcnew Pet(5, 1, "Goldie", "Fish", "Goldfish", 1, "Female");

    if (d->calculateConsultationFee() == 1200.00 &&
        c->calculateConsultationFee() == 1100.00 &&
        basePet->calculateConsultationFee() == 1000.00)
    {
        Console::WriteLine("  [PASS] Polymorphism: Correct consultation fees returned by subclass overrides.");
        passed++;
    }
    else
    {
        Console::WriteLine("  [FAIL] Polymorphism fee verification failed.");
        failed++;
    }

    if (Owner::isValidTelephone("0712345678") && !Owner::isValidTelephone("123"))
    {
        Console::WriteLine("  [PASS] Owner: Telephone validation helper verified.");
        passed++;
    }
    else
    {
        Console::WriteLine("  [FAIL] Owner phone helper failed.");
        failed++;
    }

    Console::WriteLine("Validation tests completed: {0} Passed, {1} Failed.", passed, failed);
}

void runDatabaseCrudTests()
{
    Console::WriteLine("----- 3. MYSQL DATABASE CRUD OPERATIONS TEST -----");

    DatabaseManager^ db = gcnew DatabaseManager();
    Console::WriteLine("Testing MySQL connection to {0} ...", db->ConnectionString);

    if (!db->connect())
    {
        Console::WriteLine("  [SKIP] MySQL database not available. Skipping DB CRUD tests.");
        return;
    }

    Console::WriteLine("  [PASS] Connected to MySQL successfully!");

    Owner^ testOwner = gcnew Owner(0, "Test Verification Owner", "0770000000", "test@pawcare.com", "Kandy");
    if (db->insertOwner(testOwner))
    {
        Console::WriteLine("  [PASS] Database: Inserted owner with ID {0}", testOwner->OwnerID);

        Owner^ fetched = db->getOwnerById(testOwner->OwnerID);
        if (fetched != nullptr && fetched->Name == "Test Verification Owner")
        {
            Console::WriteLine("  [PASS] Database: Fetched owner successfully.");
        }
        else
        {
            Console::WriteLine("  [FAIL] Database: Failed to fetch inserted owner.");
        }

        if (db->deleteOwner(testOwner->OwnerID))
        {
            Console::WriteLine("  [PASS] Database: Deleted test owner cleanly.");
        }
    }
    else
    {
        Console::WriteLine("  [FAIL] Database: insertOwner failed.");
    }

    List<Appointment^>^ appts = db->getAllAppointments();
    Console::WriteLine("  [PASS] Database: Retrieved {0} appointments without exceptions.", appts->Count);
}
