#pragma once
/** \copyright
holo
Copyright (C) 2023  Jon David Sawyer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <holo/sdl/EvtTypeSwitch.hh>
namespace holo {

  /** \brief distinguish between window event sub-types.
   * \todo unit test
   * \ingroup sdl */
  class SdlEvtWin
    : public EvtAbstractTypeSwitch<SDL_WindowEventID, SDL_Event&> {
    public:
      /** when window was made visible. */
      std::shared_ptr<SdlEvt> const Shown          = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const Hidden         = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const Exposed        = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const Moved          = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const Resized        = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const SizeChanged    = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const Minimized      = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const Maximized      = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const Restored       = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const Enter          = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const Leave          = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const FocusGained    = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const FocusLost      = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const Close          = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const TakeFocus      = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const HitTest        = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const IccProfChanged = std::make_shared<SdlEvt>();
      /** \todo documentation obvious, better way of handling? */
      std::shared_ptr<SdlEvt> const DisplayChanged = std::make_shared<SdlEvt>();
      SdlEvtWin();
  };
}