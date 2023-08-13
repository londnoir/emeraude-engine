/*
 * Emeraude/Resources/Container.hpp
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
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "Observer.hpp"
#include "Observable.hpp"

/* Local inclusions for usages. */
#include "FileSystem.hpp"
#include "NetworkManager.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"
#include "Stores.hpp"
#include "LoadingRequest.hpp"

namespace Emeraude::Resources
{
	constexpr auto Default = "Default";

	/**
	 * @brief The resource manager template is responsible for loading asynchronously
	 * resources with dependencies and hold their lifetime.
	 * @note Resource type is checked by LoadingRequest template.
	 * @tparam resource_t The real resource of this manager.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Libraries::Observer The manager observer resource loading.
	 */
	template< typename resource_t >
	class Container final : public ServiceInterface, public Libraries::Observer
	{
		public:

			/**
			 * @brief Class identifier.
			 * @note Explicitly declared in each template usage.
			 */
			static const char * const ClassId;

			/**
			 * @brief Observable class unique identifier.
			 * @note Explicitly declared in each template usage.
			 */
			static const size_t ClassUID;

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				Unknown,
				LoadingProcessStarted,
				ResourceLoaded,
				LoadingProcessFinished,
				Progress,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Constructs a resource manager for a specific resource from the template parameter.
			 * @param arguments A reference to the arguments of the application.
			 * @param fileSystem A reference to the service responsible for the file system.
			 * @param coreSettings A reference to the core settings.
			 * @param networkManager A reference to the service responsible for download.
			 * @param resourcesStores A reference to the service responsible of local resource stores.
			 * @param serviceName The name of the service.
			 * @param storeName The name of the resource store.
			 */
			Container (const Arguments & arguments, const FileSystem & fileSystem, Settings & coreSettings, NetworkManager & networkManager, const Stores & resourcesStores, const char * serviceName, const std::string & storeName = "") noexcept
				: ServiceInterface(serviceName),
				m_arguments(arguments),
				m_fileSystem(fileSystem),
				m_coreSettings(coreSettings),
				m_networkManager(networkManager),
				m_resourcesStores(resourcesStores),
				m_storeName(storeName)
			{
				this->observe(&m_networkManager);
			}

			/** @copydoc Libraries::Observable::classId() */
			bool
			is (size_t classUID) const noexcept
			{
				if ( ClassUID == 0UL )
				{
					Tracer::error(ClassId, "The unique class identifier has not been set !");

					return false;
				}

				return classUID == ClassUID;
			}

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool
			usable () const noexcept override
			{
				return true;
			}

			/**
			 * @brief Clean up every unused resources.
			 * @return size_t
			 */
			size_t
			unloadUnusedResources () noexcept
			{
				using namespace Libraries;

				size_t unloadedResources = 0;

				if ( !m_resources.empty() )
				{
					for ( auto it = m_resources.begin(); it != m_resources.end(); )
					{
						TraceDebug{ClassId} << it->second->name() << " used " << it->second.use_count() << " times !";

						if ( it->second.use_count() == 1 )
						{
							unloadedResources++;

							it = m_resources.erase(it);
						}
						else
						{
							++it;
						}
					}

					TraceInfo{ClassId} << unloadedResources << " resource(s) unloaded !";
				}

				return unloadedResources;
			}

			/**
			 * @brief Returns whether a resource is directly usable.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isResourceAvailable (const std::string & resourceName) const noexcept
			{
				return m_resources.contains(resourceName);
			}

			/**
			 * @brief Returns whether a resource exists in loaded resources or in stores.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isResourceExists (const std::string & resourceName) const noexcept
			{
				/* First check in live resources. */
				if ( this->isResourceAvailable(resourceName) )
					return true;

				/* If there is a local store for this resource, we check inside. */
				if ( m_storeName.empty() )
					return false;

				return m_resourcesStores.store(m_storeName).contains(resourceName);
			}

