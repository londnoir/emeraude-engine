/*
 * Emeraude/Physics/Physics.hpp
 * This file is part of Emeraude
 *
 * Copyright (C) 2012-2023 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude
 * 
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* C/C++ standard libraries. */
#include <cmath>

/* Local inclusions for usages. */
#include "Math/Vector.hpp"
#include "Constants.hpp"

namespace Emeraude::Physics
{
	// NOLINTBEGIN(*-magic-numbers)

	namespace SI
	{
		template< typename type_t = float >
		constexpr type_t Millimeter = static_cast< type_t >(0.001);

		template< typename type_t = float >
		constexpr type_t Centimeter = static_cast< type_t >(0.01);

		template< typename type_t = float >
		constexpr type_t Meter = static_cast< type_t >(1.0);

		template< typename type_t = float >
		constexpr type_t Kilometer = Meter< type_t > * static_cast< type_t >(1000);

		template< typename type_t = float >
		constexpr type_t Milligram = static_cast< type_t >(0.000001);

		template< typename type_t = float >
		constexpr type_t Gram = static_cast< type_t >(0.001);

		template< typename type_t = float >
		constexpr type_t Kilogram = static_cast< type_t >(1.0);

		template< typename type_t = float >
		constexpr type_t Tonne = Kilogram< type_t > * static_cast< type_t >(1000);

		template< typename type_t = float >
		constexpr type_t Millisecond = static_cast< type_t >(0.001);

		template< typename type_t = float >
		constexpr type_t Second = static_cast< type_t >(1.0);

		template< typename type_t = float >
		constexpr type_t Minute = Second< type_t > * static_cast< type_t >(60);

		template< typename type_t = float >
		constexpr type_t Hour = Minute< type_t > * static_cast< type_t >(60);
	}

	namespace DragCoefficient
	{
		/** @brief Drag coefficient for a sphere. */
		template< typename type_t = float >
		constexpr type_t Sphere = static_cast< type_t >(0.47);

		/** @brief Drag coefficient for a half sphere. */
		template< typename type_t = float >
		constexpr type_t HalfSphere = static_cast< type_t >(0.42);

		/** @brief Drag coefficient for a cone. */
		template< typename type_t = float >
		constexpr type_t Cone = static_cast< type_t >(0.50);

		/** @brief Drag coefficient for a cube. */
		template< typename type_t = float >
		constexpr type_t Cube = static_cast< type_t >(1.05);

		/** @brief Drag coefficient for a angled cube. */
		template< typename type_t = float >
		constexpr type_t AngledCube = static_cast< type_t >(0.80);

		/** @brief Drag coefficient for a long cylinder. */
		template< typename type_t = float >
		constexpr type_t LongCylinder = static_cast< type_t >(1.82);

		/** @brief Drag coefficient for a short cylinder. */
		template< typename type_t = float >
		constexpr type_t ShortCylinder = static_cast< type_t >(0.82);

		/** @brief Drag coefficient for a streamlined body. */
		template< typename type_t = float >
		constexpr type_t StreamlinedBody = static_cast< type_t >(0.04);

		/** @brief Drag coefficient for a streamlined half body. */
		template< typename type_t = float >
		constexpr type_t StreamlinedHalfBody = static_cast< type_t >(0.09);
	}

	namespace Gravity
	{
		/** @brief Earth gravity expressed in m/s² */
		template< typename type_t = float >
		constexpr type_t Earth = static_cast< type_t >(9.807);

		/** @brief Moon gravity expressed in m/s² */
		template< typename type_t = float >
		constexpr type_t Moon = static_cast< type_t >(1.622);

		/** @brief Mars gravity expressed in m/s² */
		template< typename type_t = float >
		constexpr type_t Mars = static_cast< type_t >(3.711);

		/** @brief Jupiter gravity expressed in m/s² */
		template< typename type_t = float >
		constexpr type_t Jupiter = static_cast< type_t >(24.79);
	}

	namespace Density
	{
		/** @brief Air density expressed in kg/m³ (Sea level a 15 degree). */
		template< typename type_t = float >
		constexpr type_t EarthStandardAir = static_cast< type_t >(1.225);

		/** @brief Water density expressed in kg/m³ (20 degree).
		 * @note References table (g/cm³) :
			0 0,999841
			1 0,9999
			2 0,999941
			3 0,999965
			4 0,999973
			5 0,999965
			6 0,999941
			7 0,999902
			8 0,999849
			9 0,999782
			10 0,999701
			11 0,999606
			12 0,999498
			13 0,999377
			14 0,999244
			15 0,999099
			16 0,998943
			17 0,998775
			18 0,998596
			19 0,998406
			20 0,998205 <- Chosen constant
			21 0,997994
			22 0,997772
			23 0,99754
			24 0,997299
			25 0,997047
			26 0,996785
			27 0,996515
			28 0,996235
			29 0,995946
			30 0,995649
			40 0,99222
			50 0,98803
			60 0,98320
			70 0,97778
			80 0,97182
			90 0,96535
			100 0,95840
		*/
		template< typename type_t = float >
		constexpr type_t EarthStandardWater = static_cast< type_t >(998.205);

		template< typename type_t = float >
		constexpr type_t AlfalfaGround = static_cast< type_t >(256);

		template< typename type_t = float >
		constexpr type_t Alum = static_cast< type_t >(817);

		template< typename type_t = float >
		constexpr type_t Alumina = static_cast< type_t >(961);

		template< typename type_t = float >
		constexpr type_t AluminumOxide = static_cast< type_t >(1522);

		template< typename type_t = float >
		constexpr type_t AmmoniaGas = static_cast< type_t >(0.77);

		template< typename type_t = float >
		constexpr type_t AmmoniumNitrate = static_cast< type_t >(730);

		template< typename type_t = float >
		constexpr type_t AmmoniumSulphateDry = static_cast< type_t >(1130);

		template< typename type_t = float >
		constexpr type_t AmmoniumSulphateWet = static_cast< type_t >(1290);

		template< typename type_t = float >
		constexpr type_t AndesiteSolid = static_cast< type_t >(2771);

		template< typename type_t = float >
		constexpr type_t Antimony = static_cast< type_t >(6696);

		template< typename type_t = float >
		constexpr type_t Apples = static_cast< type_t >(641);

		template< typename type_t = float >
		constexpr type_t Arsenic = static_cast< type_t >(5671);

		template< typename type_t = float >
		constexpr type_t AsbestosShredded = static_cast< type_t >(360);

		template< typename type_t = float >
		constexpr type_t AsbestosRock = static_cast< type_t >(1600);

		template< typename type_t = float >
		constexpr type_t AshesWet = static_cast< type_t >(810);

		template< typename type_t = float >
		constexpr type_t AshesDry = static_cast< type_t >(610);

		template< typename type_t = float >
		constexpr type_t AsphaltCrushed = static_cast< type_t >(721);

		template< typename type_t = float >
		constexpr type_t Babbitt = static_cast< type_t >(7272);

		template< typename type_t = float >
		constexpr type_t Bagasse = static_cast< type_t >(120);

