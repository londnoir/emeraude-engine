/*
 * Emeraude/Audio/Source.hpp
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
#include <map>
#include <sstream>
#include <string>

/* Local inclusions */
#include "Math/Vector.hpp"
#include "AbstractObject.hpp"
#include "EffectSlot.hpp"

namespace Emeraude::Audio
{
	// NOLINTBEGIN(readability-identifier-length)
	class PlayableInterface;

	/**
	 * @brief The Source class
	 * @extends Emeraude::Audio::AbstractObject
	 */
	class Source final : public AbstractObject
	{
		public:

			/** @brief The play mode enumerations. */
			enum class PlayMode
			{
				Once,
				Loop
			};

			/** @brief The source type enumerations. */
			enum class SourceType
			{
				Undetermined,
				Static,
				Streaming
			};

			static constexpr auto ClassId{"AudioSource"};

			/**
			 * @brief Constructs an audio source.
			 */
			Source () noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Source (const Source & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Source (Source && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Source & operator= (const Source & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Source & operator= (Source && copy) noexcept = default;

			/**
			 * @brief Destructs the audio source.
			 */
			~Source () override;

			/** @copydoc Emeraude::Engine::Audio::AbstractObject::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept override;

			/**
			 * @brief Sets the source position.
			 * @param position A reference to a vector.
			 */
			void setPosition (const Libraries::Math::Vector< 3, float > & position) noexcept;

			/**
			 * @brief Sets the source position.
			 * @param position A reference to a vector.
			 */
			void setPosition (const Libraries::Math::Vector< 4, float > & position) noexcept;

			/**
			 * @brief Sets the source position.
			 * @param x The X-axis position value.
			 * @param y The Y-axis position value.
			 * @param z The Z-axis position value.
			 */
			void setPosition (float x, float y, float z) noexcept;

			/**
			 * @brief Returns the source position.
			 * @return Libraries::Math::Vector< 3, float >
			 */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > position () const noexcept;

			/**
			 * @brief Sets the direction of the sound emission source.
			 * @param direction A reference to a vector.
			 */
			void setDirection (const Libraries::Math::Vector< 3, float > & direction) noexcept;

			/**
			 * @brief Sets the direction of the sound emission source.
			 * @param direction A reference to a vector.
			 */
			void setDirection (const  Libraries::Math::Vector< 4, float > & direction) noexcept;

			/**
			 * @brief Sets the direction of the sound emission source.
			 * @param x The X-axis direction value.
			 * @param y The Y-axis direction value.
			 * @param z The Z-axis direction value.
			 */
			void setDirection (float x, float y, float z) noexcept;

			/**
			 * @brief Returns the source direction.
			 * @return Libraries::Math::Vector< 3, float >
			 */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > direction () const noexcept;

			/**
			 * @brief Sets the source velocity to simulate doppler effect.
			 * @param velocity A reference to a vector.
			 */
			void setVelocity (const Libraries::Math::Vector< 3, float > & velocity) noexcept;

			/**
			 * @brief Sets the source velocity to simulate doppler effect.
			 * @param velocity A reference to a vector.
			 */
			void setVelocity (const Libraries::Math::Vector< 4, float > & velocity) noexcept;

			/**
			 * @brief Sets the source velocity to simulate doppler effect.
			 * @param x The X-axis velocity value.
			 * @param y The Y-axis velocity value.
			 * @param z The Z-axis velocity value.
			 */
			void setVelocity (float x, float y, float z) noexcept;

			/**
			 * @brief Returns the source velocity.
			 * @return Libraries::Math::Vector< 3, float >
			 */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > velocity () const noexcept;

			/**
			 * @brief Sets the source gain.
			 * @param gain A float from 0.0 to INF+.
			 */
			void setGain (float gain) noexcept;

			/**
			 * @brief Returns the source gain.
			 * @return float
			 */
			[[nodiscard]]
			float gain () const noexcept;

			/**
			 * @brief Sets a minimal and a maximal possible gain for this source.
			 * @param minGain A minimum value.
			 * @param maxGain A maximum value.
			 */
			void boundsGain (float minGain, float maxGain) noexcept;

			/**
			 * @brief Returns the minimal gain allowed by this source.
			 * @return float
			 */
			[[nodiscard]]
			float minimumGain () const noexcept;

			/**
			 * @brief Returns the maximal gain allowed by this source.
			 * @return float
			 */
			[[nodiscard]]
			float maximumGain () const noexcept;

			/**
			 * @brief Sets how far the sound will execute to drop.
			 * @param distance A distance in the world units.
			 */
			void setReferenceDistance (float distance) noexcept;

			/**
			 * @brief Returns how far the sound will execute to drop.
			 * @return float
			 */
			[[nodiscard]]
			float referenceDistance () const noexcept;

			/**
			 * @brief Sets how quickly (higher number) the sound will lower or not.
			 * @param factor A value bigger than 0.0. The initial value is 1.0.
			 */
			void setRolloffFactor (float factor) noexcept;

			/**
			 * @brief Returns how quickly (higher number) the sound will lower or not.
			 * @return float
			 */
			[[nodiscard]]
			float rolloffFactor () const noexcept;

			/**
			 * @brief Sets the maximum distance after which the sound will no longer be heard.
			 * @param distance A distance in the world units.
			 */
			void setMaxDistance (float distance) noexcept;

			/**
			 * @brief Returns the maximum distance after which the sound will no longer be heard.
			 * @return float
			 */
			[[nodiscard]]
			float maxDistance () const noexcept;

			/**
			 * @brief Higher method to set the attenuation parameters of the source.
			 * @param rolloffFactor Set how quickly (higher number) the sound will lower or not. Default is 1.0F.
			 * @param referenceDistance Set from what distance the sound will execute to be lowered.
			 * @param maxDistance Set the distance after which the sound will no longer be heard.
			 */
			inline
			void
			setAttenuationParameters (float rolloffFactor, float referenceDistance, float maxDistance) noexcept
			{
				this->setRolloffFactor(rolloffFactor);

				this->setReferenceDistance(referenceDistance);

				this->setMaxDistance(maxDistance);
			}

			/**
			 * @brief Sets properties of emission cone.
			 * @warning The parameter "gainFacingAway" is only available with EFX extension.
			 * @param innerAngle The inner angle of the cone where the sound is louder.
			 * @param outerAngle The outer angle of the cone where the sound is fading.
			 * @param outerGain The attenuation gain outside the gain.
			 * @param gainFacingAway The attenuation gain when facing away the cone.
			 */
			void setCone (float innerAngle, float outerAngle, float outerGain, float gainFacingAway) noexcept;

			/**
			 * @brief Returns the cone inner angle.
			 * @return float
			 */
			[[nodiscard]]
			float coneInnerAngle () const noexcept;

			/**
			 * @brief Returns the cone outer angle.
			 * @return float
			 */
			[[nodiscard]]
			float coneOuterAngle () const noexcept;

			/**
			 * @brief Returns the cone gain outside.
			 * @return float
			 */
			[[nodiscard]]
			float coneOuterGain () const noexcept;

			/**
			 * @brief Returns the cone gain when facing away.
			 * @return float
			 */
			[[nodiscard]]
			float coneGainFacingAway () const noexcept;

			/**
			 * @brief Sets the sound pitch.
			 * @param pitch The value of the pitch to apply to the sound.
			 */
			void setPitch (float pitch) noexcept;

			/**
			 * @brief Returns the sound pitch value.
			 * @return float
			 */
			[[nodiscard]]
			float pitch () const noexcept;

			/**
			 * @brief Sets the air absorption property.
			 * @warning This method only works with the EFX extension.
			 * @param factor The attenuation factor from air absorption.
			 */
			void setAirAbsorption (int factor) noexcept;

			/**
			 * @brief Returns the air absorption property.
			 * @return int
			 */
			[[nodiscard]]
			int airAbsorption () const noexcept;

			/**
			 * @brief Sets a random pitch value.
			 * @param minPitch The minimal value for the pitch.
			 * @param maxPitch The maximum value for the pitch.
			 * @return float The selected pitch value.
			 */
			float setRandomPitch (float minPitch, float maxPitch) noexcept;

			/**
			 * @brief Sets the mute state.
			 * @param state The state.
			 */
			void setMuteState (bool state) noexcept;

			/**
			 * @brief Toggles the mute state.
			 * @return bool
			 */
			bool toggleMuteState () noexcept;

			/**
			 * @brief Sets the relative state to the listener.
			 * @param state The state.
			 */
			void setRelativeState (bool state) noexcept;

			/**
			 * @brief Returns whether is the source is muted or not (gain=0.0).
			 * @return bool
			 */
			[[nodiscard]]
			bool isMuted () const noexcept;

			/**
			 * @brief Returns whether is the source is playing or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool isPlaying () const noexcept;

			/**
			 * @brief Returns whether is the source is paused or not.
			 * @note This state keep the sound reading cursor.
			 * @return bool
			 */
			[[nodiscard]]
			bool isPaused () const noexcept;

			/**
			 * @brief Returns whether is the source is stopped or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool isStopped () const noexcept;

			/**
			 * @brief Returns whether the loop mode is enabled or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool isLooping () const noexcept;

			/**
			 * @brief isRelative
			 * @return
			 */
			[[nodiscard]]
			bool isRelative () const noexcept;

			/**
			 * @brief Adds an effect on the source.
			 * @warning This method only works with the EFX extension.
			 * @param effect A reference to a effect smart pointer.
			 * @param channel The index of the slot. Default 0.
			 * @return bool
			 */
			bool addEffect (const std::shared_ptr< Effects::Abstract > & effect, int channel = 0) noexcept;

			/**
			 * @brief Adds a filter on the source.
			 * @warning This method only works with the EFX extension.
			 * @param filter A reference to a filter smart pointer.
			 * @param channel The index of the slot. Default 0.
			 * @return bool
			 */
			bool addEffect (const std::shared_ptr< Filters::Abstract > & filter, int channel = 0) noexcept;

			/**
			 * @brief Adds effects and a filter on the source.
			 * @warning This method only works with the EFX extension.
			 * @param effect A reference to a effect smart pointer.
			 * @param filter A reference to a filter smart pointer.
			 * @param channel The index of the slot. Default 0.
			 * @return bool
			 */
			bool addEffect (const std::shared_ptr< Effects::Abstract > & effect, const std::shared_ptr< Filters::Abstract > & filter, int channel = 0) noexcept;

			/**
			 * @brief Enables an effect/filter slot.
			 * @warning This method only works with the EFX extension.
			 * @param channel
			 */
			void enableEffectSlot (int channel) const noexcept;

			/**
			 * @brief Disables an effect/filter slot.
			 * @warning This method only works with the EFX extension.
			 * @param channel
			 */
			void disableEffectSlot (int channel) const noexcept;

			/**
			 * @brief Enables a direct filter.
			 * @warning This method only works with the EFX extension.
			 * @param filter A reference to a filter smart pointer.
			 * @return bool
			 */
			bool enableDirectFilter (const std::shared_ptr< Filters::Abstract > & filter) noexcept;

			/**
			 * @brief Disables the direct filter.
			 * @warning This method only works with the EFX extension.
			 */
			void disableDirectFilter () noexcept;

			/**
			 * @brief Plays a sound or a music (streamed) to the source.
			 * @note If something is playing or paused. It will be stopped and/or removed.
			 * @param sample
			 * @param mode
			 */
			bool play (const PlayableInterface * sample, PlayMode mode = PlayMode::Once) noexcept;

			/** @brief Pauses the source only if it's playing. */
			void pause () noexcept;

			/** @brief Resumes a previously paused source. */
			void resume () noexcept;

			/** @brief Gets the playback cursor at the beginning. */
			void rewind () noexcept;

			/** @brief Stops the audio source. */
			void stop () noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Source & obj);

			/**
			 * @brief Stringify the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const Source & obj) noexcept;

		private:

			/**
			 * @brief setFloatValue
			 * @param pName
			 * @param value
			 */
			void setFloatValue (ALenum pName, ALfloat value) noexcept;

			/**
			 * @brief getFloatValue
			 * @param pName
			 * @param defaultValue
			 * @return ALfloat
			 */
			[[nodiscard]]
			ALfloat getFloatValue (ALenum pName, ALfloat defaultValue = 0.0F) const noexcept;

			/**
			 * @brief setIntValue
			 * @param pName
			 * @param value
			 */
			void setIntValue (ALenum pName, ALint value) noexcept;

			/**
			 * @brief getIntValue
			 * @param pName
			 * @param defaultValue
			 * @return ALint
			 */
			[[nodiscard]]
			ALint getIntValue (ALenum pName, ALint defaultValue = 0) const noexcept;

			/** @brief Clears streaming queue. */
			void clearStream () noexcept;

			/**
			 * @brief prepareEffectSlot
			 * @warning This method only works with the EFX extension.
			 * @param channel
			 * @return bool
			 */
			bool prepareEffectSlot (int channel) noexcept;

			/**
			 * @brief getBuffersQueuedCount
			 * @return int
			 */
			[[nodiscard]]
			int getBuffersQueuedCount () const noexcept;

			/**
			 * @brief getBuffersProcessedCount
			 * @return int
			 */
			[[nodiscard]]
			int getBuffersProcessedCount () const noexcept;

			/**
			 * @brief Returns the source type.
			 * @return SourceType
			 */
			[[nodiscard]]
			SourceType getSourceType () const noexcept;

			std::map< int, std::shared_ptr< EffectSlot > > m_effectSlots{};
			std::shared_ptr< const Filters::Abstract > m_directFilter{};
			float m_previousGain = 1.0F;
	};
	// NOLINTEND(readability-identifier-length)
}
