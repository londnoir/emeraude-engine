/*
 * Emeraude/Graphics/Frustum.cpp
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

#include "Frustum.hpp"

namespace Emeraude::Graphics
{
	using namespace Libraries;
	using namespace Libraries::Math;

	bool Frustum::s_enableFrustumTest = true;

	void
	Frustum::setTestState (bool state) noexcept
	{
		s_enableFrustumTest = state;
	}

	bool
	Frustum::isTestEnabled () noexcept
	{
		return s_enableFrustumTest;
	}

	bool
	Frustum::toggleTestState () noexcept
	{
		return s_enableFrustumTest = !s_enableFrustumTest;
	}

	void
	Frustum::updateProperties (float farDistance) noexcept
	{
		/* FIXME: Empty function */
	}

	void
	Frustum::update (const Matrix< 4, float > & viewProjectionMatrix) noexcept
	{
		const auto rowA = viewProjectionMatrix.row(0);
		const auto rowB = viewProjectionMatrix.row(1);
		const auto rowC = viewProjectionMatrix.row(2);
		const auto rowD = viewProjectionMatrix.row(3);

		m_planes[Right].setData((rowD - rowA).normalize());
		m_planes[Left].setData((rowD + rowA).normalize());
		m_planes[Bottom].setData((rowD + rowB).normalize());
		m_planes[Top].setData((rowD - rowB).normalize());
		m_planes[Far].setData((rowD - rowC).normalize());
		m_planes[Near].setData((rowD + rowC).normalize());
	}

	Frustum::Result
	Frustum::isCollidingWith (const Vector< 3, float > & point) const noexcept
	{
		if ( !s_enableFrustumTest )
			return Result::Inside;

		for ( const auto & plane : m_planes )
		{
			const auto & data = plane.data();

			/* Dot product */
			const auto x = data[X] * point[X];
			const auto y = data[Y] * point[Y];
			const auto z = data[Z] * point[Z];

			if ( x + y + z + data[W] <= 0.0F )
				return Result::Outside;
		}

		return Result::Inside;
	}

	Frustum::Result
	Frustum::isCollidingWith (const Sphere< float > & sphere) const noexcept
	{
		if ( !s_enableFrustumTest )
			return Result::Inside;

		const auto & position = sphere.position();

		const auto radius = sphere.radius();

		for ( auto & plane : m_planes )
		{
			const auto & data = plane.data();

			/* Dot product */
			const auto x = data[X] * position[X];
			const auto y = data[Y] * position[Y];
			const auto z = data[Z] * position[Z];

			const auto distance = x + y + z + data[W];

			if ( distance < -radius )
				return Result::Outside;

			if ( distance < radius )
				return Result::Intersect;
		}

		return Result::Inside;
	}

	Frustum::Result
	Frustum::isCollidingWith (const Math::Cuboid< float > & box) const noexcept
	{
		if ( !s_enableFrustumTest )
			return Result::Inside;

		const auto & max = box.maximum();
		const auto & min = box.minimum();

		/* centroid */
		{
			const auto midpoint = Vector< 3, float >::midPoint(max, min);

			if ( this->isCollidingWith(Vector< 3, float >(midpoint[X], midpoint[Y], midpoint[Z])) == Result::Inside )
				return Result::Intersect;
		}

		if ( this->isCollidingWith(Vector< 3, float >(max[X], max[Y], max[Z])) == Result::Inside )
			return Result::Intersect;

		if ( this->isCollidingWith(Vector< 3, float >(max[X], max[Y], min[Z])) == Result::Inside )
			return Result::Intersect;

		if ( this->isCollidingWith(Vector< 3, float >(max[X], min[Y], max[Z])) == Result::Inside )
			return Result::Intersect;

		if ( this->isCollidingWith(Vector< 3, float >(max[X], min[Y], min[Z])) == Result::Inside )
			return Result::Intersect;

		if ( this->isCollidingWith(Vector< 3, float >(min[X], max[Y], max[Z])) == Result::Inside )
			return Result::Intersect;

		if ( this->isCollidingWith(Vector< 3, float >(min[X], max[Y], min[Z])) == Result::Inside )
			return Result::Intersect;

		if ( this->isCollidingWith(Vector< 3, float >(min[X], min[Y], max[Z])) == Result::Inside )
			return Result::Intersect;

		if ( this->isCollidingWith(Vector< 3, float >(min[X], min[Y], min[Z])) == Result::Inside )
			return Result::Intersect;

		return Result::Outside;
	}

	Frustum::Result
	Frustum::isCollidingWith (float x, float y, float z, float size) const noexcept
	{
		if ( !s_enableFrustumTest )
			return Result::Inside;

		for ( const auto & plane : m_planes )
		{
			const auto & data = plane.data();

			const auto posX = data[X] * (x + size);
			const auto negX = data[X] * (x - size);

			const auto posY = data[Y] * (y + size);
			const auto negY = data[Y] * (y - size);

			const auto posZ = data[Z] * (z + size);
			const auto negZ = data[Z] * (z - size);

			if ( negX +  negY +  negZ +  data[W] > 0.0F )
				continue;

			if ( posX +  negY +  negZ +  data[W] > 0.0F )
				continue;

			if ( negX +  posY +  negZ +  data[W] > 0.0F )
				continue;

			if ( posX +  posY +  negZ +  data[W] > 0.0F )
				continue;

			if ( negX +  negY +  posZ +  data[W] > 0.0F )
				continue;

			if ( posX +  negY +  posZ +  data[W] > 0.0F )
				continue;

			if ( negX +  posY +  posZ +  data[W] > 0.0F )
				continue;

			if ( posX +  posY +  posZ +  data[W] > 0.0F )
				continue;

			return Result::Outside;
		}

		return Result::Inside;
	}

	std::ostream &
	operator<< (std::ostream & out, const Frustum & obj)
	{
		return out << "Frustum data :\n"
			"Right plane : " << obj.m_planes[Frustum::Right] << "\n"
			"Left plane : " << obj.m_planes[Frustum::Left] << "\n"
			"Bottom plane : " << obj.m_planes[Frustum::Bottom] << "\n"
			"Top plane : " << obj.m_planes[Frustum::Top] << "\n"
			"Far plane : " << obj.m_planes[Frustum::Far] << "\n"
			"Near plane : " << obj.m_planes[Frustum::Near] << '\n';
	}

	std::string
	to_string (const Frustum & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