		template< typename type_t = float >
		constexpr type_t BakeliteSolid = static_cast< type_t >(1362);

		template< typename type_t = float >
		constexpr type_t BakingPowder = static_cast< type_t >(721);

		template< typename type_t = float >
		constexpr type_t Barium = static_cast< type_t >(3780);

		template< typename type_t = float >
		constexpr type_t Bark = static_cast< type_t >(240);

		template< typename type_t = float >
		constexpr type_t Barley = static_cast< type_t >(609);

		template< typename type_t = float >
		constexpr type_t BariteCrushed = static_cast< type_t >(2883);

		template< typename type_t = float >
		constexpr type_t BasaltBroken = static_cast< type_t >(1954);

		template< typename type_t = float >
		constexpr type_t BasaltSolid = static_cast< type_t >(3011);

		template< typename type_t = float >
		constexpr type_t BauxiteCrushed = static_cast< type_t >(1281);

		template< typename type_t = float >
		constexpr type_t BeansCastor = static_cast< type_t >(577);

		template< typename type_t = float >
		constexpr type_t BeansCocoa = static_cast< type_t >(593);

		template< typename type_t = float >
		constexpr type_t BeansNavy = static_cast< type_t >(801);

		template< typename type_t = float >
		constexpr type_t BeansSoy = static_cast< type_t >(721);

		template< typename type_t = float >
		constexpr type_t Beeswax = static_cast< type_t >(961);

		template< typename type_t = float >
		constexpr type_t Beets = static_cast< type_t >(721);

		template< typename type_t = float >
		constexpr type_t Bentonite = static_cast< type_t >(593);

		template< typename type_t = float >
		constexpr type_t BicarbonateOSoda = static_cast< type_t >(689);

		template< typename type_t = float >
		constexpr type_t Bismuth = static_cast< type_t >(9787);

		template< typename type_t = float >
		constexpr type_t BonesPulverized = static_cast< type_t >(881);

		template< typename type_t = float >
		constexpr type_t Borax = static_cast< type_t >(849);

		template< typename type_t = float >
		constexpr type_t Bran = static_cast< type_t >(256);

		template< typename type_t = float >
		constexpr type_t BrewersGgrain = static_cast< type_t >(432);

		template< typename type_t = float >
		constexpr type_t BrickCommonRed = static_cast< type_t >(1922);

		template< typename type_t = float >
		constexpr type_t BrickFireClay = static_cast< type_t >(2403);

		template< typename type_t = float >
		constexpr type_t BrickSilica = static_cast< type_t >(2050);

		template< typename type_t = float >
		constexpr type_t BrickChrome = static_cast< type_t >(2803);

		template< typename type_t = float >
		constexpr type_t BrickMagnesia = static_cast< type_t >(2563);

		template< typename type_t = float >
		constexpr type_t Buckwheat = static_cast< type_t >(657);

		template< typename type_t = float >
		constexpr type_t Butter = static_cast< type_t >(865);

		template< typename type_t = float >
		constexpr type_t Cadmium = static_cast< type_t >(8650);

		template< typename type_t = float >
		constexpr type_t CalciumCarbide = static_cast< type_t >(1201);

		template< typename type_t = float >
		constexpr type_t Caliche = static_cast< type_t >(1442);

		template< typename type_t = float >
		constexpr type_t CarbonSolid = static_cast< type_t >(2146);

		template< typename type_t = float >
		constexpr type_t CarbonPowdered = static_cast< type_t >(80);

		template< typename type_t = float >
		constexpr type_t CarbonDioxide = static_cast< type_t >(1.98);

		template< typename type_t = float >
		constexpr type_t CarbonMonoxide = static_cast< type_t >(1.25);

		template< typename type_t = float >
		constexpr type_t Cardboard = static_cast< type_t >(689);

		template< typename type_t = float >
		constexpr type_t CementClinker = static_cast< type_t >(1415);

		template< typename type_t = float >
		constexpr type_t CementPortland = static_cast< type_t >(1506);

		template< typename type_t = float >
		constexpr type_t CementMortar = static_cast< type_t >(2162);

		template< typename type_t = float >
		constexpr type_t CementSlurry = static_cast< type_t >(1442);

		template< typename type_t = float >
		constexpr type_t ChalkSolid = static_cast< type_t >(2499);

		template< typename type_t = float >
		constexpr type_t ChalkLumpy = static_cast< type_t >(1442);

		template< typename type_t = float >
		constexpr type_t ChalkFine = static_cast< type_t >(1121);

		template< typename type_t = float >
		constexpr type_t Charcoal = static_cast< type_t >(208);

		template< typename type_t = float >
		constexpr type_t Chloroform = static_cast< type_t >(1522);

		template< typename type_t = float >
		constexpr type_t ChocolatePowder = static_cast< type_t >(641);

		template< typename type_t = float >
		constexpr type_t ChromicAcidFlake = static_cast< type_t >(1201);

		template< typename type_t = float >
		constexpr type_t Chromium = static_cast< type_t >(6856);

		template< typename type_t = float >
		constexpr type_t ChromiumOre = static_cast< type_t >(2162);

		template< typename type_t = float >
		constexpr type_t CindersFurnace = static_cast< type_t >(913);

		template< typename type_t = float >
		constexpr type_t CindersCoalAsh = static_cast< type_t >(641);

		template< typename type_t = float >
		constexpr type_t ClayDryExcavated = static_cast< type_t >(1089);

		template< typename type_t = float >
		constexpr type_t ClayWetExcavated = static_cast< type_t >(1826);

		template< typename type_t = float >
		constexpr type_t ClayDryLump = static_cast< type_t >(1073);

		template< typename type_t = float >
		constexpr type_t ClayFire = static_cast< type_t >(1362);

		template< typename type_t = float >
		constexpr type_t ClayWetLump = static_cast< type_t >(1602);

		template< typename type_t = float >
		constexpr type_t ClayCompacted = static_cast< type_t >(1746);

		template< typename type_t = float >
		constexpr type_t CloverSeed = static_cast< type_t >(769);

		template< typename type_t = float >
		constexpr type_t CoalAnthraciteSolid = static_cast< type_t >(1506);

		template< typename type_t = float >
		constexpr type_t CoalAnthraciteBroken = static_cast< type_t >(1105);

		template< typename type_t = float >
		constexpr type_t CoalBituminousSolid = static_cast< type_t >(1346);

		template< typename type_t = float >
		constexpr type_t CoalBituminousBroken = static_cast< type_t >(833);

		template< typename type_t = float >
		constexpr type_t Cobaltite = static_cast< type_t >(6295);

		template< typename type_t = float >
		constexpr type_t CoconutMeal = static_cast< type_t >(513);

		template< typename type_t = float >
		constexpr type_t CoconutShredded = static_cast< type_t >(352);

		template< typename type_t = float >
		constexpr type_t CoffeeFreshBeans = static_cast< type_t >(561);

		template< typename type_t = float >
		constexpr type_t CoffeeRoastBeans = static_cast< type_t >(432);

		template< typename type_t = float >
		constexpr type_t Coke = static_cast< type_t >(610);

