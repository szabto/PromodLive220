// general definitions

#define CHOICE_X_START			0
#define CHOICE_Y_START			34

#include "ui_mp/menustyle.inc"
#include "ui/choices_setup_common.menu"
 
#define ORIGIN_STATUS			390 64
#define MENU_FONT_COLOR2		1 1 1 0.5

#define STAT_CAC_PRIMAR stat( 7 )

//#include "ui_mp/stats_info.inc"

	menuDef	{
		name			CAC_MENU_NAME
		rect			0 0 640 480
		focuscolor		COLOR_FOCUSED
		style			WINDOW_STYLE_EMPTY
		blurWorld		7.0
		onOpen {			
			setfocus primary_weapon_selection;
		}
		onEsc {
			scriptMenuResponse "back";
		}

		// background overlay
		itemDef
		{
			style			WINDOW_STYLE_FILLED
			rect			0 0 640 480 HORIZONTAL_ALIGN_FULLSCREEN VERTICAL_ALIGN_FULLSCREEN
			backcolor		0 0 0 0.75 //0 0.05 0.15 0.5
			visible			1
			decoration
		}

		CHOICE_MENU_TITLE( "INVENTORY" )				
		// ------------------------- buttons ------------------------------
		#define BACK_OPEN ;
		#include "ui_mp/navcontrols.inc"

		#define CAC_SETUP_ACTION1 \
			play "mouse_click"; \
			execOnDvarStringValue loadout_class assault "set selected_weapon_class assault;set ui_weapon_class_selected @MPUI_ASSAULT_RIFLES"; \
			execOnDvarStringValue loadout_class specops "set selected_weapon_class specops;set ui_weapon_class_selected @MPUI_SUB_MACHINE_GUNS"; \
			execOnDvarStringValue loadout_class demolitions "set selected_weapon_class demolitions;set ui_weapon_class_selected @MPUI_SHOTGUNS"; \
			execOnDvarStringValue loadout_class sniper "set selected_weapon_class sniper;set ui_weapon_class_selected @MPUI_SNIPER_RIFLES"; \
			uiScript openMenuOnDvar loadout_class assault "ocd_popup_cac_assault"; \
			uiScript openMenuOnDvar loadout_class specops "ocd_popup_cac_SMG"; \
			uiScript openMenuOnDvar loadout_class demolitions "ocd_popup_cac_shotgun"; \
			uiScript openMenuOnDvar loadout_class sniper "ocd_popup_cac_sniper";

		CHOICE_HIGHLIGHT( 1, 1 )
		CHOICE_BUTTON_VIS_NOHI( 1, "1. Primary Weapon", CAC_SETUP_ACTION1, 1 )
		execKey 1 { CAC_SETUP_ACTION1 }

		#define CAC_SETUP_ACTION_ATTACHMENT \
			play "mouse_click"; \
			uiScript openMenuOnDvar loadout_class assault "ocd_attachment_popup_assault"; \
			uiScript openMenuOnDvar loadout_class specops "ocd_attachment_popup_SMG"; \
			uiScript openMenuOnDvar loadout_class demolitions "ocd_attachment_popup_shotgun"; \
			uiScript openMenuOnDvar loadout_class sniper "ocd_attachment_popup_sniper";

		CHOICE_HIGHLIGHT( 2, 1 )		
		CHOICE_BUTTON_VIS_NOHI( 2, "2. Primary Attachment", CAC_SETUP_ACTION_ATTACHMENT, when( dvarString( loadout_primary ) != "mp44" && dvarString( loadout_class ) != "demolitions" && dvarString( loadout_class ) != "sniper" ) )
		CHOICE_DBUTTON_VIS_NOHI( 2, "2. Primary Attachment", when( dvarString( loadout_primary ) == "mp44" || dvarString( loadout_class ) == "demolitions" || dvarString( loadout_class ) == "sniper" ) )
		execKey 2 { CAC_SETUP_ACTION_ATTACHMENT }

		// SECONDARY WEAPON/SIDE ARM BUTTON =============================================================
		#define CAC_SETUP_ACTION2 \
			play "mouse_click"; \
			open "ocd_popup_cac_secondary";

		CHOICE_HIGHLIGHT( 3, 1 )
		CHOICE_BUTTON_VIS_NOHI( 3, "3. Side Arm", CAC_SETUP_ACTION2, 1 )
		execKey 3 { CAC_SETUP_ACTION2 }


		#define CAC_SETUP_ACTION3 \
			play "mouse_click"; \
			open "ocd_popup_cac_extra";

		CHOICE_DBUTTON_VIS_NOHI( 4, "4. Grenade", when( dvarint(weap_allow_smoke_grenade) != 1 && dvarint( weap_allow_flash_grenade ) != 1 ))
		CHOICE_HIGHLIGHT( 4, 1 )
		CHOICE_BUTTON_VIS_NOHI( 4, "4. Grenade", CAC_SETUP_ACTION3, when( dvarint(weap_allow_smoke_grenade) == 1 || dvarint( weap_allow_flash_grenade ) == 1 ))
		execKey 4 { CAC_SETUP_ACTION3 }

		#define CAC_SETUP_ACTION4 \
			play "mouse_click"; \
			open "ocd_popup_cac_camo";

		CHOICE_HIGHLIGHT( 5, 1 )
		CHOICE_BUTTON_VIS_NOHI( 5, "5. Camo", CAC_SETUP_ACTION4, 1 )
		execKey 5 { CAC_SETUP_ACTION4 }

		#define CAC_SETUP_ACTIONGO \
			play "mouse_click"; \
			scriptMenuResponse "go";

		CHOICE_HIGHLIGHT( 6, 1 )
		CHOICE_BUTTON_VIS_NOHI( 6, "6. Start!", CAC_SETUP_ACTIONGO, 1 )
		execKey 6 { CAC_SETUP_ACTIONGO }

		#define STAT_CAC_PRIMARY				tableLookup("mp/statstable.csv", 4, dvarString( loadout_primary ), 0)
		#define STAT_CAC_PRIMARY_ATTACHMENT		tableLookup("mp/attachmentTable.csv", 4, dvarString( loadout_primary_attachment ), 9)
		#define STAT_CAC_SECONDARY				tableLookup("mp/statstable.csv", 4, dvarString( loadout_secondary ), 0)
		#define STAT_CAC_SECONDARY_ATTACHMENT	tableLookup("mp/attachmentTable.csv", 4, dvarString( loadout_secondary_attachment ), 9)
		#define STAT_CAC_SPECIAL_GRENADE		tableLookup("mp/statstable.csv", 4, dvarString( loadout_grenade ), 0)
		#define STAT_CAC_CAMO					tableLookup("mp/attachmentTable.csv", 4, dvarString( loadout_camo ), 11)
		
		#include "ui_mp/cac_loadout_ingame.inc"

		#include "ui/safearea.menu"
	}

	// close all 2nd and 3rd layer popups on end action
	#define PREPROC_ATTACH_CLOSEALL \
	close "ocd_popup_cac_primary"; \
	close "ocd_popup_cac_secondary"; \
	close "ocd_popup_cac_assault"; \
	close "ocd_popup_cac_SMG"; \
	close "ocd_popup_cac_sniper"; \
	close "ocd_popup_cac_shotgun"; \
	close "popup_cac_template"; \
	close "ocd_attachment_popup_assault"; \
	close "ocd_attachment_popup_SMG"; \
	close "ocd_attachment_popup_LMG"; \
	close "ocd_attachment_popup_sniper"; \
	close "ocd_attachment_popup_shotgun"; \
	close "ocd_attachment_popup_pistol"; \
	close "ocd_popup_cac_camo"; \
	close "ocd_attachment_popup_fake";	
	
	// including weapon data
	#include "ui_mp/weaponinfo.menu"
	
