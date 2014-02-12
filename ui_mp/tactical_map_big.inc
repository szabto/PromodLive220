#ifndef SPLITSCREEN_ENABLED
	#ifndef MAP_X
	#define MAP_X					(- (MAP_WIDTH - RIGHTITEM_OFFSET + 20 ))
	#endif
	
	#ifndef MAP_Y
	#define MAP_Y					114
	#endif
	
	#ifndef MAP_WIDTH
	#define MAP_WIDTH				240
	#endif
	
	#ifndef MAP_HEIGHT	
	#define MAP_HEIGHT				268
	#endif
	
	#define ORIGIN_MAP_FRAME		MAP_X MAP_Y
	#define MAP_WIDTH2				(MAP_WIDTH+5)
#else
	#ifndef MAP_X
	#define MAP_X					(- (MAP_WIDTH - RIGHTITEM_OFFSET+4 ))
	#endif
	
	#ifndef MAP_Y
	#define MAP_Y					47
	#endif
	
	#ifndef MAP_WIDTH
	#define MAP_WIDTH				140
	#endif
	
	#ifndef MAP_HEIGHT	
	#define MAP_HEIGHT				120
	#endif
	
	#define ORIGIN_MAP_FRAME		MAP_X MAP_Y
	#define MAP_WIDTH2				(MAP_WIDTH+5)
#endif

#ifndef TEAM_IS_MARINES
#error "TEAM_IS_MARINES undefined"
#endif

#ifndef TEAM_IS_OPFOR
#error "TEAM_IS_OPFOR undefined"
#endif

#define SHOULD_SHOW_MAP 1

// map display ================================================

#define UI_MAP_NAME		"@"+tablelookup("mp/mapsTable.csv",0,dvarString(mapname),3)
#define MAP_OFFSET		0 21 //2 20

	itemDef
   	{
		name			"mini_map2"
		rect			ORIGIN_MAP_FRAME MAP_WIDTH MAP_WIDTH RIGHTITEM_ALIGN VERTICAL_ALIGN_TOP
		origin			MAP_OFFSET
		forecolor		1 1 1 1
		background		"compass_map_default"
		ownerdraw		CG_PLAYER_FULLMAP_MAP
		visible			when ( SHOULD_SHOW_MAP );
		decoration
   	}

	itemDef
   	{
		style			WINDOW_STYLE_SHADER
		name			"mini_map2_overlay"
		rect			ORIGIN_MAP_FRAME MAP_WIDTH MAP_WIDTH RIGHTITEM_ALIGN VERTICAL_ALIGN_TOP
		origin			MAP_OFFSET
		forecolor		1 1 1 1
		exp				material( tableLookup( "mp/mapsTable.csv", 0, dvarString( mapname ), 7 ) )
		visible			when ( SHOULD_SHOW_MAP );
		decoration
   	}
   	
	// Objective pointers
	itemDef
	{
		name			"compasspointers2"
		rect			ORIGIN_MAP_FRAME MAP_WIDTH MAP_WIDTH RIGHTITEM_ALIGN VERTICAL_ALIGN_TOP
		origin			MAP_OFFSET
		forecolor		1 1 1 1
		background		"objective_line"
		ownerdraw		CG_PLAYER_FULLMAP_POINTERS
		visible			when ( SHOULD_SHOW_MAP );
		decoration
	}
   	// Friendlies pointers
	itemDef
	{
		name			"compassfriendlies2"
		rect			ORIGIN_MAP_FRAME MAP_WIDTH MAP_WIDTH RIGHTITEM_ALIGN VERTICAL_ALIGN_TOP
		origin			MAP_OFFSET
		forecolor		1 1 1 1
		background		"compassping_friendly"
		ownerdraw		CG_PLAYER_FULLMAP_FRIENDS
		visible			when ( SHOULD_SHOW_MAP );
		decoration
	}
   	// Enemy pings
	itemDef
	{
		name			"compassenemies2"
		rect			ORIGIN_MAP_FRAME MAP_WIDTH MAP_WIDTH RIGHTITEM_ALIGN VERTICAL_ALIGN_TOP
		origin			MAP_OFFSET
		forecolor		1 1 1 1
		background		"compassping_enemy"
		ownerdraw		CG_PLAYER_FULLMAP_ENEMIES
		visible			when ( dvarbool( ui_hud_hardcore ) == 0  );
		decoration
	}

	// Player direction indicator
	itemDef
	{
		name			"compassplayer2"
		rect			ORIGIN_MAP_FRAME MAP_WIDTH MAP_WIDTH RIGHTITEM_ALIGN VERTICAL_ALIGN_TOP
		origin			MAP_OFFSET
		forecolor		1 1 1 1
		background		"compassping_player"
		ownerdraw		CG_PLAYER_FULLMAP_PLAYER
		visible			when ( SHOULD_SHOW_MAP );
		decoration
	}
