/*
 * Libraries/VertexFactory/FileFormatOBJ.hpp
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
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "FileFormatInterface.hpp"

/* Local inclusions for usages. */
#include "String.hpp"
#include "VertexFactory/ShapeBuilder.hpp"

namespace Libraries::VertexFactory
{
	/**
	 * @brief An OBJ vertex structure.
	 * @note OBJ format use index starting at 1.
	 */
	struct OBJVertex
	{
		size_t vIndex = 0;
		size_t vtIndex = 0;
		size_t vnIndex = 0;
	};

	/** @brief An OBJ triangle structure. */
	using OBJTriangle = std::array< OBJVertex, 3 >;

	/**
	 * @brief The FileFormatOBJ class.
	 * @tparam data_t The data precision type.
	 * @note http://www.fileformat.info/format/wavefrontobj/egff.htm
	 * @extends Libraries::VertexFactory::FileFormatInterface
	 */
	template< typename data_t, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	class FileFormatOBJ final : public FileFormatInterface< data_t >
	{
		public:
			
			/**
			 * @brief Constructs a default file format.
			 */
			FileFormatOBJ () noexcept
			{
				m_currentGroup = m_groups.emplace("default", std::vector< OBJTriangle >{}).first;
			}

			/** @copydoc Libraries::VertexFactory::FileFormatInterface::readFile() */
			[[nodiscard]]
			bool
			readFile (const Path::File & filepath, Shape< data_t > & geometry) noexcept override
			{
				/* 0. Opening the file. */
				std::ifstream file(to_string(filepath));

				if ( file.is_open() )
				{
					/* 1. Read a first time to calculate the space required for the structure. */
					if ( !this->firstPass(file) )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", step 1 'Reserving space' has failed !" "\n";

						return false;
					}

					file.clear();
					file.seekg(0);

					/* 2. Read a second time to fill vertex, normals and texture coordinates array. */
					if ( !this->secondPass(file) )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", step 2 'Copying base data' has failed !" "\n";

						return false;
					}

					file.clear();
					file.seekg(0);

					/* 3. Read a third and final time to assemble faces. */
					if ( !this->thirdPass(file) )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", step 3 'Assembling faces' has failed !" "\n";

						return false;
					}

