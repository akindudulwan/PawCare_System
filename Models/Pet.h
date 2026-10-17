#pragma once
using namespace System;

namespace PawCare
{
    public ref class Pet
    {
    protected:
        int petID;
        int ownerID;
        String^ name;
        String^ petType;
        String^ breed;
        int age;
        String^ gender;

    public:
        literal double BASE_CONSULTATION_FEE = 1000.00;

        Pet();
        Pet(int id, int owner, String^ petName, String^ type,
            String^ petBreed, int petAge, String^ petGender);

        property int PetID
        {
            int get();
            void set(int value);
        }

        property int OwnerID
        {
            int get();
            void set(int value);
        }

        property String^ Name
        {
            String^ get();
            void set(String^ value);
        }

        property String^ PetType
        {
            String^ get();
            void set(String^ value);
        }

        property String^ Breed
        {
            String^ get();
            void set(String^ value);
        }

        property int Age
        {
            int get();
            void set(int value);
        }

        property String^ Gender
        {
            String^ get();
            void set(String^ value);
        }

        virtual double calculateConsultationFee();
        virtual String^ displayPetInfo();

        static bool isValidGender(String^ g);
    };
}
