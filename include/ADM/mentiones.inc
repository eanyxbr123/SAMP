/*************************************************************************************************************************************
 *                                                                                                                                   *
 *                                                       )(   @mentiones   )(                                                        *
 *                                                                                                                                   *
 * Copyright © 2018 Abyss Morgan. All rights reserved.                                                                               *
 * Contributors: None                                                                                                                *
 *                                                                                                                                   *
 * Website:  adm.ct8.pl                                                                                                              *
 * Download: adm.ct8.pl/r/download                                                                                                   *
 *                                                                                                                                   *
 * Plugins: SScanf                                                                                                                   *
 * Modules: RGB                                                                                                                      *
 *                                                                                                                                   *
 * File Version: 1.0.0                                                                                                               *
 *                                                                                                                                   *
 * Functions:                                                                                                                        *
 * GetMentiones(playerid,text[],mention_color=0xCC0000FF,back_color=0xFFFFFFFF,max_len=sizeof(text));                                *
 *                                                                                                                                   *
 * Callbacks:                                                                                                                        *
 * OnPlayerMentioned(playerid,targetid);                                                                                             *
 *                                                                                                                                   *
 *************************************************************************************************************************************/

#if !defined sscanf
	#error [ADM] You need SScanf v2.8.2 (adm.ct8.pl/d/SScanf%202.8.2)
#endif

#if !defined _rgb_function
	#error [ADM] You need RGB.inc (adm.ct8.pl/d/RGB.inc)
#endif

#if defined _text_mentiones
	#endinput
#endif
#define _text_mentiones

forward OnPlayerMentioned(playerid,targetid);

stock GetMentiones(playerid,text[],mention_color=0xCC0000FF,back_color=0xFFFFFFFF,max_len=sizeof(text)){
	strreplace(text,"@@","@",.maxlength=max_len);
	new len = strlen(text), pos = 0, mentiones_start, mentiones_stop;
	while(mentiones_stop != -1 && pos < len && pos != -1 && (mentiones_start = strfind(text,"@",false,pos)) != -1){
		new p_name[MAX_PLAYER_NAME];
		
		mentiones_stop = strfind(text," ",false,mentiones_start);
		if(mentiones_stop == -1){
			strmid(p_name,text,mentiones_start+1,len);
		} else {
			strmid(p_name,text,mentiones_start+1,mentiones_stop);
		}
		pos += strlen(p_name) + 1;
		if(strlen(p_name) >= 3 && strlen(p_name) <= MAX_PLAYER_NAME){
			new targetid = INVALID_PLAYER_ID;
			sscanf(p_name,"u",targetid);
			if(IsPlayerConnected(targetid)){
				CallRemoteFunction("OnPlayerMentioned","ii",playerid,targetid);
				
				if(mentiones_stop != -1){
					strins(text,GetColorRGBA(back_color),mentiones_stop,max_len);
					pos += 4;
				}
				strins(text,GetColorRGBA(mention_color),mentiones_start,max_len);
				pos += 4;
				len = strlen(text);
			}
		}
	}
}

//EOF