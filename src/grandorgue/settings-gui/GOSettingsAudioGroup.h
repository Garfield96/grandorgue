/*
* Copyright 2006 Milan Digital Audio LLC
* Copyright 2009-2021 GrandOrgue contributors (see AUTHORS)
* License GPL-2.0 or later (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
*/

#ifndef SETTINGSAUDIOGROUP_H
#define SETTINGSAUDIOGROUP_H

#include <wx/panel.h>
#include <vector>

class GOSettings;
class wxButton;
class wxListBox;

class GOAudioGroupCallback
{
public:
	virtual std::vector<wxString> GetGroups() = 0;
};

class SettingsAudioGroup : public wxPanel, public GOAudioGroupCallback
{
	enum {
		ID_AUDIOGROUP_LIST = 200,
		ID_AUDIOGROUP_ADD,
		ID_AUDIOGROUP_DEL,
		ID_AUDIOGROUP_CHANGE,
	};

private:
	GOSettings& m_Settings;
	wxListBox* m_AudioGroups;
	wxButton* m_Add;
	wxButton* m_Del;
	wxButton* m_Change;

	void OnGroup(wxCommandEvent& event);
	void OnGroupAdd(wxCommandEvent& event);
	void OnGroupDel(wxCommandEvent& event);
	void OnGroupChange(wxCommandEvent& event);

public:
	SettingsAudioGroup(GOSettings& settings, wxWindow* parent);

	std::vector<wxString> GetGroups();

	void Save();

	DECLARE_EVENT_TABLE()
};

#endif