			/**
			 * @brief Creates a new resource.
			 * @param baseInformation A resource information.
			 * @return std::shared_ptr< resource_t >
			 */
			/*
			[[nodiscard]]
			std::shared_ptr< resource_t >
			createResource (const BaseInformation & baseInformation) noexcept
			{
				return this->pushInLoadingQueue(infos);
			}*/

			/**
			 * @brief Creates a new resource.
			 * @note When creating a new resource, put '+' in front of the resource name to prevent it to be overriden from a store resource.
			 * @param resourceName A string with the name of the resource.
			 * @param resourceFlagBits The resource construction flag bits. Default none.
			 * @param enableManualLoading Enable the manual loading control of AbstractChainableLoading class.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			createResource (const std::string & resourceName, uint32_t resourceFlagBits = 0, bool enableManualLoading = false) noexcept
			{
				using namespace Libraries;

				if ( resourceName == Default )
				{
					TraceError{ClassId} << Default << "' as resource name is a reserved key !";

					return nullptr;
				}

				/* First check in store, if the resource exists. */
				if ( !m_storeName.empty() )
				{
					if ( m_resourcesStores.store(m_storeName).contains(resourceName) )
					{
						TraceWarning{ClassId} <<
							resource_t::ClassId << " resource named '" << resourceName << "' already exists in " << m_storeName << " store ! "
							"Use get() function instead.";

						return nullptr;
					}
				}

				/* Checks in loaded resources. */
				{
					auto loadedIt = m_resources.find(resourceName);

					if ( loadedIt != m_resources.cend() )
					{
						TraceWarning{ClassId} <<
							resource_t::ClassId << " resource named '" << resourceName << "' already exists in loaded resources ! "
							"Use get() function instead.";

						return loadedIt->second;
					}
				}

				auto result = m_resources.emplace(resourceName, std::make_shared< resource_t >(resourceName, resourceFlagBits));

				if ( !result.second )
				{
					TraceFatal{ClassId} <<
						"Unable to get " << resource_t::ClassId << " resource named '" << resourceName << "' into the map. "
						"This should never happens !";

					return nullptr;
				}

				/* NOTE: This will change the behavior of loading dependencies. */
				if ( enableManualLoading && !result.first->second->enableManualLoading() )
					return nullptr;