		template< typename type_t = float >
		constexpr type_t ConcreteAsphalt = static_cast< type_t >(2243);

		template< typename type_t = float >
		constexpr type_t ConcreteGravel = static_cast< type_t >(2403);

		template< typename type_t = float >
		constexpr type_t ConcreteLimestoneWithPortland = static_cast< type_t >(2371);

		template< typename type_t = float >
		constexpr type_t CopperOre = static_cast< type_t >(2265);

		template< typename type_t = float >
		constexpr type_t CopperSulfateGround = static_cast< type_t >(3604);

		template< typename type_t = float >
		constexpr type_t CopraMediumSize = static_cast< type_t >(529);

		template< typename type_t = float >
		constexpr type_t CopraMealGround = static_cast< type_t >(641);

		template< typename type_t = float >
		constexpr type_t CopraExpellerCakeGround = static_cast< type_t >(513);

		template< typename type_t = float >
		constexpr type_t CopraExpellerCakeChopped = static_cast< type_t >(465);

		template< typename type_t = float >
		constexpr type_t CorkSolid = static_cast< type_t >(240);

		template< typename type_t = float >
		constexpr type_t CorkGround = static_cast< type_t >(160);

		template< typename type_t = float >
		constexpr type_t CornOnTheCob = static_cast< type_t >(721);

		template< typename type_t = float >
		constexpr type_t CornShelled = static_cast< type_t >(721);

		template< typename type_t = float >
		constexpr type_t CornGrits = static_cast< type_t >(673);

		template< typename type_t = float >
		constexpr type_t CottonseedDryDeLinted = static_cast< type_t >(561);

		template< typename type_t = float >
		constexpr type_t CottonseedDryNotDeLinted = static_cast< type_t >(320);

		template< typename type_t = float >
		constexpr type_t CottonseedCakeLumpy = static_cast< type_t >(673);

		template< typename type_t = float >
		constexpr type_t CottonseedHulls = static_cast< type_t >(192);

		template< typename type_t = float >
		constexpr type_t CottonseedMeal = static_cast< type_t >(593);

		template< typename type_t = float >
		constexpr type_t CottonseedMeats = static_cast< type_t >(641);

		template< typename type_t = float >
		constexpr type_t Cottonwood = static_cast< type_t >(416);

		template< typename type_t = float >
		constexpr type_t Cryolite = static_cast< type_t >(1602);

		template< typename type_t = float >
		constexpr type_t Cullet = static_cast< type_t >(1602);

		template< typename type_t = float >
		constexpr type_t Culm = static_cast< type_t >(753);

		template< typename type_t = float >
		constexpr type_t DolomiteSolid = static_cast< type_t >(2899);

		template< typename type_t = float >
		constexpr type_t DolomitePulverized = static_cast< type_t >(737);

		template< typename type_t = float >
		constexpr type_t DolomiteLumpy = static_cast< type_t >(1522);

		template< typename type_t = float >
		constexpr type_t EarthLoamDryExcavated = static_cast< type_t >(1249);

		template< typename type_t = float >
		constexpr type_t EarthMoistExcavated = static_cast< type_t >(1442);

		template< typename type_t = float >
		constexpr type_t EarthWetExcavated = static_cast< type_t >(1602);

		template< typename type_t = float >
		constexpr type_t EarthDense = static_cast< type_t >(2002);

		template< typename type_t = float >
		constexpr type_t EarthSoftLooseMud = static_cast< type_t >(1730);

		template< typename type_t = float >
		constexpr type_t EarthPacked = static_cast< type_t >(1522);

		template< typename type_t = float >
		constexpr type_t EarthFullersEaw = static_cast< type_t >(673);

		template< typename type_t = float >
		constexpr type_t Emery = static_cast< type_t >(4005);

		template< typename type_t = float >
		constexpr type_t Ether = static_cast< type_t >(737);

		template< typename type_t = float >
		constexpr type_t FeldsparSolid = static_cast< type_t >(2563);

		template< typename type_t = float >
		constexpr type_t FeldsparPulverized = static_cast< type_t >(1233);

		template< typename type_t = float >
		constexpr type_t FertilizerAcidPhosphate = static_cast< type_t >(961);

		template< typename type_t = float >
		constexpr type_t FishScrap = static_cast< type_t >(721);

		template< typename type_t = float >
		constexpr type_t FishMeal = static_cast< type_t >(593);

		template< typename type_t = float >
		constexpr type_t FlaxseedWhole = static_cast< type_t >(721);

		template< typename type_t = float >
		constexpr type_t FlintSilica = static_cast< type_t >(1390);

		template< typename type_t = float >
		constexpr type_t FlourWheat = static_cast< type_t >(593);

		template< typename type_t = float >
		constexpr type_t FlueDust = static_cast< type_t >(1735);

		template< typename type_t = float >
		constexpr type_t FluorsparSolid = static_cast< type_t >(3204);

		template< typename type_t = float >
		constexpr type_t FluorsparLumps = static_cast< type_t >(1602);

		template< typename type_t = float >
		constexpr type_t FluorsparPulverized = static_cast< type_t >(1442);

		template< typename type_t = float >
		constexpr type_t FullersEarthEawOrBurnt = static_cast< type_t >(650);

		template< typename type_t = float >
		constexpr type_t GalenaLeadOre = static_cast< type_t >(7500);

		template< typename type_t = float >
		constexpr type_t GarbageHouseholdRubbish = static_cast< type_t >(481);

		template< typename type_t = float >
		constexpr type_t GlassBroken = static_cast< type_t >(1615);

		template< typename type_t = float >
		constexpr type_t GlassWindow = static_cast< type_t >(2579);

		template< typename type_t = float >
		constexpr type_t GlueAnimalFlaked = static_cast< type_t >(561);

		template< typename type_t = float >
		constexpr type_t GlueVegetablePowdered = static_cast< type_t >(641);

		template< typename type_t = float >
		constexpr type_t GlutenMeal = static_cast< type_t >(625);

		template< typename type_t = float >
		constexpr type_t GneissBedInPlace = static_cast< type_t >(2867);

		template< typename type_t = float >
		constexpr type_t GneissBroken = static_cast< type_t >(1858);

		template< typename type_t = float >
		constexpr type_t GraniteSolid = static_cast< type_t >(2691);

		template< typename type_t = float >
		constexpr type_t GraniteBroken = static_cast< type_t >(1650);

		template< typename type_t = float >
		constexpr type_t GraphiteFlake = static_cast< type_t >(641);

		template< typename type_t = float >
		constexpr type_t GrainMaize = static_cast< type_t >(760);

		template< typename type_t = float >
		constexpr type_t GrainBarley = static_cast< type_t >(600);

		template< typename type_t = float >
		constexpr type_t GrainMillet = static_cast< type_t >(780);

		template< typename type_t = float >
		constexpr type_t GrainWheat = static_cast< type_t >(790);

		template< typename type_t = float >
		constexpr type_t GravelLooseDry = static_cast< type_t >(1522);

