/*
 * Emeraude/Audio/OpenAL.EFX.hpp
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
#include <memory>

/* Third-party libraries */
#include "Third-Party-Inclusion/openal.hpp"

namespace Emeraude::Audio
{
	// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
	/**
	 * @brief The EFX class
	 */
	class EFX final
	{
		public:

			/* Effect objects */
			static LPALGENEFFECTS alGenEffects;
			static LPALDELETEEFFECTS alDeleteEffects;
			static LPALISEFFECT alIsEffect;
			static LPALEFFECTI alEffecti;
			static LPALEFFECTIV alEffectiv;
			static LPALEFFECTF alEffectf;
			static LPALEFFECTFV alEffectfv;
			static LPALGETEFFECTI alGetEffecti;
			static LPALGETEFFECTIV alGetEffectiv;
			static LPALGETEFFECTF alGetEffectf;
			static LPALGETEFFECTFV alGetEffectfv;

			/* Filter objects */
			static LPALGENFILTERS alGenFilters;
			static LPALDELETEFILTERS alDeleteFilters;
			static LPALISFILTER alIsFilter;
			static LPALFILTERI alFilteri;
			static LPALFILTERIV alFilteriv;
			static LPALFILTERF alFilterf;
			static LPALFILTERFV alFilterfv;
			static LPALGETFILTERI alGetFilteri;
			static LPALGETFILTERIV alGetFilteriv;
			static LPALGETFILTERF alGetFilterf;
			static LPALGETFILTERFV alGetFilterfv;

			/* Auxiliary slot object */
			static LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
			static LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
			static LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
			static LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
			static LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
			static LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
			static LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
			static LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
			static LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
			static LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
			static LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;

			/**
			 * @brief Constructs the OpenAL EFX extension check.
			 * @param device A pointer to the device.
			 */
			explicit EFX (ALCdevice * device) noexcept;

			/**
			 * @brief Returns whether EFX is available or not.
			 * @return bool
			 */
			static bool isAvailable () noexcept;

			/**
			 * @brief getMaxAuxiliarySends
			 * @return ALint
			 */
			static ALint getMaxAuxiliarySends () noexcept;

		private:

			static bool s_isAvailable;
			static ALint s_maxAuxiliarySends;

			ALCdevice * m_device = nullptr;
	};
	// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
}
