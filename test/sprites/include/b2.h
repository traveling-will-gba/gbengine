
//{{BLOCK(b2)

//======================================================================
//
//	b2, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 421 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 13472 + 2048 = 16032
//
//	Time-stamp: 2018-11-13, 21:51:30
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_B2_H
#define GRIT_B2_H

#define b2TilesLen 13472
extern const unsigned int b2Tiles[3368];

#define b2MapLen 2048
extern const unsigned short b2Map[1024];

#define b2PalLen 512
extern const unsigned short b2Pal[256];

#endif // GRIT_B2_H

//}}BLOCK(b2)
