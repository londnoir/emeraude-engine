/*
 * Emeraude/Graphics/RasterizationMode.cpp
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

#include "RasterizationMode.hpp"

/* C/C++ standard libraries. */
#include <iostream>

namespace Emeraude::Graphics
{
	bool RasterizationMode::s_isTriangleWindingOverridden = false;
	bool RasterizationMode::s_isPolygonModeOverridden = false;
	bool RasterizationMode::s_isCullingModeOverridden = false;
	bool RasterizationMode::s_isDepthBufferStatesOverridden = false;
	bool RasterizationMode::s_isStencilBufferStatesOverridden = false;
	bool RasterizationMode::s_isPolygonOffsetModeOverridden = false;

	RasterizationMode &
	RasterizationMode::operator= (const RasterizationMode & other) noexcept
	{
		if ( this != &other )
		{
			/* Setup triangle winding. */
			if ( !RasterizationMode::s_isTriangleWindingOverridden && m_flags[CounterClockwise] != other.m_flags[CounterClockwise] )
			{
				m_flags[CounterClockwise] = other.m_flags[CounterClockwise];

				//glFrontFace(m_flags[CounterClockwise] ? GL_CCW : GL_CW);
			}

			/* Set up the way how triangles are drawn. */
			if ( !RasterizationMode::s_isPolygonModeOverridden && m_polygonMode != other.m_polygonMode )
			{
				m_polygonMode = other.m_polygonMode;

				/* NOTE: In modern OpenGL, only GL_FRONT_AND_BACK is still valid. */
				switch ( m_polygonMode )
				{
					case PolygonMode::FillRectangle :
					case PolygonMode::Fill :
						//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
						break;

					case PolygonMode::Line :
						//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						break;

					case PolygonMode::Point :
						//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
						break;

					case PolygonMode::Invalid:
						break;
				}
			}

			/* Sets culling mode. */
			if ( !RasterizationMode::s_isCullingModeOverridden && m_cullingMode != other.m_cullingMode )
			{
				m_cullingMode = other.m_cullingMode;

				switch ( m_cullingMode )
				{
					case CullingMode::None :
						//glDisable(GL_CULL_FACE);
						break;

					case CullingMode::Back :
						//glEnable(GL_CULL_FACE);
						//glCullFace(GL_BACK);
						break;

					case CullingMode::Front :
						//glEnable(GL_CULL_FACE);
						//glCullFace(GL_FRONT);
						break;

					case CullingMode::Both :
						//glEnable(GL_CULL_FACE);
						//glCullFace(GL_FRONT_AND_BACK);
						break;
				}
			}

			if ( !RasterizationMode::s_isDepthBufferStatesOverridden )
			{
				if ( m_flags[DepthTestEnabled] != other.m_flags[DepthTestEnabled] )
				{
					m_flags[DepthTestEnabled] = other.m_flags[DepthTestEnabled];

					/*if ( m_flags[DepthTestEnabled] )
						glEnable(GL_DEPTH_TEST);
					else
						glDisable(GL_DEPTH_TEST);*/
				}

				if ( m_flags[DepthWriteEnabled] != other.m_flags[DepthWriteEnabled] )
				{
					m_flags[DepthWriteEnabled] = other.m_flags[DepthWriteEnabled];

					//glDepthMask(m_flags[DepthWriteEnabled] ? GL_TRUE : GL_FALSE);
				}
			}

			if ( !RasterizationMode::s_isStencilBufferStatesOverridden )
			{
				if ( m_flags[StencilTestEnabled] != other.m_flags[StencilTestEnabled] )
				{
					m_flags[StencilTestEnabled] = other.m_flags[StencilTestEnabled];

					/*if ( m_flags[StencilTestEnabled] )
						glEnable(GL_STENCIL_TEST);
					else
						glDisable(GL_STENCIL_TEST);*/
				}

				if ( m_flags[StencilWriteEnabled] != other.m_flags[StencilWriteEnabled] )
				{
					m_flags[StencilWriteEnabled] = other.m_flags[StencilWriteEnabled];

					//glStencilMask(m_flags[StencilWriteEnabled] ? 0xFF : 0x00);
				}
			}

			if ( !RasterizationMode::s_isPolygonOffsetModeOverridden )
			{
				if ( m_flags[PolygonOffsetEnabled] != other.m_flags[PolygonOffsetEnabled] )
				{
					m_flags[PolygonOffsetEnabled] = other.m_flags[PolygonOffsetEnabled];

					/*if ( m_flags[PolygonOffsetEnabled] )
					{
						glEnable(GL_POLYGON_OFFSET_FILL);
						glEnable(GL_POLYGON_OFFSET_LINE);
						glEnable(GL_POLYGON_OFFSET_POINT);
					}
					else
					{
						glDisable(GL_POLYGON_OFFSET_FILL);
						glDisable(GL_POLYGON_OFFSET_LINE);
						glDisable(GL_POLYGON_OFFSET_POINT);
					}*/
				}

				//if ( m_flags[PolygonOffsetEnabled] && ( m_polygonOffsetFactor != other.m_polygonOffsetFactor || m_polygonOffsetUnits != other.m_polygonOffsetUnits ) )
				//	glPolygonOffset(m_polygonOffsetFactor, m_polygonOffsetUnits);
			}
		}

		return *this;
	}

