////////////////////////////////////////////////////////////////////////////
//	Module 		: attachable_item.cpp
//	Created 	: 11.02.2004
//  Modified 	: 11.02.2004
//	Author		: Dmitriy Iassenev
//	Description : Attachable item
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "physicsshellholder.h"
#include "attachable_item.h"
#include "inventoryowner.h"
#include "inventory.h"
#include "level.h"
#include "HUDManager.h"
#include "../xr_input.h"

#ifdef DEBUG
	CAttachableItem*	CAttachableItem::m_dbgItem = NULL;
#endif

IC	CPhysicsShellHolder &CAttachableItem::object	() const
{
	return				(item().object());
}

DLL_Pure *CAttachableItem::_construct	()
{
	VERIFY				(!m_item);
	m_item				= smart_cast<CInventoryItem*>(this);
	VERIFY				(m_item);
	return				(&item().object());
}

CAttachableItem::~CAttachableItem		()
{
}

void CAttachableItem::reload			(LPCSTR section)
{
	if (!pSettings->line_exist(section,"attach_angle_offset"))
		return;

	Fvector							angle_offset = pSettings->r_fvector3	(section,"attach_angle_offset");
	Fvector							position_offset	= pSettings->r_fvector3	(section,"attach_position_offset");
	m_offset.setHPB					(VPUSH(angle_offset));
	m_offset.c						= position_offset;
	m_bone_name						= pSettings->r_string	(section,"attach_bone_name");
//	enable							(m_auto_attach = !!(READ_IF_EXISTS(pSettings,r_bool,section,"auto_attach",TRUE)));
	enable							(false);
#ifdef DEBUG
	m_valid							= true;
#endif
}

void CAttachableItem::OnH_A_Chield		() 
{
//	VERIFY							(m_valid);
	const CInventoryOwner			*inventory_owner = smart_cast<const CInventoryOwner*>(object().H_Parent());
	if (inventory_owner && inventory_owner->attached(&item()))
		object().setVisible			(true);
}

void CAttachableItem::renderable_Render	()
{
//	VERIFY							(m_valid);
	::Render->set_Transform			(&object().XFORM());
	::Render->add_Visual			(object().Visual());
}

void CAttachableItem::OnH_A_Independent	()
{
//	VERIFY							(m_valid);
	enable							(false/*m_auto_attach*/);
}

void CAttachableItem::enable			(bool value)
{
//	VERIFY							(m_valid);
	if (!object().H_Parent()) 
	{
		m_enabled			= value;
		return;
	}

	if (value && !enabled() && object().H_Parent()) {
		CGameObject			*game_object = smart_cast<CGameObject*>(object().H_Parent());
		CAttachmentOwner	*owner = smart_cast<CAttachmentOwner*>(game_object);
//		VERIFY				(owner);
		if (owner) {
			m_enabled			= value;
			owner->attach		(&item());
			object().setVisible	(true);
		}
	}
	
	if (!value && enabled() && object().H_Parent()) {
		CGameObject			*game_object = smart_cast<CGameObject*>(object().H_Parent());
		CAttachmentOwner	*owner = smart_cast<CAttachmentOwner*>(game_object);
//		VERIFY				(owner);
		if (owner) {
			m_enabled			= value;
			owner->detach		(&item());
			object().setVisible	(false);
		}
	}
}

bool  CAttachableItem::can_be_attached	() const
{
//	VERIFY							(m_valid);
	if (!item().m_pCurrentInventory)
		return				(false);

	if (!item().m_pCurrentInventory->IsBeltUseful())
		return				(true);

	if (item().m_eItemPlace != eItemPlaceBelt)
		return				(false);
	 
	return					(true);
}
void CAttachableItem::afterAttach		()
{
	VERIFY							(m_valid);
	object().processing_activate	();
}

void CAttachableItem::afterDetach		()
{
	VERIFY							(m_valid);
	object().processing_deactivate	();
}


#ifdef DEBUG
float ATT_ITEM_MOVE_CURR = 0.01f;
float ATT_ITEM_ROT_CURR = 0.1f;

float ATT_ITEM_MOVE_STEP = 0.001f;
float ATT_ITEM_ROT_STEP = 0.01f;

