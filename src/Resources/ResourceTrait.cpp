/*
 * Emeraude/Resources/ResourceTrait.cpp
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

#include "Resources/ResourceTrait.hpp"

/* C/C++ standard libraries. */
#include <algorithm>

/* Local inclusions */
#include "Manager.hpp"
#include "Tracer.hpp"

namespace Emeraude::Resources
{
	using namespace Libraries;

	constexpr auto TracerTag{"ResourceChain"};

	ResourceTrait::ResourceTrait (const std::string & resourceName, uint32_t flagBits) noexcept
		: NamedItem(resourceName), FlagTrait(flagBits)
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

				return true;

			case Status::Enqueuing :
			case Status::ManualEnqueuing :
				TraceWarning{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") is already enqueuing dependencies !";

				return true;

			/* This is an error, the resource use manual loading. */
			case Status::Loading :
				TraceError{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") is already loading !";

				return false;

			case Status::Loaded :
				TraceWarning{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") is already loaded !";

				return false;

			case Status::Failed :
				TraceError{TracerTag} << "The resource '" << this->name() << "' (" << this->classLabel() << ") has previously tried to be loaded, but failed !";

				return false;
		}

		return false;
	}

	bool
	ResourceTrait::beginLoading () noexcept
	{
		return this->initializeEnqueuing(false);
	}

	bool
	ResourceTrait::enableManualLoading () noexcept
	{
		return this->initializeEnqueuing(true);
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

		/* If the dependency is loaded. we don't need to add it. */
		if ( dependency->isLoaded() )
		{
			if ( Stores::s_operationVerboseEnabled )
			{
				TraceInfo{TracerTag} <<
					"Resource dependency '" << dependency->name() << "' (" << dependency->classLabel() << ") is already loaded. "
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
					TraceInfo{TracerTag} <<
						"The resource '" << this->name() << "' (" << this->classLabel() << ") "
						"still enqueuing dependencies !";
				}
				break;

			/* This is the state where we want to know if dependencies are loaded. */
			case Status::Loading :
			{
				const auto stillLoading = std::any_of(m_dependencies.cbegin(), m_dependencies.cend(), [] (const auto & dependency) {
					return !dependency->isLoaded();
				});

				if ( stillLoading )
				{
					return;
				}

				if ( Stores::s_operationVerboseEnabled )
				{
					TraceInfo{TracerTag} <<
						"The resource '" << this->name() << "' (" << this->classLabel() << ") "
						"has no more dependency to wait for loading !";
				}

				if ( this->onDependenciesLoaded() )
				{
					m_status = Status::Loaded;

					this->notify(LoadFinished);

					if ( Stores::s_operationVerboseEnabled )
					{
						TraceSuccess{TracerTag} <<
							"Resource '" << this->name() << "' (" << this->classLabel() << ") "
							"is successfully loaded !";
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
						TraceError{TracerTag} <<
							"Resource '" << this->name() << "' (" << this->classLabel() << ") "
							"failed to load !";
					}
				}
			}
				break;

			case Status::Loaded :
				if ( !m_dependencies.empty() )
				{
					TraceError{TracerTag} <<
						"The resource '" << this->name() << "' (" << this->classLabel() << ") status is loaded, "
						"but still have " << m_dependencies.size() << " dependencies.";
				}

				/* NOTE: We don't want to check again dependencies. */
				break;

			case Status::Failed :
				TraceError{TracerTag} <<
					"The resource '" << this->name() << "' (" << this->classLabel() << ") "
					"status is failed !"
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
					"The resource '" << this->name() << "' (" << this->classLabel() << ") "
					"is not in a building stage !"
					"You must call call ResourceTrait::beginLoading() before.";

				return false;

			case Status::Loaded :
				TraceError{TracerTag} <<
					"The resource '" << this->name() << "' (" << this->classLabel() << ") "
					"is already loaded !";

				return false;

			case Status::Failed :
				TraceError{TracerTag} <<
					"The resource '" << this->name() << "' (" << this->classLabel() << ") "
					"has previously failed to load !";

				return false;

			default:
				break;
		}

		if ( status )
		{
			/* Set the resource in loading stage.
			 * NOTE: No more sub-resource enqueuing is possible after this point. */
			m_status = Status::Loading;

			/* We want to check every dependencies status.
			 * NOTE: This will eventually fire up the 'LoadFinished' event. */
			this->checkDependencies();
		}
		else
		{
			m_status = Status::Failed;

			this->notify(LoadFailed);

			TraceError{TracerTag} <<
				"Resource '" << this->name() << "' (" << this << ") "
				"failed to load ...";
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

	ResourceTrait::Status
	ResourceTrait::status () const noexcept
	{
		return m_status;
	}

	bool
	ResourceTrait::load (const Libraries::Path::File & filepath) noexcept
	{
		const auto filepathStr = to_string(filepath);

		const Json::CharReaderBuilder builder{};

		std::ifstream json{filepathStr, std::ifstream::binary};

		Json::Value root{};

		std::string errors{};

		if ( !Json::parseFromStream(builder, json, &root, &errors) )
		{
			TraceError{TracerTag} <<
				"Unable to parse JSON file ! "
				"Errors :" "\n" << errors;

			/* NOTE: Set status here. */
			m_status = Status::Failed;

			this->notify(LoadFailed);

			return false;
		}

		/* Checks if additional stores before loading (optional) */
		Manager::instance()->stores().update(root, filepathStr);

		return this->load(root);
	}

	bool
	ResourceTrait::isTopResource () const noexcept
	{
		return m_parents.empty();
	}

	size_t
	ResourceTrait::dependencyCount () const noexcept
	{
		return m_dependencies.size();
	}

	bool
	ResourceTrait::isUnloaded () const noexcept
	{
		switch ( m_status )
		{
			case Status::Unloaded :
			case Status::Enqueuing :
			case Status::ManualEnqueuing :
				return true;

			default :
				return false;
		}
	}

	bool
	ResourceTrait::isLoading () const noexcept
	{
		return m_status == Status::Loading;
	}

	bool
	ResourceTrait::isLoaded () const noexcept
	{
		return m_status == Status::Loaded;
	}

	void
	ResourceTrait::setDirectLoadingHint () noexcept
	{
		m_directLoad = true;
	}

	bool
	ResourceTrait::isDirectLoading () const noexcept
	{
		return m_directLoad;
	}
}