		template< typename type_t = float >
		constexpr type_t GravelWithNaturalSand = static_cast< type_t >(1922);

		template< typename type_t = float >
		constexpr type_t GummiteUraniumOre = static_cast< type_t >(5145);

		template< typename type_t = float >
		constexpr type_t GypsumSolid = static_cast< type_t >(2787);

		template< typename type_t = float >
		constexpr type_t GypsumBroken = static_cast< type_t >(1445);

		template< typename type_t = float >
		constexpr type_t GypsumCrushed = static_cast< type_t >(1602);

		template< typename type_t = float >
		constexpr type_t GypsumPulverized = static_cast< type_t >(1121);

		template< typename type_t = float >
		constexpr type_t HaliteSaltSolid = static_cast< type_t >(2323);

		template< typename type_t = float >
		constexpr type_t HaliteSaltBroken = static_cast< type_t >(1506);

		template< typename type_t = float >
		constexpr type_t HematiteIronOre = static_cast< type_t >(5150);

		template< typename type_t = float >
		constexpr type_t HemimorphiteZincOre = static_cast< type_t >(3442.5);

		template< typename type_t = float >
		constexpr type_t HydrochloricAcid40 = static_cast< type_t >(1201);

		template< typename type_t = float >
		constexpr type_t IceSolid = static_cast< type_t >(919);

		template< typename type_t = float >
		constexpr type_t IceCrushed = static_cast< type_t >(593);

		template< typename type_t = float >
		constexpr type_t Ilmenite = static_cast< type_t >(2307);

		template< typename type_t = float >
		constexpr type_t Iridium = static_cast< type_t >(22154);

		template< typename type_t = float >
		constexpr type_t IronOreCrushed = static_cast< type_t >(2500);

		template< typename type_t = float >
		constexpr type_t IronOxidePigment = static_cast< type_t >(400);

		template< typename type_t = float >
		constexpr type_t IronPyrites = static_cast< type_t >(2400);

		template< typename type_t = float >
		constexpr type_t IronSulphateDry = static_cast< type_t >(1200);

		template< typename type_t = float >
		constexpr type_t IronSulphateWet = static_cast< type_t >(1290);

		template< typename type_t = float >
		constexpr type_t Ivory = static_cast< type_t >(1842);

		template< typename type_t = float >
		constexpr type_t KaolinGreenCrushed = static_cast< type_t >(1025);

		template< typename type_t = float >
		constexpr type_t KaolinPulverized = static_cast< type_t >(352);

		template< typename type_t = float >
		constexpr type_t LeadRolled = static_cast< type_t >(11389);

		template< typename type_t = float >
		constexpr type_t LeadRed = static_cast< type_t >(3684);

		template< typename type_t = float >
		constexpr type_t LeadWhitePigment = static_cast< type_t >(4085);

		template< typename type_t = float >
		constexpr type_t Leather = static_cast< type_t >(945);

		template< typename type_t = float >
		constexpr type_t LigniteDry = static_cast< type_t >(801);

		template< typename type_t = float >
		constexpr type_t LimeQuickLump = static_cast< type_t >(849);

		template< typename type_t = float >
		constexpr type_t LimeQuickFine = static_cast< type_t >(1201);

		template< typename type_t = float >
		constexpr type_t LimeStoneLarge = static_cast< type_t >(2691);

		template< typename type_t = float >
		constexpr type_t LimeStoneLump = static_cast< type_t >(1538);

		template< typename type_t = float >
		constexpr type_t LimeHydrated = static_cast< type_t >(481);

		template< typename type_t = float >
		constexpr type_t LimeWetOrMortar = static_cast< type_t >(1540);

		template< typename type_t = float >
		constexpr type_t LimoniteSolid = static_cast< type_t >(3796);

		template< typename type_t = float >
		constexpr type_t LimoniteBroken = static_cast< type_t >(2467);

		template< typename type_t = float >
		constexpr type_t LimestoneSolid = static_cast< type_t >(2611);

		template< typename type_t = float >
		constexpr type_t LimestoneBroken = static_cast< type_t >(1554);

		template< typename type_t = float >
		constexpr type_t LimestonePulverized = static_cast< type_t >(1394);

		template< typename type_t = float >
		constexpr type_t LinseedWhole = static_cast< type_t >(753);

		template< typename type_t = float >
		constexpr type_t LinseedMeal = static_cast< type_t >(513);

		template< typename type_t = float >
		constexpr type_t LocustDry = static_cast< type_t >(705);

		template< typename type_t = float >
		constexpr type_t MagnesiteSolid = static_cast< type_t >(3011);

		template< typename type_t = float >
		constexpr type_t MagnesiumOxide = static_cast< type_t >(1940);

		template< typename type_t = float >
		constexpr type_t MagnesiumSulphateCrystal = static_cast< type_t >(1121);

		template< typename type_t = float >
		constexpr type_t MagnetiteSolidIronOre = static_cast< type_t >(5046);

		template< typename type_t = float >
		constexpr type_t MagnetiteBroken = static_cast< type_t >(3284);

		template< typename type_t = float >
		constexpr type_t MalachiteCopperOre = static_cast< type_t >(3855);

		template< typename type_t = float >
		constexpr type_t Malt = static_cast< type_t >(336);

		template< typename type_t = float >
		constexpr type_t ManganeseSolid = static_cast< type_t >(7609);

		template< typename type_t = float >
		constexpr type_t ManganeseOxide = static_cast< type_t >(1922);

		template< typename type_t = float >
		constexpr type_t Manure = static_cast< type_t >(400);

		template< typename type_t = float >
		constexpr type_t MarbleSolid = static_cast< type_t >(2563);

		template< typename type_t = float >
		constexpr type_t MarbleBroken = static_cast< type_t >(1570);

		template< typename type_t = float >
		constexpr type_t MarlWetExcavated = static_cast< type_t >(2243);

		template< typename type_t = float >
		constexpr type_t MicaSolid = static_cast< type_t >(2883);

		template< typename type_t = float >
		constexpr type_t MicaBroken = static_cast< type_t >(1602);

		template< typename type_t = float >
		constexpr type_t MicaFlake = static_cast< type_t >(520);

		template< typename type_t = float >
		constexpr type_t MicaPowder = static_cast< type_t >(986);

		template< typename type_t = float >
		constexpr type_t MilkPowdered = static_cast< type_t >(449);

		template< typename type_t = float >
		constexpr type_t MolybdenumOre = static_cast< type_t >(1600);

		template< typename type_t = float >
		constexpr type_t MortarWet = static_cast< type_t >(2403);

		template< typename type_t = float >
		constexpr type_t MudPacked = static_cast< type_t >(1906);

		template< typename type_t = float >
		constexpr type_t MudFluid = static_cast< type_t >(1730);

		template< typename type_t = float >
		constexpr type_t NickelOre = static_cast< type_t >(1600);

		template< typename type_t = float >
		constexpr type_t NickelRolled = static_cast< type_t >(8666);

		template< typename type_t = float >
		constexpr type_t NitricAcid91 = static_cast< type_t >(1506);

