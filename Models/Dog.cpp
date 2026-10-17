#include "Dog.h"

using namespace PawCare;

Dog::Dog() : Pet()
{
    petType = "Dog";
}

Dog::Dog(int id, int owner, String^ petName, String^ petBreed,
         int petAge, String^ petGender)
    : Pet(id, owner, petName, "Dog", petBreed, petAge, petGender)
{
}

double Dog::calculateConsultationFee()
{
    return DOG_CONSULTATION_FEE;
}

String^ Dog::displayPetInfo()
{
    return "[DOG]\r\n" + Pet::displayPetInfo();
}
