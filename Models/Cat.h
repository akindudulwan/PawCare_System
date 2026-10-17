#pragma once
#include "Pet.h"

namespace PawCare
{
    public ref class Cat : public Pet
    {
    public:
        literal double CAT_CONSULTATION_FEE = 1100.00;

        Cat();
        Cat(int id, int owner, String^ petName, String^ petBreed,
            int petAge, String^ petGender);

        virtual double calculateConsultationFee() override;
        virtual String^ displayPetInfo() override;
    };
}
