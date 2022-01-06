/*
* Copyright 2006 Milan Digital Audio LLC
* Copyright 2009-2021 GrandOrgue contributors (see AUTHORS)
* License GPL-2.0 or later (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
*/

#ifndef SETTINGSOPTION_H
#define SETTINGSOPTION_H

#include <wx/panel.h>

enum class GOInitialLoadType;
template<class T> class GOChoice;
class GOSettings;
class wxCheckBox;
class wxChoice;
class wxDirPickerCtrl;
class wxSpinCtrl;

class SettingsOption : public wxPanel
{
	enum {
		ID_WAVE_FORMAT = 200,
		ID_CONCURRENCY,
		ID_RELEASE_CONCURRENCY,
		ID_LOAD_CONCURRENCY,
		ID_LOSSLESS_COMPRESSION,
		ID_MANAGE_POLYPHONY,
		ID_COMPRESS_CACHE,
		ID_MANAGE_CACHE,
		ID_SCALE_RELEASE,
		ID_LOAD_LAST_FILE,
		ID_RANDOMIZE,
		ID_SETTINGS_DIR,
		ID_CACHE_DIR,
		ID_BITS_PER_SAMPLE,
		ID_LOOP_LOAD,
		ID_ATTACK_LOAD,
		ID_RELEASE_LOAD,
		ID_CHANNELS,
		ID_INTERPOLATION,
		ID_MEMORY_LIMIT,
		ID_ODF_CHECK,
		ID_RECORD_DOWNMIX,
		ID_LANGUAGE
	};
private:
	GOSettings& m_Settings;
	wxChoice* m_Concurrency;
	wxChoice* m_ReleaseConcurrency;
	wxChoice* m_LoadConcurrency;
	wxChoice* m_WaveFormat;
	wxCheckBox* m_LosslessCompression;
	wxCheckBox* m_Limit;
	wxCheckBox* m_CompressCache;
	wxCheckBox* m_ManageCache;
	GOChoice<GOInitialLoadType>* m_LoadLastFile;
	wxCheckBox* m_Scale;
	wxCheckBox* m_Random;
	wxCheckBox* m_ODFCheck;
	wxCheckBox* m_RecordDownmix;
	wxDirPickerCtrl* m_SettingsPath;
	wxDirPickerCtrl* m_CachePath;
	wxChoice* m_BitsPerSample;
	wxChoice* m_LoopLoad;
	wxChoice* m_AttackLoad;
	wxChoice* m_ReleaseLoad;
	wxChoice* m_Channels;
	wxChoice* m_Interpolation;
	wxSpinCtrl* m_MemoryLimit;
	wxChoice* m_Language;
	
	wxString m_OldLanguageCode;
	unsigned m_OldChannels;
	bool m_OldLosslessCompression;
	unsigned m_OldBitsPerSample;
	unsigned m_OldLoopLoad;
	unsigned m_OldAttackLoad;
	unsigned m_OldReleaseLoad;

public:
	SettingsOption(GOSettings& settings, wxWindow* parent);

	bool NeedReload();
	bool NeedRestart();

	void Save();
};

#endif