				return result.first->second;
			}

			/**
			 * @brief Adds a resource manually constructed to the store.
			 * @note When creating a new resource, put '+' in front of the resource name to prevent it to be overriden from a store resource.
			 * @param resource The manual resource.
			 * @return bool
			 */
			bool
			addResource (const std::shared_ptr< resource_t > & resource) noexcept
			{
				auto loadedIt = m_resources.find(resource->name());

				if ( loadedIt != m_resources.cend() )
				{
					TraceError{ClassId} << "A resource name '" << resource->name() << "' is already present in the store !";

					return false;
				}

				m_resources.emplace(resource->name(), resource);

				return true;
			}

			/**
			 * @brief Returns the resource by his name. If the resource is unloaded, a thread will take care about it.
			 * @note Returns the default resource if nothing was found and generates a warning.
			 * @param resourceName A string with the name of the resource.
			 * @param directLoad A boolean to block the call of this method until the end of load.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			getResource (const std::string & resourceName, bool directLoad = false) noexcept
			{
				using namespace Libraries;

				if ( resourceName == Default )
					return this->getDefaultResource();

				/* Checks in loaded resources. */
				{
					const auto & loadedIt = m_resources.find(resourceName);

					if ( loadedIt != m_resources.cend() )
						return loadedIt->second;
				}

				if ( m_storeName.empty() )
				{
					TraceWarning{ClassId} <<
						"The resource '" << resourceName << "' doesn't exists and doesn't have a local store ! "
						"Use create() function instead.";

					return this->getDefaultResource();
				}

				/* If not already loaded, check in store for loading. */
				const auto & store = m_resourcesStores.store(m_storeName);

				if ( store.empty() )
				{
					TraceWarning{ClassId} <<
						"The '" << m_storeName << "' store is empty, unable to get '" << resourceName << "' ! "
						"Use create() function instead.";

					return this->getDefaultResource();
				}

				const auto & resourceIt = store.find(resourceName);

				if ( resourceIt == store.cend() )
				{
					/* The resource is definitively not present. */
					TraceWarning{ClassId} <<
						resource_t::ClassId << " resource named '" << resourceName << "' doesn't exist ! "
						"Use create() function instead.";

					return this->getDefaultResource();
				}

				/* Returns the smart pointer to the future loaded resource. */
				return this->pushInLoadingQueue(resourceIt->second, directLoad);
			}

			/**
			 * @brief Preloads a resource for further use.
			 * @param resourceName A string with the name of the resource.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			preloadResource (const std::string & resourceName)
			{
				if ( this->isResourceAvailable(resourceName) )
					return true;

				if ( m_storeName.empty() )
					return false;

				/* If not already loaded, check in store for loading. */
				const auto & store = m_resourcesStores.store(m_storeName);

				if ( store.empty() )
					return false;

				const auto & resourceIt = store.find(resourceName);

				if ( resourceIt == store.cend() )
					return false;

				return this->pushInLoadingQueue(resourceIt->second, false) != nullptr;
			}

			/**
			 * @brief This a shortcut that check before if a resource is available, then returns it or create a new one.
			 * @note When creating a new resource, put '+' in front of the resource name to prevent it to be overriden from a store resource.
			 * @param resourceName A string with the name of the resource.
			 * @param resourceFlagBits The resource construction flag bits. Default none.
			 * @param enableManualLoading Enable the manual loading control of AbstractChainableLoading class. Default false.
			 * @param directLoad A boolean to block the call of this method until the end of load. Default false.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			getOrCreateResource (const std::string & resourceName, uint32_t resourceFlagBits = 0, bool enableManualLoading = false, bool directLoad = false) noexcept
			{
				if ( resourceName == Default )
					return this->getDefaultResource();

				/* Checks in loaded resources. */
				{
					auto loadedIt = m_resources.find(resourceName);

					if ( loadedIt != m_resources.cend() )
						return loadedIt->second;
				}

				/* If not already loaded, check in store for loading. */
				if ( !m_storeName.empty() )
				{
					const auto & store = m_resourcesStores.store(m_storeName);

					if ( !store.empty() )
					{
						auto resourceIt = store.find(resourceName);

						if ( resourceIt != store.cend() )
							return this->pushInLoadingQueue(resourceIt->second, directLoad);
					}
				}

				/* Creates a new one. */
				return this->createResource(resourceName, resourceFlagBits, enableManualLoading);
			}

			/**
			 * @brief Returns the default resource.
			 * @note Should always exists.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			getDefaultResource () noexcept
			{
				/* Checks in loaded resources. */
				{
					const auto & loadedIt = m_resources.find(Default);

					if ( loadedIt != m_resources.cend() )
						return loadedIt->second;
				}

				/* Creates and load the resource. */
				auto defaultResource = new resource_t(Default);

				if ( !defaultResource->load() )
				{
					TraceFatal{ClassId} << "The default resource '" << resource_t::ClassId << "' can't be loaded !";

					return nullptr;
				}

				/* Save the resource in a smart pointer and return it. */
				auto result = m_resources.emplace(
					std::piecewise_construct,
					std::forward_as_tuple(Default),
					std::forward_as_tuple(defaultResource)
				);

				if ( !result.second )
					return nullptr;

				return result.first->second;
			}

			/**
			 * @brief Returns a random resource from this manager.
			 * @param directLoading Set the to direct load the resource. Default false.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			inline
			std::shared_ptr< resource_t >
			getRandomResource (bool directLoading = false) noexcept
			{
				if ( m_storeName.empty() )
					return this->getDefaultResource();
				else
					return this->getResource(m_resourcesStores.randomName(m_storeName), directLoading);
			}

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool
			onInitialize () noexcept override
			{
				if ( Stores::s_operationVerboseEnabled )
				{
					if ( m_storeName.empty() )
					{
						TraceInfo{ClassId} << "The resource type '" << resource_t::ClassId << "' has no local store.";
					}
					else
					{
						const auto & store = m_resourcesStores.store(m_storeName);

						TraceInfo{ClassId} <<
							"The resource type '" << resource_t::ClassId << "' has " << store.size() <<
							" entries in the local store '" << m_storeName << "' available.";
					}
				}

				return true;
			}

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool
			onTerminate () noexcept override
			{
				if ( Stores::s_operationVerboseEnabled )
				{
					if ( m_storeName.empty() )
					{
						TraceInfo{ClassId} <<
							"The resource type '" << resource_t::ClassId << "' has no local store."
							"Nothing to unload.";
					}
					else
					{
						const auto & store = m_resourcesStores.store(m_storeName);

						TraceInfo{ClassId} <<
							"The resource type '" << resource_t::ClassId << "' has " << store.size() <<
							" entries in the local store '" << m_storeName << "' to check for unload.";
					}
				}

				m_externalResources.clear();
				m_resources.clear();

				return true;
			}

			/** @copydoc Libraries::Observer::onNotification() */
			bool
			onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept override
			{
				using namespace Libraries;

				if ( observable->is(NetworkManager::ClassUID) )
				{
					if ( notificationCode == NetworkManager::FileDownloaded )
					{
						const auto downloadTicket = std::any_cast< int >(data);

						auto requestIt = m_externalResources.find(downloadTicket);

						if ( requestIt != m_externalResources.end() )
						{
							switch ( m_networkManager.downloadStatus(downloadTicket) )
							{
								case DownloadItem::Status::Pending :
								case DownloadItem::Status::Transferring :
								case DownloadItem::Status::OnHold :
									return true;

								case DownloadItem::Status::Done :
								{
									Tracer::success(ClassId, "Resource downloaded.");

									requestIt->second.setDownloadProcessed(m_fileSystem, true);

									/* Creates a loading thread. */
									std::thread newTask(&Container< resource_t >::loadingTask, this, requestIt->second);

									newTask.detach();
								}
									break;

								case DownloadItem::Status::Error :
									Tracer::error(ClassId, "Resource failed to download.");

									requestIt->second.setDownloadProcessed(m_fileSystem, true);
									break;
							}

							/* Removes the loading request. */
							m_externalResources.erase(requestIt);
						}
					}

					return true;
				}

				/* We don't know who is sending this message,
				 * so we stop the listening. */
				Tracer::warning(ClassId, "Unknown notification, stop listening to this sender.");

				return false;
			}

			/**
			 * @brief Adds a resource to the loading queue.
			 * @param baseInformation A reference to the base information of the resource to be loaded.
			 * @param directLoad Enable the direct loading of the resource without passing by a thread. This is a blocking operation.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			pushInLoadingQueue (const BaseInformation & baseInformation, bool directLoad) noexcept
			{
				using namespace Libraries;

				const auto & name = baseInformation.name();

				/* 1. Check if resource is not already in loading queue ... */
				const auto & resourceIt = m_resources.find(name);

				if ( resourceIt != m_resources.cend() )
				{
					if ( Stores::s_operationVerboseEnabled )
						TraceInfo{ClassId} << "Resource (" << resource_t::ClassId << ") '" << name << "' is already in the loading queue.";

					return resourceIt->second;
				}

				TraceDebug{ClassId} << "Add resource (" << resource_t::ClassId << ") '" << name << "' to the loading queue.";

				/* Creates a new resource in the loading queue. */
				auto result = m_resources.emplace(
					std::piecewise_construct,
					std::forward_as_tuple(name),
					std::forward_as_tuple(new resource_t(name))
				);

				if ( !result.second )
				{
					TraceError{ClassId} << "Unable to create the resource (" << resource_t::ClassId << ") '" << name << "' !";

					return nullptr;
				}

				/* Gets a reference to the smart pointer of the new resource. */
				auto & newResource = result.first->second;

				LoadingRequest< resource_t > request{baseInformation, newResource};

				if ( directLoad )
				{
					newResource->setDirectLoadingHint();

					/* Call directly the loading function on the manager thread. */
					this->loadingTask(request);
				}
				else
				{
					/* NOTE: Check if we need to download the resource first. */
					if ( baseInformation.sourceType() == SourceType::ExternalData )
					{
						if ( !request.isDownloadable() )
							return nullptr;

						/* NOTE: Check the cache system before downloading. */
						auto cacheFile = request.cacheFilepath(m_fileSystem);

						if ( cacheFile.exists() )
						{
							request.setDownloadProcessed(m_fileSystem, true);
						}
						else
						{
							auto ticket = m_networkManager.download(request.url(), cacheFile, false);

							request.setDownloadTicket(ticket);

							m_externalResources.emplace(ticket, request);
						}
					}
					else
					{
						/* Creates a loading thread. */
						std::thread newTask(&Container< resource_t >::loadingTask, this, request);

						newTask.detach();
					}
				}

				return newResource;
			}

			/**
			 * @brief Task for loading a resource on a thread.
			 * @note The request parameter must be passed by value.
			 * @param request The loading request.
			 */
			void
			loadingTask (LoadingRequest< resource_t > request) noexcept
			{
				using namespace Libraries;

				/* Notify the beginning of a loading process. */
				this->notify(LoadingProcessStarted);

				const auto & infos = request.baseInformation();

				auto success = false;

				/* Load the local resource and send a notification when finished. */
				switch ( infos.sourceType() )
				{
					/* This is a local file, so we load it by using a filepath. */
					case SourceType::LocalData :
						if ( Stores::s_operationVerboseEnabled )
							TraceInfo{ClassId} << "Loading the resource (" << resource_t::ClassId << ") '" << infos.name() << "'... [CONTAINER]";

						success = request.resource()->load(Path::File{infos.data().asString()});
						break;

					/* This is direct data with a JsonCPP way of representing the data. */
					case SourceType::DirectData :
						if ( Stores::s_operationVerboseEnabled )
							TraceInfo{ClassId} << "Loading the resource (" << resource_t::ClassId << ") '" << infos.name() << "'... [CONTAINER]";

						success = request.resource()->load(infos.data());
						break;

					/* This should never happen ! ExternalData must be processed before. */
					case SourceType::ExternalData :
						TraceError{ClassId} << "The resource (" << resource_t::ClassId << ") '" << infos.name() << "' should be downloaded first. Unable to load it ! [CONTAINER]";
						break;

					/* This should never happen ! Undefined is a bug. */
					case SourceType::Undefined :
						TraceError{ClassId} << "The resource (" << resource_t::ClassId << ") '" << infos.name() << "' informations are invalid. Unable to load it ! [CONTAINER]";
						break;
				}

				if ( success )
				{
					TraceSuccess{ClassId} << "The resource (" << resource_t::ClassId << ") '" << infos.name() << "' is loaded. [CONTAINER]";

					this->notify(ResourceLoaded, request.resource().get());
				}
				else
				{
					TraceError{ClassId} << "The resource (" << resource_t::ClassId << ") '" << infos.name() << "' failed to load ! [CONTAINER]";
				}

				/* Notify the end of loading process. */
				this->notify(LoadingProcessFinished);
			}

			const Arguments & m_arguments;
			const FileSystem & m_fileSystem;
			Settings & m_coreSettings;
			NetworkManager & m_networkManager;
			const Stores & m_resourcesStores;
			std::string m_storeName{};
			std::unordered_map< std::string, std::shared_ptr< resource_t > > m_resources{};
			std::unordered_map< int, LoadingRequest< resource_t > > m_externalResources{};
	};
}
