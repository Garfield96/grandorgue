/*
* Copyright 2006 Milan Digital Audio LLC
* Copyright 2009-2021 GrandOrgue contributors (see AUTHORS)
* License GPL-2.0 or later (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
*/

#include "SettingsAudioGroup.h"

#include "settings/GOSettings.h"
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/textdlg.h>

BEGIN_EVENT_TABLE(SettingsAudioGroup, wxPanel)
	EVT_LISTBOX(ID_AUDIOGROUP_LIST, SettingsAudioGroup::OnGroup)
	EVT_LISTBOX_DCLICK(ID_AUDIOGROUP_LIST, SettingsAudioGroup::OnGroupChange)
	EVT_BUTTON(ID_AUDIOGROUP_ADD, SettingsAudioGroup::OnGroupAdd)
	EVT_BUTTON(ID_AUDIOGROUP_DEL, SettingsAudioGroup::OnGroupDel)
	EVT_BUTTON(ID_AUDIOGROUP_CHANGE, SettingsAudioGroup::OnGroupChange)
END_EVENT_TABLE()

SettingsAudioGroup::SettingsAudioGroup(GOSettings& settings, wxWindow* parent) :
	wxPanel(parent, wxID_ANY),
	m_Settings(settings)
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->AddSpacer(5);

	m_AudioGroups = new wxListBox(this, ID_AUDIOGROUP_LIST, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE | wxLB_NEEDED_SB);
	topSizer->Add(m_AudioGroups, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* buttonSizer =  new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->AddSpacer(5);
	m_Change = new wxButton(this, ID_AUDIOGROUP_CHANGE, _("Rename"));
	m_Change->Disable();
	m_Add = new wxButton(this, ID_AUDIOGROUP_ADD, _("&Add"));
	m_Del = new wxButton(this, ID_AUDIOGROUP_DEL, _("&Delete"));
	m_Del->Disable();

	buttonSizer->Add(m_Add, 0, wxALL, 5);
	buttonSizer->Add(m_Del, 0, wxALL, 5);
	buttonSizer->Add(m_Change, 0, wxALL, 5);
	topSizer->Add(buttonSizer, 0, wxALL, 5);

	std::vector<wxString> audio_groups = m_Settings.GetAudioGroups();
	for(unsigned i = 0; i < audio_groups.size(); i++)
		m_AudioGroups->Append(audio_groups[i]);

	topSizer->AddSpacer(5);
	this->SetSizer(topSizer);
	topSizer->Fit(this);
}

void SettingsAudioGroup::OnGroup(wxCommandEvent& event)
{
	if (m_AudioGroups->GetSelection() != wxNOT_FOUND)
		m_Change->Enable();
	else
		m_Change->Disable();

	if (m_AudioGroups->GetCount() > 1)
		m_Del->Enable();
	else
		m_Del->Disable();
}

void SettingsAudioGroup::OnGroupAdd(wxCommandEvent& event)
{
	wxString str = wxGetTextFromUser(_("New audio group name"), _("Audio groups")).Trim();
	if (str != wxEmptyString)
		if (m_AudioGroups->FindString(str) == wxNOT_FOUND)
			m_AudioGroups->Append(str);
}

void SettingsAudioGroup::OnGroupDel(wxCommandEvent& event)
{
	if (m_AudioGroups->GetCount() > 1)
		m_AudioGroups->Delete(m_AudioGroups->GetSelection());
	m_AudioGroups->SetSelection(0);
}

void SettingsAudioGroup::OnGroupChange(wxCommandEvent& event)
{
	int index = m_AudioGroups->GetSelection();
	wxString str = wxGetTextFromUser(_("Audio group name"), _("Audio groups"), m_AudioGroups->GetString(index)).Trim();
	if (str != wxEmptyString)
	{
		int idx = m_AudioGroups->FindString(str);
		if (idx == wxNOT_FOUND)
			m_AudioGroups->SetString(index, str);
		else if (idx != index)
			m_AudioGroups->Delete(index);
	}
}

std::vector<wxString> SettingsAudioGroup::GetGroups()
{
	std::vector<wxString> result;
	for(unsigned i = 0; i < m_AudioGroups->GetCount(); i++)
		result.push_back(m_AudioGroups->GetString(i));
	return result;
}

void SettingsAudioGroup::Save()
{
	std::vector<wxString> audio_groups;
	for(unsigned i = 0; i < m_AudioGroups->GetCount(); i++)
		audio_groups.push_back(m_AudioGroups->GetString(i));
	m_Settings.SetAudioGroups(audio_groups);
}
