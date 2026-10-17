#pragma once
#include "Pet.h"

namespace PawCare
{
    public ref class Dog : public Pet
    {
    public:
        literal double DOG_CONSULTATION_FEE = 1200.00;

        Dog();
        Dog(int id, int owner, String^ petName, String^ petBreed,
            int petAge, String^ petGender);

        virtual double calculateConsultationFee() override;
        virtual String^ displayPetInfo() override;
    };
}
