#include "stdafx.h"
#include "UIArtefactParams.h"
#include "UIStatic.h"
#include "UIXmlInit.h"
#include "UIHelper.h"
#include "../string_table.h"
#include "..\actor.h"

CUIArtefactParams::CUIArtefactParams()
{
	for (u32 i = _item_start; i < _max_item_index; ++i)
	{
		m_info_items[i] = NULL;
	}
}

CUIArtefactParams::~CUIArtefactParams()
{
	delete_data(m_info_items);
	xr_delete(m_Prop_line);
}

LPCSTR af_item_sect_names[] = {
	"health_restore_speed",
	"radiation_restore_speed",
	"satiety_restore_speed",
	"power_restore_speed",
	"bleeding_restore_speed",
	
	"burn_immunity",
	"strike_immunity",
	"shock_immunity",
	"wound_immunity",		
	"radiation_immunity",
	"telepatic_immunity",
	"chemical_burn_immunity",
	"explosion_immunity",
	"fire_wound_immunity",
};

LPCSTR af_item_param_names[] = {
	"ui_inv_health",
	"ui_inv_radiation",
	"ui_inv_satiety",
	"ui_inv_power",
	"ui_inv_bleeding",

	"ui_inv_outfit_burn_protection",			// "(burn_imm)",
	"ui_inv_outfit_strike_protection",			// "(strike_imm)",
	"ui_inv_outfit_shock_protection",			// "(shock_imm)",
	"ui_inv_outfit_wound_protection",			// "(wound_imm)",
	"ui_inv_outfit_radiation_protection",		// "(radiation_imm)",
	"ui_inv_outfit_telepatic_protection",		// "(telepatic_imm)",
	"ui_inv_outfit_chemical_burn_protection",	// "(chemical_burn_imm)",
	"ui_inv_outfit_explosion_protection",		// "(explosion_imm)",
	"ui_inv_outfit_fire_wound_protection",		// "(fire_wound_imm)",
};

LPCSTR af_actor_param_names[]={
	"satiety_health_v",
	"radiation_v",
	"satiety_v",
	"satiety_power_v",
	"wound_incarnation_v",
};
void CUIArtefactParams::InitFromXml(CUIXml& xml_doc)
{
	LPCSTR base	= "af_params";
	XML_NODE* stored_root = xml_doc.GetLocalRoot();
	XML_NODE* base_node   = xml_doc.NavigateToNode( base, 0 );
	if(!base_node)
		return;

	CUIXmlInit::InitWindow(xml_doc, base, 0, this);
	xml_doc.SetLocalRoot(base_node);
	
	m_Prop_line = xr_new<CUIStatic>();
	AttachChild(m_Prop_line);
	m_Prop_line->SetAutoDelete(false);	
	CUIXmlInit::InitStatic(xml_doc, "prop_line", 0, m_Prop_line);

	for(u32 i=_item_start; i<_max_item_index; ++i)
	{
		m_info_items[i] = xr_new<UIArtefactParamsItem>();
		m_info_items[i]->Init(xml_doc, af_item_sect_names[i]);
		m_info_items[i]->SetAutoDelete(false);

		LPCSTR name = CStringTable().translate(af_item_param_names[i]).c_str();
		m_info_items[i]->SetCaption(name);
		xml_doc.SetLocalRoot(base_node);
	}
	xml_doc.SetLocalRoot(stored_root);
}