		template< typename type_t = float >
		constexpr type_t Nitrogen = static_cast< type_t >(1.26);

		template< typename type_t = float >
		constexpr type_t WoodOakRed = static_cast< type_t >(705);

		template< typename type_t = float >
		constexpr type_t Oats = static_cast< type_t >(432);

		template< typename type_t = float >
		constexpr type_t OatsRolled = static_cast< type_t >(304);

		template< typename type_t = float >
		constexpr type_t OilCake = static_cast< type_t >(785);

		template< typename type_t = float >
		constexpr type_t OilLinseed = static_cast< type_t >(942);

		template< typename type_t = float >
		constexpr type_t OilPetroleum = static_cast< type_t >(881);

		template< typename type_t = float >
		constexpr type_t Oxygen = static_cast< type_t >(1.43);

		template< typename type_t = float >
		constexpr type_t OysterShellsGround = static_cast< type_t >(849);

		template< typename type_t = float >
		constexpr type_t PaperStandard = static_cast< type_t >(1201);

		template< typename type_t = float >
		constexpr type_t PeanutsShelled = static_cast< type_t >(641);

		template< typename type_t = float >
		constexpr type_t PeanutsNotShelled = static_cast< type_t >(272);

		template< typename type_t = float >
		constexpr type_t PeatDry = static_cast< type_t >(400);

		template< typename type_t = float >
		constexpr type_t PeatMoist = static_cast< type_t >(801);

		template< typename type_t = float >
		constexpr type_t PeatWet = static_cast< type_t >(1121);

		template< typename type_t = float >
		constexpr type_t PecanWood = static_cast< type_t >(753);

		template< typename type_t = float >
		constexpr type_t PhosphateRockBroken = static_cast< type_t >(1762);

		template< typename type_t = float >
		constexpr type_t Phosphorus = static_cast< type_t >(2339);

		template< typename type_t = float >
		constexpr type_t Pitch = static_cast< type_t >(1153);

		template< typename type_t = float >
		constexpr type_t Plaster = static_cast< type_t >(849);

		template< typename type_t = float >
		constexpr type_t PlatinumOre = static_cast< type_t >(2600);

		template< typename type_t = float >
		constexpr type_t Porcelain = static_cast< type_t >(2403);

		template< typename type_t = float >
		constexpr type_t PorphyrySolid = static_cast< type_t >(2547);

		template< typename type_t = float >
		constexpr type_t PorphyryBroken = static_cast< type_t >(1650);

		template< typename type_t = float >
		constexpr type_t Potash = static_cast< type_t >(1281);

		template< typename type_t = float >
		constexpr type_t PotassiumChloride = static_cast< type_t >(2002);

		template< typename type_t = float >
		constexpr type_t PotatoesWhite = static_cast< type_t >(769);

		template< typename type_t = float >
		constexpr type_t PumiceStone = static_cast< type_t >(641);

		template< typename type_t = float >
		constexpr type_t Pyrite = static_cast< type_t >(3707.5);

		template< typename type_t = float >
		constexpr type_t QuartzSolid = static_cast< type_t >(2643);

		template< typename type_t = float >
		constexpr type_t QuartzLump = static_cast< type_t >(1554);

		template< typename type_t = float >
		constexpr type_t QuartzSand = static_cast< type_t >(1201);

		template< typename type_t = float >
		constexpr type_t ResinSyntheticCrushed = static_cast< type_t >(561);

		template< typename type_t = float >
		constexpr type_t RiceHulled = static_cast< type_t >(753);

		template< typename type_t = float >
		constexpr type_t RiceRough = static_cast< type_t >(577);

		template< typename type_t = float >
		constexpr type_t RiceGrits = static_cast< type_t >(689);

		template< typename type_t = float >
		constexpr type_t RipRap = static_cast< type_t >(1602);

		template< typename type_t = float >
		constexpr type_t RockSoft = static_cast< type_t >(1690);

		template< typename type_t = float >
		constexpr type_t Rosin = static_cast< type_t >(1073);

		template< typename type_t = float >
		constexpr type_t RubberCaoutchouc = static_cast< type_t >(945);

		template< typename type_t = float >
		constexpr type_t RubberManufactured = static_cast< type_t >(1522);

		template< typename type_t = float >
		constexpr type_t RubberGroundScrap = static_cast< type_t >(481);

		template< typename type_t = float >
		constexpr type_t Rye = static_cast< type_t >(705);

		template< typename type_t = float >
		constexpr type_t SaltCake = static_cast< type_t >(1442);

		template< typename type_t = float >
		constexpr type_t SaltCourse = static_cast< type_t >(801);

		template< typename type_t = float >
		constexpr type_t SaltFine = static_cast< type_t >(1201);

		template< typename type_t = float >
		constexpr type_t Saltpeter = static_cast< type_t >(1201);

		template< typename type_t = float >
		constexpr type_t SandWet = static_cast< type_t >(1922);

		template< typename type_t = float >
		constexpr type_t SandWetPacked = static_cast< type_t >(2082);

		template< typename type_t = float >
		constexpr type_t SandDry = static_cast< type_t >(1602);

		template< typename type_t = float >
		constexpr type_t SandLoose = static_cast< type_t >(1442);

		template< typename type_t = float >
		constexpr type_t SandRammed = static_cast< type_t >(1682);

		template< typename type_t = float >
		constexpr type_t SandWaterFilled = static_cast< type_t >(1922);

		template< typename type_t = float >
		constexpr type_t SandWithGravelDry = static_cast< type_t >(1650);

		template< typename type_t = float >
		constexpr type_t SandWithGravelWet = static_cast< type_t >(2020);

		template< typename type_t = float >
		constexpr type_t SandstoneSolid = static_cast< type_t >(2323);

		template< typename type_t = float >
		constexpr type_t SandstoneBroken = static_cast< type_t >(1410);

		template< typename type_t = float >
		constexpr type_t Sawdust = static_cast< type_t >(210);

		template< typename type_t = float >
		constexpr type_t SewageSludge = static_cast< type_t >(721);

		template< typename type_t = float >
		constexpr type_t ShaleSolid = static_cast< type_t >(2675);

		template< typename type_t = float >
		constexpr type_t ShaleBroken = static_cast< type_t >(1586);

		template< typename type_t = float >
		constexpr type_t ShellsOyster = static_cast< type_t >(800);

		template< typename type_t = float >
		constexpr type_t Sinter = static_cast< type_t >(1890);

		template< typename type_t = float >
		constexpr type_t SlagSolid = static_cast< type_t >(2114);

		template< typename type_t = float >
		constexpr type_t SlagBroken = static_cast< type_t >(1762);

		template< typename type_t = float >
		constexpr type_t SlagCrushed = static_cast< type_t >(1185);

		template< typename type_t = float >
		constexpr type_t SlagFurnGranulated = static_cast< type_t >(961);

		template< typename type_t = float >
		constexpr type_t SlateSolid = static_cast< type_t >(2691);

		template< typename type_t = float >
		constexpr type_t SlateBroken = static_cast< type_t >(1370);

