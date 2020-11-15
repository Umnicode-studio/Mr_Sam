// (c) DPACK.inc


#include "Weapon.h"

void AWeapon::Fire()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
            "AWeapon is abstract class");
    }
}
