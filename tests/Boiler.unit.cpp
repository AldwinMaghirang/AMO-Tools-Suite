#include "catch.hpp"
#include <ssmt/Boiler.h>

TEST_CASE( "Calculate Boiler properties", "[Boiler][ssmt]") {
    auto b = Boiler(10, 85, 2, 20, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 45);
    CHECK(b.getSteamProperties()["steamEnergyFlow"] == Approx(110.7533647509));
    CHECK(b.getFeedwaterProperties()["feedwaterMassFlow"] == Approx(45.9183673469));
    CHECK(b.getFeedwaterProperties()["feedwaterEnergyFlow"] == Approx(64.6469770669));
    CHECK(b.getBlowdownProperties()["blowdownMassFlow"] == Approx(0.9183673469));
    CHECK(b.getBlowdownProperties()["blowdownEnergyFlow"] == Approx(1.6779495529));
    CHECK( b.getBoilerEnergy() == Approx(47.7843372368));
    CHECK(b.getFuelEnergy() == Approx(56.2168673374));

    auto b2 = Boiler(0.3631, 72.4, 3.7, 5.5766, SteamProperties::ThermodynamicQuantity::QUALITY, 1, 10864);
    CHECK(b2.getFuelEnergy() == Approx(33344.279478971));
}