		template< typename type_t = float >
		constexpr type_t SlatePulverized = static_cast< type_t >(1362);

		template< typename type_t = float >
		constexpr type_t SmithsoniteZincOre = static_cast< type_t >(4300);

		template< typename type_t = float >
		constexpr type_t SnowFreshlyFallen = static_cast< type_t >(160);

		template< typename type_t = float >
		constexpr type_t SnowCompacted = static_cast< type_t >(481);

		template< typename type_t = float >
		constexpr type_t SoapSolid = static_cast< type_t >(801);

		template< typename type_t = float >
		constexpr type_t SoapChips = static_cast< type_t >(160);

		template< typename type_t = float >
		constexpr type_t SoapFlakes = static_cast< type_t >(160);

		template< typename type_t = float >
		constexpr type_t SoapPowdered = static_cast< type_t >(368);

		template< typename type_t = float >
		constexpr type_t SoapstoneTalc = static_cast< type_t >(2400);

		template< typename type_t = float >
		constexpr type_t SodaAshHeavy = static_cast< type_t >(1080);

		template< typename type_t = float >
		constexpr type_t SodaAshLight = static_cast< type_t >(432);

		template< typename type_t = float >
		constexpr type_t Sodium = static_cast< type_t >(977);

		template< typename type_t = float >
		constexpr type_t SodiumAluminateGround = static_cast< type_t >(1153);

		template< typename type_t = float >
		constexpr type_t SodiumNitrateGround = static_cast< type_t >(1201);

		template< typename type_t = float >
		constexpr type_t SoyBeansWhole = static_cast< type_t >(753);

		template< typename type_t = float >
		constexpr type_t StarchPowdered = static_cast< type_t >(561);

		template< typename type_t = float >
		constexpr type_t StoneCrushed = static_cast< type_t >(1602);

		template< typename type_t = float >
		constexpr type_t StoneCommonGeneric = static_cast< type_t >(2515);

		template< typename type_t = float >
		constexpr type_t SugarBrown = static_cast< type_t >(721);

		template< typename type_t = float >
		constexpr type_t SugarPowdered = static_cast< type_t >(801);

		template< typename type_t = float >
		constexpr type_t SugarGranulated = static_cast< type_t >(849);

		template< typename type_t = float >
		constexpr type_t SugarRawCane = static_cast< type_t >(961);

		template< typename type_t = float >
		constexpr type_t SugarbeetPulpDry = static_cast< type_t >(208);

		template< typename type_t = float >
		constexpr type_t SugarbeetPulpWet = static_cast< type_t >(561);

		template< typename type_t = float >
		constexpr type_t Sugarcane = static_cast< type_t >(272);

		template< typename type_t = float >
		constexpr type_t SulphurSolid = static_cast< type_t >(2002);

		template< typename type_t = float >
		constexpr type_t SulphurLump = static_cast< type_t >(1314);

		template< typename type_t = float >
		constexpr type_t SulphurPulverized = static_cast< type_t >(961);

		template< typename type_t = float >
		constexpr type_t Taconite = static_cast< type_t >(2803);

		template< typename type_t = float >
		constexpr type_t TalcSolid = static_cast< type_t >(2691);

		template< typename type_t = float >
		constexpr type_t TalcBroken = static_cast< type_t >(1746);

		template< typename type_t = float >
		constexpr type_t TanbarkGround = static_cast< type_t >(881);

		template< typename type_t = float >
		constexpr type_t Tankage = static_cast< type_t >(961);

		template< typename type_t = float >
		constexpr type_t Tar = static_cast< type_t >(1153);

		template< typename type_t = float >
		constexpr type_t Tobacco = static_cast< type_t >(320);

		template< typename type_t = float >
		constexpr type_t TrapRockSolid = static_cast< type_t >(2883);

		template< typename type_t = float >
		constexpr type_t TrapRockBroken = static_cast< type_t >(1746);

		template< typename type_t = float >
		constexpr type_t Turf = static_cast< type_t >(400);

		template< typename type_t = float >
		constexpr type_t Turpentine = static_cast< type_t >(865);

		template< typename type_t = float >
		constexpr type_t WalnutBlackDry = static_cast< type_t >(609);

		template< typename type_t = float >
		constexpr type_t WaterPure = static_cast< type_t >(1000);

		template< typename type_t = float >
		constexpr type_t WaterSea = static_cast< type_t >(1026);

		template< typename type_t = float >
		constexpr type_t Wheat = static_cast< type_t >(769);

		template< typename type_t = float >
		constexpr type_t WheatCracked = static_cast< type_t >(673);

		template< typename type_t = float >
		constexpr type_t Wool = static_cast< type_t >(1314);

		template< typename type_t = float >
		constexpr type_t ZincOxide = static_cast< type_t >(400);

		template< typename type_t = float >
		constexpr type_t AluminiumMelted = static_cast< type_t >(2600);

		template< typename type_t = float >
		constexpr type_t AluminiumBronze = static_cast< type_t >(8200);

		template< typename type_t = float >
		constexpr type_t AluminiumFoil = static_cast< type_t >(2725);

		template< typename type_t = float >
		constexpr type_t AntifrictionMetal = static_cast< type_t >(9865);

		template< typename type_t = float >
		constexpr type_t Beryllium = static_cast< type_t >(1840);

		template< typename type_t = float >
		constexpr type_t BerylliumCopper = static_cast< type_t >(8175);

		template< typename type_t = float >
		constexpr type_t BrassCasting = static_cast< type_t >(8550);

		template< typename type_t = float >
		constexpr type_t BrassRolledAndDrawn = static_cast< type_t >(8580);

		template< typename type_t = float >
		constexpr type_t BronzeLead = static_cast< type_t >(8200);

		template< typename type_t = float >
		constexpr type_t BronzePhosphorous = static_cast< type_t >(8850);

		template< typename type_t = float >
		constexpr type_t BronzeTin = static_cast< type_t >(8150);

		template< typename type_t = float >
		constexpr type_t CastIron = static_cast< type_t >(7300);

		template< typename type_t = float >
		constexpr type_t Cobolt = static_cast< type_t >(8746);

		template< typename type_t = float >
		constexpr type_t Copper = static_cast< type_t >(8930);

		template< typename type_t = float >
		constexpr type_t DeltaMetal = static_cast< type_t >(8600);

		template< typename type_t = float >
		constexpr type_t Electrum = static_cast< type_t >(8650);

		template< typename type_t = float >
		constexpr type_t Gold = static_cast< type_t >(19320);

		template< typename type_t = float >
		constexpr type_t Iron = static_cast< type_t >(7850);

		template< typename type_t = float >
		constexpr type_t Lead = static_cast< type_t >(11340);

		template< typename type_t = float >
		constexpr type_t Magnesium = static_cast< type_t >(1738);

		template< typename type_t = float >
		constexpr type_t Mercury = static_cast< type_t >(13593);

		template< typename type_t = float >
		constexpr type_t Molybdenum = static_cast< type_t >(10188);

		template< typename type_t = float >
		constexpr type_t Monel = static_cast< type_t >(8600);