bool CUIArtefactParams::Check(const shared_str& af_section)
{
	return !!pSettings->line_exist(af_section, "af_actor_properties");
}
#include "../string_table.h"
void CUIArtefactParams::SetInfo(const shared_str& af_section)
{
	DetachAll();
	AttachChild( m_Prop_line );

	CActor* actor = smart_cast<CActor*>(Level().CurrentViewEntity());
	if (!actor)
	{
		return;
	}

	float						_h = m_Prop_line->GetWndPos().y + m_Prop_line->GetWndSize().y;
	Fvector2					pos;
	for(u32 i=_item_start; i<_max_item_index; ++i)
	{
		float					_val;
		if(i<_max_item_index1)
		{
			float _actor_val	= pSettings->r_float	("actor_condition", af_actor_param_names[i]);
			_val				= pSettings->r_float	(af_section, af_item_sect_names[i]);

			if					(fis_zero(_val))				continue;
			
			_val				= (_val/_actor_val)*100.0f;
		}else
		{
			shared_str _sect	= pSettings->r_string(af_section, "hit_absorbation_sect");
			_val				= pSettings->r_float(_sect, af_item_sect_names[i]);
			if					(fsimilar(_val, 1.0f))				continue;
			_val				= (1.0f - _val);
			_val				*= 100.0f;

		}

		if(i==_item_radiation_restore_speed || i==_item_power_restore_speed)
			_val				/= 100.0f;
				
		if(i==_item_bleeding_restore_speed)
			_val		*=	-1.0f;

		m_info_items[i]->SetValue(_val);
		
		pos.set(m_info_items[i]->GetWndPos());
		pos.y = _h;
		m_info_items[i]->SetWndPos(pos);

		_h += m_info_items[i]->GetWndSize().y;
		AttachChild(m_info_items[i]);
	}
	SetHeight					(_h);
}

/// ----------------------------------------------------------------

UIArtefactParamsItem::UIArtefactParamsItem()
{
	m_caption				= NULL;
	m_value					= NULL;
	m_magnitude				= 1.0f;
	m_show_sign				= false;
	m_color_mode			= 0;
	
	m_unit_str._set			("");
	m_texture_minus._set	("");
	m_texture_plus._set		("");
}

UIArtefactParamsItem::~UIArtefactParamsItem()
{
}

void UIArtefactParamsItem::Init(CUIXml& xml, LPCSTR section)
{
	CUIXmlInit::InitWindow(xml, section, 0, this);
	xml.SetLocalRoot(xml.NavigateToNode(section));

	m_caption   = UIHelper::CreateStatic(xml, "caption", this);
	m_value     = UIHelper::CreateTextWnd(xml, "value",   this);
	m_magnitude = xml.ReadAttribFlt("value", 0, "magnitude", 1.0f);
	m_show_sign = (xml.ReadAttribInt("value", 0, "show_sign", 1) == 1);
	m_color_mode = xml.ReadAttribInt("value", 0, "color_mode", 0);
	
	LPCSTR unit_str = xml.ReadAttrib("value", 0, "unit_str", "");
	m_unit_str._set(CStringTable().translate(unit_str));
	
	LPCSTR texture_minus = xml.Read("texture_minus", 0, "");
	if(texture_minus && xr_strlen(texture_minus))
	{
		m_texture_minus._set(texture_minus);
		
		LPCSTR texture_plus = xml.Read("caption:texture", 0, "");
		m_texture_plus._set(texture_plus);
		VERIFY(m_texture_plus.size());
	}
}

void UIArtefactParamsItem::SetCaption(LPCSTR name)
{
	m_caption->SetText(name);
}

void UIArtefactParamsItem::SetValue(float value)
{
	value *= m_magnitude;
	string32 buf;
	string32 str;
	u32 red = color_rgba(255, 0, 0, 255);
	u32 green = color_rgba(0, 255, 0, 255);
	m_show_sign?
		xr_sprintf(buf, "%+.0f", value):xr_sprintf(buf, "%.0f", value);

	m_unit_str.size()?
		xr_sprintf(str,"%s%s", buf, m_unit_str.c_str()):xr_sprintf(str,"%s", buf);

	m_value->SetText(str);

	if (m_color_mode == 2)
	{
		(value > 0)?m_value->SetTextColor(red):m_value->SetTextColor(green);
	}
	else if(m_color_mode == 1)
	{
		(value < 0)?m_value->SetTextColor(red):m_value->SetTextColor(green);
	}
	else
		m_value->SetTextColor(color_rgba(170,170,170,255));

	if(m_texture_minus.size())
	{
		if(positive)
			m_caption->InitTexture(m_texture_plus.c_str());
		else
			m_caption->InitTexture(m_texture_minus.c_str());
	}
}