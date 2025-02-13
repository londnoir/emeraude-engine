/*
 * src/Resources/ResourceTrait.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "Resources/ResourceTrait.hpp"

/* STL inclusions. */
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <mutex>
#include <string>

/* Local inclusions. */
#include "Libraries/FastJSON.hpp"
#include "Libraries/String.hpp"
#include "Stores.hpp"
#include "Types.hpp"
#include "Manager.hpp"
#include "Tracer.hpp"

namespace Emeraude::Resources
{
	using namespace Libraries;

	static constexpr auto TracerTag{"ResourceChain"};

	ResourceTrait::ResourceTrait (const std::string & resourceName, uint32_t initialResourceFlagBits) noexcept
		: NameableTrait(resourceName), FlagTrait(initialResourceFlagBits)
	{

	}

	ResourceTrait::~ResourceTrait ()
	{
		/* NOTE: Check the resource status.
		 * It should be Loaded or Failed. */
		switch ( m_status )
		{
			case Status::Unloaded :
				if ( Stores::s_operationVerboseEnabled )
				{
					TraceInfo{TracerTag} << "The resource '" << this->name() << "' (" << this << ") is destroyed with status 'Unloaded' !";
				}
				break;

			case Status::Enqueuing :
				TraceWarning{TracerTag} << "The resource '" << this->name() << "' (" << this << ") is destroyed while still enqueueing dependencies (Automatic mode) !";
				break;

			case Status::ManualEnqueuing :
				TraceWarning{TracerTag} << "The resource '" << this->name() << "' (" << this << ") is destroyed while still enqueueing dependencies (Manual mode) !";
				break;

			case Status::Loading :
				TraceError{TracerTag} << "The resource '" << this->name() << "' (" << this << ") is destroyed while still loading !";
				break;

			case Status::Loaded :
				/* NOTE: Check the parent list. It should be empty ! */
				if ( !m_parents.empty() )
				{
					TraceError{TracerTag} << "The resource '" << this->name() << "' (" << this << ") is destroyed while still having " << m_parents.size() << " parent pointer(s) !";
				}

				/* NOTE: Check the dependency list. It should be empty ! */
				if ( !m_dependencies.empty() )
				{
					TraceError{TracerTag} << "The resource '" << this->name() << "' (" << this << ") is destroyed while still having " << m_dependencies.size() << " dependency pointer(s) !";
				}

				break;

			case Status::Failed :
			default:
				break;
		}
	}