		template< typename type_t = float >
		constexpr type_t Nickel = static_cast< type_t >(8800);

		template< typename type_t = float >
		constexpr type_t NickelSilver = static_cast< type_t >(8442);

		template< typename type_t = float >
		constexpr type_t Platinum = static_cast< type_t >(21400);

		template< typename type_t = float >
		constexpr type_t Plutonium = static_cast< type_t >(19800);

		template< typename type_t = float >
		constexpr type_t Silver = static_cast< type_t >(10490);

		template< typename type_t = float >
		constexpr type_t SteelRolled = static_cast< type_t >(7850);

		template< typename type_t = float >
		constexpr type_t SteelStainless = static_cast< type_t >(7740);

		template< typename type_t = float >
		constexpr type_t Tin = static_cast< type_t >(7280);

		template< typename type_t = float >
		constexpr type_t Titanium = static_cast< type_t >(4500);

		template< typename type_t = float >
		constexpr type_t Tungsten = static_cast< type_t >(19600);

		template< typename type_t = float >
		constexpr type_t Uranium = static_cast< type_t >(18900);

		template< typename type_t = float >
		constexpr type_t Vanadium = static_cast< type_t >(5494);

		template< typename type_t = float >
		constexpr type_t WhiteMetal = static_cast< type_t >(7100);

		template< typename type_t = float >
		constexpr type_t Zinc = static_cast< type_t >(7135);

		template< typename type_t = float >
		constexpr type_t WoodChipsDry = static_cast< type_t >(380);

		template< typename type_t = float >
		constexpr type_t WoodAfromosia = static_cast< type_t >(705);

		template< typename type_t = float >
		constexpr type_t WoodApple = static_cast< type_t >(745);

		template< typename type_t = float >
		constexpr type_t WoodAshBlack = static_cast< type_t >(540);

		template< typename type_t = float >
		constexpr type_t WoodAshWhite = static_cast< type_t >(670);

		template< typename type_t = float >
		constexpr type_t WoodAspen = static_cast< type_t >(420);

		template< typename type_t = float >
		constexpr type_t WoodBalsa = static_cast< type_t >(170);

		template< typename type_t = float >
		constexpr type_t WoodBamboo = static_cast< type_t >(350);

		template< typename type_t = float >
		constexpr type_t WoodBirch = static_cast< type_t >(670);

		template< typename type_t = float >
		constexpr type_t WoodCedarRed = static_cast< type_t >(380);

		template< typename type_t = float >
		constexpr type_t WoodCypress = static_cast< type_t >(510);

		template< typename type_t = float >
		constexpr type_t WoodDouglasFir = static_cast< type_t >(530);

		template< typename type_t = float >
		constexpr type_t WoodEbony = static_cast< type_t >(1040);

		template< typename type_t = float >
		constexpr type_t WoodElm = static_cast< type_t >(707.5);

		template< typename type_t = float >
		constexpr type_t WoodIroko = static_cast< type_t >(655);

		template< typename type_t = float >
		constexpr type_t WoodLarch = static_cast< type_t >(590);

		template< typename type_t = float >
		constexpr type_t WoodLignumVitae = static_cast< type_t >(1325);

		template< typename type_t = float >
		constexpr type_t WoodMahogany = static_cast< type_t >(697.5);

		template< typename type_t = float >
		constexpr type_t WoodMaple = static_cast< type_t >(755);

		template< typename type_t = float >
		constexpr type_t WoodOak = static_cast< type_t >(760);

		template< typename type_t = float >
		constexpr type_t WoodPine = static_cast< type_t >(505);

		template< typename type_t = float >
		constexpr type_t WoodRedwood = static_cast< type_t >(480);

		template< typename type_t = float >
		constexpr type_t WoodSpruce = static_cast< type_t >(450);

		template< typename type_t = float >
		constexpr type_t WoodSycamore = static_cast< type_t >(590);

		template< typename type_t = float >
		constexpr type_t WoodTeak = static_cast< type_t >(675);

		template< typename type_t = float >
		constexpr type_t WoodWillow = static_cast< type_t >(420);
	}

	namespace Radius
	{
		/** @brief Earth radius expressed in meters. */
		template< typename type_t = float >
		constexpr type_t Earth = SI::Meter< type_t > * static_cast< type_t >(6371 * 1000);

		/** @brief Moon radius expressed in meters. */
		template< typename type_t = float >
		constexpr type_t Moon = SI::Meter< type_t > * static_cast< type_t >(1737.4 * 1000);

		/** @brief Mars radius expressed in meters. */
		template< typename type_t = float >
		constexpr type_t Mars = SI::Meter< type_t > * static_cast< type_t >(3389.5 * 1000);

		/** @brief Jupiter radius expressed in meters. */
		template< typename type_t = float >
		constexpr type_t Jupiter = SI::Meter< type_t > * static_cast< type_t >(69911 * 1000);
	}

	/** @brief Standard air pressure expressed in Pa at sea level. */
	template< typename type_t = float >
	constexpr type_t AirPressure = static_cast< type_t >(101325);

	/** @brief Absolute zero in celsius temperature. */
	template< typename type_t = float >
	constexpr type_t AbsoluteZero = static_cast< type_t >(-273.15);

	/** @brief Inertia threshold to stop infinite movement in simulation. */
	template< typename type_t = float >
	constexpr type_t InertiaThreshold = static_cast< type_t >(-10.0);

	/**
	 * @brief Geo-potential ...
	 * @param altitude The altitude in meters.
	 * @return type_t
	 */
	template< typename type_t = float >
	type_t
	getGeoPotential (type_t altitude) noexcept
	{
		return Radius::Earth< type_t > * altitude / (Radius::Earth< type_t > + altitude);
	}

	/**
	 * @brief Returns standard atmospheric temperature.
	 * @note Temperature is in kelvins = 273.15 + Celsius
	 * @param geoPotentailHeight The value returned by getGeoPotential().
	 * @return type_t, Air temperature in K°.
	 */
	template< typename type_t = float >
	type_t
	getStandardTemperature (type_t geoPotentailHeight) noexcept
	{
		/* Troposphere */
		if ( geoPotentailHeight <= static_cast< type_t >(11.0) )
			return static_cast< type_t >(288.15) - (static_cast< type_t >(6.5) * geoPotentailHeight);

		/* Stratosphere starts */
		if ( geoPotentailHeight <= static_cast< type_t >(20.0) )
			return static_cast< type_t >(216.65);

		if ( geoPotentailHeight <= static_cast< type_t >(32.0) )
			return static_cast< type_t >(196.65) + geoPotentailHeight;

		if ( geoPotentailHeight <= static_cast< type_t >(47.0) )
			return static_cast< type_t >(228.65) + static_cast< type_t >(2.8) * (geoPotentailHeight - static_cast< type_t >(32.0));

		/* Mesosphere starts */
		if ( geoPotentailHeight <= static_cast< type_t >(51.0) )
			return static_cast< type_t >(270.65);

		if ( geoPotentailHeight <= static_cast< type_t >(71.0) )
			return static_cast< type_t >(270.65) - static_cast< type_t >(2.8) * (geoPotentailHeight - static_cast< type_t >(51.0));

		if ( geoPotentailHeight <= static_cast< type_t >(84.85) )
			return static_cast< type_t >(214.65) - static_cast< type_t >(2.0) * (geoPotentailHeight - static_cast< type_t >(71.0));

		/* Thermosphere has high kinetic temperature (500 C to 2000 C) but temperature
		 * as measured by a thermometer would be very low because of almost vacuum. */

		std::cerr << __PRETTY_FUNCTION__ << ", geopot_height must be less than 84.85 km." << std::endl;

		return 0;
	}

