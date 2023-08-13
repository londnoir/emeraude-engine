/*
 * Emeraude/Audio/TrackMixer.cpp
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

#include "TrackMixer.hpp"

/* Local inclusions */
#include "Arguments.hpp"
#include "Manager.hpp"
#include "Resources/Manager.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"

namespace Emeraude::Audio
{
	using namespace Libraries;

	const size_t TrackMixer::ClassUID{Observable::getClassUID()};

	TrackMixer::TrackMixer (const Arguments & arguments, Settings & coreSettings, Resources::Manager & resourceManager, Manager & audioManager) noexcept
		: ServiceInterface(ClassId), ConsoleControllable(ClassId),
		  m_arguments(arguments), m_coreSettings(coreSettings), m_resourceManager(resourceManager), m_audioManager(audioManager)
	{

	}

	bool
	TrackMixer::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	TrackMixer::onInitialize () noexcept
	{
		if ( !Manager::isAudioAvailable() )
		{
			Tracer::warning(ClassId, "Audio external input disabled at startup.");

			return true;
		}

		/* Sets master volume. */
		const auto gain = m_coreSettings.getAs< float >(Manager::MusicVolumeKey, Manager::DefaultMusicVolume);

		this->setVolume(gain);

		/* Allocating track sources (to volume 0) */
		for ( const auto & trackPtr : std::array{&m_trackA, &m_trackB} )
		{
			auto & track = (*trackPtr);

			track = m_audioManager.requestSource();

			if ( track == nullptr )
			{
				Tracer::error(ClassId, "There is no more source available to create the mixer sound tracks !");

				return false;
			}

			track->setRelativeState(true);
			track->setRolloffFactor(0.0F);
			track->setGain(0.0F);
		}

		/* Console commands bindings. */
		this->bindCommand("play", std::bind(&TrackMixer::CFPlay, this, std::placeholders::_1), "Play or resume a music. There is no need of parameter to resume.");
		this->bindCommand("pause", std::bind(&TrackMixer::CFPause, this, std::placeholders::_1), "Pause music playback.");
		this->bindCommand("stop", std::bind(&TrackMixer::CFStop, this, std::placeholders::_1), "Stop music.");

		/* FIXME: Why commented ? */
		//this->registerToConsole();

		m_flags[Usable] = true;

		return true;
	}

	bool
	TrackMixer::onTerminate () noexcept
	{
		if ( this->usable() )
		{
			m_trackA->stop();
			m_trackB->stop();
		}

		return true;
	}

	bool
	TrackMixer::usable () const noexcept
	{
		return m_flags[Usable];
	}

	void
	TrackMixer::setVolume (float volume) noexcept
	{
		m_gain = Math::clampToUnit(volume);

		if ( this->usable() )
		{
			switch ( m_playingTrack )
			{
				case PlayingTrack::TrackA :
					m_trackA->setGain(m_gain);
					break;

				case PlayingTrack::TrackB :
					m_trackB->setGain(m_gain);
					break;

				case PlayingTrack::None:
					break;
			}
		}
	}

	bool
	TrackMixer::checkTrackLoading (const std::shared_ptr< MusicResource > & track) noexcept
	{
		if ( track->isLoaded() )
		{
			TraceSuccess{ClassId} << "The track '" << track->name() << "' is ready to play !";

			if ( m_loadingTrack != nullptr )
			{
				this->forget(m_loadingTrack.get());

				m_loadingTrack.reset();
			}

			return true;
		}

		Tracer::info(ClassId, "Wait until the track is completely loaded in memory for playing !");

		m_loadingTrack = track;

		this->observe(track.get());

		return false;
	}