#include "ui_mp/popupstyle.inc"	
#include "ui/choices_setup_popmenu.menu"

#undef CHOICE_SIZE_X
#define CHOICE_SIZE_X			216

#undef NEW_X_OFFSET			
#define NEW_X_OFFSET	(0-CHOICE_SIZE_X)

#undef NEW_Y_OFFSET			
#define NEW_Y_OFFSET	(0-2)

	// ====================================================================================================
	// primary weapon selection ===========================================================================
	// ====================================================================================================
	#define LOCAL_WEAPON_INFO_WINDOW( highlight_dvar ) \
		/* weapon information side frame*/ \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH-6) -4 280 CHOICE_POPUP_HEIGHT( 7 ) CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "white", CHOICE_POPUP_BORDER_COLOR, 1, 2, CHOICE_POPUP_BORDER_COLOR visible when( dvarString(ui_inside_popup) != "attachment" && dvarString(ui_inside_popup) != "camo" ); ) \
		LOADOUT_PLATING_RAW( CHOICE_POPUP_WIDTH 8, -2, 0, 280, (CHOICE_POPUP_HEIGHT( 7 )-4), CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN visible when( dvarString(ui_inside_popup) != "attachment" && dvarString(ui_inside_popup) != "camo" );, 0, 0 )\
		/* weapon image*/ \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH+6) 30 256 48 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "gradient_bottom", 1 1 1 0.3, 0, 2, CHOICE_POPUP_BORDER_COLOR visible when( dvarString(ui_inside_popup) != "attachment" && dvarString(ui_inside_popup) != "camo" ); ) \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH+72) -6 180 90 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, tablelookup("mp/statsTable.csv",4,dvarString(highlight_dvar),6), 1 1 1 1, 0, 2, CHOICE_POPUP_BORDER_COLOR visible when( dvarString(ui_inside_popup) != "attachment" && dvarString(ui_inside_popup) != "camo" ); ) \
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 80 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@"+tablelookup("mp/statstable.csv",4,dvarString(highlight_dvar),7), TEXTSIZE_SMALL, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, CHOICE_TEXTCOLOR visible 1; )\
		/* weapon title*/\
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 58 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@"+tablelookup("mp/statstable.csv",4,dvarString(highlight_dvar),3), TEXTSIZE_DEFAULT, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, COLOR_TITLE visible when( dvarString(ui_inside_popup) != "attachment" && dvarString(ui_inside_popup) != "camo" ); ) \ 


	#define LOCAL_PRIMARY_WEAPON_ACTION( suffix, weapClass, weapRef ) \
		play "mouse_click"; \
		scriptMenuResponse "loadout_primary:"weapRef;\
		close self;

	/*#define LOCAL_PRIMARY_WEAPON_ACTION3( suffix, weapClass, weapRef ) \
		play "mouse_click"; \
		scriptMenuResponse "loadout_primary:"weapRef;\
		close self;*/
		
	#define WI_FOCUS_ACTION( weaponRef ) \
		execOnDvarStringValue "weap_allow_"weaponRef 0 "set ui_primary_hl_unlocked 0";\
		execOnDvarStringValue "weap_allow_"weaponRef 1 "set ui_primary_hl_unlocked 1";\
		exec "set ui_primary_highlighted "weaponRef;
	
	// hacked to hide the second primary if same weapon is selected in first primary, change weapon description to "Already selected"
	#define LOCAL_WEAPON_ITEM( suffix, itemNum, weaponName, weaponClass, weaponRef )\
		CHOICE_DBUTTON_VIS_NOHI( itemNum, weaponName, when(!dvarBool( "weap_allow_"weaponRef )) ) \
		CHOICE_HIGHLIGHT( itemNum, when(dvarBool( "weap_allow_"weaponRef )) ) \
		CHOICE_BUTTON_FOCUS_VIS_NOHI( itemNum, weaponName, LOCAL_PRIMARY_WEAPON_ACTION( suffix, weaponClass, weaponRef ), \
		WI_FOCUS_ACTION( weaponRef ), ;, when(dvarBool( "weap_allow_"weaponRef )); ) \
		execKey itemNum { LOCAL_PRIMARY_WEAPON_ACTION( suffix, weaponClass, weaponRef ) }
		
	/*#define LOCAL_WEAPON_ITEM2( suffix, itemNum, weaponName, weaponClass, weaponRef )\
		CHOICE_DBUTTON_VIS_NOHI( itemNum, weaponName, when(!dvarBool( "weap_allow_"weaponRef )) ) \
		CHOICE_HIGHLIGHT( itemNum, when(dvarBool( "weap_allow_"weaponRef )) ) \
		CHOICE_BUTTON_FOCUS_VIS_NOHI( itemNum, weaponName, LOCAL_PRIMARY_WEAPON_ACTION3( suffix, weaponClass, weaponRef ), \
		WI_FOCUS_ACTION( weaponRef ), ;, when( dvarBool( "weap_allow_"weaponRef ) ); ) \
		execKey itemNum { LOCAL_PRIMARY_WEAPON_ACTION( suffix, weaponClass, weaponRef ) }*/

	// primary weapon class dropdown
	menuDef
	{
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_popup_cac_primary", 5, (CHOICE_X( 1 )-2), (CHOICE_Y( 1 )-4), ;, execnow "set ui_inside_popup weapon_class; set ui_show_preview 1";, 1 )
		onClose{	execnow "set ui_show_preview 0; set ui_primary_highlighted 0; set ui_attachment_highlighted 0";	}
		
		#define LOCAL_WEAPON_CLASS( itemNum, ptext, plabel ) \
			CHOICE_BUTTON_EX( itemNum, plabel, play "mouse_click"; execnow "set selected_weapon_class "ptext"; set ui_weapon_class_selected "plabel; open "ocd_popup_cac_"ptext;, name ptext )

		LOCAL_WEAPON_CLASS( 1, "assault", "@MPUI_ASSAULT_RIFLES" )
		LOCAL_WEAPON_CLASS( 2, "SMG", "@MPUI_SUB_MACHINE_GUNS" )
		LOCAL_WEAPON_CLASS( 3, "shotgun", "@MPUI_SHOTGUNS" )
		LOCAL_WEAPON_CLASS( 4, "sniper", "@MPUI_SNIPER_RIFLES" )	
	}

	// hackaround to work for PC's floating mouse unfocusing
	#undef  UI_FOCUSFIRST
	#define UI_FOCUSFIRST "ui_primary_highlighted"
		
	// primary weapon items
	#define LOCAL_MASTER_WEAPON_GROUP( suffix, pos, y_offset )\
	menuDef	{\
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_popup_cac_assault"suffix, 7, (CHOICE_X( pos )-2), (CHOICE_Y( pos )+y_offset), ;, execnow "set "UI_FOCUSFIRST" "REF_M16"; set ui_inside_popup assault";, 0 )\
		LOCAL_WEAPON_INFO_WINDOW( "ui_primary_highlighted" )\
		LOCAL_WEAPON_ITEM( suffix, 1, "1. M16A4", "assault", REF_M16 )\
		LOCAL_WEAPON_ITEM( suffix, 2, "2. AK-47", "assault", REF_AK47 )\
		LOCAL_WEAPON_ITEM( suffix, 3, "3. M4 Carbine", "assault", REF_M4 )\
		LOCAL_WEAPON_ITEM( suffix, 4, "4. G3", "assault", REF_G3 )\
		LOCAL_WEAPON_ITEM( suffix, 5, "5. G36C", "assault", REF_G36C )\
		LOCAL_WEAPON_ITEM( suffix, 6, "6. M14", "assault", REF_M14 )\
		LOCAL_WEAPON_ITEM( suffix, 7, "7. MP44", "assault", REF_MP44 )\
	}\
	menuDef	{\
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_popup_cac_SMG"suffix, 7, (CHOICE_X( pos )-2), (CHOICE_Y( pos )+y_offset), ;, execnow "set "UI_FOCUSFIRST" "REF_MP5";set ui_inside_popup smg";, 0 )\
		LOCAL_WEAPON_INFO_WINDOW( "ui_primary_highlighted" )\
		LOCAL_WEAPON_ITEM( suffix, 1, "1. MP5", "SMG", REF_MP5 )\
		LOCAL_WEAPON_ITEM( suffix, 2, "2. Mini-Uzi", "SMG", REF_UZI )\
		LOCAL_WEAPON_ITEM( suffix, 3, "3. AK-74u", "SMG", REF_AK74U )\
	}\
	menuDef	{\
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_popup_cac_shotgun"suffix, 7, (CHOICE_X( pos )-2), (CHOICE_Y( pos )+y_offset), ;, execnow "set "UI_FOCUSFIRST" "REF_WINCHESTER1200"; set ui_inside_popup shotgun";, 0 )\
		LOCAL_WEAPON_INFO_WINDOW( "ui_primary_highlighted" )\
		LOCAL_WEAPON_ITEM( suffix, 1, "1. W1200", "shotgun", REF_WINCHESTER1200 )\
		LOCAL_WEAPON_ITEM( suffix, 2, "2. M1014", "shotgun", REF_BENELLIM4 )\
	}\
	menuDef	{\
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_popup_cac_sniper"suffix, 7, (CHOICE_X( pos )-2), (CHOICE_Y( pos )+y_offset), ;, execnow "set "UI_FOCUSFIRST" "REF_M40A3"; set ui_inside_popup sniper";, 0 )\
		LOCAL_WEAPON_INFO_WINDOW( "ui_primary_highlighted" )\
		LOCAL_WEAPON_ITEM( suffix, 1, "1. M40A3", "sniper", REF_M40A3 )\
		LOCAL_WEAPON_ITEM( suffix, 2, "2. R700", "sniper", REF_REMINGTON700 )\
	}
	

	// primary and second primary weapon selection popup menus
	LOCAL_MASTER_WEAPON_GROUP( "", 1, -28 )
	
	// ====================================================================================================
	// primary and second primary attachment selection ====================================================
	// ====================================================================================================
	#define LOCAL_ATTACHMENT_INFO_WINDOW( parentDvar ) \
		/* attachment information side frame*/ \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH-6) -4 280 CHOICE_POPUP_HEIGHT( 7 ) CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "white", CHOICE_POPUP_BORDER_COLOR, 1, 2, CHOICE_POPUP_BORDER_COLOR visible when( dvarString(ui_inside_popup) != "camo" ); ) \
		LOADOUT_PLATING_RAW( CHOICE_POPUP_WIDTH 8, -2, 0, 280, (CHOICE_POPUP_HEIGHT( 7 )-4), CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN visible when( dvarString(ui_inside_popup) != "camo" );, 0, 0 ) \
		/* attachment image*/ \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH+6) 30 256 48 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "gradient_bottom", 1 1 1 0.3, 0, 2, CHOICE_POPUP_BORDER_COLOR visible when( dvarString(ui_inside_popup) != "camo" ); ) \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH+182) 6 64 64 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, tablelookup("mp/attachmentTable.csv",4,dvarString(ui_attachment_highlighted),6), 1 1 1 1, 0, 2, CHOICE_POPUP_BORDER_COLOR visible when( dvarString(ui_inside_popup) != "camo" ); ) \
		/* attachment title*/\
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 58 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@"+tablelookup("mp/attachmentTable.csv",4,dvarString(ui_attachment_highlighted),3), TEXTSIZE_DEFAULT, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, COLOR_TITLE visible when( dvarString(ui_inside_popup) != "camo" ); ) \
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 80 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@"+tablelookup("mp/attachmentTable.csv",4,dvarString(ui_attachment_highlighted),7), TEXTSIZE_SMALL, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, CHOICE_TEXTCOLOR visible 1; )\

	#define LOCAL_ATTACHMENT_ACTION( attachmentDvar, attachmentName, paction, groupArg ) \
		scriptMenuResponse "loadout_primary_attachment:"groupArg":"attachmentName;\
		close self;
		
	#define LOCAL_ATTACHMENT_ACTION2( attachmentDvar, attachmentName, paction, groupArg ) \
		scriptMenuResponse "loadout_secondary_attachment:"groupArg":"attachmentName;\
		PREPROC_ATTACH_CLOSEALL

	#define AI_FOCUS_ACTION( groupArg, weaponRef ) \
		execOnDvarStringValue "attach_allow_"groupArg"_"weaponRef 0 "set ui_attachment_hl_unlocked 1";\
		execOnDvarStringValue "attach_allow_"groupArg"_"weaponRef 1 "set ui_attachment_hl_unlocked 1";\
		exec "set ui_attachment_highlighted "weaponRef;

	#define LOCAL_ATTACHMENT_ITEM( itemNum, p_setstat, groupArg ,p_numref, pname, paction, ptype, statDvar, bitMask, text )\
		CHOICE_DBUTTON_VIS_NOHI( itemNum, text, when( !dvarBool( "attach_allow_"groupArg"_"pname ) ); ) \
		CHOICE_HIGHLIGHT( itemNum, when( ptype == "primary" && dvarBool( "attach_allow_"groupArg"_"pname ) ) ) \
		CHOICE_BUTTON_FOCUS_VIS_NOHI( itemNum, text, LOCAL_ATTACHMENT_ACTION( statDvar, pname, paction, groupArg );, AI_FOCUS_ACTION(groupArg,pname), ;, when( ptype == "primary" && dvarBool( "attach_allow_"groupArg"_"pname ) ); ) \
		CHOICE_BUTTON_FOCUS_VIS_NOHI( itemNum, text, LOCAL_ATTACHMENT_ACTION2( statDvar, pname, paction, groupArg );, AI_FOCUS_ACTION(groupArg,pname), ;, when( ptype == "secondary" && dvarBool( "attach_allow_"groupArg"_"pname ) ); ) \
		execKey itemNum { LOCAL_ATTACHMENT_ACTION( statDvar, pname, paction, groupArg ) }

	#define LOCAL_ATTACHMENT_ITEM_PISTOL( itemNum, p_setstat, groupArg ,p_numref, pname, paction, ptype, statDvar, bitMask, text )\
		CHOICE_DBUTTON_VIS_NOHI( itemNum, text, when( !dvarBool( "attach_allow_"groupArg"_"pname ) ); ) \
		CHOICE_HIGHLIGHT( itemNum, when( ptype == "primary" && dvarBool( "attach_allow_"groupArg"_"pname ) ) ) \
		CHOICE_BUTTON_FOCUS_VIS_NOHI( itemNum, text, LOCAL_ATTACHMENT_ACTION( statDvar, pname, paction, groupArg );, AI_FOCUS_ACTION(groupArg,pname), ;, when( ptype == "primary" && dvarBool( "attach_allow_"groupArg"_"pname ) ); ) \
		CHOICE_BUTTON_FOCUS_VIS_NOHI( itemNum, text, LOCAL_ATTACHMENT_ACTION2( statDvar, pname, paction, groupArg );, AI_FOCUS_ACTION(groupArg,pname), ;, when( ptype == "secondary" && dvarBool( "attach_allow_"groupArg"_"pname ) ); ) \
		execKey itemNum { LOCAL_ATTACHMENT_ACTION2( statDvar, pname, paction, groupArg ) }

	// hackaround to work for PC's floating mouse unfocusing
	#undef  UI_FOCUSFIRST
	#define UI_FOCUSFIRST "ui_attachment_highlighted"
		
	// primary and second primary attachment items
	#define LOCAL_MASTER_ATTACHMENT_GROUP( stat_slot, suffix, pos, ptype, y_offset, statDvar )\
	menuDef { \
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_attachment_popup_assault"suffix, 7, (CHOICE_X( pos )-2), (CHOICE_Y( pos )+24+y_offset), ;, execnow "set "UI_FOCUSFIRST" "REF_ATTACHMENT_NONE"; set ui_inside_popup attachment";, 0 )\
		onClose{execnow "set ui_inside_popup 0";} \
		LOCAL_ATTACHMENT_INFO_WINDOW( "loadout_"ptype )\
		LOCAL_ATTACHMENT_ITEM( 1, stat_slot, "assault", NUM_NONE, "none", ;, ptype, statDvar, 0, "1. None" )\
		LOCAL_ATTACHMENT_ITEM( 2, stat_slot, "assault", NUM_SUPPRESSOR, "silencer", ;, ptype, statDvar, SILENCER_NEW_BITMASK, "2. Silencer" )\
	}\
	menuDef	{ \
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_attachment_popup_SMG"suffix, 7, (CHOICE_X( pos )-2), (CHOICE_Y( pos )+24+y_offset), ;, execnow "set "UI_FOCUSFIRST" "REF_ATTACHMENT_NONE"; set ui_inside_popup attachment";, 0 )\
		onClose{execnow "set ui_inside_popup 0";} \
		LOCAL_ATTACHMENT_INFO_WINDOW( "loadout_"ptype )\
		LOCAL_ATTACHMENT_ITEM( 1, stat_slot, "specops", NUM_NONE, "none", ;, ptype, statDvar, 0, "1. None" )\
		LOCAL_ATTACHMENT_ITEM( 2, stat_slot, "specops", NUM_SUPPRESSOR, "silencer", ;, ptype, statDvar, SILENCER_NEW_BITMASK, "2. Silencer" )\
	}

	menuDef	{ 
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_attachment_popup_fake", 7, (CHOICE_X( 1 )-2), (CHOICE_Y( 1 ) + 44), ;, ;, 0 )
		LOCAL_ATTACHMENT_INFO_WINDOW( "loadout_primary" )
		PREPROC_SHADER_DRAW_ALIGNED( 0 -24 (CHOICE_POPUP_WIDTH-4) 22 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "white", 0.15 0.15 0.17 1, 0, 2, CHOICE_POPUP_BORDER_COLOR )
		PREPROC_TEXT_DRAW_ALIGNED_EXP( 8 -24 (CHOICE_POPUP_WIDTH-4) 22 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, -32 0, "@"+tablelookup("mp/statstable.csv",4,dvarString(loadout_primary),3), TEXTSIZE_SMALL, 0, 0, ITEM_ALIGN_MIDDLE_RIGHT, CHOICE_TEXTCOLOR )
		/* pointer icon */
		PREPROC_SHADER_DRAW_ALIGNED( 200 -16 16 8 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "hitech_arrow_right", 0.55 0.95 0.55 0.7, 0, 2, CHOICE_POPUP_BORDER_COLOR )
	}

	// side arm attachment selection ======================================================================
	menuDef	{ /* pistol attachments*/
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_attachment_popup_pistol", 7, (CHOICE_X( 2 )-2), (CHOICE_Y( 2 )+24), ;, execnow "set "UI_FOCUSFIRST" "REF_ATTACHMENT_NONE"; set ui_inside_popup attachment";, 0 )
		onClose{execnow "set ui_inside_popup 0";}
		LOCAL_ATTACHMENT_INFO_WINDOW( "loadout_secondary" )
		LOCAL_ATTACHMENT_ITEM_PISTOL( 1, CAC_SECONDARY_ATTACHMENT, "pistol", NUM_NONE, "none", ;, "secondary", "ui_secondary_weapon", 0, "1. None" )
		LOCAL_ATTACHMENT_ITEM_PISTOL( 2, CAC_SECONDARY_ATTACHMENT, "pistol", NUM_SUPPRESSOR, "silencer", ;, "secondary", "ui_secondary_weapon", SILENCER_NEW_BITMASK, "2. Silencer" )
	}
	
	// primary and second primary attachment popup menus
	LOCAL_MASTER_ATTACHMENT_GROUP( CAC_PRIMARY_ATTACHMENT, "", 1, "primary", -28, "loadout_primary_attachment" )

	// ====================================================================================================
	// side arm selection ===============================================================================
	// ====================================================================================================
	#define LOCAL_SIDEARM_INFO_WINDOW( highlight_dvar ) \
		/* sidearm information side frame*/ \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH-6) -4 280 CHOICE_POPUP_HEIGHT( 7 ) CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "white", CHOICE_POPUP_BORDER_COLOR, 1, 2, CHOICE_POPUP_BORDER_COLOR visible when( dvarString(ui_inside_popup) != "attachment" ); ) \
		LOADOUT_PLATING_RAW( CHOICE_POPUP_WIDTH 8, -2, 0, 280, (CHOICE_POPUP_HEIGHT( 7 )-4), CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN visible when( dvarString(ui_inside_popup) != "attachment" );, 0, 0 )\
		/* sidearm image*/ \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH+6) 30 256 48 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "gradient_bottom", 1 1 1 0.3, 0, 2, CHOICE_POPUP_BORDER_COLOR visible when( dvarString(ui_inside_popup) != "attachment" ); ) \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH+138) -12 90 90 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, tablelookup("mp/statsTable.csv",4,dvarString(highlight_dvar),6), 1 1 1 1, 0, 2, CHOICE_POPUP_BORDER_COLOR visible when( dvarString(ui_inside_popup) != "attachment" ); ) \
		/* sidearm title*/\
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 58 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@"+tablelookup("mp/statstable.csv",4,dvarString(highlight_dvar),3), TEXTSIZE_DEFAULT, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, COLOR_TITLE visible when( dvarString(ui_inside_popup) != "attachment" ); ) \
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 80 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@"+tablelookup("mp/statstable.csv",4,dvarString(highlight_dvar),7), TEXTSIZE_SMALL, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, CHOICE_TEXTCOLOR visible when( dvarBool( ui_sidearm_hl_unlocked ) ); )\

	#define LOCAL_SIDEARM_ACTION( pstat, weaponRef ) \
			play "mouse_click"; \
			scriptMenuResponse "loadout_secondary:"weaponRef;\
			PREPROC_ATTACH_CLOSEALL

	#define LOCAL_SIDEARM_ACTION2( pstat, weaponRef ) \		
			play "mouse_click"; \
			scriptMenuResponse "loadout_secondary:"weaponRef;\
			uiScript openMenuOnDvar "selected_weapon_class" pistol "ocd_attachment_popup_pistol";
	
	#define SI_FOCUS_ACTION( weaponRef ) \
		execOnDvarStringValue "weap_allow_"weaponRef 0 "set ui_sidearm_hl_unlocked 0";\
		execOnDvarStringValue "weap_allow_"weaponRef 1 "set ui_sidearm_hl_unlocked 1";\
		exec "set ui_sidearm_highlighted "weaponRef;


	#define LOCAL_SIDEARM_ITEM( itemNum, weaponName, weaponStat, weaponRef, highlight_dvar )\
		CHOICE_DBUTTON_VIS_NOHI( itemNum, weaponName, when(!dvarBool( "weap_allow_"weaponRef )) ) \
		CHOICE_HIGHLIGHT( itemNum, when(dvarBool( "weap_allow_"weaponRef )) ) \
		CHOICE_BUTTON_FOCUS_VIS_NOHI( itemNum, weaponName, LOCAL_SIDEARM_ACTION2( weaponStat, weaponRef ), \
		SI_FOCUS_ACTION( weaponRef ), ;, when(dvarBool( "weap_allow_"weaponRef )); ) \
		execKey itemNum { LOCAL_SIDEARM_ACTION2( weaponStat, weaponRef ) }

	#define LOCAL_SIDEARM_ITEM_DEF( itemNum, weaponName, weaponStat, weaponRef, highlight_dvar )\
		CHOICE_DBUTTON_VIS_NOHI( itemNum, weaponName, when(!dvarBool( "weap_allow_"weaponRef )) ) \
		CHOICE_HIGHLIGHT( itemNum, when(dvarBool( "weap_allow_"weaponRef )) ) \
		CHOICE_BUTTON_FOCUS_VIS_NOHI( itemNum, weaponName, LOCAL_SIDEARM_ACTION( weaponStat, weaponRef ), \
		SI_FOCUS_ACTION( weaponRef ), ;, when(dvarBool( "weap_allow_"weaponRef )); ) \
		execKey itemNum { LOCAL_SIDEARM_ACTION( weaponStat, weaponRef ) }

	// side arm selection popup menu
	
	// hackaround to work for PC's floating mouse unfocusing
	#undef  UI_FOCUSFIRST
	#define UI_FOCUSFIRST "ui_sidearm_highlighted"
	
	menuDef	
	{
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_popup_cac_secondary", 7, (CHOICE_X( 2 )-2), (CHOICE_Y( 2 )), ;, execnow "set "UI_FOCUSFIRST" "REF_M9BERETTA"; set selected_weapon_class pistol; set ui_inside_popup pistol";, 1 )
		onClose{execnow "set ui_inside_popup 0";}
		LOCAL_SIDEARM_INFO_WINDOW( "ui_sidearm_highlighted" )
		LOCAL_SIDEARM_ITEM_DEF( 1, "1. Gold Desert Eagle", STAT_PISTOL_DESERTEAGLEGOLD, REF_DESERTEAGLEGOLD, "ui_sidearm_highlighted" )
		LOCAL_SIDEARM_ITEM_DEF( 2, "2. Desert Eagle", STAT_PISTOL_DESERTEAGLE, REF_DESERTEAGLE, "ui_sidearm_highlighted" )
		LOCAL_SIDEARM_ITEM( 3, "3. M1911 .45", STAT_PISTOL_COLT45, REF_COLT45, "ui_sidearm_highlighted" )
		LOCAL_SIDEARM_ITEM( 4, "4. USP .45", STAT_PISTOL_USP, REF_USP, "ui_sidearm_highlighted" )
		LOCAL_SIDEARM_ITEM( 5, "5. M9", STAT_PISTOL_M9BERETTA, REF_M9BERETTA, "ui_sidearm_highlighted" )
	}

	// ====================================================================================================
	// camo skin selection ================================================================================
	// ====================================================================================================
	#define LOCAL_CAMO_INFO_WINDOW( highlight_dvar ) \
		/* camo information side frame*/ \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH-6) -4 280 CHOICE_POPUP_HEIGHT( 7 ) CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "white", CHOICE_POPUP_BORDER_COLOR, 1, 2, CHOICE_POPUP_BORDER_COLOR ) \
		LOADOUT_PLATING_RAW( CHOICE_POPUP_WIDTH 8, -2, 0, 280, (CHOICE_POPUP_HEIGHT( 7 )-4), CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0, 0 )\
		/* camo image*/ \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH+6) 30 256 48 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "gradient_bottom", 1 1 1 0.3, 0, 2, CHOICE_POPUP_BORDER_COLOR ) \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH+184) 0 64 64 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, tablelookup("mp/attachmentTable.csv",4,dvarString(highlight_dvar),6), 1 1 1 0.75, 1, 7, 0.2 0.2 0.225 1 ) \
		/* camo title*/\
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 58 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@"+tablelookup("mp/attachmenttable.csv",4,dvarString(highlight_dvar),3), TEXTSIZE_DEFAULT, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, COLOR_TITLE ) \
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 80 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@"+tablelookup("mp/attachmenttable.csv",4,dvarString(highlight_dvar),7), TEXTSIZE_SMALL, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, CHOICE_TEXTCOLOR visible when( 1 ); )\

	#define LOCAL_CAMO_ACTION( camoRef ) \
			play "mouse_click"; \
			scriptMenuResponse "loadout_camo:"camoRef;\
			setdvar loadout_camo camoRef;\
			PREPROC_ATTACH_CLOSEALL

	#define LOCAL_CAMO_ITEM( itemNum, camoName, pnum, camoRef, highlight_dvar, bitMask, visArg )\
		CHOICE_HIGHLIGHT( itemNum, visArg ) \
		CHOICE_BUTTON_FOCUS_VIS_NOHI( itemNum, camoName, LOCAL_CAMO_ACTION( camoRef );, execnow "set "highlight_dvar" "camoRef;, ;, visArg )  \
		execKey itemNum { LOCAL_CAMO_ACTION( camoRef ) }

	#define LOCAL_CAMO_ITEM_G( itemNum, camoName, vis)\
		CHOICE_DBUTTON_VIS_NOHI( itemNum, camoName, vis ) 

	// hackaround to work for PC's floating mouse unfocusing
	#undef  UI_FOCUSFIRST
	#define UI_FOCUSFIRST "ui_camo_highlighted"
	
	// camo skin selection for primary weapon popup menu
	#define LOCAL_CAMO_GROUP( prefix, onLeave )\
	menuDef	\
	{\
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_popup_cac_camo"prefix, 7, (CHOICE_X( 1 )-2), (CHOICE_Y( 1 )+68), ;, execnow "set "UI_FOCUSFIRST" "REF_CAMO_NONE"; set ui_inside_popup camo";, 0 )\
		onClose{onLeave;} \
		LOCAL_CAMO_INFO_WINDOW( "ui_camo_highlighted" )\
		LOCAL_CAMO_ITEM( 1, "1. None", CAMO_NONE, REF_CAMO_NONE, "ui_camo_highlighted", 0, 1 )\
		LOCAL_CAMO_ITEM( 2, "2. Desert", CAMO_BROCKHUARD, REF_BROCKHUARD, "ui_camo_highlighted", DESERT_NEW_BITMASK, 1 )\
		LOCAL_CAMO_ITEM( 3, "3. Woodland", CAMO_BUSHDWELLER, REF_BUSHDWELLER, "ui_camo_highlighted", WOODLAND_NEW_BITMASK, 1 )\
		LOCAL_CAMO_ITEM( 4, "4. Digital", CAMO_BLACKWHITEMARPAT, REF_BLACKWHITEMARPAT, "ui_camo_highlighted", DIGITAL_NEW_BITMASK, 1 )\
		LOCAL_CAMO_ITEM( 5, "5. Red Tiger", CAMO_TIGERRED, REF_TIGERRED, "ui_camo_highlighted", REDTIGER_NEW_BITMASK, 1 )\
		LOCAL_CAMO_ITEM( 6, "6. Blue Tiger", CAMO_STAGGER, REF_STAGGER, "ui_camo_highlighted", BLUETIGER_NEW_BITMASK, 1 )\
		LOCAL_CAMO_ITEM( 7, "7. Golden", CAMO_GOLDEN, REF_GOLDEN, "ui_camo_highlighted", GOLDEN_NEW_BITMASK, when( dvarString( loadout_primary ) == "ak47" || dvarString( loadout_primary ) == "m1014" || dvarString( loadout_primary ) == "mini_uzi" ) )\
		LOCAL_CAMO_ITEM_G( 7, "7. Golden", when( dvarString( loadout_primary ) != "ak47" && dvarString( loadout_primary ) != "m1014" && dvarString( loadout_primary ) != "mini_uzi" ) )\
	}
	// camo skin selection for primary weapon popup menu
	LOCAL_CAMO_GROUP( "", execnow "set ui_inside_popup attachment" )
	// camo skin selection for primary weapon without attachments
	LOCAL_CAMO_GROUP( "2", execnow "set ui_inside_popup 0"; close "ocd_attachment_popup_fake" )
	
	
	// ====================================================================================================
	// special grenade selection ==========================================================================
	// ====================================================================================================
	#define LOCAL_SGRENADE_INFO_WINDOW( highlight_dvar ) \
		/* special grenade information side frame*/ \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH-6) -4 280 CHOICE_POPUP_HEIGHT(6) CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "white", CHOICE_POPUP_BORDER_COLOR, 1, 2, CHOICE_POPUP_BORDER_COLOR ) \
		LOADOUT_PLATING_RAW( CHOICE_POPUP_WIDTH 8, -2, 0, 280, (CHOICE_POPUP_HEIGHT(6)-4), CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN visible when( dvarString(ui_inside_popup) != "attachment" );, 0, 0 )\
		/* special grenade image*/ \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH+6) 6 256 48 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "gradient_bottom", 1 1 1 0.3, 0, 2, CHOICE_POPUP_BORDER_COLOR visible when( dvarString(ui_inside_popup) != "attachment" ); ) \
		PREPROC_SHADER_DRAW_ALIGNED( (CHOICE_POPUP_WIDTH+178) -6 64 64 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, tablelookup("mp/statsTable.csv",4,dvarString(highlight_dvar),6), 1 1 1 1, 0, 2, CHOICE_POPUP_BORDER_COLOR ) \
		/* special grenade title*/\
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 34 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@"+tablelookup("mp/statstable.csv",4,dvarString(highlight_dvar),3), TEXTSIZE_DEFAULT, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, COLOR_TITLE ) \
		/* special grenade desc unlocked*/\
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 56 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@"+tablelookup("mp/statstable.csv",4,dvarString(highlight_dvar),7), TEXTSIZE_SMALL, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, CHOICE_TEXTCOLOR \
		visible when( ( ( dvarString(ui_sgrenade_highlighted)=="smoke_grenade") && (dvarString( loadout_perk1 )=="specialty_specialgrenade") ) == 0 ); )\
		PREPROC_TEXT_DRAW_ALIGNED_EXP( (CHOICE_POPUP_WIDTH+10) 56 256 20 CHOICE_HORIZONTAL_ALIGN CHOICE_VERTICAL_ALIGN, 0 0, "@MENU_DISABLED", TEXTSIZE_SMALL, 0, 0, ITEM_ALIGN_MIDDLE_LEFT, COLOR_TITLE \
		visible when( (dvarString(ui_sgrenade_highlighted)=="smoke_grenade") && (dvarString( loadout_perk1 )=="specialty_specialgrenade") ); )

	#define LOCAL_SGRENADE_ACTION( weaponRef ) \
			play "mouse_click"; \
			scriptMenuResponse "loadout_grenade:"weaponRef;\
			close "ocd_popup_cac_extra"
		
	#define LOCAL_SGRENADE_ITEM( itemNum, weaponName, weaponStat, weaponRef, highlight_dvar )\
		CHOICE_DBUTTON_VIS_NOHI( itemNum, weaponName, when( !(( weaponRef == REF_SMOKE_X1 && (dvarString(loadout_perk1)=="specialty_specialgrenade") ) == 0 && dvarBool("weap_allow_"weaponRef) ))) \
		CHOICE_HIGHLIGHT( itemNum, when( ( weaponRef == REF_SMOKE_X1 && (dvarString(loadout_perk1)=="specialty_specialgrenade") ) == 0 && dvarBool("weap_allow_"weaponRef) ) ) \
		CHOICE_BUTTON_FOCUS_VIS_NOHI( itemNum, weaponName, LOCAL_SGRENADE_ACTION( weaponRef ), \
		execnow "set "highlight_dvar" "weaponRef;, ;, when( ( weaponRef == REF_SMOKE_X1 && (dvarString(loadout_perk1)=="specialty_specialgrenade") ) == 0 && dvarBool("weap_allow_"weaponRef) ); ) \
		execKey itemNum { LOCAL_SGRENADE_ACTION( weaponRef ) }
	
	// hackaround to work for PC's floating mouse unfocusing
	#undef  UI_FOCUSFIRST
	#define UI_FOCUSFIRST "ui_sgrenade_highlighted"
	
	// special grenade selection popup menus
	menuDef	
	{
		IMPROVED_POPUP_SETUP_ONOPEN( "ocd_popup_cac_extra", 6, (CHOICE_X( 3 )-2), (CHOICE_Y( 3 )+4), ;, execnow "set "UI_FOCUSFIRST" "REF_FLASH_X1"; set ui_inside_popup sgrenade";, 1 )
		onClose{ execnow "set ui_inside_popup 0"; }
		LOCAL_SGRENADE_INFO_WINDOW( "ui_sgrenade_highlighted" )
		LOCAL_SGRENADE_ITEM( 1, "1. Flash", STAT_FLASH_X1, REF_FLASH_X1, "ui_sgrenade_highlighted" )
		LOCAL_SGRENADE_ITEM( 2, "2. Smoke", STAT_SMOKE_X1, REF_SMOKE_X1, "ui_sgrenade_highlighted" )
	}
