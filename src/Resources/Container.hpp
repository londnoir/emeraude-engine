/*
 * src/Resources/Container.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <any>
#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <utility>

/* Local inclusions for inheritances. */
#include "Libs/ObserverTrait.hpp"
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "Libs/ObservableTrait.hpp"
#include "Libs/IO/IO.hpp"
#include "BaseInformation.hpp"
#include "DownloadItem.hpp"
#include "PrimaryServices.hpp"
#include "LoadingRequest.hpp"
#include "NetworkManager.hpp"
#include "Stores.hpp"
#include "Types.hpp"

namespace EmEn::Resources
{
	/**
	 * @brief The resource manager template is responsible for loading asynchronously resources with dependencies and hold their lifetime.
	 * @tparam resource_t The type of resources (The resource type is checked by LoadingRequest template).
	 * @extends EmEn::ServiceInterface This is a service.
	 * @extends EmEn::Libs::ObserverTrait The manager observer resource loading.
	 */
	template< typename resource_t >
	class Container final : public ServiceInterface, public Libs::ObserverTrait
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
			 * @param primaryServices A reference to the primary services.
			 * @param networkManager A reference to the service responsible for download.
			 * @param resourcesStores A reference to the service responsible for local resource stores.
			 * @param serviceName The name of the service.
			 * @param storeName The name of the resource store.
			 */
			Container (PrimaryServices & primaryServices, NetworkManager & networkManager, const Stores & resourcesStores, const char * serviceName, std::string storeName = "") noexcept
				: ServiceInterface(serviceName),
				m_primaryServices(primaryServices),
				m_networkManager(networkManager),
				m_resourcesStores(resourcesStores),
				m_storeName(std::move(storeName))
			{
				this->observe(&m_networkManager);
			}

			/** @copydoc EmEn::Libs::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc EmEn::Libs::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				if ( ClassUID == 0UL )
				{
					Tracer::error(resource_t::ClassId, "The unique class identifier has not been set !");

					return false;
				}

				return classUID == ClassUID;
			}

			/** @copydoc EmEn::ServiceInterface::usable() */
			[[nodiscard]]
			bool
			usable () const noexcept override
			{
				return m_flags[ServiceInitialized];
			}

			/**
			 * @brief Clean up every unused resources.
			 * @return size_t
			 */
			size_t
			unloadUnusedResources () noexcept
			{
				using namespace EmEn::Libs;

				size_t unloadedResources = 0;

				if ( !m_resources.empty() )
				{
					for ( auto it = m_resources.begin(); it != m_resources.end(); )
					{
						const auto links = it->second.use_count();

						if ( links > 1 )
						{
							TraceDebug{resource_t::ClassId} << it->second->name() << " is still used " << links << " times !";
						}

						if ( links == 1 )
						{
							unloadedResources++;

							/* FIXME: Fails with some animated 2d textures. */
							it = m_resources.erase(it);
						}
						else
						{
							++it;
						}
					}

					TraceInfo{resource_t::ClassId} << unloadedResources << " resource(s) unloaded !";
				}

				return unloadedResources;
			}

			/**
			 * @brief Returns whether a resource is loaded and ready to use.
			 * @param resourceName A reference to a string.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isResourceLoaded (const std::string & resourceName) const noexcept
			{
				return m_resources.contains(resourceName);
			}

			/**
			 * @brief Returns whether a resource exists.
			 * First the container will check in loaded resources, then in available (unloaded) resources in the store.
			 * @param resourceName A reference to a string.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isResourceExists (const std::string & resourceName) const noexcept
			{
				/* First check in live resources. */
				if ( this->isResourceLoaded(resourceName) )
				{
					return true;
				}

				/* If there is a local store for this resource, we check inside. */
				if ( m_storeName.empty() )
				{
					return false;
				}