	bool
	TrackMixer::setSoundTrack (const std::shared_ptr< MusicResource > & track, bool fade) noexcept
	{
		if ( !this->usable() )
		{
			Tracer::warning(ClassId, "The track mixer is unavailable !");

			return false;
		}

		if ( track == nullptr )
		{
			Tracer::error(ClassId, "The track is a null pointer !");

			return false;
		}

		m_flags[IsFadingWasDemanded] = fade;

		/* Check if we need to wait the track to be loaded in memory. */
		if ( !this->checkTrackLoading(track) )
		{
			return true;
		}

		if ( m_flags[IsFadingWasDemanded] )
		{
			this->notify(MusicSwitching, (std::stringstream{} << "Fading to '" << track->title() << "' track from '" << track->artist() << "'.").str());

			/* Which track is playing. */
			switch ( m_playingTrack )
			{
				case PlayingTrack::TrackA :
					m_flags[IsTrackingFading] = true;

					m_trackB->play(track.get(), Source::PlayMode::Loop);

					m_playingTrack = PlayingTrack::TrackB;
					break;

				case PlayingTrack::None:
				case PlayingTrack::TrackB :
					m_flags[IsTrackingFading] = true;

					m_trackA->play(track.get(), Source::PlayMode::Loop);

					m_playingTrack = PlayingTrack::TrackA;
					break;
			}
		}
		else
		{
			this->notify(MusicPlaying, (std::stringstream{} << "Now playing '" << track->title() << "' track from '" << track->artist() << "'.").str());

			/* Which track is playing. */
			switch ( m_playingTrack )
			{
				case PlayingTrack::None:
					m_playingTrack = PlayingTrack::TrackA;

					[[fallthrough]];

				case PlayingTrack::TrackA :
					m_flags[IsTrackingFading] = false;

					m_trackA->setGain(m_gain);
					m_trackA->play(track.get(), Source::PlayMode::Loop);
					break;

				case PlayingTrack::TrackB :
					m_flags[IsTrackingFading] = false;

					m_trackB->setGain(m_gain);
					m_trackB->play(track.get(), Source::PlayMode::Loop);
					break;
			}
		}

		return true;
	}

	bool
	TrackMixer::isPlaying () const noexcept
	{
		if ( this->usable() )
		{
			switch ( m_playingTrack )
			{
				case PlayingTrack::TrackA :
				case PlayingTrack::TrackB :
					return true;

				default :
					break;
			}
		}

		return false;
	}

	void
	TrackMixer::pause () noexcept
	{
		if ( !this->usable() )
		{
			return;
		}

		switch ( m_playingTrack )
		{
			case PlayingTrack::None:
				break;

			case PlayingTrack::TrackA :
				m_trackA->pause();

				this->notify(MusicPaused);
				break;

			case PlayingTrack::TrackB :
				m_trackB->pause();

				this->notify(MusicPaused);
				break;
		}
	}

	void
	TrackMixer::resume () noexcept
	{
		if ( !this->usable() )
		{
			return;
		}

		switch ( m_playingTrack )
		{
			case PlayingTrack::None:
				break;

			case PlayingTrack::TrackA :
				m_trackA->resume();

				this->notify(MusicResumed);
				break;

			case PlayingTrack::TrackB :
				m_trackB->resume();

				this->notify(MusicResumed);
				break;
		}
	}

	void
	TrackMixer::stop () noexcept
	{
		if ( !this->usable() )
		{
			return;
		}

		switch ( m_playingTrack )
		{
			case PlayingTrack::None:
				break;

			case PlayingTrack::TrackA :
				m_trackA->stop();
				m_playingTrack = PlayingTrack::None;

				this->notify(MusicStopped);
				break;

			case PlayingTrack::TrackB :
				m_trackB->stop();
				m_playingTrack = PlayingTrack::None;

				this->notify(MusicStopped);
				break;
		}
	}

	int
	TrackMixer::CFPlay (const std::vector< std::string > & parameters) noexcept
	{
		if ( !this->usable() )
		{
			this->writeToConsole("The track mixer is unavailable !", Severity::Info);

			return 0;
		}

		/* Checks if we need to resume. */
		if ( parameters.empty() )
		{
			switch ( m_playingTrack )
			{
				case PlayingTrack::None :
					this->writeToConsole("There is no soundtrack !", Severity::Error);
					break;

				case PlayingTrack::TrackA :
					if ( m_trackA->isPaused() )
					{
						m_trackA->resume();

						this->writeToConsole("Resuming track A.", Severity::Info);

						return 0;
					}
					break;

				case PlayingTrack::TrackB :
					if ( m_trackB->isPaused() )
					{
						m_trackB->resume();

						this->writeToConsole("Resuming track B.", Severity::Info);

						return 0;
					}
					break;
			}

			return 1;
		}

		/* Search the song. */
		auto soundtrack = m_resourceManager.musics().getResource(parameters[0]);

		if ( soundtrack == nullptr )
		{
			this->writeToConsole(Blob() << "Soundtrack '" << parameters[0] << "' doesn't exist !", Severity::Error);

			return 2;
		}

		this->setSoundTrack(soundtrack);

		this->writeToConsole(Blob() << "Playing '" << parameters[0] << "' ...", Severity::Info);

		return 0;
	}

