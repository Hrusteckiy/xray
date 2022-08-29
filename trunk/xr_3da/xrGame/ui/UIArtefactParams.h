#pragma once
#include "UIWindow.h"


class CUIXml;
class CUIStatic;
class CUITextWnd;
class UIArtefactParamsItem;

class CUIArtefactParams :public CUIWindow
{
public:
								CUIArtefactParams		();
	virtual						~CUIArtefactParams		();
	void 						InitFromXml				(CUIXml& xml_doc);
	bool 						Check					(const shared_str& af_section);
	void 						SetInfo					(const shared_str& af_section);

protected:
	enum{
		_item_start						=0,
		_item_health_restore_speed		=_item_start,
		_item_radiation_restore_speed,
		_item_satiety_restore_speed,
		_item_power_restore_speed,
		_item_bleeding_restore_speed,

		_max_item_index1,

		_item_burn_immunity				= _max_item_index1,
		_item_strike_immunity,
		_item_shock_immunity,
		_item_wound_immunity,		
		_item_radiation_immunity,
		_item_telepatic_immunity,
		_item_chemical_burn_immunity,
		_item_explosion_immunit,
		_item_fire_wound_immunity,

		_max_item_index,

	};
	UIArtefactParamsItem*					m_info_items[_max_item_index];
	CUIStatic*								m_Prop_line;
};

// -----------------------------------

class UIArtefactParamsItem : public CUIWindow
{
public:
	UIArtefactParamsItem();
	virtual		~UIArtefactParamsItem();

	void	Init(CUIXml& xml, LPCSTR section);
	void	SetCaption(LPCSTR name);
	void	SetValue(float value);

private:
	CUIStatic* m_caption;
	CUITextWnd* m_value;
	float		m_magnitude;
	bool		m_show_sign;
	int			m_color_mode;
	shared_str	m_unit_str;
	shared_str	m_texture_minus;
	shared_str	m_texture_plus;

}; // class UIArtefactParamsItem
