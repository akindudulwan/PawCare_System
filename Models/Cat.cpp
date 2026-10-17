#include "Cat.h"

using namespace PawCare;

Cat::Cat() : Pet()
{
    petType = "Cat";
}

Cat::Cat(int id, int owner, String^ petName, String^ petBreed,
         int petAge, String^ petGender)
    : Pet(id, owner, petName, "Cat", petBreed, petAge, petGender)
{
}

double Cat::calculateConsultationFee()
{
    return CAT_CONSULTATION_FEE;
}

String^ Cat::displayPetInfo()
{
    return "[CAT]\r\n" + Pet::displayPetInfo();
}