	/**
	 * @brief Returns standard atmospheric pressure on earth.
	 * @param altitude The altitude in meters.
	 * @return type_t, Air pressure in Pa (Pascals).
	 */
	template< typename type_t = float >
	type_t
	getStandardPressure (type_t altitude) noexcept
	{
		auto geoPotentialHeight = Physics::getGeoPotential< type_t >(altitude);

		auto t = Physics::getStandardTemperature< type_t >(geoPotentialHeight);

		if ( geoPotentialHeight <= static_cast< type_t >(11.0) )
			return static_cast< type_t >(101325.0) * std::pow(static_cast< type_t >(288.15) / t, static_cast< type_t >(-5.255877));

		if ( geoPotentialHeight <= static_cast< type_t >(20.0) )
			return static_cast< type_t >(22632.06) * std::exp(static_cast< type_t >(-0.1577) * (geoPotentialHeight - static_cast< type_t >(11.0)));

		if ( geoPotentialHeight <= static_cast< type_t >(32.0) )
			return static_cast< type_t >(5474.889) * std::pow(static_cast< type_t >(216.65) / t, static_cast< type_t >(34.16319));

		if ( geoPotentialHeight <= static_cast< type_t >(47.0) )
			return static_cast< type_t >(868.0187) * std::pow(static_cast< type_t >(228.65) / t, static_cast< type_t >(12.2011));

		if ( geoPotentialHeight <= static_cast< type_t >(51.0) )
			return static_cast< type_t >(110.9063) * std::exp(static_cast< type_t >(-0.1262) * (geoPotentialHeight - static_cast< type_t >(47.0)));

		if ( geoPotentialHeight <= static_cast< type_t >(71.0) )
			return static_cast< type_t >(66.93887) * std::pow(static_cast< type_t >(270.65) / t, static_cast< type_t >(-12.2011));

		if ( geoPotentialHeight <= static_cast< type_t >(84.85) )
			return static_cast< type_t >(3.956420) * std::pow(static_cast< type_t >(214.65) / t, static_cast< type_t >(-17.0816));

		std::cerr << __PRETTY_FUNCTION__ << ", altitude must be less than 86 km." << std::endl;

		return 0;
	}

	/**
	 * @brief Returns air density based on earth environment in kg/m³.
	 * @note Below 51 km: Practical Meteorology by Roland Stull, pg 12.
	 * Above 51 km: http://www.braeunig.us/space/atmmodel.htm.
	 * Validation data: https://www.avs.org/AVS/files/c7/c7edaedb-95b2-438f-adfb-36de54f87b9e.pdf
	 * @param altitude The altitude in meters.
	 * @param temperature The ambient temperature in degree C°.
	 * @return float
	 */
	template< typename type_t = float >
	type_t
	getAirDensity (type_t altitude = 0, type_t temperature = 20) noexcept
	{
		/* http://barani.biz/apps/air-density/ */
		/* density = 101325 / (287.05 * (15 + 273.15)) = 1.225 kg/m3 */
		const auto k = std::abs(AbsoluteZero< type_t >) + temperature;

		return Physics::getStandardPressure< type_t >(altitude) / (static_cast< type_t >(287.05) * k);
	}

	/**
	 * @brief Returns a force vector from a mass and an acceleration.
	 * @note 1. Every object persists in its state of rest or uniform motion
	 * in a straight line unless it is compelled to change that state
	 * by forces impressed on it.
	 * 2. Force is equal to the change in momentum (mV) per change
	 * in time. For a constant mass, force equals mass times acceleration.
	 * "F = m * a".
	 * 3. For every action, there is an equal and opposite re-action.
	 * @param mass The mass of the object in Kg.
	 * @param acceleration A vector 3 that define the direction of the acceleration.
	 * @return type_t
	 */
	template< typename type_t = float >
	type_t
	force (type_t mass, const Libraries::Math::Vector< 3, type_t > & acceleration) noexcept
	{
		/* F = m * a */
		return mass * acceleration;
	}

	/**
	 * @brief Computes terminal velocity of a moving object in a fluid or air.
	 * @param mass The mass of the object in Kg.
	 * @param surface The object surface in m².
	 * @param dragCoefficient The drag coefficient of the object. Use constants.
	 * @param gravity The gravity acceleration of the object in m/s².
	 * @param density The density of the environment where the object is moving in kg/m³.
	 * @return type_t, Terminal velocity in m/s.
	 */
	template< typename type_t = float >
	type_t
	computeTerminalVelocity (type_t mass, type_t surface, type_t dragCoefficient, type_t gravity, type_t density) noexcept
	{
		return std::sqrt((static_cast< type_t >(2.0) * mass * gravity) / (density * surface * dragCoefficient));
	}

	/**
	 * @brief Returns the drag magnitude.
	 * @param dragCoefficient
	 * @param density
	 * @param velocity
	 * @param surface
	 * @return
	 */
	template< typename type_t = float >
	type_t
	getDragMagnitude (type_t dragCoefficient, type_t density, type_t velocity, type_t surface) noexcept
	{
		/* Formula : "D = Cd * .5 * rho * V^2 * A" */
		/* Formula : Drag = [Drag coefficient] * 0.5 * [density "kg/m³"] * [Velocity "m/s²"]² * [Area "m²"] */
		return dragCoefficient * static_cast< type_t >(0.5) * density * (velocity * velocity) * surface;
	}

	/**
	 * @brief Returns the drag force vector.
	 * @param velocity
	 * @param dragMagnitude
	 * @return
	 */
	template< class vector_t, typename type_t >
	vector_t
	getDragForce (const vector_t & velocity, type_t dragMagnitude) noexcept
	{
		/* The drag vector is the inverse of the velocity scaled by the drag magnitude. */
		return (-velocity).rescale(dragMagnitude);
	}

	/**
	 * @brief getDragForce
	 * @param velocity
	 * @param surface
	 * @param dragCoefficient
	 * @param density
	 * @return
	 */
	template< class vector_t >
	vector_t
	getDragForce (const vector_t & velocity, float surface, float dragCoefficient, float density) noexcept
	{
		auto speed = velocity.getLength();

		/* If there is no velocity, there is no drag. */
		if ( speed <= 0 )
			return 0;

		/* The drag vector is the inverse of the velocity scaled by the drag magnitude. */
		return velocity.normalizedCopy().scale(-Physics::getDragMagnitude(dragCoefficient, density, speed, surface));
	}

	// NOLINTEND(*-magic-numbers)
}