				return m_resourcesStores.store(m_storeName).contains(resourceName);
			}

			/**
			 * @brief Creates a new resource.
			 * @note When creating a new resource, put '+' in front of the resource name to prevent it to be overridden from a store resource.
			 * @param resourceName A string with the name of the resource.
			 * @param resourceFlagBits The resource construction flag bits. Default none.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			createResource (const std::string & resourceName, uint32_t resourceFlagBits = 0) noexcept
			{
				using namespace EmEn::Libs;

				if ( resourceName == Default )
				{
					TraceError{resource_t::ClassId} << Default << "' as resource name is a reserved key !";

					return nullptr;
				}

				/* First check in store, if the resource exists. */
				if ( !m_storeName.empty() )
				{
					if ( m_resourcesStores.store(m_storeName).contains(resourceName) )
					{
						TraceWarning{resource_t::ClassId} <<
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
						TraceWarning{resource_t::ClassId} <<
							resource_t::ClassId << " resource named '" << resourceName << "' already exists in loaded resources ! "
							"Use getResource() function instead.";

						return loadedIt->second;
					}
				}

				auto result = m_resources.emplace(resourceName, std::make_shared< resource_t >(resourceName, resourceFlagBits));

				if ( !result.second )
				{
					TraceFatal{resource_t::ClassId} <<
						"Unable to get " << resource_t::ClassId << " resource named '" << resourceName << "' into the map. "
						"This should never happens !";

					return nullptr;
				}

				return result.first->second;
			}

			/**
			 * @brief Adds a resource manually constructed to the store.
			 * @note When creating a new resource, put '+' in front of the resource name to prevent it to be overridden from a store resource.
			 * @param resource The manual resource.
			 * @return bool
			 */
			bool
			addResource (const std::shared_ptr< resource_t > & resource) noexcept
			{
				auto loadedIt = m_resources.find(resource->name());

				if ( loadedIt != m_resources.cend() )
				{
					TraceError{resource_t::ClassId} << "A resource name '" << resource->name() << "' is already present in the store !";

					return false;
				}

				m_resources.emplace(resource->name(), resource);

				return true;
			}

			/**
			 * @brief Preloads asynchronously a resource.
			 * @param resourceName A string with the name of the resource.
			 * @param asyncLoad Load the resource asynchronously. Default true.
			 * @return bool
			 */
			bool
			preloadResource (const std::string & resourceName, bool asyncLoad = true)
			{
				if ( this->isResourceLoaded(resourceName) )
				{
					return true;
				}

				if ( m_storeName.empty() )
				{
					return false;
				}

				/* If not already loaded, check in store for loading. */
				const auto & store = m_resourcesStores.store(m_storeName);

				if ( store.empty() )
				{
					return false;
				}

				const auto & resourceIt = store.find(resourceName);

				if ( resourceIt == store.cend() )
				{
					return false;
				}

				return this->pushInLoadingQueue(resourceIt->second, asyncLoad) != nullptr;
			}

			/**
			 * @brief Returns a resource by its name. If the resource is unloaded, a thread will take care about it unless "asyncLoad" argument is set to "false".
			 * @note The default resource of the store will be returned if nothing was found. A warning trace will be generated.
			 * @param resourceName A reference to a string for the resource name.
			 * @param asyncLoad Load the resource asynchronously. Default true.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			getResource (const std::string & resourceName, bool asyncLoad = true) noexcept
			{
				if ( resourceName == Default )
				{
					return this->getDefaultResource();
				}

				/* Checks in loaded resources. */
				{
					const auto & loadedIt = m_resources.find(resourceName);

					if ( loadedIt != m_resources.cend() )
					{
						return loadedIt->second;
					}
				}

				if ( m_storeName.empty() )
				{
					TraceWarning{resource_t::ClassId} <<
						"The resource '" << resourceName << "' doesn't exists and doesn't have a local store ! "
						"Use Resource::create() function instead.";

					return this->getDefaultResource();
				}

				/* If not already loaded, check in store for loading. */
				const auto & store = m_resourcesStores.store(m_storeName);

				if ( store.empty() )
				{
					TraceWarning{resource_t::ClassId} <<
						"The '" << m_storeName << "' store is empty, unable to get '" << resourceName << "' ! "
						"Use Resource::create() function instead.";

					return this->getDefaultResource();
				}

				const auto & resourceIt = store.find(resourceName);

				if ( resourceIt == store.cend() )
				{
					/* The resource is definitively not present. */
					TraceWarning{resource_t::ClassId} <<
						"The resource named '" << resourceName << "' doesn't exist ! "
						"Use Resource::create() function instead.";

					return this->getDefaultResource();
				}

				/* Returns the smart pointer to the future loaded resource. */
				return this->pushInLoadingQueue(resourceIt->second, asyncLoad);
			}

			/**
			 * @brief Returns an existing resource or a new empty one.
			 * @param resourceName A string with the name of the resource.
			 * @param resourceFlagBits The resource construction flag bits. Default none.
			 * @param asyncLoad Load the resource asynchronously. Default true.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			getOrNewResource (const std::string & resourceName, uint32_t resourceFlagBits = 0, bool asyncLoad = true) noexcept
			{
				const auto alreadyLoadedResource = this->checkLoadedResource(resourceName, asyncLoad);

				return alreadyLoadedResource != nullptr ? alreadyLoadedResource : this->createResource(resourceName, resourceFlagBits);
			}

			/**
			 * @brief Returns an existing resource or use a method to create a new one.
			 * @param resourceName A string with the name of the resource.
			 * @param createFunction A reference to a function to create the existent resource.
			 * @param resourceFlagBits The resource construction flag bits. Default none.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			getOrCreateResource (const std::string & resourceName, const std::function< bool (resource_t & resource) > & createFunction, uint32_t resourceFlagBits = 0) noexcept
			{
				const auto alreadyLoadedResource = this->checkLoadedResource(resourceName, false);

				if ( alreadyLoadedResource != nullptr )
				{
					return alreadyLoadedResource;
				}

				/* Creates a new resource. */
				const auto newResource = this->createResource(resourceName, resourceFlagBits);

				/* Already defines that the resource is in manual loading mode. */
				if ( !newResource->enableManualLoading() )
				{
					return nullptr;
				}

				if ( !createFunction(*newResource) )
				{
					TraceError{resource_t::ClassId} << "The manual loading function has return an error !";

					return nullptr;
				}

				switch ( newResource->status() )
				{
					case Status::Unloaded :
					case Status::Enqueuing :
					case Status::ManualEnqueuing :
						TraceError{resource_t::ClassId} <<
							"The manual resource '" << resourceName << " is still in creation mode !"
							"A manual loading should ends with a call to ResourceTrait::setManualLoadSuccess() or ResourceTrait::load().";

						return nullptr;

					case Status::Failed :
						return nullptr;

					default :
						return newResource;
				}
			}

			/**
			 * @brief Returns an existing resource or use a method to create a new one asynchronously.
			 * @param resourceName A string with the name of the resource.
			 * @param createFunction A reference to a function to create the existent resource.
			 * @param resourceFlagBits The resource construction flag bits. Default none.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			getOrCreateResourceAsync (const std::string & resourceName, const std::function< bool (resource_t & resource) > & createFunction, uint32_t resourceFlagBits = 0) noexcept
			{
				const auto alreadyLoadedResource = this->checkLoadedResource(resourceName, true);

				if ( alreadyLoadedResource != nullptr )
				{
					return alreadyLoadedResource;
				}

				/* Creates a new resource. */
				const auto newResource = this->createResource(resourceName, resourceFlagBits);

				/* Already defines that the resource is in manual loading mode. */
				if ( !newResource->enableManualLoading() )
				{
					return nullptr;
				}

				std::thread generation{[] (const std::function< bool (resource_t & resource) > & createResource, const std::shared_ptr< resource_t > & resource) {
					if ( createResource(*resource) )
					{
						switch ( resource->status() )
						{
							case Status::Unloaded :
							case Status::Enqueuing :
							case Status::ManualEnqueuing :
								TraceError{resource_t::ClassId} <<
									"The manual resource '" << resource->name() << " is still in creation mode !"
									"A manual loading should ends with a call to ResourceTrait::setManualLoadSuccess() or ResourceTrait::load().";
								break;

							default :
								break;
						}
					}
					else
					{
						TraceError{resource_t::ClassId} << "The manual loading function has return an error !";
					}
				}, createFunction, newResource};

				generation.detach();

				return newResource;
			}

			/**
			 * @brief Returns the default resource.
			 * @note Should always exist.
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
					{
						return loadedIt->second;
					}
				}

				/* Creates and load the resource. */
				auto defaultResource = std::make_shared< resource_t >(Default);

				if ( !defaultResource->load() )
				{
					TraceFatal{resource_t::ClassId} << "The default resource '" << resource_t::ClassId << "' can't be loaded !";

					return nullptr;
				}

				/* Save the resource in a smart pointer and return it. */
				auto result = m_resources.emplace(
					std::piecewise_construct,
					std::forward_as_tuple(Default),
					std::forward_as_tuple(defaultResource)
				);

				if ( !result.second )
				{
					return nullptr;
				}

				return defaultResource;
			}

			/**
			 * @brief Returns a random resource from this manager.
			 * @param asyncLoad Load the resource asynchronously. Default true.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			getRandomResource (bool asyncLoad = true) noexcept
			{
				if ( m_storeName.empty() )
				{
					return this->getDefaultResource();
				}

				return this->getResource(m_resourcesStores.randomName(m_storeName), asyncLoad);
			}

		private:

			/** @copydoc EmEn::ServiceInterface::onInitialize() */
			bool
			onInitialize () noexcept override
			{
				if ( Stores::s_operationVerboseEnabled )
				{
					if ( m_storeName.empty() )
					{
						TraceInfo{resource_t::ClassId} << "The resource type '" << resource_t::ClassId << "' has no local store.";
					}
					else
					{
						const auto & store = m_resourcesStores.store(m_storeName);

						TraceInfo{resource_t::ClassId} <<
							"The resource type '" << resource_t::ClassId << "' has " << store.size() <<
							" entries in the local store '" << m_storeName << "' available.";
					}
				}

				m_flags[ServiceInitialized] = true;

				return true;
			}

			/** @copydoc EmEn::ServiceInterface::onTerminate() */
			bool
			onTerminate () noexcept override
			{
				m_flags[ServiceInitialized] = false;

				if ( Stores::s_operationVerboseEnabled )
				{
					if ( m_storeName.empty() )
					{
						TraceInfo{resource_t::ClassId} <<
							"The resource type '" << resource_t::ClassId << "' has no local store."
							"Nothing to unload.";
					}
					else
					{
						const auto & store = m_resourcesStores.store(m_storeName);

						TraceInfo{resource_t::ClassId} <<
							"The resource type '" << resource_t::ClassId << "' has " << store.size() <<
							" entries in the local store '" << m_storeName << "' to check for unload.";
					}
				}

				m_externalResources.clear();
				m_resources.clear();

				return true;
			}

			/** @copydoc EmEn::Libs::ObserverTrait::onNotification() */
			bool
			onNotification (const Libs::ObservableTrait * observable, int notificationCode, const std::any & data) noexcept override
			{
				using namespace EmEn::Libs;

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
									Tracer::success(resource_t::ClassId, "Resource downloaded.");

									requestIt->second.setDownloadProcessed(m_primaryServices.fileSystem(), true);

									/* Creates a loading thread. */
									std::thread newTask(&Container::loadingTask, this, requestIt->second);

									newTask.detach();
								}
									break;

								case DownloadItem::Status::Error :
									Tracer::error(resource_t::ClassId, "Resource failed to download.");

									requestIt->second.setDownloadProcessed(m_primaryServices.fileSystem(), true);
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
				Tracer::warning(resource_t::ClassId, "Unknown notification, stop listening to this sender.");

				return false;
			}

			/**
			 * @brief Checks for a previously loaded resource and return it.
			 * @param resourceName A reference to a string.
			 * @param asyncLoad Load the resource asynchronously.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			checkLoadedResource (const std::string & resourceName, bool asyncLoad) noexcept
			{
				if ( resourceName == Default )
				{
					return this->getDefaultResource();
				}

				/* Checks in loaded resources. */
				const auto & loadedIt = m_resources.find(resourceName);

				if ( loadedIt != m_resources.cend() )
				{
					return loadedIt->second;
				}

				/* If not already loaded, check in store for loading. */
				if ( !m_storeName.empty() )
				{
					const auto & store = m_resourcesStores.store(m_storeName);

					if ( !store.empty() )
					{
						const auto resourceIt = store.find(resourceName);

						if ( resourceIt != store.cend() )
						{
							return this->pushInLoadingQueue(resourceIt->second, !asyncLoad);
						}
					}
				}

				return nullptr;
			}

			/**
			 * @brief Adds a resource to the loading queue.
			 * @param baseInformation A reference to the base information of the resource to be loaded.
			 * @param asyncLoad Load the resource asynchronously.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			pushInLoadingQueue (const BaseInformation & baseInformation, bool asyncLoad) noexcept
			{
				using namespace EmEn::Libs;

				const auto & name = baseInformation.name();

				/* 1. Check if resource is not already in loading queue ... */
				const auto & resourceIt = m_resources.find(name);

				if ( resourceIt != m_resources.cend() )
				{
					if ( Stores::s_operationVerboseEnabled )
					{
						TraceInfo{resource_t::ClassId} << "Resource (" << resource_t::ClassId << ") '" << name << "' is already in the loading queue.";
					}

					return resourceIt->second;
				}

				/* Creates a new resource in the loading queue. */
				auto result = m_resources.emplace(
					std::piecewise_construct,
					std::forward_as_tuple(name),
					std::forward_as_tuple(new resource_t(name))
				);

				if ( !result.second )
				{
					TraceError{resource_t::ClassId} << "Unable to create the resource (" << resource_t::ClassId << ") '" << name << "' !";

					return nullptr;
				}

				/* Gets a reference to the smart pointer of the new resource. */
				auto & newResource = result.first->second;

				LoadingRequest< resource_t > request{baseInformation, newResource};

				if ( asyncLoad )
				{
					/* NOTE: Check if we need to download the resource first. */
					if ( baseInformation.sourceType() == SourceType::ExternalData )
					{
						if ( !request.isDownloadable() )
						{
							return nullptr;
						}

						/* NOTE: Check the cache system before downloading. */
						const auto cacheFile = request.cacheFilepath(m_primaryServices.fileSystem());

						if ( IO::fileExists(cacheFile) )
						{
							request.setDownloadProcessed(m_primaryServices.fileSystem(), true);
						}
						else
						{
							const auto ticket = m_networkManager.download(request.url(), cacheFile, false);

							request.setDownloadTicket(ticket);

							m_externalResources.emplace(ticket, request);
						}
					}
					else
					{
						/* Create a thread for the resource loading. */
						std::thread newTask(&Container::loadingTask, this, request);

						newTask.detach();
					}
				}
				else
				{
					newResource->setDirectLoadingHint();

					/* Call directly the loading function on the manager thread. */
					this->loadingTask(request);
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
				using namespace EmEn::Libs;

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
						{
							TraceInfo{resource_t::ClassId} << "Loading the resource (" << resource_t::ClassId << ") '" << infos.name() << "'... [CONTAINER]";
						}

						success = request.resource()->load(std::filesystem::path{infos.data().asString()});
						break;

					/* This is direct data with a JsonCPP way of representing the data. */
					case SourceType::DirectData :
						if ( Stores::s_operationVerboseEnabled )
						{
							TraceInfo{resource_t::ClassId} << "Loading the resource (" << resource_t::ClassId << ") '" << infos.name() << "'... [CONTAINER]";
						}

						success = request.resource()->load(infos.data());
						break;

					/* This should never happen ! ExternalData must be processed before. */
					case SourceType::ExternalData :
						TraceError{resource_t::ClassId} << "The resource (" << resource_t::ClassId << ") '" << infos.name() << "' should be downloaded first. Unable to load it ! [CONTAINER]";
						break;

					/* This should never happen ! Undefined is a bug. */
					case SourceType::Undefined :
					default:
						TraceError{resource_t::ClassId} << "The resource (" << resource_t::ClassId << ") '" << infos.name() << "' information are invalid. Unable to load it ! [CONTAINER]";
						break;
				}

				if ( success )
				{
					if ( Stores::s_operationVerboseEnabled )
					{
						TraceSuccess{resource_t::ClassId} << "The resource (" << resource_t::ClassId << ") '" << infos.name() << "' is loaded. [CONTAINER]";
					}

					this->notify(ResourceLoaded, request.resource().get());
				}
				else
				{
					TraceError{resource_t::ClassId} << "The resource (" << resource_t::ClassId << ") '" << infos.name() << "' failed to load ! [CONTAINER]";
				}

				/* Notify the end of loading process. */
				this->notify(LoadingProcessFinished);
			}

			/* Flag names. */
			static constexpr auto ServiceInitialized{0UL};

			PrimaryServices & m_primaryServices;
			NetworkManager & m_networkManager;
			const Stores & m_resourcesStores;
			std::string m_storeName;
			std::unordered_map< std::string, std::shared_ptr< resource_t > > m_resources;
			std::unordered_map< int, LoadingRequest< resource_t > > m_externalResources;
			std::array< bool, 8 > m_flags{
				false/*ServiceInitialized*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