void CAttachableItem::attach_adjust_mode_keyb(int dik)
{
	if(!CAttachableItem::m_dbgItem)	return;

	bool b_move		= !!(pInput->iGetAsyncKeyState(DIK_LSHIFT));
	bool b_rot		= !!(pInput->iGetAsyncKeyState(DIK_LMENU));
	
	int axis		= -1;
	if(pInput->iGetAsyncKeyState(DIK_Z))
		axis = 0;
	else
	if(pInput->iGetAsyncKeyState(DIK_X))
		axis = 1;
	if(pInput->iGetAsyncKeyState(DIK_C))
		axis = 2;

	if(!b_move && !b_rot)	return;

	switch(dik)
	{
	case DIK_LEFT:
		{
			if(b_move)
			{
				CAttachableItem::mov(axis, ATT_ITEM_MOVE_CURR);
				Fvector _pos = CAttachableItem::get_pos_offset();
				Fvector _ang = CAttachableItem::get_angle_offset();
				Msg("[%s]", CAttachableItem::m_dbgItem->object().cNameSect().c_str());
				Msg("attach_position_offset = %3.3f, %3.3f, %3.3f", _pos.x, _pos.y, _pos.z);
				Msg("attach_angle_offset = %3.3f, %3.3f, %3.3f", _ang.x, _ang.y, _ang.z);
				Log("-----------");
			}
			else
			{
				CAttachableItem::rot(axis, ATT_ITEM_ROT_CURR);
				Fvector _pos = CAttachableItem::get_pos_offset();
				Fvector _ang = CAttachableItem::get_angle_offset();
				Msg("[%s]", CAttachableItem::m_dbgItem->object().cNameSect().c_str());
				Msg("attach_position_offset = %3.3f, %3.3f, %3.3f", _pos.x, _pos.y, _pos.z);
				Msg("attach_angle_offset = %3.3f, %3.3f, %3.3f", _ang.x, _ang.y, _ang.z);
				Log("-----------");
			}
		}break;
	case DIK_RIGHT:
			{
			if(b_move)
			{
				CAttachableItem::mov(axis, -ATT_ITEM_MOVE_CURR);
				Fvector _pos = CAttachableItem::get_pos_offset();
				Fvector _ang = CAttachableItem::get_angle_offset();
				Msg("[%s]", CAttachableItem::m_dbgItem->object().cNameSect().c_str());
				Msg("attach_position_offset = %3.3f, %3.3f, %3.3f", _pos.x, _pos.y, _pos.z);
				Msg("attach_angle_offset = %3.3f, %3.3f, %3.3f", _ang.x, _ang.y, _ang.z);
				Log("-----------");
			}
			else
			{
				CAttachableItem::rot(axis, -ATT_ITEM_ROT_CURR);
				Fvector _pos = CAttachableItem::get_pos_offset();
				Fvector _ang = CAttachableItem::get_angle_offset();
				Msg("[%s]", CAttachableItem::m_dbgItem->object().cNameSect().c_str());
				Msg("attach_position_offset = %3.3f, %3.3f, %3.3f", _pos.x, _pos.y, _pos.z);
				Msg("attach_angle_offset = %3.3f, %3.3f, %3.3f", _ang.x, _ang.y, _ang.z);
				Log("-----------");
			}
		}break;
	case DIK_PRIOR:
		{
			if(b_move)
				ATT_ITEM_MOVE_CURR += ATT_ITEM_MOVE_STEP;
			else
				ATT_ITEM_ROT_CURR += ATT_ITEM_ROT_STEP;
		}break;
	case DIK_NEXT:
		{
			if(b_move)
				ATT_ITEM_MOVE_CURR -= ATT_ITEM_MOVE_STEP;
			else
				ATT_ITEM_ROT_CURR -= ATT_ITEM_ROT_STEP;
		}break;
	case DIK_NUMPADPLUS:
		{
			if (b_move)
				ATT_ITEM_MOVE_CURR += ATT_ITEM_MOVE_STEP;
			else
				ATT_ITEM_ROT_CURR += ATT_ITEM_ROT_STEP;
		}break;
	case DIK_NUMPADMINUS:
		{
			if (b_move)
				ATT_ITEM_MOVE_CURR -= ATT_ITEM_MOVE_STEP;
			else
				ATT_ITEM_ROT_CURR -= ATT_ITEM_ROT_STEP;
		}break;
	};
}

void CAttachableItem::attach_draw_adjust_mode()
{
	if(!CAttachableItem::m_dbgItem)	return;

	string1024 _text;

	CGameFont* F		= HUD().Font().pFontDI;
	F->SetAligment		(CGameFont::alCenter);
	F->OutSetI			(0.f,-0.8f);
	F->SetColor			(0xffffffff);
	xr_sprintf(_text, "Adjusting attachable item [%s]", CAttachableItem::m_dbgItem->object().cNameSect().c_str());
	F->OutNext			(_text);
	xr_sprintf(_text, "move step  [%3.3f] rotate step  [%3.3f]", ATT_ITEM_MOVE_CURR, ATT_ITEM_ROT_CURR);
	F->OutNext			(_text);

	F->OutNext			("HOLD LShift to move. ALT to rotate");
	F->OutNext			("HOLD [Z]-x axis [X]-y axis [C]-z axis");

	F->OutNext			("RIGHT-LEFT - move. PgUP-PgDOWN - step");
	F->OutSkip			();

	Fvector _pos = CAttachableItem::get_pos_offset();
	xr_sprintf(_text, "attach_position_offset IS [%3.3f][%3.3f][%3.3f]", _pos.x, _pos.y, _pos.z);
	F->OutNext			(_text);

	Fvector _ang = CAttachableItem::get_angle_offset();
	xr_sprintf(_text, "attach_angle_offset IS [%3.3f][%3.3f][%3.3f]", _ang.x, _ang.y, _ang.z);
	F->OutNext			(_text);
}
#endif // #ifdef DEBUG