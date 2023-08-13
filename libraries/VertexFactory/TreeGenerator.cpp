/*
 * Libraries/VertexFactory/TreeGenerator.cpp
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

#include "TreeGenerator.hpp"

/* Local inclusions */
#include "ShapeGenerator.hpp"

namespace Libraries::VertexFactory
{
	using namespace Math;

	float
	TreeGenerator::baseSize () const noexcept
	{
		return m_baseSize;
	}

	void
	TreeGenerator::setBaseSize (float baseSize) noexcept
	{
		m_baseSize = baseSize;
	}

	float
	TreeGenerator::baseHeight () const noexcept
	{
		return m_baseHeight;
	}

	void
	TreeGenerator::setBaseHeight (float baseHeight) noexcept
	{
		m_baseHeight = baseHeight;
	}

	float
	TreeGenerator::reduceFactor () const noexcept
	{
		return m_reduceFactor;
	}

	void
	TreeGenerator::setReduceFactor (float reduceFactor) noexcept
	{
		m_reduceFactor = Math::clampToUnit(reduceFactor);
	}

	float
	TreeGenerator::maxSpreadingAngle () const noexcept
	{
		return m_maxSpreadingAngle;
	}

	void
	TreeGenerator::setMaxSpreadingAngle (float maxSpreadingAngle) noexcept
	{
		m_maxSpreadingAngle = maxSpreadingAngle;
	}

	float
	TreeGenerator::chaos () const noexcept
	{
		return m_chaos;
	}

	void
	TreeGenerator::setChaos (float chaos) noexcept
	{
		m_chaos = chaos;
	}

	size_t
	TreeGenerator::depth () const noexcept
	{
		return m_depth;
	}

	void
	TreeGenerator::setDepth (size_t depth) noexcept
	{
		m_depth = depth;
	}

	void
	TreeGenerator::generateBranch (ShapeAssembler< float > & assembler, float size, float height, const Coordinates< float > & origin, size_t currentDepth, bool generateSubBranches) noexcept
	{
		std::cout << "Level #" << currentDepth << " generation." "\n";

		/*Shape branch{};
		ShapeAssembler branchAssembler{branch};

		Coordinates< float > chunkCoords{};

		for ( auto thisDepth = currentDepth; thisDepth < m_depth; thisDepth++ )
		{
			chunkCoords.clearRotation();

			if ( generateSubBranches && thisDepth > currentDepth )
			{
				//for ( auto branchDepth = depth - 1; branchDepth < m_depth; branchDepth++ )
				{
					std::cout << "Level #" << currentDepth << " sub-generation." "\n";

					auto branchOrigin = chunkCoords;
					branchOrigin.yaw(Math::Radian(Utility::random(0.0F, 360.0F)));
					branchOrigin.pitch(Math::Radian(m_maxSpreadingAngle * 2.0F));

					this->generateBranch(assembler, size * 0.5F, height * 0.75F, branchOrigin, thisDepth, true);
				}
			}

			chunkCoords.roll(Math::Radian(Utility::random(-m_maxSpreadingAngle, m_maxSpreadingAngle)));
			chunkCoords.pitch(Math::Radian(Utility::random(-m_maxSpreadingAngle, m_maxSpreadingAngle)));

			const auto nextSize = size * m_reduceFactor;

			auto chunk = ShapeGenerator::generateCylinder(size, nextSize, height, 8, 4);

			branchAssembler.merge(chunk, chunkCoords, false);

			chunkCoords.translateAlongLocalYAxis(height);
			size = nextSize;
			height *= m_reduceFactor;
		}

		{
			auto branchOrigin = ShapeGenerator::generateSphere(size * 5.0F, 8, 8);

			assembler.merge(branchOrigin, origin);
		}

		if ( branch.empty() )
			return;

		assembler.merge(branch, origin);*/

		std::cout << "Level #" << currentDepth << " assembled to the parent." "\n";
	}

	Shape< float >
	TreeGenerator::generate (size_t seed) noexcept
	{
		Shape< float > treeShape{};

		ShapeAssembler treeAssembler{treeShape};

		std::srand(seed);

		this->generateBranch(treeAssembler, m_baseSize, m_baseHeight, {}, 0U, true);

		return treeShape;
	}
}
