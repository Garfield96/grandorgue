/*
* Copyright 2006 Milan Digital Audio LLC
* Copyright 2009-2021 GrandOrgue contributors (see AUTHORS)
* License GPL-2.0 or later (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
*/

#include "SettingsMidiMessage.h"

#include "settings/GOSettings.h"
#include "midi/MIDIEventDialog.h"
#include <wx/button.h>
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/sizer.h>

BEGIN_EVENT_TABLE(SettingsMidiMessage, wxPanel)
	EVT_LIST_ITEM_SELECTED(ID_EVENTS, SettingsMidiMessage::OnEventsClick)
	EVT_LIST_ITEM_ACTIVATED(ID_EVENTS, SettingsMidiMessage::OnEventsDoubleClick)
	EVT_BUTTON(ID_PROPERTIES, SettingsMidiMessage::OnProperties)
END_EVENT_TABLE()

SettingsMidiMessage::SettingsMidiMessage(GOSettings& settings, GOMidi& midi, wxWindow* parent) :
	wxPanel(parent, wxID_ANY),
	m_Settings(settings),
	m_midi(midi)
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->AddSpacer(5);
	topSizer->Add(new wxStaticText(this, wxID_ANY, _("Attention:\nThese initial midi settings only affect the first load of a organ.\nRight-click on manuals, stops, ... to do further changes.")), 0, wxALL);
	topSizer->AddSpacer(5);

	m_Events = new wxListView(this, ID_EVENTS, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_HRULES | wxLC_VRULES);
	m_Events->InsertColumn(0, _("Group"));
	m_Events->InsertColumn(1, _("Element"));
	m_Events->InsertColumn(2, _("MIDI Event"));
	topSizer->Add(m_Events, 1, wxEXPAND | wxALL, 5);
	m_Properties = new wxButton(this, ID_PROPERTIES, _("P&roperties..."));
	m_Properties->Disable();
	topSizer->Add(m_Properties, 0, wxALIGN_RIGHT | wxALL, 5);

	for (unsigned i = 0; i < m_Settings.GetEventCount(); i++)
	{
		GOMidiReceiverBase* recv = m_Settings.GetMidiEvent(i);
		m_Events->InsertItem(i, m_Settings.GetEventGroup(i));
		m_Events->SetItemPtrData(i, (wxUIntPtr)recv);
		m_Events->SetItem(i, 1, m_Settings.GetEventTitle(i));
		m_Events->SetItem(i, 2, recv->GetEventCount() > 0 ? _("Yes") : _("No") );
	}

	topSizer->AddSpacer(5);
	this->SetSizer(topSizer);
	topSizer->Fit(this);

	m_Events->SetColumnWidth(0, wxLIST_AUTOSIZE);
	m_Events->SetColumnWidth(1, wxLIST_AUTOSIZE);
	m_Events->SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
}

void SettingsMidiMessage::OnEventsClick(wxListEvent& event)
{
	m_Properties->Enable();
}

void SettingsMidiMessage::OnEventsDoubleClick(wxListEvent& event)
{
	m_Properties->Enable();
	int index = m_Events->GetFirstSelected();

	GOMidiReceiverBase* recv = (GOMidiReceiverBase*)m_Events->GetItemData(m_Events->GetFirstSelected());
	MIDIEventDialog dlg(NULL, this, wxString::Format(_("Initial MIDI settings for %s"), m_Settings.GetEventTitle(index).c_str()), m_Settings, recv, NULL, NULL);
	dlg.RegisterMIDIListener(&m_midi);
	dlg.ShowModal();
	m_Events->SetItem(index, 2, recv->GetEventCount() > 0 ? _("Yes") : _("No") );
}

void SettingsMidiMessage::OnProperties(wxCommandEvent& event)
{
	wxListEvent listevent;
	OnEventsDoubleClick(listevent);
}