					file.close();
				}
				else
				{
					std::cerr << __PRETTY_FUNCTION__ << ", unable to read OBJ file '" << filepath << "' !" "\n";

					return false;
				}

				return this->convertToGeometry(geometry);
			}

			/** @copydoc Libraries::VertexFactory::FileFormatInterface::writeFile() */
			[[nodiscard]]
			bool
			writeFile (const Path::File & filepath, const Shape< data_t > & geometry) const noexcept override
			{
				if ( !geometry.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry parameter is invalid !" "\n";

					return false;
				}

				if ( m_v.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", there is nothing to write !" "\n";

					return false;
				}

				/* FIXME: This only write an opened OBJ file for testing ! The geometry parameter must fill first the OBJ containers. */

				std::ofstream file;

				file.open(to_string(filepath));

				if ( !file.is_open() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", unable to open '" << filepath << "' file to write !" "\n";

					return false;
				}

				for ( const auto & value : m_v )
				{
					file << "v " << value[Math::X] << ' ' << value[Math::Y] << ' ' << value[Math::Z] << '\n';
				}
				
				for ( const auto & value : m_vt )
				{
					file << "vt " << value[Math::X] << ' ' << value[Math::Y] << '\n';
				}
				
				for ( const auto & value : m_vn )
				{
					file << "vn " << value[Math::X] << ' ' << value[Math::Y] << ' ' << value[Math::Z] << '\n';
				}
				
				for ( const auto & group : m_groups )
				{
					const auto & triangles = group.second;

					if ( triangles.empty() )
					{
						continue;
					}
					
					file << "g " << group.first << '\n';

					for ( const auto & triangle : triangles )
					{
						file << "f " <<
							 triangle[0].vIndex << '/' << triangle[0].vtIndex << '/' << triangle[0].vnIndex << ' ' <<
							 triangle[1].vIndex << '/' << triangle[1].vtIndex << '/' << triangle[1].vnIndex << ' ' <<
							 triangle[2].vIndex << '/' << triangle[2].vtIndex << '/' << triangle[2].vnIndex << '\n';
					}
				}

				file.close();

				return true;
			}

			/**
			 * @brief Sets a scale factor for the final object.
			 * @param factor The scale factor value.
			 * @return FileFormatOBJ &
			 */
			FileFormatOBJ &
			setScaleFactor (data_t factor) noexcept
			{
				m_scaleFactor = factor;

				return *this;
			}

			/**
			 * @brief Rotates the final object on X axis with -90 degree.
			 * @param state The state.
			 * @return FileFormatOBJ &
			 */
			FileFormatOBJ &
			rotateNeg90X (bool state) noexcept
			{
				m_flags[NegX90] = state;

				return *this;
			}

		private:

			/* Flag names */
			static constexpr auto NegX90 = 0UL;

			static constexpr data_t NegativeCos90Degree = -0;
			static constexpr data_t NegativeSin90Degree = -1;

			enum class LineType
			{
				Unknown,
				Comment,
				VertexValues,
				TexCoordValues,
				NormalValues,
				FaceAssembly,
				ObjectName,
				GroupName,
				SmoothShadingState,
				MaterialFile,
				MaterialState
			};

			/**
			 * @brief Reads a first time to calculate the space required for the structure.
			 * @param file The OBJ file.
			 * @return bool
			 */
			bool
			firstPass (std::ifstream & file) noexcept
			{
				std::string line;

				auto verticesCount = 0UL;
				auto texCoordCount = 0UL;
				auto normalCount = 0UL;
				auto facesCount = 0UL;

				std::map< std::string, size_t > facesCountPerGroup;

				while ( std::getline(file, line) )
				{
					line = String::trim(line);

					if ( line.empty() )
					{
						continue;
					}
					
					switch ( FileFormatOBJ::getLineType(line) )
					{
						case LineType::GroupName :
							if ( this->parseGLine(line) )
							{
								auto groupIt = facesCountPerGroup.find(m_currentGroup->first);

								if ( groupIt == facesCountPerGroup.cend() )
								{ 
									facesCountPerGroup[m_currentGroup->first] = 0; 
								}
							}
							else
							{
								std::cerr << __PRETTY_FUNCTION__ << ", invalid 'g' definition : " << line << '\n';
							}
							break;

						case LineType::VertexValues :
							verticesCount++;
							break;

						case LineType::TexCoordValues :
							texCoordCount++;
							break;

						case LineType::NormalValues :
							normalCount++;
							break;

						case LineType::FaceAssembly :
							facesCount++;
							facesCountPerGroup[m_currentGroup->first]++;
							break;

						case LineType::Unknown :
							std::cerr << __PRETTY_FUNCTION__ << ", unknown line type in OBJ format : " << line << '\n';
							break;

						case LineType::Comment :
							std::cout << __PRETTY_FUNCTION__ << ", OBJ Comment : " << line << '\n';
							break;

						case LineType::ObjectName :
						case LineType::SmoothShadingState :
						case LineType::MaterialFile :
						case LineType::MaterialState :
							/* Ignored ... */
							break;
					}
				}

#ifdef OBJ_DEBUG
				std::cout <<
					"[OBJ_DEBUG] File Parsing - First pass result.\n" <<
					"\tVertices : " << verticesCount << '\n' <<
					"\tTexture Coordinates : " << texCoordCount << '\n' <<
					"\tNormals : " << normalCount << '\n' <<
					"\tGroups : " << m_groups.size() << '\n' <<
					"\tFaces : " << facesCount << '\n';

				for ( const auto & group : facesCountPerGroup )
					std::cout << "\t\tGroup '" << group.first << "', Faces : " << group.second << '\n';

				std::cout << '\n';
#endif

				if ( verticesCount == 0 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", there is no vertex definition in the OBJ file. Aborting." "\n";

					return false;
				}

				/* NOTE : Disable texture coordinates from vertex attributes,
				 * if they don't exist within the file. */
				if ( texCoordCount == 0 )
				{
					std::cout << __PRETTY_FUNCTION__ << ", there is no texture coords in the OBJ file. Disabling texture2Ds coordinates." "\n";

				}

				if ( facesCount == 0 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", there is no face definition in the OBJ file. Aborting." "\n";

					return false;
				}

				/* Reserving memory space. */
				m_v.reserve(verticesCount);
				m_vt.reserve(texCoordCount);
				m_vn.reserve(normalCount);

				for ( const auto & group : facesCountPerGroup )
				{
					m_groups[group.first].reserve(group.second * 2); // NOTE: assuming face can be expressed in quads
				}

				return true;
			}

			/**
			 * @brief Reads a second time to fill vertex, normals and texture coordinates array.
			 * @param file The OBJ file.
			 * @return bool
			 */
			bool
			secondPass (std::ifstream & file) noexcept
			{
				std::string line;

				while ( std::getline(file, line) )
				{
					line = String::trim(line);

					if ( line.empty() )
					{
						continue;
					}

					switch ( FileFormatOBJ::getLineType(line) )
					{
						case LineType::VertexValues :
						{
							Math::Vector< 3, data_t > position(line, ' ', 1);

							if ( m_flags[NegX90] )
							{
								const auto yCos = position[Math::Y] * NegativeCos90Degree;
								const auto ySin = position[Math::Y] * NegativeSin90Degree;

								const auto zCos = position[Math::Z] * NegativeCos90Degree;
								const auto zSin = position[Math::Z] * NegativeSin90Degree;

								position[Math::Y] = yCos - zSin;
								position[Math::Z] = ySin + zCos;
							}

							if ( Utility::different(m_scaleFactor, 1.0F) )
							{
								position.scale(m_scaleFactor);
							}

							m_v.emplace_back(position);
						}
							break;

						case LineType::TexCoordValues :
							m_vt.emplace_back(line, ' ', 1);
							break;

						case LineType::NormalValues :
							m_vn.emplace_back(line, ' ', 1);
							break;

						case LineType::GroupName :
						case LineType::FaceAssembly :
						case LineType::Unknown :
						case LineType::Comment :
						case LineType::ObjectName :
						case LineType::SmoothShadingState :
						case LineType::MaterialFile :
						case LineType::MaterialState :
							/* Ignored ... */
							break;
					}
				}

#ifdef OBJ_DEBUG
				std::cout <<
					"[OBJ_DEBUG] File Parsing - Second pass result.\n" <<
					"\tVertices array size : " << m_v.size() << '\n' <<
					"\tTexture Coordinates array size : " << m_vt.size() << '\n' <<
					"\tNormals array size : " << m_vn.size() << '\n';

				std::cout << '\n';
#endif

				return true;
			}

			/**
			 * @brief Reads a third and final time to assemble faces.
			 * @param file The OBJ file.
			 * @return bool
			 */
			bool
			thirdPass (std::ifstream & file) noexcept
			{
				std::string line;

				while ( std::getline(file, line) )
				{
					line = String::trim(line);

					if ( line.empty() )
					{
						continue;
					}

					switch ( FileFormatOBJ::getLineType(line) )
					{
						case LineType::GroupName :
							/* NOTE: This is only useful to switch back to the right group. */
							if ( !this->parseGLine(line) )
							{
								std::cerr << __PRETTY_FUNCTION__ << ", invalid 'g' definition : " << line << '\n';
							}
							break;

						case LineType::FaceAssembly :
							/* NOTE: At this point every vertex attributes are already loaded. */
							if ( !this->parseFLine(line) )
							{
								std::cerr << __PRETTY_FUNCTION__ << ", invalid 'f' definition : " << line << '\n';
							}
							break;

						case LineType::VertexValues :
						case LineType::TexCoordValues :
						case LineType::NormalValues :
						case LineType::Unknown :
						case LineType::Comment :
						case LineType::ObjectName :
						case LineType::SmoothShadingState :
						case LineType::MaterialFile :
						case LineType::MaterialState :
							/* Ignored ... */
							break;
					}
				}

#ifdef OBJ_DEBUG
				std::cout <<
					"[OBJ_DEBUG] File Parsing - Third pass result.\n" <<
					"\tVertices array size : " << m_v.size() << '\n' <<
					"\tTexture Coordinates array size : " << m_vt.size() << '\n' <<
					"\tNormals array size : " << m_vn.size() << '\n' <<
					"\tGroups array size : " << m_groups.size() << '\n';

				for ( const auto & group : m_groups )
					std::cout << "\t\tGroup '" << group.first << "', triangles array size : " << group.second.size() << '\n';

				std::cout << '\n';
#endif

				return true;
			}

			/**
			 * @brief Parses a G line for group.
			 * @param line The current line in the OBJ file.
			 * @return bool
			 */
			bool
			parseGLine (const std::string & line) noexcept
			{
				/* Undersized group name can't be used ! */
				if ( line.size() <= 2 )
				{
					return false;
				}

				const auto groupName = line.substr(2, line.length() - 2);

				auto groupIt = m_groups.find(groupName);

				if ( groupIt == m_groups.end() )
				{
					m_currentGroup = m_groups.emplace(groupName, std::vector<OBJTriangle>()).first;
				}
				else
				{
					m_currentGroup = groupIt;
				}

				return true;
			}

			/**
			 * @brief Returns a list of usable vertices from F line.
			 * @param OBJVertices Vertices definition from the F line as indexes.
			 * @param vertices The target vector with final vertex.
			 * @return bool
			 */
			bool
			extractVertices (const std::vector< std::string > & OBJVertices, std::vector< OBJVertex > & vertices) const noexcept
			{
				if ( OBJVertices.size() != vertices.size() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", array are not the same size !" "\n";

					return false;
				}

				for ( auto index = 0U; index < OBJVertices.size(); index++ )
				{
					/* Line format : "f v1 v2 v3 v4" */
					if ( OBJVertices[index].find('/') == std::string::npos )
					{
						vertices[index].vIndex = String::toNumber< uint32_t >(OBJVertices[index]);
					}
					else
					{
						auto subCmp = String::explode(String::trim(OBJVertices[index]), '/', false);

						vertices[index].vIndex = String::toNumber< uint32_t >(subCmp[0]);

						/* Line format : "f v1//vn1 v2//vn2 v3//vn3" */
						if ( OBJVertices[index].find("//") != std::string::npos )
						{
							vertices[index].vnIndex = String::toNumber< uint32_t >(subCmp[1]);
						}
						/* Line format : "f v1/vt1 v2/vt2 v3/vt3" */
						else if ( subCmp.size() == 2 )
						{
							vertices[index].vtIndex = String::toNumber< uint32_t >(subCmp[1]);
						}
						/* Line format : "f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3" */
						else
						{
							vertices[index].vtIndex = String::toNumber< uint32_t >(subCmp[1]);
							vertices[index].vnIndex = String::toNumber< uint32_t >(subCmp[2]);
						}
					}

					/* Checks for outbound with vertices list. */
					if ( (vertices[index].vIndex - 1) >= m_v.size() )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", vertex #" << vertices[index].vIndex << " doesn't exist in OBJ file." "\n";

						return false;
					}

					/* Checks for outbound with texture coords list. */
					if ( vertices[index].vtIndex > 0 && (vertices[index].vtIndex - 1) >= m_vt.size() )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", texture coordinates #" << vertices[index].vtIndex << " doesn't exist in OBJ file." "\n";

						return false;
					}

					/* Checks for outbound with normals list. */
					if ( vertices[index].vnIndex > 0 && (vertices[index].vnIndex - 1) >= m_vn.size() )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", normal #" << vertices[index].vnIndex << " doesn't exist in OBJ file." "\n";

						return false;
					}
				}

				return true;
			}

			/**
			 * @brief Assembles a triangle from a F line.
			 * @param vertices Extracted vertices.
			 * @return bool
			 */
			bool
			assembleTriangles (const std::vector< OBJVertex > & vertices) noexcept
			{
				OBJTriangle triangle;

				auto triangleVertexIndex = 0U;

				/* 3+ vertex list */
				for ( auto vertexIndex = 0U; vertexIndex < vertices.size(); ++vertexIndex )
				{
					triangle[triangleVertexIndex++] = vertices[vertexIndex];

					if ( triangleVertexIndex > 2 )
					{
						/* We copy the new triangle. */
						m_currentGroup->second.emplace_back(triangle);

						/* Rearrange the next triangle from previous vertices. */
						triangle[0] = vertices[vertexIndex-2];
						triangle[1] = vertices[vertexIndex];

						/* Reset triangle vertex index. */
						triangleVertexIndex = 2;
					}
				}

				return true;
			}

			/**
			 * @brief Parses a F line to assemble a triangle.
			 * @param line The current line in the OBJ file.
			 * @return bool
			 */
			bool
			parseFLine (const std::string & line) noexcept
			{
				/* 1. Split the vertex definition separated by a space */
				auto OBJVertices = String::explode(String::trim(line), ' ', false);

				/* Removes "f " */
				OBJVertices.erase(OBJVertices.begin());

				if ( OBJVertices.size() < 3 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", an OBJ face must be defined by a least 3 vertices !" "\n" "Faulty line: " << line << '\n';

					return false;
				}

				/* 2. Extract vertices. */
				std::vector< OBJVertex > vertices(OBJVertices.size());

				if ( !this->extractVertices(OBJVertices, vertices) )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", unable to extract vertices !" "\n" "Faulty line: " << line << '\n';

					return false;
				}

				/* 3. Assembling triangles. */
				return this->assembleTriangles(vertices);
			}

			/**
			 * @brief Converts the internal format to the native one.
			 * @param geometry A reference to the native geometry.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			convertToGeometry (Shape< data_t > & geometry) const noexcept
			{
				if ( m_v.empty() )
				{
					return false;
				}

				/* 1. Check data and reserve space. */
				auto trianglesCount = std::accumulate(m_groups.cbegin(), m_groups.cend(), 0UL, [] (auto sum, const auto & item) {
					return sum + item.second.size();
				});

				/* NOTE: There is no vertex color in OBJ. */
				geometry.reserveData(m_v.size(), m_vt.size(), 0U, trianglesCount);

				ShapeBuilderOptions< data_t > options{};
				options.enableGlobalVertexColor(PixelFactory::White);

				ShapeBuilder builder{geometry, options};
				builder.beginConstruction(ConstructionMode::Triangles);

				/* Per groups of triangles */
				for ( const auto & group : m_groups )
				{
					const auto & triangles = group.second;

					/* NOTE: A group can be empty. ie 'default' */
					if ( triangles.empty() )
					{
						continue;
					}

					/* Declare a new group to the builder. */
					builder.newGroup();

					/* Vertices + Texture Coordinates + Normals. */
					if ( !m_vt.empty() && !m_vn.empty() )
					{
						for ( const auto & triangle : triangles )
						{
							for ( const auto &vertex: triangle )
							{
								builder.newVertex(m_v[vertex.vIndex - 1], m_vt[vertex.vtIndex - 1], m_vn[vertex.vnIndex - 1]);
							}
						}
					}
					/* Vertices + Texture Coordinates. */
					else if ( !m_vt.empty() )
					{
						for ( const auto & triangle : triangles )
						{
							for ( const auto &vertex: triangle )
							{
								builder.newVertex(m_v[vertex.vIndex - 1], m_vt[vertex.vtIndex - 1]);
							}
						}
					}
					/* Vertices + Normals. */
					else if ( !m_vn.empty() )
					{
						for ( const auto & triangle : triangles )
						{
							for ( const auto &vertex: triangle )
							{
								builder.newVertex(m_v[vertex.vIndex - 1], m_vn[vertex.vnIndex - 1]);
							}
						}
					}
					/* Vertices */
					else
					{
						for ( const auto & triangle : triangles )
						{
							for ( const auto &vertex: triangle )
							{
								builder.newVertex(m_v[vertex.vIndex - 1]);
							}
						}
					}
				}

				builder.endConstruction();

				return true;
			}

			/**
			 * @brief Determines the type of the OBJ file line.
			 * @param line The current parsed line.
			 * @return LineType
			 */
			static
			LineType
			getLineType (const std::string & line) noexcept
			{
				/* # this is a comment */
				if ( String::startsWith(line, "#") )
				{
					return LineType::Comment;
				}

				/* mtllib [external .mtl file name] */
				if ( String::startsWith(line, "mtllib") )
				{
					return LineType::MaterialFile;
				}

				/* usemtl [material name] */
				if ( String::startsWith(line, "usemtl") )
				{
					return LineType::MaterialState;
				}

				/* vt 0.500 -1.352 [0.234] */
				if ( String::startsWith(line, "vt ") )
				{
					return LineType::TexCoordValues;
				}

				/* vn 0.707 0.000 0.707 */
				if ( String::startsWith(line, "vn ") )
				{
					return LineType::NormalValues;
				}

				/* v 0.123 0.234 0.345 1.0 */
				if ( String::startsWith(line, "v ") )
				{
					return LineType::VertexValues;
				}

				/*
				f v1 v2 v3 v4
				f v1/vt1 v2/vt2 v3/vt3
				f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
				f v1//vn1 v2//vn2 v3//vn3
				*/
				if ( String::startsWith(line, "f ") )
				{
					return LineType::FaceAssembly;
				}

				/* o [object name] */
				if ( String::startsWith(line, "o ") )
				{
					return LineType::ObjectName;
				}

				/* g [group name] */
				if ( String::startsWith(line, "g ") )
				{
					return LineType::GroupName;
				}

				/* s 1 OR s off */
				if ( String::startsWith(line, "s ") )
				{
					return LineType::SmoothShadingState;
				}

				/* ??? undetermined line */
				return LineType::Unknown;
			}

			std::vector< Math::Vector< 3, data_t > > m_v{};
			std::vector< Math::Vector< 2, data_t > > m_vt{};
			std::vector< Math::Vector< 3, data_t > > m_vn{};
			std::map< std::string, std::vector< OBJTriangle > > m_groups{};
			std::map< std::string, std::vector< OBJTriangle > >::iterator m_currentGroup{};
			data_t m_scaleFactor{1};
			std::array< bool, 4 > m_flags{
				false/*NegX90*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
			};
	};
}
