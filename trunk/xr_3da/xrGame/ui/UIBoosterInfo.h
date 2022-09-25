#pragma once
#include "UIWindow.h"

class CUIXml;
class CUIStatic;
class CUITextWnd;
class CInventoryItem;
class UIBoosterInfoItem;

class CUIBoosterInfo : public CUIWindow
{
public:
					CUIBoosterInfo		();
	virtual			~CUIBoosterInfo		();
			void	InitFromXml			(CUIXml& xml);
			void	SetInfo				(CInventoryItem& pInvItem);

protected:
	enum {
		_item_start = 0,
		_item_health_restore_speed = _item_start,
		_item_bleeding_restore_speed,
		_item_power_restore_speed,
		_item_radiation_restore_speed,
		_item_satiety_restore_speed,
		_item_alcohol_restore_speed,

		eBoostExplImmunity
	};
	UIBoosterInfoItem*	m_booster_items[eBoostExplImmunity];
	UIBoosterInfoItem*	m_portions;
	
	CUIStatic*			m_Prop_line;

}; // class CUIBoosterInfo

// -----------------------------------

class UIBoosterInfoItem : public CUIWindow
{
public:
				UIBoosterInfoItem	();
	virtual		~UIBoosterInfoItem();
		
		void	Init				( CUIXml& xml, LPCSTR section );
		void	SetCaption			( LPCSTR name );
		void	SetValue			( float value );
	
private:
	CUIStatic*	m_caption;
	CUIStatic*	m_value;
	float		m_magnitude;
	bool		m_show_sign;
	int			m_color_mode;
	shared_str	m_unit_str;
	shared_str	m_texture_minus;
	shared_str	m_texture_plus;

}; // class UIBoosterInfoItem
