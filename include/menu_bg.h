
//{{BLOCK(menu_bg)

//======================================================================
//
//	menu_bg, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 478 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 30592 + 2048 = 33152
//
//	Time-stamp: 2018-04-18, 12:17:46
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MENU_BG_H
#define GRIT_MENU_BG_H

#define menu_bgTilesLen 30592
extern const unsigned int menu_bgTiles[7648];

#define menu_bgMapLen 2048
extern const unsigned short menu_bgMap[1024];

#define menu_bgPalLen 512
extern const unsigned short menu_bgPal[256];

#endif // GRIT_MENU_BG_H

//}}BLOCK(menu_bg)