	bool
	ResourceTrait::initializeEnqueuing (bool manual) noexcept
	{
		if ( Stores::s_operationVerboseEnabled )
		{
			TraceInfo{TracerTag} << "Beginning the creation of resource '" << this->name() << "' (" << this->classLabel() << ") ...";
		}

		switch ( m_status )
		{
			case Status::Unloaded :
				m_status = manual ? Status::ManualEnqueuing : Status::Enqueuing;
				[[fallthrough]];
			case Status::Enqueuing :
			case Status::ManualEnqueuing :
				return true;

			case Status::Loading :
				TraceError{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") is already loading !";

				return false;

			case Status::Loaded :
				TraceWarning{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") is already loaded !";

				return false;

			case Status::Failed :
			default:
				TraceError{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") has previously tried to be loaded, but failed !";

				return false;
		}
	}

	bool
	ResourceTrait::addDependency (ResourceTrait * dependency) noexcept
	{
		/* First, we check the current resource status. */
		switch ( m_status )
		{
			case Status::Unloaded :
				TraceError{TracerTag} <<
					"The resource '" << this->name() << "' (" << this->classLabel() << ") is not in loading stage ! "
					"You should call ResourceTrait::beginLoading() first.";

				return false;

			case Status::Enqueuing :
			case Status::ManualEnqueuing :
				/* The status is in the right condition to add dependency. */
				break;

			case Status::Loading :
				TraceError{TracerTag} <<
					"The resource '" << this->name() << "' (" << this->classLabel() << ") is loading !"
					"No more dependency can be added !";
				break;

			case Status::Loaded :
				TraceWarning{TracerTag} <<
					"The resource '" << this->name() << "' (" << this->classLabel() << ") is loaded !"
					"No more dependency can be added !";
				break;

			case Status::Failed :
			default:
				TraceError{TracerTag} <<
					"The resource '" << this->name() << "' (" << this->classLabel() << ") is failed !"
					"This resource should be removed.";

				return false;
		}

		if ( dependency == nullptr )
		{
			Tracer::error(TracerTag, "The dependency pointer is null !");

			return false;
		}

		/* If the dependency is loaded or already present.
		 * we don't need to add it. */
		if ( dependency->isLoaded() || m_dependencies.contains(dependency) )
		{
			if ( Stores::s_operationVerboseEnabled )
			{
				TraceInfo{TracerTag} <<
					"Resource dependency '" << dependency->name() << "' (" << dependency->classLabel() << ") is already loaded or in the queue. "
					"Skipping this dependency ...";
			}

			return true;
		}

		const auto result = m_dependencies.emplace(dependency);

		/* Set this resource as parent of the dependency (double-link). */
		if ( result.second )
		{
			dependency->m_parents.emplace(this);

			if ( Stores::s_operationVerboseEnabled )
			{
				TraceInfo{TracerTag} <<
					"Resource dependency '" << dependency->name() << "' (" << dependency->classLabel() << ") "
					"added to resource '" << this->name() << "' (" << this->classLabel() << "). "
					"Dependency count : " << m_dependencies.size() << ".";
			}

			return true;
		}

		m_status = Status::Failed;

		if ( Stores::s_operationVerboseEnabled )
		{
			TraceError{TracerTag} <<
				"Unable to dependency '" << dependency->name() << "' (" << dependency->classLabel() << ") "
				"to resource '" << this->name() << "' (" << this->classLabel() << ") !";
		}

		return false;
	}

	void
	ResourceTrait::dependencyLoaded (ResourceTrait * dependency) noexcept
	{
		if ( Stores::s_operationVerboseEnabled )
		{
			TraceInfo{TracerTag} <<
				"The dependency '" << dependency->name() << "' (" << dependency->classLabel() << ") "
				"is loaded from resource '" << this->name() << "' (" << this->classLabel() << ") !";
		}

		/* Removes the resource from dependencies. */
		m_dependencies.erase(dependency);

		/* Launch an overall check for dependencies loading. */
		this->checkDependencies();
	}

	void
	ResourceTrait::checkDependencies () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_checkAccess};

		/* NOTE: First we check the resource current status. */
		switch ( m_status )
		{
			/* For these status, there is no need to check dependencies now. */
			case Status::Unloaded :
			case Status::Enqueuing :
			case Status::ManualEnqueuing :
				if ( Stores::s_operationVerboseEnabled )
				{
					TraceInfo{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") still enqueuing dependencies !";
				}
				break;

			/* This is the state where we want to know if dependencies are loaded. */
			case Status::Loading :
			{
				/* NOTE: If any of dependencies are in a loading state. */
				if ( std::ranges::any_of(m_dependencies, [] (const auto & dependency) {return !dependency->isLoaded();}) )
				{
					return;
				}

				if ( Stores::s_operationVerboseEnabled )
				{
					TraceInfo{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") has no more dependency to wait for loading !";
				}

				if ( this->onDependenciesLoaded() )
				{
					m_status = Status::Loaded;

					this->notify(LoadFinished);

					if ( Stores::s_operationVerboseEnabled )
					{
						TraceSuccess{TracerTag} << "Resource '" << this->name() << "' (" << this->classLabel() << ") is successfully loaded !";
					}

					if ( !this->isTopResource() )
					{
						/* We want to notice parents the resource is loaded. */
						for ( auto * parent : m_parents )
						{
							parent->dependencyLoaded(this);
						}

						/* We don't need to keep tracks of parents. */
						m_parents.clear();
					}
				}
				else
				{
					m_status = Status::Failed;

					this->notify(LoadFailed);

					if ( Stores::s_operationVerboseEnabled )
					{
						TraceError{TracerTag} << "Resource '" << this->name() << "' (" << this->classLabel() << ") failed to load !";
					}
				}
			}
				break;

			case Status::Loaded :
				if ( !m_dependencies.empty() )
				{
					TraceError{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") status is loaded, but still have " << m_dependencies.size() << " dependencies.";
				}

				/* NOTE: We don't want to check again dependencies. */
				break;

			case Status::Failed :
			default:
				TraceError{TracerTag} <<
					"The resource '" << this->name() << "' (" << this->classLabel() << ") status is failed ! "
					"This resource should be removed !";
				break;
		}
	}

	bool
	ResourceTrait::setLoadSuccess (bool status) noexcept
	{
		if ( Stores::s_operationVerboseEnabled )
		{
			TraceInfo{TracerTag} << "Ending the creation of resource '" << this->name() << "' (" << this->classLabel() << ") ...";
		}

		/* NOTE: If status is not Enqueuing, ManualEnqueuing or Loading,
		 * the resource is in an incoherent status ! */
		switch ( m_status )
		{
			case Status::Unloaded :
				TraceError{TracerTag} <<
					"The resource '" << this->name() << "' (" << this->classLabel() << ") is not in a building stage ! "
					"You must call call ResourceTrait::beginLoading() before.";

				return false;

			case Status::Loaded :
				TraceError{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") is already loaded !";

				return false;

			case Status::Failed :
				TraceError{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") has previously failed to load !";

				return false;

			default:
				break;
		}

		if ( status )
		{
			/* Set the resource in loading stage.
			 * NOTE: No more sub-resource enqueuing is possible after this point. */
			m_status = Status::Loading;

			/* We want to check every dependency status.
			 * NOTE: This will eventually fire up the 'LoadFinished' event. */
			this->checkDependencies();
		}
		else
		{
			m_status = Status::Failed;

			this->notify(LoadFailed);

			TraceError{TracerTag} << "Resource '" << this->name() << "' (" << this << ") failed to load ...";
		}

		return status;
	}

	bool
	ResourceTrait::setManualLoadSuccess (bool status) noexcept
	{
		/* Avoid to call this method on an automatic loading resource. */
		if ( m_status != Status::ManualEnqueuing )
		{
			TraceError{TracerTag} << "Resource '" << this->name() << "' (" << this << ") is not in manual mode !";

			return false;
		}

		return this->setLoadSuccess(status);
	}

	bool
	ResourceTrait::load (const std::filesystem::path & filepath) noexcept
	{
	    Json::Value root;

	    if ( !FastJSON::getRootFromFile(filepath, root) )
		{
			TraceError{TracerTag} << "Unable to parse the resource file " << filepath << " !" "\n";

			/* NOTE: Set status here. */
			m_status = Status::Failed;

			this->notify(LoadFailed);

			return false;
		}

		/* Checks if additional stores before loading (optional) */
		Manager::instance()->stores().update(root, filepath.string());

		return this->load(root);
	}

	std::string
	ResourceTrait::getResourceNameFromFilepath (const std::filesystem::path & filepath, const std::string & storeName) noexcept
	{
		const auto filename = String::right(filepath.string(), storeName + IO::Separator);

#if IS_WINDOWS
	    /* NOTE: Resource name use the UNIX convention. */
	    return String::replace(IO::Separator, '/', String::removeFileExtension(filename));
#else
	    return String::removeFileExtension(filename);
#endif
	}
}
