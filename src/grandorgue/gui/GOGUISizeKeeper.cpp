/*
 * Copyright 2006 Milan Digital Audio LLC
 * Copyright 2009-2023 GrandOrgue contributors (see AUTHORS)
 * License GPL-2.0 or later
 * (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
 */

#include "GOGUISizeKeeper.h"

#include <wx/display.h>
#include <wx/toplevel.h>

#include "config/GOConfigReader.h"
#include "config/GOConfigWriter.h"

constexpr static int windowLimit = 10000;

const wxString WX_WINDOW_X = wxT("WindowX");
const wxString WX_WINDOW_Y = wxT("WindowY");
const wxString WX_WINDOW_WIDTH = wxT("WindowWidth");
const wxString WX_WINDOW_HEIGHT = wxT("WindowHeight");
const wxString WX_DISPLAY_NUMBER = wxT("DisplayNumber");
const wxString WX_WINDOW_MAXIMIZED = wxT("WindowMaximized");

// read the size info from config files
void GOGUISizeKeeper::Load(GOConfigReader &cfg, const wxString &group) {
  SetGroup(group);
  int x = cfg.ReadInteger(
    CMBSetting, m_group, WX_WINDOW_X, -windowLimit, windowLimit, false, 0);
  int y = cfg.ReadInteger(
    CMBSetting, m_group, WX_WINDOW_Y, -windowLimit, windowLimit, false, 0);
  int w = cfg.ReadInteger(
    CMBSetting, m_group, WX_WINDOW_WIDTH, 0, windowLimit, false, 0);
  int h = cfg.ReadInteger(
    CMBSetting, m_group, WX_WINDOW_HEIGHT, 0, windowLimit, false, 0);

  m_rect = wxRect(x, y, w, h);
  m_DisplayNum = cfg.ReadInteger(
    CMBSetting, m_group, WX_DISPLAY_NUMBER, -1, windowLimit, false, -1);
  m_IsMaximized
    = cfg.ReadBoolean(CMBSetting, m_group, WX_WINDOW_MAXIMIZED, false, false);
}

// save the size info to the config file
void GOGUISizeKeeper::Save(GOConfigWriter &cfg) {
  cfg.WriteBoolean(m_group, WX_WINDOW_MAXIMIZED, m_IsMaximized);
  if (m_DisplayNum >= 0)
    cfg.WriteInteger(m_group, WX_DISPLAY_NUMBER, m_DisplayNum);

  wxRect size = m_rect;

  cfg.WriteInteger(
    m_group,
    WX_WINDOW_X,
    std::min(windowLimit, std::max(-windowLimit, size.GetLeft())));
  cfg.WriteInteger(
    m_group,
    WX_WINDOW_Y,
    std::min(windowLimit, std::max(-windowLimit, size.GetTop())));
  cfg.WriteInteger(
    m_group, WX_WINDOW_WIDTH, std::min(windowLimit, size.GetWidth()));
  cfg.WriteInteger(
    m_group, WX_WINDOW_HEIGHT, std::min(windowLimit, size.GetHeight()));
}

// gets the current size info of the window
void GOGUISizeKeeper::CaptureSizeInfo(const wxTopLevelWindow &win) {
  m_rect = win.GetRect();
  m_IsMaximized = win.IsMaximized();

  // calculate the best display num
  m_DisplayNum = wxDisplay::GetFromWindow(&win);
  if (m_DisplayNum == wxNOT_FOUND)
    // actually wxNOT_FOUND == -1, but we don't want to depend on it
    m_DisplayNum = -1;
  else if (!m_IsMaximized) {
    // check that the window fits the display
    // we do not check it for maximized window because their decoration may be
    // outside the display
    const wxDisplay display(m_DisplayNum);
    const wxRect clientArea = display.GetClientArea();

    if (!clientArea.Contains(m_rect))
      // do not store the dispplay num if the window does not fit it
      m_DisplayNum = -1;
  }
}

// make the windows position and size as the stored size info
void GOGUISizeKeeper::ApplySizeInfo(wxTopLevelWindow &win) {
  // m_rect contains the position and size of the window as saved by the user
  // previously, or otherwise its default values

  // If both width and height are set, set position and size of the window
  // E.g. in case of corrupted preferences, this might not be the case
  if (!m_rect.IsEmpty())
    win.SetSize(m_rect);

  // However, even if this worked, we cannot be sure that the window is now
  // fully within the client area of an existing display.
  // For example, the user may have disconnected the display, or lowered its
  // resolution. So, we need to get the client area of the desired display, or
  // if it does not exist anymore, the client area of the default display
  int nr = m_DisplayNum >= 0 && m_DisplayNum < (int)wxDisplay::GetCount()
    ? m_DisplayNum
    : wxDisplay::GetFromWindow(&win);

  // Check if the window is visible. If not, center it at the first display
  if (nr == wxNOT_FOUND) {
    wxRect max = wxDisplay((unsigned)0).GetClientArea();
    // If our current window is within this area, all is fine
    wxRect current = win.GetRect();

    if (!max.Contains(current)) {
      // Otherwise, check and correct width and height,
      // and place the frame at the center of the Client Area of the display
      if (current.GetWidth() > max.GetWidth())
        current.SetWidth(max.GetWidth());
      if (current.GetHeight() > max.GetHeight())
        current.SetHeight(max.GetHeight());
      win.SetSize(current.CenterIn(max, wxBOTH));
    }
  }
  win.Maximize(m_IsMaximized);
}