	void
	RasterizationMode::setInvertedTriangleWinding (bool state) noexcept
	{
		m_flags[CounterClockwise] = !state;
	}

	void
	RasterizationMode::setPolygonMode (PolygonMode mode) noexcept
	{
		m_polygonMode = mode;
	}

	void
	RasterizationMode::setCullingMode (CullingMode mode) noexcept
	{
		m_cullingMode = mode;
	}

	void
	RasterizationMode::setDepthBufferStates (bool readState, bool writeState) noexcept
	{
		m_flags[DepthTestEnabled] = readState;
		m_flags[DepthWriteEnabled] = writeState;
	}

	void
	RasterizationMode::setStencilBufferStates (bool readState, bool writeState) noexcept
	{
		m_flags[StencilTestEnabled] = readState;
		m_flags[StencilWriteEnabled] = writeState;
	}

	void
	RasterizationMode::setPolygonOffset (bool state, float factor, float units) noexcept
	{
		m_flags[PolygonOffsetEnabled] = state;
		m_polygonOffsetFactor = factor;
		m_polygonOffsetUnits = units;
	}

	void
	RasterizationMode::resetToDefaultStates () noexcept
	{
		/* Reset triangle winding. */
		if ( !RasterizationMode::s_isTriangleWindingOverridden )
		{
			m_flags[CounterClockwise] = true;

			//glFrontFace(GL_CCW);
		}

		/* Reset drawing mode. */
		if ( !RasterizationMode::s_isPolygonModeOverridden )
		{
			m_polygonMode = PolygonMode::Fill;

			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		/* Reset face culling. */
		if ( !RasterizationMode::s_isCullingModeOverridden )
		{
			m_cullingMode = CullingMode::Back;

			/*glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);*/
		}

		if ( !RasterizationMode::s_isDepthBufferStatesOverridden )
		{
			/* Reset depth test mode. */
			m_flags[DepthTestEnabled] = true;

			//glEnable(GL_DEPTH_TEST);

			/* Reset depth write mode. */
			m_flags[DepthWriteEnabled] = true;

			//glDepthMask(GL_TRUE);
		}

		if ( !RasterizationMode::s_isStencilBufferStatesOverridden )
		{
			/* Reset stencil test mode. */
			m_flags[StencilTestEnabled] = true;

			//glEnable(GL_STENCIL_TEST);

			/* Reset stencil write mode. */
			m_flags[StencilWriteEnabled] = true;

			//glStencilMask(1);
		}

		if ( !RasterizationMode::s_isPolygonOffsetModeOverridden )
		{
			/*glPolygonOffset(0.0F, 0.0F);

			glDisable(GL_POLYGON_OFFSET_FILL);
			glDisable(GL_POLYGON_OFFSET_LINE);
			glDisable(GL_POLYGON_OFFSET_POINT);*/
		}
	}

	std::ostream &
	operator<< (std::ostream & out, const RasterizationMode & obj)
	{
		using namespace std;

		out << "Polygon draw mode : ";

		switch ( obj.m_polygonMode )
		{
			case PolygonMode::Fill :
				out << "Fill" << '\n';
				break;

			case PolygonMode::Line :
				out << "Line" << '\n';
				break;

			case PolygonMode::Point :
				out << "Point" << '\n';
				break;

			case PolygonMode::FillRectangle :
				out << "FillRectangle" << '\n';
				break;

			case PolygonMode::Invalid :
				out << "Invalid" << '\n';
				break;
		}

		out << "Polygon culling mode : ";

		switch ( obj.m_cullingMode )
		{
			case CullingMode::None :
				out << "None" << '\n';
				break;

			case CullingMode::Back :
				out << "Back" << '\n';
				break;

			case CullingMode::Front :
				out << "Front" << '\n';
				break;

			case CullingMode::Both :
				out << "Both" << '\n';
				break;
		}

		out <<
			"ShapeTriangle winding : " << ( obj.m_flags[RasterizationMode::CounterClockwise] ? "Counter-Clockwise (Default)" : "Clockwise" ) << '\n' <<
			"Depth buffer read : " << ( obj.m_flags[RasterizationMode::DepthTestEnabled] ? "Enabled" : "Disabled" ) << '\n' <<
			"Depth buffer write : " << ( obj.m_flags[RasterizationMode::DepthWriteEnabled] ? "Enabled" : "Disabled" ) << '\n' <<
			"Stencil buffer read : " << ( obj.m_flags[RasterizationMode::StencilTestEnabled] ? "Enabled" : "Disabled" ) << '\n' <<
			"Stencil buffer write : " << ( obj.m_flags[RasterizationMode::StencilWriteEnabled] ? "Enabled" : "Disabled" ) << '\n' <<
			"ShapeTriangle winding overridden : " << ( RasterizationMode::s_isTriangleWindingOverridden ? "Yes" : "No" ) << '\n' <<
			"Polygon mode overridden : " << ( RasterizationMode::s_isPolygonModeOverridden ? "Yes" : "No" ) << '\n' <<
			"Culling mode overridden : " << ( RasterizationMode::s_isCullingModeOverridden ? "Yes" : "No" ) << '\n' <<
			"Depth configuration overridden : " << ( RasterizationMode::s_isDepthBufferStatesOverridden ? "Yes" : "No" ) << '\n' <<
			"Stencil configuration overridden : " << ( RasterizationMode::s_isStencilBufferStatesOverridden ? "Yes" : "No" ) << '\n' <<
			"Polygon offset overridden : " << ( RasterizationMode::s_isPolygonOffsetModeOverridden ? "Yes" : "No" ) << '\n';

		return out;
	}

	void
	RasterizationMode::overrideTriangleWinding (bool state, bool counterClockwise) noexcept
	{
		/*if ( state )
			glFrontFace(counterClockwise ? GL_CCW : GL_CW);
		else
			glFrontFace(GL_CCW);

		s_isTriangleWindingOverridden = state;*/
	}

	bool
	RasterizationMode::isTriangleWindingOverriden () noexcept
	{
		return s_isTriangleWindingOverridden;
	}

	bool
	RasterizationMode::triangleWinding () noexcept
	{
		/*GLint value;

		glGetIntegerv(GL_FRONT_FACE, &value);

		return value == static_cast< GLenum >(GL_CCW);*/
		return false;
	}

	void
	RasterizationMode::overridePolygonMode (bool overridingState, PolygonMode mode) noexcept
	{
		switch ( mode )
		{
			case PolygonMode::Fill :
				//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;

			case PolygonMode::Line :
				//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				break;

			case PolygonMode::Point :
				//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				break;

			default:
				break;
		}

		s_isPolygonModeOverridden = overridingState;
	}

	bool
	RasterizationMode::isPolygonModeOverridden () noexcept
	{
		return s_isPolygonModeOverridden;
	}

	PolygonMode
	RasterizationMode::polygonMode () noexcept
	{
		/*GLint params[2];

		glGetIntegerv(GL_POLYGON_MODE, params);

		switch ( params[0] )
		{
			case GL_POINT :
				return PolygonMode::Point;

			case GL_LINE :
				return PolygonMode::Line;

			case GL_FILL :
				return PolygonMode::Fill;
		}*/

		return PolygonMode::Fill;
	}

	void
	RasterizationMode::overrideCullingMode (bool overridingState, CullingMode mode) noexcept
	{
		/*switch ( mode )
		{
			case CullingMode::None :
				glDisable(GL_CULL_FACE);
				break;

			/ * NOTE: Default state * /
			case CullingMode::Back :
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				break;

			case CullingMode::Front :
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				break;

			case CullingMode::Both :
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT_AND_BACK);
				break;
		}*/

		s_isCullingModeOverridden = overridingState;
	}

	bool
	RasterizationMode::isCullingModeOverridden () noexcept
	{
		return s_isCullingModeOverridden;
	}

	CullingMode
	RasterizationMode::cullingMode () noexcept
	{
		/*if ( glIsEnabled(GL_CULL_FACE) == GL_FALSE )
			return CullingMode::None;

		GLint params;

		glGetIntegerv(GL_CULL_FACE_MODE, &params);

		switch ( params )
		{
			case GL_BACK :
				return CullingMode::Back;

			case GL_FRONT :
				return CullingMode::Front;

			case GL_FRONT_AND_BACK :
				return CullingMode::Both;
		}*/

		return CullingMode::None;
	}

	void
	RasterizationMode::overridePolygonOffset (bool overridingState, bool offsetState, float factor, float units) noexcept
	{
		/*if ( offsetState )
		{
			glEnable(GL_POLYGON_OFFSET_FILL);
			glEnable(GL_POLYGON_OFFSET_LINE);
			glEnable(GL_POLYGON_OFFSET_POINT);
		}
		else
		{
			glDisable(GL_POLYGON_OFFSET_FILL);
			glDisable(GL_POLYGON_OFFSET_LINE);
			glDisable(GL_POLYGON_OFFSET_POINT);
		}

		glPolygonOffset(factor, units);*/

		s_isPolygonOffsetModeOverridden = overridingState;
	}

	bool
	RasterizationMode::isPolygonOffsetOverriden () noexcept
	{
		return s_isPolygonOffsetModeOverridden;
	}

	float
	RasterizationMode::polygonOffsetFactor () noexcept
	{
		/*GLfloat value;

		glGetFloatv(GL_POLYGON_OFFSET_FACTOR, &value);

		return value;*/
		return 0.0F;
	}

	float
	RasterizationMode::polygonOffsetUnits () noexcept
	{
		/*GLfloat value;

		glGetFloatv(GL_POLYGON_OFFSET_UNITS, &value);

		return value;*/
		return 0.0F;
	}

	void
	RasterizationMode::overrideDepthBufferStates (bool overridingState, bool readState, bool writeState) noexcept
	{
		/*if ( readState )
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		glDepthMask(writeState ? GL_TRUE : GL_FALSE);*/

		s_isDepthBufferStatesOverridden = overridingState;
	}

	bool
	RasterizationMode::isDepthBufferStatesOverriden () noexcept
	{
		return s_isDepthBufferStatesOverridden;
	}

	bool
	RasterizationMode::isDepthBufferReadingEnabled () noexcept
	{
		//return glIsEnabled(GL_DEPTH_TEST) == GL_TRUE;
		return false;
	}

	bool
	RasterizationMode::isDepthBufferWrittingEnabled () noexcept
	{
		/*GLboolean writingState;

		glGetBooleanv(GL_DEPTH_WRITEMASK, &writingState);

		return writingState == GL_TRUE;*/
		return false;
	}

	void
	RasterizationMode::overrideStencilBufferStates (bool overridingState, bool readState, bool writeState) noexcept
	{
		/*if ( readState )
			glEnable(GL_STENCIL_TEST);
		else
			glDisable(GL_STENCIL_TEST);

		glStencilMask(writeState ? 1 : 0);*/

		s_isStencilBufferStatesOverridden = overridingState;
	}

	bool
	RasterizationMode::isStencilBufferStatesOverriden () noexcept
	{
		return s_isStencilBufferStatesOverridden;
	}

	bool
	RasterizationMode::isStencilBufferReadingEnabled () noexcept
	{
		//return glIsEnabled(GL_STENCIL_TEST) == GL_TRUE;
		return false;
	}

	bool
	RasterizationMode::isStencilBufferWrittingEnabled () noexcept
	{
		/*GLint writingState;

		glGetIntegerv(GL_STENCIL_WRITEMASK, &writingState);

		return writingState == 0xFF;*/
		return false;
	}

	void
	RasterizationMode::enableColorBufferWritting (bool redState, bool greenState, bool blueState, bool alphaState) noexcept
	{
		/*glColorMask(
			redState ? GL_TRUE : GL_FALSE,
			greenState ? GL_TRUE : GL_FALSE,
			blueState ? GL_TRUE : GL_FALSE,
			alphaState ? GL_TRUE : GL_FALSE
		);*/
	}

	bool
	RasterizationMode::isColorBufferWrittingEnabled (bool strict) noexcept
	{
		/*std::array< GLboolean, 4 > values;

		glGetBooleanv(GL_COLOR_WRITEMASK, values.data());

		if ( strict )
			return ( values[0] == GL_TRUE && values[1] == GL_TRUE && values[2] == GL_TRUE && values[3] == GL_TRUE );
		else
			return ( values[0] == GL_TRUE || values[1] == GL_TRUE || values[2] == GL_TRUE || values[3] == GL_TRUE );*/
		return false;
	}

	bool
	RasterizationMode::isRedColorBufferWrittingEnabled () noexcept
	{
		/*std::array< GLboolean, 4 > values;

		glGetBooleanv(GL_COLOR_WRITEMASK, values.data());

		return ( values[0] == GL_TRUE );*/
		return false;
	}

	bool
	RasterizationMode::isGreenColorBufferWrittingEnabled () noexcept
	{
		/*std::array< GLboolean, 4 > values;

		glGetBooleanv(GL_COLOR_WRITEMASK, values.data());

		return ( values[1] == GL_TRUE );*/
		return false;
	}

	bool
	RasterizationMode::isBlueColorBufferWrittingEnabled () noexcept
	{
		/*std::array< GLboolean, 4 > values;

		glGetBooleanv(GL_COLOR_WRITEMASK, values.data());

		return ( values[2] == GL_TRUE );*/
		return false;
	}

	bool
	RasterizationMode::isAlphaColorBufferWrittingEnabled () noexcept
	{
		/*std::array< GLboolean, 4 > values;

		glGetBooleanv(GL_COLOR_WRITEMASK, values.data());

		return ( values[3] == GL_TRUE );*/
		return false;
	}
}