	int
	TrackMixer::CFPause (const std::vector< std::string > & /*parameters*/) noexcept
	{
		if ( !this->usable() )
		{
			this->writeToConsole("The track mixer is unavailable !", Severity::Info);

			return 1;
		}

		switch ( m_playingTrack )
		{
			case PlayingTrack::None :
				this->writeToConsole("There is no track playing !", Severity::Info);
				break;

			case PlayingTrack::TrackA :
				m_trackA->pause();

				this->writeToConsole("Track A paused.", Severity::Info);
				break;

			case PlayingTrack::TrackB :
				m_trackB->pause();

				this->writeToConsole("Track B paused.", Severity::Info);
				break;
		}

		return 0;
	}

	int
	TrackMixer::CFStop (const std::vector< std::string > & /*parameters*/) noexcept
	{
		if ( !this->usable() )
		{
			this->writeToConsole("The track mixer is unavailable !", Severity::Info);

			return 1;
		}

		switch ( m_playingTrack )
		{
			case PlayingTrack::None:
				this->writeToConsole("There is no track playing !", Severity::Info);
				break;

			case PlayingTrack::TrackA :
				m_trackA->stop();
				m_playingTrack = PlayingTrack::None;

				this->writeToConsole("Track A stopped.", Severity::Info);
				break;

			case PlayingTrack::TrackB :
				m_trackB->stop();
				m_playingTrack = PlayingTrack::None;

				this->writeToConsole("Track B stopped.", Severity::Info);
				break;
		}

		return 0;
	}

	float
	TrackMixer::volume () const noexcept
	{
		return m_gain;
	}

	bool
	TrackMixer::onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable->is(MusicResource::ClassUID) )
		{
			if ( m_loadingTrack != nullptr )
			{
				switch ( notificationCode )
				{
					/* The track loaded successfully, we can now play it. */
					case Resources::ResourceTrait::LoadFinished :
						this->setSoundTrack(m_loadingTrack, m_flags[IsFadingWasDemanded]);
						break;

					case Resources::ResourceTrait::LoadFailed :
						Tracer::warning(ClassId, "The track has failed to load ! Cancelling the playback...");
						break;

					default:
						TraceDebug{ClassId} << "Event #" << notificationCode << " from a music resource ignored.";
						break;
				}
			}
			else
			{
				Tracer::info(ClassId, "No music track was waited here !");
			}

			/* NOTE: We don't keep any observable here. */
			return false;
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled event from observable @" << observable << " (code:" << notificationCode << ") ! "
			"Forgetting it ...";
#endif

		return false;
	}

	bool
	TrackMixer::fadeTrack (Source & track, float step) const noexcept
	{
		auto bound = false;

		auto currentVolume = track.gain();

		/* Stepping */
		currentVolume += step;

		if ( currentVolume > m_gain )
		{
			currentVolume = m_gain;
			bound = true;
		}
		else if ( currentVolume < 0.0F )
		{
			currentVolume = 0.0F;
			bound = true;
		}

		track.setGain(currentVolume);

		return bound;
	}

	void
	TrackMixer::update () noexcept
	{
		if ( !this->usable() )
		{
			return;
		}

		if ( m_flags[IsTrackingFading] )
		{
			constexpr auto stepValue = 0.01F;// NOLINT(*-magic-numbers)

			switch ( m_playingTrack )
			{
				case PlayingTrack::TrackA :
					/* Decrease TrackB volume. */
					if ( !m_trackB->isMuted() )
					{
						this->fadeTrack(*m_trackB, -stepValue);
					}

					/* Increase TrackA volume. */
					if ( this->fadeTrack(*m_trackA, stepValue) )
					{
						m_trackB->setGain(0.0F);

						m_flags[IsTrackingFading] = false;
					}
					break;

				case PlayingTrack::TrackB :
					/* Decrease TrackA volume. */
					if ( !m_trackA->isMuted() )
					{
						this->fadeTrack(*m_trackA, -stepValue);
					}

					/* Increase TrackB volume. */
					if ( this->fadeTrack(*m_trackB, stepValue) )
					{
						m_trackA->setGain(0.0F);

						m_flags[IsTrackingFading] = false;
					}
					break;

				case PlayingTrack::None :
					m_flags[IsTrackingFading] = false;
					break;
			}
		}
	}
}
